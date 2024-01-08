from __future__ import annotations
import argparse
import os
import re
from enum import Enum
from enum import Flag
from io import StringIO

#region StringIO Util
def peek(string_reader: StringIO, peek_count: int = 1)-> str:
    pos = string_reader.tell()
    for i in range(peek_count):
        peek_char = string_reader.read(1)
    string_reader.seek(pos)

    return peek_char
#endregion

#region Evaluation Parser Classes
class ConditionalStackEntry(Flag):
    NONE = 0
    WRITEABLE = 2
    CONDITION_MET = 4

class EvaluationTokenType(Enum):
    NONE = 0
    OPEN_PAREN = 1
    CLOSE_PAREN = 2
    UNARY_OP = 3
    BINARY_OP = 4
    LITERAL = 5
    EXPR_END = 6

class EvaluationOperatorType(Enum):
    NONE = 0
    NOT = 1
    AND = 2
    OR = 3
    EQUALS = 4
    NOT_EQUALS = 5
    GREATER_THAN = 6
    GREATER_THAN_OR_EQ = 7
    LESS_THAN = 8
    LESS_THAN_OR_EQ = 9

evaluation_token_dict = {
        "(" : [EvaluationTokenType.OPEN_PAREN, EvaluationOperatorType.NONE],
        ")" : [EvaluationTokenType.CLOSE_PAREN, EvaluationOperatorType.NONE],
        "!" : [EvaluationTokenType.UNARY_OP, EvaluationOperatorType.NOT],
        "&&" : [EvaluationTokenType.BINARY_OP, EvaluationOperatorType.AND],
        "||" : [EvaluationTokenType.BINARY_OP, EvaluationOperatorType.OR],
        "==" : [EvaluationTokenType.BINARY_OP, EvaluationOperatorType.EQUALS],
        "!=" : [EvaluationTokenType.BINARY_OP, EvaluationOperatorType.NOT_EQUALS],
        ">" : [EvaluationTokenType.BINARY_OP, EvaluationOperatorType.GREATER_THAN],
        ">=" : [EvaluationTokenType.BINARY_OP, EvaluationOperatorType.GREATER_THAN_OR_EQ],
        "<" : [EvaluationTokenType.BINARY_OP, EvaluationOperatorType.LESS_THAN],
        "<=" : [EvaluationTokenType.BINARY_OP, EvaluationOperatorType.LESS_THAN_OR_EQ],
    }

class EvaluationToken:
    token_type = EvaluationTokenType.NONE
    token_operator = EvaluationOperatorType.NONE
    literal_value = ""

    def __init__(self, string_reader: StringIO)->None:
        c = string_reader.read(1)
        if not c:
            # End of the string reached
            self.token_type = EvaluationTokenType.EXPR_END
            self.token_operator = EvaluationOperatorType.NONE
            return
        
        peek_char = peek(string_reader)
        if c not in evaluation_token_dict and peek_char:
            # Not a recognized single character operator, but might be a two character one
            # so append another character
            combined_char = c + peek_char
            if combined_char in evaluation_token_dict:
                c = combined_char
                string_reader.read(1)

        if c in evaluation_token_dict:
            # Recognized token. Check for special case !=
            if c == "!" or c == ">" or c == "<":
                peek_char = peek(string_reader)
                if peek_char == "=":
                    c += peek_char
                    string_reader.read(1)

            # Assign types from the dictionary
            token_tuple = evaluation_token_dict[c]
            self.token_type = token_tuple[0]
            self.token_operator = token_tuple[1]
            return
        
        # Not a recognized token, so treat it as a literal
        while True:
            next_char = peek(string_reader)
            if not next_char or next_char in evaluation_token_dict:
                break

            peek_char = peek(string_reader, 2)
            if peek_char:
                # Check if the combination of the current and next char make a two character operator
                two_char_token = next_char + peek_char
                if two_char_token in evaluation_token_dict:
                    break
            
            # Append character and move to the next one
            c += next_char
            string_reader.read(1)
        
        # Save the generated value
        self.token_type = EvaluationTokenType.LITERAL
        self.literal_value = c

    @staticmethod
    def to_polish_notation(token_list: list[EvaluationToken]) -> list[EvaluationToken]:
        output_queue: list[EvaluationToken] = []
        stack: list[EvaluationToken] = []

        index = 0
        while index < len(token_list):
            token = token_list[index]

            match token.token_type:
                case EvaluationTokenType.LITERAL:
                    output_queue.append(token)
                case EvaluationTokenType.BINARY_OP | EvaluationTokenType.UNARY_OP | EvaluationTokenType.OPEN_PAREN:
                    stack.insert(0, token)
                case EvaluationTokenType.CLOSE_PAREN:
                    while stack[len(stack) - 1].token_type is not EvaluationTokenType.OPEN_PAREN:
                        output_queue.append(stack.pop())
                    
                    stack.pop()

                    if len(stack) > 0 and stack[len(stack) - 1].token_type is EvaluationTokenType.UNARY_OP:
                        output_queue.append(stack.pop())
            
            index += 1
        
        while len(stack) > 0:
            output_queue.append(stack.pop())
        
        output_queue.reverse()
        return output_queue

