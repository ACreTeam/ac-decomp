#include "m_event.h"

#include "libultra/libultra.h"
#include "m_common_data.h"
#include "ac_aprilfool_control_h.h"
#include "m_play.h"
#include "m_scene_table.h"

static int n_today_events;
static int status_edge;
static int funeral;
static int dead;
static lbRTC_year_t weekday1st_year;
static lbRTC_weekday_t weekday1st[lbRTC_MONTHS_MAX];

extern void mEv_ClearSpecialEvent(mEv_special_c* special_event) {
  special_event->type = -1;
  bzero(&special_event->event, sizeof(mEv_special_u));
  bzero(Common_GetPointer(event_common), sizeof(mEv_event_common_u));
}

extern void mEv_ClearEventKabuPeddler(mEv_kabu_peddler_c* kabu_peddler) {
  if (kabu_peddler != NULL) {
    mPr_ClearAnyPersonalID(kabu_peddler->spoken_pids, TOTAL_PLAYER_NUM);
  }
}

extern void mEv_ClearEventSaveInfo(mEv_event_save_c* save_event) {
  mEv_ClearSpecialEvent(&save_event->special);
  mEv_ClearEventKabuPeddler(&save_event->weekly.kabu_peddler);
  save_event->flags = 0;
}

extern void mEv_ClearEventInfo() {
  u32* event_flag = Common_Get(event_flags);
  int i;

  for (i = 0; i < mEv_EVENT_TYPE_NUM; i++) {
    event_flag[0] = 0;
    event_flag++;
  }

  Common_Set(event_flags[1], Save_Get(event_save_data.flags));
  Common_Get(event_common).fieldday_event_id = -1;
  Common_Get(event_common).fieldday_event_over_status = -1;
}

extern void mEv_EventON(u32 event_kind) {
  int type = mEv_GET_TYPE(event_kind);
  u32 flag;

  if (type >= mEv_EVENT_TYPE_NUM) {
    return;
  }

  flag = Common_Get(event_flags[type]);
  flag |= (1 << mEv_GET_SUBTYPE(event_kind));
  Common_Set(event_flags[type], flag);

  if (type != mEv_SAVED_EVENT) {
    return;
  }

  Save_Get(event_save_data).flags = Common_Get(event_flags[flag]);
}

extern void mEv_EventOFF(u32 event_kind) {
  int type = mEv_GET_TYPE(event_kind);
  u32 flag;

  if (type >= mEv_EVENT_TYPE_NUM) {
    return;
  }

  flag = Common_Get(event_flags[type]);
  flag &= ~(1 << mEv_GET_SUBTYPE(event_kind));
  Common_Set(event_flags[type], flag);

  if (type != mEv_SAVED_EVENT) {
    return;
  }

  Save_Get(event_save_data).flags = Common_Get(event_flags[flag]);
}

extern int mEv_CheckEvent(u32 event_kind) {
  int type = mEv_GET_TYPE(event_kind);
  int res = FALSE;

  if (type < mEv_EVENT_TYPE_NUM && ((Common_Get(event_flags[type]) >> mEv_GET_SUBTYPE(event_kind)) & 1)) {
    res = TRUE;
  }

  return res;
}

extern void mEv_ClearPersonalEventFlag(int player_no) {
  mEv_EventOFF(mEv_SAVED_FIRSTJOB_PLR0 + player_no);
  mEv_EventOFF(mEv_SAVED_FIRSTINTRO_PLR0 + player_no);
  mEv_EventOFF(mEv_SAVED_HRAWAIT_PLR0 + player_no);
  mEv_EventOFF(mEv_SAVED_HRATALK_PLR0 + player_no);
  mEv_EventOFF(mEv_SAVED_FJOPENQUEST_PLR0 + player_no);
  mEv_EventOFF(mEv_SAVED_GATEWAY_PLR0 + player_no);

  {
    aAPC_event_save_data_c* data = (aAPC_event_save_data_c*)mEv_get_save_area(mEv_EVENT_APRILFOOLS_DAY, 0);

    if (data != NULL) {
      data->talk_bitfield[player_no] = 0;
    }
  }
}

