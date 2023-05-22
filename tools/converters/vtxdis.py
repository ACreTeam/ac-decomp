from argparse import ArgumentParser
import struct

def convert_binary_to_vtx_c_source(src_path, dest_path):
  # Load data
  with open(src_path, "rb") as binary_file, open(dest_path, "w") as c_file:
    while True:
      chunk = binary_file.read(16)  # 16 bytes for each Vtx struct

      if len(chunk) < 16:
        break

      ob = struct.unpack(">hhh", chunk[0:6])  # 3 * 2 bytes
      flag = struct.unpack(">H", chunk[6:8])  # 2 bytes
      tc = struct.unpack(">hh", chunk[8:12])  # 2 * 2 bytes
      cn = struct.unpack(">BBBB", chunk[12:16])  # 4 * 1 byte

      c_file.write(f"  {{{ob[0]}, {ob[1]}, {ob[2]}, {flag[0]}, {tc[0]}, {tc[1]}, {cn[0]}, {cn[1]}, {cn[2]}, {cn[3]}}},\n")

def main():
  parser = ArgumentParser(description="Converts a binary file to an array of N64 Vtx type")
  parser.add_argument("src_path", type=str, help="Binary source file path")
  parser.add_argument("dest_path", type=str, help="Destination C include file path")

  args = parser.parse_args()
  convert_binary_to_vtx_c_source(args.src_path, args.dest_path)

if __name__ == '__main__':
  main()
