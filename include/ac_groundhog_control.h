#ifndef AC_GROUNDHOG_CONTROL_H
#define AC_GROUNDHOG_CONTROL_H

#include "types.h"
#include "m_actor.h"
#include "ac_groundhog_control_h.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aGHC_TIME_CHECK(hour, min, sec) \
    (Common_Get(time.now_sec) >= ((hour) * mTM_SECONDS_IN_HOUR + (min) * mTM_SECONDS_IN_MINUTE + (sec)))

typedef struct groundhog_control_actor_s GROUNDHOG_CONTROL_ACTOR;

enum {
    aGHC_ACTION_BEFORE_800,
    aGHC_ACTION_BIRTH_RESET_WAIT,
    aGHC_ACTION_BIRTH_RESET,
    aGHC_ACTION_RETIRE_RESET_WAIT,
    aGHC_ACTION_RESET_SPEECH_BGM_START_WAIT,
    aGHC_ACTION_SONCHO_SPEECH_START_WAIT,
    aGHC_ACTION_SONCHO_SPEECH_END_WAIT,
    aGHC_ACTION_FADE_OUT_START_WAIT,
    aGHC_ACTION_AFTER_800,

    aGHC_ACTION_NUM
};

enum {
    aGHC_ATTENTION_SONCHO,
    aGHC_ATTENTION_GROUNDHOG,

    aGHC_ATTENTION_NUM
};

enum {
    aGHC_EVENT_STATE_NONE,        /* nothing to report */
    aGHC_EVENT_STATE_MAJIN_DONE,  /* ac_ev_majin signals it is done */
    aGHC_EVENT_STATE_SONCHO_DONE, /* ac_ev_speech_soncho signals it is done */

    aGHC_EVENT_STATE_NUM
};

enum {
    aGHC_TERM_1_HOUR,
    aGHC_TERM_30_MIN,
    aGHC_TERM_15_MIN,
    aGHC_TERM_5_MIN,
    aGHC_TERM_1_MIN,
    aGHC_TERM_EVENT_TIME,

    aGHC_TERM_NUM
};

typedef struct groundhog_control_clip_s {
    int now_term;
    ACTOR* groundhog_npc_actor;
    ACTOR* attention_target_actor;
    int fading_title;
} aGHC_Clip_c;

typedef void (*aGHC_ACTION_PROC)(GROUNDHOG_CONTROL_ACTOR*, GAME_PLAY*);

struct groundhog_control_actor_s {
    ACTOR actor_class;
    int action;
    aGHC_ACTION_PROC action_proc;
    int event_state;
    int timer;
    aGHC_Clip_c clip;
    aGHC_event_area_c* event_area_p;
    int attention_mode;
};

typedef struct groundhog_save_s {
    int _00;
} aGHC_save_c;

extern ACTOR_PROFILE Groundhog_Control_Profile;

#ifdef __cplusplus
}
#endif

#endif
