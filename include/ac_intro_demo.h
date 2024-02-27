#ifndef AC_INTRO_DEMO_H
#define AC_INTRO_DEMO_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    aID_STATE_0,
    aID_STATE_TAKEN_HOUSE,
    aID_STATE_FREE_HOUSE,
    // more?

    aID_STATE_NUM
};

typedef struct actor_intor_demo_s INTRO_DEMO_ACTOR;

struct actor_intor_demo_s {
    ACTOR actor_class;
    int action;
    int rcn_action;
    void (*action_proc)(ACTOR*, GAME*);
    void* train1_actor_p;         // TODO: correct type
    void* station_master_actor_p; // TODO: correct type
    void* rcn_guide_actor_p;      // TODO: correct type
    int player_in_intro_demo;
    int player_intro_demo_state;
    int selected_house;
    int _198;
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
