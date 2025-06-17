#include "m_demo.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_choice.h"
#include "m_msg.h"
#include "m_bgm.h"
#include "m_event.h"
#include "_mem.h"

/* Z-X */
static f32 direct_vector[mDemo_DIRECT_NUM][2] = { { -1.0f, 0.0f },      { -F_SQRT2, F_SQRT2 }, { 0.0f, 1.0f },
                                                  { F_SQRT2, F_SQRT2 }, { 1.0f, 0.0f },        { F_SQRT2, -F_SQRT2 },
                                                  { 0.0f, -1.0f },      { -F_SQRT2, -F_SQRT2 } };

static s16 direct_back_angle[mDemo_DIRECT_NUM] = { 0x0000, 0xE000, 0xC000, 0xA000, 0x8000, 0x6000, 0x4000, 0x2000 };

static mDemo_Data_c demo_data;
static mDemo_Data_c* const demo = &demo_data;

static int mDemo_Check_talk_type() {
    int res = FALSE;

    switch (demo->current.type) {
        case mDemo_TYPE_TALK:
        case mDemo_TYPE_SPEAK:
        case mDemo_TYPE_REPORT:
        case mDemo_TYPE_SPEECH:
            res = TRUE;
            break;
    }

    return res;
}

extern ACTOR* mDemo_Get_talk_actor() {
    if (mDemo_Check_talk_type() == TRUE) {
        return demo->current.actor;
    }

    return NULL;
}

/* @unused @fabricated */
extern void mDemo_Set_speaker_actor(ACTOR* actor) {
    demo->current.actor = actor;
}

extern void mDemo_Set_OrderValue(int type, int idx, u16 value) {
    if (type >= 0 && type < mDemo_ORDER_NUM && idx >= 0 && idx < mDemo_ORDER_VALUE_MAX) {
        demo->order_data[type][idx] = value;
    }
}

extern u16 mDemo_Get_OrderValue(int type, int idx) {
    if (type >= 0 && type < mDemo_ORDER_NUM && idx >= 0 && idx < mDemo_ORDER_VALUE_MAX) {
        return demo->order_data[type][idx];
    }

    return 0;
}

static void mDemo_Init_OrderValue() {
    int i;
    int j;

    for (i = 0; i < mDemo_ORDER_NUM; i++) {
        for (j = 0; j < mDemo_ORDER_VALUE_MAX; j++) {
            demo->order_data[i][j] = 0;
        }
    }
}

extern void mDemo_Set_msg_num(int msg_num) {
    if (mDemo_Check_talk_type() == TRUE) {
        demo->data.talk.msg_no = msg_num;
    }
}

extern int mDemo_Get_Talk_Actors(ACTOR** speaker, ACTOR** listener) {
    if (mDemo_Check_talk_type() == TRUE) {

        speaker[0] = demo->speaker_actor;
        listener[0] = demo->listen_actor;
        return TRUE;
    } else {
        speaker[0] = NULL;
        listener[0] = NULL;
        return FALSE;
    }
}

extern void mDemo_Set_change_player_destiny(s8 destiny) {
    demo->change_player_destiny = destiny;
}

static int mDemo_Get_change_player_destiny() {
    return demo->change_player_destiny;
}

static void mDemo_Clear_change_player_destiny() {
    mDemo_Set_change_player_destiny(-1);
}

static void mDemo_Copy_change_player_destiny() {
    if (mDemo_Get_change_player_destiny() >= 0) {
        Private_c* priv = Common_Get(now_private);
        lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

        priv->destiny.received_time.sec = rtc_time->sec;
        priv->destiny.received_time.min = rtc_time->min;
        priv->destiny.received_time.hour = rtc_time->hour;
        priv->destiny.received_time.day = rtc_time->day;
        priv->destiny.received_time.weekday = rtc_time->weekday;
        priv->destiny.received_time.month = rtc_time->month;
        priv->destiny.received_time.year = rtc_time->year;
        priv->destiny.type = mDemo_Get_change_player_destiny();
        mDemo_Clear_change_player_destiny();
    }
}

extern void mDemo_Set_use_zoom_sound(u8 use_zoom_sound) {
    if (mDemo_Check_talk_type() == TRUE) {
        demo->data.talk.use_zoom_sound = use_zoom_sound;
    }
}

extern int mDemo_Get_use_zoom_sound() {
    if (mDemo_Check_talk_type() == TRUE) {
        return demo->data.talk.use_zoom_sound;
    }

    return FALSE;
}

extern void mDemo_Set_talk_display_name(s8 display_name) {
    if (mDemo_Check_talk_type() == TRUE) {
        demo->data.talk.display_name = display_name;
    }
}

/* @unused @fabricated */
extern int mDemo_Get_talk_display_name() {
    if (mDemo_Check_talk_type() == TRUE) {
        return demo->data.talk.display_name;
    }

    return FALSE;
}

