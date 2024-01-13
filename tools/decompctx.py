# This script makes leaves most of the heavy lifting to pcpp which does preprocessing and expansion of files:
# https://github.com/ned14/pcpp
# To use it make sure you run 'pip install pcpp'
import os
import re
import argparse
from io import StringIO
from pcpp import CmdPreprocessor
from contextlib import redirect_stdout

#region Regex Patterns
at_address_pattern = re.compile(r"(?:.*?)(?:[a-zA-Z_$][\w$]*\s*\*?\s[a-zA-Z_$][\w$]*)\s*((?:AT_ADDRESS|:)(?:\s*\(?\s*)(0x[0-9a-fA-F]+|[a-zA-Z_$][\w$]*)\)?);")
attribute_pattern = re.compile(r"(__attribute__)")
binary_literal_pattern = re.compile(r"\b(0b[01]+)\b")
#endregion

#region Defaults
default_defines: dict[str, str] = {"__MWERKS__" : "1", "_LANGUAGE_C": "1", "F3DEX_GBI_2": "1"}

src_dir = "src"
include_dir = "include"
cwd_dir = os.getcwd()
script_dir = os.path.dirname(os.path.realpath(__file__))
root_dir = os.path.abspath(os.path.join(script_dir, ".."))
default_include_directories: list[str] = [
    os.path.join(root_dir, src_dir),
    os.path.join(root_dir, include_dir),
    os.path.join(script_dir, src_dir),
    os.path.join(script_dir, include_dir),
    os.path.join(cwd_dir, src_dir),
    os.path.join(cwd_dir, include_dir),
]

default_output_filename = "ctx.h"
#endregion

#region Attribute Stripping
def strip_attributes(text_to_strip: str)->str:
    if not text_to_strip:
        return text_to_strip
    
    attribute_matches = reversed(list(re.finditer(attribute_pattern, text_to_strip)))
    for attribute_match in attribute_matches:
        # Find the end index of the second double paranthesis
        paren_count = 0

        match_span = attribute_match.span(0)
        end_index = match_span[1]
        attribute_opened = False
        while end_index < len(text_to_strip):
            if text_to_strip[end_index] == "(":
                paren_count += 1

                if paren_count == 2:
                    attribute_opened = True
            
            if text_to_strip[end_index] == ")":
                paren_count -= 1

            if attribute_opened and paren_count == 0:
                end_index += 1
                break

            end_index += 1

        # Create the substring
        start_index = match_span[0]
        prefix = text_to_strip[0:start_index]
        postfix = text_to_strip[end_index:len(text_to_strip)]
        text_to_strip = prefix + postfix

    return text_to_strip
#endregion

#region At Address Stripping
def strip_at_address(text_to_strip: str) -> str:
    if not text_to_strip:
        return text_to_strip
    
    at_address_matches = reversed(list(re.finditer(at_address_pattern, text_to_strip)))
    for attribute_match in at_address_matches:
        # Create the substring
        match_span = attribute_match.span(1)
        start_index = match_span[0]
        end_index = match_span[1]
        prefix = text_to_strip[0:start_index]
        postfix = text_to_strip[end_index:len(text_to_strip)]
        text_to_strip = prefix + postfix
    
    return text_to_strip
#endregion

#region Binary Literal Conversion
def convert_binary_literals(text_to_strip: str) -> str:
    if not text_to_strip:
        return text_to_strip
    
    binary_literal_matches = reversed(list(re.finditer(binary_literal_pattern, text_to_strip)))
    for binary_literal_match in binary_literal_matches:
        # Create the substring
        match_span = binary_literal_match.span(1)
        start_index = match_span[0]
        end_index = match_span[1]

        # Convert from binary literal format to regular int
        binary_converted = int(text_to_strip[start_index:end_index], 2)

        prefix = text_to_strip[0:start_index]
        postfix = text_to_strip[end_index:len(text_to_strip)]
        text_to_strip = prefix + str(binary_converted) + postfix
    
    return text_to_strip
#endregion

#region N64 SDK
def get_n64_sdk(sdk_argument: str)->str:
    if sdk_argument:
        return sdk_argument
    
    # No sdk path provided. Try to use default
    sdk_argument = os.environ['N64_SDK']
    if not sdk_argument:
        return None
    
    # Since we don't want the user to have to type the full path, all they need
    # is to provide the top-level folder for the SDK
    sdk_argument = os.path.join(sdk_argument, "ultra/usr/include")
    return sdk_argument
#endregion

