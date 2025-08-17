#ifndef AC_BOAT_DEMO_H
#define AC_BOAT_DEMO_H

#include "types.h"
#include "m_actor.h"
#include "m_demo.h"
#include "ac_boat.h"
#include "ac_npc_sendo.h"
#include "ac_ev_castaway.h"
#include "m_common_data.h"

#ifdef __cplusplus
extern "C" {
#endif

// Aus version increased program size by 0x04 bytes
#if VERSION >= VER_GAFU01_00
#define aBTD_LOADER_SIZE 0xC83C
#define aBTD_PROGRAM_SIZE 0x15248
#else
#define aBTD_LOADER_SIZE 0xC83C
#define aBTD_PROGRAM_SIZE 0x15244
#endif

enum {
    aBTD_ACTION_SENDO_BIRTH_WAIT,
    aBTD_ACTION_PL_RIDE_ON_START_WAIT,
    aBTD_ACTION_PL_RIDE_ON_END_WAIT,
    aBTD_ACTION_START_CALL_END_WAIT,
    aBTD_ACTION_SONG_BGM_START_WAIT,
    aBTD_ACTION_SING_SENDO_START_WAIT,
    aBTD_ACTION_SING_SENDO_MSG_SET_WAIT,
    aBTD_ACTION_SENDO_DIALOGUE_START_WAIT,
    aBTD_ACTION_SING_SENDO_START_WAIT2,
    aBTD_ACTION_MOVE_BOAT_END_WAIT,
    aBTD_ACTION_TOUCH_WHARF_END_WAIT,
    aBTD_ACTION_PL_RIDE_OFF_START_WAIT,
    aBTD_ACTION_PL_RIDE_OFF_END_WAIT,
    aBTD_ACTION_ANCHOR_WAIT,

    aBTD_ACTION_NUM
};

enum {
    aBTD_DEMO_PL_RIDE_ON_START,
    aBTD_DEMO_PL_RIDE_ON_END,
    aBTD_DEMO_START_CALL_END,
    aBTD_DEMO_MOVE_BOAT_END,
    aBTD_DEMO_TOUCH_WHARF_END,
    aBTD_DEMO_PL_RIDE_OFF_START,
    aBTD_DEMO_PL_RIDE_OFF_END,
    aBTD_DEMO_ANCHOR,

    aBTD_DEMO_NUM
};

typedef struct boat_demo_s BOAT_DEMO_ACTOR;

#define aBTD_GET_DEMO_ACTOR() (BOAT_DEMO_ACTOR*)(Common_Get(clip).demo_clip2->demo_class)

typedef void (*aBTD_PROC)(BOAT_DEMO_ACTOR*, GAME_PLAY*);

struct boat_demo_s {
    ACTOR actor_class;
    int action;
    aBTD_PROC action_proc;
    int demo_act;
    int song_bgm_timer;
    BOAT_ACTOR* boat_actor;
    NPC_SENDO_ACTOR* npc_sendo_actor;
    EV_CASTAWAY_ACTOR* castaway_actor;
    int at_island;
    xyz_t passenger_ofs;
    f32 boat_speed;
    int island_npc_info_registered;
    u8* island_gba_loader_p;
    u8* island_gba_program_p;
    u8 player_pattern;
    u8 sing_dialog_ofs;
    u8 sing_2nd_part;
    u8 sing_2nd_part_bgm_no;
    int sing_msg_no;
    u16 touch_wharf_timer;
    u8 touching_wharf;
};

extern ACTOR_PROFILE Boat_Demo_Profile;

#ifdef __cplusplus
}
#endif

#endif