extern void mDemo_Set_talk_change_player(u8 change_player) {
    if (mDemo_Check_talk_type() == TRUE) {
        demo->data.talk.change_player = change_player;
    }
}

/* @unused @fabricated */
extern int mDemo_Get_talk_change_player() {
    if (mDemo_Check_talk_type() == TRUE) {
        return demo->data.talk.change_player;
    }

    return FALSE;
}

extern void mDemo_Set_talk_return_demo_wait(u8 return_demo_wait) {
    if (mDemo_Check_talk_type() == TRUE) {
        demo->data.talk.return_demo_wait = return_demo_wait;
    }
}

/* @unused @fabricated */
extern int mDemo_Get_talk_return_demo_wait() {
    if (mDemo_Check_talk_type() == TRUE) {
        return demo->data.talk.return_demo_wait;
    }

    return FALSE;
}

extern void mDemo_Set_talk_return_get_golden_axe_demo(u8 return_get_golden_axe_demo) {
    if (mDemo_Check_talk_type() == TRUE) {
        demo->data.talk.return_get_golden_axe_demo = return_get_golden_axe_demo;
    }
}

/* @unused @fabricated */
extern int mDemo_Get_talk_return_get_golden_axe_demo() {
    if (mDemo_Check_talk_type() == TRUE) {
        return demo->data.talk.return_get_golden_axe_demo;
    }

    return FALSE;
}

extern void mDemo_Set_talk_turn(u8 turn) {
    if (mDemo_Check_talk_type() == TRUE) {
        demo->data.talk.turn = turn;
    }
}

extern int mDemo_Get_talk_turn() {
    if (mDemo_Check_talk_type() == TRUE) {
        return demo->data.talk.turn;
    }

    return FALSE;
}

extern void mDemo_Set_talk_window_color(rgba_t* window_color) {
    switch (demo->current.type) {
        case mDemo_TYPE_TALK:
        case mDemo_TYPE_SPEAK:
        case mDemo_TYPE_REPORT:
        case mDemo_TYPE_SPEECH:
            demo->data.talk.window_color = *window_color;
            break;

        case mDemo_TYPE_EVENTMSG:
        case mDemo_TYPE_EVENTMSG2:
            demo->data.emsg.window_color = *window_color;
            break;
    }
}

/* @unused @fabricated */
extern rgba_t* mDemo_Get_talk_window_color_p() {
    if (demo->current.type >= mDemo_TYPE_TALK && demo->current.type < mDemo_TYPE_OUTDOOR) {
        return &demo->data.talk.window_color;
    } else if (demo->current.type >= mDemo_TYPE_EVENTMSG && demo->current.type < mDemo_TYPE_15) {
        return &demo->data.emsg.window_color;
    }

    return NULL;
}

extern void mDemo_Set_camera(u8 camera_type) {
    demo->camera_type = camera_type;
}

extern int mDemo_Get_camera() {
    return demo->camera_type;
}

extern int mDemo_CheckDemoType() {
    if (mDemo_CheckDemo()) {
        return demo->current.type;
    }

    return mDemo_TYPE_NONE;
}

static int change_camera(int camera_type) {
    GAME_PLAY* play;
    PLAYER_ACTOR* player;

    player = GET_PLAYER_ACTOR_NOW();
    play = (GAME_PLAY*)gamePT;

    if (camera_type == play->camera.now_main_index) {
        return FALSE;
    }

    switch (camera_type) {
        case CAMERA2_PROCESS_TALK:
            Camera2_request_main_talk(play, (ACTOR*)player, demo->current.actor, mDemo_CAMERA_PRIORITY);
            break;
        case CAMERA2_PROCESS_ITEM:
            Camera2_request_main_item(play, 0, mDemo_CAMERA_PRIORITY);
            break;
        case CAMERA2_PROCESS_DOOR:
            Camera2_request_main_door(play, (ACTOR*)player, demo->current.type != mDemo_TYPE_OUTDOOR,
                                      mDemo_CAMERA_PRIORITY);
            break;
        case CAMERA2_PROCESS_LOCK: {
            s_xyz angle;
            f32 dist;
            int sh_bx;
            int sh_bz;
            xyz_t camera_wpos;

            switch (demo->current.type) {
                case mDemo_TYPE_EVENTMSG: {
                    Camera2_main_Simple_AngleDistStd(play, &angle, &dist);
                    Camera2_request_main_simple((GAME_PLAY*)gamePT, &player->actor_class.world.position, &angle, dist,
                                                0, mDemo_CAMERA_PRIORITY);
                    break;
                }

                case mDemo_TYPE_SPEECH:
                case mDemo_TYPE_EVENTMSG2: {
                    Camera2_main_Simple_AngleDistStd(play, &angle, &dist);
                    mFI_BlockKind2BkNum(&sh_bx, &sh_bz, mRF_BLOCKKIND_SHRINE);
                    mFI_BkNum2WposXZ(&camera_wpos.x, &camera_wpos.z, sh_bx, sh_bz);
                    camera_wpos.x += 320.0f;
                    camera_wpos.y = player->actor_class.world.position.y;
                    camera_wpos.z += 400.0f;
                    Camera2_request_main_simple((GAME_PLAY*)gamePT, &camera_wpos, &angle, dist, 0,
                                                mDemo_CAMERA_PRIORITY);
                    break;
                }
            }

            break;
        }
        case CAMERA2_PROCESS_CUST_TALK: {
            switch (demo->current.actor->id) {
                case mAc_PROFILE_EV_YOMISE:
                    Camera2_request_main_listen_front_low_talk(play, (ACTOR*)player, demo->current.actor,
                                                               mDemo_CAMERA_PRIORITY);
                    break;
            }

            break;
        }
        case CAMERA2_PROCESS_SIMPLE: {
            switch (demo->current.actor->id) {
                case mAc_PROFILE_EV_DESIGNER:
                    Camera2_request_main_simple_kirin(play, &demo->current.actor->world.position,
                                                      mDemo_CAMERA_PRIORITY - 1);
                    break;
            }

            break;
        }
        case CAMERA2_PROCESS_NORMAL:
            Camera2_request_main_normal(play, 0, mDemo_CAMERA_PRIORITY - 1);
            break;
        case CAMERA2_PROCESS_INTER2: {
            xyz_t center;
            xyz_t eye;

            center = play->camera.lookat.center;
            center.x -= 80.0f;

            eye = play->camera.lookat.eye;
            eye.x -= 80.0f;
            eye.z -= 20.0f;

            Camera2_request_main_inter(play, &center, &eye, &center, &eye, 0.6f, 0.3f, TRUE, 14,
                                       mDemo_CAMERA_PRIORITY + 1);
            play->camera.requested_main_index = CAMERA2_PROCESS_INTER2;
            break;
        }
        case CAMERA2_PROCESS_NUM:
            break;
    }

    return TRUE;
}

