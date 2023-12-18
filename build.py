import subprocess
import sys
import os
import hashlib

# List of Ninja build targets
NINJA_BUILD_TARGETS = [ ['src/data/bin1', 'out/forest_1st.arc', 'dump/forest_1st.arc'], ['src/data/bin2', 'out/forest_2nd.arc', 'dump/forest_2nd.arc'] ]

def calculate_directory_hash(path, hash_func):
    if not os.path.isdir(path):
        raise NotADirectoryError(f"{path} is not a directory")
    
    hasher = hash_func()
    for root, dirs, files in os.walk(path):
        for names in files:
            filepath = os.path.join(root, names)
            try:
                with open(filepath, 'rb') as f:
                    while True:
                        data = f.read(65536)  # Read in chunks to handle large files
                        if not data:
                            break
                        hasher.update(data)
            except IOError:
                # Handle errors as needed
                pass
    return hasher.hexdigest()

def directory_changed(path, build_dir, hash_func=hashlib.md5):
    hash_file = os.path.join(build_dir, '.dirhash')
    current_hash = calculate_directory_hash(path, hash_func)
    try:
        with open(hash_file, 'r') as f:
            stored_hash = f.read()
    except FileNotFoundError:
        stored_hash = None

    if current_hash != stored_hash:
        os.makedirs(build_dir, exist_ok=True)
        with open(hash_file, 'w') as f:
            f.write(current_hash)
        return True
    return False

def run_ninja_build(target):
    try:
        subprocess.run(['ninja', '-v', target], check=True)
    except subprocess.CalledProcessError as e:
        print(f"Error running Ninja build for target {target}: {e}")
        sys.exit(1)

def check_and_dump_arc(target, dump):
    if not os.path.exists(target):
        assert os.path.exists(dump), f"Please add missing file: {dump}"
        print(f'Dumping {dump}')

        try:
            subprocess.run(['python3', 'tools/arc_tool.py', dump, os.path.dirname(target)])
        except subprocess.CalledProcessError as e:
            print(f"Error running arc_tool")
            sys.exit(1)

if __name__ == "__main__":
    for target in NINJA_BUILD_TARGETS:
        check_and_dump_arc(target[0], target[2])
        if directory_changed(target[0], 'build'):
            run_ninja_build(target[1])
        else:
            print(f"No changes in {target[0]}, skipping build.")
    try:
        subprocess.run(['ninja'], check=True)
    except subprocess.CalledProcessError as e:
        print(f"Error running Ninja build")
        sys.exit(1)
