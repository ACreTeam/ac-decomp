from argparse import ArgumentParser
import struct

def convert_binary_to_vtx_c_source(src_path, dest_path):
  # Load data
  with open(src_path, "rb") as binary_file, open(dest_path, "w") as c_file:
    while True:
      chunk = binary_file.read(2)  # 2 bytes for each 16-bit palette entry

      if len(chunk) < 2:
        break

      pal = struct.unpack(">H", chunk[0:2])  # 2 bytes

      c_file.write(f"{hex(pal[0])}, ")

def main():
  parser = ArgumentParser(description="Converts a binary file to an array of u16 type")
  parser.add_argument("src_path", type=str, help="Binary source file path")
  parser.add_argument("dest_path", type=str, help="Destination C include file path")

  args = parser.parse_args()
  convert_binary_to_vtx_c_source(args.src_path, args.dest_path)

if __name__ == '__main__':
  main()