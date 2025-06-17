
static void aNRTC_talk_request(ACTOR* actor, GAME*);

static void aNRTC_think_start(NPC_ACTOR* actor, GAME_PLAY* play) {
    NPC_RTC_ACTOR* rtc = (NPC_RTC_ACTOR*)actor;
    if (rtc->first_talk_timer > 0) {
        rtc->first_talk_timer--;
    } else {
        rtc->talk_flag = TRUE;
        rtc->npc_class.talk_info.talk_request_proc = &aNRTC_talk_request;
        rtc->npc_class.condition_info.demo_flg = aNPC_COND_DEMO_SKIP_HEAD_LOOKAT;
    }
}

static void aNRTC_think_title(NPC_ACTOR* actor, GAME_PLAY* play) {
    NPC_RTC_ACTOR* rtc = (NPC_RTC_ACTOR*)actor;

    play->fb_wipe_type = WIPE_TYPE_FADE_BLACK;
    play->fb_fade_type = FADE_TYPE_OUT_RETURN_TITLE;
    mPlib_request_main_invade_type1((GAME*)play);
    Actor_info_save_actor(play);
    rtc->think_idx = aNRTC_THINK_WAIT;
}

// clang-format off
static Door_data_c door_data = {
    SCENE_PLAYERSELECT,
    mSc_DIRECT_NORTH,
    FALSE,
    0,
    { 100, 0, 120 },
    EMPTY_NO,
    3,
    { 0, 0, 0 },
};
// clang-format on

static void aNRTC_think_door(NPC_ACTOR* actor, GAME_PLAY* play) {
    if (sAdo_BgmFadeoutCheck() != 0) {
        goto_other_scene(play, &door_data, 1);
        Common_Set(transition.wipe_type, WIPE_TYPE_FADE_BLACK);
    }
}

static void aNRTC_think_check(NPC_ACTOR* actor, GAME_PLAY* play) {
    NPC_RTC_ACTOR* rtc = (NPC_RTC_ACTOR*)actor;
    if (sAdo_BgmFadeoutCheck() != 0) {
        goto_other_scene(play, &door_data, 1);
        mCD_ReCheckLoadLand(play);
        Common_Set(transition.wipe_type, WIPE_TYPE_FADE_BLACK);
        rtc->think_idx = aNRTC_THINK_WAIT;
    }
}

static void aNRTC_think_ipmenu(NPC_ACTOR* actor, GAME_PLAY* play) {
    NPC_RTC_ACTOR* rtc = (NPC_RTC_ACTOR*)actor;
    if (sAdo_BgmFadeoutCheck() != 0) {
        HotResetIplMenu();
        rtc->think_idx = aNRTC_THINK_WAIT;
    }
}

// clang-format off
static aNPC_SUB_PROC aNRTC_proc_table[] = {
    &aNRTC_think_start,
    &aNRTC_think_title,
    &aNRTC_think_door,
    &aNRTC_think_check,
    &aNRTC_think_ipmenu,
    (aNPC_SUB_PROC)mActor_NONE_PROC1,
};
// clang-format on

static void aNRTC_think_main_proc(NPC_ACTOR* actor, GAME_PLAY* play) {
    NPC_RTC_ACTOR* rtc = (NPC_RTC_ACTOR*)actor;
    if (rtc->fade_timer > 0) {
        rtc->fade_timer--;
        if (rtc->fade_timer == 0) {
            play->fade_color_value.c.a = -1;
        } else if (rtc->fade_timer < 25) {
            play->fade_color_value.c.a = 255.0f * (1.0f - (0.04f * rtc->fade_timer));
        }
    } else if (rtc->talk_flag == 0) {
        aNRTC_proc_table[rtc->think_idx](actor, play);
    }

    if (rtc->bgm_timer == 0) {
        if (rtc->think_idx == 1) {
            mBGMPsComp_make_ps_wipe(0x21C2);
        } else {
            mBGMPsComp_make_ps_wipe(0x621C);
        }
        rtc->bgm_timer = -2;
    } else if (rtc->bgm_timer > 0) {
        rtc->bgm_timer--;
    }
}

static void aNRTC_think_init_proc(NPC_ACTOR* actor, GAME_PLAY* play) {
    NPC_RTC_ACTOR* rtc = (NPC_RTC_ACTOR*)actor;
    rtc->npc_class.request.act_priority = 4;
    rtc->npc_class.request.act_idx = 8;
    rtc->npc_class.request.act_type = 0;
}

static void aNRTC_think_proc(NPC_ACTOR* actor, GAME_PLAY* play, int idx) {
    static aNPC_SUB_PROC think_proc[] = {
        &aNRTC_think_init_proc,
        &aNRTC_think_main_proc,
    };

    think_proc[idx](actor, play);
}

static void aNRTC_schedule_init_proc(NPC_ACTOR* actor, GAME_PLAY* play) {
    NPC_RTC_ACTOR* rtc = (NPC_RTC_ACTOR*)actor;
    rtc->npc_class.draw.anim_speed_type = aNPC_ANIM_SPEED_TYPE_FREE;
    rtc->npc_class.talk_info.default_animation = aNPC_ANIM_4HAKU_E1;
    rtc->bgm_timer = -1;
    rtc->fade_timer = 0;
    rtc->first_talk_timer = 90;
    rtc->npc_class.think.think_proc = aNRTC_think_proc;
    rtc->think_idx = 0;
    Common_Get(clip.npc_clip)->think_proc(actor, play, aNPC_THINK_IN_BLOCK, 0);
}

static void aNRTC_schedule_main_proc(NPC_ACTOR* actor, GAME_PLAY* play) {
    NPC_RTC_ACTOR* rtc = (NPC_RTC_ACTOR*)actor;
    if (Common_Get(clip.npc_clip)->think_proc(actor, play, -1, 1) == 0) {
        Common_Get(clip.npc_clip)->think_proc(actor, play, -1, 2);
    }
}

static void aNRTC_schedule_proc(NPC_ACTOR* actor, GAME_PLAY* play, int idx) {
    static aNPC_SUB_PROC sche_proc[] = {
        &aNRTC_schedule_init_proc,
        &aNRTC_schedule_main_proc,
    };

    sche_proc[idx](actor, play);
}
