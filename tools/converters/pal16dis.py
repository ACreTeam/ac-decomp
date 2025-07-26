from argparse import ArgumentParser
import struct


def convert_binary_to_vtx_c_source(src_path, dest_path):
    # Load data
    with open(src_path, "rb") as binary_file, open(dest_path, "w") as c_file:
        all_bin = binary_file.read()
        # parse all data as an array of u16,
        # use tuple's str method to create "(1, 2, 3)", and then sub-string to remove the parentheses
        c_file.write(
            str(struct.unpack(">" + "H" * (len(all_bin) // 2), all_bin))[1:-1])


def main():
    parser = ArgumentParser(
        description="Converts a binary file to an array of u16 type"
    )
    parser.add_argument("src_path", type=str, help="Binary source file path")
    parser.add_argument("dest_path", type=str,
                        help="Destination C include file path")

    args = parser.parse_args()
    convert_binary_to_vtx_c_source(args.src_path, args.dest_path)


if __name__ == "__main__":
    main()
