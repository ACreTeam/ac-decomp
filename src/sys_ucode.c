#include "sys_ucode.h"

long long int gspF3DZEX2_NoN_PosLight_fifoTextStart[1];
long long int gspF3DZEX2_NoN_PosLight_fifoDataStart[1];
long long int gspS2DEX2_fifoTextStart[1];
long long int gspS2DEX2_fifoDataStart[1];

s64* poly_tbl[] = { gspF3DZEX2_NoN_PosLight_fifoTextStart, gspF3DZEX2_NoN_PosLight_fifoDataStart };

s64* sprite_tbl[] = { gspS2DEX2_fifoTextStart, gspS2DEX2_fifoDataStart };

extern s64* ucode_GetPolyTextStart(void) {
    return poly_tbl[0];
}

extern s64* ucode_GetPolyDataStart(void) {
    return poly_tbl[1];
}

extern s64* ucode_GetSpriteTextStart(void) {
    return sprite_tbl[0];
}

extern s64* ucode_GetSpriteDataStart(void) {
    return sprite_tbl[1];
}
