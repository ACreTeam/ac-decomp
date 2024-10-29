from argparse import ArgumentParser
import os
import struct
import sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
import ninja_syntax  # noqa: E402


def convert_binary_to_vtx_c_source(src_path, dest_path, dyndep_path, stamp_path):
    out_paths = []
    with open(src_path, "rb") as binary_file:
        # Obtain file size, iterate in 0x20 byte chunks
        file_size = binary_file.seek(0, 2)
        binary_file.seek(0, 0)
        for i in range(0, file_size, 0x20):
            # Split the dest_path into multiple files depending on how many chunks there are
            name, ext = os.path.splitext(dest_path)
            file_name = f"{name}_{i // 0x20}{ext}"
            out_paths.append(file_name)
            # Only write the file if we're not generating a dyndep file
            if dyndep_path is None:
                with open(file_name, "w") as c_file:
                    # Iterate each chunk and parse out the data
                    for j in range(0, 0x20, 2):
                        # 2 bytes for each 16-bit palette entry
                        chunk = binary_file.read(2)

                        if len(chunk) < 2:
                            break

                        pal = struct.unpack(">H", chunk[0:2])  # 2 bytes

                        c_file.write(f"{hex(pal[0])}, ")
    if dyndep_path is not None:
        with open(dyndep_path, "w") as out:
            n = ninja_syntax.Writer(out)
            n.variable("ninja_dyndep_version", "1")
            n.build(stamp_path, "dyndep", implicit_outputs=out_paths)


def main():
    parser = ArgumentParser(
        description="Converts a binary file to a number of u16 palettes"
    )
    parser.add_argument("src_path", type=str, help="Binary source file path")
    parser.add_argument("dest_path", type=str, help="Destination C include file path")
    parser.add_argument("-d", "--dyndep", type=str, help="Ninja dyndep file path")
    parser.add_argument("-s", "--stamp", type=str, help="Stamp file path")
    args = parser.parse_args()

    if args.dyndep is not None and args.stamp is None:
        parser.error("dyndep requires stamp file to be set")

    convert_binary_to_vtx_c_source(
        args.src_path, args.dest_path, args.dyndep, args.stamp
    )

    # Touch the stamp file
    if args.dyndep is None and args.stamp is not None:
        with open(args.stamp, "w") as stamp_file:
            stamp_file.write("")


if __name__ == "__main__":
    main()
