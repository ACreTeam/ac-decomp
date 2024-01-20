# Decompilation Context
In order to use tools such as [decomp.me](https://decomp.me/), [m2c](https://simonsoftware.se/other/m2c.html), or [Ghidra](https://ghidra-sre.org/) more effectively you will need to generate a "context" file that contains all of the necessary functions and structures needed to properly parse extracted blocks.

To help make this easier you can use the [`decompctx.py`](../tools/decompctx.py) script located inside of the `tools/` folder. This script recursively includes and expands all of the header files used by the specified file.

## Generating Context
In order to generate the context for a given file run the following command:
~~~console
./tools/decompctx.py <PATH_TO_C_FILE>
~~~

This will generate a `ctx.h` file at the root of the project. You can then copy the content of this file to the tool of your choice.

The script attempts to use the `N64_SDK` environment path variable for the necessary [ultralib](https://github.com/decompals/ultralib) header files. If this environment variable has not been set, or if you'd like to use an alternative SDK path, a path can be provided by using the `--n64-sdK` flag (see below).

If generating context for Ghidra or m2c, use the `--ghidra` or `--m2c` respectively as those tools require specific changes to be made to the generated context.

## Tool Arguments
You can modify the output of the context by passing in specific arguments. Some tools may require specific options to be turned on or off. For convenience certains tools have flags that automatically set these options.

| Argument                    | Description                                                          |
|-----------------------------|----------------------------------------------------------------------|
| `--ghidra`                  | Outputs Ghidra-friendly context.                                     |
| `--m2c`                     | Outputs m2c-friendly context.                                        |
| `-o`                        | Specifies a specific path to output the context file to.             |
| `-r`                        | If the context file should be output relative to the source file.    |
| `--n64-sdk`                 | Specify the top-level path of the N64 SDK.                           |
| `--strip-attributes`        | If `__attribute__(())` usages should be stripped.                    |
| `--strip-at-address`        | Strips out `AT_ADDRES()` and `:` uses.                               |
| `--convert_binary_literals` | Converts binary literals (0bxxxx) to decimal format.                 |
| `--clipboard`               | Copies the contents of the generated context file to your clipboard. |


## Preprocessor Arguments
`decompctx.py` uses [pcpp](https://pypi.org/project/pcpp/) to preprocess and expand the header files used by the file argument. `decompctx.py` will automatically pass arguments to `pcpp`. For a list of additional preprocessor arguments you can use, please refer to the [pcpp page](https://github.com/ned14/pcpp).