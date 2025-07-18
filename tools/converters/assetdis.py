from argparse import ArgumentParser
from gfxdis import convert_binary_to_gfx
from dataclasses import dataclass
import struct


@dataclass
class EVW_REF:
    symbol_name: str
    symbol_type: str


@dataclass
class EVW_ANIME_result:
    formatted_str: str
    referenced_objects: list[EVW_REF]


def anim_type_conv(anim_type: int):
    return {
        0: "EVW_ANIME_TYPE_SCROLL1",
        1: "EVW_ANIME_TYPE_SCROLL2",
        2: "EVW_ANIME_TYPE_COLREG_MANUAL",
        3: "EVW_ANIME_TYPE_COLREG_LINEAR",
        4: "EVW_ANIME_TYPE_COLREG_NONLINEAR",
        5: "EVW_ANIME_TYPE_TEXANIME",
    }.get(anim_type, str(anim_type))


def parse_evw_anime_data(buff: bytes, symbols: list[str]) -> EVW_ANIME_result:
    BUFF_SIZE = 8
    assert ((len(buff) % BUFF_SIZE) == 0)
    found_syms = []
    out_data = ""
    i = 0
    while True:
        b = buff[i:i+BUFF_SIZE]
        i += BUFF_SIZE
        if len(b) < BUFF_SIZE:
            break
        (segment, anim_type) = struct.unpack(">bxhxxxx", b)
        anim_type = anim_type_conv(anim_type)
        this_symbol_name = symbols.pop(0)
        vals = (segment, anim_type, this_symbol_name)
        out_data += f"\t{{ {', '.join([str(x) for x in vals])} }},\n"
        found_syms.append(EVW_REF(this_symbol_name, anim_type))
    return EVW_ANIME_result(out_data, found_syms)


def parse_evw_anime_col_prim(buff: bytes, symbols: list[str]):
    BUFF_SIZE = 5
    assert ((len(buff) % BUFF_SIZE) == 0)
    out_data = ""
    i = 0
    while True:
        b = buff[i:i+BUFF_SIZE]
        i += BUFF_SIZE
        if len(b) < BUFF_SIZE:
            break
        vals = struct.unpack(">BBBBB", b)
        out_data += f"\t{{ {', '.join([str(x) for x in vals])} }},\n"
    return EVW_ANIME_result(out_data, [])


def parse_evw_anime_col_env(buff: bytes, symbols: list[str]):
    BUFF_SIZE = 4
    assert ((len(buff) % BUFF_SIZE) == 0)
    out_data = ""
    i = 0
    while True:
        b = buff[i:i+BUFF_SIZE]
        i += BUFF_SIZE
        if len(b) < BUFF_SIZE:
            break
        vals = struct.unpack(">BBBB", b)
        out_data += f"\t{{ {', '.join([str(x) for x in vals])} }},\n"
    return EVW_ANIME_result(out_data, [])


def parse_evw_anime_colreg(buff: bytes, symbols: list[str]):
    BUFF_SIZE = 0x10
    assert ((len(buff) % BUFF_SIZE) == 0)
    found_syms = []
    out_data = ""
    i = 0
    while True:
        b = buff[i:i+BUFF_SIZE]
        i += BUFF_SIZE
        if len(b) < BUFF_SIZE:
            break
        (frame_count, key_count) = struct.unpack(">HHxxxxxxxxxxxx", b)
        prim_colors = symbols.pop(0)
        env_colors = symbols.pop(0)
        keyframes = symbols.pop(0)
        vals = (frame_count, key_count, prim_colors, env_colors, keyframes)
        out_data += f"\t{{ {', '.join([str(x) for x in vals])} }},\n"
        found_syms.append(EVW_REF(prim_colors, "EVW_ANIME_COL_PRIM"))
        found_syms.append(EVW_REF(env_colors, "EVW_ANIME_COL_ENV"))
        found_syms.append(EVW_REF(keyframes, "u16"))
    return EVW_ANIME_result(out_data, found_syms)


