#include "ac_npc_majin4.h"

#include <dolphin/os.h>
#include "libultra/libultra.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_font.h"
#include "m_msg.h"
#include "ac_reset_demo.h"
#include "m_bgm.h"
#include "m_house.h"
#include "m_rcp.h"

enum {
    aMJN4_THINK_START_WAIT,
    aMJN4_THINK_START_WAIT_ST,
    aMJN4_THINK_CALL,
    aMJN4_THINK_FORCE_RESET_END_WAIT,
    aMJN4_THINK_COLOR_FILTER_END_WAIT,
    aMJN4_THINK_CALL_2,
    aMJN4_THINK_EXIT,

    aMJN4_THINK_NUM
};

enum {
    aMJN4_TALK_END_WAIT,
    
    aMJN4_TALK_NUM
};

static void aMJN4_actor_ct(ACTOR* actorx, GAME* game);
static void aMJN4_actor_dt(ACTOR* actorx, GAME* game);
static void aMJN4_actor_move(ACTOR* actorx, GAME* game);
static void aMJN4_actor_draw(ACTOR* actorx, GAME* game);
static void aMJN4_actor_save(ACTOR* actorx, GAME* game);
static void aMJN4_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_Majin4_Profile = {
    mAc_PROFILE_NPC_MAJIN4,
    ACTOR_PART_NPC,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    SP_NPC_MAJIN4,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_MAJIN4_ACTOR),
    aMJN4_actor_ct,
    aMJN4_actor_dt,
    aMJN4_actor_init,
    mActor_NONE_PROC1,
    aMJN4_actor_save,
};
// clang-format on

static u8 l_fade_alpha = 0;
static u64 l_ResetTime = 0;

static void aMJN4_force_talk_request(ACTOR* actorx, GAME* game);
static void aMJN4_norm_talk_request(ACTOR* actorx, GAME* game);
static int aMJN4_talk_init(ACTOR* actorx, GAME* game);
static int aMJN4_talk_end_chk(ACTOR* actorx, GAME* game);

static void aMJN4_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);
static void aMJN4_setup_think_proc(NPC_MAJIN4_ACTOR* actor, GAME_PLAY* play, int think_idx);
static void aMJN4_change_talk_proc(NPC_MAJIN4_ACTOR* actor, int talk_idx);

static void aMJN4_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aMJN4_actor_move,
        aMJN4_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)none_proc1,
        aMJN4_talk_init,
        aMJN4_talk_end_chk,
        0,
    };

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        NPC_MAJIN4_ACTOR* actor = (NPC_MAJIN4_ACTOR*)actorx;

        actor->npc_class.schedule.schedule_proc = aMJN4_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
    }

    l_fade_alpha = 0;
    l_ResetTime = 0;
}

static void aMJN4_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aMJN4_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
    eEC_CLIP->effect_kill_proc(eEC_EFFECT_RESET_HOLE, RSV_NO);
    if (CLIP(demo_clip2) != NULL && CLIP(demo_clip2)->type == mDemo_CLIP_TYPE_RESET_DEMO) {
        ACTOR* demox = (ACTOR*)CLIP(demo_clip2)->demo_class;

        if (demox != NULL) {
            RESET_DEMO_ACTOR* reset_demo = (RESET_DEMO_ACTOR*)demox;

            reset_demo->reset_actor = NULL;
            reset_demo->request_light = FALSE;
        }
    }
}

static void aMJN4_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aMJN4_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
    actorx->shape_info.draw_shadow = FALSE;
}

static void aMJN4_set_animation(NPC_MAJIN4_ACTOR* actor, int think_idx) {
    static s16 animeSeqNo[] = { aNPC_ANIM_WAIT1, aNPC_ANIM_WAIT1, aNPC_ANIM_APPEAR1, aNPC_ANIM_WAIT_R1, aNPC_ANIM_WAIT_R1, aNPC_ANIM_WAIT_R1, aNPC_ANIM_GO_UG1 };

    NPC_CLIP->animation_init_proc((ACTOR*)actor, animeSeqNo[think_idx], FALSE);
}

#include "../src/actor/npc/ac_npc_majin4_talk.c_inc"
#include "../src/actor/npc/ac_npc_majin4_schedule.c_inc"

static void aMJN4_prenmi_draw(NPC_MAJIN4_ACTOR* actor, GAME* game) {
    GRAPH* graph = game->graph;

    OPEN_DISP(graph);
    if (l_fade_alpha != 0) {
        Gfx* gfx = NOW_OVERLAY_DISP;

        fade_black_draw(&gfx, l_fade_alpha);
        SET_OVERLAY_DISP(gfx);

        if (l_ResetTime != 0) {
            Gfx* gfx = NOW_OVERLAY_DISP;
            f32 time = OSTicksToMicroseconds(osGetTime() - l_ResetTime);
            f32 line_y;

            if (time < 500000.0f) {
                u32 alpha;
                
                
                gDPPipeSync(gfx++);
                gDPSetOtherMode(gfx++, G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE | G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE, G_AC_NONE | G_ZS_PRIM | G_RM_XLU_SURF | G_RM_XLU_SURF2);
                gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);

                alpha = (int)((time / 500000.0f) * -200.0f + 250.0f);
                line_y = (time / 500000.0f) * -15.0f + 127.0f;
                gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, alpha);
                
                gfx = gfx_gSPTextureRectangle1(gfx, 0, (u32)(line_y * 4), 320 << G_TEXTURE_IMAGE_FRAC, (u32)((line_y + 1) * 4), G_TX_RENDERTILE, 0, 0, 0, 0);
                gDPPipeSync(gfx++);   
            }

            SET_OVERLAY_DISP(gfx);
        }
    }
    CLOSE_DISP(graph);
}

static void aMJN4_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
    aMJN4_prenmi_draw((NPC_MAJIN4_ACTOR*)actorx, game);
}
