import argparse
import struct
import os
import re

CHAR_MAP = [
    "¡",
    "¿",
    "Ä",
    "À",
    "Á",
    "Â",
    "Ã",
    "Å",
    "Ç",
    "È",
    "É",
    "Ê",
    "Ë",
    "Ì",
    "Í",
    "Î",
    "Ï",
    "Ð",
    "Ñ",
    "Ò",
    "Ó",
    "Ô",
    "Õ",
    "Ö",
    "Ø",
    "Ù",
    "Ú",
    "Û",
    "Ü",
    "ß",
    "Þ",
    "à",
    " ",
    "!",
    '"',
    "á",
    "â",
    "%",
    "&",
    "'",
    "(",
    ")",
    "~",
    "♥",
    ",",
    "-",
    ".",
    "♪",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    ":",
    "🌢",
    "<",
    "=",
    ">",
    "?",
    "@",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "ã",
    "💢",
    "ä",
    "å",
    "_",
    "ç",
    "a",
    "b",
    "c",
    "d",
    "e",
    "f",
    "g",
    "h",
    "i",
    "j",
    "k",
    "l",
    "m",
    "n",
    "o",
    "p",
    "q",
    "r",
    "s",
    "t",
    "u",
    "v",
    "w",
    "x",
    "y",
    "z",
    "è",
    "é",
    "ê",
    "ë",
    "\u007f",
    "�",
    "ì",
    "í",
    "î",
    "ï",
    "•",
    "ð",
    "ñ",
    "ò",
    "ó",
    "ô",
    "õ",
    "ö",
    "⁰",
    "ù",
    "ú",
    "ー",
    "û",
    "ü",
    "ý",
    "ÿ",
    "þ",
    "Ý",
    "¦",
    "§",
    "ḏ",
    "ṉ",
    "‖",
    "µ",
    "³",
    "²",
    "¹",  # note that a̱ and o̱ had to be changed because they're actually two characters in unicode. a̱ -> ḏ | o̱ -> ṉ
    "¯",
    "¬",
    "Æ",
    "æ",
    "„",
    "»",
    "«",
    "☀",
    "☁",
    "☂",
    "🌬",
    "☃",
    "∋",
    "∈",
    "/",
    "∞",
    "○",
    "🗙",
    "□",
    "△",
    "+",
    "⚡",
    "♂",
    "♀",
    "🍀",
    "★",
    "💀",
    "😮",
    "😄",
    "😣",
    "😠",
    "😃",
    "×",
    "➗",
    "🔨",
    "🎀",
    "✉",
    "💰",
    "🐾",
    "🐶",
    "🐱",
    "🐰",
    "🐦",
    "🐮",
    "🐷",
    "\n",
    "🐟",
    "🐞",
    ";",
    "#",
    "\u00d2",
    "\u00d3",
    "⚷",
    "\u00d5",
    "\u00d6",
    "\u00d7",
    "\u00d8",
    "\u00d9",
    "\u00da",
    "\u00db",
    "\u00dc",
    "Ỳ",
    "ꟓ",
    "\u00df",
    "\u00e0",
    "\u00e1",
    "\u00e2",
    "\u00e3",
    "\u00e4",
    "\u00e5",
    "\u00e6",
    "\u00e7",
    "\u00e8",
    "\u00e9",
    "\u00ea",
    "\u00eb",
    "\u00ec",
    "\u00ed",
    "\u00ee",
    "\u00ef",
    "\u00f0",
    "\u00f1",
    "\u00f2",
    "\u00f3",
    "\u00f4",
    "\u00f5",
    "\u00f6",
    "÷",
    "\u00f8",
    "\u00f9",
    "\u00fa",
    "\u00fb",
    "\u00fc",
    "\u00fd",
    "\u00fe",
    "\u00ff",
]

