#ifndef M_CALENDAR_OVL_H
#define M_CALENDAR_OVL_H

#include "types.h"
#include "m_calendar_ovl_h.h"
#include "m_submenu_ovl.h"
#include "m_calendar.h"
#include "m_string.h"
#include "m_font.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mCD_YEARS_SHOWN 3
#define mCD_EVENT_NAME_STR_LEN 16

enum {
    mCD_STICK_AREA_LEFT,
    mCD_STICK_AREA_TOP_LEFT,
    mCD_STICK_AREA_TOP,
    mCD_STICK_AREA_TOP_RIGHT,
    mCD_STICK_AREA_RIGHT,
    mCD_STICK_AREA_BOTTOM_RIGHT,
    mCD_STICK_AREA_BOTTOM,
    mCD_STICK_AREA_BOTTOM_LEFT,
    mCD_STICK_AREA_CENTER,
  
    mCD_STICK_AREA_NUM
};

enum {
    mCD_MVPL_SELECT,
    mCD_MVPL_MV0,
    mCD_MVPL_MV1,
    mCD_MVPL_CHG0,
    mCD_MVPL_CHG1,
    mCD_MVPL_DAY,
    mCD_MVPL_ESCAPE,
    mCD_MVPL_ENTRANCE,

    mCD_MVPL_NUM
};

#define mCD_DAY_NONE (0) // day panel not enabled, part of previous or next month
#define mCD_DAY_NORMAL (1) // regular day
#define mCD_DAY_FIRST_OF_WEEK (2) // first day of the week (Sunday)
#define mCD_DAY_EVENT (3) // event present on this day
#define mCD_DAY_CURRENT (4) // current day
#define mCD_DAY_UNDEFINED (5) // invalid/unset

// TODO: fill out the rest of these struct fields with proper names

typedef struct calendar_month_entry_s {
    u8 day_data[37];
    u8 _25[37];
    u8 _4A[lbRTC_MONTHS_MAX][2];
    u8 _62[16];
    u8 _72;
} mCD_month_entry_c;

struct calendar_ovl_s {
    mCD_month_entry_c month_entries[mCD_YEARS_SHOWN * lbRTC_MONTHS_MAX];
    f32 _102C;
    f32 _1030;
    f32 _1034;
    f32 _1038;
    u8 _103C[6];
    u8 _1042;
    u8 _1043;
    u8 event_name_str[mCD_EVENT_NAME_STR_LEN];
    u8 _1054;
    u8 move_proc_idx;
    u8 _1056;
    u8 _1057;
    u8 day_type;
    u8 _1059;
    u8 _105A;
    u8 stick_area;
    u8 _105C;
    u8 _105D;
    u8 _105E;
    u8 _105F;
};

extern void mCD_calendar_ovl_construct(Submenu* submenu);
extern void mCD_calendar_ovl_destruct(Submenu* submenu);
extern void mCD_calendar_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