extern void mEv_SetFirstJob() {
  int player_no = Common_Get(player_no);

  if (player_no < PLAYER_NUM) {
    mEv_EventON(mEv_SAVED_FIRSTJOB_PLR0 + player_no);
  }
}

extern int mEv_CheckRealArbeit() {
  int player_no = Common_Get(player_no);
  int res = FALSE;
  
  if (
    player_no < PLAYER_NUM &&
    (
      mEv_CheckEvent(mEv_SAVED_FIRSTJOB_PLR0 + player_no) == TRUE ||
      mEv_CheckEvent( mEv_SAVED_HRAWAIT_PLR0 + player_no) == TRUE
    )
  ) {
    res = TRUE;
  }

  return res;
}

extern int mEv_CheckArbeit() {
  int player_no = Common_Get(player_no);
  int res = FALSE;
  
  if (
    player_no < PLAYER_NUM &&
    (
      mEv_CheckEvent(mEv_SAVED_FIRSTJOB_PLR0 + player_no) == TRUE ||
      mEv_CheckEvent( mEv_SAVED_HRAWAIT_PLR0 + player_no) == TRUE ||
      mEv_CheckEvent( mEv_SAVED_HRATALK_PLR0 + player_no) == TRUE
    )
  ) {
    res = TRUE;
  }

  return res;
}

extern int mFI_CheckFirstJob() {
  int player_no = Common_Get(player_no);
  int res = FALSE;
  
  if (
    player_no < PLAYER_NUM &&
    mEv_CheckEvent(mEv_SAVED_FIRSTJOB_PLR0 + player_no) == TRUE
  ) {
    res = TRUE;
  }

  return res;
}

extern void mEv_UnSetFirstJob() {
  int player_no = Common_Get(player_no);

  if (player_no < PLAYER_NUM) {
    mEv_EventOFF(mEv_SAVED_FIRSTJOB_PLR0 + player_no);
    mEv_EventON(mEv_SAVED_HRAWAIT_PLR0 + player_no);
  }
}

extern void mEv_SetFirstIntro() {
  int player_no = Common_Get(player_no);

  if (player_no < PLAYER_NUM) {
    mEv_EventON(mEv_SAVED_FIRSTINTRO_PLR0 + player_no);
  }
}

extern int mEv_CheckFirstIntro() {
  int player_no = Common_Get(player_no);
  int res = FALSE;

  if (
    player_no < PLAYER_NUM &&
    mEv_CheckEvent(mEv_SAVED_FIRSTINTRO_PLR0 + player_no) == TRUE
  ) {
    res = TRUE;
  }

  return res;
}

extern void mEv_UnSetFirstIntro() {
  int player_no = Common_Get(player_no);

  if (player_no < PLAYER_NUM) {
    mEv_EventOFF(mEv_SAVED_FIRSTINTRO_PLR0 + player_no);
  }
}

extern void mEv_SetGateway() {
  int player_no = Common_Get(player_no);

  if (player_no < TOTAL_PLAYER_NUM) {
    mEv_EventON(mEv_SAVED_GATEWAY_PLR0 + player_no);
  }
}

extern int mEv_CheckGateway() {
  int player_no = Common_Get(player_no);
  int res = FALSE;

  if (
    player_no < TOTAL_PLAYER_NUM &&
    mEv_CheckEvent(mEv_SAVED_GATEWAY_PLR0 + player_no) == TRUE
  ) {
    res = TRUE;
  }

  return res;
}

extern void mEv_UnSetGateway() {
  int player_no = Common_Get(player_no);

  if (player_no < TOTAL_PLAYER_NUM) {
    mEv_EventOFF(mEv_SAVED_GATEWAY_PLR0 + player_no);
  }
}

static int title_demo_number = -1;

extern int mEv_CheckTitleDemo() {
  return title_demo_number;
}

extern void mEv_SetTitleDemo(int demo_number) {
  title_demo_number = demo_number;
}