static int set_speak_default() {
    PLAYER_ACTOR* player;

    demo->data.talk.msg_no = 0;
    demo->data.talk.turn = FALSE;
    demo->data.talk.display_name = TRUE;
    demo->data.talk.change_player = TRUE;
    demo->data.talk.return_demo_wait = FALSE;
    demo->data.talk.return_get_golden_axe_demo = FALSE;
    demo->data.talk.use_zoom_sound = TRUE;
    demo->data.talk.window_color.r = mDemo_WINDOW_COLOR_R;
    demo->data.talk.window_color.g = mDemo_WINDOW_COLOR_G;
    demo->data.talk.window_color.b = mDemo_WINDOW_COLOR_B;
    demo->data.talk.window_color.a = mDemo_WINDOW_COLOR_A;
    demo->camera_type = CAMERA2_PROCESS_TALK;
    mDemo_Unset_SpeakerAble();
    mDemo_Unset_ListenAble();

    player = GET_PLAYER_ACTOR_NOW();
    demo->speaker_actor = (ACTOR*)player;
    demo->listen_actor = demo->current.actor;
    return TRUE;
}

static int set_report_default() {
    PLAYER_ACTOR* player;

    demo->data.talk.msg_no = 0;
    demo->data.talk.turn = FALSE;
    demo->data.talk.display_name = FALSE;
    demo->data.talk.change_player = FALSE;
    demo->data.talk.return_demo_wait = FALSE;
    demo->data.talk.return_get_golden_axe_demo = FALSE;
    demo->data.talk.use_zoom_sound = TRUE;
    demo->data.talk.window_color.r = mDemo_WINDOW_COLOR_R;
    demo->data.talk.window_color.g = mDemo_WINDOW_COLOR_G;
    demo->data.talk.window_color.b = mDemo_WINDOW_COLOR_B;
    demo->data.talk.window_color.a = mDemo_WINDOW_COLOR_A;
    demo->camera_type = CAMERA2_PROCESS_NORMAL;
    mDemo_Set_SpeakerAble();
    mDemo_Unset_ListenAble();
    player = GET_PLAYER_ACTOR_NOW();
    demo->speaker_actor = (ACTOR*)player;
    demo->listen_actor = demo->current.actor;
    return TRUE;
}

static int set_talk_default() {
    demo->data.talk.msg_no = 0;
    demo->data.talk.turn = TRUE;
    demo->data.talk.display_name = TRUE;
    demo->data.talk.change_player = TRUE;
    demo->data.talk.return_demo_wait = FALSE;
    demo->data.talk.return_get_golden_axe_demo = FALSE;
    demo->data.talk.use_zoom_sound = TRUE;
    demo->data.talk.window_color.r = mDemo_WINDOW_COLOR_R;
    demo->data.talk.window_color.g = mDemo_WINDOW_COLOR_G;
    demo->data.talk.window_color.b = mDemo_WINDOW_COLOR_B;
    demo->data.talk.window_color.a = mDemo_WINDOW_COLOR_A;
    demo->camera_type = CAMERA2_PROCESS_TALK;
    mDemo_Unset_SpeakerAble();
    mDemo_Unset_ListenAble();
    demo->speaker_actor = (ACTOR*)GET_PLAYER_ACTOR_NOW();
    demo->listen_actor = demo->current.actor;
    return TRUE;
}

