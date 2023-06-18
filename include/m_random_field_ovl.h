#ifndef M_RANDOM_FIELD_OVL_H
#define M_RANDOM_FIELD_OVL_H

#include "types.h"
#include "m_random_field_h.h"
#include "m_field_make.h"
#include "game_h.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void mRF_MakeRandomField_ovl(mFM_combination_c* combi_table, mFM_combo_info_c* combo_info, int combo_count, GAME* game);

#ifdef __cplusplus
}
#endif

#endif
