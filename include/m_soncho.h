#ifndef M_SONCHO_H
#define M_SONCHO_H

#include "types.h"
#include "m_play_h.h"
#include "ac_taisou_npc0.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mSC_TROPHY_MAX 32
#define mSC_RADIO_DAYS 13
#define mSC_LIGHTHOUSE_DAYS 17

#define mSC_TROPHY_GOLDEN_NET 28
#define mSC_TROPHY_GOLDEN_AXE 29
#define mSC_TROPHY_GOLDEN_SCOOP 30 // assumed
#define mSC_TROPHY_GOLDEN_ROD 31

enum {
    mSC_LIGHTHOUSE_EVENT_NONE,
    mSC_LIGHTHOUSE_EVENT_JAN_CONTRIBUTED,
    mSC_LIGHTHOUSE_EVENT_JAN_STARTED,
    mSC_LIGHTHOUSE_EVENT_FEB_CONTRIBUTED,
    mSC_LIGHTHOUSE_EVENT_FEB_STARTED,

    mSC_LIGHTHOUSE_EVENT_NUM
};

enum {
  mSC_EVENT_NEW_YEARS_DAY,
  mSC_EVENT_FOUNDERS_DAY,
  mSC_EVENT_GRADUATION_DAY,
  mSC_EVENT_APRILFOOLS_DAY,
  mSC_EVENT_TOWN_DAY,
  mSC_EVENT_MOTHERS_DAY,
  mSC_EVENT_SALE_DAY,
  mSC_EVENT_CHERRY_BLOSSOM_FESTIVAL,
  mSC_EVENT_SPRING_SPORTS_FAIR,
  mSC_EVENT_NATURE_DAY,
  mSC_EVENT_SPRING_CLEANING,
  mSC_EVENT_FATHERS_DAY,
  mSC_EVENT_FISHING_TOURNEY_1,
  mSC_EVENT_GROUNDHOG_DAY,
  mSC_EVENT_EXPLORERS_DAY,
  mSC_EVENT_FIREWORKS_SHOW,
  mSC_EVENT_METEOR_SHOWER,
  mSC_EVENT_HARVEST_MOON_FESTIVAL,
  mSC_EVENT_MAYORS_DAY,
  mSC_EVENT_OFFICERS_DAY,
  mSC_EVENT_FALL_SPORTS_FAIR,
  mSC_EVENT_HALLOWEEN,
  mSC_EVENT_FISHING_TOURNEY_2,
  mSC_EVENT_SNOW_DAY,
  mSC_EVENT_LABOR_DAY,
  mSC_EVENT_TOY_DAY,
  mSC_EVENT_NEW_YEARS_EVE_COUNTDOWN,
  mSC_EVENT_HARVEST_FESTIVAL,
  mSC_EVENT_PLAYER_BIRTHDAY,

  mSC_EVENT_NUM = mSC_EVENT_PLAYER_BIRTHDAY,

  mSC_SPECIAL_EVENT_ARBEIT = 32,

  mSC_SPECIAL_EVENT_JAN_VACATION = 101,
  mSC_SPECIAL_EVENT_FEB_VACATION = 102,
  mSC_SPECIAL_EVENT_MORNING_AEROBICS = 103
};

enum {
  mSC_FIELD_EVENT_FOOT_RACE,
  mSC_FIELD_EVENT_BALL_TOSS,
  mSC_FIELD_EVENT_TUG_O_WAR,
  mSC_FIELD_EVENT_AEROBICS,

  mSC_FIELD_EVENT_NUM
};

enum {
  mSC_RADIO_TIME_LESS,
  mSC_RADIO_TIME_SAME_DAY,
  mSC_RADIO_TIME_OVER,

  mSC_RADIO_TIME_NUM
};

enum {
  mSCR_TALK_PICKUP_ALL,
  mSCR_TALK_INSPECTION,
  mSCR_TALK_NEXT_INSPECTION,
  mSCR_TALK_NEWCARD,
  mSCR_TALK_BEFORE_GIVE,
  mSCR_TALK_GIVE,
  mSCR_TALK_NEXT,
  mSCR_TALK_7,
  mSCR_TALK_8,
  mSCR_TALK_9,

  mSCR_TALK_NUM
};

enum {
  mSCR_ACTION_TOO_LATE, // too late into aerobics to complete
  mSCR_ACTION_DELETE_OLD_CARD,
  mSCR_ACTION_NEW_CARD,
  mSCR_ACTION_LOST_CARD,
  mSCR_ACTION_STAMP_CARD,
  mSCR_ACTION_FINISH_CARD,
  mSCR_ACTION_LOST_CARD_AND_FINISH, // "lost" radio card but finished today

  mSCR_ACTION_NUM
};

enum {
  mSC_LIGHTHOUSE_PERIOD_0,
  mSC_LIGHTHOUSE_PERIOD_1,
  mSC_LIGHTHOUSE_PERIOD_2,
  mSC_LIGHTHOUSE_PERIOD_NONE,

  mSC_LIGHTHOUSE_PERIOD_NUM
};

extern u8 mSC_get_soncho_event();
extern u8 mSC_get_soncho_field_event();
extern void mSC_delete_soncho(ACTOR* actor, GAME_PLAY* play);
extern int mSC_trophy_get(u8 num);
extern void mSC_trophy_set(u8 num);
extern mActor_name_t mSC_trophy_item(u8 soncho_event);
extern void mSC_item_string_set(mActor_name_t item, int str_no);
extern void mSC_get_event_name_str(u8* buf, int buf_len, int soncho_event);
extern void mSC_event_name_set(u8 soncho_event);
extern void mSC_set_free_str_number(int free_str_no, u32 num);
extern int mSC_Radio_Set_Talk_Proc(TAISOU_NPC0_ACTOR* taisou_actor);
extern void mSC_Radio_Talk_Proc(TAISOU_NPC0_ACTOR* taisou_actor, GAME_PLAY* play);
extern int mSC_LightHouse_get_period(lbRTC_time_c* time);
extern int mSC_LightHouse_day(const lbRTC_time_c* time);
extern int mSC_LightHouse_Event_Check(int player_no);
extern void mSC_LightHouse_Event_Clear(int player_no);
extern mActor_name_t mSC_LightHouse_Event_Present_Item(u32 player_no);
extern int mSC_LightHouse_Event_Start();
extern int mSC_LightHouse_Talk_After_Check();
extern void mSC_LightHouse_Quest_Start();
extern int mSC_LightHouse_Switch_Check();
extern int mSC_LightHouse_In_Check();
extern void mSC_LightHouse_Switch_On();
extern void mSC_LightHouse_Delete_Player(int player_no);
extern int mSC_LightHouse_travel_check();
extern void mSC_change_player_freeze(GAME_PLAY* play);
extern u32 mSC_check_ArbeitPlayer();

#ifdef __cplusplus
}
#endif

#endif