def parse_evw_anime_scroll(buff: bytes, symbols: list[str]):
    BUFF_SIZE = 4
    assert ((len(buff) % BUFF_SIZE) == 0)
    found_syms = []
    out_data = ""
    i = 0
    while True:
        b = buff[i:i+BUFF_SIZE]
        i += BUFF_SIZE
        if len(b) < BUFF_SIZE:
            break
        vals = struct.unpack(">bbBB", b)
        out_data += f"\t{{ {', '.join([str(x) for x in vals])} }},\n"
    return EVW_ANIME_result(out_data, found_syms)


def parse_evw_texanime(buff: bytes, symbols: list[str]):
    BUFF_SIZE = 0x10
    assert ((len(buff) % BUFF_SIZE) == 0)
    found_syms = []
    out_data = ""
    i = 0
    while True:
        b = buff[i:i+BUFF_SIZE]
        i += BUFF_SIZE
        if len(b) < BUFF_SIZE:
            break
        (frame_count, key_count) = struct.unpack(">HHxxxxxxxxxxxx", b)
        texture_tbl = symbols.pop(0)
        animation_pattern = symbols.pop(0)
        keyframes = symbols.pop(0)
        vals = (frame_count, key_count, texture_tbl,
                animation_pattern, keyframes)
        out_data += f"\t{{ {', '.join([str(x) for x in vals])} }},\n"
        found_syms.append(EVW_REF(texture_tbl, "VOID*_LIST"))
        found_syms.append(EVW_REF(animation_pattern, "u8"))
        found_syms.append(EVW_REF(keyframes, "u16"))
    return EVW_ANIME_result(out_data, found_syms)


def lookup_bins_and_symbols(lines: list[str], name: str):
    out_bin = bytearray()
    out_symbols = []
    begin_ind = 0
    end_ind = 0
    for i, line in enumerate(lines):
        if line.startswith(f".obj {name}"):
            begin_ind = i
        if line.startswith(f".endobj {name}"):
            end_ind = i
    data_lines = lines[begin_ind+1:end_ind]

    for line in data_lines:
        if ".4byte" in line:
            data = line.split(".4byte ")[1]
            try:
                out_bin.extend(int(data, 16).to_bytes(4, 'big'))
            except Exception as e:
                out_bin.extend(b'\0\0\0\0')
                out_symbols.append(data)
        elif ".rel" in line:
            out_bin.extend(b'\0\0\0\0')
            out_symbols.append(f"&{line.split(".rel ")[1].split(",")[0]}[xxx]")
    return out_bin, out_symbols


