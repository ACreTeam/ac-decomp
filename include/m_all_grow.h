#ifndef M_ALL_GROW_H
#define M_ALL_GROW_H

#include "types.h"
#include "m_field_info.h"
#include "libu64/gfxprint.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mAGrw_DUMP_WIDTH 4
#define mAGrw_DUMP_HEIGHT 4

extern void mAGrw_SearchDump(mFI_unit_c* dump_info);

extern void mAGrw_PrintFossilHaniwa_debug(gfxprint_t* gfxprint);

#ifdef __cplusplus
}
#endif

#endif