static int wait_talk_start() {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR_NOW();

    if (demo->data.talk.change_player) {
        if (mPlib_get_player_actor_main_index(gamePT) != 65 &&
            mPlib_request_main_talk_type1(gamePT, demo->current.actor, demo->data.talk.turn, FALSE) == FALSE) {
            return FALSE;
        }
    } else {
        mDemo_Set_SpeakerAble();
    }

    if (mDemo_Check_SpeakerAble() && mDemo_Check_ListenAble()) {
        mMsg_Window_c* msg_win = mMsg_Get_base_window_p();

        mDemo_Init_OrderValue();

        if (mMsg_Check_main_index(msg_win, mMsg_INDEX_APPEAR) == FALSE) {
            int msg_no = demo->data.talk.msg_no; // pulled out here, probably for debug or something?

            player->actor_class.state_bitfield |= ACTOR_STATE_IN_DEMO;
            demo->current.actor->state_bitfield |= ACTOR_STATE_IN_DEMO;
            demo->data.talk.actor_saved_weight = demo->current.actor->status_data.weight;
            demo->current.actor->status_data.weight = 255;
            mMsg_request_main_appear(msg_win, demo->current.actor, demo->data.talk.display_name,
                                     &demo->data.talk.window_color, msg_no, mDemo_MSG_PRIORITY);

            if (demo->data.talk.use_zoom_sound) {
                sAdo_SysTrgStart(demo->camera_type == CAMERA2_PROCESS_TALK ? (u16)0x8014 : (u16)0x8004);
            }

            if (mFI_GET_TYPE(mFI_GetFieldId()) != mFI_FIELD_DEMO_STARTDEMO &&
                demo->data.talk.msg_no != 0x07DD && /* Porter "Now arriving at <TOWN NAME>!" message (new player) */
                demo->data.talk.msg_no != 0x0949 && /* Porter "Now arriving in <TOWN NAME>!" message (returning home) */
                demo->data.talk.msg_no != 0x0965 && /* Porter "Take care!" message (travelling to another town) */
                demo->data.talk.msg_no != 0x07DE    /* Tom Nook "Hey, you there!" message (walking down from station) */
            ) {
                mBGMPsComp_volume_talk_start();
            }

            return TRUE;
        }
    }

    return FALSE;
}

static int wait_talk_end() {
    if (mMsg_Check_main_hide(mMsg_Get_base_window_p()) || demo->state == mDemo_STATE_STOP) {
        if (demo->data.talk.change_player) {
            mPlib_request_main_talk_end_type1(gamePT, demo->data.talk.return_demo_wait,
                                              demo->data.talk.return_get_golden_axe_demo);
        }

        demo->current.actor->status_data.weight = demo->data.talk.actor_saved_weight;
        mDemo_Copy_change_player_destiny();

        if (mFI_GET_TYPE(mFI_GetFieldId()) != mFI_FIELD_DEMO_STARTDEMO) {
            mBGMPsComp_volume_talk_end();
        }

        return TRUE;
    }

    return FALSE;
}

static int set_speech_default() {
    demo->data.talk.msg_no = 0;
    demo->data.talk.turn = FALSE;
    demo->data.talk.display_name = TRUE;
    demo->data.talk.change_player = FALSE;
    demo->data.talk.return_demo_wait = FALSE;
    demo->data.talk.return_get_golden_axe_demo = FALSE;
    demo->data.talk.use_zoom_sound = TRUE;
    demo->data.talk.window_color.r = mDemo_WINDOW_COLOR_R;
    demo->data.talk.window_color.g = mDemo_WINDOW_COLOR_G;
    demo->data.talk.window_color.b = mDemo_WINDOW_COLOR_B;
    demo->data.talk.window_color.a = mDemo_WINDOW_COLOR_A;
    demo->camera_type = CAMERA2_PROCESS_INTER2;
    mDemo_Set_SpeakerAble();
    mDemo_Unset_ListenAble();
    demo->speaker_actor = (ACTOR*)GET_PLAYER_ACTOR_NOW();
    demo->listen_actor = demo->current.actor;
    return TRUE;
}

static int wait_scroll_start() {
    return TRUE;
}

static int set_door_default() {
    demo->data.door.type = 0;
    demo->data.door.house_info.size = 80.0f;
    demo->data.door.house_info.direct = mDemo_DIRECT_S;
    demo->camera_type = CAMERA2_PROCESS_NORMAL;
    return TRUE;
}

