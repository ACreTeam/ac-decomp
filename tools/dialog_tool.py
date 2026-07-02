#!/usr/bin/env python3
"""dialog_tool.py - JSON-driven text editing for ac-decomp.

Animal Crossing stores editable text as pairs of binary blobs: a data blob of
concatenated text plus a table of big-endian ``u32`` *cumulative end offsets*.
Entry ``i`` occupies ``data[table[i-1] : table[i]]`` (entry 0 starts at offset
0) and the game looks entries up purely by integer index.

Two such resources are supported:

* ``message`` - the main villager/character dialog, in ``forest_2nd.arc`` as
  ``message_data.bin`` / ``message_data_table.bin`` (one group).
* ``mail`` - the letters villagers send, in ``forest_1st.arc`` split across four
  groups (``mail``, ``maila``, ``mailb``, ``mailc``), each its own
  ``*_data.bin`` / ``*_data_table.bin`` pair.

There is no per-villager grouping in the data itself: villagers of a given
personality share the same entries and the specific name is injected at runtime
via control codes such as ``<<STR_TALKNAME>>`` / ``<<STR_FREE0>>``. Because of
that, the natural editable unit is a single entry index (plus its group, for
multi-group resources like mail).

This tool provides these commands:

``extract`` / ``extract-iso``
    Read ``forest_2nd.arc`` (from a loose file or straight out of a GameCube
    ``.iso``) and produce a JSON file. Each entry contains the message
    ``index``, a best-effort ``label`` (a human friendly name for the ranges
    that are known from the source), the decoded ``original`` text and a ``new``
    field (pre-filled with the original) that you overwrite with your rewritten
    dialog.

``build``
    Read that JSON plus the original ``forest_2nd.arc`` and write a new
    ``forest_2nd.arc`` in which any entry whose ``new`` text differs from its
    ``original`` is re-encoded. Entries you did not touch are copied byte for
    byte from the source, so an untouched JSON reproduces the original archive
    exactly.

``apply-iso``
    The one-shot workflow: read the original ``.iso``, pull ``forest_2nd.arc``
    out of it, apply the JSON overrides, and write a patched ``.iso`` with the
    rebuilt archive. Only that one file (and its FST entry) changes.

The text codec (character map + control codes) is shared with ``msg_tool.py``.
Because ``msg_tool.CHAR_MAP`` contains a handful of duplicate glyphs, re-encoding
is not guaranteed to be byte-identical, which is exactly why unchanged entries
are preserved verbatim instead of being round-tripped.
"""

import argparse
import json
import os
import struct
import sys

# Ensure sibling modules (msg_tool, pyjkernel) are importable regardless of CWD.
_TOOLS_DIR = os.path.dirname(os.path.abspath(__file__))
if _TOOLS_DIR not in sys.path:
    sys.path.insert(0, _TOOLS_DIR)

import msg_tool  # noqa: E402  (shared text codec)
import pyjkernel  # noqa: E402  (RARC archive read/write)
import gcm  # noqa: E402  (GameCube disc image read/patch)

# Editable resources. Each resource lives in one archive and is made up of one
# or more (data, table) blob pairs, all in the same format (a text blob plus a
# table of big-endian u32 cumulative end offsets). "message" is the main dialog
# in forest_2nd.arc; "mail" is the letters villagers send, which live in
# forest_1st.arc split across four blobs.
RESOURCES = {
    "message": {
        "iso_path": "files/forest_2nd.arc",
        "arc_name": "forest_2nd.arc",
        "groups": [
            {"name": "message",
             "data": "message_data.bin",
             "table": "message_data_table.bin"},
        ],
    },
    "mail": {
        "iso_path": "files/forest_1st.arc",
        "arc_name": "forest_1st.arc",
        "groups": [
            {"name": "mail", "data": "mail_data.bin", "table": "mail_data_table.bin"},
            {"name": "maila", "data": "maila_data.bin", "table": "maila_data_table.bin"},
            {"name": "mailb", "data": "mailb_data.bin", "table": "mailb_data_table.bin"},
            {"name": "mailc", "data": "mailc_data.bin", "table": "mailc_data_table.bin"},
        ],
    },
}

