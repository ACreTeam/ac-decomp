#ifndef M_DEMO_H
#define M_DEMO_H

#include "types.h"
#include "m_actor_type.h"
#include "m_play_h.h"
#include "m_lib.h"
#include "m_scene.h"
#include "m_msg_enum.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mDemo_ORDER_VALUE_NUM 16
#define mDemo_ORDER_VALUE_MAX 10
#define mDemo_REQUEST_NUM 32

#define mDemo_MSG_PRIORITY 5
#define mDemo_CAMERA_PRIORITY 6

#define mDemo_WINDOW_COLOR_R 235
#define mDemo_WINDOW_COLOR_G 255
#define mDemo_WINDOW_COLOR_B 235
#define mDemo_WINDOW_COLOR_A 255

enum {
    mDemo_STATE_WAIT,
    mDemo_STATE_READY,
    mDemo_STATE_RUN,
    // ???
    mDemo_STATE_STOP = 9,

    mDemo_STATE_NUM
};

enum {
    mDemo_DIRECT_N,
    mDemo_DIRECT_NE,
    mDemo_DIRECT_E,
    mDemo_DIRECT_SE,
    mDemo_DIRECT_S,
    mDemo_DIRECT_SW,
    mDemo_DIRECT_W,
    mDemo_DIRECT_NW,

    mDemo_DIRECT_NUM
};

enum demo_type {
    mDemo_TYPE_NONE,
    mDemo_TYPE_SCROLL,
    mDemo_TYPE_EXITSCENE,
    mDemo_TYPE_DOOR,
    mDemo_TYPE_4,
    mDemo_TYPE_SCROLL2,
    mDemo_TYPE_DOOR2,
    mDemo_TYPE_TALK,
    mDemo_TYPE_SPEAK,
    mDemo_TYPE_REPORT,
    mDemo_TYPE_SPEECH,
    mDemo_TYPE_OUTDOOR,
    mDemo_TYPE_12,
    mDemo_TYPE_EVENTMSG,
    mDemo_TYPE_EVENTMSG2,
    mDemo_TYPE_15,
    mDemo_TYPE_SCROLL3,

    mDemo_TYPE_NUM
};

enum demo_order_type {
    mDemo_ORDER_PLAYER,
    mDemo_ORDER_1,
    mDemo_ORDER_2,
    mDemo_ORDER_3,
    mDemo_ORDER_NPC0,
    mDemo_ORDER_NPC1,
    mDemo_ORDER_NPC2,
    mDemo_ORDER_7,
    mDemo_ORDER_8,
    mDemo_ORDER_QUEST,

    mDemo_ORDER_NUM
};

typedef void (*mDemo_REQUEST_PROC)(ACTOR*);

typedef struct demo_clip_s {
    void* demo_class;
    int type; /* 0 = none?, 1 = intro_demo, 2 = ride_off_demo */
} mDemo_Clip_c;

enum demo_clip_type {
    mDemo_CLIP_TYPE_NONE,
    mDemo_CLIP_TYPE_INTRO_DEMO,
    mDemo_CLIP_TYPE_RIDE_OFF_DEMO,
    mDemo_CLIP_TYPE_PRESENT_DEMO,
    mDemo_CLIP_TYPE_BOAT_DEMO,
    mDemo_CLIP_TYPE_RESET_DEMO,

    mDemo_CLIP_TYPE_NUM
};

typedef struct demo_req_s {
    ACTOR* actor;
    int type;
    mDemo_REQUEST_PROC proc;
    f32 talk_weight;
} mDemo_Request_c;

typedef struct demo_door_data_s {
    int type;

    struct {
        f32 size;
        int direct;
    } house_info;
} mDemo_door_data_c;

typedef struct demo_emsg_data_s {
    int msg_no;
    rgba_t window_color;
    int msg_delay_timer;
    int scene_delay_timer;
    Door_data_c door_data;
    u8 _24[4]; // unused?
} mDemo_emsg_data_c;