static int wait_door_start() {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR_NOW();
    ACTOR* door_actor = (ACTOR*)(*GET_PLAYER_ACTOR_NOW()->get_door_label_proc)(gamePT);

    if (demo->current.actor == door_actor) {
        return TRUE;
    } else {
        f32 size_adj = demo->data.door.house_info.size / 2.0f + 20.0f;
        xyz_t pos;
        s16 back_angle;

        pos.x = demo->current.actor->world.position.x + size_adj * direct_vector[demo->data.door.house_info.direct][1];
        pos.y = demo->current.actor->world.position.y;
        pos.z = demo->current.actor->world.position.z + size_adj * direct_vector[demo->data.door.house_info.direct][0];

        back_angle = direct_back_angle[demo->data.door.house_info.direct];
        player->actor_class.state_bitfield |= ACTOR_STATE_IN_DEMO;
        demo->current.actor->state_bitfield |= ACTOR_STATE_IN_DEMO;

        mPlib_request_main_door_type1(gamePT, &pos, back_angle, demo->data.door.type, demo->current.actor);
        mPlib_strength_request_main_door_priority(gamePT);
    }

    return FALSE;
}

extern int mDemo_Set_house_info(f32 size, int direct) {
    if (demo->current.type == mDemo_TYPE_DOOR || demo->current.type == mDemo_TYPE_DOOR2) {
        demo->data.door.house_info.size = size;
        demo->data.door.house_info.direct = direct;
        return TRUE;
    }

    return FALSE;
}

static int wait_door2_start() {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR_NOW();
    ACTOR* door_actor = (ACTOR*)(*GET_PLAYER_ACTOR_NOW()->get_door_label_proc)(gamePT);

    if (demo->current.actor == door_actor) {
        return TRUE;
    } else {
        f32 size_adj = demo->data.door.house_info.size / 2.0f + 20.0f;
        xyz_t pos;
        s16 back_angle;

        pos.x = demo->current.actor->world.position.x + size_adj * direct_vector[demo->data.door.house_info.direct][1];
        pos.y = demo->current.actor->world.position.y;
        pos.z = demo->current.actor->world.position.z + size_adj * direct_vector[demo->data.door.house_info.direct][0];

        back_angle = direct_back_angle[demo->data.door.house_info.direct];
        player->actor_class.state_bitfield |= ACTOR_STATE_IN_DEMO;
        demo->current.actor->state_bitfield |= ACTOR_STATE_IN_DEMO;

        mPlib_request_main_door_type2(gamePT, &pos, back_angle, demo->data.door.type, demo->current.actor);
        mPlib_strength_request_main_door_priority(gamePT);
    }

    return FALSE;
}

static s16 get_title_no_for_event(s16 event) {
    switch (event) {
        case mEv_EVENT_FIREWORKS_SHOW:
            return 0;
        case mEv_EVENT_CHERRY_BLOSSOM_FESTIVAL:
            return 1;
        case mEv_EVENT_SPORTS_FAIR_AEROBICS:
            return 2;
        case mEv_EVENT_SPORTS_FAIR_FOOT_RACE:
            return 3;
        case mEv_EVENT_SPORTS_FAIR_BALL_TOSS:
            return 4;
        case mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR:
            return 5;
        case mEv_EVENT_MORNING_AEROBICS:
            return 6;
        case mEv_EVENT_HARVEST_MOON_FESTIVAL:
            return 7;
        case mEv_EVENT_METEOR_SHOWER:
            return 8;
        case mEv_EVENT_NEW_YEARS_EVE_COUNTDOWN:
            return 9;
        case mEv_EVENT_NEW_YEARS_DAY:
            return 10;
        case mEv_EVENT_FISHING_TOURNEY_1:
        case mEv_EVENT_FISHING_TOURNEY_2:
            return 11;
        case mEv_EVENT_HALLOWEEN:
            return 12;
        case mEv_EVENT_TOY_DAY_JINGLE:
            return 13;
        case mEv_EVENT_SPORTS_FAIR:
            return 10;
        case mEv_EVENT_GROUNDHOG_DAY:
            return 14;
        case mEv_EVENT_HARVEST_FESTIVAL:
            return 15;
        default:
            return -1;
    }
}

static int set_emsg_default() {
    s16 event_id = Common_Get(event_id);
    s16 flags = Common_Get(event_title_flags);
    s16 title_no;

    memcpy(&demo->data.emsg.door_data, Common_GetPointer(event_door_data), sizeof(Door_data_c));
    title_no = get_title_no_for_event(event_id);

    if (title_no >= 0) {
        if (flags == 1) {
            demo->data.emsg.msg_no = 0x1743; // start message
        } else {
            demo->data.emsg.msg_no = 0x1799; // conclusion message
        }

        demo->data.emsg.msg_no += title_no;
    } else {
        demo->data.emsg.msg_no = 0;
    }

    demo->data.emsg.window_color.r = mDemo_WINDOW_COLOR_R;
    demo->data.emsg.window_color.g = mDemo_WINDOW_COLOR_G;
    demo->data.emsg.window_color.b = mDemo_WINDOW_COLOR_B;
    demo->data.emsg.window_color.a = mDemo_WINDOW_COLOR_A;
    demo->camera_type = CAMERA2_PROCESS_LOCK;
    demo->data.emsg.msg_delay_timer = 0;
    demo->data.emsg.scene_delay_timer = 30;

    return TRUE;
}

