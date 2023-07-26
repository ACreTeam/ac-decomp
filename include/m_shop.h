#ifndef M_SHOP_H
#define M_SHOP_H

#include "types.h"
#include "libu64/gfxprint.h"
#include "lb_rtc.h"
#include "m_personal_id.h"
#include "m_actor_type.h"
#include "game.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mSP_PERSONAL_ID_COUNT 10
#define mSP_GOODS_COUNT 39
#define mSP_LOTTERY_ITEM_COUNT 3

/* item list groups */
enum {
  mSP_LIST_A,                 /* A priority list */
  mSP_LIST_B,                 /* B priority list */
  mSP_LIST_C,                 /* C priority list */
  mSP_LIST_EVENT,             /* event list */
  mSP_LIST_TRAIN,             /*  */
  mSP_LIST_LOTTERY,           /* lottery list */
  mSP_LIST_HALLOWEEN,         /* halloween theme list */
  mSP_LIST_PRESENT,           /*  */
  mSP_LIST_CHRISTMAS,
  mSP_LIST_SNOW,
  mSP_LIST_HALLOWEEN2,
  mSP_LIST_JONASON,
  mSP_LIST_POSTOFFICE,
  mSP_LIST_NINTENDO64,
  mSP_LIST_SPECIALPRESENT,
  mSP_LIST_ISLAND,
  mSP_LIST_HOMEPAGE,
  mSP_LIST_EVENTPRESENTCHUMON,
  mSP_LIST_KAMAKURA,
  mSP_LIST_ISLANDFAMICOM,
  mSP_LIST_HARVEST,
  mSP_LIST_MARIO,
  mSP_LIST_TENT,
  mSP_LIST_DUMMY23,
  mSP_LIST_DUMMY24,
  mSP_LIST_DUMMY25,
  mSP_LIST_DUMMY26,
  mSP_LIST_DUMMY27,
  mSP_LIST_DUMMY28,
  mSP_LIST_DUMMY29,

  mSP_LIST_NUM
};

/* item List types */
enum {
  mSP_LISTTYPE_COMMON,            /* common ABC priority list */
  mSP_LISTTYPE_UNCOMMON,          /* uncommon ABC priority list */
  mSP_LISTTYPE_RARE,              /* rare ABC priority list */
  mSP_LISTTYPE_EVENT,             /* event list */
  mSP_LISTTYPE_TRAIN,             /*  */
  mSP_LISTTYPE_LOTTERY,           /* lottery list */
  mSP_LISTTYPE_HALLOWEEN,         /* halloween theme list */
  mSP_LISTTYPE_PRESENT,           /*  */
  mSP_LISTTYPE_ABC,               /* ABC */
  mSP_LISTTYPE_CHRISTMAS,
  mSP_LISTTYPE_SNOW,
  mSP_LISTTYPE_HALLOWEEN2,
  mSP_LISTTYPE_JONASON,
  mSP_LISTTYPE_POSTOFFICE,
  mSP_LISTTYPE_NINTENDO64,
  mSP_LISTTYPE_SPECIALPRESENT,
  mSP_LISTTYPE_ISLAND,
  mSP_LISTTYPE_HOMEPAGE,
  mSP_LISTTYPE_EVENTPRESENTCHUMON,
  mSP_LISTTYPE_KAMAKURA,
  mSP_LISTTYPE_ISLANDFAMICOM,
  mSP_LISTTYPE_HARVEST,
  mSP_LISTTYPE_MARIO,
  mSP_LISTTYPE_TENT,

  mSP_LISTTYPE_NUM
};

/* item list kinds */
enum {
  mSP_KIND_FURNITURE,
  mSP_KIND_PAPER,
  mSP_KIND_CLOTH,
  mSP_KIND_CARPET,
  mSP_KIND_WALLPAPER,

  mSP_KIND_MAX
};

/* sizeof(mSP_goods_priority_list_c) == 1 */
typedef struct shop_goods_priority_list_s {
  u8 a:2; /* list A rarity */
  u8 b:2; /* list B rarity */
  u8 c:2; /* list C rarity */
  u8 pad:2;
} mSP_goods_priority_list_c;

/* sizeof(Shop_c) == 0x140 */
typedef struct shop_s {
  /* 0x000 */ mSP_goods_priority_list_c priority_lists[mSP_KIND_MAX]; /* ABC list rarity (known internally as priority) */
  /* 0x006 */ PersonalID_c unused_ids[mSP_PERSONAL_ID_COUNT]; /* unused personal ids */
  /* 0x0CE */ mActor_name_t items[mSP_GOODS_COUNT]; /* standard shop items */
  /* 0x11C */ mActor_name_t rare_item; /* spotlight rare item taken from rare furniture ABC list */
  /* 0x11E */ mActor_name_t lottery_items[mSP_LOTTERY_ITEM_COUNT]; /* lottery items */
  /* 0x124 */ s8 flowers_candy_grab_bag_count; /* count of items that are flowers, candy, or grab bags */
  /* 0x126 */ struct {
    /* 0x126 */ u16 shop_level:2; /* shop type, 0 = Cranny, 1 = Nook 'n Go, 2 = Nookway, 3 = Nookington's */
    /* 0x126 */ u16 upgrading_today:1; /* enabled when the shop is 'undergoing renovations' */
    /* 0x126 */ u16 send_upgrade_notice:1; /* triggers the upgrade letter to be sent out */
    /* 0x126 */ u16 not_loaded_before:1; /* cleared when the shop actor has loaded for the first time in a play session */
    /* 0x126/0x127 */ u16 paint_color:4; /* paint bucket color being sold */
    /* 0x127 */ u16 unused:7; /* seems to be unused */
  } shop_info;
  /* 0x128 */ u32 sales_sum; /* current money towards upgrading shop */
  /* 0x12C */ lbRTC_time_c exchange_time; /* last time the shop's items were updated */
  /* 0x134 */ lbRTC_time_c renewal_time; /* last time the shop was 'renewed' which includes upgrading its 'level' */
  /* 0x13C */ int visitor_flag; /* set when a foreign player enters Nook's shop, required for Nookington's */
} Shop_c;

extern void mSP_PrintNowShopSalesSum(gfxprint_t* gfxprint);
extern void mSP_SelectRandomItem_New(GAME* unused, mActor_name_t* item_tbl, int item_tbl_count, mActor_name_t* goods_exist_tbl, int goods_exist_tbl_count, int category, int list_type, int get_uncollected_item);
extern void mSP_RandomUmbSelect(mActor_name_t* item_buf, int item_buf_count);
extern int mSP_GetShopLevel();
extern u32 mSP_ItemNo2ItemPrice(mActor_name_t item_no);
extern int mSP_SearchItemCategoryPriority(mActor_name_t item_no, int category, int priority, GAME* unused); // not sure if it's actually a GAME*
extern mActor_name_t mSP_RandomOneFossilSelect(int multi_fossil);

extern void mItemDebug_ItemDebugMain();
extern void mItemDebug_ItemDebugDraw(gfxprint_t* gfxprint);

#ifdef __cplusplus
}
#endif

#endif
