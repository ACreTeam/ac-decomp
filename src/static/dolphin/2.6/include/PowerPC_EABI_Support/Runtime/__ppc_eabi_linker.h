#ifndef __PPC_EABI_LINKER
#define __ppc_eabi_linker

#include "macros.h"

DECL_SECTION(".init") extern char _stack_addr[];
DECL_SECTION(".init") extern char _stack_end[];
DECL_SECTION(".init") extern char _heap_addr[];
DECL_SECTION(".init") extern char _heap_end[];
DECL_SECTION(".init") extern const char _fextabindex_rom[];
DECL_SECTION(".init") extern char _fextabindex[];
DECL_SECTION(".init") extern char _eextabindex[];

DECL_SECTION(".init") extern char _SDA_BASE_[];

DECL_SECTION(".init") extern char _SDA2_BASE_[];

typedef struct __rom_copy_info {
	char* rom;
	char* addr;
	unsigned int size;
} __rom_copy_info;

DECL_SECTION(".init") extern __rom_copy_info _rom_copy_info[];

typedef struct __bss_init_info {
	char* addr;
	unsigned int size;
} __bss_init_info;

DECL_SECTION(".init") extern __bss_init_info _bss_init_info[];

typedef struct __eti_init_info {
	void* eti_start;
	void* eti_end;
	void* code_start;
	unsigned long code_size;
} __eti_init_info;

DECL_SECTION(".init") extern __eti_init_info _eti_init_info[];
DECL_SECTION(".init") extern const char _f_init_rom[];
DECL_SECTION(".init") extern char _f_init[];
DECL_SECTION(".init") extern char _e_init[];
DECL_SECTION(".init") extern const char _f_text_rom[];
DECL_SECTION(".init") extern char _f_text[];
DECL_SECTION(".init") extern char _e_text[];
DECL_SECTION(".init") extern const char _f_rodata_rom[];
DECL_SECTION(".init") extern char _f_rodata[];
DECL_SECTION(".init") extern char _e_rodata[];
DECL_SECTION(".init") extern const char _fextab_rom[];
DECL_SECTION(".init") extern char _fextab[];
DECL_SECTION(".init") extern char _eextab[];
DECL_SECTION(".init") extern const char _f_data_rom[];
DECL_SECTION(".init") extern char _f_data[];
DECL_SECTION(".init") extern char _e_data[];
DECL_SECTION(".init") extern char _f_bss[];
DECL_SECTION(".init") extern char _e_bss[];
DECL_SECTION(".init") extern const char _f_sdata_rom[];
DECL_SECTION(".init") extern char _f_sdata[];
DECL_SECTION(".init") extern char _e_sdata[];
DECL_SECTION(".init") extern char _f_sbss[];
DECL_SECTION(".init") extern char _e_sbss[];
DECL_SECTION(".init") extern const char _f_sdata2_rom[];
DECL_SECTION(".init") extern char _f_sdata2[];
DECL_SECTION(".init") extern char _e_sdata2[];
DECL_SECTION(".init") extern char _f_sbss2[];
DECL_SECTION(".init") extern char _e_sbss2[];
DECL_SECTION(".init") extern const char _f_PPC_EMB_sdata0_rom[];
DECL_SECTION(".init") extern char _f_PPC_EMB_sdata0[];
DECL_SECTION(".init") extern char _e_PPC_EMB_sdata0[];
DECL_SECTION(".init") extern char _f_PPC_EMB_sbss0[];
DECL_SECTION(".init") extern char _e_PPC_EMB_sbss0[];

#endif // __PPC_EABI_LINKER