CONT_SIZES = [
    2,
    2,
    2,
    3,
    2,
    5,
    2,
    2,
    5,
    5,
    5,
    5,
    5,
    2,
    4,
    4,
    4,
    4,
    4,
    6,
    8,
    10,
    6,
    8,
    10,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    6,
    3,
    3,
    3,
    3,
    2,
    4,
    4,
    3,
    3,
    3,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    6,
    3,
    3,
    4,
    3,
    2,
    2,
    6,
    2,
    2,
    3,
    3,
    3,
    3,
    2,
    2,
    2,
    2,
    2,
    2,
    4,
    4,
    12,
    14,
]

COMMANDS = [
    "MSGEND",
    "MSGCONTINUE",
    "MSGCLEAR",
    "PAUSE",
    "BTN",
    "TEXTCOLOR",
    "ABLECANCEL",
    "UNABLECANCEL",
    "DEMOPLR",
    "DEMONPC0",
    "DEMONPC1",
    "DEMONPC2",
    "DEMONPCQST",
    "OPENCHOICE",
    "SETFORCEMSG",
    "SETNEXTMSG0",
    "SETNEXTMSG1",
    "SETNEXTMSG2",
    "SETNEXTMSG3",
    "SETNEXTMSGRND2",
    "SETNEXTMSGRND3",
    "SETNEXTMSGRND4",
    "SETSELSTR2",
    "SETSELSTR3",
    "SETSELSTR4",
    "FORCENEXT",
    "STR_PLAYERNAME",
    "STR_TALKNAME",
    "STR_TAIL",
    "STR_YEAR",
    "STR_MONTH",
    "STR_WEEK",
    "STR_DAY",
    "STR_HOUR",
    "STR_MIN",
    "STR_SEC",
    "STR_FREE0",
    "STR_FREE1",
    "STR_FREE2",
    "STR_FREE3",
    "STR_FREE4",
    "STR_FREE5",
    "STR_FREE6",
    "STR_FREE7",
    "STR_FREE8",
    "STR_FREE9",
    "STR_DETERMINATION",
    "STR_COUNTRYNAME",
    "STR_RNDNUM",
    "STR_ITEM0",
    "STR_ITEM1",
    "STR_ITEM2",
    "STR_ITEM3",
    "STR_ITEM4",
    "STR_FREE10",
    "STR_FREE11",
    "STR_FREE12",
    "STR_FREE13",
    "STR_FREE14",
    "STR_FREE15",
    "STR_FREE16",
    "STR_FREE17",
    "STR_FREE18",
    "STR_FREE19",
    "STR_MAIL",
    "LUCK_NEUTRAL",
    "LUCK_RELATIONSHIP",
    "LUCK_UNPOPULAR",
    "LUCK_BAD",
    "LUCK_MONEY",
    "LUCK_GOODS",
    "LUCK_6",
    "LUCK_7",
    "LUCK_8",
    "LUCK_9",
    "MSGCONTENTS_NORMAL",
    "MSGCONTENTS_ANGRY",
    "MSGCONTENTS_SAD",
    "MSGCONTENTS_FUN",
    "MSGCONTENTS_SLEEPY",
    "COLORCHARS",
    "SNDCUT",
    "LINEOFS",
    "LINETYPE",
    "CHARSCALE",
    "BTN2",
    "BGMMAKE",
    "BGMDELETE",
    "MSGTIMEEND",
    "SNDTRGSYS",
    "LINESCALE",
    "SNDNOPAGE",
    "VOICETRUE",
    "VOICEFALSE",
    "SELNOB",
    "GIVEOPEN",
    "GIVECLOSE",
    "MSGCONTENTS_GLOOMY",
    "SELNOBCLOSE",
    "SETNEXTMSGRNDSECTION",
    "AGBDUMMY0",
    "AGBDUMMY1",
    "AGBDUMMY2",
    "SPACE",
    "AGBDUMMY3",
    "AGBDUMMY4",
    "MALEFEMALECHK",
    "AGBDUMMY5",
    "AGBDUMMY6",
    "AGBDUMMY7",
    "AGBDUMMY8",
    "AGBDUMMY9",
    "AGBDUMMY10",
    "STR_ISLANDNAME",
    "SETCURSORJUST",
    "CLRCUSRORJUST",
    "CUTARTICLE",
    "CAPTIALIZE",
    "STR_AMPM",
    "SETNEXTMSG4",
    "SETNEXTMSG5",
    "SETSELSTR5",
    "SETSELSTR6",
]


