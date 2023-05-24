# TODO: this program is slightly messed up. It can output the wrong end address for symbols. Will fix later. Use with caution until then.

import argparse
from ruamel.yaml import YAML, comments

class HexInt(int):
    def __new__(cls, *args, **kwargs):
        return  super().__new__(cls, *args, **kwargs)

def hexint_presenter(dumper, data):
    return dumper.represent_scalar('tag:yaml.org,2002:int', hex(data))

def find_symbol_and_append(input_string, config_file_path, src_path="config/symbols.yml", dest_path="config/assets.yml"):
    yaml = YAML()
    yaml.representer.add_representer(HexInt, hexint_presenter)

    # Load the symbols file
    with open(src_path, 'r') as symbols_file:
        symbols_data = yaml.load(symbols_file)

    # Search for the input string and store its address along with the next address
    address_pair = []
    found_symbol = False
    for section, data in symbols_data.items():
        for address, name in data.items():
            if found_symbol:
                address_pair.append(HexInt(address))
                break
            if name == input_string:
                found_symbol = True
                address_pair.append(HexInt(address))
        if found_symbol:
            break

  # If the input string was found, append it to the assets file
    if address_pair:
        # Make the pair yaml friendly
        address_pair = comments.CommentedSeq(address_pair)
        address_pair.fa.set_flow_style()

        # Load the assets file
        with open(dest_path, 'r') as assets_file:
            assets_data = yaml.load(assets_file)

        # If the file is empty, initialize a new dict
        if assets_data is None:
            assets_data = {}

        # Create entry or update existing entry under the config file path
        if config_file_path not in assets_data:
            assets_data[config_file_path] = {}
        
        if input_string in assets_data[config_file_path]:
            assets_data[config_file_path][input_string]['addrs'] = address_pair
        else:
            assets_data[config_file_path][input_string] = {'addrs': address_pair}

        # Write back to the assets file
        with open(dest_path, 'w') as assets_file:
            yaml.dump(assets_data, assets_file)

def main():
    parser = argparse.ArgumentParser(description='Search for a symbol in a YAML file and append to another YAML file.')
    parser.add_argument('input_string', help='The symbol name to search for.')
    parser.add_argument('config_file_path', help='The path of the configuration file.')

    args = parser.parse_args()
    find_symbol_and_append(args.input_string, args.config_file_path)

if __name__ == '__main__':
    main()
