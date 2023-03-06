#ifndef PPC_EABI_INIT_H
#define PPC_EABI_INIT_H

#ifdef __cplusplus
extern "C"{
#endif

typedef void (*voidfunctionptr)(void); // pointer to function returning void
__declspec(section ".ctors") extern voidfunctionptr _ctors[];
__declspec(section ".dtors") extern voidfunctionptr _dtors[];

void __init_hardware(void);
void __flush_cache(void*, size_t);
void __init_user(void);
void __fini_cpp(void);
void _ExitProcess(void);

typedef struct RomSection {
    void* romOfs;     // at 0x4
    void* virtualOfs; // at 0x0
    size_t size;      // at 0x8
} RomSection;

typedef struct BssSection {
    void* virtualOfs; // at 0x0
    size_t size;      // at 0x8
} BssSection;

typedef struct ExtabIndexInfo {
    void* etiStart;  // at 0x0
    void* etiEnd;    // at 0x4
    void* codeStart; // at 0x8
    u32 codeSize;    // at 0x10
} ExtabIndexInfo;

__declspec(section ".init") extern  RomSection _rom_copy_info[];
__declspec(section ".init") extern  BssSection _bss_init_info[];
__declspec(section ".init") extern  ExtabIndexInfo _eti_init_info[];

#ifdef __cplusplus
}
#endif
#endif
