import argparse
import os
import subprocess
import sys
import numpy as np
from pathlib import Path
from PIL import Image

current_path = sys.path.copy()
sys.path.append(str(Path(__file__).parent.parent))
import common as c
sys.path = current_path

def unswizzle(input_list, width, height, pixels_per_block_w=8, pixels_per_block_h=8):
    if width * height > len(input_list):
        raise Exception(f"There are not enough elements in input_list for the specified Width and Height!"
                        f"\nExpected a length of {width * height}, but got a length of {len(input_list)}!")

    block_x_count = width // pixels_per_block_w
    block_y_count = height // pixels_per_block_h
    if block_y_count < 1:
        block_y_count = 1  # Hack for small textures -- Not sure if this is correct.

    output_buffer = [None] * len(input_list)
    pixel_index = 0

    for y_block in range(block_y_count):
        for x_block in range(block_x_count):
            for y_pixel in range(pixels_per_block_h):
                for x_pixel in range(pixels_per_block_w):
                    output_buffer_index = (width * pixels_per_block_h * y_block) + y_pixel * width + x_block * pixels_per_block_w + x_pixel
                    output_buffer[output_buffer_index] = input_list[pixel_index]
                    pixel_index += 1

    return output_buffer

def swizzle(input_list, width, height, pixels_per_block_w=8, pixels_per_block_h=8):
    if width * height > len(input_list):
        raise Exception(f"There are not enough elements in input_list for the specified Width and Height!\n"
                        f"Width = {width} | Height = {height} | Width * Height = {width * height} | Input List Length = {len(input_list)}")

    block_x_count = width // pixels_per_block_w
    block_y_count = height // pixels_per_block_h

    output_buffer = [None] * len(input_list)
    output_buffer_index = 0

    for y_block in range(block_y_count):
        for x_block in range(block_x_count):
            for y_pixel in range(pixels_per_block_h):
                for x_pixel in range(pixels_per_block_w):
                    pixel_index = (width * pixels_per_block_h * y_block) + y_pixel * width + x_block * pixels_per_block_w + x_pixel
                    output_buffer[output_buffer_index] = input_list[pixel_index]
                    output_buffer_index += 1

    return output_buffer

def read_rgb5a3_colors(input_bytes, n):
    """
    Reads N unsigned 16-bit values from an input bytearray as big-endian RGB5A3 colors.

    Args:
    - input_bytes (bytearray): The input bytearray.
    - n (int): The number of 16-bit values to read.

    Returns:
    - List of tuples representing RGB5A3 colors.
    """
    if len(input_bytes) < n * 2:
        raise ValueError("Input bytearray does not contain enough data for N colors")

    colors = []
    for i in range(n):
        # Extract 16-bit value for each color, assuming big-endian order
        color_value = int.from_bytes(input_bytes[i*2:i*2+2], 'big')
        colors.append(color_value)

    return colors

def to_argb8(pixel):
    if (pixel & 0x8000) == 0x8000:
        # No Alpha Channel
        a = 0xFF

        # Separate RGB from bits
        r = (pixel & 0x7C00) >> 10
        g = (pixel & 0x03E0) >> 5
        b = (pixel & 0x001F)

        # Convert to RGB8 values
        r = (r << (8 - 5)) | (r >> (10 - 8))
        g = (g << (8 - 5)) | (g >> (10 - 8))
        b = (b << (8 - 5)) | (b >> (10 - 8))
    else:
        # An Alpha Channel Exists, 3 bits for Alpha Channel and 4 bits each for RGB
        a = (pixel & 0x7000) >> 12
        r = (pixel & 0x0F00) >> 8
        g = (pixel & 0x00F0) >> 4
        b = (pixel & 0x000F)

        a = (a << (8 - 3)) | (a << (8 - 6)) | (a >> (9 - 8))
        r = (r << (8 - 4)) | r
        g = (g << (8 - 4)) | g
        b = (b << (8 - 4)) | b

    # Ensure the values are byte-sized (0-255)
    a = a & 0xFF
    r = r & 0xFF
    g = g & 0xFF
    b = b & 0xFF

    return r, g, b, a

