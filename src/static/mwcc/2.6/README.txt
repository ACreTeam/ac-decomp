GameCube MWCC 2.6 MSL and runtime

Used only by the Australian GAFU01_00 build. The US library sources,
headers and compiler flags remain in their existing locations.

Imported from zeldaret/tp (CC0):
https://github.com/zeldaret/tp
Commit: c8fa8c9e2aab72cf4e5db0e5d1c84a9ea6ee6eb0
Paths: libs/PowerPC_EABI_Support/MSL/MSL_C and Runtime.
The cstdint header comes from MSL/MSL_C++/MSL_Common/Include.
See LICENSE.txt and the retained notices in individual files.

Adaptations for the 2.6 library linked into Animal Crossing:
- float.c retains TP's constants, including the required __float_max.
  Unreferenced constants, including __float_huge, are removed by the linker.
- Added ldiv/lldiv, strstr and __cvt_ull_flt from the existing project
  implementations; TP does not contain these functions. rand.c also uses
  the existing implementation because TP has no rand.c.
- sprintf is omitted because this executable supplies it from libultra.
- pow is force-active; its code generation is immediate so the pragma is
  still active when MWCC emits the function.
- math_ppc.c emits the header's __fpclassifyf definition out of line.
- __init_cpp_exceptions.cpp uses the returning GetR2 helper, and runtime
  constructor/destructor references use .ctors/.dtors instead of $ sections.
- runtime.c uses register directly in place of TP's __REGISTER SDK macro.
- include/global.h selects the GameCube branches of the imported sources.
- include/stddef.h bridges the new MSL headers to the existing Dolphin SDK.

The configure.py library entries preserve the original split/object names;
only their source root, local header paths and compiler options change.
All 54 objects match their Australian target code/data sections under
MWCC GC/2.6, including all 115 functions, when imported.

Validation:
- All 54 target library objects and 115 functions score 100% in objdiff-cli.
- GAFE01_00 library configuration is identical to the pre-import snapshot;
  its complete DOL/REL checksum checks pass.
- The Australian build completes static linking, REL generation and REL
  compression. Its DOL checksum check passes after correcting runtime
  function order. Its REL checksum check also passes after correcting game
  function retention/order and constant ordering.
