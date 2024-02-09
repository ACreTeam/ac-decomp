import os
import re
import argparse
from re import Match
from io import TextIOWrapper
import typing
from ruamel.yaml import YAML
from ruamel.yaml import CommentedMap
from ruamel.yaml import CommentedSeq
from ruamel.yaml import scalarint

#region Types
class SymbolInfo:
    symbol_name: str = None
    start_address: int = 0
    end_address: int = 0

    def __init__(self, name:str, start:int, size:int) -> None:
        self.symbol_name = name
        self.start_address = start
        self.end_address = start + size

    def get_address_range(self)->typing.Tuple[int, int]:
        return self.start_address, self.end_address

class SliceSection:
    section_symbol: SymbolInfo = None
    symbols: typing.List[SymbolInfo] = None

    def __init__(self, symbol: SymbolInfo) -> None:
        self.section_symbol = symbol
        self.symbols = []

class SliceInfo:
    sections: typing.List[SliceSection] = None

    def __init__(self) -> None:
        self.sections = []

    def get_address_range(self)->typing.Tuple[int, int]:
        start_address = self.sections[0].section_symbol.start_address
        end_address = self.sections[-1].section_symbol.end_address
        if len(self.sections[-1].symbols) > 0:
            end_address = self.sections[-1].symbols[-1].end_address

        return start_address, end_address
    
class Address_Sort_Entry:
    key : str = None
    value: CommentedMap = None
    starting_address: int = None

    def __init__(self, entry_key: str, entry_value: CommentedMap, entry_starting_address: int) -> None:
        self.key = entry_key
        self.value = entry_value
        self.starting_address = entry_starting_address
#endregion

#region Constants
# Dictionary for the offsets we need to apply to the addresses from the map
address_offset_map : typing.Dict[str, int] = {
    ".text": int("0x803702A8", 16),
    ".rodata": int("0x80641260", 16),
    ".data": int("0x8064D500", 16),
    ".bss": int("0x8125A7C0", 16)
}

prioritized_addresses: typing.List[str] = [".text", ".rodata", ".data", ".bss"]

script_dir: str = os.path.dirname(os.path.realpath(__file__))
root_dir: str = os.path.abspath(os.path.join(script_dir, ".."))
default_map_path: str = os.path.join(root_dir, "dump/foresta.map")
default_binary_slice_file_path: str = os.path.join(root_dir, "config/rel_slices.yml")
default_asset_slice_file_path: str = os.path.join(root_dir, "config/assets.yml")

specific_tu_pattern_format = r"\s*([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+(?:([0-9a-fA-F]+)\s+(.+?)|\.\.\.data\.\d \(entry of \.data\))\s+({tu_name})\s*"
general_symbol_pattern = re.compile(specific_tu_pattern_format.format(tu_name = ".+\.o"))

slice_boundary_format = "[{start_address}, {end_address}]"
#endregion

#region Sorting
def sort_by_starting_address(data: CommentedMap, address_sort_keys: typing.List[str])->CommentedMap:
    if len(data) <= 1:
        return data
    
    ordered_entries : list[Address_Sort_Entry] = []
    for key in data.keys():
        entry = data[key]
        starting_address = 0

        for address_key in address_sort_keys:
            if address_key not in entry:
                continue
            
            # Ensure starting_address is an integer
            if isinstance(entry[address_key], int):
                starting_address = entry[address_key]
            elif isinstance(entry[address_key], CommentedSeq):
                starting_address = entry[address_key][0]
            else:
                print('Address key %s is not an int or CommentedSeq! type: %s value: %s' % (address_key, type(entry[address_key]), entry[address_key]))
                starting_address = 0
            break

        ordered_entries.append(Address_Sort_Entry(key, entry, starting_address))
    
    ordered_entries.sort(key=lambda entry: entry.starting_address)

    ordered_map = CommentedMap()
    for ordered_entry in ordered_entries:
        ordered_map[ordered_entry.key] = ordered_entry.value
        if ordered_entry.key not in data.ca.items:
            continue
        
        ordered_map.ca.items[ordered_entry.key] = data.ca.items[ordered_entry.key]

    return ordered_map
#endregion

#region Symbol Gathering
def get_symbol_from_map_match(symbol_match: Match, address_offset: int)->SymbolInfo:
    name = symbol_match.group(5)
    start_address = int(symbol_match.group(1), 16) + address_offset
    size = int(symbol_match.group(2), 16)
    return SymbolInfo(name, start_address, size)

