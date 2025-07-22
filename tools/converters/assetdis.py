from argparse import ArgumentParser
from gfxdis import convert_binary_to_gfx
from dataclasses import dataclass
import struct

ASSET_ALIGN = "ATTRIBUTE_ALIGN(32)"
NO_ALIGN = ""


@dataclass
class struct_ref:
    symbol_name: str
    symbol_type: str


@dataclass
class struct_parse_result:
    formatted_str: str
    referenced_objects: list[struct_ref]


def anim_type_conv(anim_type: int):
    return {
        0: "EVW_ANIME_TYPE_SCROLL1",
        1: "EVW_ANIME_TYPE_SCROLL2",
        2: "EVW_ANIME_TYPE_COLREG_MANUAL",
        3: "EVW_ANIME_TYPE_COLREG_LINEAR",
        4: "EVW_ANIME_TYPE_COLREG_NONLINEAR",
        5: "EVW_ANIME_TYPE_TEXANIME",
    }.get(anim_type, str(anim_type))


def parse_bin_formatted(buff: bytes, in_format: list[tuple[str, str]], _symbols: dict[int, str], val_conv: callable = None, type_conv: callable = None):
    struct_format = ">"
    symbols_offsets = {}
    symbol_order = []
    reloc_symbols = set()

    for format_pair in in_format:
        if format_pair == None:
            struct_format += "x"
            continue

        this_offset = struct.calcsize(struct_format)
        struct_type, name = format_pair

        if struct_type == "p":
            reloc_symbols.add(name)
            struct_type = "xxxx"

        struct_format += struct_type
        symbols_offsets[name] = this_offset
        symbol_order.append(name)

    BUFF_SIZE = struct.calcsize(struct_format)
    assert ((len(buff) % BUFF_SIZE) == 0)
    found_syms = []
    out_c_data = []
    i = 0
    for i in range(0, len(buff), BUFF_SIZE):
        b = buff[i:i+BUFF_SIZE]
        if len(b) < BUFF_SIZE:
            break
        extracted_data: list[int] = list(struct.unpack(struct_format, b))

        collapsed_data = {}

        for this_symbol_name in symbol_order:
            if this_symbol_name in reloc_symbols:
                ref_name = _symbols.get(
                    i + symbols_offsets[this_symbol_name], "NULL")

                collapsed_data[this_symbol_name] = ref_name
            else:
                collapsed_data[this_symbol_name] = extracted_data.pop(0)

        new_converted_vals = {}

        if val_conv:
            for name, val in collapsed_data.items():
                new_val = val_conv(name, val, dict(collapsed_data))
                if new_val != None:
                    new_converted_vals[name] = new_val

        collapsed_data.update(new_converted_vals)

        if type_conv:
            for name, value in collapsed_data.items():
                new_type = type_conv(name, dict(collapsed_data))
                if new_type != None:
                    found_syms.append(struct_ref(value, new_type))

        vals = collapsed_data.values()
        out_c_data.append(f"\t{{ {', '.join([str(x) for x in vals])} }}")

    return struct_parse_result(",\n".join(out_c_data), found_syms)


def parse_evw_anime_data(buff: bytes, symbols) -> struct_parse_result:
    this_format = [("b", "segment"), None, ("h", "anim_type"),
                   ("p", "this_symbol_name")]

    def vcf(name, value, all_values):
        if name == "anim_type":
            return anim_type_conv(value)

    def tcf(name, all_values):
        if name == "this_symbol_name":
            return all_values["anim_type"]

    return parse_bin_formatted(buff, this_format, symbols, vcf, tcf)


def parse_evw_anime_col_prim(buff: bytes, symbols):
    this_format = [("B", "r"), ("B", "g"), ("B", "b"), ("B", "a"), ("B", "l")]
    return parse_bin_formatted(buff, this_format, symbols)


def parse_evw_anime_col_env(buff: bytes, symbols: list[str]):
    this_format = [("B", "r"), ("B", "g"), ("B", "b"), ("B", "a")]
    return parse_bin_formatted(buff, this_format, symbols)


def parse_evw_anime_colreg(buff: bytes, symbols: list[str]):
    this_format = [("H", "prim_colors"), ("H", "key_count"),
                   ("p", "prim_colors"), ("p", "env_colors"), ("p", "keyframes")]

    def tcf(name, symbols):
        return {
            "prim_colors": "EVW_ANIME_COL_PRIM",
            "env_colors": "EVW_ANIME_COL_ENV",
            "keyframes": "u16",
        }.get(name, None)
    return parse_bin_formatted(buff, this_format, symbols, type_conv=tcf)


