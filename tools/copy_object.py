"""Copy an object compiled under its source stem to its translation-unit name."""

import argparse
import shutil


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source")
    parser.add_argument("destination")
    args = parser.parse_args()
    shutil.copyfile(args.source, args.destination)


if __name__ == "__main__":
    main()