def gather_symbols_for_section(address_offset: int, file_reader:TextIOWrapper, slice_info: SliceInfo, starting_match: Match):
    section_tu_name = starting_match.group(6)
    section_symbol = get_symbol_from_map_match(starting_match, address_offset)
    section = SliceSection(section_symbol)
    slice_info.sections.append(section)

    # Keep reading until the end of the section has been reached
    line: str = None
    while True:
        line = file_reader.readline()
        if not line:
            return
        if "entry of .data" in line:
            continue
        break
    
    next_match: Match = general_symbol_pattern.match(line)
    while True:
        # Check if the next match belongs to this group or not
        curr_match = next_match
        if not curr_match:
            break

        curr_match_tu_name = curr_match.group(6)
        if curr_match_tu_name != section_tu_name:
            break

        curr_match_symbol_name = curr_match.group(5)
        if curr_match_symbol_name in address_offset_map:
            gather_symbols_for_section(address_offset, file_reader, slice_info, starting_match)
            break

        # Make symbol for current match
        symbol = get_symbol_from_map_match(curr_match, address_offset)

        # Check the next match to get a more accurate ending address
        next_line = file_reader.readline()
        if not next_line:
            # Eof reached. Just add as is
            section.symbols.append(symbol)
        
        # Match against the next line
        next_match = general_symbol_pattern.match(next_line)
        if not next_match:
            # Non matching line
            section.symbols.append(symbol)
        
        # Use start address as the end boundary for the slice
        next_match_start_address = int(next_match.group(1), 16) + address_offset
        symbol.end_address = next_match_start_address
        section.symbols.append(symbol)

def gather_tu_symbols(tu_name: str, map_path: str)->typing.Dict[str, SliceInfo]:
    gathered_symbols: dict[str, SliceInfo] = {}
    tu_regex = re.compile(specific_tu_pattern_format.format(tu_name = tu_name))

    with open(map_path, "r", encoding="utf-8", newline="\n") as file_reader:
        while True:
            line = file_reader.readline()
            if not line:
                break

            # Check if the line matches the TU name
            match = tu_regex.match(line)
            if not match:
                continue

            # It is a match
            slice_name = match.group(5)
            if slice_name not in address_offset_map:
                continue

            # Add to dictionary
            offset = address_offset_map[slice_name]
            slice_info = SliceInfo()
            gathered_symbols[slice_name] = slice_info

            gather_symbols_for_section(offset, file_reader, slice_info, match)

    return gathered_symbols
#endregion

#region Asset Slices Config File
def update_asset_slice_config(tu_name: str, binary_slice_file_path: str, asset_slice_file_path: str, symbols_for_tu: typing.Dict[str, SliceInfo]):
    if ".data" not in symbols_for_tu:
        return
    
    print("Add data entries to: " + asset_slice_file_path + "? (y/n)")
    reply = input().lower()
    if reply != "y" and reply != "yes":
        return

    yaml = YAML(typ="rt")
    data: CommentedMap = None
    with open(asset_slice_file_path, "r", encoding="utf-8", newline="\n") as file_reader:
        data = yaml.load(file_reader)

        binary_commented_map : CommentedMap = None
        binary_commented_map_key: str = None
        if "rel" in binary_slice_file_path:
            binary_commented_map_key = "config/rel.yml"
        else:
            binary_commented_map_key = "config/dol.yml"

        binary_commented_map = data[binary_commented_map_key]

        for section in symbols_for_tu[".data"].sections:
            for asset_symbol in section.symbols:
                print("Add entry for: " + asset_symbol.symbol_name + "? (y/n)")
                reply = input().lower()
                if reply != "y" and reply != "yes":
                    continue
                
                print("What is the asset type? (optional)")
                asset_type = input()

                asset_commented_map : CommentedMap = None
                if binary_commented_map.__contains__(asset_symbol.symbol_name):
                    asset_commented_map = binary_commented_map[asset_symbol.symbol_name]
                else:
                    asset_commented_map = CommentedMap()
                    binary_commented_map.insert(len(binary_commented_map), asset_symbol.symbol_name, asset_commented_map)
                    binary_commented_map.ca.insert(asset_symbol.symbol_name, asset_symbol.symbol_name)

                # Add in the address range
                address_commented_seq: CommentedSeq = None
                if asset_commented_map.__contains__("addrs"):
                    # Re-use the same commented section
                    address_commented_seq = asset_commented_map["addrs"]
                    address_commented_seq.clear()
                else:
                    address_commented_seq: CommentedSeq = CommentedSeq()
                    
                    # Assign to the slice section
                    asset_commented_map["addrs"] = address_commented_seq

                # Add in the start and end address
                start_address, end_address = asset_symbol.get_address_range()
                address_commented_seq.fa.set_flow_style()
                address_commented_seq.append(scalarint.HexCapsInt(start_address))
                address_commented_seq.append(scalarint.HexCapsInt(end_address))

                # Add in the asset type
                if not asset_type or asset_type is None:
                    # Type not specified
                    if asset_commented_map.__contains__("type"):
                        # Using a previous entry where the type was used, so delete it
                        asset_commented_map.__delitem__("type")
                    continue

                asset_commented_map["type"] = asset_type
        
            # Sort by starting address and replace
            data[binary_commented_map_key] = sort_by_starting_address(binary_commented_map, ["addrs"])
        
    # Write out to file
    with open(asset_slice_file_path, "w", encoding="utf-8", newline="\n") as file_writer:
        yaml.dump(data, file_writer)