def parse_evw_anime_scroll(buff: bytes, symbols: list[str]):
    this_format = [("b", "x"), ("b", "y"), ("B", "width"), ("B", "height")]
    return parse_bin_formatted(buff, this_format, symbols)


def parse_evw_texanime(buff: bytes, symbols: list[str]):
    this_format = [("H", "frame_count"), ("H", "key_count"), ("p",
                                                              "texture_tbl"), ("p", "animation_pattern"), ("p", "keyframes")]

    def tcf(name, symbols):
        return {
            "texture_tbl": "VOID*_LIST",
            "animation_pattern": "u8",
            "keyframes": "u16",
        }.get(name, None)
    return parse_bin_formatted(buff, this_format, symbols, type_conv=tcf)


def parse_cKF_Skeleton_R_c(buff: bytes, symbols: list[str]):
    this_format = [("B", "num_joints"), ("B", "num_shown_joints"),
                   None, None, ("p", "joint_table")]

    def tcf(name, symbols):
        return {
            "joint_table": "cKF_Joint_R_c",
        }.get(name, None)

    def vcf(name, value, symbols):
        if name == "num_joints":
            return f"ARRAY_COUNT({symbols["joint_table"]})"

    return parse_bin_formatted(buff, this_format, symbols, vcf, tcf)


def parse_cKF_Animation_R_c(buff: bytes, symbols: list[str]):
    this_format = [("p", "flag_table"), ("p", "data_table"),
                   ("p", "key_table"), ("p", "fixed_table"), ("h", "pad"), ("h", "frames")]

    def tcf(name, symbols):
        return {
            "flag_table": "u8",
            "data_table": "s16",
            "key_table": "s16",
            "fixed_table": "s16",
        }.get(name, None)

    def vcf(name, value, symbols):
        if name == "x":
            return f"{{ {value}"
        if name == "z":
            return f"{value} }}"
    return parse_bin_formatted(buff, this_format, symbols, vcf, tcf)


def parse_cKF_Joint_R_c(buff: bytes, symbols: list[str]):
    this_format = [("p", "model"), ("B", "child"),
                   ("B", "flags"), ("H", "x"), ("H", "y"), ("H", "z")]

    def tcf(name, symbols):
        return {
            "joint_table": "Gfx",
        }.get(name, None)

    def vcf(name, value, symbols):
        if name == "x":
            return f"{{ {value}"
        if name == "z":
            return f"{value} }}"
        if name == "flags":
            return {
                0: "cKF_JOINT_FLAG_DISP_OPA",
                1: "cKF_JOINT_FLAG_DISP_XLU"
            }.get(value, None)
    return parse_bin_formatted(buff, this_format, symbols, vcf, tcf)


