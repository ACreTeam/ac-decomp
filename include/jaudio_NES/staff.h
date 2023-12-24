#ifndef STAFF_H
#define STAFF_H

#include "types.h"

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct staff_roll_info_s{
    s16 unk0;
    int unk4;
    f64 unk8;
}StaffRoll;

extern void Na_GetStaffRollInfo(void*);

#ifdef __cplusplus
 }
#endif


#endif