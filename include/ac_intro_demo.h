#ifndef AC_INTRO_DEMO_H
#define AC_INTRO_DEMO_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc_rcn_guide.h"
#include "ac_npc_station_master.h"
#include "ac_train1.h"
#include "m_demo.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aID_PLR_START_X_POS (mFI_BK_WORLDSIZE_X_F * 3 + 1.25f * mFI_UT_WORLDSIZE_X_F)
#define aID_PLR_START_Z_POS (mFI_BK_WORLDSIZE_Z_F * 1 + 3 * mFI_UT_WORLDSIZE_Z_F)

#define aID_OFF_UT_X_POS (mFI_BK_WORLDSIZE_X_F * 3 + 7 * mFI_UT_WORLDSIZE_X_F + mFI_UT_WORLDSIZE_HALF_X_F)
#define aID_OFF_UT_Z_POS (mFI_BK_WORLDSIZE_Z_F * 1 + 5 * mFI_UT_WORLDSIZE_Z_F) /* A @ 5 */

#define aID_OUT_OF_STATION_Z_POS (mFI_BK_WORLDSIZE_Z_F * 1 + 8.25f * mFI_UT_WORLDSIZE_Z_F)

enum {
    aID_STATE_INITIAL,
    aID_STATE_TAKEN_HOUSE,
    aID_STATE_FREE_HOUSE,

    aID_STATE_NUM
};

typedef struct actor_intro_demo_s INTRO_DEMO_ACTOR;

typedef void (*aID_ACT_PROC)(INTRO_DEMO_ACTOR*, GAME_PLAY*);

struct actor_intro_demo_s {
    ACTOR actor_class;
    int action;
    int next_action;
    aID_ACT_PROC action_proc;
    TRAIN1_ACTOR* train1_actor_p;
    ACTOR* station_master_actor_p; // TODO: correct type
    ACTOR* rcn_guide_actor_p;      // TODO: correct type
    int player_in_house;
    int player_intro_demo_state;
    int house_idx;
    int talk_flag;
    u8 first_field_bgm_state;
    int _1A0;
    int _1A4;
    int _1A8;
};

extern ACTOR_PROFILE Intro_Demo_Profile;

#ifdef __cplusplus
}
#endif

#endif