def parse_u16(buff: bytes, symbols: list[str]):
    vals = struct.unpack(">" + "H" * (len(buff) // 2), buff)
    out_str = ",\n".join(str(x) for x in vals)
    return struct_parse_result(out_str, [])


def parse_s16(buff: bytes, symbols: list[str]):
    vals = struct.unpack(">" + "h" * (len(buff) // 2), buff)
    out_str = ",\n".join(str(x) for x in vals)
    return struct_parse_result(out_str, [])


def parse_u8(buff: bytes, symbols: list[str]):
    vals = struct.unpack(">" + "B" * len(buff), buff)
    out_str = ",\n".join(str(x) for x in vals)
    return struct_parse_result(out_str, [])


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
            out_symbols.append(f"&{line.split(".rel ")[1].split(",")[0]}[0]")
        elif ".byte" in line:
            data = line.split(".byte ")[1]
            out_bin.extend(int(data, 16).to_bytes(1, 'big'))

    return out_bin, out_symbols


def lookup_static(lines: list[str], name: str):
    lookfor = f".obj {name}"
    for line in lines:
        if line.startswith(lookfor):
            if line.startswith(lookfor + ", local"):
                return "static "
            else:
                return ""
    return ""


def lookup_bins_and_symbols2(lines: list[str], name: str):
    out_bin = bytearray()
    out_symbols = {}
    begin_ind = 0
    end_ind = 0
    for i, line in enumerate(lines):
        if line.startswith(f".obj {name}"):
            begin_ind = i
        if line.startswith(f".endobj {name}"):
            end_ind = i
    data_lines = lines[begin_ind+1:end_ind]
    offset_count = 0
    for line in data_lines:
        if ".4byte" in line:
            data = line.split(".4byte ")[1]
            try:
                out_bin.extend(int(data, 16).to_bytes(4, 'big'))
            except Exception as e:
                out_bin.extend(b'\0\0\0\0')
                out_symbols[offset_count] = data
            offset_count += 4
        elif ".2byte" in line:
            data = line.split(".2byte ")[1]
            out_bin.extend(int(data, 16).to_bytes(2, 'big'))
            offset_count += 2
        elif ".byte" in line:
            data = line.split(".byte ")[1]
            if ", " in data:
                for d in data.split(", "):
                    out_bin.extend(int(d, 16).to_bytes(1, 'big'))
                    offset_count += 1
            else:
                out_bin.extend(int(data, 16).to_bytes(1, 'big'))
                offset_count += 1

        elif ".rel" in line:
            out_bin.extend(b'\0\0\0\0')
            data = f"&{line.split(".rel ")[1].split(",")[0]}[xxx]"
            out_symbols[offset_count] = data
            offset_count += 4
        else:
            assert (False), line
    return out_bin, out_symbols


def convert_source_to_gfx_c_source(src_file, dest_path):
    with open(src_file) as f:
        lines = f.read().split("\n")

    includes = ["libforest/gbi_extensions.h",
                "PR/gbi.h", "evw_anime.h", "c_keyframe.h"]

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
            elif "_tex_index" in this_obj:
                found_types.append((this_obj, "u8"))
            elif this_obj.endswith("evw_anime"):
                found_types.append((this_obj, "EVW_ANIME_DATA"))
            elif this_obj.endswith("_pal"):
                found_types.append((this_obj, "PAL"))
            elif this_obj.endswith("_tex"):
                found_types.append((this_obj, "TEX"))
            elif this_obj.startswith("cKF_bs_r"):
                found_types.append((this_obj, "cKF_Skeleton_R_c"))
            elif this_obj.startswith("cKF_ba_r"):
                found_types.append((this_obj, "cKF_Animation_R_c"))

    # we now have a list of all objects, and we have a partial mapping of what type they could have
    # what we want to do is go through all the objects we know, and get the out-data
    # there are some objs that will add to this list, we can queue them onto the list

    converted_types = {}
    lookup_table = {
        "EVW_ANIME_DATA": parse_evw_anime_data,
        "EVW_ANIME_TYPE_SCROLL1": parse_evw_anime_scroll,
        "EVW_ANIME_TYPE_SCROLL2": parse_evw_anime_scroll,
        "EVW_ANIME_TYPE_COLREG_MANUAL": parse_evw_anime_colreg,
        "EVW_ANIME_TYPE_COLREG_LINEAR": parse_evw_anime_colreg,
        "EVW_ANIME_TYPE_COLREG_NONLINEAR": parse_evw_anime_colreg,
        "EVW_ANIME_TYPE_TEXANIME": parse_evw_texanime,
        "EVW_ANIME_COL_PRIM": parse_evw_anime_col_prim,
        "EVW_ANIME_COL_ENV": parse_evw_anime_col_env,
        "cKF_Skeleton_R_c": parse_cKF_Skeleton_R_c,
        "cKF_Joint_R_c": parse_cKF_Joint_R_c,
        "cKF_Animation_R_c": parse_cKF_Animation_R_c,
        "u8": parse_u8,
        "u16": parse_u16,
        "s16": parse_s16,
    }
    # we now have a list of objects+type
    while len(found_types) > 0:
        obj_name, type = found_types.pop()
        if obj_name in converted_types:
            continue
        if type == "Vtx":
            data = f'#include "assets/{obj_name}.inc"'
            converted_types[obj_name] = (type, data, NO_ALIGN)
        elif type == "Gfx":
            data = convert_binary_to_gfx(
                *lookup_bins_and_symbols(lines, obj_name))
            converted_types[obj_name] = (type, data, NO_ALIGN)
        elif type == "PAL":
            data = f'#include "assets/{obj_name}.inc"'
            converted_types[obj_name] = ("u16", data, ASSET_ALIGN)
        elif type == "TEX":
            data = f'#include "assets/{obj_name}.inc"'
            converted_types[obj_name] = ("u8", data, ASSET_ALIGN)

        elif type in lookup_table:
            res: struct_parse_result = lookup_table[type](
                *lookup_bins_and_symbols2(lines, obj_name))
            data = res.formatted_str
            converted_types[obj_name] = (type, data, NO_ALIGN)
            if len(res.referenced_objects) > 0:
                found_types = [(ref.symbol_name, ref.symbol_type)
                               for ref in res.referenced_objects] + found_types

    out = header + "\n\n"
    for obj in all_objs:
        this_type, out_data, align = converted_types.get(
            obj, ("u8", f'#include "assets/{obj}.inc"', NO_ALIGN))
        static_typing = lookup_static(lines, obj)
        out += f"{static_typing}{this_type} {obj}[] {align}= {{ \n{out_data}\n}};\n\n"
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
