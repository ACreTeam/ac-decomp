#ifndef M_SHOP_H
#define M_SHOP_H

#include "types.h"
#include "libu64/gfxprint.h"
#include "lb_rtc.h"
#include "m_personal_id.h"
#include "m_actor_type.h"
#include "game.h"
#include "m_item_debug.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mSP_PERSONAL_ID_COUNT 10
#define mSP_GOODS_COUNT 39
#define mSP_LOTTERY_ITEM_COUNT 3

#define mSP_SIGNBOARD_PRICE 500
#define mSP_FOREIGN_FRUIT_PRICE 2000

#define mSP_NET_SALES_SUM  3000 // minimum sales sum before net appears (Nook's Cranny only)
#define mSP_ROD_SALES_SUM  8000 // minimum sales sum before rod appears (Nook's Cranny only)
#define mSP_AXE_SALES_SUM 12000 // minimum sales sum before axe appears (Nook's Cranny only)

#define mSP_COMBINI_SUM 25000 // sales sum for upgrading to Nook 'n' Go
#define mSP_SUPER_SUM   90000 // sales sum for upgrading to Nookway
#define mSP_DSUPER_SUM 240000 // sales sum for upgrading to Nookington's

enum {
  mSP_ROOF_COLOR_RED,
  mSP_ROOF_COLOR_ORANGE,
  mSP_ROOF_COLOR_YELLOW,
  mSP_ROOF_COLOR_PALE_GREEN,
  mSP_ROOF_COLOR_GREEN,
  mSP_ROOF_COLOR_SKY_BLUE,
  mSP_ROOF_COLOR_BLUE,
  mSP_ROOF_COLOR_PURPLE,
  mSP_ROOF_COLOR_PINK,
  mSP_ROOF_COLOR_BLACK,
  mSP_ROOF_COLOR_WHITE,
  mSP_ROOF_COLOR_BROWN,

  mSP_ROOF_COLOR_NUM
};

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
  mSP_KIND_DIARY,

  mSP_KIND_MAX = mSP_KIND_DIARY,
  mSP_KIND_EXTENDED_MAX /* includes diary */
};

enum {
  mSP_PRIORITY_COMMON,
  mSP_PRIORITY_UNCOMMON,
  mSP_PRIORITY_RARE,

  mSP_PRIORITY_NUM
};

enum {
  mSP_CLOTH_SEASON_ANY,
  mSP_CLOTH_SEASON_SPRING,
  mSP_CLOTH_SEASON_SUMMER,
  mSP_CLOTH_SEASON_AUTUMN,
  mSP_CLOTH_SEASON_WINTER,

  mSP_CLOTH_SEASON_NUM
};

enum {
  mSP_GOODS_TYPE_PAPER,
  mSP_GOODS_TYPE_CLOTH,
  mSP_GOODS_TYPE_FTR,
  mSP_GOODS_TYPE_RARE_FTR,
  mSP_GOODS_TYPE_CARPET,
  mSP_GOODS_TYPE_WALL,
  mSP_GOODS_TYPE_6,
  mSP_GOODS_TYPE_7,
  mSP_GOODS_TYPE_SAPLING,
  mSP_GOODS_TYPE_TOOL,
  mSP_GOODS_TYPE_PLANT,

  mSP_GOODS_TYPE_NUM
};

enum {
  mSP_SHOP_TYPE_ZAKKA,
  mSP_SHOP_TYPE_COMBINI,
  mSP_SHOP_TYPE_SUPER,
  mSP_SHOP_TYPE_DSUPER,

  mSP_SHOP_TYPE_NUM
};

enum {
  mSP_SHOP_STATUS_PRE,
  mSP_SHOP_STATUS_END,
  mSP_SHOP_STATUS_OPEN,
  mSP_SHOP_STATUS_RENEW,
  mSP_SHOP_STATUS_PREEVENT,
  mSP_SHOP_STATUS_ENDEVENT,
  mSP_SHOP_STATUS_OPENEVENT,

  mSP_SHOP_STATUS_NUM
};