def convert_source_to_gfx_c_source(src_file, dest_path):
    with open(src_file) as f:
        lines = f.read().split("\n")

    includes = ["libforest/gbi_extensions.h", "PR/gbi.h", "evw_anime.h"]

    header = "\n".join([f'#include "{x}"' for x in includes]) + "\n"

    # found_objs = []
    found_types = []
    all_objs = []
    for line in lines:
        if line.startswith(".obj"):
            this_obj = line.split(" ")[1].strip(",")
            all_objs.append(this_obj)

            if this_obj.endswith("_v"):
                found_types.append((this_obj, "Vtx"))
            elif "_model" in this_obj:
                found_types.append((this_obj, "Gfx"))
            elif this_obj.endswith("evw_anime"):
                found_types.append((this_obj, "EVW_ANIME_DATA"))
            elif this_obj.endswith("_pal"):
                found_types.append((this_obj, "PAL"))
            elif this_obj.endswith("_tex"):
                found_types.append((this_obj, "TEX"))

    # we now have a list of all objects, and we have a partial mapping of what type they could have
    # what we want to do is go through all the objects we know, and get the out-data
    # there are some objs that will add to this list, we can queue them onto the list

    converted_types = {}
    # we now have a list of objects+type
    while len(found_types) > 0:
        obj_name, type = found_types.pop()
        if obj_name in converted_types:
            continue
        if type == "Vtx":
            data = f'#include "assets/{obj_name}.inc"'
            converted_types[obj_name] = (type, data, "")
        elif type == "Gfx":
            data = convert_binary_to_gfx(
                *lookup_bins_and_symbols(lines, obj_name))
            converted_types[obj_name] = (type, data, "")
        elif type == "PAL":
            data = f'#include "assets/{obj_name}.inc"'
            converted_types[obj_name] = ("u16", data, "ATTRIBUTE_ALIGN(32)")
        elif type == "TEX":
            data = f'#include "assets/{obj_name}.inc"'
            converted_types[obj_name] = ("u8", data, "ATTRIBUTE_ALIGN(32)")
        elif type == "EVW_ANIME_DATA":
            res = parse_evw_anime_data(
                *lookup_bins_and_symbols(lines, obj_name))
            data = res.formatted_str
            converted_types[obj_name] = (type, data, "")
            for ref in res.referenced_objects:
                found_types.insert(
                    0, (ref.symbol_name, ref.symbol_type))

        elif type in ["EVW_ANIME_TYPE_SCROLL1", "EVW_ANIME_TYPE_SCROLL2"]:
            res = parse_evw_anime_scroll(
                *lookup_bins_and_symbols(lines, obj_name))
            data = res.formatted_str
            converted_types[obj_name] = ("EVW_ANIME_SCROLL", data, "")
            for ref in res.referenced_objects:
                found_types.insert(
                    0, (ref.symbol_name, ref.symbol_type))
        elif type == "EVW_ANIME_TYPE_COLREG_MANUAL":
            res = parse_evw_anime_colreg(
                *lookup_bins_and_symbols(lines, obj_name))
            data = res.formatted_str
            converted_types[obj_name] = (type, data, "")
            for ref in res.referenced_objects:
                found_types.insert(
                    0, (ref.symbol_name, ref.symbol_type))
        elif type == "EVW_ANIME_TYPE_COLREG_LINEAR":
            res = parse_evw_anime_colreg(
                *lookup_bins_and_symbols(lines, obj_name))
            data = res.formatted_str
            converted_types[obj_name] = (type, data, "")
            for ref in res.referenced_objects:
                found_types.insert(
                    0, (ref.symbol_name, ref.symbol_type))
        elif type == "EVW_ANIME_TYPE_COLREG_NONLINEAR":
            res = parse_evw_anime_colreg(
                *lookup_bins_and_symbols(lines, obj_name))
            data = res.formatted_str
            converted_types[obj_name] = (type, data, "")
            for ref in res.referenced_objects:
                found_types.insert(
                    0, (ref.symbol_name, ref.symbol_type))
        elif type == "EVW_ANIME_TYPE_TEXANIME":
            res = parse_evw_texanime(
                *lookup_bins_and_symbols(lines, obj_name))
            data = res.formatted_str
            converted_types[obj_name] = (type, data, "")
            for ref in res.referenced_objects:
                found_types.insert(
                    0, (ref.symbol_name, ref.symbol_type))
        elif type == "EVW_ANIME_COL_PRIM":
            res = parse_evw_anime_col_prim(
                *lookup_bins_and_symbols(lines, obj_name))
            data = res.formatted_str
            converted_types[obj_name] = (type, data, "")
            for ref in res.referenced_objects:
                found_types.insert(
                    0, (ref.symbol_name, ref.symbol_type))
        elif type == "EVW_ANIME_COL_ENV":
            res = parse_evw_anime_col_env(
                *lookup_bins_and_symbols(lines, obj_name))
            data = res.formatted_str
            converted_types[obj_name] = (type, data, "")
            for ref in res.referenced_objects:
                found_types.insert(
                    0, (ref.symbol_name, ref.symbol_type))
        elif type == "u16":
            assert (False)
        elif type == "u8":
            assert (False)

    out = header + "\n\n"
    for obj in all_objs:
        this_type, out_data, align = converted_types.get(
            obj, (None, None, None))
        out += f"{this_type} {obj}[] {align}= {{ \n{out_data}\n}};\n\n"
    # print(out)
    with open(dest_path, "w") as f:
        f.write(out)


def main():
    parser = ArgumentParser(
        description="Converts a binary file into gfx calls"
    )
    parser.add_argument("src_path", type=str, help="Binary source file path")
    parser.add_argument("dest_path", type=str,
                        help="Destination C include file path")

    args = parser.parse_args()
    convert_source_to_gfx_c_source(args.src_path, args.dest_path)


if __name__ == "__main__":
    main()
