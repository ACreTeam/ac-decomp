# Decompilation Basics And Tips

## Adding TU Boundaries And Asset Boundaries With TU Config Tool
Adding boundaries for the binary sections and assets of a given TU can be done by using the [TU Config script](../tools/tu_config.py) inside of the tools folder. Using this tool allows you to more quickly add in the address boundaries for each section of a TU and optionally add in any assets to the asset config file.

To use this tool follow the steps below:
1. Run the command:

``` console
python3 ./tools/tu_config.py
```

2. Type the name of the TU you want to add to the config files.
3. If it detects that the TU had data assets it will prompt you if you would like to add them to the assets config file.
4. For each data symbol you will be given the option to add them to the config file or not.
5. If you are adding the symbol to the config file it will optionally ask you if you know the data type.
6. After the tool has finished, run the [configure script](../configure.py).

A list of tool parameters can be found below:

| Argument               | Description                                                                                    |
|------------------------|------------------------------------------------------------------------------------------------|
| `--symbol-map`         | Path to the [symbol map](./extract_game.md).                                                   |
| `--binary-slices-file` | Path to the binary slices config file. Defaults to [rel_slices.yml](../config/rel_slices.yml). |
| `--asset-slices-file` | Path to the asset slices config file. Defaults to [assets.yml](../config/assets.yml).          |


## Determining Slice Boundaries (Manual)
If you do not use the TU Config tool, you will need to manually add in the slice boundaries to the config file. You can determine the boundaries for a new TU by using the [symbol map files extracted from the game](./extract_game.md) and adding an offset to the addresses.

If using the symbol map, search for `<TU_NAME>.o` to find each applicable section, its start address and end address (usually the address of the next address with a different TU name attached to it). Note that some TUs may or may not have certain sections. You can determine this by searching through the symbol map and noting which sections are found.

The address offsets to add for each section in `foresta.rel` are:

| Section    | Offset       | Usage              |
|------------|--------------|--------------------|
| `.text:`   | `0x803702A8` | Code               |
| `.rodata:` | `0x80641260` | Const data         |
| `.data:`   | `0x8064D500` | Non-const data     |
| `.bss:`    | `0x8125A7C0` | Uninitialized data |

Once the boundaries have been determined, paste them into the [slices file](../config/rel_slices.yml). You will then have to re-run the [configuration script](../configure.py) after modifying the file.

> ### Example (ac_dummy.c)
>
> #### Symbol Map
>~~~
>  ...
>  00052540 000024 00052540  1 .data 	ac_dummy.o 
>  00052540 000024 00052540  4 Dummy_Profile 	ac_dummy.o 
>  00052568 0002a0 00052568  1 .data 	m_all_grow_ovl.o
>  ...
>  0019f590 000010 0019f590  1 .text 	ac_dummy.o 
>  0019f590 000004 0019f590  4 Dummy_Actor_ct 	ac_dummy.o 
>  0019f594 000004 0019f594  4 Dummy_Actor_dt 	ac_dummy.o 
>  0019f598 000004 0019f598  4 Dummy_Actor_draw 	ac_dummy.o 
>  0019f59c 000004 0019f59c  4 Dummy_Actor_move 	ac_dummy.o 
>  0019f5a0 005b84 0019f5a0  1 .text 	m_all_grow_ovl.o 
>  ...
>~~~
> #### Calculation
>~~~
>  .data start: (0x00052540 + 0x8064D500) = 0x8069FA40
>  .data end: (0x00052568 + 0x8064D500) = 0x8069FA68
>
>  .text start: (0x0019F590 + 0x803702A8) = 0x8050F838
>  .text end: (0x0019F5a0 + 0x803702A8) = 0x8050F848
>~~~
> #### Final
>~~~
>ac_dummy.c:
>    .data: [0x8069FA40, 0x8069FA68]
>    .text: [0x8050F838, 0x8050F848]
>~~~

## Determining Asset Boundaries
We declare asset data such as textures and palettes in the [assets config file](../config/assets.yml) and include them into the C file in which they are referenced. This process follows similar steps as above where a new entry for each data object is declared in the config file using the starting and ending address range. You can include the data type if it is known. Optionally this step can be done with the [TU Config tool](../tools/tu_config.py) instead of manually updating the file.

Once the data address range has been added to the config file, you can add it to the C source file using an `#include` statement following the format of `#include "assets/OBJECT_NAME"` where `OBJECT_NAME` is the name of the data object.

> :warning: Due to how the configure script scans through files, if you used `.c_inc` files you currently need to "hint" to the configure script that these files are referenced by using them in the root C file. An example can be found in [`ac_lotus.c`](../src/ac_lotus.c) and [`ac_lotus_draw.c_inc`](../src/ac_lotus_draw.c_inc)

After the steps above have been completed, run the [configure script](../configure.py).

## Generating Assembly Text File

To use sites such as [decomp.me](https://decomp.me) or [m2c](https://simonsoftware.se/other/m2c.html) you will need to paste in the assembly code you wish to match. The easiest way to get the assembly is by first generating an assembly text file with symbols included. To create this file run the following command at the root of the repository:

~~~console
python3 tools/ppcdis/disassembler.py config/rel.yml build/rel_labels.pickle build/rel_relocs.pickle rel.s -m config/symbols.yml
~~~

This will generate a `rel.s` file. Once generated open the file and search for the name of the function you wish to match and copy the assembly listed in the file for that function.

### Copying Function Assembly
To copy the assembly for a specific function, follow the steps below:
1. Open the generated `rel.s` file.
2. Search for the name of the function. Search for the first line with the format of `.global FUNCTION_NAME` where `FUNCTION_NAME` is the name of the function you are searching for.
3. Search for the line at the bottom of the assembly code block following the format `.size FUNCTION_NAME, . - FUNCTION_NAME` where `FUNCTION_NAME` is the name of the function you are searching for.
4. Select all of the lines between those two lines, include the two lines themselves.
5. Paste the copied assembly into the tool of your choice.