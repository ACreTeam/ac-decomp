#!/usr/bin/env python3
"""dialog_tool.py - JSON-driven villager/character dialog for ac-decomp.

Animal Crossing stores *all* in-game dialog as two binary blobs that live
inside ``forest_2nd.arc``:

* ``message_data.bin``       - the raw text bytes for every message, concatenated.
* ``message_data_table.bin`` - a table of big-endian ``u32`` *cumulative end
                               offsets*. Entry ``i`` occupies
                               ``data[table[i-1] : table[i]]`` (entry 0 starts
                               at offset 0). The game looks messages up purely
                               by integer index (see ``mMsg_Get_BodyParam`` /
                               ``mMsg_LoadMsgData`` in ``src/game``).

There is no per-villager grouping in the data itself: every villager of a given
personality shares the same message entries and the specific name is injected at
runtime via control codes such as ``<<STR_TALKNAME>>``. Because of that, the
natural editable unit is a single message index.

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

# forest_2nd.arc's path inside a retail Animal Crossing GameCube disc.
ISO_ARC_PATH = "files/forest_2nd.arc"


DATA_FILE_NAME = "message_data.bin"
TABLE_FILE_NAME = "message_data_table.bin"

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


class DialogError(Exception):
    """Raised for user-facing, recoverable errors."""


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


def _find_message_files(archive):
    """Locate the message data + table files inside the archive.

    Returns ``(data_file, table_file)`` accessors. Raises ``DialogError`` when
    either is missing.
    """
    data_file = None
    table_file = None
    for _path, file in _walk_files(archive):
        name = file.name.lower()
        if name == DATA_FILE_NAME:
            data_file = file
        elif name == TABLE_FILE_NAME:
            table_file = file

    if data_file is None or table_file is None:
        missing = []
        if data_file is None:
            missing.append(DATA_FILE_NAME)
        if table_file is None:
            missing.append(TABLE_FILE_NAME)
        raise DialogError(
            "Archive does not contain " + " and ".join(missing) + ". "
            "Are you sure this is forest_2nd.arc?"
        )
    return data_file, table_file


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
def _build_document(archive, source_name, include_empty):
    """Decode every message in ``archive`` into a dialog JSON document.

    Returns ``(document, skipped_empty)``.
    """
    data_file, table_file = _find_message_files(archive)
    table = _parse_table(table_file.data)
    entries = _split_entries(data_file.data, table)

    out_entries = []
    skipped_empty = 0
    for index, raw in entries:
        if len(raw) == 0 and not include_empty:
            skipped_empty += 1
            continue
        text, had_error = decode_message(raw)
        entry = {
            "index": index,
            "label": KNOWN_LABELS.get(index, ""),
            "original": text,
            "new": text,
        }
        if had_error:
            entry["decode_error"] = True
        out_entries.append(entry)

    document = {
        "version": JSON_VERSION,
        "source_arc": source_name,
        "data_file": data_file.name,
        "table_file": table_file.name,
        "entry_count": len(table),
        "entries": out_entries,
    }
    return document, skipped_empty


def _write_document(document, out_path):
    os.makedirs(os.path.dirname(os.path.abspath(out_path)), exist_ok=True)
    with open(out_path, "w", encoding="utf-8") as f:
        json.dump(document, f, ensure_ascii=False, indent=2)


def cmd_extract(args):
    archive, _compression = _load_arc(args.arc)
    document, skipped_empty = _build_document(
        archive, os.path.basename(args.arc), args.include_empty
    )
    _write_document(document, args.out)

    if not args.quiet:
        print(
            f"Extracted {len(document['entries'])} message(s) "
            f"({skipped_empty} empty skipped) to {args.out}"
        )


def cmd_extract_iso(args):
    disc = gcm.Gcm(args.iso)
    gf = disc.find(ISO_ARC_PATH)
    if gf is None:
        raise DialogError(
            f"{args.iso} does not contain {ISO_ARC_PATH}. "
            "Is this a US Animal Crossing GameCube disc image?"
        )
    archive, _compression = _open_arc_bytes(disc.read_file(gf))
    document, skipped_empty = _build_document(archive, gf.name, args.include_empty)
    _write_document(document, args.out)

    if not args.quiet:
        print(
            f"Extracted {len(document['entries'])} message(s) "
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


def _collect_overrides(document):
    """Return ``{index: new_text}`` for entries whose text was changed."""
    overrides = {}
    for entry in document["entries"]:
        try:
            index = int(entry["index"])
        except (KeyError, TypeError, ValueError):
            raise DialogError("An entry is missing a valid integer 'index'.")

        new_text = entry.get("new")
        original_text = entry.get("original")
        if new_text is None:
            continue
        # Only re-encode entries that actually changed. This keeps untouched
        # data byte-for-byte identical to the source archive.
        if new_text == original_text:
            continue
        if entry.get("decode_error"):
            raise DialogError(
                f"Entry {index} was flagged with decode_error and cannot be "
                "edited safely. Revert its 'new' text to match 'original'."
            )
        overrides[index] = new_text
    return overrides


def _rebuild_message_bins(data_bytes, table, overrides):
    """Return ``(new_data, new_table)`` bytes with overrides applied."""
    entries = _split_entries(data_bytes, table)

    new_data = bytearray()
    new_table = bytearray()
    for index, raw in entries:
        if index in overrides:
            raw = encode_message(overrides[index])
        new_data += raw
        new_table += struct.pack(">I", len(new_data))

    # Preserve the original data padding when nothing shifted, otherwise pad to
    # a 32-byte boundary to match the game's alignment expectations.
    if len(new_data) < len(data_bytes):
        new_data += data_bytes[len(new_data):]
    elif len(new_data) % 32 != 0:
        new_data += b"\x00" * (32 - (len(new_data) % 32))

    return bytes(new_data), bytes(new_table)


def _apply_overrides_to_archive(archive, overrides):
    """Apply ``{index: new_text}`` overrides in-place to ``archive``.

    Only touches ``message_data.bin`` / ``message_data_table.bin``. When there
    are no overrides the archive is left completely untouched, so re-packing it
    reproduces the source bytes.
    """
    if not overrides:
        return
    data_file, table_file = _find_message_files(archive)
    table = _parse_table(table_file.data)
    new_data, new_table = _rebuild_message_bins(data_file.data, table, overrides)
    data_file.data = bytearray(new_data)
    table_file.data = bytearray(new_table)


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
    overrides = _collect_overrides(document)

    archive, compression = _load_arc(args.in_arc)
    compression = _resolve_compression(args.compression, compression)
    _apply_overrides_to_archive(archive, overrides)

    os.makedirs(os.path.dirname(os.path.abspath(args.out_arc)), exist_ok=True)
    pyjkernel.write_archive_file(archive, args.out_arc, True, compression, 9)

    if not args.quiet:
        print(
            f"Applied {len(overrides)} dialog change(s); wrote {args.out_arc}"
        )


def cmd_apply_iso(args):
    document = _load_json(args.json)
    overrides = _collect_overrides(document)

    disc = gcm.Gcm(args.iso)
    gf = disc.find(ISO_ARC_PATH)
    if gf is None:
        raise DialogError(
            f"{args.iso} does not contain {ISO_ARC_PATH}. "
            "Is this a US Animal Crossing GameCube disc image?"
        )

    archive, compression = _open_arc_bytes(disc.read_file(gf))
    compression = _resolve_compression(args.compression, compression)
    _apply_overrides_to_archive(archive, overrides)
    new_arc = pyjkernel.write_archive_buffer(archive, True, compression, 9)

    out_iso = args.out or _default_out_iso(args.iso)
    if not args.quiet:
        print(f"Copying disc image to {out_iso} ...")
    info = disc.replace_file(gf, bytes(new_arc), out_iso)

    if not args.quiet:
        print(
            f"Applied {len(overrides)} dialog change(s) to {ISO_ARC_PATH} "
            f"({info['old_size']} -> {info['new_size']} bytes, {info['mode']}).\n"
            f"Wrote {out_iso}"
        )


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
        "extract", help="Decode forest_2nd.arc dialog into an editable JSON file."
    )
    p_extract.add_argument(
        "--arc", required=True, help="Path to the source forest_2nd.arc."
    )
    p_extract.add_argument(
        "--out", required=True, help="Path of the JSON file to write."
    )
    p_extract.add_argument(
        "--include-empty",
        action="store_true",
        help="Also emit empty/placeholder message slots.",
    )
    p_extract.set_defaults(func=cmd_extract)

    p_extract_iso = sub.add_parser(
        "extract-iso",
        help="Decode dialog straight out of a GameCube .iso into a JSON file.",
    )
    p_extract_iso.add_argument(
        "--iso", required=True, help="Path to the Animal Crossing .iso."
    )
    p_extract_iso.add_argument(
        "--out", required=True, help="Path of the JSON file to write."
    )
    p_extract_iso.add_argument(
        "--include-empty",
        action="store_true",
        help="Also emit empty/placeholder message slots.",
    )
    p_extract_iso.set_defaults(func=cmd_extract_iso)

    p_build = sub.add_parser(
        "build", help="Apply a dialog JSON back into a forest_2nd.arc."
    )
    p_build.add_argument("--json", required=True, help="Path to the dialog JSON.")
    p_build.add_argument(
        "--in-arc", required=True, help="Path to the original forest_2nd.arc."
    )
    p_build.add_argument(
        "--out-arc", required=True, help="Path of the rebuilt forest_2nd.arc."
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
        help="One shot: apply a dialog JSON and write a patched .iso.",
    )
    p_apply_iso.add_argument(
        "--iso", required=True, help="Path to the original Animal Crossing .iso."
    )
    p_apply_iso.add_argument(
        "--json", required=True, help="Path to the dialog JSON."
    )
    p_apply_iso.add_argument(
        "--out",
        help="Path of the patched .iso (default: '<name> (dialog).iso').",
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
