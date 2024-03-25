import pyjkernel
import os
import argparse

def unpack_dir(archive: pyjkernel.JKRArchive, dir: str, verbose=False):
  if verbose:
    print('Dumping dir: ' + dir)
  # create all files
  for file in archive.list_files(dir):
    if verbose:
      print('Dumping file: ' + file.name)
    with open(os.path.join(dir, file.name), "wb") as f:
      f.write(archive.get_file(dir + os.sep + file.name).data)

  # create all subdirectories and recurse through them
  for subdir in archive.list_folders(dir):
    if not os.path.exists(dir + os.sep + subdir):
      os.mkdir(dir + os.sep + subdir)
    unpack_dir(archive, dir + os.sep + subdir, verbose)

def unpack_archive(path: str, out_path: str, verbose=False):
  archive = pyjkernel.from_archive_file(path, True)
  orig_dir = os.path.abspath(os.curdir)
  os.chdir(out_path)
  if not os.path.exists(archive.root_name):
    os.mkdir(archive.root_name)
  unpack_dir(archive, archive.root_name, verbose)
  os.chdir(orig_dir)

def pack_dir(archive: pyjkernel.JKRArchive, path: str, verbose=False):
  local_path = os.path.dirname(path)
  orig_dir = os.path.abspath(os.curdir)
  if local_path != "":
    os.chdir(local_path)
  local_root = os.path.basename(os.path.normpath(path))

  for root, dirs, files in os.walk(local_root):
    files.sort(key=lambda item: (item.lower(), item))
    for dir in dirs:
      archive.create_folder(root + os.sep + dir)

    for file in files:
      if verbose:
        print('Packing file: ' + root + os.sep + file)
      with open(root + os.sep + file, "rb") as f:
        archive.create_file(root + os.sep + file, bytearray(f.read()), pyjkernel.JKRPreloadType.ARAM)
  os.chdir(orig_dir)

def pack_archive(root_path: str, out_path: str, verbose=False):
  root_name = os.path.basename(os.path.normpath(root_path))
  archive = pyjkernel.create_new_archive(root_name)
  pack_dir(archive, root_path, verbose)
  pyjkernel.write_archive_file(archive, out_path, True, pyjkernel.jkrcomp.JKRCompression.NONE, 0)

def main():
  parser = argparse.ArgumentParser(description='Pack or unpack JSystem JKernel archives.')
  parser.add_argument('-v', help='Enable verbose logging.', required=False, action='store_true')
  parser.add_argument('path', help='The path of the folder to pack or archive file to unpack.')
  parser.add_argument('out', help='The path of the destination folder or file.')

  args = parser.parse_args()
  if os.path.isfile(args.path):
    unpack_archive(args.path, args.out, args.v)
  elif os.path.isdir(args.path):
    pack_archive(args.path, args.out, args.v)
  else:
    raise Exception('path is not a valid file or directory!')

if __name__ == '__main__':
  main()