def rgb5a3_to_argb8(colors):
    """
    Converts an array of RGB5A3 colors to standard ARGB8 colors.

    Args:
    - colors (List[int]): List of integers representing RGB5A3 colors.

    Returns:
    - List of tuples representing ARGB8 colors.
    """
    argb8_colors = []
    for color in colors:
        argb8_colors.append((to_argb8(color)))

    return argb8_colors

def extract_texture_asset(byte_array, width, height, tex_count):
    texture_data_size = (width * height) // 2
    entry_size = 2 * 16 + texture_data_size * tex_count
    n_entries = len(byte_array) // entry_size
    entries = []

    for entry_index in range(n_entries):
        offset = entry_index * entry_size
        palette_bytes = byte_array[offset:offset + 2 * 16]
        palette_colors = read_rgb5a3_colors(palette_bytes, 16)

        textures = []
        for texture_index in range(tex_count):
            texture_offset = offset + 2 * 16 + (texture_index * texture_data_size)
            texture_bytes = byte_array[texture_offset:texture_offset + texture_data_size]
            textures.append(texture_bytes)

        entries.append({'palette': palette_colors, 'textures': textures})

    return entries

def generate_c_source_entries_with_all_textures(entries, width):
    """
    Generates a list of C source strings from extracted palette and textures data.
    Each string contains one palette and all textures formatted for a C source file,
    where each entry is represented as a separate string in the list.

    Args:
    - entries (List[Dict]): Extracted data containing 'palette' and 'textures' for each entry.

    Returns:
    - List of strings, each representing the C source code for one entry including one palette and all textures.
    """
    c_source_entries = []
    for i, entry in enumerate(entries):
        c_source = ""
        # Palette
        c_source += f"// clang-format off\nunsigned short floor{i:02d}_pal[] = {{\n    "
        for j, color in enumerate(entry['palette']):
            c_source += f"0x{color:04X},"
            if (j + 1) % 8 == 0 and (j + 1) < 16:  # Newline after every 8 entries
                c_source += "\n    "
            else:
                c_source += " "
        c_source = c_source.rstrip(", \n") + "\n};\n// clang-format on\n\n"  # Remove trailing comma and add closing bracket

        # Textures
        c_source += f"// clang-format off\nunsigned char floor{i:02d}_tex[] = {{\n    // texture 0\n    "
        for texture_index, texture in enumerate(entry['textures']):
            for k, pixel in enumerate(texture):
                c_source += f"0x{pixel:02X},"
                if (k + 1) % (width // 2) == 0:  # Newline after width/2 texture pixels
                    if k + 1 != len(texture) or texture_index < len(entry['textures']) - 1:
                        c_source += "\n    "
                else:
                    c_source += " "
            if texture_index < len(entry['textures']) - 1:
                c_source += f"// texture {texture_index + 1}\n    "  # Add a newline after each texture except the last
        c_source = c_source.rstrip(", \n") + "\n};\n// clang-format on\n"  # Close texture array

        c_source_entries.append(c_source)

    return c_source_entries

def save_palette_as_hex(palette, directory_path):
    """
    Saves an RGB5A3 palette list to a text file with hex values.

    Args:
    - palette (List[int]): List of colors in RGB5A3 format.
    - directory_path (Path): The directory where 'palette.txt' will be saved.
    """
    # Ensure the directory exists
    directory_path.mkdir(parents=True, exist_ok=True)
    
    # Define the file path
    file_path = directory_path / 'palette.txt'
    
    with file_path.open(mode='w') as file:
        for color in palette:
            # Write each color as a hexadecimal value
            file.write(f'{color:04X}\n')

def save_textures_as_png(base_path, entries, width, height, base_name):
    for i, entry in enumerate(entries):
        folder_name = base_path / f"{base_name}{i:02d}"
        folder_name.mkdir(parents=True, exist_ok=True)  # Create the directory, including any necessary parent directories

        # Save RGB5A3 palette to 'palette.txt'
        save_palette_as_hex(entry['palette'], folder_name)

        # Convert to RGBA8
        palette = rgb5a3_to_argb8(entry['palette'])

        for j, texture_data in enumerate(entry['textures']):
            # Construct an image from the 4-bit indexed data
            img_data = bytearray(len(texture_data) * 2)  # Each byte in texture_data represents two pixels
            for idx, byte in enumerate(texture_data):
                img_data[idx * 2] = byte >> 4  # High nibble for the first pixel
                img_data[idx * 2 + 1] = byte & 0x0F  # Low nibble for the second pixel

            # Map the indexed pixels to RGBA using the palette
            rgba_img = [palette[pix] for pix in img_data]

            # Unswizzle the RGBA image data
            unswizzled_data = unswizzle(rgba_img, width, height)  # Assume unswizzle is defined elsewhere

            # Create the final image and save it
            img = Image.new("RGBA", (width, height))
            img.putdata(unswizzled_data)
            img_file_path = folder_name / f"texture{j:02d}.png"
            img.save(img_file_path)

def generate_includes(n, input_string):
    includes = ""
    for i in range(n):
        includes += f'#include "./{input_string}{i:02d}.c"\n'
    return includes

def extract_player_room_floor(byte_array: bytearray, out_dir: str):
    entries = extract_texture_asset(byte_array, 64, 64, 4)
    entry_sources = generate_c_source_entries_with_all_textures(entries, 64)
    Path(out_dir).mkdir(parents=True, exist_ok=True) # make dirs
    for i in range(len(entries)):
        path = Path(out_dir) / ('floor%02d.c' % i)
        with path.open("w") as f:
            f.write(entry_sources[i])
    save_textures_as_png(Path(out_dir) / 'tex', entries, 64, 64, "floor")

    # write aggregate file
    with (Path(out_dir) / 'player_room_floor.c').open('w') as f:
        f.write(generate_includes(len(entries), "floor"))

def extract_player_room_wall(byte_array: bytearray, out_dir: str):
    entries = extract_texture_asset(byte_array, 64, 64, 2)
    entry_sources = generate_c_source_entries_with_all_textures(entries, 64)
    Path(out_dir).mkdir(parents=True, exist_ok=True) # make dirs
    for i in range(len(entries)):
        path = Path(out_dir) / ('wall%02d.c' % i)
        with path.open("w") as f:
            f.write(entry_sources[i])
    save_textures_as_png(Path(out_dir) / 'tex', entries, 64, 64, "wall")

    # write aggregate file
    with (Path(out_dir) / 'player_room_wall.c').open('w') as f:
        f.write(generate_includes(len(entries), "wall"))

# packing
    
def rgba8_to_rgb5a3(r, g, b, a):
    if a >= 224:  # Treat as opaque
        return ((1 << 15) | ((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3))
    else:  # Use 3 bits for alpha
        return (((a >> 5) << 12) | ((r >> 4) << 8) | ((g >> 4) << 4) | (b >> 4))

def find_closest_color(color, palette):
    min_dist, index = float('inf'), -1
    for i, p in enumerate(palette):
        # Directly compare the integer values
        dist = (color - p) ** 2
        if dist < min_dist:
            min_dist, index = dist, i
    return index

def load_palette_from_hex(directory_path):
    """
    Loads an RGB5A3 palette list from a text file containing hex values.

    Args:
    - directory_path (Path): The directory where 'palette.txt' is located.

    Returns:
    - List[int]: List of colors in RGB5A3 format.
    """
    # Define the file path
    file_path = directory_path / 'palette.txt'
    
    palette = []
    with file_path.open(mode='r') as file:
        for line in file:
            # Convert each hexadecimal string back to an integer
            color = int(line.strip(), 16)
            palette.append(color)
    
    return palette

def process_png_image(image_path, palette):
    img = Image.open(image_path).convert("RGBA")
    pixels = np.array(img)
    
    # Create a texture map with indices
    texture_map = []
    for row in pixels:
        row_indices = []
        for r, g, b, a in row:
            rgb5a3 = rgba8_to_rgb5a3(r, g, b, a)
            closest_index = find_closest_color(rgb5a3, palette)
            row_indices.append(closest_index)
        texture_map.extend(row_indices)

    # Swizzle texture
    swizzled_texture = swizzle(texture_map, img.width, img.height)

    # Pack texture into 4bpp texels
    packed_texture_map = [0] * (len(swizzled_texture) // 2)
    for i, p in enumerate(swizzled_texture):
        if (i % 2) == 0:
            packed_texture_map[i // 2] = (p & 0xF) << 4
        else:
            packed_texture_map[i // 2] |= p & 0xF

    return packed_texture_map

def pack_player_room_floor(main_path: Path):
    objects = []
    for dir in (main_path / 'tex').iterdir():
        # load palette file
        palette = load_palette_from_hex(dir)

        # load texture00.png-texture03.png
        textures = []
        for i in range(0, 4):
            textures.append(process_png_image(dir / f'texture{i:02d}.png', palette))
        
        obj = {'palette': palette, 'textures': textures, 'idx': int(dir.name.replace('floor', ''))}
        objects.append(obj)

    # sort list
    objects.sort(key=lambda x: x['idx'])

    # process texture data into C source
    c_source = generate_c_source_entries_with_all_textures(objects, 64)

    # output C source to files
    for i in range(len(objects)):
        with (main_path / f'floor{i:02d}.c').open('w') as f:
            f.write(c_source[i])

    # build elf file and dump .data section
    os.chdir(str(Path(__file__).parent.parent))

    cmd = c.CC_R
    out_elf = main_path / f'{main_path.name}.o'

    if cmd.find('wibo') >= 0:
        subprocess.run(['wibo', './' + cmd.replace('wibo ', ''), f'-I{str(main_path)}', '-c', main_path / f'{main_path.name}.c', '-o', out_elf])
    else:
        subprocess.run([cmd, f'-I{str(main_path)}', '-c', main_path / f'{main_path.name}.c', '-o', out_elf])

    out_obj = main_path / f'{main_path.name}.bin'
    subprocess.run(['powerpc-eabi-objcopy', '--dump-section', f'.data={out_obj}', out_elf])

    # restore current dir
    os.chdir(str(Path(__file__).parent))

def pack_player_room_wall(main_path: Path):
    objects = []
    for dir in (main_path / 'tex').iterdir():
        # load palette file
        palette = load_palette_from_hex(dir)

        # load texture00.png-texture03.png
        textures = []
        for i in range(0, 2):
            textures.append(process_png_image(dir / f'texture{i:02d}.png', palette))
        
        obj = {'palette': palette, 'textures': textures, 'idx': int(dir.name.replace('wall', ''))}
        objects.append(obj)

    # sort list
    objects.sort(key=lambda x: x['idx'])

    # process texture data into C source
    c_source = generate_c_source_entries_with_all_textures(objects, 64)

    # output C source to files
    for i in range(len(objects)):
        with (main_path / f'wall{i:02d}.c').open('w') as f:
            f.write(c_source[i])

    # build elf file and dump .data section
    os.chdir(str(Path(__file__).parent.parent))

    cmd = c.CC_R
    out_elf = main_path / f'{main_path.name}.o'

    if cmd.find('wibo') >= 0:
        subprocess.run(['wibo', './' + cmd.replace('wibo ', ''), f'-I{str(main_path)}', '-c', main_path / f'{main_path.name}.c', '-o', out_elf])
    else:
        subprocess.run([cmd, f'-I{str(main_path)}', '-c', main_path / f'{main_path.name}.c', '-o', out_elf])

    out_obj = main_path / f'{main_path.name}.bin'
    subprocess.run(['powerpc-eabi-objcopy', '--dump-section', f'.data={out_obj}', out_elf])


def unpack():
    with open('src/data/bin2/data/player_room_floor.bin', 'rb') as f:
        extract_player_room_floor(bytearray(f.read()), 'src/data/item/player_room_floor')

    with open('src/data/bin2/data/player_room_wall.bin', 'rb') as f:
        extract_player_room_wall(bytearray(f.read()), 'src/data/item/player_room_wall')

def pack():
    cwd = os.getcwd()

    pack_player_room_floor(Path('src/data/item/player_room_floor'))
    os.chdir(cwd)

    pack_player_room_wall(Path('src/data/item/player_room_wall'))
    os.chdir(cwd)

def main():
    parser = argparse.ArgumentParser(description='Pack or dump Animal Crossing player_room_[floor][wall].bin files.')
    parser.add_argument('-m', help="The mode to run. Valid arguments are un[pack].")

    args = parser.parse_args()
    
    if args.m.lower() == "pack":
        pack()
    elif args.m.lower() == "unpack":        
        unpack()
    else:
        raise Exception(f'Invalid mode! Please use -m un[pack]')

if __name__ == '__main__':
    main()
