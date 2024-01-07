#include "ac_npc_rtc.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "jaudio_NES/staff.h"
#include "m_msg.h"
#include "m_bgm.h"
#include "m_soncho.h"
#include "m_card.h"

extern void aNRTC_actor_ct(ACTOR*, GAME*);
extern void aNRTC_actor_dt(ACTOR*, GAME*);
extern void aNRTC_actor_init(ACTOR*, GAME*);
extern void aNRTC_actor_save(ACTOR*, GAME*);

ACTOR_PROFILE Npc_Rtc_Profile = {
    mAc_PROFILE_NPC_RTC,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_RTC,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPCRTC_ACTOR),
    aNRTC_actor_ct,
    aNRTC_actor_dt,
    aNRTC_actor_init,
    mActor_NONE_PROC1,
    aNRTC_actor_save,
};

extern void aNRTC_actor_move(ACTOR*, GAME*);
extern void aNRTC_actor_draw(ACTOR*, GAME*);

extern int aNRTC_talk_init(ACTOR*, GAME*); 
extern int aNRTC_talk_end_chk(ACTOR*, GAME*);

extern void aNRTC_schedule_proc(NPC_ACTOR*, GAME_PLAY*, int);

extern void aNRTC_talk_request(ACTOR* actor,GAME*);

extern void aNRTC_change_talk_proc(NPCRTC_ACTOR* rtc, int idx);

u8 aNRTC_sound_mode[] = {0x00,0x01,0x02,0x00};
u8 aNRTC_voice_mode[] = {0x00,0x01,0x02,0x00};  

void aNRTC_actor_ct(ACTOR* actor, GAME* game){
    static aNPC_ct_data_c ct_data = {
        &aNRTC_actor_move,
        &aNRTC_actor_draw,
        5,
        mActor_NONE_PROC1,
        &aNRTC_talk_init,
        &aNRTC_talk_end_chk,
        0
    };

    NPCRTC_ACTOR* rtc = (NPCRTC_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;
    PLAYER_ACTOR* player;
    xyz_t center;
    xyz_t eye;
    if(Common_Get(clip.npc_clip)->birth_check_proc(actor,game) == TRUE){
        rtc->npc_class.schedule.schedule_proc = aNRTC_schedule_proc;
        Common_Get(clip.npc_clip)->ct_proc(actor,game,&ct_data);
        actor->status_data.weight = MASSTYPE_IMMOVABLE;
        mPlib_request_main_demo_wait_type1(play,0,NULL); 
        player = GET_PLAYER_ACTOR(play); 
        if(player != NULL){
            player->actor_class.state_bitfield |= 0x80;
        }

        center.x = 100.0f;
        center.y = 60.0f;
        center.z = 60.0f;

        eye.x = 100.0f;
        eye.y = 130.0f;
        eye.z = 210.0f;
        
        Camera2_change_priority(play,0);
        Camera2_request_main_lock(play, &center, &eye, 40.0f, 0, 100.0f, 400.0f, 5);
        sAdo_SetOutMode(aNRTC_sound_mode[Save_Get(config.sound_mode)]);
        sAdo_SetVoiceMode(aNRTC_voice_mode[Save_Get(config.voice_mode)]);
        rtc->npc_class.condition_info.hide_request = 0;
        rtc->npc_class.talk_info.default_act = 9;
        rtc->npc_class.talk_info.melody_inst = 0;
        rtc->unk9A0 = 0;
    } 
}


void aNRTC_actor_save(ACTOR* actor, GAME* game) {
    Common_Get(clip.npc_clip)->save_proc(actor,game);
}

void aNRTC_actor_dt(ACTOR* actor, GAME* game) {
    Common_Get(clip.npc_clip)->dt_proc(actor,game);
}

void aNRTC_actor_init(ACTOR* actor, GAME* game) {
    Common_Get(clip.npc_clip)->init_proc(actor,game);
}

void aNRTC_actor_move(ACTOR* actor, GAME* game){ 
    StaffRoll info;
    f32 val = 0.5f;
    u8 arm_flag = TRUE;
    NPCRTC_ACTOR* rtc = (NPCRTC_ACTOR*)actor;
    GAME_PLAY* play = (GAME_PLAY*)game;

 
    if(rtc->npc_class.draw.animation_id == 0x76){
        sAdos_GetStaffRollInfo(&info);
        if(info.unk0 != 4){
            val = 0.0f;
            arm_flag = FALSE;
            rtc->npc_class.draw.main_animation.keyframe.frame_control.current_frame = 1.0f + (64.0f * (f32)info.unk8); 
        }
    } 

    rtc->npc_class.draw.main_animation.keyframe.frame_control.speed = val;
    sAdos_TTKK_ARM(arm_flag);
    Common_Get(clip.npc_clip)->move_proc(actor,game);
    mSC_change_player_freeze(play);
}


void aNRTC_actor_draw(ACTOR* actor, GAME* game) {
    Common_Get(clip.npc_clip)->draw_proc(actor,game);
}

#include "../src/ac_npc_rtc_think.c.inc"

#include "../src/ac_npc_rtc_talk.c.inc"