static int wait_emsg_start() {
    mMsg_Window_c* msg_win = mMsg_Get_base_window_p();

    if (demo->data.emsg.msg_delay_timer <= 0) {
        if (demo->data.emsg.msg_no != 0) {
            mMsg_request_main_appear(msg_win, NULL, FALSE, &demo->data.emsg.window_color, demo->data.emsg.msg_no,
                                     mDemo_MSG_PRIORITY);
        }

        Common_Set(event_title_flags, 2);
        return TRUE;
    } else {
        demo->data.emsg.msg_delay_timer--;
    }

    return FALSE;
}

static int wait_emsg_end() {
    GAME_PLAY* play = (GAME_PLAY*)gamePT;
    mMsg_Window_c* msg_win = mMsg_Get_base_window_p();

    if (mMsg_Check_main_hide(msg_win)) {
        demo->data.emsg.scene_delay_timer--;
    }

    if (demo->data.emsg.scene_delay_timer <= 0 || demo->state == mDemo_STATE_STOP) {
        if (goto_other_scene(play, &demo->data.emsg.door_data, FALSE)) {
            play->fb_wipe_type = demo->data.emsg.door_data.wipe_type;
            play->fb_fade_type = FADE_TYPE_EVENT;
            Common_Set(transition.wipe_type, demo->data.emsg.door_data.wipe_type);
            mBGMForce_inform_end();

            return TRUE;
        } else {
            return FALSE;
        }
    }

    return FALSE;
}

static int set_emsg2_default() {
    memcpy(&demo->data.emsg.door_data, Common_GetPointer(event_door_data), sizeof(Door_data_c));
    demo->camera_type = CAMERA2_PROCESS_LOCK;
    demo->data.emsg.msg_delay_timer = 0;
    demo->data.emsg.scene_delay_timer = 30;
    memcpy(&demo->request_save, &demo->current, sizeof(mDemo_Request_c));

    return TRUE;
}

static int wait_emsg2_start() {
    Common_Set(event_title_flags, 2);
    return TRUE;
}

static int wait_emsg2_end() {
    int res = FALSE;

    if (Common_Get(event_title_fade_in_progress) == TRUE) {
        GAME_PLAY* play = (GAME_PLAY*)gamePT;

        if (goto_other_scene(play, Common_GetPointer(event_door_data), FALSE)) {
            play->fb_wipe_type = Common_Get(event_door_data).wipe_type;
            play->fb_fade_type = FADE_TYPE_EVENT;
            Common_Set(transition.wipe_type, Common_Get(event_door_data).wipe_type);
            mBGMForce_inform_end();
            memset(&demo->request_save, 0, sizeof(mDemo_Request_c));

            res = TRUE;
        }
    }

    return res;
}

static f32 weight_of_talk_position(ACTOR* actor) {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR_NOW();
    f32 actor_talk_dist;
    f32 player_dist;
    f32 dist_y = player->actor_class.world.position.y - actor->world.position.y;
    s16 diff_y = player->actor_class.shape_info.rotation.y - actor->player_angle_y;
    s16 angle_y;

    if (dist_y < 0.0f) {
        dist_y = -dist_y;
    }

    angle_y = diff_y < 0 ? (s16)(diff_y + -0x8000) : (s16)(-diff_y + -0x8000);

    if (actor->player_distance_xz <= actor->talk_distance && dist_y <= 33.0f && angle_y <= 12530) {
        f32 dist_factor = 1.0f - (actor->player_distance_xz / 55.0f);
        f32 angle_factor;

        dist_y = 1.0f - (actor->player_distance_xz / 55.0f);

        if (dist_y < 0.0f) {
            dist_y = 0.0f;
        }

        angle_factor = 1.0f - ((f32)((int)angle_y) / 12530.0f);

        return angle_factor * angle_factor * 0.6f + dist_y * dist_y * 0.4f;
    } else {
        return -99.0f;
    }
}

static int allways_true() {
    return TRUE;
}

static int allways_false() {
    return FALSE;
}

static int scroll_check() {
    return mPlib_check_request_main_wade_priority(gamePT);
}

static int scroll2_check() {
    return mPlib_check_request_main_demo_wade_priority(gamePT);
}

static int scroll3_check() {
    return mPlib_check_request_main_demo_geton_boat_wade_priority(gamePT);
}

static int door_check() {
    return mPlib_check_request_main_door_type1_priority(gamePT);
}

static int door2_check() {
    return mPlib_check_request_main_door_type2_priority(gamePT);
}

static int outdoor_check() {
    return mPlib_check_request_main_outdoor_priority(gamePT);
}

static int talk_check() {
    return mPlib_check_request_main_talk_type1_priority(gamePT) != 0;
}

static int speak_check() {
    return mPlib_check_request_main_speak_type1_priority(gamePT) != 0;
}

