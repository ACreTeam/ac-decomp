# This script makes leaves most of the heavy lifting to pcpp which does preprocessing and expansion of files:
# https://github.com/ned14/pcpp
# To use it make sure you run 'pip install pcpp'
#
# This script also optionally uses pyperclip to conveniently copy the context to the clipboard:
# https://github.com/asweigart/pyperclip
# Install via `pip install pyperclip`

import os
import re
import argparse
import pyperclip
from io import StringIO
from pcpp import Preprocessor
from pcpp import CmdPreprocessor
from contextlib import redirect_stdout

#region Context Options
class ContextGenerationOptions:
    should_strip_attributes = False
    should_strip_at_address = False
    should_convert_binary_literals = False
    should_replace_enums_in_initializers = False
    should_strip_initializer_trailing_commas = False
#endregion

#region Regex Patterns
at_address_pattern = re.compile(r"(?:.*?)(?:[a-zA-Z_$][\w$]*\s*\*?\s[a-zA-Z_$][\w$]*)\s*((?:AT_ADDRESS|:)(?:\s*\(?\s*)(0x[0-9a-fA-F]+|[a-zA-Z_$][\w$]*)\)?);")
attribute_pattern = re.compile(r"(__attribute__)")
binary_literal_pattern = re.compile(r"\b(0b[01]+)\b")
trailing_initializer_pattern = re.compile(r"^.*?=\s*\{(?:.|\s)+?(,)\s*(?:\/\/.*?|\/\*.*?\*\/)*\s*?\}\s*;", re.MULTILINE)
enum_array_size_initializer_pattern = re.compile(r"\[\s*([a-zA-Z_$][\w$]*)\s*\]\s*;")
enum_declaration_pattern = re.compile(r"^.*(?:typedef\s+)*enum\s(?:[a-zA-Z_$][\w$]*)*\s*\{\s*((?:.|\s)*?)\}\s*(?:[a-zA-Z_$][\w$]*)*\s*;", re.MULTILINE)
enum_value_pattern = re.compile(r"([a-zA-Z_$][\w$]*)\s*(?:=\s*(.*))*")
word_pattern = re.compile(r"\b([a-zA-Z_][\w]*)\b")
white_space_pattern = re.compile(r"\s+")
cast_patterns = re.compile(r"\(int\)")
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

#region Strip Trailing Commas
def strip_initializer_trailing_commas(text_to_strip: str) -> str:
    if not text_to_strip:
        return text_to_strip
    
    trailing_comma_matches = reversed(list(re.finditer(trailing_initializer_pattern, text_to_strip)))
    for attribute_match in trailing_comma_matches:
        # Create the substring
        match_span = attribute_match.span(1)
        start_index = match_span[0]
        end_index = match_span[1]
        prefix = text_to_strip[0:start_index]
        postfix = text_to_strip[end_index:len(text_to_strip)]
        text_to_strip = prefix + postfix
    
    return text_to_strip
#endregion

