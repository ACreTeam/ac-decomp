# Dynamic villager / character dialog

This folder drives a dialog rewrite pipeline. You edit a single JSON file, then
run **one command** to bake your rewritten text straight into a playable `.iso`.

## Quick start (single command → patched .iso)

```sh
# 1. Pull the editable dialog out of your game disc (run once):
python tools/dialog_tool.py extract-iso \
  --iso "orig/GAFE01_00/Animal Crossing (USA).iso" \
  --out dialog/dialog.json

# 2. Edit the "new" fields in dialog/dialog.json (see below).

# 3. Bake the changes into a new .iso in one shot:
python tools/dialog_tool.py apply-iso \
  --iso "orig/GAFE01_00/Animal Crossing (USA).iso" \
  --json dialog/dialog.json \
  --out "build/GAFE01_00/Animal Crossing (USA) (dialog).iso"
```

Load the produced `.iso` in Dolphin. Step 3 is the "single command" you re-run
whenever you change dialog — it reads the original disc, rebuilds
`forest_2nd.arc` with your text, and writes a patched disc. Only that one file
(and its FST entry) ever changes; every other file on the disc is left
byte-for-byte identical.

## How it works

All in-game dialog lives inside `forest_2nd.arc` as two binary blobs:

- `message_data.bin` — raw concatenated message text
- `message_data_table.bin` — cumulative end offsets that split the text into
  individual messages

The tool [`tools/dialog_tool.py`](../tools/dialog_tool.py) reads and rewrites
those blobs for you; you never touch the binaries directly. The disc itself is
read/patched by [`tools/gcm.py`](../tools/gcm.py) (a minimal GameCube disc
patcher) — no external tools like `wit` are required.

## Why messages are indexed, not per-villager

Villager dialog is **personality-based**, not per-character. The game stores one
shared pool of lines per personality and injects the specific villager's name at
runtime via control codes (e.g. `<<STR_TALKNAME>>`). So the natural unit of
editing is a single **message index**. Each JSON entry carries a best-effort
`label` (derived from known message-table ranges) to help you orient yourself,
but there is no reliable one-to-one "this line belongs to villager X" mapping.

## Editing `dialog/dialog.json`

Each entry looks like:

```json
{
  "index": 1234,
  "label": "MSG_...",
  "original": "Original text with <<CONTROL>> codes<<MSGEND>>",
  "new": "Original text with <<CONTROL>> codes<<MSGEND>>"
}
```

- Only change the **`new`** field. Leave `index`, `label`, and `original`
  alone (they are how the tool maps text back and shows you what it was).
- Keep every `<<...>>` **control code** intact — they drive text speed,
  colors, name/item substitution, line breaks, choices, message jumps, and
  termination. Removing `<<MSGEND>>`, `<<BTN>>`, `<<MSGCLEAR>>` or a
  pause/prompt code can corrupt the text box or break the conversation flow.
- Any entry with `"decode_error": true` could not be fully decoded; **do not
  edit it** — it is packed back byte-for-byte unchanged.
- Entries whose `new` still equals `original` are packed byte-for-byte
  unchanged, so an unedited JSON reproduces a **byte-identical** disc.

Keeping each visible line roughly the same length as the original avoids
overflowing the in-game text window.

## Alternative: pack a loose `forest_2nd.arc` / wire into `ninja`

If you'd rather work with an extracted archive instead of the `.iso`:

```sh
# extract from a loose arc
python tools/dialog_tool.py extract --arc dump/forest_2nd.arc --out dialog/dialog.json

# repack a loose arc
python tools/dialog_tool.py build --json dialog/dialog.json \
  --in-arc dump/forest_2nd.arc --out-arc build/GAFE01_00/forest_2nd.arc
```

`configure.py` also auto-wires an **optional** post-build step: if
`dialog/dialog.json` exists *and* a source arc is found (in `dump/`,
`orig/GAFE01_00/`, or `orig/GAFE01_00/files/`), a plain `ninja` regenerates
`build/GAFE01_00/forest_2nd.arc` with your changes. If neither exists, the
dialog step is silently skipped and the normal matching build is unaffected.

Add `--compression {auto,none,szs,szp}` to any pack command to override archive
compression (`auto`, the default, preserves whatever the source used).

## Safety notes

- `apply-iso` copies your disc image and patches the copy; it never modifies the
  original `.iso` unless you explicitly point `--out` at it.
- Only `forest_2nd.arc`'s data and its single FST entry change — every other
  file on the disc stays byte-for-byte identical (verified for `famicom.arc`,
  `forest_1st.arc`, etc.).
- Nothing here touches the DOL/REL matching build or any source under `src/`.
- Text re-encoding is only applied to entries you actually change; everything
  else is copied verbatim, so you can't accidentally corrupt untouched lines.

