#!/usr/bin/env python3
"""
Fix K&R prototype/definition conflicts for Apple Clang 17.

Apple Clang 17 hard-errors when a function has a typed prototype declaration
like `static void fn(TYPE* a, TYPE* b);` followed by a K&R-style empty-paren
definition `static void fn() { ... }`.

This script scans each .c file, collects all prototypes that have parameters,
and patches matching empty-paren definitions to use the prototype's parameter list.
"""

import re
import sys
import os
from pathlib import Path

# Match a function prototype with parameters (ends with semicolon)
# Captures: return-type + name, parameter list (non-empty)
# e.g.  static void Foo_bar(ACTOR* a, GAME* g);
PROTO_RE = re.compile(
    r'^((?:static\s+)?(?:[\w\s\*]+?)\s+(\w+))\s*\(([^)]+)\)\s*;',
    re.MULTILINE
)

# Match a K&R-style function definition with empty parens
# e.g.  static void Foo_bar() {
DEF_RE = re.compile(
    r'^((?:static\s+)?(?:[\w\s\*]+?)\s+(\w+))\s*\(\s*\)\s*\{',
    re.MULTILINE
)


def fix_file(path: Path) -> bool:
    """Return True if the file was modified."""
    text = path.read_text(encoding='utf-8', errors='replace')

    # Collect all prototypes with parameters: name -> param string
    protos = {}
    for m in PROTO_RE.finditer(text):
        params = m.group(3).strip()
        # Skip prototypes that are themselves empty or only 'void'
        if params.lower() in ('', 'void'):
            continue
        name = m.group(2)
        protos[name] = params

    if not protos:
        return False

    modified = False

    def replacer(m):
        nonlocal modified
        name = m.group(2)
        if name in protos:
            # Replace `funcname() {` with `funcname(params) {`
            original = m.group(0)
            fixed = m.group(1) + '(' + protos[name] + ') {'
            if fixed != original:
                modified = True
                return fixed
        return m.group(0)

    new_text = DEF_RE.sub(replacer, text)

    if modified:
        path.write_text(new_text, encoding='utf-8')

    return modified


def main():
    root = Path(sys.argv[1]) if len(sys.argv) > 1 else Path('src')
    # Exclude AUS sources (PAL variant — not compiled)
    sources = [
        p for p in root.rglob('*.c')
        if '/AUS/' not in str(p)
    ]

    changed = []
    for p in sorted(sources):
        if fix_file(p):
            changed.append(p)
            print(f'  fixed: {p}')

    print(f'\n{len(changed)} file(s) modified.')


if __name__ == '__main__':
    main()
