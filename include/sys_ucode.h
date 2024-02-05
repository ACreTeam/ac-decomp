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

extern long long int gspF3DZEX2_NoN_PosLight_fifoDataStart[];
extern long long int gspF3DZEX2_NoN_PosLight_fifoTextStart[];

extern long long int gspS2DEX2_fifoDataStart[];
extern long long int gspS2DEX2_fifoTextStart[];

extern long long int* ucode_GetPolyTextStart();
extern long long int* ucode_GetPolyDataStart();
extern long long int* ucode_GetSpriteTextStart();
extern long long int* ucode_GetSpriteDataStart();

#ifdef __cplusplus
};
#endif

#endif
