#ifndef AC_EV_TURKEY_H
#define AC_EV_TURKEY_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    PersonalID_c pid;
    u16 given_present_bitfield;
} aEv_turkey_save_c;

typedef struct {
    u8 _00;
    u8 _01;
    u8 _02;
} aEv_turkey_common_c;

typedef struct ev_turkey_actor_s EV_TURKEY_ACTOR;

typedef void (*aETKY_ACT_PROC)(EV_TURKEY_ACTOR* turkey);
typedef void (*aETKY_TALK_PROC)(EV_TURKEY_ACTOR* turkey, GAME_PLAY* play);
typedef void (*aETKY_TALK_SETUP_STATUS_PROC)(EV_TURKEY_ACTOR* turkey, GAME_PLAY* play, int talk_act);

struct ev_turkey_actor_s {
    NPC_ACTOR npc_class;
    int talk_action;
    aETKY_TALK_PROC talk_proc;
    aETKY_TALK_SETUP_STATUS_PROC talk_setup_proc;
    int talk_msg_no;
    int next_talk_action;
    aEv_turkey_save_c* ev_save_p;
    aEv_turkey_common_c* ev_common_p;
    u8 present_idx;
    u8 _9B1;
    aETKY_ACT_PROC act_proc;
    int action;
    int _9BC;
    xyz_t _9C0;
};

extern ACTOR_PROFILE Ev_Turkey_Profile;

#ifdef __cplusplus
}
#endif

#endif
