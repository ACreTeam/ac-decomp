#include "ac_npc_p_sel2.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_soncho.h"
#include "m_card.h"
#include "m_string.h"
#include "m_msg.h"
#include "m_font.h"
#include "m_vibctl.h"
#include "m_house.h"
#include "m_bgm.h"
#include "m_timeIn_ovl.h"
#include "dolphin/os/OSRtc.h"

enum {
    aNPS2_TALK_SETUP_YURE,
    aNPS2_TALK_SETUP_SOUND,
    aNPS2_TALK_SETUP_VOICE,
    aNPS2_TALK_SETUP_VOICE_OK,
    aNPS2_TALK_WHATS_HAPPEN,
    aNPS2_TALK_CHK_OPTION,
    aNPS2_TALK_CHK_OPTION2,
    aNPS2_TALK_CHK_CLR_VILLAGE_DATA_CARTRIDGE,
    aNPS2_TALK_CLR_VILLAGE_DATA_CARTRIDGE,
    aNPS2_TALK_CHK_CLR_PL_DATA,
    aNPS2_TALK_CHK_CLR_PL_DATA2,
    aNPS2_TALK_CHK_CLR_PL_DATA3,
    aNPS2_TALK_CHK_CLR_PL_DATA4,
    aNPS2_TALK_CHK_CLR_PASSPORT_FILE,
    aNPS2_TALK_CLR_PASSPORT_FILE,
    aNPS2_TALK_CLR_PL_DATA,
    aNPS2_TALK_TI_MENU_OPEN_MSG_WAIT,
    aNPS2_TALK_TI_MENU_OPEN_WAIT,
    aNPS2_TALK_TI_MENU_CLOSE_WAIT,
    aNPS2_TALK_SELECT_PLAYER,
    aNPS2_TALK_SELECT_CARD_PLAYER,
    aNPS2_TALK_CHK_FUZAI_PLAYER,
    aNPS2_TALK_CHK_KITAKU_PLAYER,
    aNPS2_TALK_START_TYPE0,
    aNPS2_TALK_START_TYPE1,
    aNPS2_TALK_START_TYPE2,
    aNPS2_TALK_START_TYPE3,
    aNPS2_TALK_RETURN_TITLE,
    aNPS2_TALK_WAIT,

    aNPS2_TALK_NUM
};

static void aNPS2_actor_ct(ACTOR* actorx, GAME* game);
static void aNPS2_actor_dt(ACTOR* actorx, GAME* game);
static void aNPS2_actor_init(ACTOR* actorx, GAME* game);
static void aNPS2_actor_move(ACTOR* actorx, GAME* game);
static void aNPS2_actor_draw(ACTOR* actorx, GAME* game);
static void aNPS2_actor_save(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_P_Sel2_Profile = {
    mAc_PROFILE_NPC_P_SEL2,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_P_SEL2,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_P_SEL2_ACTOR),
    &aNPS2_actor_ct,
    &aNPS2_actor_dt,
    &aNPS2_actor_init,
    mActor_NONE_PROC1,
    &aNPS2_actor_save,
};
// clang-format on

static u8 aNPS2_sound_mode[] = { Config_SOUND_MODE_STEREO, Config_SOUND_MODE_MONO, Config_SOUND_MODE_HEADPHONES };
static u8 aNPS2_voice_mode[] = { Config_VOICE_MODE_ANIMALESE, Config_VOICE_MODE_CLICK, Config_VOICE_MODE_SILENT };

static void aNPS2_talk_request(ACTOR*, GAME*);
static int aNPS2_talk_init(ACTOR*, GAME*);
static int aNPS2_talk_end_chk(ACTOR*, GAME*);

static void aNPS2_schedule_proc(NPC_ACTOR*, GAME_PLAY*, int);

static int aNPS2_count_player_sum(void);
static int aNPS2_setup_game_start(NPC_P_SEL2_ACTOR* p_sel2, GAME_PLAY* play);