enum {
  mSP_TANUKI_SHOP_STATUS_NORMAL,
  mSP_TANUKI_SHOP_STATUS_EVENT,
  mSP_TANUKI_SHOP_STATUS_HALLOWEEN,
  mSP_TANUKI_SHOP_STATUS_FUKUBIKI,
  mSP_TANUKI_SHOP_STATUS_HUKUBUKURO_SALE,

  mSP_TANUKI_SHOP_STATUS_NUM
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

#define mSP_GC_FAMICOM_TABLE_CNT 8 // update this if the # of items in mSP_gc_famicom_table is changed
extern mActor_name_t mSP_gc_famicom_table[];

extern int mSP_CollectCheck(mActor_name_t item);
extern void mSP_SelectRandomItem_New(GAME* game, mActor_name_t* goods_table, int goods_count, mActor_name_t* goods_exist_table, int goods_exist_count, int category, int list_type, int uncollected_only);
extern int mSP_ShopSaleReport(mActor_name_t sold_item, mActor_name_t* goods_table, int goods_count, mActor_name_t rsv_item);
extern u32 mSP_ItemNo2ItemPrice(mActor_name_t item_no);
extern int mSP_SearchItemCategoryPriority(mActor_name_t item_no, int category, int list_type, GAME* game);
extern int mSP_CountElementInGoodsList();
extern int mSP_CheckExchangeDay2();
extern int mSP_CheckExchangeMonth();
extern void mSP_NewExchangeDay();
extern void mSP_ShopItsumoChirashi(int house_no, int shop_level, mActor_name_t item, int type, int send_proc);
extern void mSP_SetShopRareFurnitureChirashi(int player_no, mActor_name_t* goods_list, int goods_count, GAME* game);
extern void mSP_SetRenewalChiraswhi_AppoDay();
extern void mSP_ExchangeLineUp_InGame(GAME* game);
extern void mSP_PlusSales(u32 sum);
extern int mSP_SetNewVisitor();
extern u32 mSP_GetSalesSum();
extern int mSP_GetShopLevel();
extern int mSP_RenewShopLevel();
extern int mSP_GetRealShopLevel();
extern int mSP_GetGoodsPercent(int priority);
extern void mSP_PrintNowShopSalesSum(gfxprint_t* gfxprint);
extern void mSP_GetGoodsPriority(u8* abc_priorities, int category);
extern void mSP_ExchangeLineUp_ZeldaMalloc();
extern void mSP_LotteryLineUp_ZeldaMalloc();
extern void mSP_ExchangeLineUp_GameAlloc(GAME* game);
extern void mSP_LotteryLineUp_GameAlloc(GAME* game);
extern void mSP_InitShopSaveData();
extern void mSP_ShopGameStartCt(GAME* game);
extern mActor_name_t mSP_GetNowShopBgNum();
extern int mSP_WhatSpecialSale();
extern mActor_name_t mSP_GetNowShopFgNum();
extern lbRTC_hour_t mSP_GetShopOpenTime();
extern lbRTC_hour_t mSP_GetShopCloseTime();
extern lbRTC_hour_t mSP_GetShopCloseTime_Bgm();
extern int mSP_InRenewal();
extern int mSP_ShopOpen();
extern void mSP_RandomHaniwaSelect(mActor_name_t* haniwa_list, int count);
extern void mSP_RandomMDSelect(mActor_name_t* md_list, int count);
extern void mSP_RandomUmbSelect(mActor_name_t* umb_list, int count);
extern mActor_name_t mSP_RandomOneFossilSelect(int multi_fossil);
extern int mSP_Chk_HukubukuroSail();
extern int mSP_CheckFukubikiDay();
extern int mSP_SetGoods2ReservedPoint(mActor_name_t goods, mActor_name_t reserved_no);
extern int mSP_CheckHallowinDay();
extern void mSP_SetTanukiShopStatus();
extern int mSP_money_check(u32 amount);
extern void mSP_get_sell_price(u32 amount);
extern mActor_name_t mSP_SelectFishginPresent(int player_no);
extern void mSP_SelectRandomItemToAGB();
extern const char* mSP_ShopStatus2String(int status);
extern mActor_name_t mSP_GetRandomStationToyItemNo();

#ifdef __cplusplus
}
#endif

#endif