#endregion

#region Slice Config File
def update_binary_slice_config(tu_name: str, slice_file_path: str, symbols_for_tu: typing.Dict[str, SliceInfo]):
    yaml = YAML(typ="rt")
    yaml.indent(mapping=4, sequence=4, offset=4)
    data: CommentedMap = None
    with open(slice_file_path, "r", encoding="utf-8", newline="\n") as file_reader:
        data = yaml.load(file_reader)

        tu_c_file_name = tu_name.replace(".o", ".c")
        slice_commented_map : CommentedMap = None
        if data.__contains__(tu_c_file_name):
            print("TU already exists in file. Overwrite values? (y/n)")
            reply = input().lower()
            if reply != "y" and reply != "yes":
                return
            
            # Re-use the existing commented map
            slice_commented_map = data[tu_c_file_name]
        else:
            # Create a new commented map
            slice_commented_map : CommentedMap = CommentedMap()
            
            # Add to the end of the file
            data.insert(len(data), tu_c_file_name, slice_commented_map)
        
        for slice_name, slice_info in symbols_for_tu.items():
            if len(slice_info.sections) == 0:
                # No symbols for this TU
                continue

            address_commented_seq: CommentedSeq = None
            if slice_commented_map.__contains__(slice_name):
                # Re-use the same commented section
                address_commented_seq = slice_commented_map[slice_name]
                address_commented_seq.clear()
            else:
                address_commented_seq: CommentedSeq = CommentedSeq()
                
                # Assign to the slice section
                slice_commented_map[slice_name] = address_commented_seq

            # Add in the start and end address
            start_address, end_address = slice_info.get_address_range()
            address_commented_seq.fa.set_flow_style()
            address_commented_seq.append(scalarint.HexCapsInt(start_address))
            address_commented_seq.append(scalarint.HexCapsInt(end_address))

    # Sort by address
    data = sort_by_starting_address(data, prioritized_addresses)

    # Write out to file
    with open(slice_file_path, "w", encoding="utf-8", newline="\n") as file_writer:
        yaml.dump(data, file_writer)
#endregion

#region Main
def main():
    parser = argparse.ArgumentParser(prog="Translation Unit Config Updater", description="Adds the corresponding addresses to slice config files")
    parser.add_argument("tu_name", nargs="?", help="Name of the translation unit to get addresses for")
    parser.add_argument("-map", "--symbol-map", dest="symbol_map", help="Path to the symbol map file used for reference", action="store")
    parser.add_argument("-binary", "--binary-slices-file", dest="binary_slices_file", help="Path to the binary slices file to write to", action="store")
    parser.add_argument("-asset", "--asset-slices-file", dest="asset_slices_file", help="Path to the asset slices file to write to", action="store")
    args = parser.parse_args()

    # Make sure the translation unit name ends with .o
    tu_name = args.tu_name
    if tu_name[-2:] != ".o":
        tu_name = tu_name + ".o"
    
    symbol_map_path = args.symbol_map
    if not symbol_map_path:
        symbol_map_path = default_map_path

    binary_slices_file = args.binary_slices_file
    if not binary_slices_file:
        binary_slices_file = default_binary_slice_file_path
    
    asset_slices_file = args.asset_slices_file
    if not asset_slices_file:
        asset_slices_file = default_asset_slice_file_path

    # Get the symbols for the TU
    symbols_for_tu = gather_tu_symbols(tu_name, symbol_map_path)

    # Make a call to update the binary file
    update_binary_slice_config(tu_name, binary_slices_file, symbols_for_tu)
    update_asset_slice_config(tu_name, binary_slices_file, asset_slices_file, symbols_for_tu)

if __name__ == "__main__":
    main()
#endregion