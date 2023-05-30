#ifndef FAMICOM_H
#define FAMICOM_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef u8 (*FAMICOM_GETSAVECHAN_PROC)(int* player_no, int* slot_card_result);

extern void famicom_setCallback_getSaveChan(FAMICOM_GETSAVECHAN_PROC getSaveChan_proc);

#ifdef __cplusplus
}
#endif

#endif