extern void mEv_RenewalDataEveryDay() {
  if (mTM_check_renew_time(mTM_RENEW_TIME_DAILY) == TRUE) {
    int i;

    for (i = 0; i < PLAYER_NUM; i++) {
      if (mEv_CheckEvent(mEv_SAVED_HRAWAIT_PLR0 + i) == TRUE) {
        /* After a new day starts, turn off all players' 'wait a day' HRA event and turn on talk to Tom Nook HRA event */
        mEv_EventOFF(mEv_SAVED_HRAWAIT_PLR0 + i);
        mEv_EventON(mEv_SAVED_HRATALK_PLR0 + i);
      }
    }
  }
}

extern void mEv_GetEventWeather(s16* weather, s16* intensity) {
  intensity[0] = mEnv_WEATHER_INTENSITY_HEAVY;

  if (mEv_check_schedule(mEv_EVENT_WEATHER_CLEAR)) {
    weather[0] = mEnv_WEATHER_CLEAR;
  }
  else if (mEv_check_schedule(mEv_EVENT_WEATHER_SNOW)) {
    weather[0] = mEnv_WEATHER_SNOW;
  }
  else if (mEv_check_schedule(mEv_EVENT_WEATHER_SPORTS_FAIR)) {
    weather[0] = mEnv_WEATHER_CLEAR;
  }
  else {
    weather[0] = -1; // no event weather
  }
}

static lbRTC_day_t last_day_of_month(lbRTC_month_t month) {
  static lbRTC_day_t last_day[lbRTC_MONTHS_MAX] = {
    31, 28, 31, 30,
    31, 30, 31, 31,
    30, 31, 30, 31
  };

  lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
  lbRTC_year_t year = rtc_time->year;

  if (month != lbRTC_FEBRUARY) {
    return last_day[month - 1];
  }
  else if (lbRTC_IS_LEAPYEAR(year)) {
    return 29;
  }
  else {
    return 28;
  }
}

static void init_weekday1st() {
  lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
  lbRTC_month_t month = rtc_time->month & 0xF; // ??
  lbRTC_month_t i;
  lbRTC_weekday_t weekday;

  weekday1st_year = rtc_time->year;

  weekday = (rtc_time->weekday + (1 - rtc_time->day)) % lbRTC_WEEK;
  if (weekday < 0) {
    weekday += lbRTC_WEEK;
  }

  weekday1st[month] = weekday;

  for (i = month + 1; i <= lbRTC_MONTHS_MAX; i++) {
    weekday1st[i] = (weekday1st[i - 1] + last_day_of_month(i)) % lbRTC_WEEK;
  }

  for (i = month - 1; i >= lbRTC_JANUARY; i--) {
    weekday = (weekday1st[i + 1] - last_day_of_month(i)) % lbRTC_WEEK;
    if (weekday < 0) {
      weekday += lbRTC_WEEK;
    }

    weekday1st[i] = weekday;
  }
}

static int check_date_range(u16 date, u16 lower_bound, u16 upper_bound) {
  if (upper_bound < lower_bound) {
    if (date < lower_bound && date > upper_bound) {
      return FALSE;
    }
    else {
      return TRUE;
    }
  }
  else if (date < lower_bound || date > upper_bound) {
    return FALSE;
  }
  else {
    return TRUE;
  }
}

static int check_ymdh_range(u32 ymdh, u32 lower_bound, u32 upper_bound) {
  int res = FALSE;

  if (ymdh >= lower_bound && ymdh <= upper_bound) {
    res = TRUE;
  }

  return res;
}

static mEv_MonthDay_u after_n_day(mEv_MonthDay_u month_day, int n_day) {
  mEv_MonthDay_u after = month_day;

  if (n_day >= 0) {
    lbRTC_day_t last_day = last_day_of_month(after.month);

    after.day = after.day + n_day;
    if (after.day > last_day) {
      if (after.month == lbRTC_DECEMBER) {
        after.month = lbRTC_JANUARY;
      }
      else {
        after.month++;
      }

      after.day -= last_day;
    }
  }
  else {
    after.day = after.day + n_day;
    if ((after.day & 0x80) != 0 || after.day == 0) {
      if (after.month == lbRTC_JANUARY) {
        after.month = lbRTC_DECEMBER;
      }
      else {
        after.month--;
      }

      after.day += last_day_of_month(after.month);
    }
  }

  return after;
}

