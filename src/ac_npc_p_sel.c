#include "ac_npc_p_sel.h"

#include "m_config.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_soncho.h"
#include "m_play.h"
#include "m_card.h"
#include "m_bgm.h"
#include "m_choice.h"
#include "m_msg.h"
#include "m_vibctl.h"
#include "libultra/libultra.h"
#include "dolphin/os/OSRtc.h"

enum {
    aNPS_TALK_CHK_SETUP_SOUND,
    aNPS_TALK_SETUP_SOUND,
    aNPS_TALK_SETUP_VOICE,
    aNPS_TALK_CONFIRM_INPUT_DATA,
    aNPS_TALK_CONFIRM_INPUT_DATA2,
    aNPS_TALK_SETUP_YURE,
    aNPS_TALK_WAIT,

    aNPS_TALK_NUM
};

typedef void (*aNPS_THINK_PROC)(NPC_ACTOR*, GAME_PLAY*);

static void aNPS_actor_ct(ACTOR* actorx, GAME* game);
static void aNPS_actor_dt(ACTOR* actorx, GAME* game);
static void aNPS_actor_init(ACTOR* actorx, GAME* game);
static void aNPS_actor_save(ACTOR* actorx, GAME* game);
static void aNPS_actor_move(ACTOR* actorx, GAME* game);
static void aNPS_actor_draw(ACTOR* actorx, GAME* game);

static void aNPS_talk_request(ACTOR* actorx, GAME* game);
static void aNPS_change_talk_proc(NPC_P_SEL_ACTOR* p_sel, int talk_idx);
static int aNPS_talk_init(ACTOR* actorx, GAME* game);
static int aNPS_talk_end_chk(ACTOR* actorx, GAME* game);
static void aNPS_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);

// clang-format off
ACTOR_PROFILE Npc_P_Sel_Profile = {
    mAc_PROFILE_NPC_P_SEL,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_P_SEL,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_P_SEL_ACTOR),
    &aNPS_actor_ct,
    &aNPS_actor_dt,
    &aNPS_actor_init,
    mActor_NONE_PROC1,
    &aNPS_actor_save,
};
// clang-format on

static u8 aNPS_sound_mode[] = { Config_SOUND_MODE_STEREO, Config_SOUND_MODE_MONO, Config_SOUND_MODE_HEADPHONES };
static u8 aNPS_voice_mode[] = { Config_VOICE_MODE_ANIMALESE, Config_VOICE_MODE_CLICK, Config_VOICE_MODE_SILENT };

static void aNPS_actor_ct(ACTOR* actorx, GAME* game) {
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        &aNPS_actor_move,
        &aNPS_actor_draw,
        5,
        (aNPC_TALK_REQUEST_PROC)&none_proc1,
        &aNPS_talk_init,
        &aNPS_talk_end_chk,
        0,
    };
    // clang-format off

    GAME_PLAY* play = (GAME_PLAY*)game;
    NPC_P_SEL_ACTOR* p_sel = (NPC_P_SEL_ACTOR*)actorx;
    PLAYER_ACTOR* player;
    xyz_t center;
    xyz_t eye;

    if (CLIP(npc_clip)->birth_check_proc(actorx, game) == TRUE) {
        p_sel->npc_class.schedule.schedule_proc = &aNPS_schedule_proc;
        CLIP(npc_clip)->ct_proc(actorx, game, &ct_data);
        actorx->status_data.weight = MASSTYPE_IMMOVABLE;
        mPlib_request_main_demo_wait_type1(game, FALSE, NULL);

        player = GET_PLAYER_ACTOR(play);
        if (player != NULL) {
            player->actor_class.state_bitfield |= ACTOR_STATE_INVISIBLE;
        }

        center.x = 100.0f;
        center.y = 60.0f;
        center.z = 60.0f;

        eye.x = 100.0f;
        eye.y = 130.0f;
        eye.z = 210.0f;

        Camera2_change_priority(play, 0);
        Camera2_request_main_lock(play, &center, &eye, 40.0f, 0, 100.0f, 400.0f, 5);
        if (OSGetSoundMode() == OS_SOUND_MODE_MONO) {
            Save_Get(config).sound_mode = Config_SOUND_MODE_MONO;
        } else {
            Save_Get(config).sound_mode = Config_SOUND_MODE_STEREO;
        }
        
        sAdo_SetOutMode(aNPS_sound_mode[Save_Get(config).sound_mode]);
        Save_Get(config).voice_mode = Config_VOICE_MODE_ANIMALESE;
        sAdo_SetVoiceMode(aNPS_voice_mode[Save_Get(config).voice_mode]);

        p_sel->npc_class.condition_info.hide_request = FALSE;
        p_sel->npc_class.talk_info.default_act = aNPC_ACT_INTO_HOUSE;
    }
}

static void aNPS_actor_save(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->save_proc(actorx, game);
}

static void aNPS_actor_dt(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->dt_proc(actorx, game);
}

static void aNPS_actor_init(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->init_proc(actorx, game);
}

static void aNPS_actor_move(ACTOR* actorx, GAME* game) {
    NPC_P_SEL_ACTOR* p_sel;
    cKF_FrameControl_c* fc_p;
    f32 speed;
    u8 arm_flag;
    StaffRollInfo_c staffroll_info;

    p_sel = (NPC_P_SEL_ACTOR*)actorx;
    fc_p = &p_sel->npc_class.draw.main_animation.keyframe.frame_control;
    speed = 0.5f;
    arm_flag = TRUE;

    if (p_sel->npc_class.draw.animation_id == aNPC_ANIM_4HAKU_E1) {
        sAdos_GetStaffRollInfo(&staffroll_info);

        if (staffroll_info.staffroll_part != STAFFROLL_PART_FINISH) {
            speed = 0.0f;
            arm_flag = FALSE;
            fc_p->current_frame = 1.0f + 64.0f * (f32)staffroll_info.percent;
        }
    }

    fc_p->speed = speed;
    sAdos_TTKK_ARM(arm_flag);
    CLIP(npc_clip)->move_proc(actorx, game);
    mSC_change_player_freeze((GAME_PLAY*)game); // TODO: mSC_change_player_freeze almost certainly takes a GAME*
}

static void aNPS_actor_draw(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->draw_proc(actorx, game);
}

#include "../src/ac_npc_p_sel_schedule.c_inc"
#include "../src/ac_npc_p_sel_talk.c_inc"
