#ifndef SYS_UCODE_H
#define SYS_UCODE_H

#include "types.h"
#include "PR/mbi.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ucode_info_s {
    int type;
    void* ucode_p;
} ucode_info;

#define UCODE_TYPE_NONE 0
#define UCODE_TYPE_POLY_TEXT 1
#define UCODE_TYPE_POLY_DATA 2
#define UCODE_TYPE_SPRITE_TEXT 3
#define UCODE_TYPE_SPRITE_DATA 4

#define SP_UCODE_DATA_SIZE 0x800

extern long long int gspF3DZEX2_NoN_PosLight_fifoDataStart[];
extern long long int gspF3DZEX2_NoN_PosLight_fifoTextStart[];

extern unsigned long long gspS2DEX2_fifoDataStart[];
extern unsigned long long gspS2DEX2_fifoTextStart[];

extern long long int* ucode_GetPolyTextStart();
extern long long int* ucode_GetPolyDataStart();
extern unsigned long long* ucode_GetSpriteTextStart();
extern unsigned long long* ucode_GetSpriteDataStart();

#ifdef __cplusplus
};
#endif

#endif