extern lbRTC_day_t mEv_get_next_weekday(lbRTC_weekday_t weekday) {
  lbRTC_weekday_t next_weekday;
  lbRTC_day_t day;
  lbRTC_day_t last_day;

  if (weekday >= Common_Get(time.rtc_time).weekday) {
    next_weekday = weekday - Common_Get(time.rtc_time).weekday;
  }
  else {
    next_weekday = lbRTC_WEEK - (Common_Get(time.rtc_time).weekday - weekday);
  }

  day = Common_Get(time.rtc_time).day + next_weekday;
  last_day = last_day_of_month(Common_Get(time.rtc_time).month);

  if (day > last_day) {
    day -= last_day;
  }

  return day;
}

#define mEv_date_decode_weekday(day) ((day) & 0b00000111) // 0-6 (which weekday, Sunday-Saturday)
#define mEv_date_decode_week(day) (((day) & 0b00111000) >> 3) // 0-5 (which week of the month, 1st, 2nd, 3rd, ...)

static lbRTC_day_t m_weekday2day(lbRTC_month_t month, u8 day_enc) {
  int week = mEv_date_decode_week(day_enc); // get the week of the month
  int weekday = mEv_date_decode_weekday(day_enc); // get the weekday
  lbRTC_day_t day = 0;
  lbRTC_day_t last_day = last_day_of_month(month);

  if (week == mEv_SCHEDULE_WEEKLY) {
    if (month > Common_Get(time.rtc_time).month) {
      week = 1; /* 1st week of this month */
    }
    else if (month < Common_Get(time.rtc_time).month) {
      week = mEv_SCHEDULE_LAST_WEEKDAY_OF_MONTH; /* last weekday of the month */
    }
    else {
      day = Common_Get(time.rtc_time).day - (Common_Get(time.rtc_time).weekday - weekday);

      if (day > last_day) {
        week = mEv_SCHEDULE_LAST_WEEKDAY_OF_MONTH;
      }
      else {
        week = 0; /* cleared */
      }
    }
  }

  if (week == mEv_SCHEDULE_LAST_WEEKDAY_OF_MONTH) {
    int t_day = (last_day + weekday1st[month] - 1) % lbRTC_WEEK; /* get the weekday of the first day of next month */

    if (t_day < weekday) {
      day = (last_day - (t_day - weekday)) - lbRTC_WEEK;
    }
    else {
      day = last_day - (t_day - weekday);
    }
  }
  else if (week != 0) {
    int t_day = weekday1st[month];

    if (weekday < t_day) {
      day = week * lbRTC_WEEK + (weekday - t_day) + 1;
    }
    else {
      day = (week - 1) * lbRTC_WEEK + (weekday - t_day) + 1;
    }
  }

  return day;
}

extern lbRTC_day_t mEv_weeday2day(lbRTC_month_t month, int week, int weekday) {
  lbRTC_day_t day = 0;
  lbRTC_day_t last_day = last_day_of_month(month);

  if (week == mEv_SCHEDULE_WEEKLY) {
    if (month > Common_Get(time.rtc_time).month) {
      week = 1; /* 1st week of this month */
    }
    else if (month < Common_Get(time.rtc_time).month) {
      week = mEv_SCHEDULE_LAST_WEEKDAY_OF_MONTH; /* last weekday of the month */
    }
    else {
      day = Common_Get(time.rtc_time).day - (Common_Get(time.rtc_time).weekday - weekday);

      if (day > last_day) {
        week = mEv_SCHEDULE_LAST_WEEKDAY_OF_MONTH;
      }
      else {
        week = 0; /* cleared */
      }
    }
  }

  if (week == mEv_SCHEDULE_LAST_WEEKDAY_OF_MONTH) {
    int t_day = (last_day + weekday1st[month] - 1) % lbRTC_WEEK; /* get the weekday of the first day of next month */

    if (t_day < weekday) {
      day = (last_day - (t_day - weekday)) - lbRTC_WEEK;
    }
    else {
      day = last_day - (t_day - weekday);
    }
  }
  else if (week != 0) {
    int t_day = weekday1st[month];

    if (weekday < t_day) {
      day = week * lbRTC_WEEK + (weekday - t_day) + 1;
    }
    else {
      day = (week - 1) * lbRTC_WEEK + (weekday - t_day) + 1;
    }
  }

  return day;
}