DEFAULT_RESOURCE = "message"

JSON_VERSION = 1

# Best-effort labels for message ranges that are named in the source
# (see include/m_msg_data.h and friends). Anything not listed simply gets an
# empty label - it is purely a human-readable hint and never affects the build.
KNOWN_LABELS = {
    0x048A: "MSG_CARPETPEDDLER_START",
    0x1B93: "MSG_TOTAKEKE_START",
    0x2B54: "MSG_SANTA_WISH_FTR",
    0x2B55: "MSG_SANTA_WISH_WALL",
    0x2B56: "MSG_SANTA_WISH_CARPET",
    0x2B57: "MSG_SANTA_WISH_CLOTH",
    0x3280: "MSG_SONCHO_EVENTS",
    0x3391: "MSG_HARVEST_FESTIVAL",
    0x33F4: "MSG_SONCHO_LIGHTHOUSE_1",
    0x340B: "MSG_SONCHO_LIGHTHOUSE_2",
}

# Only the "message" resource has named ranges in the source.
RESOURCE_LABELS = {"message": KNOWN_LABELS}


class DialogError(Exception):
    """Raised for user-facing, recoverable errors."""


def _get_resource(name):
    """Return the resource definition for ``name`` (raises on unknown)."""
    try:
        return RESOURCES[name]
    except KeyError:
        raise DialogError(
            f"Unknown resource '{name}'. Choose one of: "
            + ", ".join(sorted(RESOURCES))
        )


# ---------------------------------------------------------------------------
# Archive helpers
# ---------------------------------------------------------------------------
def _walk_files(archive):
    """Yield ``(full_path, JKRArchiveFile)`` for every file in the archive."""

    def recurse(folder_path):
        for file in archive.list_files(folder_path):
            yield folder_path + "/" + file.name, file
        for sub in archive.list_folders(folder_path):
            yield from recurse(folder_path + "/" + sub)

    yield from recurse(archive.root_name)


def _find_resource_blobs(archive, resource):
    """Locate every ``(data, table)`` blob pair for ``resource``.

    Returns ``{group_name: (data_file, table_file)}``. Raises ``DialogError``
    when any expected blob is missing.
    """
    wanted = {}
    for group in resource["groups"]:
        wanted[group["data"].lower()] = (group["name"], "data")
        wanted[group["table"].lower()] = (group["name"], "table")

    found = {g["name"]: {"data": None, "table": None} for g in resource["groups"]}
    for _path, file in _walk_files(archive):
        key = wanted.get(file.name.lower())
        if key is not None:
            found[key[0]][key[1]] = file

    result = {}
    missing = []
    for group in resource["groups"]:
        data_file = found[group["name"]]["data"]
        table_file = found[group["name"]]["table"]
        if data_file is None:
            missing.append(group["data"])
        if table_file is None:
            missing.append(group["table"])
        result[group["name"]] = (data_file, table_file)

    if missing:
        raise DialogError(
            f"{resource['arc_name']} is missing: " + ", ".join(missing) + ". "
            f"Are you sure this is {resource['arc_name']}?"
        )
    return result


def _parse_table(table_bytes):
    """Parse the message table into a list of cumulative end offsets."""
    count = len(table_bytes) // 4
    return list(struct.unpack(">" + "I" * count, bytes(table_bytes[: count * 4])))


def _split_entries(data_bytes, table):
    """Split the concatenated data into ``[(index, raw_bytes), ...]``."""
    entries = []
    prev_end = 0
    for index, end in enumerate(table):
        # The table is monotonic; guard against malformed data just in case.
        start = 0 if index == 0 else prev_end
        if end < start:
            # Empty / placeholder entry - keep the index but no bytes.
            entries.append((index, b""))
            continue
        entries.append((index, bytes(data_bytes[start:end])))
        prev_end = end
    return entries