class BooleanExpression:
    left_expression: BooleanExpression = None
    right_expression: BooleanExpression = None
    
    expression_operator = EvaluationOperatorType.NONE
    literal_value = ""

    def __init__(self, operator: EvaluationOperatorType, left: BooleanExpression, right: BooleanExpression, value: str) -> None:
        self.expression_operator = operator
        self.left_expression = left
        self.right_expression = right
        self.literal_value = value

    @staticmethod
    def create_and(left: BooleanExpression, right: BooleanExpression)->BooleanExpression:
        return BooleanExpression(EvaluationOperatorType.AND, left, right, "0")
    
    @staticmethod
    def create_or(left: BooleanExpression, right: BooleanExpression)->BooleanExpression:
        return BooleanExpression(EvaluationOperatorType.OR, left, right, "0")
    
    @staticmethod
    def create_equals(left: BooleanExpression, right: BooleanExpression)->BooleanExpression:
        return BooleanExpression(EvaluationOperatorType.EQUALS, left, right, "0")
    
    @staticmethod
    def create_not_equals(left: BooleanExpression, right: BooleanExpression)->BooleanExpression:
        return BooleanExpression(EvaluationOperatorType.NOT_EQUALS, left, right, "0")
    
    @staticmethod
    def create_not(child: BooleanExpression)->BooleanExpression:
        return BooleanExpression(EvaluationOperatorType.NOT, child, None, "0")
    
    @staticmethod
    def create_less_than(left: BooleanExpression, right: BooleanExpression)->BooleanExpression:
        return BooleanExpression(EvaluationOperatorType.LESS_THAN, left, right, "0")
    
    @staticmethod
    def create_less_than_or_eq(left: BooleanExpression, right: BooleanExpression)->BooleanExpression:
        return BooleanExpression(EvaluationOperatorType.LESS_THAN_OR_EQ, left, right, "0")

    @staticmethod
    def create_greater_than(left: BooleanExpression, right: BooleanExpression)->BooleanExpression:
        return BooleanExpression(EvaluationOperatorType.GREATER_THAN, left, right, "0")
    
    @staticmethod
    def create_greater_than_or_eq(left: BooleanExpression, right: BooleanExpression)->BooleanExpression:
        return BooleanExpression(EvaluationOperatorType.GREATER_THAN_OR_EQ, left, right, "0")
    
    @staticmethod
    def create_literal(value: str)->BooleanExpression:
        return BooleanExpression(EvaluationOperatorType.NONE, None, None, value)

    @staticmethod
    def make_boolean_expression(tokens: list[EvaluationToken], index: list[int])->BooleanExpression:
        curr_token = tokens[index[0]]
        
        if curr_token.token_type == EvaluationTokenType.LITERAL:
            index[0] += 1
            return BooleanExpression.create_literal(curr_token.literal_value)
        
        if curr_token.token_operator == EvaluationOperatorType.NOT:
            index[0] += 1
            operand = BooleanExpression.make_boolean_expression(tokens, index)
            return BooleanExpression.create_not(operand)
        
        if curr_token.token_operator == EvaluationOperatorType.AND:
            index[0] += 1
            left = BooleanExpression.make_boolean_expression(tokens, index)
            right = BooleanExpression.make_boolean_expression(tokens, index)
            return BooleanExpression.create_and(left, right)
        
        if curr_token.token_operator == EvaluationOperatorType.OR:
            index[0] += 1
            left = BooleanExpression.make_boolean_expression(tokens, index)
            right = BooleanExpression.make_boolean_expression(tokens, index)
            return BooleanExpression.create_or(left, right)
        
        if curr_token.token_operator == EvaluationOperatorType.EQUALS:
            index[0] += 1
            left = BooleanExpression.make_boolean_expression(tokens, index)
            right = BooleanExpression.make_boolean_expression(tokens, index)
            return BooleanExpression.create_equals(left, right)
        
        if curr_token.token_operator == EvaluationOperatorType.NOT_EQUALS:
            index[0] += 1
            left = BooleanExpression.make_boolean_expression(tokens, index)
            right = BooleanExpression.make_boolean_expression(tokens, index)
            return BooleanExpression.create_not_equals(left, right)
        
        if curr_token.token_operator == EvaluationOperatorType.LESS_THAN:
            index[0] += 1
            left = BooleanExpression.make_boolean_expression(tokens, index)
            right = BooleanExpression.make_boolean_expression(tokens, index)
            return BooleanExpression.create_less_than(left, right)
        
        if curr_token.token_operator == EvaluationOperatorType.LESS_THAN_OR_EQ:
            index[0] += 1
            left = BooleanExpression.make_boolean_expression(tokens, index)
            right = BooleanExpression.make_boolean_expression(tokens, index)
            return BooleanExpression.create_less_than_or_eq(left, right)
        
        if curr_token.token_operator == EvaluationOperatorType.GREATER_THAN:
            index[0] += 1
            left = BooleanExpression.make_boolean_expression(tokens, index)
            right = BooleanExpression.make_boolean_expression(tokens, index)
            return BooleanExpression.create_greater_than(left, right)
        
        if curr_token.token_operator == EvaluationOperatorType.GREATER_THAN_OR_EQ:
            index[0] += 1
            left = BooleanExpression.make_boolean_expression(tokens, index)
            right = BooleanExpression.make_boolean_expression(tokens, index)
            return BooleanExpression.create_greater_than_or_eq(left, right)
        
        return None

    @staticmethod
    def evaluate_boolean_expression_node(node: BooleanExpression)-> int:
        if node.expression_operator == EvaluationOperatorType.NONE:
            stripped_value = node.literal_value.strip()

            try:
                if "0x" in stripped_value:
                    parsed_int_value = int(stripped_value, 16)
                else:
                    parsed_int_value = int(stripped_value)
                return parsed_int_value
            except Exception:
                return 0
        
        if node.expression_operator == EvaluationOperatorType.NOT:
            is_non_zero = BooleanExpression.evaluate_boolean_expression_node(node.left_expression) != 0
            if is_non_zero:
                return 0
            return 1
        if node.expression_operator == EvaluationOperatorType.OR:
            if BooleanExpression.evaluate_boolean_expression_node(node.left_expression) != 0 or BooleanExpression.evaluate_boolean_expression_node(node.right_expression) != 0:
                return 1
            return 0
        if node.expression_operator == EvaluationOperatorType.AND:
            if BooleanExpression.evaluate_boolean_expression_node(node.left_expression) != 0 and BooleanExpression.evaluate_boolean_expression_node(node.right_expression) != 0:
                return 1
            return 0
        if node.expression_operator == EvaluationOperatorType.EQUALS:
            if BooleanExpression.evaluate_boolean_expression_node(node.left_expression) == BooleanExpression.evaluate_boolean_expression_node(node.right_expression):
                return 1
            return 0
        if node.expression_operator == EvaluationOperatorType.NOT_EQUALS:
            if BooleanExpression.evaluate_boolean_expression_node(node.left_expression) != BooleanExpression.evaluate_boolean_expression_node(node.right_expression):
                return 1
            return 0
        if node.expression_operator == EvaluationOperatorType.LESS_THAN:
            if BooleanExpression.evaluate_boolean_expression_node(node.left_expression) < BooleanExpression.evaluate_boolean_expression_node(node.right_expression):
                return 1
            return 0
        if node.expression_operator == EvaluationOperatorType.LESS_THAN_OR_EQ:
            if BooleanExpression.evaluate_boolean_expression_node(node.left_expression) <= BooleanExpression.evaluate_boolean_expression_node(node.right_expression):
                return 1
            return 0
        if node.expression_operator == EvaluationOperatorType.GREATER_THAN:
            if BooleanExpression.evaluate_boolean_expression_node(node.left_expression) > BooleanExpression.evaluate_boolean_expression_node(node.right_expression):
                return 1
            return 0
        if node.expression_operator == EvaluationOperatorType.GREATER_THAN_OR_EQ:
            if BooleanExpression.evaluate_boolean_expression_node(node.left_expression) >= BooleanExpression.evaluate_boolean_expression_node(node.right_expression):
                return 1
            return 0
        
        return 0

    @staticmethod
    def evaluate_boolean_expression(expression: str)->bool:
        # Sanitize the string
        expression = re.sub(define_white_space_pattern, '', expression)

        tokens: list[EvaluationToken] = []
        with StringIO(expression) as string_reader:
            # Tokenize the string
            token = None
            while True:
                token = EvaluationToken(string_reader)
                tokens.append(token)

                if token.token_type is EvaluationTokenType.EXPR_END:
                    break

            # Convert to polish notation
            polish_notation = EvaluationToken.to_polish_notation(tokens)

            # Create expressions
            root_expression_node = BooleanExpression.make_boolean_expression(polish_notation, [0])
            evaluation = BooleanExpression.evaluate_boolean_expression_node(root_expression_node) != 0
            return evaluation
