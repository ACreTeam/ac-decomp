#ifndef KS_NES_DRAW_H
#define KS_NES_DRAW_H

#include "types.h"
#include "Famicom/ks_nes_common.h"

extern void ksNesDrawInit(ksNesCommonWorkObj* wp);
extern void ksNesDraw(ksNesCommonWorkObj* wp, ksNesStateObj* sp);
extern void ksNesDrawEnd();

extern u8 ksNesPaletteNormal[];

#endif
