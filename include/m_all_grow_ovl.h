#ifndef M_ALL_GROW_OVL_H
#define M_ALL_GROW_OVL_H

#include "types.h"
#include "m_time.h"
#include "m_field_info.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mAGrw_FOSSIL_NUM 5
#define mAGrw_HANIWA_NUM 3

extern void mAGrw_RenewalFgItem_ovl(lbRTC_time_c* time, int* haniwa_scheduled);
extern void mAGrw_SearchDump(mFI_unit_c* dump_info);

#ifdef __cplusplus
}
#endif

#endif
