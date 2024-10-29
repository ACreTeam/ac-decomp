#include "ac_npc_rtc.h"

#include "m_name_table.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "jaudio_NES/staff.h"
#include "m_msg.h"
#include "m_bgm.h"
#include "m_soncho.h"
#include "m_card.h"
#include "boot.h"
#include "m_string.h"
#include "libultra/libultra.h"
#include "m_timeIn_ovl.h"

enum {
    aNRTC_THINK_START,
    aNRTC_THINK_TITLE,
    aNRTC_THINK_DOOR,
    aNRTC_THINK_CHECK,
    aNRTC_THINK_IPMENU,
    aNRTC_THINK_WAIT,

    aNRTC_THINK_NUM
};

enum {
    aNRTC_TALK_BREAK_DATA,
    aNRTC_TALK_BREAK_DATA2,
    aNRTC_TALK_RTC_ERR,
    aNRTC_TALK_TIMER_OPEN_MSG_WAIT,
    aNRTC_TALK_TIMER_OPEN_WAIT,
    aNRTC_TALK_TIMER_CLOSE_WAIT,
    aNRTC_TALK_DELETE_BF,
    aNRTC_TALK_DELETE,
    aNRTC_TALK_FORMAT_CHK,
    aNRTC_TALK_FORMAT,
    aNRTC_TALK_END,

    aNRTC_TALK_NUM
};

static void aNRTC_actor_ct(ACTOR*, GAME*);
static void aNRTC_actor_dt(ACTOR*, GAME*);
static void aNRTC_actor_init(ACTOR*, GAME*);
static void aNRTC_actor_save(ACTOR*, GAME*);

// clang-format off
ACTOR_PROFILE Npc_Rtc_Profile = {
    mAc_PROFILE_NPC_RTC,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_RTC,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_RTC_ACTOR),
    &aNRTC_actor_ct,
    &aNRTC_actor_dt,
    &aNRTC_actor_init,
    mActor_NONE_PROC1,
    &aNRTC_actor_save,
};

static void aNRTC_actor_move(ACTOR*, GAME*);
static void aNRTC_actor_draw(ACTOR*, GAME*);

static int aNRTC_talk_init(ACTOR*, GAME*);
static int aNRTC_talk_end_chk(ACTOR*, GAME*);

static void aNRTC_schedule_proc(NPC_ACTOR*, GAME_PLAY*, int);

static void aNRTC_talk_request(ACTOR* actor, GAME*);

static void aNRTC_change_talk_proc(NPC_RTC_ACTOR* rtc, int idx);

static u8 aNRTC_sound_mode[] = { Config_SOUND_MODE_STEREO, Config_SOUND_MODE_MONO, Config_SOUND_MODE_HEADPHONES };
static u8 aNRTC_voice_mode[] = { Config_VOICE_MODE_ANIMALESE, Config_VOICE_MODE_CLICK, Config_VOICE_MODE_SILENT };

static void aNRTC_actor_ct(ACTOR* actor, GAME* game) {
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        &aNRTC_actor_move,
        &aNRTC_actor_draw,
        5,
        mActor_NONE_PROC1,
        &aNRTC_talk_init,
        &aNRTC_talk_end_chk,
        0,
    };
    // clang-format on

    NPC_RTC_ACTOR* rtc = (NPC_RTC_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;
    PLAYER_ACTOR* player;
    xyz_t center;
    xyz_t eye;
    if (Common_Get(clip.npc_clip)->birth_check_proc(actor, game) == TRUE) {
        rtc->npc_class.schedule.schedule_proc = &aNRTC_schedule_proc;
        Common_Get(clip.npc_clip)->ct_proc(actor, game, &ct_data);
        actor->status_data.weight = MASSTYPE_IMMOVABLE;
        mPlib_request_main_demo_wait_type1(game, 0, NULL);
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
        sAdo_SetOutMode(aNRTC_sound_mode[Save_Get(config.sound_mode)]);
        sAdo_SetVoiceMode(aNRTC_voice_mode[Save_Get(config.voice_mode)]);
        rtc->npc_class.condition_info.hide_request = 0;
        rtc->npc_class.talk_info.default_act = 9;
        rtc->npc_class.talk_info.melody_inst = 0;
        rtc->talk_flag = FALSE;
    }
}

static void aNRTC_actor_save(ACTOR* actor, GAME* game) {
    Common_Get(clip.npc_clip)->save_proc(actor, game);
}

static void aNRTC_actor_dt(ACTOR* actor, GAME* game) {
    Common_Get(clip.npc_clip)->dt_proc(actor, game);
}

static void aNRTC_actor_init(ACTOR* actor, GAME* game) {
    Common_Get(clip.npc_clip)->init_proc(actor, game);
}

static void aNRTC_actor_move(ACTOR* actor, GAME* game) {
    StaffRollInfo_c info;
    f32 val = 0.5f;
    u8 arm_flag = TRUE;
    NPC_RTC_ACTOR* rtc = (NPC_RTC_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (rtc->npc_class.draw.animation_id == aNPC_ANIM_4HAKU_E1) {
        sAdos_GetStaffRollInfo(&info);
        if (info.staffroll_part != STAFFROLL_PART_FINISH) {
            val = 0.0f;
            arm_flag = FALSE;
            rtc->npc_class.draw.main_animation.keyframe.frame_control.current_frame =
                1.0f + (64.0f * (f32)info.percent);
        }
    }

    rtc->npc_class.draw.main_animation.keyframe.frame_control.speed = val;
    sAdos_TTKK_ARM(arm_flag);
    Common_Get(clip.npc_clip)->move_proc(actor, game);
    mSC_change_player_freeze(play);
}

static void aNRTC_actor_draw(ACTOR* actor, GAME* game) {
    Common_Get(clip.npc_clip)->draw_proc(actor, game);
}

#include "../src/ac_npc_rtc_think.c.inc"
#include "../src/ac_npc_rtc_talk.c.inc"
