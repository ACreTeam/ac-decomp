#ifndef M_EVENT_H
#define M_EVENT_H

#include "types.h"
#include "libu64/gfxprint.h"
#include "m_time.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Event type definition
 *  xxxyyyyy yyyyyyyy yyyyyyyy yyyyyyyy
 * 
 *  x: event type (e.g. special event, 'first job' (chores) event, holidays, ...) (0-7)
 *  y: sub-type (specific event)
 **/

#define mEv_SUBTYPE_BITS 29
#define mEv_TYPE_BITMASK (0b111 << mEv_SUBTYPE_BITS)
#define mEv_SUBTYPE_BITMASK ((1 << mEv_SUBTYPE_BITS) - 1)

#define mEv_GET_TYPE(event) (((event) & mEv_TYPE_BITMASK) >> mEv_SUBTYPE_BITS)
#define mEv_SET_TYPE(t) (((t) << mEv_SUBTYPE_BITS) & mEv_TYPE_BITMASK)

#define mEv_GET_SUBTYPE(event) ((event) & mEv_SUBTYPE_BITMASK)
#define mEv_SET_SUBTYPE(s) ((s) & mEv_SUBTYPE_BITMASK)

#define mEv_SET(type, subtype) (mEv_SET_TYPE(type) | mEv_SET_TYPE(subtype))

enum event_type {
  mEv_SPNPC_EVENT, /* special NPC events */
  mEv_SAVED_EVENT, /* events saved to data */
  mEv_TYPE2_EVENT, /* unused? */
  mEv_TYPE3_EVENT, /* unused? */
  mEv_TYPE4_EVENT, /* unused? */
  mEv_DAILY_EVENT, /* checked daily always? aSL_ReportShopOpen2Event has event 3 */
  mEv_SPECL_EVENT, /* ??? secondary special npc event data? */

  mEv_EVENT_NUM
};

enum events {
  mEv_SPNPC_SHOP = (int)mEv_SET(mEv_SPNPC_EVENT, 0),
  mEv_SPNPC_DESIGNER,
  mEv_SPNPC_BROKER,
  mEv_SPNPC_ARTIST,
  mEv_SPNPC_ARABIAN,
  mEv_SPNPC_GYPSY,

  mEv_SAVED_RENEWSHOP = (int)mEv_SET(mEv_SAVED_EVENT, 0), /* renew shop */
  mEv_SAVED_UNK1, /* unused */
  
  /* intro through chores */
  mEv_SAVED_FIRSTJOB_PLR0,
  mEv_SAVED_FIRSTJOB_PLR1,
  mEv_SAVED_FIRSTJOB_PLR2,
  mEv_SAVED_FIRSTJOB_PLR3,

  /* selecting house */
  mEv_SAVED_FIRSTINTRO_PLR0,
  mEv_SAVED_FIRSTINTRO_PLR1,
  mEv_SAVED_FIRSTINTRO_PLR2,
  mEv_SAVED_FIRSTINTRO_PLR3,

  /* wait for next day to talk about HRA */
  mEv_SAVED_HRAWAIT_PLR0,
  mEv_SAVED_HRAWAIT_PLR1,
  mEv_SAVED_HRAWAIT_PLR2,
  mEv_SAVED_HRAWAIT_PLR3,

  /* Nook will talk about HRA when entering the shop */
  mEv_SAVED_HRATALK_PLR0,
  mEv_SAVED_HRATALK_PLR1,
  mEv_SAVED_HRATALK_PLR2,
  mEv_SAVED_HRATALK_PLR3,

  /* Do a 'favor' for a villager during chores */
  mEv_SAVED_FJOPENQUEST_PLR0,
  mEv_SAVED_FJOPENQUEST_PLR1,
  mEv_SAVED_FJOPENQUEST_PLR2,
  mEv_SAVED_FJOPENQUEST_PLR3,

  /* Player going to another town, set at train station */
  mEv_SAVED_GATEWAY_PLR0,
  mEv_SAVED_GATEWAY_PLR1,
  mEv_SAVED_GATEWAY_PLR2,
  mEv_SAVED_GATEWAY_PLR3,
  mEv_SAVED_GATEWAY_FRGN, /* Foreigner */

  mEv_DAILY_0 = (int)mEv_SET(mEv_DAILY_EVENT, 0), /* unused */
  mEv_DAILY_1, /* unused */
  mEv_DAILY_2, /* unused */
  mEv_DAILY_OPEN_SHOP, /* shop opened */

  mEv_SPECL_DESIGNER_COMPLETE = (int)mEv_SET(mEv_SPECL_EVENT, 0)
};

enum week_type {
  mEv_WEEKTYPE_NONE,
  mEv_WEEKTYPE_1ST,
  mEv_WEEKTYPE_2ND,
  mEv_WEEKTYPE_3RD,
  mEv_WEEKTYPE_4TH,
  mEv_WEEKTYPE_5TH,
  mEv_WEEKTYPE_LAST,
  mEv_WEEKTYPE_SPECIAL
};

enum event_table {
  mEv_EVENT_FISHING_TOURNEY_1 = 29,
  mEv_EVENT_MUSHROOM_SEASON = 47,
  mEv_EVENT_FISHING_TOURNEY_2 = 54,
  mEv_EVENT_GHOST = 64,
};

#define mEv_STATUS_ACTIVE     (1 << 0) /* event is active */
#define mEv_STATUS_STOP       (1 << 1) /* event is stopped */
#define mEv_STATUS_SHOW       (1 << 2) /* event is shown */
#define mEv_STATUS_PLAYSOUND  (1 << 3) /* event should play sound */
#define mEv_STATUS_RUN        (1 << 4) /* event should run */
#define mEv_STATUS_ERROR      (1 << 5) /* event is in error state */
#define mEv_STATUS_TALK       (1 << 6) /* event requires talking to player */

#define mEv_GHOST_HITODAMA_NUM 5
typedef struct ghost_spirit_block_data_s {
  u8 block_x[mEv_GHOST_HITODAMA_NUM];
  u8 block_z[mEv_GHOST_HITODAMA_NUM];
} mEv_gst_hitodama_block_c;

#define mEv_GHOST_FLAG_ACTIVE 0x4000 // TODO: do these live in the ghost actor itself?
typedef struct ghost_common_s {
  mEv_gst_hitodama_block_c hitodama_block_data;
  u16 flags;
  u8 _0C[0x2C - 0x0C];
} mEv_gst_common_c;

extern int mEv_CheckFirstJob();
extern int mEv_CheckArbeit();
extern int mEv_CheckTitleDemo();
extern int mEv_check_status(int event, s16 status);
extern s8* mEv_get_common_area(int type, s8 id);

extern int mEv_weekday2day(lbRTC_month_t month, int week_type, lbRTC_weekday_t weekday);
extern void mEv_ClearEventInfo();

extern int mEv_CheckTitleDemo();
extern void mEv_SetTitleDemo(int titledemo_no);

extern void mEv_debug_print4f(gfxprint_t* gfxprint);
extern void mEv_sp_debug_print4f(gfxprint_t* gfxprint);

#ifdef __cplusplus
}
#endif

#endif