typedef int (*mDemo_PROC)();

static int choice_demo_sub() {
    static const mDemo_PROC check_func[mDemo_TYPE_NUM] = { &allways_true, &scroll_check,  &allways_true, &door_check,
                                                           &allways_true, &scroll2_check, &door2_check,  &talk_check,
                                                           &speak_check,  &allways_true,  &allways_true, &outdoor_check,
                                                           &allways_true, &allways_true,  &allways_true, &allways_true,
                                                           &scroll3_check };

    f32 max_talk_weight = 0.0f;
    int i;
    int idx = -1;

    for (i = 0; i < demo->request_num; i++) {
        mDemo_Request_c* request = &demo->request[i];
        int type = request->type;

        if (((mEv_CheckTitleDemo() == 0 || type == mDemo_TYPE_SCROLL ||
              (mEv_CheckTitleDemo() == -9 && type == mDemo_TYPE_SPEAK && request->actor != NULL &&
               request->actor->id == mAc_PROFILE_NPC_TOTAKEKE)) &&
             (demo->request_save.type != mDemo_TYPE_NONE || type >= demo->priority_type)) &&
            (*check_func[type])() != FALSE) {
            if (type == mDemo_TYPE_TALK) {
                if (chkTrigger(BUTTON_A) && request->talk_weight > max_talk_weight) {
                    idx = i;
                    max_talk_weight = request->talk_weight;
                }
            } else {
                idx = i; /* non-TALK types have instant priority */
                break;
            }
        }
    }

    return idx;
}

static int choice_demo() {
    static const mDemo_PROC default_set_func[mDemo_TYPE_NUM] = {
        &allways_true,       &allways_true,     &allways_true,     &set_door_default,  &allways_true,
        &allways_true,       &set_door_default, &set_talk_default, &set_speak_default, &set_report_default,
        &set_speech_default, &allways_true,     &allways_true,     &set_emsg_default,  &set_emsg2_default,
        &allways_true,       &allways_true
    };

    int request_idx = choice_demo_sub();

    if (request_idx != -1) {
        memcpy(&demo->current, &demo->request[request_idx], sizeof(mDemo_Request_c));
        (*default_set_func[demo->current.type])();

        if (demo->current.proc != NULL) {
            (*demo->current.proc)(demo->current.actor);
        }

        demo->state = 1;
    }

    return request_idx;
}

static int check_speech_request() {
    int request_idx = choice_demo_sub();
    int res = FALSE;

    if (request_idx != -1) {
        mDemo_Request_c* request = &demo->request[request_idx];

        if (request->type == mDemo_TYPE_SPEECH) {
            res = TRUE;
        }
    }

    return res;
}

static void emsg_set() {
    static rgba_t win_color = { 175, 255, 255, 255 };

    mDemo_Set_talk_window_color(&win_color);
}

static void init_demo() {
    int initial_demo_type = Common_Get(start_demo_request).type;

    memset(&demo->current, 0, sizeof(mDemo_Request_c));
    memset(&demo->request_save, 0, sizeof(mDemo_Request_c));
    demo->state = mDemo_STATE_WAIT;
    demo->request_num = 0;
    demo->priority_type = 0;
    demo->camera_type = CAMERA2_PROCESS_NORMAL;
    demo->keep_camera_type = CAMERA2_PROCESS_STOP;

    switch (initial_demo_type) {
        case mDemo_TYPE_EVENTMSG:
        case mDemo_TYPE_EVENTMSG2:
            mDemo_Request(initial_demo_type, NULL, &emsg_set);
            Common_Set(start_demo_request.type, mDemo_TYPE_NONE);
            break;
    }
}

static const mDemo_PROC wait_start[mDemo_TYPE_NUM] = {
    &allways_true,     &wait_scroll_start, &allways_true,     &wait_door_start, &allways_true,     &wait_scroll_start,
    &wait_door2_start, &wait_talk_start,   &wait_talk_start,  &wait_talk_start, &wait_talk_start,  &allways_true,
    &allways_true,     &wait_emsg_start,   &wait_emsg2_start, &allways_true,    &wait_scroll_start
};

static const mDemo_PROC wait_end[mDemo_TYPE_NUM] = { &allways_false, &allways_false, &allways_false,  &allways_false,
                                                     &allways_false, &allways_false, &allways_false,  &wait_talk_end,
                                                     &wait_talk_end, &wait_talk_end, &wait_talk_end,  &allways_false,
                                                     &allways_false, &wait_emsg_end, &wait_emsg2_end, &allways_false,
                                                     &allways_false };

static void run_demo() {
    if (demo->state == mDemo_STATE_READY) {
        if ((*wait_start[demo->current.type])()) {
            change_camera(demo->camera_type);
            demo->state = mDemo_STATE_RUN;
        }
    } else if (demo->state == mDemo_STATE_RUN && (*wait_end[demo->current.type])()) {
        demo->state = mDemo_STATE_STOP;
    }
}

