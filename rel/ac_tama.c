#include "ac_tama.h"

#include "m_name_table.h"
#include "m_player_lib.h"
#include "m_field_info.h"
#include "m_demo.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

static void aTAM_actor_ct(ACTOR* actorx, GAME* game);
static void aTAM_actor_init(ACTOR* actorx, GAME* game);
static void aTAM_actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Tama_Profile = {
  mAc_PROFILE_TAMA,
  ACTOR_PART_ITEM,
  ACTOR_STATE_TA_SET,
  SPORTSFAIR_BALLS_RED,
  ACTOR_OBJ_BANK_KEEP,
  sizeof(TAMA_ACTOR),
  &aTAM_actor_ct,
  mActor_NONE_PROC1,
  &aTAM_actor_init,
  &aTAM_actor_draw,
  NULL
};

static void aTAM_actor_ct(ACTOR* actorx, GAME* game) {
  TAMA_ACTOR* tama = (TAMA_ACTOR*)actorx;

  tama->structure_class.action = actorx->npc_id - SPORTSFAIR_BALLS_RED;
  tama->structure_class.structure_type = aSTR_TYPE_SPORTSFAIR_A + tama->structure_class.action;
  tama->structure_class.structure_pal = aSTR_PAL_KAGO_R + tama->structure_class.action;
}

#include "../rel/ac_tama_move.c_inc"

#include "../rel/ac_tama_draw.c_inc"
