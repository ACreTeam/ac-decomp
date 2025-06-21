#ifndef AUDIOTABLE_H
#define AUDIOTABLE_H

#include "types.h"
#include "jaudio_NES/audiostruct.h"

extern f32 PCENTTABLE[];
extern f32 PCENTTABLE2[];
extern envdat DEFAULT_ENV[];
extern f32 PITCHTABLE[];
extern u8 DEFAULT_VTABLE[];
extern u8 DEFAULT_GTABLE[];

extern u8 BDB_SEQDATA[];
extern s16* WAVEMEM_TABLE[];

#endif