def _open_arc_bytes(raw):
    """Open a RARC archive from raw bytes, returning ``(archive, compression)``."""
    compression = pyjkernel.jkrcomp.check_compression(bytes(raw))
    archive = pyjkernel.from_archive_buffer(bytearray(raw), True)
    return archive, compression


def _load_arc(path):
    with open(path, "rb") as f:
        raw = f.read()
    return _open_arc_bytes(raw)


# ---------------------------------------------------------------------------
# Text codec (built on top of msg_tool's tables)
# ---------------------------------------------------------------------------
def decode_message(raw):
    """Decode raw message bytes into editable text with ``<<CMD>>`` tokens.

    Returns ``(text, had_error)``. ``had_error`` is True when a control code
    could not be decoded; such entries should not be edited by hand because
    re-encoding them is not possible. Their original bytes are preserved on
    build regardless.
    """
    parts = []
    had_error = False
    i = 0
    n = len(raw)
    while i < n:
        byte = raw[i]
        if byte == 0x7F:
            try:
                token, size = msg_tool.decode_control_code(bytearray(raw), i)
            except ValueError:
                had_error = True
                parts.append("<<RAW [%02X]>>" % byte)
                i += 1
                continue
            parts.append(token)
            i += size
        else:
            parts.append(msg_tool.CHAR_MAP[byte])
            i += 1
    return "".join(parts), had_error


def encode_message(text):
    """Encode editable text back into raw message bytes.

    Raises ``DialogError`` with a helpful message on invalid content.
    """
    try:
        return bytes(msg_tool.encode_entry(text))
    except ValueError as exc:
        raise DialogError(str(exc))


# ---------------------------------------------------------------------------
# extract
# ---------------------------------------------------------------------------
def _build_document(archive, resource_name, source_name, include_empty):
    """Decode every entry of ``resource_name`` in ``archive`` into a document.

    Returns ``(document, skipped_empty)``. Single-group resources (``message``)
    use a flat schema; multi-group resources (``mail``) tag each entry with its
    ``group``.
    """
    resource = _get_resource(resource_name)
    blobs = _find_resource_blobs(archive, resource)
    labels = RESOURCE_LABELS.get(resource_name, {})
    multi = len(resource["groups"]) > 1

    out_entries = []
    group_info = []
    skipped_empty = 0
    for group in resource["groups"]:
        name = group["name"]
        data_file, table_file = blobs[name]
        table = _parse_table(table_file.data)
        group_info.append({
            "name": name,
            "data_file": data_file.name,
            "table_file": table_file.name,
            "entry_count": len(table),
        })
        for index, raw in _split_entries(data_file.data, table):
            if len(raw) == 0 and not include_empty:
                skipped_empty += 1
                continue
            text, had_error = decode_message(raw)
            entry = {}
            if multi:
                entry["group"] = name
            entry["index"] = index
            entry["label"] = labels.get(index, "")
            entry["original"] = text
            entry["new"] = text
            if had_error:
                entry["decode_error"] = True
            out_entries.append(entry)

    document = {
        "version": JSON_VERSION,
        "resource": resource_name,
        "source_arc": source_name,
    }
    if multi:
        document["groups"] = group_info
    else:
        document["data_file"] = group_info[0]["data_file"]
        document["table_file"] = group_info[0]["table_file"]
        document["entry_count"] = group_info[0]["entry_count"]
    document["entries"] = out_entries
    return document, skipped_empty


def _write_document(document, out_path):
    os.makedirs(os.path.dirname(os.path.abspath(out_path)), exist_ok=True)
    with open(out_path, "w", encoding="utf-8") as f:
        json.dump(document, f, ensure_ascii=False, indent=2)


def cmd_extract(args):
    archive, _compression = _load_arc(args.arc)
    document, skipped_empty = _build_document(
        archive, args.resource, os.path.basename(args.arc), args.include_empty
    )
    _write_document(document, args.out)

    if not args.quiet:
        print(
            f"Extracted {len(document['entries'])} {args.resource} entry(ies) "
            f"({skipped_empty} empty skipped) to {args.out}"
        )