#region Main
def main():
    # Write initial parser
    parser = argparse.ArgumentParser(prog="Decomp Context", description="Wrapper around pcpp that can create a context file which can be used for decompilation", add_help=False)
    parser.add_argument("c_file", nargs="?", help="File from which to create context")
    parser.add_argument("-h", "-help", "--help", dest="help", action="store_true")
    parser.add_argument("-n64", "--n64-sdk", dest="n64_sdk", help="Path to the N64 SDK top level directory", action="store")
    parser.add_argument('-D', dest = 'defines', metavar = 'macro[=val]', nargs = 1, action = 'append', help = 'Predefine name as a macro [with value]')
    parser.add_argument("--strip-attributes", dest="strip_attributes", help="If __attribute__(()) string should be stripped", action="store_true", default=True)
    parser.add_argument("--strip-at-address", dest="strip_at_address", help="If AT_ADDRESS or : formatted string should be stripped", action="store_true", default=True)
    parser.add_argument("--convert-binary-literals", dest="convert_binary_literals", help="If binary literals (0bxxxx) should be converted to decimal", action="store_true", default=True)

    # For the output path, we either want to be explicit or relative, but not both
    output_target_group = parser.add_mutually_exclusive_group()
    output_target_group.add_argument("-o", dest="output_path", help="Explicit path to output the context file to", action="store")
    output_target_group.add_argument("-r", "--relative", dest="relative", help="Generate context relative to the source file", action="store_true")

    # When targeting a specific platform we want to only do one thing or another
    platform_target_group = parser.add_mutually_exclusive_group()
    platform_target_group.add_argument("--m2c", dest="m2c", help="Generates an m2c-friendly file", action="store_true")
    platform_target_group.add_argument("--ghidra", dest="ghidra", help="Generates an Ghidra-friendly file", action="store_true")
    
    # Parse the known arguments
    parsed_args = parser.parse_known_args()
    known_args = parsed_args[0]
    
    preprocessor_arguments = ['pcpp']
    if known_args.help or not known_args.c_file:
        # Since this script acts as a wrapper for the main pcpp script
        # we want to manually display the help and pass it through to the
        # pcpp preprocessor to show its full list of arguments
        parser.print_help()
        preprocessor_arguments.append("--help")
        CmdPreprocessor(preprocessor_arguments)
        return

    # Append in the default include directories
    include_directories: list[str] = []
    include_directories.extend(default_include_directories)
    n64_sdk = get_n64_sdk(known_args.n64_sdk)
    if n64_sdk:
        include_directories.append(n64_sdk)

    for include_directory in include_directories:
        preprocessor_arguments.extend(("-I", include_directory))

    # Check if we have any passed in defines
    include_defines = []
    known_defines: list[str] = []
    if known_args.defines:
        argument_defines = [x[0] for x in known_args.defines]
        for define in argument_defines:
            include_defines.append(define)
            known_defines.append(define.split("=")[0])
    
    # Add in the default defines unless explicitly passed in as arguments
    for default_define, default_define_value in default_defines.items():
        if default_define in known_defines:
            continue
        define_str: str = default_define + "=" + default_define_value
        include_defines.append(define_str)

    # Add the defines to the arguments
    for define in include_defines:
        preprocessor_arguments.extend(("-D", define))

    # If not targeting Ghidra or m2c we can include more in
    if not known_args.ghidra and not known_args.m2c:
        preprocessor_arguments.append("--passthru-defines")

    # Compress to minimize whitespace
    preprocessor_arguments.append("--compress")

    # Add unknown arguments and pass them to pcpp
    pass_through_args = parsed_args[1]
    preprocessor_arguments.extend(pass_through_args)

    # Add the file we want to read
    c_file = known_args.c_file
    preprocessor_arguments.append(known_args.c_file)

    # Check if we need to do further conversions after the file is preprocessed
    should_strip_at_address = known_args.strip_at_address or known_args.ghidra or known_args.m2c
    should_strip_attributes = known_args.strip_attributes or known_args.ghidra or known_args.m2c
    should_convert_binary_literals = known_args.convert_binary_literals or known_args.ghidra

    # Create the temp string writer to pass to the preprocessor since we still want to modify
    # the contents for project-specific conditions
    with StringIO() as file_string_writer:
        with redirect_stdout(file_string_writer):
            # Parse the target file:
            CmdPreprocessor(preprocessor_arguments)
          
            # Check if empty
            string_writer_position = file_string_writer.tell()
            if string_writer_position == 0:
                return
            
            # Write to file
            target_file_name = None
            if known_args.output_path:
                target_file_name = known_args.output_path
            elif known_args.relative:
                target_file_name = f"{c_file}.ctx"
            else:
                target_file_name = os.path.join(os.getcwd(), default_output_filename)

            with open(target_file_name, "w", encoding="utf-8", newline="\n") as f:
                # Do we need to sanitize this further?
                if not should_strip_attributes and not should_strip_at_address and not should_convert_binary_literals:
                    f.write(file_string_writer.getvalue())
                    return
                
                # Sanitize line-by line for easier parsing
                file_string_writer.seek(0)
                while True:
                    line_to_write = file_string_writer.readline()
                    if not line_to_write:
                        break

                    if should_strip_attributes:
                        line_to_write = strip_attributes(line_to_write)

                    if should_strip_at_address:
                        line_to_write = strip_at_address(line_to_write)

                    if should_convert_binary_literals:
                        line_to_write = convert_binary_literals(line_to_write)
                    
                    f.writelines(line_to_write)
#endregion

if __name__ == "__main__":
    main()