#region Enums
def replace_enums_with_numeric_values(text_to_strip: str)->str:
    if not text_to_strip:
        return text_to_strip
    
    # Check if there are any uses of enums to initialize arrays
    enum_array_size_initializer_matches = list(re.finditer(enum_array_size_initializer_pattern, text_to_strip))
    if len(enum_array_size_initializer_matches) == 0:
        # None found, so no need to evaluate the enums
        return text_to_strip
    
    # We need to replace enums. But to do so we need to gather all of the enum values from the context thus far
    enum_declarations = list(re.finditer(enum_declaration_pattern, text_to_strip))
    if len(enum_declarations) == 0:
        return text_to_strip
    
    preprocessor = Preprocessor()
    enum_to_numeric_dict : dict[str, int] = {}
    for enum_declaration in enum_declarations:
        enum_members = enum_declaration[1]
        split_enum_members = enum_members.split(",")

        enum_numeric_value = 0
        for split_member in split_enum_members:
            split_member = re.sub(white_space_pattern, "", split_member)
            if not split_member or split_member.isspace():
                continue

            enum_value_match = re.match(enum_value_pattern, split_member)
            enum_member_name = enum_value_match[1]

            # Does the enum have an explicit value assigned?
            if enum_value_match[2]:
                assigned_value = enum_value_match[2]
                try:
                    # Replace usages of enum with numeric value
                    numeric_expression = enum_value_match[2]

                    # Remove casts
                    numeric_expression = re.sub(cast_patterns, "", numeric_expression)

                    # Replace enum names with numerical values
                    for word_match in reversed(list(re.finditer(word_pattern, numeric_expression))):
                        word = word_match[1]
                        if word not in enum_to_numeric_dict:
                            continue

                        word_span = word_match.span(1)
                        numeric_expression = numeric_expression[0:word_span[0]] + str(enum_to_numeric_dict[word]) + numeric_expression[word_span[1]:len(numeric_expression)]

                    # Try to parse it out
                    tokens = preprocessor.tokenize(numeric_expression)
                    evaluation = preprocessor.evalexpr(tokens)
                    assigned_value = evaluation[0]
                except Exception as e:
                    # Can't parse. Might be another enum
                    print(e)

                # Convert to int
                enum_numeric_value = int(assigned_value)

            # Record the value
            enum_to_numeric_dict[enum_member_name] = enum_numeric_value

            # By default the enum increases by 1
            enum_numeric_value += 1

    # With the enum map built we can now replace the usages with the numeric values
    enum_array_size_initializer_matches_reversed = reversed(enum_array_size_initializer_matches)
    for array_size_initializer_match in enum_array_size_initializer_matches_reversed:
        # Does this use a known enum?
        enum_name = array_size_initializer_match[1]
        if enum_name not in enum_to_numeric_dict:
            continue
        
        enum_numeric_value = enum_to_numeric_dict[enum_name]

        # Create the substring
        match_span = array_size_initializer_match.span(1)
        start_index = match_span[0]
        end_index = match_span[1]

        prefix = text_to_strip[0:start_index]
        postfix = text_to_strip[end_index:len(text_to_strip)]
        text_to_strip = prefix + str(enum_numeric_value) + postfix
    
    return text_to_strip
#endregion

#region Preprocessing
def generate_context(preprocessor_arguments: list[str], context_options: ContextGenerationOptions)->str:
    # Create the temp string writer to pass to the preprocessor since we still want to modify
    # the contents for project-specific conditions
    with StringIO() as preprocessor_string_writer:
        with redirect_stdout(preprocessor_string_writer):
            # Parse the target file:
            CmdPreprocessor(preprocessor_arguments)
          
            # Check if empty
            string_writer_position = preprocessor_string_writer.tell()
            if string_writer_position == 0:
                return None
            
            # Do we need to sanitize this further?
            if not context_options.should_strip_attributes and not context_options.should_strip_at_address and not context_options.should_strip_initializer_trailing_commas and not context_options.should_convert_binary_literals:
                # No sanitation needed, so write the entire file out
                return preprocessor_string_writer.getvalue()
            
            # Sanitize/change the file depending on the context options
            with StringIO() as context_string_writer:
                # Sanitize line-by line for easier parsing
                preprocessor_string_writer.seek(0)
                while True:
                    line_to_write = preprocessor_string_writer.readline()
                    if not line_to_write:
                        break

                    if context_options.should_strip_attributes:
                        line_to_write = strip_attributes(line_to_write)

                    if context_options.should_strip_at_address:
                        line_to_write = strip_at_address(line_to_write)

                    if context_options.should_convert_binary_literals:
                        line_to_write = convert_binary_literals(line_to_write)
                    
                    context_string_writer.writelines(line_to_write)
                
                # SIngle line cleanup completed
                generated_context = context_string_writer.getvalue()

                # Search for multi-line cleanup
                if context_options.should_strip_initializer_trailing_commas or context_options.should_replace_enums_in_initializers:
                    if context_options.should_strip_initializer_trailing_commas:
                        generated_context = strip_initializer_trailing_commas(generated_context)

                    if context_options.should_replace_enums_in_initializers:
                        generated_context = replace_enums_with_numeric_values(generated_context)
                
                return generated_context
