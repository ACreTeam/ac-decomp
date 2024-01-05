#include "ac_boat_demo.h"

#include "libultra/libultra.h"
#include "ac_weather.h"
#include "m_bg_item.h"
#include "m_bgm.h"
#include "m_msg.h"

/* For whatever reason, this file seems to have -pool off */
#pragma push
#pragma pool_data off

static void aBTD_actor_ct(ACTOR* actorx, GAME* game);
static void aBTD_actor_dt(ACTOR* actorx, GAME* game);
static void aBTD_actor_move(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Boat_Demo_Profile = {
  mAc_PROFILE_BOAT_DEMO,
  ACTOR_PART_CONTROL,
  ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
  EMPTY_NO,
  ACTOR_OBJ_BANK_KEEP,
  sizeof(BOAT_DEMO_ACTOR),
  &aBTD_actor_ct,
  &aBTD_actor_dt,
  &aBTD_actor_move,
  mActor_NONE_PROC1,
  NULL
};

static mDemo_Clip_c aBTD_clip;

static u8 aBTD_island_prg[] = {
#include "assets/aBTD_island_prg.inc"
};

static u8 aBTD_island_ldr[] = {
#include "assets/aBTD_island_ldr.inc"
};

static void aBTD_setupAction(BOAT_DEMO_ACTOR* boat_demo, GAME_PLAY* play, int action);

static void aBTD_actor_ct(ACTOR* actorx, GAME* game) {
  BOAT_DEMO_ACTOR* boat_demo = (BOAT_DEMO_ACTOR*)actorx;
  GAME_PLAY* play = (GAME_PLAY*)game;

  Common_Get(clip).demo_clip2 = &aBTD_clip;
  bzero(&aBTD_clip, sizeof(aBTD_clip));
  Common_Get(clip).demo_clip2->class = boat_demo;
  Common_Get(clip).demo_clip2->type = mDemo_CLIP_TYPE_BOAT_DEMO;
  boat_demo->island_gba_loader_p = aBTD_island_ldr;
  boat_demo->island_gba_program_p = aBTD_island_prg;

  if (mFI_CheckBlockKind(play->block_table.block_x, play->block_table.block_z, mRF_BLOCKKIND_ISLAND) == TRUE) {
    boat_demo->at_island = TRUE;
    boat_demo->island_npc_info_registered = TRUE;
  }

  aBTD_setupAction(boat_demo, play, aBTD_ACTION_SENDO_BIRTH_WAIT);
}

static void aBTD_actor_dt(ACTOR* actorx, GAME* game) {
  if (Common_Get(clip).demo_clip2 != NULL) {
    Common_Get(clip).demo_clip2 = NULL;
  }
}

#include "../src/ac_boat_demo_move.c_inc"

#pragma pop