def cmd_extract_iso(args):
    resource = _get_resource(args.resource)
    disc = gcm.Gcm(args.iso)
    gf = disc.find(resource["iso_path"])
    if gf is None:
        raise DialogError(
            f"{args.iso} does not contain {resource['iso_path']}. "
            "Is this a US Animal Crossing GameCube disc image?"
        )
    archive, _compression = _open_arc_bytes(disc.read_file(gf))
    document, skipped_empty = _build_document(
        archive, args.resource, gf.name, args.include_empty
    )
    _write_document(document, args.out)

    if not args.quiet:
        print(
            f"Extracted {len(document['entries'])} {args.resource} entry(ies) "
            f"({skipped_empty} empty skipped) from {os.path.basename(args.iso)} "
            f"to {args.out}"
        )


# ---------------------------------------------------------------------------
# build
# ---------------------------------------------------------------------------
def _load_json(path):
    with open(path, "r", encoding="utf-8") as f:
        document = json.load(f)
    if not isinstance(document, dict) or "entries" not in document:
        raise DialogError(f"{path} is not a valid dialog JSON (missing 'entries').")
    return document


def _resolve_resource_name(document, override):
    """Pick the resource: explicit CLI override wins, else the JSON's own
    ``resource`` field, else the default (``message``) for legacy files."""
    name = override or document.get("resource") or DEFAULT_RESOURCE
    _get_resource(name)  # validate
    return name


def _collect_overrides(document, resource):
    """Return ``{group_name: {index: new_text}}`` for changed entries.

    Legacy single-group documents omit ``group`` on their entries; those are
    attributed to the resource's only group.
    """
    default_group = resource["groups"][0]["name"]
    valid_groups = {g["name"] for g in resource["groups"]}
    overrides = {g["name"]: {} for g in resource["groups"]}

    for entry in document["entries"]:
        try:
            index = int(entry["index"])
        except (KeyError, TypeError, ValueError):
            raise DialogError("An entry is missing a valid integer 'index'.")

        group = entry.get("group", default_group)
        if group not in valid_groups:
            raise DialogError(
                f"Entry {index} references unknown group '{group}' for "
                f"resource with groups {sorted(valid_groups)}."
            )

        new_text = entry.get("new")
        original_text = entry.get("original")
        if new_text is None or new_text == original_text:
            # Only re-encode entries that actually changed, keeping untouched
            # data byte-for-byte identical to the source.
            continue
        if entry.get("decode_error"):
            raise DialogError(
                f"Entry {index} (group '{group}') was flagged with decode_error "
                "and cannot be edited safely. Revert its 'new' text to match "
                "'original'."
            )
        overrides[group][index] = new_text
    return overrides


def _rebuild_message_bins(data_bytes, table, overrides):
    """Return ``(new_data, new_table)`` bytes with ``{index: new_text}``
    overrides applied.

    The table is recomputed as cumulative end offsets over the actual data, so
    it stays internally consistent even when an entry changes size. Unused
    trailing slots (whose original offset was 0) keep their 0 sentinel; every
    other slot gets the correct running offset.
    """
    entries = _split_entries(data_bytes, table)

    new_data = bytearray()
    new_table = bytearray()
    for index, raw in entries:
        if index in overrides:
            raw = encode_message(overrides[index])
        if len(raw) == 0 and index < len(table) and table[index] == 0:
            # Unused padding slot - preserve the original zero sentinel.
            new_table += struct.pack(">I", 0)
            continue
        new_data += raw
        new_table += struct.pack(">I", len(new_data))

    # Preserve the original data padding when nothing shifted, otherwise pad to
    # a 32-byte boundary to match the game's alignment expectations.
    if len(new_data) < len(data_bytes):
        new_data += data_bytes[len(new_data):]
    elif len(new_data) % 32 != 0:
        new_data += b"\x00" * (32 - (len(new_data) % 32))

    return bytes(new_data), bytes(new_table)


