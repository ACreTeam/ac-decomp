import os
import re
import argparse
import typing
from ruamel.yaml import YAML
from ruamel.yaml import CommentedMap
from ruamel.yaml import CommentedSeq
from ruamel.yaml import scalarint
import yaml
import ntpath

#region Types
class SymbolInfo:
    symbol_name: str = None
    asset_path: str = None
    start_address: int = 0
    end_address: int = 0

    def __init__(self, name:str, asset_path:str, start:int, size:int) -> None:
        self.symbol_name = name
        self.asset_path = asset_path
        self.start_address = start
        self.end_address = start + size

    def get_address_range(self)->typing.Tuple[int, int]:
        return self.start_address, self.end_address
    
class Address_Sort_Entry:
    key : str = None
    value: CommentedMap = None
    starting_address: int = None

    def __init__(self, entry_key: str, entry_value: CommentedMap, entry_starting_address: int) -> None:
        self.key = entry_key
        self.value = entry_value
        self.starting_address = entry_starting_address
#endregion

# Pattern to match '#include "assets/[...].inc"'
pattern_format = r'\s*#include "assets/([^"]*/)([^"]+)\.inc"\s*'
asset_include_pattern = re.compile(pattern_format)

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

def load_symbols_yaml():
    # Load the YAML file using CSafeLoader for best perf
    with open("config/symbols.yml", "r", encoding="utf-8", newline="\n") as file_reader:
            data = yaml.load(file_reader, Loader=yaml.CSafeLoader)

    # Flatten the data by combining all sections
    all_symbols = {}
    for section in data.values():
        all_symbols.update(section)

    # Convert addresses to a sorted list of tuples (address, symbol_name)
    return sorted((addr, name) for addr, name in all_symbols.items())

def search_for_symbol(symbol_name, sorted_symbols):
    # Search for the symbol
    for i, (addr, name) in enumerate(sorted_symbols):
        if name == symbol_name:
            current_address = addr
            next_address = sorted_symbols[i + 1][0] if i + 1 < len(sorted_symbols) else None
            return current_address, next_address if next_address else None

    # If the symbol is not found
    return None, None

sorted_symbols = None
def search_for_assetrip_includes(src_file: str)->typing.List[SymbolInfo]:
    global sorted_symbols # make sorted_symbols accessible for writing
    symbols_for_tu: typing.List[SymbolInfo] = []

    with open(src_file, "r", encoding="utf-8", newline="\n") as file_reader:
        while True:
            line = file_reader.readline()
            if not line:
                break

            # Check if the line matches an assetrip include
            match = asset_include_pattern.match(line)
            if not match:
                continue

            # It is a match
            path = match.group(1)
            name = match.group(2)
            # print(path, name)

            # Load symbols if not already done
            if sorted_symbols == None:
                sorted_symbols = load_symbols_yaml()

            sym_beg, sym_end = search_for_symbol(name, sorted_symbols)
            size = sym_end - sym_beg
            symbols_for_tu.append(SymbolInfo(name, path, sym_beg, size))
            # print(hex(sym_beg), hex(sym_end), hex(size))
    return symbols_for_tu


#region Asset Slices Config File
def update_asset_slice_config(data: CommentedMap, tu_name: str, symbols_for_tu: typing.List[SymbolInfo]):
    binary_commented_map : CommentedMap = None
    binary_commented_map_key: str = "config/rel.yml" # TODO: do we want to support assets in the dol?
    binary_commented_map = data[binary_commented_map_key]

    insert_tu_name_comment = True
    for asset_symbol in symbols_for_tu:            
        asset_type: str = None
        if asset_symbol.symbol_name.endswith('_pal'):
            asset_type = "pal16"
        elif asset_symbol.symbol_name.endswith(('_vtx', '_v')):
            asset_type = "vtx"
        elif not asset_symbol.symbol_name.endswith(('_txt', '_tex')):
            print(f"What is the asset type? {asset_symbol.symbol_name} (optional)")
            asset_type = input()

        if not asset_type:
            asset_type = None

        asset_commented_map : CommentedMap = None
        asset_key = None
        if asset_symbol.asset_path != None:
            asset_key = f"{asset_symbol.asset_path}{asset_symbol.symbol_name}"
        else:
            asset_key = asset_symbol.symbol_name

        if binary_commented_map.__contains__(asset_key):
            asset_commented_map = binary_commented_map[asset_key]
            insert_tu_name_comment = False
        else:
            asset_commented_map = CommentedMap()
            binary_commented_map.insert(len(binary_commented_map), asset_key, asset_commented_map)

            if insert_tu_name_comment:
                insert_tu_name_comment = False
                binary_commented_map.yaml_set_comment_before_after_key(key=asset_key, indent=2, before=tu_name)

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

def process_file_or_directory(data: CommentedMap, src_file: str):
    if os.path.isdir(src_file):
        # List all files and directories in the current directory
        for entry in os.listdir(src_file):
            full_path = os.path.join(src_file, entry)
            # Recursively call the function for each entry
            process_file_or_directory(data, full_path)
    else:
        # Process the file
        src_filename: str = ntpath.basename(src_file)
        include_symbols: typing.List[SymbolInfo] = search_for_assetrip_includes(src_file)
        update_asset_slice_config(data, src_filename, include_symbols)
#endregion

#region Main
def main():
    parser = argparse.ArgumentParser(prog="Asset Include/Rip Generation", description="Adds the corresponding assetrip addresses assets YAML config file")
    parser.add_argument("src_file", nargs="?", help="Name of the translation unit to search for assets")
    args = parser.parse_args()

    src_file: str = args.src_file
    yaml = YAML(typ="rt")
    data: CommentedMap = None
    with open("config/assets.yml", "r", encoding="utf-8", newline="\n") as file_reader:
        data = yaml.load(file_reader)

    process_file_or_directory(data, src_file)

    # Sort by starting address and replace
    binary_commented_map_key: str = "config/rel.yml" # TODO: do we want to support assets in the dol?
    binary_commented_map = data[binary_commented_map_key]
    data[binary_commented_map_key] = sort_by_starting_address(binary_commented_map, ["addrs"])

    # Write out to file
    with open("config/assets.yml", "w", encoding="utf-8", newline="\n") as file_writer:
        yaml.dump(data, file_writer)

if __name__ == "__main__":
    main()
#endregion