static int get_end_time(u32 active_hours) {
  int hour;
  int i;

  if (active_hours & ((1 << 24) - 1) == 0) {
    return -1; /* no active hours */
  }

  hour = 23;
  for (i = 0; i < 24; i++) {
    if ((active_hours & (1 << 23)) & 1) {
      break;
    }

    active_hours <<= 1; /* move hours left by one bit, MSB is latest hour */
    hour--;
  }

  return hour;
}

static mEv_event_today_c event_today[mEv_TODAY_EVENT_NUM];
static u8 index_today[mEv_EVENT_NUM];

extern int mEv_get_end_time(int event_type) {
  u8 idx = index_today[event_type];

  if (idx == 0xFF) {
    return -1;
  }
  else {
    return get_end_time(event_today[idx].active_hours);
  }
}

static int search_empty_event_today() {
  int i;

  for (i = 0; i < mEv_TODAY_EVENT_NUM; i++) {
    if (event_today[i].type == -1) {
      return i;
    }
  }

  return i;
}

static int add_event_today(mEv_MonthDay_u month_day, mEv_schedule_c* schedule) {
  u8 idx = index_today[schedule->type];
  int res = FALSE;

  if (idx == 0xFF) {
    idx = search_empty_event_today();

    if (idx >= mEv_TODAY_EVENT_NUM) {
      return FALSE;
    }

    n_today_events++;
    index_today[schedule->type] = idx;
  }

  {
    u8 start_hour = schedule->date[0].hour;
    u8 end_hour = schedule->date[1].hour;
    u32 i;
    u32 n;

    if ((start_hour & mEv_SCHEDULE_TODAY) == 0) {
      event_today[idx].begin_date = schedule->date[0].month_day;
      event_today[idx].end_date = schedule->date[1].month_day;
    }
    else {
      event_today[idx].begin_date = month_day;
      event_today[idx].end_date = month_day;
      start_hour &= ~mEv_SCHEDULE_TODAY;
      end_hour &= ~mEv_SCHEDULE_TODAY;
    }

    if ((start_hour & mEv_SCHEDULE_MULTIDAY) != 0) {
      start_hour &= ~mEv_SCHEDULE_MULTIDAY;
      end_hour &= ~mEv_SCHEDULE_MULTIDAY;

      if (month_day.raw != schedule->date[0].month_day.raw) {
        start_hour = 0;
      }

      if (month_day.raw != schedule->date[1].month_day.raw) {
        end_hour = 23;
      }
    }

    n = 1;
    for (i = 0; i < 24; i++) {
      if (i >= start_hour && i <= end_hour) {
        event_today[idx].active_hours |= n;
      }

      n <<= 1;
    }

    event_today[idx].type = schedule->type;
    event_today[idx].status |= mEv_STATUS_EXIST;
  }

  return res;
}

static int check_and_clear_event_today(Event_c* event, int type) {
  u8 idx = index_today[idx];

  if (idx != 0xFF) {
    mEv_event_today_c* today_event = &event_today[idx];

    if ((today_event->status & mEv_STATUS_EXIST) == FALSE) {
      int flags = 0;
      mEv_place_data_c* place = mEv_get_common_place(today_event->type, 81);

      if (place != NULL && place->block.x == event->block_x && place->block.z == event->block_z) {
        flags |= 0b00000001; // 1, in the block the event is supposed to exist
      }

      if (mEv_check_status(today_event->type, mEv_STATUS_RUN)) {
        flags |= 0b00000010; // 2, event is currently running
        today_event->active_hours = 0x20000000;
      }

      if (type == today_event->type && flags == 0) {
        today_event->type = -1;
        n_today_events--;
        today_event->active_hours = 0;
        today_event->end_date.raw = 0;
        today_event->status = 0;
        index_today[type] = 0xFF;

        return TRUE;
      }
    }
  }

  return FALSE;
}

