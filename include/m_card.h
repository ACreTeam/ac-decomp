#ifndef M_CARD_H
#define M_CARD_H

#include "types.h"
#include "libu64/gfxprint.h"
#include "m_personal_id.h"
#include "m_land_h.h"
#include "m_private.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  mLd_land_info_c land;
  PersonalID_c pid[PLAYER_NUM];
} mCD_persistent_data_c;

extern s32 mCD_GetThisLandSlotNo_code(int* player_no, s32* slot_card_results);
extern void mCD_save_data_aram_malloc();
extern void mCD_set_aram_save_data();
extern void mCD_init_card();

extern void mCD_PrintErrInfo(gfxprint_t* gfxprint);
extern void mCD_InitAll();
extern void mCD_LoadLand();
extern void mCD_toNextLand();

extern int mCD_EraseBrokenLand_bg(void*);
extern int mCD_card_format_bg(u8);
#ifdef __cplusplus
}
#endif

#endif
