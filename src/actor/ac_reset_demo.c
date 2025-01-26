#include "ac_reset_demo.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "libultra/libultra.h"

enum {
    aRSD_ACT_FIRST_SET,
    aRSD_ACT_RETIRE_NPC_WAIT,

    aRSD_ACT_NUM
};

static void aRSD_actor_ct(ACTOR* actorx, GAME* game);
static void aRSD_actor_dt(ACTOR* actorx, GAME* game);
static void aRSD_actor_move(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Reset_Demo_Profile = {
    mAc_PROFILE_RESET_DEMO,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(RESET_DEMO_ACTOR),
    &aRSD_actor_ct,
    &aRSD_actor_dt,
    &aRSD_actor_move,
    mActor_NONE_PROC1,
    NULL,
};
// clang-format on

static mDemo_Clip_c aRSD_clip;

static void aRSD_setupAction(RESET_DEMO_ACTOR* reset_demo, GAME_PLAY* play, int act);

static void aRSD_actor_ct(ACTOR* actorx, GAME* game) {
    RESET_DEMO_ACTOR* reset_demo = (RESET_DEMO_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    CLIP(demo_clip2) = &aRSD_clip;
    bzero(&aRSD_clip, sizeof(aRSD_clip));
    CLIP(demo_clip2)->demo_class = actorx;
    CLIP(demo_clip2)->type = mDemo_CLIP_TYPE_RESET_DEMO;
    aRSD_setupAction(reset_demo, play, aRSD_ACT_FIRST_SET);
}

static void aRSD_actor_dt(ACTOR* actorx, GAME* game) {
    RESET_DEMO_ACTOR* reset_demo = (RESET_DEMO_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (reset_demo->light_list != NULL) {
        Global_light_list_delete(&play->global_light, reset_demo->light_list);
    }

    if (CLIP(demo_clip2) != NULL) {
        CLIP(demo_clip2) = NULL;
    }
}

static void aRSD_set_point_light(RESET_DEMO_ACTOR* reset_demo, GAME_PLAY* play) {
    if (reset_demo->request_light == TRUE) {
        int now_sec = Common_Get(time.now_sec);

        if (now_sec > mTM_TIME2SEC(19, 0, 0) || now_sec < mTM_TIME2SEC(5, 0, 0)) {
            NPC_ACTOR* nactorx = (NPC_ACTOR*)reset_demo->reset_actor;
            s16 angleX = nactorx->head.angle_x + nactorx->actor_class.shape_info.rotation.x;
            s16 angleY = nactorx->head.angle_y + nactorx->actor_class.shape_info.rotation.y;
            xyz_t pos;
            f32 xz;

            pos.y = 30.0f * sin_s(angleX) + 20.0f * cos_s(angleX);
            xz = 30.0f * cos_s(angleX) - 20.0f * sin_s(angleX);
            pos.x = xz * sin_s(angleY);
            pos.z = xz * cos_s(angleY);

            // clang-format off
            Light_point_ct(&reset_demo->light,
                nactorx->actor_class.world.position.x + pos.x,
                nactorx->actor_class.world.position.y + pos.y,
                nactorx->actor_class.world.position.z + pos.z,
                255, 200, 0,
                92
            );
            // clang-format on

            if (reset_demo->light_list == NULL) {
                reset_demo->light_list = Global_light_list_new((GAME*)play, &play->global_light, &reset_demo->light);
            }
        } else {
            if (reset_demo->light_list != NULL) {
                Global_light_list_delete(&play->global_light, reset_demo->light_list);
                reset_demo->light_list = NULL;
            }
        }
    }
}

static void aRSD_first_set(RESET_DEMO_ACTOR* reset_demo, GAME_PLAY* play) {
    if (CLIP(npc_clip) != NULL && CLIP(npc_clip)->setupActor_proc != NULL) {
        if (CLIP(npc_clip)->setupActor_proc(play, reset_demo->reset_name, -1, -1, -1, 3, 2, 0, 0) == TRUE) {
            reset_demo->reset_actor = Actor_info_fgName_search(&play->actor_info, reset_demo->reset_name, ACTOR_PART_NPC);
            if (reset_demo->reset_actor != NULL) {
                aRSD_setupAction(reset_demo, play, aRSD_ACT_RETIRE_NPC_WAIT);
            }
        }
    }
}

static void aRSD_retire_npc_wait(RESET_DEMO_ACTOR* reset_demo, GAME_PLAY* play) {
    if (reset_demo->reset_actor == NULL) {
        play->submenu.start_refuse = FALSE;
        Actor_delete(&reset_demo->actor_class);
        mPlib_Set_unable_wade(FALSE);
        Common_Set(reset_flag, FALSE);
    } else {
        aRSD_set_point_light(reset_demo, play);
    }
}

static void aRSD_first_set_init(RESET_DEMO_ACTOR* reset_demo, GAME_PLAY* play) {
    // clang-format off
    static mActor_name_t majin_name[] = {
        SP_NPC_MAJIN_D07C,
        SP_NPC_MAJIN_D07D,
        SP_NPC_MAJIN,
        SP_NPC_MAJIN2,
        SP_NPC_MAJIN_BROTHER,
        SP_NPC_MAJIN3,
        SP_NPC_MAJIN4,
        SP_NPC_MAJIN_D080,
    };
    // clang-format on

    int reset = Now_Private->reset_count;

    play->submenu.start_refuse = TRUE;
    if (reset >= 9) {
        reset = 6 + ((reset - 9) % 3);
        Now_Private->reset_count = reset;
    }

    reset_demo->reset_name = majin_name[reset - 1];
}

static void aRSD_retire_npc_wait_init(RESET_DEMO_ACTOR* reset_demo, GAME_PLAY* play) {
    mPlib_Set_unable_wade(TRUE);
}

typedef void (*aRSD_ACT_INIT_PROC)(RESET_DEMO_ACTOR* reset_demo, GAME_PLAY* play);

static void aRSD_init_proc(RESET_DEMO_ACTOR* reset_demo, GAME_PLAY* play, int act) {
    static aRSD_ACT_INIT_PROC init_proc[] = { &aRSD_first_set_init, &aRSD_retire_npc_wait_init };

    (*init_proc[act])(reset_demo, play);
}

static void aRSD_setupAction(RESET_DEMO_ACTOR* reset_demo, GAME_PLAY* play, int action) {
    static aRSD_ACT_PROC process[] = { &aRSD_first_set, &aRSD_retire_npc_wait };

    reset_demo->act_proc = process[action];
    reset_demo->action = action;
    aRSD_init_proc(reset_demo, play, action);
}

static void aRSD_actor_move(ACTOR* actorx, GAME* game) {
    RESET_DEMO_ACTOR* reset_demo = (RESET_DEMO_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    (*reset_demo->act_proc)(reset_demo, play);
}