#endregion

#region Main
def main():
    # Write initial parser
    parser = argparse.ArgumentParser(prog="Decomp Context", description="Wrapper around pcpp that can create a context file which can be used for decompilation", add_help=False)
    parser.add_argument("c_file", nargs="?", help="File from which to create context")
    parser.add_argument("-h", "-help", "--help", dest="help", action="store_true")
    parser.add_argument("-n64", "--n64-sdk", dest="n64_sdk", help="Path to the N64 SDK top level directory", action="store")
    parser.add_argument('-D', dest = 'defines', metavar = 'macro[=val]', nargs = 1, action = 'append', help = 'Predefine name as a macro [with value]')
    parser.add_argument("--strip-attributes", dest="strip_attributes", help="If __attribute__(()) string should be stripped", action="store_true", default=False)
    parser.add_argument("--strip-at-address", dest="strip_at_address", help="If AT_ADDRESS or : formatted string should be stripped", action="store_true", default=False)
    parser.add_argument("--strip-initializer_trailing_commas", dest="strip_initializer_trailing_commas", help="If trailing commas in initializers should be stripped", action="store_true", default=False)
    parser.add_argument("--convert-binary-literals", dest="convert_binary_literals", help="If binary literals (0bxxxx) should be converted to decimal", action="store_true", default=False)
    parser.add_argument("--replace-enums-in-initializers", dest="replace_enums_in_initializers", help="If enums should be replaced by its numeric value in initializers", action="store_true", default=False)
    parser.add_argument("--clipboard", dest="copy_to_clipboard", help="If the context should be copied to the clipboard", action="store_true", default=False)

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
        CmdPreprocessor(preprocessor_arguments).tokenize
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
    else:
        # Don't include the line directives if targeting Ghidra/m2c
        preprocessor_arguments.append("--line-directive")

    # For debugging purposes, include unfound includes in output to mark errors
    preprocessor_arguments.append("--passthru-unfound-includes")

    # Compress to minimize whitespace
    preprocessor_arguments.append("--compress")

    # Add unknown arguments and pass them to pcpp
    pass_through_args = parsed_args[1]
    preprocessor_arguments.extend(pass_through_args)

    # Add the file we want to read
    c_file = known_args.c_file
    preprocessor_arguments.append(known_args.c_file)

    # Check if we need to do further conversions after the file is preprocessed
    context_options = ContextGenerationOptions()
    context_options.should_strip_at_address = known_args.strip_at_address or known_args.ghidra or known_args.m2c
    context_options.should_strip_attributes = known_args.strip_attributes or known_args.m2c
    context_options.should_convert_binary_literals = known_args.convert_binary_literals or known_args.ghidra
    context_options.should_strip_initializer_trailing_commas = known_args.strip_initializer_trailing_commas or known_args.ghidra
    context_options.should_replace_enums_in_initializers = known_args.replace_enums_in_initializers or known_args.ghidra

    # Generate the context
    generated_context = generate_context(preprocessor_arguments, context_options)

    # Determine the file to write to
    target_file_name = None
    if known_args.output_path:
        target_file_name = known_args.output_path
    elif known_args.relative:
        target_file_name = f"{c_file}.ctx"
    else:
        target_file_name = os.path.join(os.getcwd(), default_output_filename)
    
    # Write the generated context to the file
    with open(target_file_name, "w", encoding="utf-8", newline="\n") as file_writer:
        file_writer.write(generated_context)

    # Check if we also want to copy to the clipboard
    if known_args.copy_to_clipboard:
        pyperclip.copy(generated_context)
#endregion

if __name__ == "__main__":
    main()