#endregion
        
#region Macro Info Class
class MacroInfo:
    arguments: list[str] = []
    value: str = None
    function_override_name: str = None

    def __init__(self, macro_value: str, macro_arguments: list[str], macro_override_name: str) -> None:
        self.value = macro_value
        self.arguments = macro_arguments
        self.function_override_name = macro_override_name
#endregion

#region Global Variables
script_dir = os.path.dirname(os.path.realpath(__file__))
root_dir = os.path.abspath(os.path.join(script_dir, ".."))
src_dir = os.path.join(root_dir, "src")
include_dir = os.path.join(root_dir, "include")
n64sdk_dir: str = None

include_pattern = re.compile(r'^#\s*include\s*[<"](.+?)[>"]$')
guard_pattern = re.compile(r"^#\s*if(?:(n)def|def)?\s*([a-zA-Z0-9_\!\(\)\&\|=><\s]*)(?:.*?)(?=(?:\s?\/\*|\s?\/\/))?")
else_pattern = re.compile(r"^#\s*(?:el(?:se|s)?(?:if)?)\s?([a-zA-Z0-9_\!\(\)\&\|=\s]*)(?=(?:\s?\/\*|\s?\/\/))?")
endif_pattern = re.compile(r"^#\s*endif")
define_pattern = re.compile(r"^(?:\/\*.*\*\/)?\s*#\s*define\s+([a-zA-Z_$][\w$]*)(?:\(([a-zA-Z0-9_,\s]*)(\)|\s*(?=\\)))?\s*((?:\\x|[^\\])*?)(\\?)\s*(?:\/\*|\/\/|$)")
defined_evaluation_token_pattern = re.compile(r"((?:defined\()([a-zA-Z_$][\w$]*)(?:\)))")
define_white_space_pattern = re.compile(r"\s+")
at_address_pattern = re.compile(r"(?:.*?)(?:[a-zA-Z_$][\w$]*\s*\*?\s[a-zA-Z_$][\w$]*)\s*((?:AT_ADDRESS\(|:)\s*(0x[0-9a-fA-F]+|[a-zA-Z_$][\w$]*)\)?);")
pragma_once_pattern = re.compile(r'^#\s*pragma once$')
word_pattern = re.compile(r"\b([a-zA-Z_][\w]*)\b")
attribute_pattern = re.compile(r"(__attribute__)")

