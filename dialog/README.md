# Dynamic villager / character dialog

This folder drives a text rewrite pipeline. You edit a single JSON file, then
run **one command** to bake your rewritten text straight into a playable `.iso`.

Two kinds of text are supported:

- **`message`** — the main villager/character dialog (in `forest_2nd.arc`).
  Lives in [dialog.json](dialog.json).
- **`mail`** — the letters villagers send you (in `forest_1st.arc`). Lives in
  [mail.json](mail.json).

Both use the same commands and the same format; you pick which with
`--resource message` (default) or `--resource mail`.

## Quick start (single command → patched .iso)

```sh
# Dialog:
python tools/dialog_tool.py extract-iso \
  --iso "orig/GAFE01_00/Animal Crossing (USA).iso" \
  --out dialog/dialog.json --resource message

python tools/dialog_tool.py apply-iso \
  --iso "orig/GAFE01_00/Animal Crossing (USA).iso" \
  --json dialog/dialog.json \
  --out "build/GAFE01_00/Animal Crossing (USA) (dialog).iso"

# Mail (letters):
python tools/dialog_tool.py extract-iso \
  --iso "orig/GAFE01_00/Animal Crossing (USA).iso" \
  --out dialog/mail.json --resource mail

python tools/dialog_tool.py apply-iso \
  --iso "orig/GAFE01_00/Animal Crossing (USA).iso" \
  --json dialog/mail.json \
  --out "build/GAFE01_00/Animal Crossing (USA) (mail).iso"
```

Each `apply-iso` is the "single command" you re-run whenever you change that
text. It reads the original disc, rebuilds the relevant archive, and writes a
patched disc. Only that one archive (and its FST entry) ever changes; every
other file on the disc is left byte-for-byte identical. The `--resource` is read
automatically from the JSON, so you don't need to repeat it on `apply-iso`.

### Applying dialog *and* mail into one .iso

Pass multiple JSONs to a single `apply-iso` and all their changes are baked into
**one** output disc:

```sh
python tools/dialog_tool.py apply-iso \
  --iso "orig/GAFE01_00/Animal Crossing (USA).iso" \
  --json dialog/dialog.json dialog/mail.json \
  --out "build/GAFE01_00/Animal Crossing (USA) (modded).iso"
```

Each JSON declares its own resource, so the tool rebuilds `forest_2nd.arc`
(dialog) and `forest_1st.arc` (mail) and writes them both into the single
`(modded).iso`. Every other file on the disc stays byte-for-byte identical.

## How it works

Each resource is one or more `*_data.bin` / `*_data_table.bin` blob pairs inside
an archive: the data blob is concatenated text, and the table holds cumulative
end offsets that split it into individual entries. `mail` has four blobs
(`mail`, `maila`, `mailb`, `mailc`); each entry in `mail.json` is tagged with
its `group`.

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

## Editing the JSON

Each entry looks like this (mail entries also carry a `group`):

```json
{
  "group": "maila",
  "index": 1234,
  "label": "",
  "original": "Original text with <<CONTROL>> codes",
  "new": "Original text with <<CONTROL>> codes"
}
```

- Only change the **`new`** field. Leave `group`, `index`, `label`, and
  `original` alone (they are how the tool maps text back and shows you what it
  was).
- Keep every `<<...>>` **control code** intact — they drive text speed,
  colors, name/item substitution, line breaks, choices, message jumps, and
  termination. Removing `<<MSGEND>>`, `<<BTN>>`, `<<MSGCLEAR>>` or a
  pause/prompt code can corrupt the text box or break the conversation flow.
- Any entry with `"decode_error": true` could not be fully decoded; **do not
  edit it** — it is packed back byte-for-byte unchanged.
- Only the lines you actually change are re-encoded; every entry whose `new`
  still equals `original` keeps its exact original message bytes. (The
  `forest_2nd.arc` container itself is repacked, so its internal layout differs
  from the retail file, but the message content is preserved verbatim.)

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

