#!/usr/bin/env python3
"""
Generate empty .inc stub files for all asset #includes that are missing.

Game source files embed binary data like:
    static u8 texture[] = {
    #include "assets/foo.inc"
    };

The .inc files contain comma-separated hex values extracted from the ROM.
Without the ROM we generate single-element stubs (just "0") so the arrays
have one placeholder byte and everything compiles.
"""

import re
import sys
from pathlib import Path

ASSET_INCLUDE_RE = re.compile(r'#include\s+"(assets/[^"]+\.inc)"')

def find_missing_incs(src_root: Path):
    """Return {inc_path_relative_to_src_file: absolute_path_where_to_create}."""
    missing = {}
    for c_file in sorted(src_root.rglob('*.c')) + sorted(src_root.rglob('*.c_inc')):
        if '/AUS/' in str(c_file):
            continue
        text = c_file.read_text(encoding='utf-8', errors='replace')
        for m in ASSET_INCLUDE_RE.finditer(text):
            rel = m.group(1)  # e.g. "assets/npc/tex/wol_1_pal.inc"
            # .inc is searched relative to the .c file's directory
            inc_abs = c_file.parent / rel
            if not inc_abs.exists():
                missing[inc_abs] = True
    return list(missing.keys())


def main():
    repo_root = Path(sys.argv[1]) if len(sys.argv) > 1 else Path('.')
    src_root = repo_root / 'src'
    if not src_root.exists():
        print(f'ERROR: src directory not found at {src_root}', file=sys.stderr)
        sys.exit(1)

    missing = find_missing_incs(src_root)
    if not missing:
        print('No missing .inc files found.')
        return

    created = 0
    for inc_path in sorted(missing):
        inc_path.parent.mkdir(parents=True, exist_ok=True)
        # Write a single placeholder byte so the array is non-empty
        inc_path.write_text('0\n', encoding='utf-8')
        created += 1

    print(f'Created {created} stub .inc file(s).')


if __name__ == '__main__':
    main()