def decode_control_code(ba: bytearray, idx: int):
    if ba[idx] != 0x7F:
        raise ValueError("First character must be 0x7F")
    cont_type = ba[idx + 1]
    if cont_type >= len(CONT_SIZES):
        raise ValueError(f"Invalid control code id {cont_type:02X}")
    cont_size = CONT_SIZES[cont_type]
    if len(ba) < idx + cont_size:
        raise ValueError(
            f"Bytearray is not large enough for control code {cont_type:02X}"
        )

    cmd = COMMANDS[cont_type]
    if cmd is not None:
        if cont_size > 2:
            hex_values = " ".join(
                "{:02X}".format(b)
                for b in ba[(idx + 2) : (idx + CONT_SIZES[cont_type])]
            )
            return f"<<{cmd} [{hex_values}]>>", cont_size
        else:
            return f"<<{cmd}>>", cont_size
    else:
        hex_values = " ".join(
            "{:02X}".format(b) for b in ba[(idx + 2) : (idx + CONT_SIZES[cont_type])]
        )
        return f"<<Control Code [{cont_type:02X}] [{hex_values}]>>", cont_size


def decode_entry(ba: bytearray, start: int, end: int, idx: int):
    parts = [f"[[ENTRY {idx} START]]\n"]  # Use a list to collect string parts
    i = start
    while i < end:
        char = ba[i]
        if char == 0x7F:
            cont_str, cont_size = decode_control_code(ba, i)
            parts.append(cont_str)
            i += cont_size
        else:
            parts.append(CHAR_MAP[ba[i]])
            i += 1
    parts.append("\n\n")
    return "".join(parts)  # Join the parts into a final string at the end


def decode_file(data_path: str, table_path: str, out_path: str):
    idx = 0
    last_end = 0
    output_buffer = []

    with open(data_path, "rb") as df, open(table_path, "rb") as tf, open(
        out_path, "w"
    ) as of:
        while True:
            bytes = tf.read(4)
            if not bytes:
                break
            end = struct.unpack(">I", bytes)[0]
            if end != 0:
                size = end - last_end
                last_end = end
                data = bytearray(df.read(size))
                decoded_str = decode_entry(data, 0, size, idx)
                output_buffer.append(decoded_str)

            idx += 1
            # Write buffer content to file to reduce write calls
            if len(output_buffer) >= 8192:
                of.write("".join(output_buffer))
                output_buffer.clear()

        # Write remaining buffer content to file
        if output_buffer:
            of.write("".join(output_buffer))


# Function to convert a hex string to a list of integers
def convert_hex_string_to_ints(hex_str):
    # Remove spaces and convert to upper case
    clean_str = hex_str.replace(" ", "").upper()
    # Convert every two characters to an integer
    return [int(clean_str[i : i + 2], 16) for i in range(0, len(clean_str), 2)]


# pre-compiled regex patterns
cmd_pattern = re.compile(r"^([\w\s]+)")
arg_pattern = re.compile(r"\[([0-9A-Fa-f\s]*)\]")


def encode_control_code(cont_code_str: str, start_idx: int = 0, end_idx: int = None):
    sliced_str = cont_code_str[start_idx:end_idx]  # bad but necessary in python
    cmd_match = cmd_pattern.match(sliced_str)
    if not cmd_match:
        raise ValueError("Missing command in control code!")

    cmd = cmd_match.group(1).strip()
    args = arg_pattern.findall(sliced_str)

    cmd_idx = COMMANDS.index(cmd)
    arg_list = [
        byte for hex_str in args for byte in convert_hex_string_to_ints(hex_str)
    ]
    return cmd_idx, arg_list


