Dolphin SDK sources and headers imported from zeldaret/tp:
https://github.com/zeldaret/tp/tree/c8fa8c9e2aab72cf4e5db0e5d1c84a9ea6ee6eb0/libs/dolphin

PAL's SDK objects use this isolated tree with GC/1.2.5n and SDK_REVISION=1.
The build maps the existing archive/TU names to src/ and puts include/ and include/dolphin/
ahead of the game's SDK headers. US and Australian SDK builds retain their
existing sources and flags. Matching status is maintained separately in
tools/pal.py.

All five PAL languages link all 81 SDK translation units. English PAL has
passed the full build hashes with the complete SDK linked.

Local adaptations: OSExec.c's argument-vector declaration and OSReboot.c's
argument pointer are const-correct. No runtime logic was changed.
OS.c's DriveInfo buffer is explicitly aligned to 32 bytes, as in the original.
The OS library uses unsigned chars; the other SDK libraries retain signed chars.
The PAL DOL configs force CARDGetSectorSize and CARDFormat active so the linker
retains these otherwise unreferenced entry points, as in the original binaries.
EXIBios.c uses -schedule off. DSP_INIT_IN_JAUDIO omits the SDK DSPInit definition
so JAudio's existing DSPInit stub remains authoritative; unused SDK task-manager
dependencies are not pulled into the link.
All SDK TUs define __GEKKO__, including those inheriting the alternate compiler
flags; OSReset.c requires it to emit the assembly Reset implementation.
