#include "ac_nameplate.h"
#include "m_npc.h"
#include "m_lib.h"
#include "m_name_table.h"
#include "m_field_info.h"
#include "m_demo.h"
#include "m_player_lib.h"
#include "m_msg.h"

extern void aNP_actor_init(ACTOR* actor, GAME* game);

ACTOR_PROFILE Nameplate_Profile = {
    mAc_PROFILE_NAMEPLATE,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    ACTOR_PROP_VILLAGER_SIGNBOARD,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NAMEPLATE_ACTOR),
    NONE_ACTOR_PROC,
    NONE_ACTOR_PROC,
    aNP_actor_init,
    NULL,
    NULL,
};

static void aNP_set_talk_info(ACTOR* actor) {
    rgba_t color;
    u8 name[ANIMAL_NAME_LEN];

    mNpc_GetAnimalPlateName(name, actor->world.position);
    mMsg_Set_free_str(mMsg_Get_base_window_p(), 0, name, ANIMAL_NAME_LEN);
    mDemo_Set_msg_num(MSG_4969);
    mDemo_Set_talk_display_name(0);
    mDemo_Set_ListenAble();
    mDemo_Set_camera(TRUE);
    mPlib_Set_able_hand_all_item_in_demo(TRUE);
    color.r = 205;
    color.g = 120;
    color.b = 0;
    color.a = 255;
    mDemo_Set_talk_window_color(&color);
}

static void aNP_actor_move(ACTOR* actor, GAME_PLAY* play) {
    PLAYER_ACTOR* player;
    s16 player_angle;
    int angle;

    if ((mDemo_Check(7, actor) == 0) && (mDemo_Check(8, actor) == 0)) {
        player = GET_PLAYER_ACTOR(play);
        if ((player != NULL) && (player->actor_class.world.position.z >= actor->world.position.z)) {
            player_angle = actor->player_angle_y;
            angle = (player_angle >= 0) ? player_angle : -player_angle;
            if (angle < 0x2000) {
                mDemo_Request(7, actor, aNP_set_talk_info);
            }
        }
    }
}

extern void aNP_actor_init(ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    mFI_SetFG_common(DUMMY_NAMEPLATE, actor->home.position, 0);
    aNP_actor_move(actor, play);
    actor->mv_proc = (mActor_proc)(aNP_actor_move);
}