def _apply_overrides_to_archive(archive, resource, overrides_by_group):
    """Apply per-group overrides in-place to ``archive``.

    Only touches the resource's own blob pairs. Groups with no changes are left
    completely untouched, so re-packing reproduces the source bytes for them.
    """
    if not any(overrides_by_group.values()):
        return
    blobs = _find_resource_blobs(archive, resource)
    for group in resource["groups"]:
        overrides = overrides_by_group.get(group["name"])
        if not overrides:
            continue
        data_file, table_file = blobs[group["name"]]
        table = _parse_table(table_file.data)
        new_data, new_table = _rebuild_message_bins(data_file.data, table, overrides)
        data_file.data = bytearray(new_data)
        table_file.data = bytearray(new_table)


def _count_overrides(overrides_by_group):
    return sum(len(v) for v in overrides_by_group.values())


def _resolve_compression(name, detected):
    if name == "auto":
        return detected
    return {
        "none": pyjkernel.jkrcomp.JKRCompression.NONE,
        "szs": pyjkernel.jkrcomp.JKRCompression.SZS,
        "szp": pyjkernel.jkrcomp.JKRCompression.SZP,
    }[name]


def cmd_build(args):
    document = _load_json(args.json)
    resource_name = _resolve_resource_name(document, args.resource)
    resource = _get_resource(resource_name)
    overrides = _collect_overrides(document, resource)

    archive, compression = _load_arc(args.in_arc)
    compression = _resolve_compression(args.compression, compression)
    _apply_overrides_to_archive(archive, resource, overrides)

    os.makedirs(os.path.dirname(os.path.abspath(args.out_arc)), exist_ok=True)
    pyjkernel.write_archive_file(archive, args.out_arc, True, compression, 9)

    if not args.quiet:
        print(
            f"Applied {_count_overrides(overrides)} {resource_name} change(s); "
            f"wrote {args.out_arc}"
        )


def cmd_apply_iso(args):
    json_paths = args.json if isinstance(args.json, list) else [args.json]

    disc = gcm.Gcm(args.iso)

    # Merge overrides per resource so multiple JSONs targeting the same archive
    # (or the same resource) are applied together, and each archive is rebuilt
    # exactly once.
    order = []
    grouped = {}
    for jpath in json_paths:
        document = _load_json(jpath)
        resource_name = _resolve_resource_name(document, args.resource)
        resource = _get_resource(resource_name)
        overrides = _collect_overrides(document, resource)
        if resource_name not in grouped:
            grouped[resource_name] = {
                "resource": resource,
                "overrides": {g["name"]: {} for g in resource["groups"]},
                "count": 0,
            }
            order.append(resource_name)
        bucket = grouped[resource_name]
        for group_name, changes in overrides.items():
            bucket["overrides"][group_name].update(changes)
        bucket["count"] += _count_overrides(overrides)

    replacements = []
    summary = []
    for resource_name in order:
        bucket = grouped[resource_name]
        resource = bucket["resource"]
        gf = disc.find(resource["iso_path"])
        if gf is None:
            raise DialogError(
                f"{args.iso} does not contain {resource['iso_path']}. "
                "Is this a US Animal Crossing GameCube disc image?"
            )
        archive, compression = _open_arc_bytes(disc.read_file(gf))
        compression = _resolve_compression(args.compression, compression)
        _apply_overrides_to_archive(archive, resource, bucket["overrides"])
        new_arc = pyjkernel.write_archive_buffer(archive, True, compression, 9)
        replacements.append((gf, bytes(new_arc)))
        summary.append((resource_name, resource["iso_path"], bucket["count"]))

    out_iso = args.out or _default_out_iso(args.iso)
    if not args.quiet:
        print(f"Copying disc image to {out_iso} ...")
    results = disc.replace_files(replacements, out_iso)

    if not args.quiet:
        for (resource_name, iso_path, count), result in zip(summary, results):
            print(
                f"Applied {count} {resource_name} change(s) to {iso_path} "
                f"({result['old_size']} -> {result['new_size']} bytes, "
                f"{result['mode']})."
            )
        print(f"Wrote {out_iso}")