static int delete_too_short_event(Event_c* event, int type, mEv_schedule_date_u date) {
  u8 idx = index_today[type];

  if (idx != 0xFF) {
    mEv_event_today_c* today_event = &event_today[idx];
    mEv_schedule_date_u new_date;

    switch (today_event->type) {
      case mEv_EVENT_NEW_YEARS_DAY:
      case mEv_EVENT_GROUNDHOG_DAY:
      case mEv_EVENT_SPORTS_FAIR_BALL_TOSS:
      case mEv_EVENT_SPORTS_FAIR_AEROBICS:
      case mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR:
      case mEv_EVENT_SPORTS_FAIR_FOOT_RACE:
      case mEv_EVENT_CHERRY_BLOSSOM_FESTIVAL:
      case mEv_EVENT_FISHING_TOURNEY_1:
      case mEv_EVENT_FIREWORKS_SHOW:
      case mEv_EVENT_MORNING_AEROBICS:
      case mEv_EVENT_HARVEST_MOON_FESTIVAL:
      case mEv_EVENT_FISHING_TOURNEY_2:
      case mEv_EVENT_HARVEST_FESTIVAL:
      {
        new_date = date;
        new_date.hour = mEv_get_end_time(today_event->type);

        break;
      }

      case mEv_EVENT_HALLOWEEN:
      case mEv_EVENT_TOY_DAY_JINGLE:
      case mEv_EVENT_NEW_YEARS_EVE_COUNTDOWN:
      {
        new_date.raw = 0;
        new_date.month_day = today_event->end_date;
        new_date.hour = mEv_get_end_time(today_event->type);

        break;
      }

      default:
      {
        return FALSE;
      }
    }

    if (new_date.raw != date.raw) {
      return FALSE;
    }

    if (Common_Get(time.rtc_time).min < 55) {
      return FALSE;
    }

    Common_Get(event_common).too_short = type;
  }

  return TRUE;
}

static void init_today_event() {
  mEv_event_today_c* today_event = event_today;
  int i;

  for (i = 0; i < mEv_TODAY_EVENT_NUM; i++) {
    today_event->type = -1;
    today_event->active_hours = 0;
    today_event->end_date.raw = 0;
    today_event->begin_date.raw = 0;
    today_event->status = 0;

    today_event++;
  }

  n_today_events = 0;

  {
    u8* index_today_p = index_today;

    for (i = 0; i < mEv_EVENT_NUM; i++) {
      index_today_p[0] = 0xFF;
      index_today_p++;
    }
  }
}

static void init_time_seat() {
  mEv_event_today_c* today_event = event_today;
  int i;

  for (i = 0; i < mEv_TODAY_EVENT_NUM; i++) {
    today_event->active_hours = 0;
    today_event->end_date.raw = 0;
    today_event->begin_date.raw = 0;
    today_event->status &= ~mEv_STATUS_EXIST;
  }
}

static int get_special_event_end_time(s16 event_type) {
  int end_time = 0;

  switch (event_type) {
    case mEv_EVENT_DESIGNER:
      end_time = 5;
      break;
    case mEv_EVENT_ARTIST:
      end_time = 5;
      break;
    case mEv_EVENT_CARPET_PEDDLER:
      end_time = 5;
      break;
    case mEv_EVENT_GYPSY:
      end_time = 20;
      break;
    case mEv_EVENT_BROKER_SALE:
      end_time = 17;
      break;
    case mEv_EVENT_SHOP_SALE:
      end_time = 23;
      break;
  }

  return end_time;
}

static int init_special_init(int new_event) {
  int res = FALSE;

  switch (Save_Get(scene_no)) {
    case SCENE_BUGGY:
    case SCENE_BROKER_SHOP:
    {
      if (gamePT->frame_counter == 0) {
        return FALSE;
      }

      break;
    }
  }

  switch (Save_Get(scene_no)) {
    case SCENE_BUGGY:
    case SCENE_BROKER_SHOP:
      return FALSE;

    case SCENE_SHOP0:
    case SCENE_CONVENI:
    case SCENE_SUPER:
    case SCENE_DEPART:
    case SCENE_DEPART_2:
    {
      if (Save_Get(event_save_data).special.type == mEv_EVENT_SHOP_SALE) {
        return FALSE;
      }
    }

    // fallthrough case
    default:
    {
      
      break;
    }
  }
}