typedef struct demo_talk_data_s {
    int msg_no;
    int turn;
    int use_zoom_sound;
    int display_name;
    int change_player;
    int return_get_golden_axe_demo;
    int return_demo_wait;
    rgba_t window_color;
    u8 actor_saved_weight;
} mDemo_talk_data_c;

typedef struct demo_data_s {
    ACTOR* speaker_actor;
    ACTOR* listen_actor;
    int speaker_able;
    int listen_able;
    u16 order_data[mDemo_ORDER_NUM][mDemo_ORDER_VALUE_MAX];
    s8 change_player_destiny;
    int state;
    mDemo_Request_c current;
    mDemo_Request_c request[mDemo_REQUEST_NUM];
    int request_num;
    int priority_type;
    int camera_type;
    int keep_camera_type;

    union {
        mDemo_door_data_c door;
        mDemo_emsg_data_c emsg;
        mDemo_talk_data_c talk;
    } data;

    mDemo_Request_c request_save;
} mDemo_Data_c;

extern ACTOR* mDemo_Get_talk_actor();
extern void mDemo_Set_speaker_actor(ACTOR* actor);
extern void mDemo_Set_OrderValue(int type, int idx, u16 value);
extern u16 mDemo_Get_OrderValue(int type, int idx);
extern void mDemo_Set_msg_num(int msg_num);
extern int mDemo_Get_Talk_Actors(ACTOR** speaker, ACTOR** listener);
extern void mDemo_Set_change_player_destiny(s8 destiny);
extern void mDemo_Set_use_zoom_sound(u8 use_zoom_sound);
extern int mDemo_Get_use_zoom_sound();
extern void mDemo_Set_talk_display_name(s8 display_name);
extern int mDemo_Get_talk_display_name();
extern void mDemo_Set_talk_change_player(u8 change_player);
extern int mDemo_Get_talk_change_player();
extern void mDemo_Set_talk_return_demo_wait(u8 return_demo_wait);
extern int mDemo_Get_talk_return_demo_wait();
extern void mDemo_Set_talk_return_get_golden_axe_demo(u8 return_get_golden_axe_demo);
extern int mDemo_Get_talk_return_get_golden_axe_demo();
extern void mDemo_Set_talk_turn(u8 turn);
extern int mDemo_Get_talk_turn();
extern void mDemo_Set_talk_window_color(rgba_t* window_color);
extern rgba_t* mDemo_Get_talk_window_color_p();
extern void mDemo_Set_camera(u8 camera_type);
extern int mDemo_Get_camera();
extern int mDemo_CheckDemoType();
extern int mDemo_Set_house_info(f32 size, int direct);
extern void mDemo_stock_clear();
extern int mDemo_Request(int type, ACTOR* actor, mDemo_REQUEST_PROC req_proc);
extern int mDemo_Check(int type, ACTOR* actor);
extern int mDemo_Start(ACTOR* actor);
extern int mDemo_Check_and_Go(int type, ACTOR* actor);
extern int mDemo_End(ACTOR* actor);
extern void mDemo_Main(GAME_PLAY* play);
extern void mDemo_Init(GAME_PLAY* play);
extern int mDemo_CheckDemo();
extern int mDemo_CheckDemo4Event();
extern void mDemo_Set_SpeakerAble();
extern void mDemo_Set_ListenAble();
extern void mDemo_Unset_SpeakerAble();
extern void mDemo_Unset_ListenAble();
extern int mDemo_Check_SpeakerAble();
extern int mDemo_Check_ListenAble();
extern int mDemo_Check_DiffAngle_forTalk(s16 diff_angle);
extern void mDemo_KeepCamera(int camera_type);

#define mDemo_CAN_ACTOR_TALK(actor) (!mDemo_Check(mDemo_TYPE_SPEAK, (actor)) && !mDemo_Check(mDemo_TYPE_TALK, (actor)))
#define mDemo_IS_ACTOR_TALKING(actor) (mDemo_Check(mDemo_TYPE_SPEAK, (actor)) == TRUE || mDemo_Check(mDemo_TYPE_TALK, (actor)) == TRUE)

#ifdef __cplusplus
}
#endif

#endif