defines: dict[str, MacroInfo] = {"F3DEX_GBI_2" : MacroInfo(None, None, None), "_LANGUAGE_C" : MacroInfo(None, None, None)}
quiet = False
expand_macros = False
strip_out_comments = False
strip_out_attributes = False
max_consecutive_newlines = -1
sanitize_at_address_syntax = False
evaluate_preprocessor_directives = False

pragma_once_visits: set[str] = set([])
consecutive_newlines = 0
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

#region Macro Expansion
def expand_for_macros(text_to_expand: str, check_for_defined_wrappers: bool = False, concatenate_pound_signs: bool = False, expand_empty_args_func = False)-> tuple[str, str]:
    if not text_to_expand:
        return text_to_expand, None
    
    # Replace the defined(TOKEN)'s with their numerical values
    if check_for_defined_wrappers:
        for split in re.finditer(defined_evaluation_token_pattern, text_to_expand):
            defined_expression = split[1]
            if not defined_expression:
                continue
            
            defined_token = split[2]
            numeric_value = "1" if defined_token in defines else "0"
            text_to_expand = text_to_expand.replace(defined_expression, numeric_value)
    
    # Split the string into individual words
    split_words = reversed(list(re.finditer(word_pattern, text_to_expand)))
    for word in split_words:
        macro_to_expand = word[0]
        if macro_to_expand not in defines:
            continue

        macro_span = word.span(1)

        # Word is a defined macro. Replace it
        define_value = defines[macro_to_expand]
        if define_value.arguments or define_value.function_override_name:
            # If we have an override, get the replacement function
            if define_value.function_override_name:
                # In case we have nested function replacements, keep searching
                # until we find the function that is expanded
                override_name = define_value.function_override_name
                while True:
                    override = defines[override_name]
                    override_name = override.function_override_name
                    
                    if override_name is not None:
                        continue

                    define_value = override
                    break

            paren_count = 0
            argument_values: list[str] = []
            
            text_func_substring = text_to_expand[macro_span[0]:len(text_to_expand)]
            with StringIO(text_func_substring) as function_string_reader:
                with StringIO() as var_writer:
                    while function_string_reader.tell() < len(text_func_substring):
                        # Make sure the end of the string has not been reached
                        curr_func_char = function_string_reader.read(1)
                        if curr_func_char is None:
                            if paren_count != 0:
                                print("Argument mismatch! Perhaps the arguments extend across multiple lines?")
                            break

                        # Keep reading until we've read the function name
                        if paren_count == 0:
                            if curr_func_char == "(":
                                paren_count = 1
                            continue

                        # Keep reading until we've reached either the end of function or reached a comma
                        end_of_argument = False
                        if curr_func_char == ",":
                            if paren_count == 1:
                                # End of argument
                                end_of_argument = True
                        elif curr_func_char == "(" or curr_func_char == "{" or curr_func_char == "[":
                            paren_count += 1
                        elif curr_func_char == ")" or curr_func_char == "}" or curr_func_char == "]":
                            paren_count -=1
                            if paren_count == 0:
                                end_of_argument = True

                        # Check if we reached the end of the argument
                        if end_of_argument:
                            argument_value = var_writer.getvalue().strip()
                            argument_values.append(argument_value)
                            var_writer = StringIO()
                            if paren_count == 0:
                                # Arguments complete. Function closed
                                break
                            continue
                        
                        # Append to the running variable name
                        var_writer.write(curr_func_char)

                # Create a sub-string of the function including arguments
                curr_func_idx = function_string_reader.tell()
                function_string_reader.seek(0)

            if not expand_empty_args_func and len(argument_values) != len(define_value.arguments):
                if len(argument_values) == 0:
                    if check_for_defined_wrappers:
                        return "1", None
                    
                    # Intentional replacement of one word for another so that it can be expanded
                    return None, text_to_expand

            # Now that we have the argument values, replace the words
            expanded_function = define_value.value    

            split_function_words = list(re.finditer(word_pattern, expanded_function))
            split_function_words_reversed = reversed(split_function_words)
            for function_word in split_function_words_reversed:
                if function_word[1] not in define_value.arguments:
                    continue

                function_word_span = function_word.span(1)
                argument_idx = define_value.arguments.index(function_word[1])
                word_replacement = ""
                if argument_idx < len(argument_values):
                    word_replacement = argument_values[argument_idx]

                prefix = expanded_function[0:function_word_span[0]]
                postfix = expanded_function[function_word_span[1]:len(expanded_function)]
                expanded_function = prefix + word_replacement + postfix
            
            # Replace the string
            prefix = text_to_expand[0:macro_span[0]]
            postfix = text_to_expand[macro_span[0] + curr_func_idx:len(text_to_expand)]
            text_to_expand = prefix + expanded_function + postfix

            # Don't need to do the logic below since this was to resolve a function
            continue

        define_string = define_value.value
        if not define_string:
            if check_for_defined_wrappers:
                define_string = "1"
            else:
                define_string = ""

        # Replace it in-line so that it doesn't mess up the overall ordering
        text_to_expand = text_to_expand[0:macro_span[0]] + define_string + text_to_expand[macro_span[1]:len(text_to_expand)]

    # Remove cases of ## since that just concatenates the string, which we don't need
    if concatenate_pound_signs:
        text_to_expand = text_to_expand.replace("##", "")

    return text_to_expand, None
