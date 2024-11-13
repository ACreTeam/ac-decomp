#include "ac_museum_fish.h"
#include "m_kankyo.h"
#include "m_play.h"
#include "m_demo.h"
#include "m_name_table.h"

// TODO: move function declarations and struct declarations into ac_museum_fish.h
// maybe we move all the different .text sections into .inc files

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

typedef struct {
    s16 unk0;
    s16 unk2;
} UNK_FISH_STRUCT_2S16;

typedef struct {
    ACTOR actor;
    u8 _00_padding[0x14BAC];
    int unk_14d20;
    int unk_14d24;
    UNK_FISH_STRUCT_2S16 unk_14d28[1];

    u8 _14d28_padding[0x8c];
    s16 unk_14db8;
    s16 unk_14dba;
} UNK_FISH_STRUCT;

void Museum_Fish_Prv_data_init();
void Museum_Fish_Actor_ct();
void Museum_Fish_Actor_dt();
int Museum_Fish_GetMsgNo(UNK_FISH_STRUCT* r31);
void Museum_Fish_Check_Talk_Distance();
void Museum_Fish_Set_MsgFishInfo();
void Museum_Fish_set_talk_info();
void Museum_Fish_Talk_process();
void Museum_Fish_Actor_move();
void Museum_Fish_Suisou_draw();
void kusa_before_disp();
void Museum_Fish_Kusa_Draw();
void Museum_Fish_Actor_draw();
void mfish_cull_check();
void mfish_point_ligh_pos_get();
void mfish_point_light_ct();
void mfish_point_light_dt(UNK_FISH_STRUCT* r30, GAME_PLAY* r31);
void mfish_point_light_mv();
void mfish_normal_light_set();

void Museum_Fish_Prv_data_init() { }
void Museum_Fish_Actor_ct() { }
void Museum_Fish_Actor_dt(UNK_FISH_STRUCT* r30, GAME_PLAY* r31) {
    mfish_point_light_dt(r30, r31);
}
int Museum_Fish_GetMsgNo(UNK_FISH_STRUCT* r29) 
{ 
    s16 temp = r29->unk_14d28[r29->unk_14d24].unk2;
    mNT_FishIdx2FishItemNo(r29->unk_14d28[r29->unk_14d24].unk0);
    mNT_FishIdx2FishItemNo(temp);

    // TODO: start here

}
void Museum_Fish_Check_Talk_Distance() { }
void Museum_Fish_Set_MsgFishInfo() { }
void Museum_Fish_set_talk_info(UNK_FISH_STRUCT* r31) 
{ 
    static rgba_t window_color = {255,255,0xcd,255};
    int r3;
    if(r31->unk_14d20 > 0) { // maybe related to if there are fish in the tank
        r3 = Museum_Fish_GetMsgNo(r31);
        r31->unk_14d24 += 1; // maybe iterating through the fish donation record, given which fish are donated?
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
void Museum_Fish_Talk_process() { }
void Museum_Fish_Actor_move() { }
void Museum_Fish_Suisou_draw() { }
void kusa_before_disp() { }
void Museum_Fish_Kusa_Draw() { }
void Museum_Fish_Actor_draw() { }
void mfish_cull_check() { }
void mfish_point_ligh_pos_get() { }
void mfish_point_light_ct() { }


void mfish_point_light_dt(UNK_FISH_STRUCT* r30, GAME_PLAY* r31) 
{ 
    if (r30->unk_14db8 != -1) {
        mEnv_CancelReservedPointLight(r30->unk_14db8, r31);
    }

    if (r30->unk_14dba != -1) {
        mEnv_CancelReservedPointLight(r30->unk_14dba, r31);
    }
}
void mfish_point_light_mv() { }

void mfish_normal_light_set(UNK_FISH_STRUCT* r30, GAME_PLAY* r31) 
{ 
    LightsN* lights;

    // TODO: figure out where these are actually coming from
    xyz_t r5;
    r5.x = 320;
    r5.y = 0;
    r5.z = 240;

    lights = Global_light_read(&r31->global_light, r31->game.graph);
    LightsN_list_check(lights, r31->global_light.list, &r5);
    LightsN_disp(lights, r31->game.graph);
}