static void aNPS2_change_talk_proc(NPC_P_SEL2_ACTOR* p_sel2, GAME_PLAY* play, int talk_idx);

static u8 static_str[mChoice_CHOICE_STRING_LEN * mChoice_CHOICE_NUM];

static void aNPS2_actor_ct(ACTOR* actorx, GAME* game) {
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        &aNPS2_actor_move,
        &aNPS2_actor_draw,
        5,
        (aNPC_TALK_REQUEST_PROC)&none_proc1,
        &aNPS2_talk_init,
        &aNPS2_talk_end_chk,
        0,
    };
    // clang-format on

    GAME_PLAY* play = (GAME_PLAY*)game;

    if (CLIP(npc_clip)->birth_check_proc(actorx, game) == TRUE) {
        NPC_P_SEL2_ACTOR* p_sel2 = (NPC_P_SEL2_ACTOR*)actorx;

        p_sel2->npc_class.schedule.schedule_proc = &aNPS2_schedule_proc;
        CLIP(npc_clip)->ct_proc(actorx, game, &ct_data);
        actorx->status_data.weight = MASSTYPE_IMMOVABLE;
        p_sel2->player_sum = aNPS2_count_player_sum();
        p_sel2->npc_class.talk_info.melody_inst = 0;
        p_sel2->npc_class.talk_info.memory = 0;

        mPlib_request_main_demo_wait_type1(game, FALSE, NULL);
        {
            ACTOR* player_actor = GET_PLAYER_ACTOR_GAME_ACTOR(game);

            if (player_actor != NULL) {
                player_actor->state_bitfield |= ACTOR_STATE_INVISIBLE;
            }
        }

        {
            xyz_t center;
            xyz_t eye;

            center.x = 100.0f;
            center.y = 60.0f;
            center.z = 60.0f;

            eye.x = 100.0f;
            eye.y = 130.0f;
            eye.z = 210.0f;

            Camera2_change_priority(play, 0);
            Camera2_request_main_lock(play, &center, &eye, 40.0f, 0, 100.0f, 400.0f, 5);
        }

        sAdo_SetOutMode(aNPS2_sound_mode[Save_Get(config).sound_mode]);
        sAdo_SetVoiceMode(aNPS2_voice_mode[Save_Get(config).voice_mode]);

        p_sel2->npc_class.condition_info.hide_request = FALSE;
        p_sel2->npc_class.condition_info.demo_flg = aNPC_COND_DEMO_SKIP_FEEL_CHECK;

        {
            static int base_msg_table[] = { MSG_5106, MSG_5146, MSG_5186, MSG_5226, MSG_5266, MSG_5306 };

            p_sel2->base_message = base_msg_table[mNpc_GetNpcLooks(actorx)];
        }

        {
            static int base_msg_table2[] = { MSG_14830, MSG_14840, MSG_14850, MSG_14860, MSG_14870, MSG_14880 };

            p_sel2->base_message2 = base_msg_table2[mNpc_GetNpcLooks(actorx)];
        }

        p_sel2->start_flag = FALSE;
    }
}

static void aNPS2_actor_save(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->save_proc(actorx, game);
}

static void aNPS2_actor_dt(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->dt_proc(actorx, game);
}

static void aNPS2_actor_init(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->init_proc(actorx, game);
}

static void aNPS2_actor_move(ACTOR* actorx, GAME* game) {
    NPC_P_SEL2_ACTOR* p_sel2 = (NPC_P_SEL2_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    CLIP(npc_clip)->move_proc(actorx, game);

    if (p_sel2->start_flag == TRUE && aNPS2_setup_game_start(p_sel2, play) == TRUE) {
        p_sel2->start_flag = FALSE;
    }

    mSC_change_player_freeze(play);
}

static void aNPS2_actor_draw(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_npc_p_sel2_schedule.c_inc"
#include "../src/actor/npc/ac_npc_p_sel2_talk.c_inc"