#endregion

#region If Statement Evaluation
def evaluate_if_statement(if_statement: str) -> bool:
    if not if_statement:
        return True

    if_statement, _ = expand_for_macros(if_statement, check_for_defined_wrappers=True, concatenate_pound_signs=True)
    if_statement_evaluation = BooleanExpression.evaluate_boolean_expression(if_statement)
    return if_statement_evaluation
#endregion

#region Import .h File
def import_h_file(in_file: str, r_path: str, file_string_writer: StringIO) -> None:
    rel_path = os.path.join(root_dir, r_path, in_file)
    inc_path = os.path.join(include_dir, in_file)
    n64sdk_path = os.path.join(n64sdk_dir, in_file)
    if os.path.exists(rel_path):
        import_c_file(rel_path, file_string_writer)
    elif os.path.exists(inc_path):
        import_c_file(inc_path, file_string_writer)
    elif os.path.exists(n64sdk_path):
        import_c_file(n64sdk_path, file_string_writer)
    else:
        if not quiet:
            print("Failed to locate", in_file)
        exit(1)
#endregion

#region Import .c File
def read_line(string_reader: StringIO, in_open_comment_block: int)->tuple[str, str, bool]:
    number_of_lines_read = 0

    with StringIO() as full_line_writer:
        with StringIO() as commentless_line_writer:
            while True:
                current_char = string_reader.read(1)
                if not current_char:
                    # End of the file
                    break

                if current_char == "\n":
                    number_of_lines_read += 1
                    full_line_writer.write(current_char)
                    commentless_line_writer.write(current_char)
                    break

                peek_char = peek(string_reader, 1)
                if current_char == "/" and peek_char == "/":
                    # This is the start of a // comment which means everything coming after is commented out
                    while True:
                        full_line_writer.write(current_char)
                        current_char = string_reader.read(1)

                        if current_char == "\n" or not current_char:
                            if current_char == "\n":
                                full_line_writer.write(current_char)
                                commentless_line_writer.write(current_char)

                            number_of_lines_read += 1
                            break
                    break
                
                if current_char == "*" and peek_char == "/":
                    # End of a comment block. Still can't write to the commentless
                    # writer, so just skip ahead to the next char
                    in_open_comment_block = False
                    full_line_writer.write(current_char)
                    full_line_writer.write(peek_char)
                    string_reader.read(1)
                    continue

                if current_char == "/" and peek_char == "*":
                    in_open_comment_block = True

                # Write out the character
                full_line_writer.write(current_char)
                
                # Only write to the commentless writer if we're not commented out
                if not in_open_comment_block:
                    commentless_line_writer.write(current_char)

            full_line = full_line_writer.getvalue()
            commentless_line = commentless_line_writer.getvalue()
            return full_line, commentless_line, in_open_comment_block

