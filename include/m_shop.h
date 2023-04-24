#ifndef M_SHOP_H
#define M_SHOP_H

#include "types.h"
#include "libu64/gfxprint.h"
#include "lb_rtc.h"
#include "m_personal_id.h"
#include "m_actor_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mSP_PERSONAL_ID_COUNT 10
#define mSP_GOODS_COUNT 39
#define mSP_LOTTERY_ITEM_COUNT 3

enum {
  mSP_LIST_FURNITURE,
  mSP_LIST_PAPER,
  mSP_LIST_CLOTH,
  mSP_LIST_CARPET,
  mSP_LIST_WALLPAPER,

  mSP_LIST_MAX
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
  /* 0x000 */ mSP_goods_priority_list_c priority_lists[mSP_LIST_MAX]; /* ABC list rarity (known internally as priority) */
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

extern void mItemDebug_ItemDebugMain();
extern void mItemDebug_ItemDebugDraw(gfxprint_t* gfxprint);

#ifdef __cplusplus
}
#endif

#endif
