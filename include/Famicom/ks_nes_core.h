#ifndef KS_NES_CORE_H
#define KS_NES_CORE_H

#include "types.h"
#include "Famicom/ks_nes_common.h"

extern int ksNesReset(ksNesCommonWorkObj* wp, ksNesStateObj* sp, u32 flags, u8* chrramp, u8* bbramp);
extern void ksNesEmuFrame(ksNesCommonWorkObj* wp, ksNesStateObj* sp, u32 flags);
extern void ksNesPushResetButton(ksNesStateObj* sp);

#endif
