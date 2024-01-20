# Decompilation Basics And Tips

## Determining Slice Boundaries
When adding in a new Translation Unit (TU) you currently need to manually calculate the addresses for the TU's section boundaries. You can determine the boundaries for a new TU by using the [symbol map files extracted from the game](./extract_game.md) and adding an offset to the addresses.

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

## Generating Assembly Text File

To use sites such as [decomp.me](https://decomp.me) or [m2c](https://simonsoftware.se/other/m2c.html) you will need to paste in the assembly code you wish to match. The easiest way to get the assembly is by first generating an assembly text file with symbols included. To create this file run the following command at the root of the repository:

~~~console
python3 tools/ppcdis/disassembler.py config/rel.yml build/rel_labels.pickle build/rel_relocs.pickle rel.s -m config/symbols.yml
~~~

This will generate a `rel.s` file. Once generated open the file and search for the name of the function you wish to match and copy the assembly listed in the file for that function.