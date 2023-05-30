#ifndef M_CARD_H
#define M_CARD_H

#include "types.h"
#include "libu64/gfxprint.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u8 mCD_GetThisLandSlotNo_code(int* player_no, int* slot_card_results);
extern void mCD_save_data_aram_malloc();

extern void mCD_PrintErrInfo(gfxprint_t* gfxprint);
extern void mCD_InitAll();

#ifdef __cplusplus
}
#endif

#endif
