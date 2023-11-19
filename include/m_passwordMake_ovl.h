#ifndef M_PASSWORDMAKE_OVL_H
#define M_PASSWORDMAKE_OVL_H

#include "types.h"
#include "m_passwordMake_ovl_h.h"
#include "m_submenu_ovl.h"
#include "m_personal_id.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  mPM_ENTRY_TOWN,
  mPM_ENTRY_PLAYER,

  mPM_ENTRY_NUM
};

struct passwordMake_ovl_s {
  int selected_idx;
  u8 lengths[mPM_ENTRY_NUM];
  u8 town_name[LAND_NAME_SIZE];
  u8 player_name[PLAYER_NAME_LEN];
};

#ifdef __cplusplus
}
#endif

#endif
