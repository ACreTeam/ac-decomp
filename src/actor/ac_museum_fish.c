#include "ac_museum_fish.h"
#include "m_kankyo.h"
#include "m_play.h"
#include "m_demo.h"
#include "m_name_table.h"
#include "m_item_name.h"
#include "m_msg.h"
#include "m_common_data.h"

/*
 NEW KNOWLEDGE:
Cuyler — Today at 10:56 AM
    yeah, the _move, _draw, _ct, _dt, and _save funcs all take ACTOR*, GAME*
    thankfully the ZZZ_Profile data objects give us the class size, just re-type it to ACTOR_PROFILE
Roeming — Today at 10:55 AM
    hmm, not sure I understand
Cuyler — Today at 10:55 AM
    so AC is a weird pseudo-inheritance class system since it's C
    all classes which inherit from ACTOR have an "actor profile"
    which is basically like a weird C++ vtable

    There will be data with this C file `ACTOR_PROFILE Museum_Fish_Profile;`
    and part of that data will be the size of our UNK_FISH_STRUCT,
    `Museum_Fish_Profile->class_size;`
*/

void Museum_Fish_Prv_data_init() {
}
void Museum_Fish_Actor_ct(ACTOR* actor, GAME* game) {
}
void Museum_Fish_Actor_dt(ACTOR* actor, GAME* game) {
    mfish_point_light_dt(actor, game);
}
int Museum_Fish_GetMsgNo(ACTOR* actorx) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;

    static u8 item_name[20];
    int itemArticle;
    mMsg_Window_c* msg;

    // who donated the fish?
    int playerNumber = actor->unk_14d28[actor->unk_14d24].unk2;
    mActor_name_t actorName = mNT_FishIdx2FishItemNo(actor->unk_14d28[actor->unk_14d24].unk0);
    mIN_copy_name_str(item_name, actorName);
    mMsg_Set_item_str_art(mMsg_Get_base_window_p(), 0, item_name, 0x10, mIN_get_item_article(actorName));

    if (playerNumber >= 1 && playerNumber <= 4) {
        mMsg_Set_free_str(mMsg_Get_base_window_p(), 0,
                          common_data.save.save.private_data[playerNumber - 1].player_ID.player_name, 8);
    }

    if (actor->unk_14d24 < actor->unk_14d20 - 1) {
        if (playerNumber >= 1 && playerNumber <= 4) {
            return 0x2fa2;
        } else {
            return 0x2fa3;
        }
    }

    if (playerNumber >= 1 && playerNumber <= 4) {
        return 0x2f9f;
    } else {
        return 0x2fa0;
    }
}
void Museum_Fish_Check_Talk_Distance() {
}
void Museum_Fish_Set_MsgFishInfo() {
}
void Museum_Fish_set_talk_info(ACTOR* actorx) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;

    static rgba_t window_color = { 255, 255, 0xcd, 255 };
    int r3;
    if (actor->unk_14d20 > 0) { // maybe related to if there are fish in the tank
        r3 = Museum_Fish_GetMsgNo(actorx);
        actor->unk_14d24 += 1; // maybe iterating through the fish donation record, given which fish are donated?
    } else {
        r3 = 0x2fa1;
    }

    mDemo_Set_msg_num(r3);
    mDemo_Set_talk_window_color(&window_color);
    mDemo_Set_talk_display_name(0);
    mDemo_Set_ListenAble();
    mDemo_Set_camera(CAMERA2_PROCESS_NORMAL);
    mDemo_Set_use_zoom_sound(TRUE);
}
void Museum_Fish_Talk_process() {
}
void Museum_Fish_Actor_move(ACTOR* actor, GAME* game) {
}
void Museum_Fish_Suisou_draw(ACTOR* actor, GAME* game) {
}
void kusa_before_disp() {
}
void Museum_Fish_Kusa_Draw(ACTOR* actor, GAME* game) {
}
void Museum_Fish_Actor_draw(ACTOR* actor, GAME* game) {
}
void mfish_cull_check() {
}
void mfish_point_ligh_pos_get() {
}
void mfish_point_light_ct(ACTOR* actor, GAME* game) {
}

void mfish_point_light_dt(ACTOR* actorx, GAME* game) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;

    if (actor->unk_14db8 != -1) {
        mEnv_CancelReservedPointLight(actor->unk_14db8, (GAME_PLAY*)game);
    }

    if (actor->unk_14dba != -1) {
        mEnv_CancelReservedPointLight(actor->unk_14dba, (GAME_PLAY*)game);
    }
}
void mfish_point_light_mv(ACTOR* actor, GAME* game) {
}

void mfish_normal_light_set(ACTOR* actor, GAME* _game) {
    LightsN* lights;
    GAME_PLAY* game = (GAME_PLAY*)_game;
    // TODO: figure out where these are actually coming from
    xyz_t r5;
    r5.x = 320;
    r5.y = 0;
    r5.z = 240;

    lights = Global_light_read(&game->global_light, game->game.graph);
    LightsN_list_check(lights, game->global_light.list, &r5);
    LightsN_disp(lights, game->game.graph);
}
