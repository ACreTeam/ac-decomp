#include "__ppc_eabi_linker.h"

#if __MWERKS__
#pragma exceptions off
#pragma internal on
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern void __init_cpp_exceptions(void);
extern void __fini_cpp_exceptions(void);

extern void __destroy_global_chain(void);
extern void __unregister_fragment(int);
extern int __register_fragment(struct __eti_init_info* info, char* TOC);

#ifdef __cplusplus
}
#endif

static int fragmentID = -2;

asm char* GetR2(void) {
    nofralloc
    mr r3, r2
    blr
}

void __init_cpp_exceptions(void) {
    if (fragmentID == -2) {
        fragmentID = __register_fragment(_eti_init_info, GetR2());
    }
}

void __fini_cpp_exceptions(void) {
    char* R2;
    if (fragmentID != -2) {
        __unregister_fragment(fragmentID);
        fragmentID = -2;
    }
}

__declspec(section ".ctors")
extern void* const __init_cpp_exceptions_reference = __init_cpp_exceptions;

__declspec(section ".dtors")
extern void* const __destroy_global_chain_reference = __destroy_global_chain;

__declspec(section ".dtors")
extern void* const __fini_cpp_exceptions_reference = __fini_cpp_exceptions;