def encode_entry(entry: str):
    ba = bytearray()
    i = 0
    max = len(entry)
    while i < max:
        char = entry[i]
        if char == "<" and i < max - 1 and entry[i + 1] == "<":
            start = i + 2
            end = start
            found = False
            while end < max:
                if entry[end] == ">" and end < max - 1 and entry[end + 1] == ">":
                    found = True
                    break
                end += 1
            if found:
                cmd_idx, arg_list = encode_control_code(entry, start, end)
                cmd_size = CONT_SIZES[cmd_idx]
                if len(arg_list) != cmd_size - 2:
                    raise ValueError(
                        f"Expected args of length {cmd_size - 2} for command {COMMANDS[cmd_idx]}, but got {len(arg_list)}"
                    )
                ba.append(0x7F)
                ba.append(cmd_idx)
                ba.extend(arg_list)
                i = end + 2
                continue

        ba.append(CHAR_MAP.index(char))
        i += 1
    return ba


def encode_file(
    file_path: str,
    data_path: str,
    table_path: str,
    data_size: int = -1,
    table_size: int = -1,
):
    entries = {}
    current_entry = None
    recording = False

    with open(file_path, "r") as tf, open(data_path, "wb") as df, open(
        table_path, "wb"
    ) as tabf:
        for line in tf:
            stripped_line = line.strip()

            # Check for entry start
            if stripped_line.startswith("[[ENTRY") and stripped_line.endswith("START]]"):
                entry_index = stripped_line.split()[1]  # Assuming the format [[ENTRY X START]]
                current_entry = entry_index
                entries[current_entry] = []
                recording = True
                continue

            # Check for entry end
            if (
                line.find("<<MSGEND>>") != -1
                or line.find("<<MSGTIMEEND")
                or line.find("<<MSGCONTINUE>>")
            ):
                entries[current_entry].append(line)
                recording = False
                continue

            # Record lines if within an entry and not empty
            if recording and line:
                entries[current_entry].append(line)

        # end_ofs = 0
        for entry in entries:
            entries[entry] = encode_entry("".join(entries[entry]).rstrip())
            df.write(entries[entry])
            tabf.write(struct.pack(">I", df.tell()))

        if data_size > 0:
            data_remain = data_size - df.tell()
            if data_remain > 0:
                df.write(b"\x00" * data_remain)

        if table_size > 0:
            table_remain = table_size - tabf.tell()
            if table_remain > 0:
                tabf.write(b"\x00" * table_remain)

    return entries


def main():
    parser = argparse.ArgumentParser(
        description="Pack or dump Animal Crossing text files."
    )
    parser.add_argument("-m", help="The mode to run. Valid arguments are un[pack].")
    parser.add_argument("path", help="The path of the source file.")
    parser.add_argument("out", help="The path of the destination file.")
    parser.add_argument(
        "--data_size",
        help="Optional hexadecimal padded size for the data file.",
        required=False,
    )
    parser.add_argument(
        "--table_size",
        help="Optional hexadecimal padded size for the table file.",
        required=False,
    )

    args = parser.parse_args()
    if args.m.lower() == "pack":
        # Create *_table.bin path
        dir_name, file_name = os.path.split(args.out)
        name, ext = os.path.splitext(file_name)
        new_file_name = f"{name}_table{ext}"

        # encode
        encode_file(
            args.path,
            args.out,
            os.path.join(dir_name, new_file_name),
            int(args.data_size, 16) if args.data_size is not None else -1,
            int(args.table_size, 16) if args.table_size is not None else -1,
        )
    elif args.m.lower() == "unpack":
        # Search for *_table.bin
        dir_name, file_name = os.path.split(args.path)
        name, ext = os.path.splitext(file_name)
        new_file_name = f"{name}_table{ext}"
        table_path = os.path.join(dir_name, new_file_name)

        if not os.path.exists(table_path):
            raise Exception(
                f"Couldn't find a valid table path. Please ensure {new_file_name} exists!"
            )

        # decode
        decode_file(args.path, table_path, args.out)
    else:
        raise Exception("Invalid mode! Please use -m un[pack]")


if __name__ == "__main__":
    main()
