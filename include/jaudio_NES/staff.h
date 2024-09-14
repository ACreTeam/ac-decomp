#ifndef STAFF_H
#define STAFF_H

#include "types.h"
#include "audio.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void Na_StaffRollInit(void);
extern void Na_StaffRollStart(s16 seq_no);
extern void Na_GetStaffRollInfo(StaffRollInfo_c* info);

#ifdef __cplusplus
}
#endif

#endif
