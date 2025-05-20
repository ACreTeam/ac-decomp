# Decompilation Basics And Tips

## Determining Asset Boundaries
> [!IMPORTANT]
> This section has not yet been updated to reflect the new asset boundary workflow under DTK. It remains here for reference purposes only and should not be considered accurate to the current workflow.

We declare asset data such as textures and palettes in the [assets config file](../config/assets.yml) and include them into the C file in which they are referenced. This process follows similar steps as above where a new entry for each data object is declared in the config file using the starting and ending address range. You can include the data type if it is known. Optionally this step can be done with the [TU Config tool](../tools/tu_config.py) instead of manually updating the file.

Once the data address range has been added to the config file, you can add it to the C source file using an `#include` statement following the format of `#include "assets/OBJECT_NAME"` where `OBJECT_NAME` is the name of the data object.

> :warning: Due to how the configure script scans through files, if you used `.c_inc` files you currently need to "hint" to the configure script that these files are referenced by using them in the root C file. An example can be found in [`ac_lotus.c`](../src/ac_lotus.c) and [`ac_lotus_draw.c_inc`](../src/ac_lotus_draw.c_inc)

After the steps above have been completed, run the [configure script](../configure.py).

## Generating Assembly Text File

To use tools such as [decomp.me](https://decomp.me) or [m2c](https://simonsoftware.se/other/m2c.html) when not uploading from directly within objdiff, you will need to paste in the assembly code you wish to match. The easiest way to get the assembly is by first generating an assembly text file with symbols included. To create this file, run the following command:

```console
python3 decompctx.py <srcfile>.c
```

This will generate a `rel.s` file. Once generated, open the file and search for the name of the function you wish to match, then copy the assembly listed in the file for that function.

### Copying Function Assembly
To copy the assembly for a specific function, follow the steps below:
1. Open the generated `rel.s` file.
2. Search for the name of the function. Search for the first line with the format of `.global FUNCTION_NAME`, where `FUNCTION_NAME` is the name of the function you are searching for.
3. Search for the line at the bottom of the assembly code block following the format `.size FUNCTION_NAME, . - FUNCTION_NAME`, where `FUNCTION_NAME` is the name of the function you are searching for.
4. Select all of the lines between those two lines, including the two lines themselves.
5. Paste the copied assembly into the tool of your choice.