def _default_out_iso(in_iso):
    base, ext = os.path.splitext(in_iso)
    return f"{base} (dialog){ext or '.iso'}"


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------
def main(argv=None):
    parser = argparse.ArgumentParser(
        description="Extract or rebuild Animal Crossing dialog via JSON."
    )
    parser.add_argument(
        "-q", "--quiet", action="store_true", help="Suppress progress output."
    )
    sub = parser.add_subparsers(dest="command", required=True)

    p_extract = sub.add_parser(
        "extract", help="Decode an archive's text (dialog or mail) into JSON."
    )
    p_extract.add_argument(
        "--arc", required=True,
        help="Path to the source arc (forest_2nd.arc for message, forest_1st.arc for mail).",
    )
    p_extract.add_argument(
        "--out", required=True, help="Path of the JSON file to write."
    )
    p_extract.add_argument(
        "--resource", choices=sorted(RESOURCES), default=DEFAULT_RESOURCE,
        help="Which text set to extract (default: message).",
    )
    p_extract.add_argument(
        "--include-empty",
        action="store_true",
        help="Also emit empty/placeholder slots.",
    )
    p_extract.set_defaults(func=cmd_extract)

    p_extract_iso = sub.add_parser(
        "extract-iso",
        help="Decode dialog or mail straight out of a GameCube .iso into JSON.",
    )
    p_extract_iso.add_argument(
        "--iso", required=True, help="Path to the Animal Crossing .iso."
    )
    p_extract_iso.add_argument(
        "--out", required=True, help="Path of the JSON file to write."
    )
    p_extract_iso.add_argument(
        "--resource", choices=sorted(RESOURCES), default=DEFAULT_RESOURCE,
        help="Which text set to extract (default: message).",
    )
    p_extract_iso.add_argument(
        "--include-empty",
        action="store_true",
        help="Also emit empty/placeholder slots.",
    )
    p_extract_iso.set_defaults(func=cmd_extract_iso)

    p_build = sub.add_parser(
        "build", help="Apply a dialog/mail JSON back into its source arc."
    )
    p_build.add_argument("--json", required=True, help="Path to the JSON.")
    p_build.add_argument(
        "--in-arc", required=True, help="Path to the original source arc."
    )
    p_build.add_argument(
        "--out-arc", required=True, help="Path of the rebuilt arc."
    )
    p_build.add_argument(
        "--resource", choices=sorted(RESOURCES), default=None,
        help="Override the resource (default: read from the JSON, else message).",
    )
    p_build.add_argument(
        "--compression",
        choices=["auto", "none", "szs", "szp"],
        default="auto",
        help="Output compression (default: match the source archive).",
    )
    p_build.set_defaults(func=cmd_build)

    p_apply_iso = sub.add_parser(
        "apply-iso",
        help="One shot: apply a dialog/mail JSON and write a patched .iso.",
    )
    p_apply_iso.add_argument(
        "--iso", required=True, help="Path to the original Animal Crossing .iso."
    )
    p_apply_iso.add_argument(
        "--json", required=True, nargs="+",
        help="One or more JSON files to apply (e.g. dialog.json mail.json). "
             "All changes are baked into a single output .iso.",
    )
    p_apply_iso.add_argument(
        "--out",
        help="Path of the patched .iso (default: '<name> (dialog).iso').",
    )
    p_apply_iso.add_argument(
        "--resource", choices=sorted(RESOURCES), default=None,
        help="Override the resource (default: read from the JSON, else message).",
    )
    p_apply_iso.add_argument(
        "--compression",
        choices=["auto", "none", "szs", "szp"],
        default="auto",
        help="Archive compression (default: match the source archive).",
    )
    p_apply_iso.set_defaults(func=cmd_apply_iso)

    args = parser.parse_args(argv)
    try:
        args.func(args)
    except DialogError as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