static void main_proc() {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR_NOW();

    if (demo->state == mDemo_STATE_STOP) {
        player->actor_class.state_bitfield &= ~ACTOR_STATE_IN_DEMO;

        if (demo->current.actor != NULL) {
            demo->current.actor->state_bitfield &= ~ACTOR_STATE_IN_DEMO;
        }

        demo->camera_type = CAMERA2_PROCESS_NORMAL;
        if (demo->keep_camera_type != CAMERA2_PROCESS_STOP && demo->current.actor != NULL) {
            change_camera(demo->keep_camera_type);
        } else {
            change_camera(demo->camera_type);
        }

        demo->keep_camera_type = CAMERA2_PROCESS_STOP;
        memset(&demo->current, 0, sizeof(mDemo_Request_c));
        demo->state = mDemo_STATE_WAIT;
    }

    if (demo->request_save.type != mDemo_TYPE_NONE && demo->request_save.type == demo->current.type &&
        check_speech_request() == TRUE) {
        demo->state = mDemo_STATE_WAIT;
    }

    if (demo->state == mDemo_STATE_WAIT) {
        choice_demo();
    }

    if (demo->state != mDemo_STATE_WAIT) {
        run_demo();
    }

    if (demo->state == mDemo_STATE_STOP && demo->request_save.type != mDemo_TYPE_NONE &&
        demo->request_save.type != demo->current.type) {
        memcpy(&demo->current, &demo->request_save, sizeof(mDemo_Request_c));
        demo->state = mDemo_STATE_RUN;
        change_camera(CAMERA2_PROCESS_NUM);
    }
}

extern void mDemo_stock_clear() {
    demo->request_num = 0;
    demo->priority_type = 0;
}

extern int mDemo_Request(int type, ACTOR* actor, mDemo_REQUEST_PROC req_proc) {
    f32 weight = 1.0f;
    int request_num = demo->request_num;

    if (request_num < mDemo_REQUEST_NUM) {
        if (type >= demo->priority_type) {
            mDemo_Request_c* req = &demo->request[request_num];

            if (type == mDemo_TYPE_TALK) {
                weight = weight_of_talk_position(actor);

                if (weight < 0.0f) {
                    return FALSE;
                }
            } else if (type == mDemo_TYPE_SPEAK && mPlib_Check_able_force_speak_label(gamePT, actor) == FALSE) {
                return FALSE;
            }

            demo->priority_type = type;

            req->type = type;
            req->actor = actor;
            req->proc = req_proc;
            req->talk_weight = weight;

            demo->request_num++;
        }

        return TRUE;
    }

    return FALSE;
}

extern int mDemo_Check(int type, ACTOR* actor) {
    if (type == demo->current.type && actor == demo->current.actor) {
        return TRUE;
    }

    return FALSE;
}

extern int mDemo_Start(ACTOR* actor) {
    return FALSE;
}

/* @unused @fabricated */
extern int mDemo_Check_and_Go(int type, ACTOR* actor) {
    if (mDemo_Check(type, actor) == FALSE) {
        return FALSE;
    }

    return mDemo_Start(actor);
}

extern int mDemo_End(ACTOR* actor) {
    if (actor == demo->current.actor) {
        demo->state = mDemo_STATE_STOP;
        return TRUE;
    }

    return FALSE;
}

extern void mDemo_Main(GAME_PLAY* play) {
    main_proc();
}

extern void mDemo_Init(GAME_PLAY* play) {
    demo->speaker_actor = NULL;
    demo->listen_actor = NULL;
    mDemo_Unset_SpeakerAble();
    mDemo_Unset_ListenAble();
    mDemo_Init_OrderValue();
    mDemo_Clear_change_player_destiny();
    init_demo();
}

extern int mDemo_CheckDemo() {
    return demo->state != mDemo_STATE_WAIT;
}

extern int mDemo_CheckDemo4Event() {

    switch (mDemo_CheckDemoType()) {
        case mDemo_TYPE_NONE:
        case mDemo_TYPE_EVENTMSG:
        case mDemo_TYPE_EVENTMSG2:
            return FALSE;
    }

    return TRUE;
}

extern void mDemo_Set_SpeakerAble() {
    demo->speaker_able = TRUE;
}

extern void mDemo_Set_ListenAble() {
    demo->listen_able = TRUE;
}

extern void mDemo_Unset_SpeakerAble() {
    demo->speaker_able = FALSE;
}

extern void mDemo_Unset_ListenAble() {
    demo->listen_able = FALSE;
}

extern int mDemo_Check_SpeakerAble() {
    return demo->speaker_able;
}

extern int mDemo_Check_ListenAble() {
    return demo->listen_able;
}

extern int mDemo_Check_DiffAngle_forTalk(s16 diff_angle) {
    int res = FALSE;

    if (diff_angle > -5000 && diff_angle < 5000) {
        res = TRUE;
    }

    return res;
}

extern void mDemo_KeepCamera(int camera_type) {
    demo->keep_camera_type = camera_type;
}
