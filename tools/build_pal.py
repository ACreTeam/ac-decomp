#!/usr/bin/env python3
"""Build and hash-check all five PAL languages sequentially with fast MWCC."""

import argparse
import subprocess
import sys
from pathlib import Path


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("-j", "--jobs", type=int, help="parallel jobs within each build")
    args = parser.parse_args()
    if args.jobs is not None and args.jobs < 1:
        parser.error("--jobs must be positive")

    root = Path(__file__).resolve().parent.parent
    try:
        for language in ("en", "fr", "de", "it", "es"):
            version = f"GAFP01_00_{language}"
            print(f"\nBuilding {version}", flush=True)
            subprocess.run(
                [sys.executable, "configure.py", "--version", version, "--fast-mwcc"],
                cwd=root,
                check=True,
            )
            command = ["ninja"]
            if args.jobs is not None:
                command += ["-j", str(args.jobs)]
            subprocess.run(command + [f"build/{version}/ok"], cwd=root, check=True)
    except subprocess.CalledProcessError as error:
        print(f"Build stopped at {version} (exit {error.returncode}).", file=sys.stderr)
        return error.returncode
    except KeyboardInterrupt:
        return 130

    print("\nAll five PAL builds passed their hash checks.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