def import_c_file(in_file: str, file_string_writer: StringIO) -> None:
    in_file = os.path.relpath(in_file, root_dir)
    if in_file in pragma_once_visits:
        return

    # Flag for whether the "Processing File" log has ben outputted 
    process_file_log_outputted = quiet

    can_write = True
    previous_conditions_met = True
    current_condition_met = True
    conditional_stack = [ConditionalStackEntry.CONDITION_MET | ConditionalStackEntry.WRITEABLE]
    in_open_comment_block = False

    file_contents = ""
    with open(in_file, encoding="utf-8") as file:
        file_contents = file.read()

    # Local function to help with writing line and outputting log
    def write_file_line(line_writer: StringIO, should_expand_macros: bool, should_strip_attributes: bool) -> str:
        nonlocal file_string_writer
        nonlocal can_write
        nonlocal previous_conditions_met
        nonlocal current_condition_met
        global consecutive_newlines

        if not can_write or line_writer.tell() == 0:
            # Can't write or there is nothing to write
            return

        if evaluate_preprocessor_directives:
            if not can_write or not previous_conditions_met or not current_condition_met:
                return

        line_to_write = line_writer.getvalue()
        is_white_space = str.isspace(line_to_write)
        if len(line_to_write) == 0 or is_white_space:
            consecutive_newlines += 1

            if max_consecutive_newlines >= 0 and consecutive_newlines > max_consecutive_newlines:
                # If we've reached the limit of consecutive newlines in a row, skip
                return
        else:
            # Reset the counter
            consecutive_newlines = 0

        # Only expand/strip is we have more than whitespace to work with
        if not is_white_space:
            if should_expand_macros and previous_conditions_met and current_condition_met:
                line_to_write, _ = expand_for_macros(line_to_write, check_for_defined_wrappers=False, concatenate_pound_signs=True, expand_empty_args_func=True)

            if should_strip_attributes and "__attribute__" in line_to_write:
                line_to_write = strip_attributes(line_to_write)
        
        file_string_writer.write(line_to_write)

        nonlocal process_file_log_outputted
        if process_file_log_outputted:
            return
        
        process_file_log_outputted = True

        nonlocal in_file
        print("Processing file", in_file)
        

    with StringIO(file_contents) as string_reader:
        idx = -1
        while True:
            with StringIO() as pending_line_writer:
                # Read until a newline character has been reached
                idx += 1
                full_line, commentless_line, in_open_comment_block = read_line(string_reader, in_open_comment_block)

                if not full_line:
                    # End of the file has been reached
                    break

                # Check if we want to write without comments
                line_to_write: str = None
                if strip_out_comments:
                    line_to_write = commentless_line
                else:
                    line_to_write = full_line

                # Reuse the same line writer, but clear on each loop
                pending_line_writer.write(line_to_write)

                # CASE 1: All whitespace
                is_white_space = str.isspace(line_to_write)
                if len(line_to_write) == 0 or is_white_space:
                    # If the string is all whitespace, there is nothing to parse and anothing that can change the parsing stack state
                    write_file_line(pending_line_writer, should_expand_macros=False, should_strip_attributes=False)
                    continue

                # CASE 2: Commented Out Blocks
                if in_open_comment_block:
                    # We don't want to act on any lines that commented out in blocks
                    # since it is essentially "dead" code
                    if strip_out_comments and full_line != commentless_line and len(commentless_line) <= 1:
                        continue

                    write_file_line(pending_line_writer, should_expand_macros=False, should_strip_attributes=False)
                    continue

                # Strip the end of the line of whitespace for our regex searches
                stripped_commentless_line = commentless_line.strip()

                # Check if the current condition for the scope we're in has been met
                current_condition_met = conditional_stack[len(conditional_stack) - 1] & ConditionalStackEntry.CONDITION_MET == ConditionalStackEntry.CONDITION_MET

                # CASE 3: #endif block
                endif_match = endif_pattern.match(stripped_commentless_line)
                if endif_match:
                    # End reached so we can pop the stacks
                    conditional_stack.pop()
                    
                    # Re-evaluate the flags since the stack changed
                    previous_conditions_met = True
                    can_write = True
                    for conditional_entry in conditional_stack:
                        previous_conditions_met &= conditional_entry & ConditionalStackEntry.CONDITION_MET == ConditionalStackEntry.CONDITION_MET
                        can_write &= conditional_entry & ConditionalStackEntry.WRITEABLE == ConditionalStackEntry.WRITEABLE
                    
                    if not evaluate_preprocessor_directives:
                        write_file_line(pending_line_writer, should_expand_macros=False, should_strip_attributes=False)
                    continue

                # CASE 4: #if/#ifdef/#ifndef
                guard_match = guard_pattern.match(stripped_commentless_line)
                if guard_match:
                    if not can_write:
                        # Earlier evaluation makes it so that we don't need to check this
                        conditional_stack.append(ConditionalStackEntry.CONDITION_MET)
                    else:
                        # What definition are we checking against?
                        is_ifndef_evaluation = False if not guard_match[1] else True
                        if_statement_to_evaluate = guard_match[2]
                        
                        current_condition_met = evaluate_if_statement(if_statement_to_evaluate)
                        if is_ifndef_evaluation:
                            current_condition_met = not current_condition_met

                        if is_ifndef_evaluation and not current_condition_met and idx == 0:
                            # Current assumption is if the first line is the ifndef guard and it fails, just short-circuit early
                            break

                        entry_to_add = ConditionalStackEntry.WRITEABLE
                        if current_condition_met:
                            entry_to_add |= ConditionalStackEntry.CONDITION_MET

                        conditional_stack.append(entry_to_add)

                    if not evaluate_preprocessor_directives:
                        write_file_line(pending_line_writer, expand_macros, should_strip_attributes=False)
                    continue

                # CASE 5: #else/#elif
                else_match = else_pattern.match(stripped_commentless_line)
                if else_match:
                    if current_condition_met:
                        # We alread met an earlier condition so we don't want to write any more lines
                        conditional_stack[len(conditional_stack) - 1] &= ~ConditionalStackEntry.WRITEABLE
                        can_write = False
                    else:
                        else_statemet_to_evaluate = else_match[1]
                        else_statement_condition_met = True
                        
                        if else_statemet_to_evaluate:
                            else_statement_condition_met = evaluate_if_statement(else_statemet_to_evaluate)

                        if else_statement_condition_met:
                            # We have fulfilled a condition
                            conditional_stack[len(conditional_stack) - 1] |= ConditionalStackEntry.CONDITION_MET

                    if not evaluate_preprocessor_directives:
                        write_file_line(pending_line_writer, expand_macros, should_strip_attributes=strip_out_attributes)
                    continue

                # If we're in a state where the line is functionally ignore, don't bother doing
                # any special evaluations
                if not can_write or not previous_conditions_met or not current_condition_met:
                    write_file_line(pending_line_writer, should_expand_macros=False, should_strip_attributes=False)
                    continue

                # CASE 6: #pragma once
                pragma_once_match = pragma_once_pattern.match(stripped_commentless_line)
                if pragma_once_match:
                    pragma_once_visits.add(in_file)
                    continue

                # CASE 7: #include
                include_match = include_pattern.match(stripped_commentless_line)
                if include_match:
                    # To avoid expanding header files that don't apply to our project such as #ifdef TARGET_PC
                    # we need to see if we've met the definition requirement. Otherwise skip the include
                    if can_write and previous_conditions_met and current_condition_met:
                        pending_line_writer = StringIO()
                        if not strip_out_comments:
                            pending_line_writer.write(f'/* "{in_file}" line {idx} "{include_match[1]}" */\n')

                        # Write out the contents to the pending line writer
                        import_h_file(include_match[1], os.path.dirname(in_file), pending_line_writer)

                        if not strip_out_comments:
                            pending_line_writer.write(f'/* end "{include_match[1]}" */\n')

                        write_file_line(pending_line_writer, should_expand_macros=False, should_strip_attributes=False)
                    continue

                # Case 8: #define
                define_match = define_pattern.match(stripped_commentless_line)
                if define_match:
                    define_symbol = define_match[1]
                    if define_symbol in defines:
                        print("Symbol already defined: ", define_symbol)

                    define_macro_signature = define_match[2]
                    define_value = define_match[4]
                    is_signature_closed = define_match[3] == ")"
                    is_multiline_define = define_match[5] == "\\"

                    if is_multiline_define:
                        while True:
                            # Read one new line
                            idx += 1
                            additional_line, additional_commentless_line, in_open_comment_block = read_line(string_reader, in_open_comment_block)

                            # Use the commentless version since it is easier to parse and expands out better
                            additional_stripped_line = additional_commentless_line.strip()
                            
                            # Add the line to the macro value and the line that will be printed
                            pending_line_writer.write(additional_commentless_line if strip_out_comments else additional_line)

                            # Check if this is the last line
                            is_last_line = additional_stripped_line[-1] != "\\"
                            last_char_index = len(additional_stripped_line)
                            if not is_last_line:
                                last_char_index -= 1
                            
                            # If the function signature has not yet been closed, keep adding to it until it does close
                            if define_macro_signature is not None and not is_signature_closed:
                                closing_paren_index = additional_stripped_line.find(")")
                                if closing_paren_index >= 0:
                                    is_signature_closed = True
                                    define_macro_signature += additional_stripped_line[0:closing_paren_index]
                                    define_value = additional_stripped_line[closing_paren_index + 2:last_char_index]
                                else:
                                    define_macro_signature += additional_stripped_line[0:last_char_index]
                            else:
                                define_value += " " + additional_stripped_line[0:last_char_index]

                            # Check if this is the end of the multiline define
                            if not is_last_line:
                                continue
                            break
                    
                    # Remove any attributes from the value
                    if strip_out_attributes and "__attribute__" in define_value:
                        define_value = strip_attributes(define_value)
                    
                    # Check if this is a macro function
                    signature_arguments: list[str] = None
                    if define_macro_signature is not None:
                        # Get the arguments
                        signature_arguments = []
                        for split_argument in define_macro_signature.split(","):
                            split_argument = split_argument.strip()
                            signature_arguments.append(split_argument)

                    # Expand out any potentially nested macros
                    define_value, function_override = expand_for_macros(define_value)
                        
                    # Add it to the dictionary
                    defines[define_symbol] = MacroInfo(define_value, signature_arguments, function_override)

                    if not expand_macros:
                        write_file_line(pending_line_writer, should_expand_macros=False, should_strip_attributes=False)
                    continue

                # CASE 9: Regular line. If we've made it here, this is just a regular
                # line and just needs to be check for certain patterns to be sanitized

                # CASE 9A: AT_ADDRESS
                if sanitize_at_address_syntax:
                    at_address_match = at_address_pattern.match(stripped_commentless_line)
                    if at_address_match:
                        original_line = pending_line_writer.getvalue()
                        pending_line_writer = StringIO()
                        pending_line_writer.write(original_line.replace(at_address_match[1], ""))

                # Write out the line with any sanitization already done
                write_file_line(pending_line_writer, expand_macros, should_strip_attributes=strip_out_attributes)
