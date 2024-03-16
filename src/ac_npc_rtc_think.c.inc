
static void aNRTC_talk_request(ACTOR* actor, GAME*);

static void aNRTC_think_start(NPC_ACTOR* actor, GAME_PLAY* play) {
    NPCRTC_ACTOR* rtc = (NPCRTC_ACTOR*)actor;
    if (rtc->unk9B8 > 0) {
        rtc->unk9B8--;
    } else {
        rtc->unk9A0 = 1;
        rtc->npc_class.talk_info.talk_request_proc = aNRTC_talk_request;
        rtc->npc_class.condition_info.demo_flg = 0x100;
    }
}

static void aNRTC_think_title(NPC_ACTOR* actor, GAME_PLAY* play) {
    NPCRTC_ACTOR* rtc = (NPCRTC_ACTOR*)actor;

    play->fb_wipe_type = 3;
    play->fb_fade_type = 4;
    mPlib_request_main_invade_type1(play);
    Actor_info_save_actor(play);
    rtc->unk9A8 = 5;
}

Door_data_c door_data = { SCENE_PLAYERSELECT, 4, FALSE, 0, { 100, 0, 120 }, EMPTY_NO, 3, { 0, 0, 0 } };

static void aNRTC_think_door(NPC_ACTOR* actor, GAME_PLAY* play) {

    if (sAdo_BgmFadeoutCheck() != 0) {
        goto_other_scene(play, &door_data, 1);
        Common_Set(transition.wipe_type, 3);
    }
}

static void aNRTC_think_check(NPC_ACTOR* actor, GAME_PLAY* play) {
    NPCRTC_ACTOR* rtc = (NPCRTC_ACTOR*)actor;
    if (sAdo_BgmFadeoutCheck() != 0) {
        goto_other_scene(play, &door_data, 1);
        mCD_ReCheckLoadLand(play);
        Common_Set(transition.wipe_type, 3);
        rtc->unk9A8 = 5;
    }
}

static void aNRTC_think_ipmenu(NPC_ACTOR* actor, GAME_PLAY* play) {
    NPCRTC_ACTOR* rtc = (NPCRTC_ACTOR*)actor;
    if (sAdo_BgmFadeoutCheck() != 0) {
        HotResetIplMenu();
        rtc->unk9A8 = 5;
    }
}

aNPC_SUB_PROC aNRTC_proc_table[] = {
    aNRTC_think_start, aNRTC_think_title,  aNRTC_think_door,
    aNRTC_think_check, aNRTC_think_ipmenu, (aNPC_SUB_PROC)mActor_NONE_PROC1,
};

static void aNRTC_think_main_proc(NPC_ACTOR* actor, GAME_PLAY* play) {
    NPCRTC_ACTOR* rtc = (NPCRTC_ACTOR*)actor;
    if (rtc->unk9B0 > 0) {
        rtc->unk9B0--;
        if (rtc->unk9B0 == 0) {
            play->fade_color_value.c.a = -1;
        } else if (rtc->unk9B0 < 25) {
            play->fade_color_value.c.a = 255.0f * (1.0f - (0.04f * rtc->unk9B0));
        }
    } else if (rtc->unk9A0 == 0) {
        aNRTC_proc_table[rtc->unk9A8](actor, play);
    }
    if (rtc->unk9B4 == 0) {
        if (rtc->unk9A8 == 1) {
            mBGMPsComp_make_ps_wipe(0x21C2);
        } else {
            mBGMPsComp_make_ps_wipe(0x621C);
        }
        rtc->unk9B4 = -2;
    } else if (rtc->unk9B4 > 0) {
        rtc->unk9B4--;
    }
}

static void aNRTC_think_init_proc(NPC_ACTOR* actor, GAME_PLAY* play) {
    NPCRTC_ACTOR* rtc = (NPCRTC_ACTOR*)actor;
    rtc->npc_class.request.act_priority = 4;
    rtc->npc_class.request.act_idx = 8;
    rtc->npc_class.request.act_type = 0;
}

static void aNRTC_think_proc(NPC_ACTOR* actor, GAME_PLAY* play, int idx) {
    static aNPC_SUB_PROC think_proc[] = {
        aNRTC_think_init_proc,
        aNRTC_think_main_proc,
    };

    think_proc[idx](actor, play);
}

static void aNRTC_schedule_init_proc(NPC_ACTOR* actor, GAME_PLAY* play) {
    NPCRTC_ACTOR* rtc = (NPCRTC_ACTOR*)actor;
    rtc->npc_class.draw._5BE = 1;
    rtc->npc_class.talk_info.default_animation = 0x76;
    rtc->unk9B4 = -1;
    rtc->unk9B0 = 0;
    rtc->unk9B8 = 0x5A;
    rtc->npc_class.think.think_proc = aNRTC_think_proc;
    rtc->unk9A8 = 0;
    Common_Get(clip.npc_clip)->think_proc(actor, play, 6, 0);
}

static void aNRTC_schedule_main_proc(NPC_ACTOR* actor, GAME_PLAY* play) {
    NPCRTC_ACTOR* rtc = (NPCRTC_ACTOR*)actor;
    if (Common_Get(clip.npc_clip)->think_proc(actor, play, -1, 1) == 0) {
        Common_Get(clip.npc_clip)->think_proc(actor, play, -1, 2);
    }
}

static void aNRTC_schedule_proc(NPC_ACTOR* actor, GAME_PLAY* play, int idx) {
    static aNPC_SUB_PROC sche_proc[] = { aNRTC_schedule_init_proc, aNRTC_schedule_main_proc };

    sche_proc[idx](actor, play);
}
