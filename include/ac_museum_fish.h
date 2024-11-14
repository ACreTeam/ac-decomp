#ifndef AC_MUSEUM_FISH_H
#define AC_MUSEUM_FISH_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Museum_Fish_Profile;

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
} MUSEUM_FISH_ACTOR;

void Museum_Fish_Prv_data_init();
void Museum_Fish_Actor_ct(ACTOR* actor, GAME* game);
void Museum_Fish_Actor_dt(ACTOR* actor, GAME* game);
int Museum_Fish_GetMsgNo(ACTOR* r31);
void Museum_Fish_Check_Talk_Distance();
void Museum_Fish_Set_MsgFishInfo();
void Museum_Fish_set_talk_info();
void Museum_Fish_Talk_process();
void Museum_Fish_Actor_move(ACTOR* actor, GAME* game);
void Museum_Fish_Suisou_draw(ACTOR* actor, GAME* game);
void kusa_before_disp();
void Museum_Fish_Kusa_Draw(ACTOR* actor, GAME* game);
void Museum_Fish_Actor_draw(ACTOR* actor, GAME* game);
void mfish_cull_check();
void mfish_point_ligh_pos_get();
void mfish_point_light_ct(ACTOR* actor, GAME* game);
void mfish_point_light_dt(ACTOR* r30, GAME* r31);
void mfish_point_light_mv(ACTOR* actor, GAME* game);
void mfish_normal_light_set();

#ifdef __cplusplus
}
#endif

#endif