#endregion

#region Main
def main():
    parser = argparse.ArgumentParser(description="Create a context file which can be used for decomp.me")
    parser.add_argument("c_file", help="File from which to create context")
    parser.add_argument(
        "--relative", "-r", dest="relative", help="Extract context relative to the source file", action="store_true"
    )
    parser.add_argument(
        "--n64_sdk", "-n64", dest="n64sdk", help="Path to the N64 SDK", action="store"
    )
    parser.add_argument("--quiet", "-q", dest="quiet", help="Don't output anything", action="store_true")
    parser.add_argument("--define", "-d", dest="defines", help="Add a default definition to bring in potentially excluded sections", action="append")
    parser.add_argument("--max_consecutive_newlines", "-nl", dest="max_newlines", help="The maximum number of consecutive newlines to print before omitting", action="store")
    parser.add_argument("--m2c", "-m", dest="m2c", help="Convenience flag to turn on all settings needed to generate an m2c-friendly file", action="store_true", default=False)
    args = parser.parse_args()

    global quiet
    quiet = args.quiet    

    global n64sdk_dir
    n64sdk_dir = os.environ['N64_SDK'] if args.n64sdk is None else args.n64sdk
    n64sdk_dir = os.path.join(n64sdk_dir, "ultra/usr/include")

    global expand_macros
    global strip_out_comments
    global strip_out_attributes
    global max_consecutive_newlines
    global sanitize_at_address_syntax
    global evaluate_preprocessor_directives

    if args.m2c:
        expand_macros = True
        strip_out_comments = True
        strip_out_attributes = True
        sanitize_at_address_syntax = True
        evaluate_preprocessor_directives = True
        max_consecutive_newlines = 1

    if args.max_newlines is not None:
        max_consecutive_newlines = args.max_newlines

    global defines
    if args.defines is not None:
        for define in args.defines:
            defines[define] = MacroInfo("1", None, None)

    c_file = args.c_file
    with StringIO() as string_writer:
        if not expand_macros:
            for definition in defines:
                string_writer.write("#define " + definition + "\n")
        
        # Don't write, but do include the special MWERKS define for evaluation purposes
        if "__MWERKS__" not in defines:
            defines["__MWERKS__"] = MacroInfo("1", None, None)

        import_c_file(c_file, string_writer)
        filename = f"{c_file}.ctx" if args.relative else os.path.join(root_dir, "ctx.c")

        with open(filename, "w", encoding="utf-8", newline="\n") as f:
            file_contents = string_writer.getvalue()
            f.write(file_contents)
#endregion

if __name__ == "__main__":
    main()
