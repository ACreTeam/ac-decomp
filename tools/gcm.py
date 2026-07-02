"""Minimal GameCube disc image (GCM / .iso, uncompressed) reader + single-file patcher.

Only supports plain "ISO"/GCM images (not WBFS/CISO/RVZ). Enough to read a single
file out of the disc and write a modified version back, without external tools.
"""

from __future__ import annotations

import struct
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, List, Optional, Tuple

# Disc header (boot.bin) field offsets.
_OFF_AUDIO_STREAM = 0x08
_OFF_DOL = 0x420
_OFF_FST = 0x424
_OFF_FST_SIZE = 0x428
_OFF_FST_MAX = 0x42C

_ENTRY_SIZE = 12


class GcmError(Exception):
    pass


@dataclass
class GcmFile:
    path: str          # full path like "files/forest_2nd.arc"
    name: str          # basename
    offset: int        # data offset on disc
    size: int          # data size
    entry_index: int   # index into the FST entry table
    entry_pos: int     # absolute byte position of this entry in the FST


class Gcm:
    def __init__(self, path: Path):
        self.path = Path(path)
        with open(self.path, "rb") as f:
            self.header = f.read(0x440)
            if len(self.header) < 0x440:
                raise GcmError("File too small to be a GCM/ISO image.")
            self.dol_offset = self._u32(self.header, _OFF_DOL)
            self.fst_offset = self._u32(self.header, _OFF_FST)
            self.fst_size = self._u32(self.header, _OFF_FST_SIZE)
            self.audio_streaming = self.header[_OFF_AUDIO_STREAM]
            f.seek(self.fst_offset)
            self.fst = f.read(self.fst_size)
        if len(self.fst) < _ENTRY_SIZE:
            raise GcmError("FST is empty or unreadable.")
        self.disc_size = self.path.stat().st_size
        self.files: List[GcmFile] = []
        self._parse_fst()

    @staticmethod
    def _u32(buf: bytes, off: int) -> int:
        return struct.unpack_from(">I", buf, off)[0]

    def _parse_fst(self) -> None:
        num_entries = self._u32(self.fst, 8)  # root entry length = total count
        str_table_off = num_entries * _ENTRY_SIZE
        if str_table_off > len(self.fst):
            raise GcmError("FST entry table exceeds FST size; not a valid image.")

        def name_at(name_off: int) -> str:
            start = str_table_off + name_off
            end = self.fst.find(b"\x00", start)
            if end < 0:
                end = len(self.fst)
            return self.fst[start:end].decode("shift_jis", errors="replace")

        # Stack of (dir_end_index, dir_path) to reconstruct full paths.
        stack: List[Tuple[int, str]] = [(num_entries, "")]
        for i in range(1, num_entries):
            pos = i * _ENTRY_SIZE
            flags = self.fst[pos]
            name_off = struct.unpack_from(">I", self.fst, pos)[0] & 0x00FFFFFF
            arg1 = self._u32(self.fst, pos + 4)
            arg2 = self._u32(self.fst, pos + 8)
            while len(stack) > 1 and i >= stack[-1][0]:
                stack.pop()
            parent_path = stack[-1][1]
            name = name_at(name_off)
            full = f"{parent_path}{name}" if not parent_path else f"{parent_path}/{name}"
            if flags & 1:  # directory
                stack.append((arg2, full))
            else:
                self.files.append(
                    GcmFile(path=full, name=name, offset=arg1, size=arg2,
                            entry_index=i, entry_pos=pos)
                )

    def find(self, path: str) -> Optional[GcmFile]:
        want = path.strip("/").lower()
        for gf in self.files:
            if gf.path.lower() == want:
                return gf
        # Fall back to basename match.
        base = want.rsplit("/", 1)[-1]
        for gf in self.files:
            if gf.name.lower() == base:
                return gf
        return None

    def read_file(self, gf: GcmFile) -> bytes:
        with open(self.path, "rb") as f:
            f.seek(gf.offset)
            return f.read(gf.size)

    def layout(self) -> Dict[str, int]:
        used_end = max((gf.offset + gf.size) for gf in self.files)
        used_end = max(used_end, self.fst_offset + self.fst_size)
        first_user = min((gf.offset for gf in self.files), default=self.fst_offset)
        return {
            "disc_size": self.disc_size,
            "fst_offset": self.fst_offset,
            "fst_size": self.fst_size,
            "dol_offset": self.dol_offset,
            "audio_streaming": self.audio_streaming,
            "file_count": len(self.files),
            "first_user_offset": first_user,
            "used_end": used_end,
            "free_after_used": self.disc_size - used_end,
        }

    def replace_file(self, gf: GcmFile, new_data: bytes, out_path: Path) -> Dict[str, int]:
        """Convenience wrapper around :meth:`replace_files` for a single file."""
        return self.replace_files([(gf, new_data)], out_path)[0]

    def replace_files(self, replacements, out_path: Path):
        """Write a copy of the disc to ``out_path`` with several files replaced
        at once and the FST updated accordingly.

        ``replacements`` is a list of ``(GcmFile, new_data)`` pairs. Each target
        file must be distinct. Only those files' data and their FST entries ever
        change; no other file moves. For each file, two cases:

        * ``len(new_data) <= gf.size`` - patch in place and zero-pad the slack.
        * otherwise - append the new data at an aligned position past the end of
          the disc (a shared, advancing cursor so multiple appended files never
          overlap), zero the old region, and repoint the FST entry.

        The huge region between the FST and the file cluster is *not* free space
        on this disc (the game reads it by absolute offset), so it is never used.
        """
        out_path = Path(out_path)
        same = out_path.resolve() == self.path.resolve()
        if not same:
            import shutil
            out_path.parent.mkdir(parents=True, exist_ok=True)
            shutil.copyfile(self.path, out_path)

        seen = set()
        results = []
        append_cursor = self.disc_size
        with open(out_path, "r+b") as f:
            for gf, new_data in replacements:
                if gf.entry_pos in seen:
                    raise GcmError(
                        f"File {gf.path} was given more than once in a single "
                        "replace_files call."
                    )
                seen.add(gf.entry_pos)

                old_size = gf.size
                entry_abs = self.fst_offset + gf.entry_pos
                if len(new_data) <= old_size:
                    f.seek(gf.offset)
                    f.write(new_data)
                    pad = old_size - len(new_data)
                    if pad:
                        f.write(b"\x00" * pad)
                    new_off = gf.offset
                    mode = "in-place"
                else:
                    new_off = (append_cursor + 0x1F) & ~0x1F
                    f.seek(new_off)
                    f.write(new_data)
                    # Zero the now-dead original region.
                    f.seek(gf.offset)
                    f.write(b"\x00" * old_size)
                    append_cursor = new_off + len(new_data)
                    mode = "appended"
                # Update the FST entry: [type|nameoff][offset][length].
                f.seek(entry_abs + 4)
                f.write(struct.pack(">II", new_off, len(new_data)))

                results.append({
                    "path": gf.path,
                    "old_offset": gf.offset,
                    "old_size": old_size,
                    "new_size": len(new_data),
                    "new_offset": new_off,
                    "mode": mode,
                })

        self.disc_size = max(self.disc_size, out_path.stat().st_size)
        for r in results:
            r["out_disc_size"] = self.disc_size
        return results
