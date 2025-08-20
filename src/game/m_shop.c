#include "m_shop.h"

#include "game.h"
#include "m_cockroach.h"
#include "m_collision_bg.h"
#include "m_common_data.h"
#include "m_event.h"
#include "m_handbill.h"
#include "m_house.h"
#include "m_item_name.h"
#include "m_name_table.h"
#include "m_room_type.h"
#include "m_fg_type.h"

extern mActor_name_t* mSP_ftr_list[];
extern mActor_name_t* mSP_binsen_list[];
extern mActor_name_t* mSP_cloth_list[];
extern mActor_name_t* mSP_carpet_list[];
extern mActor_name_t* mSP_wall_list[];

static mActor_name_t diary_listA[6] = { ITM_DIARY01, ITM_DIARY04, ITM_DIARY07, ITM_DIARY10, ITM_DIARY13, EMPTY_NO };

static mActor_name_t diary_listB[6] = { ITM_DIARY02, ITM_DIARY05, ITM_DIARY08, ITM_DIARY11, ITM_DIARY14, EMPTY_NO };

static mActor_name_t diary_listC[7] = { ITM_DIARY03, ITM_DIARY06, ITM_DIARY09, ITM_DIARY12,
                                        ITM_DIARY15, ITM_DIARY00, EMPTY_NO };

static mActor_name_t* mSP_diary_list[mSP_LIST_NUM] = { diary_listA, diary_listB, diary_listC, NULL, NULL, NULL,
                                                       NULL,        NULL,        NULL,        NULL, NULL, NULL,
                                                       NULL,        NULL,        NULL,        NULL, NULL, NULL,
                                                       NULL,        NULL,        NULL,        NULL, NULL };

static mActor_name_t** mSP_goods_seg_inf[mSP_KIND_EXTENDED_MAX] = { mSP_ftr_list,    mSP_binsen_list, mSP_cloth_list,
                                                                    mSP_carpet_list, mSP_wall_list,   mSP_diary_list };

static void mSP_InitItemTable(mActor_name_t* item_table, int count) {
    int i;

    if (item_table == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        *item_table++ = EMPTY_NO;
    }
}

static mActor_name_t* mSP_SelectListFromPriority(mActor_name_t** lists, u8* priorities, int list_type) {
    mActor_name_t* list = NULL;

    switch (list_type) {
        case mSP_LISTTYPE_EVENT:
            list = lists[mSP_LIST_EVENT];
            break;
        case mSP_LISTTYPE_TRAIN:
            list = lists[mSP_LIST_TRAIN];
            break;
        case mSP_LISTTYPE_LOTTERY:
            list = lists[mSP_LIST_LOTTERY];
            break;
        case mSP_LISTTYPE_HALLOWEEN:
            list = lists[mSP_LIST_HALLOWEEN];
            break;
        case mSP_LISTTYPE_HALLOWEEN2:
            list = lists[mSP_LIST_HALLOWEEN2];
            break;
        case mSP_LISTTYPE_PRESENT:
            list = lists[mSP_LIST_PRESENT];
            break;
        case mSP_LISTTYPE_CHRISTMAS:
            list = lists[mSP_LIST_CHRISTMAS];
            break;
        case mSP_LISTTYPE_SNOW:
            list = lists[mSP_LIST_SNOW];
            break;
        case mSP_LISTTYPE_JONASON:
            list = lists[mSP_LIST_JONASON];
            break;
        case mSP_LISTTYPE_POSTOFFICE:
            list = lists[mSP_LIST_POSTOFFICE];
            break;
        case mSP_LISTTYPE_NINTENDO64:
            list = lists[mSP_LIST_NINTENDO64];
            break;
        case mSP_LISTTYPE_SPECIALPRESENT:
            list = lists[mSP_LIST_SPECIALPRESENT];
            break;
        case mSP_LISTTYPE_ISLAND:
            list = lists[mSP_LIST_ISLAND];
            break;
        case mSP_LISTTYPE_ISLANDFAMICOM:
            list = lists[mSP_LIST_ISLANDFAMICOM];
            break;
        case mSP_LISTTYPE_HOMEPAGE:
            list = lists[mSP_LIST_HOMEPAGE];
            break;
        case mSP_LISTTYPE_EVENTPRESENTCHUMON:
            list = lists[mSP_LIST_EVENTPRESENTCHUMON];
            break;
        case mSP_LISTTYPE_KAMAKURA:
            list = lists[mSP_LIST_KAMAKURA];
            break;
        case mSP_LISTTYPE_HARVEST:
            list = lists[mSP_LIST_HARVEST];
            break;
        case mSP_LISTTYPE_MARIO:
            list = lists[mSP_LIST_MARIO];
            break;
        case mSP_LISTTYPE_TENT:
            list = lists[mSP_LIST_TENT];
            break;

        case mSP_LISTTYPE_ABC:
        default: {
            int i;

            for (i = 0; i < 3; i++, priorities++) {
                if (list_type == priorities[0]) {
                    switch (i) {
                        case mSP_LISTTYPE_COMMON:
                            list = lists[mSP_LIST_A];
                            break;
                        case mSP_LISTTYPE_UNCOMMON:
                            list = lists[mSP_LIST_B];
                            break;
                        case mSP_LISTTYPE_RARE:
                            list = lists[mSP_LIST_C];
                            break;
                    }
                }
            }
            break;
        }
    }

    if (list == NULL) {
        list = lists[mSP_LIST_A];
    }

    return list;
}

static void mSP_SetSeasonFTR_local_december(mActor_name_t* item_table, int count, mActor_name_t ftr0,
                                            mActor_name_t ftr1) {
    if (count > 1) {
        item_table[0] = ftr0;
        item_table[1] = ftr1;
    } else if (fqrand() < 0.5f) {
        item_table[0] = ftr0;
    } else {
        item_table[0] = ftr1;
    }
}

static void mSP_SetSeasonFTR(mActor_name_t* item_table, int count) {
    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
    lbRTC_month_t month = rtc_time.month;
    lbRTC_day_t day = rtc_time.day;

    if (count > 0 && month == lbRTC_DECEMBER) {

        if (day <= 24) {
            mSP_SetSeasonFTR_local_december(item_table, count, FTR_START(FTR_NOG_XTREE), FTR_START(FTR_KON_XTREE02));
        } else if (day >= 26) {
            mSP_SetSeasonFTR_local_december(item_table, count, FTR_START(FTR_YAZ_CANDLE), FTR_START(FTR_YOS_KFLAG));
        }
    }
}

static mActor_name_t* mSP_GetItemList(mActor_name_t** lists, u8* priorities, int list_type) {
    if (list_type == mSP_LISTTYPE_ABC) {
        int abc_roll = RANDOM(100);
        int goods_power = mPr_GetGoodsPower();
        int rare_chance;
        int uncommon_chance;

        if (goods_power < 0) {
            uncommon_chance = goods_power + 40; /* [10%, 39%] */
            rare_chance = 5;                    /* always 5% chance */
                                                /* common_chance = [85%, 66%] */
        } else {
            rare_chance = goods_power + 5;      /* [5%, 55%] */
            uncommon_chance = rare_chance + 35; /* always 35% chance */
                                                /* common_chance = [60%, 10%]*/
        }

        if (abc_roll < rare_chance) {
            return mSP_SelectListFromPriority(lists, priorities, mSP_LISTTYPE_RARE);
        } else if (abc_roll < uncommon_chance) {
            return mSP_SelectListFromPriority(lists, priorities, mSP_LISTTYPE_UNCOMMON);
        } else {
            return mSP_SelectListFromPriority(lists, priorities, mSP_LISTTYPE_COMMON);
        }
    } else {
        return mSP_SelectListFromPriority(lists, priorities, list_type);
    }
}

static int mSP_GoodsExistAlready(mActor_name_t* goods_table, int count, mActor_name_t item) {
    int i;

    if (goods_table != NULL) {
        for (i = 0; i < count; i++) {
            if (goods_table[i] == item) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

extern int mSP_CollectCheck(mActor_name_t item) {
    mActor_name_t ftr_item = mRmTp_Item1ItemNo2FtrItemNo_AtPlayerRoom(item, FALSE);
    u32* bitfield;
    int idx;

    bitfield = NULL;

    switch (ITEM_NAME_GET_TYPE(ftr_item)) {
        case NAME_TYPE_FTR0:
        case NAME_TYPE_FTR1: {
            bitfield = Common_Get(now_private)->furniture_collected_bitfield;
            idx = mRmTp_FtrItemNo2FtrIdx(ftr_item);
            break;
        }

        case NAME_TYPE_ITEM1: {
            switch (ITEM_NAME_GET_CAT(ftr_item)) {
                case ITEM1_CAT_PAPER: {
                    bitfield = Common_Get(now_private)->paper_collected_bitfield;
                    idx = (ftr_item - ITM_PAPER_START) % PAPER_UNIQUE_NUM;
                    break;
                }

                case ITEM1_CAT_WALL: {
                    bitfield = Common_Get(now_private)->wall_collected_bitfield;
                    idx = ftr_item - ITM_WALL_START;
                    break;
                }

                case ITEM1_CAT_CARPET: {
                    bitfield = Common_Get(now_private)->carpet_collected_bitfield;
                    idx = ftr_item - ITM_CARPET_START;
                    break;
                }

                case ITEM1_CAT_MINIDISK: {
                    bitfield = Common_Get(now_private)->music_collected_bitfield;
                    idx = (mActor_name_t)(ftr_item - ITM_MINIDISK_START);
                    break;
                }
            }

            break;
        }
    }

    if (bitfield == NULL) {
        return FALSE;
    }

    return ((1 << (idx & 0x1F)) & bitfield[idx >> 5]) != 0;
}

static int mSP_CountElementInCommonList(mActor_name_t* list) {
    int count = 0;

    for (list; list[0] != EMPTY_NO; list++, count++) {}

    return count;
}

static int mSP_CountElementInCommonList_collect(mActor_name_t* list, int* selected_idx, int uncollected_only) {
    int count = 0;
    int selected;
    mActor_name_t* list_p;

    if (uncollected_only == FALSE) {
        count = mSP_CountElementInCommonList(list);
        selected_idx[0] = RANDOM(count);

        return count;
    }

    /* Count all uncollected items in the list */
    for (list_p = list; list_p[0] != EMPTY_NO; list_p++) {
        if (mSP_CollectCheck(list_p[0]) == FALSE) {
            count++;
        }
    }

    if (count == 0) {
        selected_idx[0] = 0;
        return 0;
    }

    selected = RANDOM(count);
    selected_idx[0] = 0;
    for (list_p = list; list_p[0] != EMPTY_NO && selected > 0; list_p++) {
        if (mSP_CollectCheck(list_p[0]) == FALSE) {
            selected--;
        }

        selected_idx[0]++;
    }

    return count;
}

static int mSP_get_cloth_season() {
    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
    lbRTC_month_t month = rtc_time.month;
    int res;

    switch (month) {
        case lbRTC_JANUARY:
            res = mSP_CLOTH_SEASON_WINTER;
            break;

        case lbRTC_FEBRUARY: {
            if (rtc_time.day > 24) {
                res = mSP_CLOTH_SEASON_SPRING;
            } else {
                res = mSP_CLOTH_SEASON_WINTER;
            }

            break;
        }

        case lbRTC_MARCH:
        case lbRTC_APRIL:
            res = mSP_CLOTH_SEASON_SPRING;
            break;

        case lbRTC_MAY: {
            if (rtc_time.day > 26) {
                res = mSP_CLOTH_SEASON_SUMMER;
            } else {
                res = mSP_CLOTH_SEASON_SPRING;
            }

            break;
        }

        case lbRTC_JUNE:
        case lbRTC_JULY:
            res = mSP_CLOTH_SEASON_SUMMER;
            break;

        case lbRTC_AUGUST: {
            if (rtc_time.day > 26) {
                res = mSP_CLOTH_SEASON_AUTUMN;
            } else {
                res = mSP_CLOTH_SEASON_SUMMER;
            }

            break;
        }

        case lbRTC_SEPTEMBER:
        case lbRTC_OCTOBER:
            res = mSP_CLOTH_SEASON_AUTUMN;
            break;

        case lbRTC_NOVEMBER: {
            if (rtc_time.day > 26) {
                res = mSP_CLOTH_SEASON_WINTER;
            } else {
                res = mSP_CLOTH_SEASON_AUTUMN;
            }

            break;
        }

        case lbRTC_DECEMBER:
            res = mSP_CLOTH_SEASON_WINTER;
            break;
    }

    return res;
}

extern u8 cloth_season_cnt[];

static int mSP_CountElementInClothList(int* selected) {
    u8* count_p = cloth_season_cnt;
    int cloth_season = mSP_get_cloth_season();
    int cloth_count = count_p[mSP_CLOTH_SEASON_ANY] + count_p[cloth_season];

    selected[0] = RANDOM(cloth_count); // random cloth selected

    if (selected[0] >= cloth_season_cnt[mSP_CLOTH_SEASON_ANY]) {
        int i;

        /* seasonal cloths are sequential in the item lists, so add previous season counts to the selected index */
        for (i = mSP_CLOTH_SEASON_SPRING; i < cloth_season; i++) {
            selected[0] += count_p[i];
        }
    }

    return cloth_count;
}

static int mSP_CountElementInClothList_collect(mActor_name_t* list, int* selected, int uncollected_only) {
    u8* count_p = cloth_season_cnt;

    if (uncollected_only == FALSE) {
        return mSP_CountElementInClothList(selected);
    } else {
        int cloth_season;
        int count;
        mActor_name_t* list_p;
        mActor_name_t* list_p2;
        int uncollected_num;
        int n;
        int s;
        int i;
        cloth_season = mSP_get_cloth_season();
        uncollected_num = 0;
        count = 0;

        for (list_p = list; count < count_p[mSP_CLOTH_SEASON_ANY] && list_p != NULL; list_p++) {
            if (mSP_CollectCheck(list_p[0]) == FALSE) {
                uncollected_num++;
            }

            count++;
        }

        n = count_p[mSP_CLOTH_SEASON_ANY];
        for (i = mSP_CLOTH_SEASON_SPRING; i < cloth_season; i++) {
            n += count_p[i]; // add intermediate season counts
        }

        i = n;
        s = n + count_p[cloth_season];
        list_p2 = list + (int)n;
        for (list_p = list_p2; i < s && list_p != NULL; list_p++) {
            if (mSP_CollectCheck(list_p[0]) == FALSE) {
                uncollected_num++;
            }

            i++;
        }

        if (uncollected_num == 0) {
            selected[0] = 0;
            return 0;
        } else {
            int selected_idx = RANDOM(uncollected_num);

            count = 0;
            selected[0] = 0;
            for (list; count < count_p[mSP_CLOTH_SEASON_ANY] && list != NULL && selected_idx > 0; list++) {
                if (mSP_CollectCheck(list[0]) == FALSE) {
                    selected_idx--;
                }

                selected[0]++;
                count++;
            }

            i = n;
            for (list_p2; i < s && list_p2 != NULL && selected_idx > 0; list_p2++) {
                if (mSP_CollectCheck(list_p2[0]) == FALSE) {
                    selected_idx--;
                }

                selected[0]++;
                i++;
            }
        }

        return uncollected_num;
    }
}

static int mSP_NoList(mActor_name_t* items_table, int count, mActor_name_t* list) {
    if (list == NULL) {
        int i;

        for (i = 0; i < count; i++) {
            items_table[0] = EMPTY_NO;
            items_table++;
        }

        return TRUE;
    }

    return FALSE;
}

static void mSP_SetDummyItem(mActor_name_t* items_table, int count, int kind) {
    mActor_name_t dummy_table[mSP_KIND_EXTENDED_MAX] = {
        FTR_START(FTR_SUM_CLCHEST03), ITM_PAPER00, ITM_CLOTH000, ITM_CARPET00, ITM_WALL00, ITM_DIARY00
    };

    mActor_name_t dummy_item = dummy_table[kind];
    int i;

    for (i = 0; i < count; i++) {
        items_table[i] = dummy_item;
    }
}

extern void mSP_SelectRandomItem_New(GAME* game, mActor_name_t* goods_table, int goods_count,
                                     mActor_name_t* goods_exist_table, int goods_exist_count, int category,
                                     int list_type, int uncollected_only) {
    mSP_InitItemTable(goods_table, goods_count);

    if (goods_count != 0 && goods_table != NULL) {
        if (goods_table != NULL) {
            u8 abc_priorities[3];
            mActor_name_t** goods_seg_p = mSP_goods_seg_inf[category];
            int i = 0;

            mSP_GetGoodsPriority(abc_priorities, category);

            while (i < goods_count) {
                mActor_name_t* item_list_p = mSP_GetItemList(goods_seg_p, abc_priorities, list_type);
                int list_item_count;
                int selected_idx;

                if (mSP_NoList(goods_table, goods_count, item_list_p) != FALSE) {
                    mSP_SetDummyItem(goods_table, goods_count, category);
                    return;
                }

                if (category == mSP_KIND_CLOTH && (list_type == mSP_LISTTYPE_ABC || list_type == mSP_LIST_A ||
                                                   list_type == mSP_LIST_B || list_type == mSP_LIST_C)) {
                    list_item_count = mSP_CountElementInClothList_collect(item_list_p, &selected_idx, uncollected_only);
                } else {
                    list_item_count =
                        mSP_CountElementInCommonList_collect(item_list_p, &selected_idx, uncollected_only);
                }

                if (list_item_count == 0) {
                    mSP_InitItemTable(goods_table, goods_count);
                    return;
                }

                if (mSP_GoodsExistAlready(goods_table, goods_count, item_list_p[selected_idx]) == FALSE &&
                    mSP_GoodsExistAlready(goods_exist_table, goods_exist_count, item_list_p[selected_idx]) == FALSE &&
                    Save_Get(shop).rare_item != item_list_p[selected_idx]) {
                    goods_table[i] = item_list_p[selected_idx];
                    i++;
                } else if (list_item_count < goods_count + goods_exist_count) {
                    /* forcibly add duplicate items if the list size is less than total possible goods */
                    goods_table[i] = item_list_p[selected_idx];
                    i++;
                }
            }
        } else {
            mSP_SetDummyItem(goods_table, goods_count, category); // ?????
        }
    }
}

static int mSP_CountPriceTableElement(u16* price_table) {
    int n = 0;

    while (price_table[0] != 0xFFFF) {
        price_table++;
        n++;
    }

    return n;
}

extern int mSP_ShopSaleReport(mActor_name_t sold_item, mActor_name_t* goods_table, int goods_count,
                              mActor_name_t rsv_item) {
    int i;

    if (sold_item == ITM_HUKUBUKURO_BAG) {
        Save_Get(shop).flowers_candy_grab_bag_count--;
        return FALSE;
    }

    if (sold_item == ITM_FOOD_CANDY) {
        Save_Get(shop).flowers_candy_grab_bag_count--;
        return FALSE;
    }

    for (i = 0; i < goods_count; i++) {
        if (sold_item == goods_table[i]) {
            goods_table[i] = rsv_item;
            return FALSE;
        }
    }

    if (sold_item == Save_Get(shop).rare_item) {
        Save_Get(shop).rare_item = rsv_item;
        return FALSE;
    }

    return FALSE;
}

extern u16 binsen_price_table[];
extern u16 cloth_price_table[];
extern u16 carpet_price_table[];
extern u16 wall_price_table[];
extern u16 tool_price_table[];
extern u16 plant_price_table[];
extern u16 food_price_table[];
extern u16 fish_price_table[];
extern u16 md_price_table[];
extern u16 diary_price_table[];
extern u16 insect_price_table[];

static u16* l_binsen_price_info = binsen_price_table;
static u16* l_cloth_price_info = cloth_price_table;
static u16* l_carpet_price_info = carpet_price_table;
static u16* l_wall_price_info = wall_price_table;
static u16* l_tool_price_info = tool_price_table;
static u16* l_plant_price_info = plant_price_table;
static u16* l_food_price_info = food_price_table;
static u16* l_fish_price_info = fish_price_table;
static u16* l_md_price_info = md_price_table;
static u16* l_diary_price_info = diary_price_table;
static u16* l_insect_price_info = insect_price_table;

static u16** l_price_info[ITEM1_CAT_NUM] = { &l_binsen_price_info,
                                             NULL,
                                             &l_tool_price_info,
                                             &l_fish_price_info,
                                             &l_cloth_price_info,
                                             NULL,
                                             &l_carpet_price_info,
                                             &l_wall_price_info,
                                             &l_food_price_info,
                                             &l_plant_price_info,
                                             &l_md_price_info,
                                             &l_diary_price_info,
                                             NULL,
                                             &l_insect_price_info,
                                             NULL,
                                             NULL };

static mActor_name_t mSP_item1_start_idx_table[ITEM1_CAT_NUM] = {
    ITM_PAPER_START,  ITM_MONEY_START,  ITM_TOOL_START,       ITM_FISH_START, ITM_CLOTH_START,    ITM_ETC_START,
    ITM_CARPET_START, ITM_WALL_START,   ITM_FOOD_START,       ITM_ENV_START,  ITM_MINIDISK_START, ITM_DIARY_START,
    ITM_TICKET_START, ITM_INSECT_START, ITM_HUKUBUKURO_START, ITM_KABU_START
};

extern u16 ftr_price_table[];

extern u32 mSP_ItemNo2ItemPrice(mActor_name_t item_no) {
    static u32 shellfish_price_table[ITM_SHELL_END - ITM_SHELL_START] = { 160, 80, 600, 120, 240, 1800, 1400, 1000 };

    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
    lbRTC_year_t year = rtc_time.year;
    u32 price = 0;

    if (item_no == ITM_HUKUBUKURO_BAG) {
        return year;
    }

    item_no = mRmTp_FtrItemNo2Item1ItemNo(item_no, FALSE);
    if (item_no >= ITM_SHELL0 && item_no <= ITM_SHELL7) {
        u32 idx = item_no - ITM_SHELL0;

        return shellfish_price_table[idx % 8];
    }

    if (item_no == ITM_SIGNBOARD) {
        return mSP_SIGNBOARD_PRICE;
    }

    switch (ITEM_NAME_GET_TYPE(item_no)) {
        case NAME_TYPE_ITEM1: {
            u16** price_list_pp = l_price_info[ITEM_NAME_GET_CAT(item_no)];

            if (price_list_pp != NULL && &price != NULL) {
                u16* price_list_p = *price_list_pp;
                int idx = item_no - mSP_item1_start_idx_table[ITEM_NAME_GET_CAT(item_no)];

                if (item_no >= ITM_PAPER_START && item_no <= (ITM_PAPER_END - 1)) {
                    int paper_idx = (item_no - ITM_PAPER_START);

                    idx = (item_no - ITM_PAPER_START) % PAPER_UNIQUE_NUM;
                    if (idx < mSP_CountPriceTableElement(price_list_p)) {
                        price = price_list_p[idx];
                        price = price * ((paper_idx / 64) + 1);
                        return price;
                    }
                }

                if (idx < mSP_CountPriceTableElement(price_list_p)) {
                    switch (item_no) {
                        case ITM_FOOD_APPLE:
                        case ITM_FOOD_CHERRY:
                        case ITM_FOOD_PEAR:
                        case ITM_FOOD_PEACH:
                        case ITM_FOOD_ORANGE: {
                            if (Save_Get(fruit) != item_no) {
                                return mSP_FOREIGN_FRUIT_PRICE;
                            }

                            break;
                        }
                    }

                    price = price_list_p[idx];
                    return price;
                }

                return 0;
            }

            break;
        }

        case NAME_TYPE_FTR0:
        case NAME_TYPE_FTR1: {
            if (&price != NULL) {
                int ftr_idx = mRmTp_FtrItemNo2FtrIdx(item_no);
                u16* price_list_p = ftr_price_table;

                if (ftr_idx < mSP_CountPriceTableElement(price_list_p)) {
                    price = price_list_p[ftr_idx];
                    return price;
                }

                return 0;
            }

            break;
        }

        default: {
            return 0;
        }
    }

    return 0;
}

extern int mSP_SearchItemCategoryPriority(mActor_name_t item_no, int category, int list_type, GAME* game) {
    u8 abc_priorities[3];
    mActor_name_t** lists_p = mSP_goods_seg_inf[category];
    mActor_name_t* list_p;
    int count;
    int i;

    mSP_GetGoodsPriority(abc_priorities, category);
    list_p = mSP_GetItemList(lists_p, abc_priorities, list_type);
    count = mSP_CountElementInCommonList(list_p);

    if (list_p != NULL) {
        for (i = 0; i < count; i++) {
            if (item_no == list_p[i]) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

static int mSP_ItemNo2GoodsListCategory(mActor_name_t item_no) {
    if (ITEM_IS_FTR(item_no)) {
        return mSP_KIND_FURNITURE;
    } else if (item_no >= ITM_PAPER_START && item_no < ITM_PAPER_END) {
        return mSP_KIND_PAPER;
    } else if (item_no >= ITM_CLOTH_START && item_no < ITM_CLOTH_END) {
        return mSP_KIND_CLOTH;
    } else if (item_no >= ITM_WALL_START && item_no < ITM_WALL_END) {
        return mSP_KIND_WALLPAPER;
    } else if (item_no >= ITM_CARPET_START && item_no < ITM_CARPET_END) {
        return mSP_KIND_CARPET;
    } else if (item_no >= ITM_DIARY_START && item_no <= (ITM_DIARY_END - 1)) {
        return mSP_KIND_DIARY;
    }

    return -1;
}

static u8 l_zakka_goods[mSP_GOODS_TYPE_NUM] = {
    1, // stationery
    1, // clothing
    1, // ABC ftr
    0, // rare ftr
    1, // carpet
    1, // wallpaper
    1, // ??
    0, // ??
    1, // saplings
    2, // tools
    2  // plants
};

static u8 l_conbini_goods[mSP_GOODS_TYPE_NUM] = {
    2, // stationery
    2, // clothing
    2, // ABC ftr
    0, // rare ftr
    1, // carpet
    1, // wallpaper
    1, // ??
    0, // ??
    1, // saplings
    3, // tools
    3  // plants
};

static u8 l_super_goods[mSP_GOODS_TYPE_NUM] = {
    2, // stationery
    3, // clothing
    3, // ABC ftr
    1, // rare ftr
    2, // carpet
    2, // wallpaper
    1, // ??
    0, // ??
    2, // saplings
    2, // tools
    4  // plants
};

static u8 l_dsuper_goods[mSP_GOODS_TYPE_NUM] = {
    4, // stationery
    5, // clothing
    5, // ABC ftr
    1, // rare ftr
    3, // carpet
    3, // wallpaper
    1, // ??
    0, // ??
    3, // saplings
    3, // tools
    5  // plants
};

static u8* l_goods_count_table[mSP_SHOP_TYPE_NUM] = { l_zakka_goods, l_conbini_goods, l_super_goods, l_dsuper_goods };

static void mSP_MakeRandomGoodsList(GAME* game, int* count, mActor_name_t* goods_list) {
    int shop_level = mSP_GetShopLevel();
    u8* goods_count = l_goods_count_table[shop_level];
    Shop_c* shop = Save_GetPointer(shop);
    mActor_name_t rare;

    /* roll rare furniture if the shop has one */
    if (goods_count[mSP_GOODS_TYPE_RARE_FTR] != 0) {
        mSP_SelectRandomItem_New(game, &rare, 1, NULL, 0, mSP_KIND_FURNITURE, mSP_LISTTYPE_RARE, FALSE);
    } else {
        rare = EMPTY_NO;
    }

    Save_Get(shop).rare_item = rare;

    /* roll ABC list furniture */
    mSP_SelectRandomItem_New(game, goods_list + count[0], goods_count[mSP_GOODS_TYPE_FTR], NULL, 0, mSP_KIND_FURNITURE,
                             mSP_LISTTYPE_ABC, FALSE);
    mSP_SetSeasonFTR(goods_list + count[0],
                     goods_count[mSP_GOODS_TYPE_FTR]); // replace with seasonal furniture if necessary
    count[0] += goods_count[mSP_GOODS_TYPE_FTR];

    /* check for grab bag sale */
    if (mSP_Chk_HukubukuroSail()) {
        shop->flowers_candy_grab_bag_count += (s8)goods_count[mSP_GOODS_TYPE_PAPER];
        if (shop_level >= mSP_SHOP_TYPE_SUPER) {
            shop->flowers_candy_grab_bag_count += 1;
        }
    } else {
        /* no grab bag sale, so roll paper & diaries */
        mSP_SelectRandomItem_New(game, goods_list + count[0], goods_count[mSP_GOODS_TYPE_PAPER], NULL, 0,
                                 mSP_KIND_PAPER, mSP_LISTTYPE_ABC, FALSE);
        count[0] += goods_count[mSP_GOODS_TYPE_PAPER];

        /* only roll diaries for Nookway or higher */
        if (shop_level >= mSP_SHOP_TYPE_SUPER) {
            mSP_SelectRandomItem_New(game, goods_list + count[0], 1, NULL, 0, mSP_KIND_DIARY, mSP_LISTTYPE_ABC, FALSE);
            count[0] += 1;
        }
    }

    /* roll clothing */
    mSP_SelectRandomItem_New(game, goods_list + count[0], goods_count[mSP_GOODS_TYPE_CLOTH], NULL, 0, mSP_KIND_CLOTH,
                             mSP_LISTTYPE_ABC, FALSE);
    count[0] += goods_count[mSP_GOODS_TYPE_CLOTH];

    /* roll carpets */
    mSP_SelectRandomItem_New(game, goods_list + count[0], goods_count[mSP_GOODS_TYPE_CARPET], NULL, 0, mSP_KIND_CARPET,
                             mSP_LISTTYPE_ABC, FALSE);
    count[0] += goods_count[mSP_GOODS_TYPE_CARPET];

    /* roll wallpaper */
    mSP_SelectRandomItem_New(game, goods_list + count[0], goods_count[mSP_GOODS_TYPE_WALL], NULL, 0, mSP_KIND_WALLPAPER,
                             mSP_LISTTYPE_ABC, FALSE);
    count[0] += goods_count[mSP_GOODS_TYPE_WALL];
}

extern int mSP_CountElementInGoodsList() {
    mActor_name_t* items = Save_Get(shop).items;
    int goods_count = 0;
    int i;

    for (i = 0; i < mSP_GOODS_COUNT; i++) {
        if (items[i] != EMPTY_NO) {
            goods_count++;
        }
    }

    return goods_count;
}

static void mSP_SelectTool(mActor_name_t* goods_list, int* count, int tool_num, int shop_level) {
    static int table[4] = { ITM_SHOVEL, ITM_NET, ITM_ROD, ITM_AXE };

    int tools_added = 0;
    u16 paint_idx = Save_Get(shop).shop_info.paint_color;
    u32 sales_sum = Save_Get(shop).sales_sum;
    f32 tool_max;

    /* tool lockout based on sales sum is only applicable to Nook's Cranny */
    if (shop_level > mSP_SHOP_TYPE_ZAKKA) {
        tool_max = 4; /* shove, net, rod, axe */
    } else if (sales_sum < mSP_NET_SALES_SUM) {
        tool_max = 1; /* shovel only */
    } else if (sales_sum < mSP_ROD_SALES_SUM) {
        tool_max = 2; /* shovel, net */
    } else if (sales_sum < mSP_AXE_SALES_SUM) {
        tool_max = 3; /* shovel, net, rod */
    } else {
        tool_max = 4; /* shove, net, rod, axe */
    }

    if (tool_num > (int)tool_max) {
        tool_num = (int)tool_max;
    }

    /*
      This implementation kind of sucks.
      At best case there's a (1/4)^4 (~0.4%) chance of
      rolling all four unique tools in a single go.
    */
    while (tools_added < tool_num) {
        int idx = RANDOM_F(tool_max);
        mActor_name_t tool = table[idx];

        /* Don't allow duplicate tools */
        if (mSP_GoodsExistAlready(goods_list, count[0], tool) == FALSE) {
            goods_list[(int)count[0]] = tool;
            tools_added++;
            count[0]++;
        }
    }

    /* Add paint & signboard if shop is Nookway or greater */
    if (shop_level >= mSP_SHOP_TYPE_SUPER) {
        if ((u16)paint_idx >= PAINT_NUM) {
            paint_idx = 0; /* wrap over to beginning */
        }

        goods_list[count[0]] = ITM_RED_PAINT + paint_idx;
        paint_idx++;
#if VERSION == VER_GAFU01_00
        Save_Get(shop).shop_info.paint_color = (u16)paint_idx;
#else
        Save_Get(shop).shop_info.paint_color = paint_idx;
#endif
        count[0]++;
        goods_list[count[0]] = ITM_SIGNBOARD;
        count[0]++;
    }

    /* Add umbrella */
    mSP_RandomUmbSelect(goods_list + count[0], 1);
    count[0]++;
}

static void mSP_SelectPlant(mActor_name_t* goods_list, int* count, int flower_count, int sapling_count,
                            const int shop_level) {
    u8 flower_use[FLOWER_NUM];
    int i;

    if (mSP_CheckHallowinDay()) {
        Save_Get(shop).flowers_candy_grab_bag_count = flower_count;
        flower_count = sapling_count;
        sapling_count = 0;
    }

    if (shop_level >= mSP_SHOP_TYPE_SUPER && sapling_count > 0) {
        goods_list[count[0]] = ITM_CEDAR_SAPLING;
        sapling_count--;
        count[0] += 1;
    }

    for (i = sapling_count; i > 0; i--) {
        goods_list[count[0]] = ITM_SAPLING;
        count[0] += 1;
    }

    for (i = 0; i < FLOWER_NUM; i++) {
        flower_use[i] = FALSE;
    }

    while (flower_count > 0) {
        int idx = RANDOM(FLOWER_NUM);

        if (flower_use[idx] == FALSE) {
            goods_list[count[0]] = ITM_WHITE_PANSY_BAG + idx;
            flower_use[idx] = TRUE;
            flower_count--;
            count[0] += 1;
        }
    }
}

static void mSP_MakeGoodsList(GAME* game) {
    int count = 0;
    mActor_name_t* shop_items = Save_Get(shop).items;
    Shop_c* shop = Save_GetPointer(shop);
    int shop_level = mSP_GetShopLevel();
    u8* goods_count = l_goods_count_table[shop_level];
    u8 tool_count = goods_count[mSP_GOODS_TYPE_TOOL];
    u8 flower_count = goods_count[mSP_GOODS_TYPE_PLANT];
    u8 sapling_count = goods_count[mSP_GOODS_TYPE_SAPLING];

    if (mSP_CheckFukubikiDay() == FALSE) {
        if (mSP_Chk_HukubukuroSail() != FALSE) {
            shop->flowers_candy_grab_bag_count = 0;
        }

        mSP_MakeRandomGoodsList(game, &count, shop_items);

        if (mSP_Chk_HukubukuroSail() != FALSE) {
            shop->flowers_candy_grab_bag_count += (s8)tool_count;
            shop->flowers_candy_grab_bag_count += (s8)flower_count;
            shop->flowers_candy_grab_bag_count += (s8)sapling_count;

            if (shop_level >= mSP_SHOP_TYPE_SUPER) {
                shop->flowers_candy_grab_bag_count++; // add signboard & paint
                shop->flowers_candy_grab_bag_count++;
            }
        } else {
            mSP_SelectTool(shop_items, &count, tool_count, shop_level & 3);
            mSP_SelectPlant(shop_items, &count, flower_count, sapling_count, shop_level & 3);
        }
    }
}

static void mSP_MakeLotteryList(GAME* game) {
    mActor_name_t* lottery_items = Save_Get(shop).lottery_items;
    mActor_name_t unobtained_lottery_item;

    mSP_SelectRandomItem_New(game, &unobtained_lottery_item, 1, NULL, 0, mSP_KIND_FURNITURE, mSP_LISTTYPE_LOTTERY,
                             TRUE);

    if (unobtained_lottery_item == EMPTY_NO) {
        mSP_SelectRandomItem_New(game, lottery_items, mSP_LOTTERY_ITEM_COUNT, NULL, 0, mSP_KIND_FURNITURE,
                                 mSP_LISTTYPE_LOTTERY, FALSE);
    } else {
        mSP_SelectRandomItem_New(game, lottery_items + 1, mSP_LOTTERY_ITEM_COUNT - 1, &unobtained_lottery_item, 1,
                                 mSP_KIND_FURNITURE, mSP_LISTTYPE_LOTTERY, FALSE);

        lottery_items[0] = unobtained_lottery_item;
    }
}

extern int mSP_CheckExchangeDay2() {
    Shop_c* shop = Save_GetPointer(shop);
    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
    int res =
        lbRTC_IsEqualTime(&rtc_time, &shop->exchange_time, lbRTC_CHECK_DAYS | lbRTC_CHECK_MONTHS | lbRTC_CHECK_YEARS);

    return res == lbRTC_EQUAL;
}

extern int mSP_CheckExchangeMonth() {
    Shop_c* shop = Save_GetPointer(shop);
    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
    int res = lbRTC_IsEqualTime(&rtc_time, &shop->exchange_time, lbRTC_CHECK_MONTHS | lbRTC_CHECK_YEARS);

    return res == lbRTC_EQUAL;
}

extern void mSP_NewExchangeDay() {
    Save_Get(shop).exchange_time = Common_Get(time.rtc_time);
}

/* @unused size: 0x104 */
// ? mSP_SearchRareFurniture(...)

extern void mSP_ShopItsumoChirashi(int house_no, int shop_level, mActor_name_t item, int type, int send_proc) {
    static int rare_chirashi_bunmen[mSP_SHOP_TYPE_NUM][2] = { { 18, 18 }, { 19, 19 }, { 21, 20 }, { 23, 22 } };

    if (Save_Get(homes[house_no]).ownerID.land_id != 0xFFFF) {
        int free_mail_idx = mMl_chk_mail_free_space(Save_Get(homes[house_no]).mailbox, HOME_MAILBOX_SIZE);

        if (mEv_ArbeitPlayer(mHS_get_pl_no(house_no) & 3) != TRUE) {
            u8 item_name_str[mIN_ITEM_NAME_LEN];
            Mail_c leaflet;
            int header_back_start;

            mIN_copy_name_str(item_name_str, item);
            mHandbill_Set_free_str(mHandbill_FREE_STR7, item_name_str, mIN_ITEM_NAME_LEN);
            mMl_clear_mail(&leaflet);
            mHandbill_Load_HandbillFromRom(leaflet.content.header, &header_back_start, leaflet.content.footer,
                                           leaflet.content.body, rare_chirashi_bunmen[shop_level][type & 1]);
            leaflet.content.font = mMl_FONT_RECV;
            leaflet.content.header_back_start = header_back_start;
            leaflet.content.mail_type = mMl_TYPE_SHOP_SALE_LEAFLET;
            leaflet.content.paper_type = ITM_PAPER55; // simple paper

            switch (send_proc) {
                case mPO_SENDTYPE_MAIL: {
                    mPO_receipt_proc(&leaflet, mPO_SENDTYPE_LEAFLET);

                    break;
                }

                default: {
                    if (free_mail_idx >= 0) {
                        mPr_CopyPersonalID(&leaflet.header.recipient.personalID,
                                           &Save_Get(private_data[mHS_get_pl_no(house_no) & 3]).player_ID);
                        leaflet.header.recipient.type = mMl_NAME_TYPE_PLAYER;

                        mMl_copy_mail(Save_Get(homes[house_no]).mailbox + free_mail_idx, &leaflet);
                    }

                    break;
                }
            }
        }
    }
}

extern void mSP_SetShopRareFurnitureChirashi(int player_no, mActor_name_t* goods_list, int goods_count, GAME* game) {
    const int p = player_no;
    int shop_level = mSP_GetShopLevel();
    int is_rare_item = FALSE;
    mActor_name_t rare_item = EMPTY_NO;
    int arrange_idx = mHS_get_arrange_idx(p);
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

    if (player_no != mHS_get_pl_no_detail(arrange_idx)) {
        mCkRh_SavePlayTime(player_no);
        return;
    }

    /* Check if we're on the last day of the month */
    if (Common_Get(time.rtc_time).day ==
        lbRTC_GetDaysByMonth(Common_Get(time.rtc_time).year, Common_Get(time.rtc_time).month)) {
        mCkRh_SavePlayTime(player_no);
    } else if (mEv_CheckEvent(mEv_SAVED_RENEWSHOP) == TRUE) {
        mCkRh_SavePlayTime(player_no); // shop was already 'renewed' today
    } else {
        u16 bargain_day = mEv_get_bargain_day();
        lbRTC_time_c goki_time;
        mHm_hs_c* home;

        if (bargain_day != 0) {
            u32 month = mEv_TO_MONTH(bargain_day);
            u32 day = mEv_TO_DAY(bargain_day);
            if (Common_Get(time.rtc_time).month == month && Common_Get(time.rtc_time).day == day) {
                mCkRh_SavePlayTime(player_no); // shop 'bargin' event is active
                return;
            }
        }

        goki_time = Save_Get(homes[arrange_idx]).goki.time;
        lbRTC_Add_DD(&goki_time, 1);
        home = Save_GetPointer(homes[arrange_idx]);

        /* check if the current date & time is past the renew time */
        if (home->goki.time.year == rtc_time->year && home->goki.time.month == rtc_time->month &&
            home->goki.time.day == rtc_time->day)
            return;

        if (goki_time.year == rtc_time->year && goki_time.month == rtc_time->month && goki_time.day == rtc_time->day &&
            goki_time.hour < mTM_FIELD_RENEW_HOUR)
            return;

        if (rtc_time->hour < mTM_FIELD_RENEW_HOUR || rtc_time->hour > mSP_GetShopCloseTime())
            return;

        if (mSP_SearchItemCategoryPriority(Save_Get(shop).rare_item, mSP_KIND_FURNITURE, mSP_LISTTYPE_RARE, game)) {
            rare_item = Save_Get(shop).rare_item;
            is_rare_item = TRUE;
        } else {
            int i;

            /* spotlight item in shop wasn't the rare item, so check all
             * the goods for one */
            for (i = 0; i < goods_count; i++) {
                if (mSP_ItemNo2GoodsListCategory(goods_list[i]) == mSP_KIND_FURNITURE) {
                    is_rare_item =
                        mSP_SearchItemCategoryPriority(goods_list[i], mSP_KIND_FURNITURE, mSP_LISTTYPE_RARE, game);

                    if (is_rare_item != FALSE) {
                        rare_item = goods_list[i];

                        break;
                    }
                }
            }
        }

        /* check if a rare item was found, and if so, send the notice
         * leaflet to the player */
        if (is_rare_item != FALSE) {
            int arrange_idx = mHS_get_arrange_idx(p);

            if (mHS_get_pl_no_detail(arrange_idx) != -1) {
                mSP_ShopItsumoChirashi(arrange_idx, shop_level, rare_item, is_rare_item, mPO_SENDTYPE_LEAFLET);
                mCkRh_SavePlayTime(player_no);
            }
        }
    }
}

extern void mSP_SetRenewalChiraswhi_AppoDay() {
    static int chirashi_idx_appoday[mSP_SHOP_TYPE_NUM] = { 0x1B, 0x1B, 0x1C, 0x1D };
    Mail_c leaflet;
    Mail_ct_c* content = &leaflet.content;
    int header_back_start;

    if (Save_Get(shop).shop_info.upgrading_today && mEv_CheckEvent(mEv_SAVED_RENEWSHOP) == FALSE) {
        int shop_level = mSP_GetRealShopLevel();
        int i;

        for (i = 0; i < mHS_HOUSE_NUM; i++) {
            int player_no = mHS_get_pl_no(i) & 3;
            int free_mail_idx = mMl_chk_mail_free_space(Save_Get(homes[i]).mailbox, HOME_MAILBOX_SIZE);

            if (free_mail_idx >= 0 && Save_Get(homes[i]).ownerID.land_id != 0xFFFF &&
                mEv_ArbeitPlayer(player_no) == FALSE) {

                mMl_clear_mail(&leaflet);
                mHandbill_Load_HandbillFromRom(content->header, &header_back_start, content->footer, content->body,
                                               chirashi_idx_appoday[shop_level]);
                leaflet.content.font = mMl_FONT_RECV;
                leaflet.content.header_back_start = header_back_start;
                leaflet.content.mail_type = mMl_TYPE_SHOP_SALE_LEAFLET;
                leaflet.content.paper_type = ITM_PAPER55; // simple paper

                mPr_CopyPersonalID(&leaflet.header.recipient.personalID,
                                   &Save_Get(private_data[mHS_get_pl_no(i) & 3]).player_ID);
                leaflet.header.recipient.type = mMl_NAME_TYPE_PLAYER;

                mMl_copy_mail(Save_Get(homes[i]).mailbox + free_mail_idx, &leaflet);
            }
        }

        Save_Get(shop).shop_info.upgrading_today = FALSE;
    }
}

extern void mSP_ExchangeLineUp_InGame(GAME* game) {
    if (mSP_CheckExchangeDay2()) {
        if (mSP_CheckExchangeMonth()) {
            mSP_LotteryLineUp_GameAlloc(game);
        }

        mSP_NewExchangeDay();
        mSP_ExchangeLineUp_GameAlloc(game);
        Save_Get(shop).shop_info.not_loaded_before = TRUE;
        mSP_SetShopRareFurnitureChirashi(Common_Get(player_no), Save_Get(shop).items, mSP_GOODS_COUNT, game);
    }
}

extern void mSP_PlusSales(u32 sum) {
    Save_Get(shop).sales_sum += sum;

    if (mSP_GetShopLevel() == mSP_SHOP_TYPE_ZAKKA) {
        if (Save_Get(shop).sales_sum > mSP_COMBINI_SUM) {
            Save_Get(shop).sales_sum = mSP_COMBINI_SUM;
        }
    } else if (mSP_GetShopLevel() == mSP_SHOP_TYPE_COMBINI) {
        if (Save_Get(shop).sales_sum > mSP_SUPER_SUM) {
            Save_Get(shop).sales_sum = mSP_SUPER_SUM;
        }
    } else if (mSP_GetShopLevel() == mSP_SHOP_TYPE_SUPER) {
        if (Save_Get(shop).sales_sum > mSP_DSUPER_SUM) {
            Save_Get(shop).sales_sum = mSP_DSUPER_SUM;
        }
    }
}

/* @unused size: 0x74 */
// extern int mSP_GetVisitorCount()

extern int mSP_SetNewVisitor() {
    if (mLd_PlayerManKindCheck()) {
        Save_Get(shop).visitor_flag = TRUE;
        return TRUE;
    }

    return FALSE;
}

extern u32 mSP_GetSalesSum() {
    return Save_Get(shop).sales_sum;
}

extern int mSP_GetShopLevel() {
    return Save_Get(shop).shop_info.shop_level;
}

extern int mSP_RenewShopLevel() {
    if (Save_Get(shop).shop_info.shop_level != (u8)mSP_GetRealShopLevel()) {
        Save_Get(shop).shop_info.shop_level = mSP_GetRealShopLevel();
        return TRUE;
    }

    return FALSE;
}

extern int mSP_GetRealShopLevel() {
    u32 sales_sum = mSP_GetSalesSum();

    if (sales_sum >= mSP_DSUPER_SUM && Save_Get(shop).visitor_flag != FALSE) {
        return mSP_SHOP_TYPE_DSUPER;
    } else if (sales_sum >= mSP_SUPER_SUM) {
        return mSP_SHOP_TYPE_SUPER;
    }

    return sales_sum >= mSP_COMBINI_SUM ? mSP_SHOP_TYPE_COMBINI : mSP_SHOP_TYPE_ZAKKA;
}

extern int mSP_GetGoodsPercent(int priority) {
    int goods_power = mPr_GetGoodsPower();

    if (priority >= 0 && priority <= mSP_PRIORITY_RARE) {
        int rare;
        int uncommon;

        if (goods_power < 0) {
            uncommon = goods_power + 35 + 5;
            rare = 5;
        } else {
            rare = goods_power + 5;
            uncommon = rare + 35;
        }

        switch (priority) {
            case mSP_PRIORITY_COMMON:
                return 100 - uncommon;
            case mSP_PRIORITY_UNCOMMON:
                return uncommon - rare;
            case mSP_PRIORITY_RARE:
                return rare;
            default:
                return 0;
        }
    } else {
        return 0;
    }
}

extern void mSP_PrintNowShopSalesSum(gfxprint_t* gfxprint) {
    if (mFI_CheckFieldData()) {
        int shop_level = mSP_GetShopLevel();
        int status = mSP_ShopOpen();
        u32 sales_sum = mSP_GetSalesSum();
        u32 working_sum;

        switch (shop_level) {
            case mSP_SHOP_TYPE_ZAKKA:
                working_sum = sales_sum;
                break;
            case mSP_SHOP_TYPE_COMBINI:
                working_sum = sales_sum - mSP_COMBINI_SUM;
                break;
            case mSP_SHOP_TYPE_SUPER:
                working_sum = sales_sum - mSP_SUPER_SUM;
                break;
            default:
                working_sum = sales_sum - mSP_DSUPER_SUM;
                break;
        }

        gfxprint_color(gfxprint, 200, 200, 250, 255);
        gfxprint_locate8x8(gfxprint, 3, 12);

        if (mEv_CheckEvent(mEv_SAVED_RENEWSHOP) == FALSE) {
            gfxprint_printf(gfxprint, "%d %d %s", shop_level, working_sum, mSP_ShopStatus2String(status));

            gfxprint_color(gfxprint, 200, 200, 250, 255);
            gfxprint_printf(gfxprint, "A%2d,%2d,%2d,%2d,%2d",
                            mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_FURNITURE].a),
                            mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_WALLPAPER].a),
                            mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_CARPET].a),
                            mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_CLOTH].a),
                            mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_PAPER].a));
        } else {
            gfxprint_color(gfxprint, 200, 100, 100, 255);
            gfxprint_printf(gfxprint, "%d %d %s->%d.%d.%d", shop_level, working_sum, mSP_ShopStatus2String(status),
                            Save_Get(shop).renewal_time.year, Save_Get(shop).renewal_time.month,
                            Save_Get(shop).renewal_time.day);

            gfxprint_color(gfxprint, 200, 200, 250, 255);
            gfxprint_printf(gfxprint, " A%2d,%2d,%2d,%2d,%2d",
                            mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_FURNITURE].a),
                            mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_WALLPAPER].a),
                            mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_CARPET].a),
                            mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_CLOTH].a),
                            mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_PAPER].a));
        }

        gfxprint_color(gfxprint, 200, 200, 250, 255);
        gfxprint_locate8x8(gfxprint, 3, 13);
        gfxprint_printf(gfxprint, "B%2d,%2d,%2d,%2d,%2d",
                        mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_FURNITURE].b),
                        mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_WALLPAPER].b),
                        mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_CARPET].b),
                        mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_CLOTH].b),
                        mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_PAPER].b));
        gfxprint_printf(gfxprint, "C%2d,%2d,%2d,%2d,%2d",
                        mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_FURNITURE].c),
                        mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_WALLPAPER].c),
                        mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_CARPET].c),
                        mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_CLOTH].c),
                        mSP_GetGoodsPercent(Save_Get(shop).priority_lists[mSP_KIND_PAPER].c));
    }
}

extern void mSP_GetGoodsPriority(u8* abc_priorities, int category) {
    mSP_goods_priority_list_c* priorities = Save_Get(shop).priority_lists;

    if (category == mSP_KIND_DIARY) {
        category = mSP_KIND_FURNITURE;
    }

    abc_priorities[0] = priorities[category].a;
    abc_priorities[1] = priorities[category].b;
    abc_priorities[2] = priorities[category].c;
}

static void mSP_SetExchangeDay() {
    Save_Get(shop).exchange_time = Common_Get(time.rtc_time);
}

static void mSP_InitGoods() {
    Shop_c* shop = Save_GetPointer(shop);
    mActor_name_t* items = shop->items;
    int i;

    for (i = 0; i < mSP_GOODS_COUNT; i++) {
        *items++ = EMPTY_NO;
    }
}

extern void mSP_ExchangeLineUp_ZeldaMalloc() {
    mSP_InitGoods();
    mSP_MakeGoodsList(NULL);
    mSP_SetExchangeDay();
}

extern void mSP_LotteryLineUp_ZeldaMalloc() {
    mSP_MakeLotteryList(NULL);
}

extern void mSP_ExchangeLineUp_GameAlloc(GAME* game) {
    mSP_InitGoods();
    mSP_MakeGoodsList(game);
    mSP_SetExchangeDay();
}

extern void mSP_LotteryLineUp_GameAlloc(GAME* game) {
    mSP_MakeLotteryList(game);
}

extern void mSP_InitShopSaveData() {
    Shop_c* shop = Save_GetPointer(shop);
    PersonalID_c* pid = shop->unused_ids;
    mActor_name_t* lottery_items = shop->lottery_items;
    int i = 0;

    while (i < mSP_PERSONAL_ID_COUNT) {
        mPr_ClearPersonalID(pid);
        pid++;
        i++;
    }

    mSP_InitGoods();
    Save_Get(shop).rare_item = EMPTY_NO;

    for (i = 0; i < mSP_LOTTERY_ITEM_COUNT; i++) {
        lottery_items[0] = EMPTY_NO;
        lottery_items++;
    }

    Save_Get(shop).flowers_candy_grab_bag_count = 0;
    shop->sales_sum = 0;
    shop->exchange_time = Common_Get(time.rtc_time);
    shop->exchange_time.month--;
    shop->shop_info.shop_level = mSP_SHOP_TYPE_ZAKKA;
    shop->renewal_time = shop->exchange_time;
    shop->shop_info.upgrading_today = FALSE;
    Save_Get(shop).visitor_flag = FALSE;
}

static void mSP_DecideUniqueCommonList(mSP_goods_priority_list_c* priority_list) {
    static mSP_goods_priority_list_c priority_candidate[6] = {
        { mSP_PRIORITY_COMMON, mSP_PRIORITY_UNCOMMON, mSP_PRIORITY_RARE, 0 },
        { mSP_PRIORITY_COMMON, mSP_PRIORITY_RARE, mSP_PRIORITY_UNCOMMON, 0 },
        { mSP_PRIORITY_UNCOMMON, mSP_PRIORITY_COMMON, mSP_PRIORITY_RARE, 0 },
        { mSP_PRIORITY_RARE, mSP_PRIORITY_COMMON, mSP_PRIORITY_UNCOMMON, 0 },
        { mSP_PRIORITY_RARE, mSP_PRIORITY_UNCOMMON, mSP_PRIORITY_COMMON, 0 },
        { mSP_PRIORITY_UNCOMMON, mSP_PRIORITY_RARE, mSP_PRIORITY_COMMON, 0 }
    };

    priority_list[0] = priority_candidate[RANDOM(6)];
}

static void mSP_DecideGoodsCommonList() {
    mSP_goods_priority_list_c* priority_lists = Save_Get(shop).priority_lists;

    mSP_DecideUniqueCommonList(&priority_lists[mSP_KIND_FURNITURE]);
    mSP_DecideUniqueCommonList(&priority_lists[mSP_KIND_PAPER]);
    mSP_DecideUniqueCommonList(&priority_lists[mSP_KIND_CLOTH]);
    mSP_DecideUniqueCommonList(&priority_lists[mSP_KIND_CARPET]);
    mSP_DecideUniqueCommonList(&priority_lists[mSP_KIND_WALLPAPER]);
}

extern void mSP_ShopGameStartCt(GAME* game) {
    mSP_DecideGoodsCommonList();
    mSP_InitShopSaveData();
    mSP_ExchangeLineUp_InGame(game);
}

extern mActor_name_t mSP_GetNowShopBgNum() {
    switch (Save_Get(scene_no)) {
        case SCENE_SHOP0: {
            if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI) {
                return BG_TYPE_ROM_SHOP1_FUKU;
            }

            return BG_TYPE_ROM_SHOP1;
        }

        case SCENE_CONVENI: {
            if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI) {
                return BG_TYPE_ROM_SHOP2_FUKU;
            }

            return BG_TYPE_ROM_SHOP2;
        }

        case SCENE_SUPER: {
            if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI) {
                return BG_TYPE_ROM_SHOP3_FUKU;
            }

            return BG_TYPE_ROM_SHOP3;
        }

        case SCENE_DEPART: {
            if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI) {
                return BG_TYPE_ROM_SHOP4_FUKU;
            }

            return BG_TYPE_ROM_SHOP4_1;
        }

        case SCENE_DEPART_2:
            return BG_TYPE_ROM_SHOP4_2;

        default:
            return BG_TYPE_ROM_SHOP2;
    }
}

static int mSP_what_special_sale;

extern int mSP_WhatSpecialSale() {
    return mSP_what_special_sale;
}

extern mActor_name_t mSP_GetNowShopFgNum() {
    int event_kind = Save_Get(event_save_data).special.event.bargin.kind;

    switch (Save_Get(scene_no)) {
        case SCENE_SHOP0: {
            if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_EVENT) {
                if (event_kind == mSP_KIND_FURNITURE) {
                    mSP_what_special_sale = mSP_KIND_FURNITURE;
                    return FG_TYPE_ROM_SHOP1_SALE_FTR;
                }

                if (event_kind == mSP_KIND_CLOTH) {
                    mSP_what_special_sale = mSP_KIND_CLOTH;
                    return FG_TYPE_ROM_SHOP1_SALE_CLOTH;
                }

                if (event_kind == mSP_KIND_WALLPAPER) {
                    mSP_what_special_sale = mSP_KIND_WALLPAPER;
                    return FG_TYPE_ROM_SHOP1_SALE_WALL;
                }

                mSP_what_special_sale = mSP_KIND_CARPET;
                return FG_TYPE_ROM_SHOP1_SALE_CARPET;
            }

            if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI) {
                return FG_TYPE_ROM_SHOP1_FUKU;
            }

            return FG_TYPE_ROM_SHOP1;
        }

        case SCENE_CONVENI: {
            if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_EVENT) {
                if (Save_Get(event_save_data).special.event.bargin.kind == mSP_KIND_FURNITURE) {
                    mSP_what_special_sale = mSP_KIND_FURNITURE;
                    return FG_TYPE_ROM_SHOP2_SALE_FTR;
                }

                if (Save_Get(event_save_data).special.event.bargin.kind == mSP_KIND_CLOTH) {
                    mSP_what_special_sale = mSP_KIND_CLOTH;
                    return FG_TYPE_ROM_SHOP2_SALE_CLOTH;
                }

                if (Save_Get(event_save_data).special.event.bargin.kind == mSP_KIND_WALLPAPER) {
                    mSP_what_special_sale = mSP_KIND_WALLPAPER;
                    return FG_TYPE_ROM_SHOP2_SALE_WALL;
                }

                mSP_what_special_sale = mSP_KIND_CARPET;
                return FG_TYPE_ROM_SHOP2_SALE_CARPET;
            }

            if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI) {
                return FG_TYPE_ROM_SHOP2_FUKU;
            }

            return FG_TYPE_ROM_SHOP2;
        }

        case SCENE_SUPER: {
            if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_EVENT) {
                if (Save_Get(event_save_data).special.event.bargin.kind == mSP_KIND_FURNITURE) {
                    mSP_what_special_sale = mSP_KIND_FURNITURE;
                    return FG_TYPE_ROM_SHOP3_SALE_FTR;
                }

                if (Save_Get(event_save_data).special.event.bargin.kind == mSP_KIND_CLOTH) {
                    mSP_what_special_sale = mSP_KIND_CLOTH;
                    return FG_TYPE_ROM_SHOP3_SALE_CLOTH;
                }

                if (Save_Get(event_save_data).special.event.bargin.kind == mSP_KIND_WALLPAPER) {
                    mSP_what_special_sale = mSP_KIND_WALLPAPER;
                    return FG_TYPE_ROM_SHOP3_SALE_WALL;
                }

                mSP_what_special_sale = mSP_KIND_CARPET;
                return FG_TYPE_ROM_SHOP3_SALE_CARPET;
            }

            if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI) {
                return FG_TYPE_ROM_SHOP3_FUKU;
            }

            return FG_TYPE_ROM_SHOP3;
        }

        case SCENE_DEPART: {
            if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_EVENT) {
                return FG_TYPE_ROM_SHOP4_1_SALE;
            }

            if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI) {
                return FG_TYPE_ROM_SHOP4_1_FUKU;
            }

            return FG_TYPE_ROM_SHOP4_1;
        }

        case SCENE_DEPART_2: {
            if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_EVENT) {
                if (Save_Get(event_save_data).special.event.bargin.kind == mSP_KIND_FURNITURE) {
                    mSP_what_special_sale = mSP_KIND_FURNITURE;
                    return FG_TYPE_ROM_SHOP4_2_SALE_FTR;
                }

                if (Save_Get(event_save_data).special.event.bargin.kind == mSP_KIND_CLOTH) {
                    mSP_what_special_sale = mSP_KIND_CLOTH;
                    return FG_TYPE_ROM_SHOP4_2_SALE_CLOTH;
                }

                if (Save_Get(event_save_data).special.event.bargin.kind == mSP_KIND_WALLPAPER) {
                    mSP_what_special_sale = mSP_KIND_WALLPAPER;
                    return FG_TYPE_ROM_SHOP4_2_SALE_WALL;
                }

                mSP_what_special_sale = mSP_KIND_CARPET;
                return FG_TYPE_ROM_SHOP4_2_SALE_CARPET;
            }

            return FG_TYPE_ROM_SHOP4_2;
        }

        default:
            return FG_TYPE_ROM_SHOP4_1;
    }
}

extern lbRTC_hour_t mSP_GetShopOpenTime() {
    static lbRTC_hour_t shop_open_time_table[mSP_SHOP_TYPE_NUM] = { 9, 7, 9, 9 };

    int shop_level = mSP_GetShopLevel();

    if (Common_Get(time.rtc_time).day ==
        lbRTC_GetDaysByMonth(Common_Get(time.rtc_time).year, Common_Get(time.rtc_time).month)) {
        return 10; // lottery starts at 10AM
    } else {
        return shop_open_time_table[shop_level];
    }
}

extern lbRTC_hour_t mSP_GetShopCloseTime() {
    static lbRTC_hour_t shop_close_time_table[mSP_SHOP_TYPE_NUM] = { 22, 23, 22, 22 };

    return shop_close_time_table[mSP_GetShopLevel()];
}

extern lbRTC_hour_t mSP_GetShopCloseTime_Bgm() {
    static lbRTC_hour_t shop_close_time_table[mSP_SHOP_TYPE_NUM] = { 22, 23, 22, 22 };

    return shop_close_time_table[mSP_GetShopLevel()];
}

extern int mSP_InRenewal() {
    if (mEv_CheckEvent(mEv_SAVED_RENEWSHOP) == TRUE) {
        lbRTC_time_c renew_time = Save_Get(shop).renewal_time;
        lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);

        lbRTC_Sub_DD(&renew_time, 1);

        if (lbRTC_IsOverTime(&renew_time, rtc_time) == lbRTC_OVER ||
            lbRTC_IsEqualTime(rtc_time, &renew_time, lbRTC_CHECK_YEARS | lbRTC_CHECK_MONTHS | lbRTC_CHECK_DAYS) !=
                FALSE) {
            return TRUE;
        }
    }

    return FALSE;
}

/* @unused size: 0xF0 */
// int mSP_CheckSpecialSalesSoldOut(...)

extern int mSP_ShopOpen() {
    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
    lbRTC_hour_t now_hour;

    if (mEv_CheckFirstJob()) {
        return mSP_SHOP_STATUS_OPEN; // shop is forcefully open during chores
    }

    if (mEv_CheckEvent(mEv_SPNPC_SHOP) == TRUE) {
        lbRTC_time_c bargin_time = Save_Get(event_save_data).special.event.bargin.start_time;

        if (bargin_time.day == rtc_time.day) {
            lbRTC_time_c end_time = Save_Get(event_save_data).special.event.bargin.end_time;
            lbRTC_time_c start_time_pre = bargin_time;
            lbRTC_time_c end_time_post = end_time;
            now_hour = rtc_time.hour;

            lbRTC_Sub_hh(&start_time_pre, 1);
            lbRTC_Add_hh(&end_time_post, 1);

            if (now_hour >= mTM_FIELD_RENEW_HOUR && now_hour < mSP_GetShopOpenTime()) {
                return mSP_SHOP_STATUS_PRE;
            }

            if (now_hour < mTM_FIELD_RENEW_HOUR || now_hour >= mSP_GetShopCloseTime()) {
                return mSP_SHOP_STATUS_END;
            }

            if (lbRTC_IsOverTime(&start_time_pre, &rtc_time) == lbRTC_LESS) {
                return mSP_SHOP_STATUS_OPEN;
            }

            if (lbRTC_IsOverTime(&bargin_time, &rtc_time) == lbRTC_LESS) {
                return mSP_SHOP_STATUS_PREEVENT;
            }

            if (lbRTC_IsOverTime(&end_time, &rtc_time) == lbRTC_LESS) {
                return mSP_SHOP_STATUS_OPENEVENT;
            }

            if (lbRTC_IsOverTime(&end_time_post, &rtc_time) == lbRTC_LESS) {
                return mSP_SHOP_STATUS_ENDEVENT;
            }

            return mSP_SHOP_STATUS_OPEN;
        }
    }

    now_hour = rtc_time.hour;

    if (mSP_InRenewal() != FALSE) {
        return mSP_SHOP_STATUS_RENEW;
    }

    if (now_hour >= mSP_GetShopOpenTime() && now_hour < mSP_GetShopCloseTime()) {
        return mSP_SHOP_STATUS_OPEN;
    }

    if (now_hour >= mTM_FIELD_RENEW_HOUR && now_hour < mSP_GetShopOpenTime()) {
        return mSP_SHOP_STATUS_PRE;
    }

    return mSP_SHOP_STATUS_END;
}

extern void mSP_RandomHaniwaSelect(mActor_name_t* haniwa_list, int count) {
    int i;

    for (i = 0; i < count; i++) {
        haniwa_list[i] = EMPTY_NO;
    }

    for (i = 0; i < count; i++) {
        int set = FALSE;

        while (!set) {
            mActor_name_t haniwa = HANIWA_START + (mActor_name_t)FTR_NO_2_IDX(RANDOM(HANIWA_NUM));

            if (mSP_GoodsExistAlready(haniwa_list, count, haniwa) == FALSE) {
                haniwa_list[i] = haniwa;
                set = TRUE;
            } else if (count > HANIWA_NUM) {
                haniwa_list[i] = haniwa;
                set = TRUE;
            }
        }
    }
}

extern void mSP_RandomMDSelect(mActor_name_t* md_list, int count) {
    int i;

    for (i = 0; i < count; i++) {
        md_list[i] = EMPTY_NO;
    }

    for (i = 0; i < count; i++) {
        int set = FALSE;

        while (!set) {
            mActor_name_t md = ITM_MINIDISK_START + RANDOM(NOT_SECRET_MD_NUM);

            if (mSP_GoodsExistAlready(md_list, count, md) == FALSE) {
                md_list[i] = md;
                set = TRUE;
            } else if (count > NOT_SECRET_MD_NUM) {
                md_list[i] = md;
                set = TRUE;
            }
        }
    }
}

extern void mSP_RandomUmbSelect(mActor_name_t* umb_list, int count) {
    int i;

    for (i = 0; i < count; i++) {
        umb_list[i] = EMPTY_NO;
    }

    for (i = 0; i < count; i++) {
        int set = FALSE;

        while (!set) {
            mActor_name_t umb = ITM_UMBRELLA00 + RANDOM(UMBRELLA_NUM);

            if (mSP_GoodsExistAlready(umb_list, count, umb) == FALSE) {
                umb_list[i] = umb;
                set = TRUE;
            } else if (count > UMBRELLA_NUM) {
                umb_list[i] = umb;
                set = TRUE;
            }
        }
    }
}

static int mSP_CountBirth(u8 birth_type) {
    int count = 0;
    u8* birth_type_p = mRmTp_CheckFtrBirthInfoTop();
    int i;

    for (i = 0; i < FTR_NUM; i++) {
        if (birth_type_p[0] == birth_type) {
            count++;
        }

        birth_type_p++;
    }

    return count;
}

static mActor_name_t mSP_FtrBirthIdx2ItemNo(u8 birth_type, int birth_idx) {
    int count = 0;
    u8* birth_type_p = mRmTp_CheckFtrBirthInfoTop();
    int i;

    for (i = 0; i < FTR_NUM; i++) {
        if (birth_type_p[0] == birth_type) {
            if (count == birth_idx) {
                return mRmTp_FtrIdx2FtrItemNo(i, mRmTp_DIRECT_SOUTH);
            }

            count++;
        }

        birth_type_p++;
    }

    return FTR_START(FTR_DIN_TREX_HEAD);
}

extern mActor_name_t mSP_RandomOneFossilSelect(int multi_fossil) {
    u8 birth_type = multi_fossil == FALSE ? mRmTp_BIRTH_TYPE_SINGLE_FOSSIL : mRmTp_BIRTH_TYPE_MULTI_FOSSIL;
    int count = mSP_CountBirth(birth_type);

    return mSP_FtrBirthIdx2ItemNo(birth_type, RANDOM(count));
}

extern int mSP_Chk_HukubukuroSail() {
    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
    lbRTC_year_t year = rtc_time.year;
    lbRTC_month_t month = rtc_time.month;
    lbRTC_day_t day = rtc_time.day;

    if (month == lbRTC_NOVEMBER) {
        int black_friday = lbRTC_Weekly_day(year, lbRTC_NOVEMBER, 4, lbRTC_THURSDAY) + 1;

        if (black_friday == day) {
            return TRUE;
        }
    }

    return FALSE;
}

extern int mSP_CheckFukubikiDay() {
    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
    lbRTC_year_t year = rtc_time.year;
    lbRTC_month_t month = rtc_time.month;
    lbRTC_day_t day = rtc_time.day;
    lbRTC_day_t days_in_month = lbRTC_GetDaysByMonth(year, month);

    return days_in_month == day;
}

extern int mSP_SetGoods2ReservedPoint(mActor_name_t goods, mActor_name_t reserved_no) {
    mActor_name_t* shop_fg = mFI_BkNumtoUtFGTop(0, 0);
    int i;

    for (i = 0; i < UT_TOTAL_NUM; i++) {
        if (reserved_no == shop_fg[0]) {
            mFI_UtNumtoFGSet_common(goods, i % UT_X_NUM, i / UT_X_NUM, FALSE);
            return TRUE;
        }

        shop_fg++;
    }

    return FALSE;
}

extern int mSP_CheckHallowinDay() {
    int res = FALSE;
    lbRTC_time_c rtc_time = Common_Get(time.rtc_time);
    lbRTC_month_t month = rtc_time.month;
    lbRTC_day_t day = rtc_time.day;

    if (month == lbRTC_OCTOBER && day >= 16 && day <= 30) {
        res = TRUE;
    }

    return res;
}

extern void mSP_SetTanukiShopStatus() {
    if (mSP_ShopOpen() == mSP_SHOP_STATUS_OPENEVENT) {
        Common_Set(tanuki_shop_status, mSP_TANUKI_SHOP_STATUS_EVENT);
    } else if (mSP_CheckFukubikiDay()) {
        Common_Set(tanuki_shop_status, mSP_TANUKI_SHOP_STATUS_FUKUBIKI);
    } else if (mSP_Chk_HukubukuroSail()) {
        Common_Set(tanuki_shop_status, mSP_TANUKI_SHOP_STATUS_HUKUBUKURO_SALE);
    } else if (mSP_CheckHallowinDay()) {
        Common_Set(tanuki_shop_status, mSP_TANUKI_SHOP_STATUS_HALLOWEEN);
    } else {
        Common_Set(tanuki_shop_status, mSP_TANUKI_SHOP_STATUS_NORMAL);
    }
}

static u32 mSP_sack_amount[MONEY_NUM] = { 100, 1000, 10000, 30000 };

static mActor_name_t mSP_itemNo[MONEY_NUM] = { ITM_MONEY_100, ITM_MONEY_1000, ITM_MONEY_10000, ITM_MONEY_30000 };

extern int mSP_money_check(u32 amount) {
    u32 money = Common_Get(now_private)->inventory.wallet;
    int res = FALSE;

    if (money < amount) {
        int i;

        for (i = 0; i < MONEY_NUM; i++) {
            int sack_num =
                mPr_GetPossessionItemSumWithCond(Common_Get(now_private), mSP_itemNo[i], mPr_ITEM_COND_NORMAL);

            money += sack_num * mSP_sack_amount[i];
            if (money >= amount) {
                res = TRUE;
                break;
            }
        }
    } else {
        res = TRUE;
    }

    return res;
}

static u32 mSP_get_sell_price_sub(u32 money, u32 amount) {
    u32 sack_num;
    int i;

    for (i = 0; i < MONEY_NUM; i++) {
        for (sack_num = mPr_GetPossessionItemSumWithCond(Common_Get(now_private), mSP_itemNo[i], mPr_ITEM_COND_NORMAL);
             sack_num != 0; sack_num--) {
            int sack_idx =
                mPr_GetPossessionItemIdxWithCond(Common_Get(now_private), mSP_itemNo[i], mPr_ITEM_COND_NORMAL);

            mPr_SetPossessionItem(Common_Get(now_private), sack_idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
            money += mSP_sack_amount[i];

            if (money >= amount) {
                return money - amount;
            }
        }
    }

    return 0;
}

extern void mSP_get_sell_price(u32 amount) {
    u32 money = Common_Get(now_private)->inventory.wallet;

    if (money < amount) {
        money = mSP_get_sell_price_sub(money, amount);
    } else {
        money -= amount;
    }

    Common_Get(now_private)->inventory.wallet = money;
}

static int mSP_GetNonePossessionItemCount_InList(mActor_name_t* list, int category, u32* collect_bitfield) {
    mActor_name_t* list_p;

    if (list != NULL) {
        int count = 0;

        for (list_p = list; list_p[0] != EMPTY_NO; list_p++) {
            int collect_idx;

            if (category == mSP_KIND_FURNITURE) {
                collect_idx = mRmTp_FtrItemNo2FtrIdx(list_p[0]);
            } else if (category == mSP_KIND_CARPET) {
                collect_idx = list_p[0] - ITM_CARPET_START;
            } else {
                collect_idx = list_p[0] - ITM_WALL_START;
            }

            if (((collect_bitfield[collect_idx >> 5] >> (collect_idx & 0x1F)) & 1) == 0) {
                count++;
            }
        }

        return count;
    }

    return 0;
}

static mActor_name_t mSP_GetNonePossessionItem_InList(mActor_name_t* list, int category, u32* collect_bitfield) {
    int none_count = mSP_GetNonePossessionItemCount_InList(list, category, collect_bitfield);

    if (none_count != 0 && list != NULL) {
        int selected_idx = RANDOM(none_count);
        mActor_name_t* list_p;
        int count = 0;

        for (list_p = list; list_p[0] != EMPTY_NO; list_p++) {
            int collect_idx;

            if (category == mSP_KIND_FURNITURE) {
                collect_idx = mRmTp_FtrItemNo2FtrIdx(list_p[0]);
            } else if (category == mSP_KIND_CARPET) {
                collect_idx = list_p[0] - ITM_CARPET_START;
            } else {
                collect_idx = list_p[0] - ITM_WALL_START;
            }

            if (((collect_bitfield[collect_idx >> 5] >> (collect_idx & 0x1F)) & 1) == 0) {
                if (selected_idx == count) {
                    return list_p[0];
                } else {
                    count++;
                }
            }
        }
    }

    return EMPTY_NO;
}

static mActor_name_t mSP_GetNonePossessionItem_InLotteryFurniture(int player_no) {
    return mSP_GetNonePossessionItem_InList(mSP_ftr_list[mSP_LIST_LOTTERY], mSP_KIND_FURNITURE,
                                            (player_no >= 0 && player_no < PLAYER_NUM)
                                                ? Save_Get(private_data[player_no]).furniture_collected_bitfield
                                                : Common_Get(now_private)->furniture_collected_bitfield);
}

static mActor_name_t mSP_GetNonePossessionItem_InEventFurniture(int player_no) {
    return mSP_GetNonePossessionItem_InList(mSP_ftr_list[mSP_LIST_EVENT], mSP_KIND_FURNITURE,
                                            (player_no >= 0 && player_no < PLAYER_NUM)
                                                ? Save_Get(private_data[player_no]).furniture_collected_bitfield
                                                : Common_Get(now_private)->furniture_collected_bitfield);
}

/* @fabricated @unused */
static mActor_name_t mSP_GetNonePossessionItem_InEventWall(int player_no) {
    return mSP_GetNonePossessionItem_InList(mSP_ftr_list[mSP_LIST_EVENT], mSP_KIND_WALLPAPER,
                                            (player_no >= 0 && player_no < PLAYER_NUM)
                                                ? Save_Get(private_data[player_no]).wall_collected_bitfield
                                                : Common_Get(now_private)->wall_collected_bitfield);
}

/* @fabricated @unused */
static mActor_name_t mSP_GetNonePossessionItem_InEventCarpet(int player_no) {
    return mSP_GetNonePossessionItem_InList(mSP_ftr_list[mSP_LIST_EVENT], mSP_KIND_CARPET,
                                            (player_no >= 0 && player_no < PLAYER_NUM)
                                                ? Save_Get(private_data[player_no]).carpet_collected_bitfield
                                                : Common_Get(now_private)->carpet_collected_bitfield);
}

/* @fabricated @unused */
static mActor_name_t mSP_GetNonePossessionItem_InABCFurniture(int player_no) {
    // TODO: check this impl is right using func size -- they probably did the list calc in this func itself
    u8 abc_priorities[3];

    mSP_GetGoodsPriority(abc_priorities, mSP_KIND_FURNITURE);

    return mSP_GetNonePossessionItem_InList(
        mSP_GetItemList(mSP_ftr_list, abc_priorities, mSP_LISTTYPE_ABC), mSP_KIND_FURNITURE,
        (player_no >= 0 && player_no < PLAYER_NUM) ? Save_Get(private_data[player_no]).furniture_collected_bitfield
                                                   : Common_Get(now_private)->furniture_collected_bitfield);
}

typedef mActor_name_t (*mSP_GET_NONE_POSSESSION_ITEM_PROC)(int);

static mActor_name_t mSP_CarryOutAlternativeRandomSelect(mSP_GET_NONE_POSSESSION_ITEM_PROC proc0,
                                                         mSP_GET_NONE_POSSESSION_ITEM_PROC proc1, int player_no) {
    int rng = RANDOM(100);

    if ((rng & 1)) {
        mActor_name_t item = (*proc0)(player_no);

        if (item == EMPTY_NO) {
            item = (*proc1)(player_no);

            if (item != EMPTY_NO) {
                return item;
            }
        } else {
            return item;
        }
    } else {
        mActor_name_t item = (*proc1)(player_no);

        if (item == EMPTY_NO) {
            item = (*proc0)(player_no);

            if (item != EMPTY_NO) {
                return item;
            }
        } else {
            return item;
        }
    }

    return EMPTY_NO;
}

static mActor_name_t mSP_CarryOutAlternativeRandomSelect_NoneNULL(int category0, int list0, int category1, int list1) {
    int rng = RANDOM(100);
    mActor_name_t item;

    if ((rng & 1)) {
        mSP_SelectRandomItem_New(NULL, &item, 1, NULL, 0, category0, list0, FALSE);
        return item;
    } else {
        mSP_SelectRandomItem_New(NULL, &item, 1, NULL, 0, category1, list1, FALSE);
        return item;
    }
}

/* @unused size: 0xB8 */
// extern mActor_name_t mSP_SelectNpcBirthdayPresent(...)
static void mSP_SelectNpcBirthdayPresent() {
    // necessary to include for data
    static int priority[6][3] = {
        { mSP_PRIORITY_COMMON, mSP_PRIORITY_UNCOMMON, mSP_PRIORITY_RARE },
        { mSP_PRIORITY_COMMON, mSP_PRIORITY_RARE,
          mSP_PRIORITY_RARE }, // lol based on this, I think it should've been common, rare, uncommon
        { mSP_PRIORITY_UNCOMMON, mSP_PRIORITY_COMMON, mSP_PRIORITY_RARE },
        { mSP_PRIORITY_UNCOMMON, mSP_PRIORITY_RARE, mSP_PRIORITY_COMMON },
        { mSP_PRIORITY_RARE, mSP_PRIORITY_COMMON, mSP_PRIORITY_UNCOMMON },
        { mSP_PRIORITY_RARE, mSP_PRIORITY_UNCOMMON, mSP_PRIORITY_COMMON }
    };
}

extern mActor_name_t mSP_SelectFishginPresent(int player_no) {
    mActor_name_t item = mSP_CarryOutAlternativeRandomSelect(&mSP_GetNonePossessionItem_InLotteryFurniture,
                                                             &mSP_GetNonePossessionItem_InEventFurniture, player_no);

    if (item != EMPTY_NO) {
        return item;
    }

    return mSP_CarryOutAlternativeRandomSelect_NoneNULL(mSP_KIND_FURNITURE, mSP_LISTTYPE_LOTTERY, mSP_KIND_FURNITURE,
                                                        mSP_LISTTYPE_EVENT);
}

mActor_name_t mSP_gc_famicom_table[8] = {
    FTR_START(FTR_FAMICOM_COMMON00), FTR_START(FTR_FAMICOM_COMMON01), FTR_START(FTR_FAMICOM_COMMON02), FTR_START(FTR_FAMICOM_COMMON03),
    FTR_START(FTR_FAMICOM_COMMON04), FTR_START(FTR_FAMICOM_COMMON05), FTR_START(FTR_FAMICOM_COMMON06), FTR_START(FTR_FAMICOM_COMMON13),
};

/* @unused size: 0xDC */
// static mActor_name_t mSP_RandomOneFamicomSelect(...)

static mActor_name_t mSP_AGBRandomFamicomSelect() {
    mActor_name_t item = EMPTY_NO;

    mSP_SelectRandomItem_New(NULL, &item, 1, NULL, 0, mSP_KIND_FURNITURE, mSP_LISTTYPE_ISLANDFAMICOM, FALSE);
    return item;
}

static mActor_name_t mSP_GetRandomTrash() {
    static mActor_name_t trash_table[3] = { ITM_DUST0_EMPTY_CAN, ITM_DUST1_BOOT, ITM_DUST2_OLD_TIRE };

    return trash_table[RANDOM(3)];
}

static void mSP_SelectRandomItemToAGB_Unit(mActor_name_t* item, xyz_t* wpos, int ut_x, int ut_z) {
    switch (item[0]) {
        case 0xFEB2: {
            item[0] = mSP_GetRandomTrash();
            break;
        }

        case 0xFEA1: {
            mSP_SelectRandomItem_New(NULL, item, 1, NULL, 0, mSP_KIND_FURNITURE, mSP_LISTTYPE_COMMON, FALSE);
            break;
        }

        case 0xFEA2: {
            mSP_SelectRandomItem_New(NULL, item, 1, NULL, 0, mSP_KIND_FURNITURE, mSP_LISTTYPE_RARE, FALSE);
            break;
        }

        case 0xFEA3: {
            if ((RANDOM(10) & 1)) {
                mSP_SelectRandomItem_New(NULL, item, 1, NULL, 0, mSP_KIND_FURNITURE, mSP_LISTTYPE_EVENT, FALSE);
            } else {
                mSP_SelectRandomItem_New(NULL, item, 1, NULL, 0, mSP_KIND_FURNITURE, mSP_LISTTYPE_LOTTERY, FALSE);
            }

            break;
        }

        case 0xFEA5: {
            mSP_SelectRandomItem_New(NULL, item, 1, NULL, 0, mSP_KIND_FURNITURE, mSP_LISTTYPE_ISLAND, FALSE);
            break;
        }

        case 0xFEA4: {
            item[0] = mSP_AGBRandomFamicomSelect();
            break;
        }

        case 0xFEA9: {
            mSP_RandomUmbSelect(item, 1);
            break;
        }

        case 0xFEA6: {
            item[0] = mSP_RandomOneFossilSelect((RANDOM(4) & 1));
            break;
        }

        case 0xFEA7: {
            mSP_RandomMDSelect(item, 1);
            break;
        }

        case 0xFEA8: {
            mSP_RandomHaniwaSelect(item, 1);
            break;
        }

        case 0xFEAA: {
            mSP_SelectRandomItem_New(NULL, item, 1, NULL, 0, mSP_KIND_CARPET, mSP_LISTTYPE_COMMON, FALSE);
            break;
        }

        case 0xFEAB: {
            mSP_SelectRandomItem_New(NULL, item, 1, NULL, 0, mSP_KIND_CARPET, mSP_LISTTYPE_RARE, FALSE);
            break;
        }

        case 0xFEAC: {
            mSP_SelectRandomItem_New(NULL, item, 1, NULL, 0, mSP_KIND_WALLPAPER, mSP_LISTTYPE_COMMON, FALSE);
            break;
        }

        case 0xFEAD: {
            mSP_SelectRandomItem_New(NULL, item, 1, NULL, 0, mSP_KIND_WALLPAPER, mSP_LISTTYPE_RARE, FALSE);
            break;
        }

        case 0xFEAE: {
            mSP_SelectRandomItem_New(NULL, item, 1, NULL, 0, mSP_KIND_CLOTH, mSP_LISTTYPE_COMMON, FALSE);
            break;
        }

        case 0xFEAF: {
            mSP_SelectRandomItem_New(NULL, item, 1, NULL, 0, mSP_KIND_CLOTH, mSP_LISTTYPE_RARE, FALSE);
            break;
        }

        case 0xFEB0: {
            int hole_no = mCoBG_GetHoleNumber(*wpos);

            if (hole_no != -1) {
                item[0] = HOLE_START + (mActor_name_t)hole_no;
            } else {
                item[0] = EMPTY_NO;
            }

            break;
        }

        case 0xFEB1: {
            item[0] = ITM_WHITE_PANSY_BAG + RANDOM(FLOWER_NUM);
            break;
        }

        case ITM_KABU_10:
        case ITM_KABU_50:
        case ITM_KABU_100: {
            item[0] = ITM_KABU_SPOILED; // spoil any turnips
            break;
        }

        case 0xF11F: {
            item[0] = ACTOR_PROP_VILLAGER_SIGNBOARD;
            break;
        }
    }
}

#if VERSION == VER_GAFE01_00
// @fakematch
// @HACK - we shouldn't have to force propagation off, nor access the Save_t* struct directly
#pragma opt_propagation off
extern void mSP_SelectRandomItemToAGB() {
    int i;
    int ut_x;
    int ut_z;
    xyz_t* wpos_p;
    mActor_name_t* start_p;
    mActor_name_t* item_p;
    Save_t* save;
    xyz_t tpos;

    xyz_t wpos = { 0.0f, 0.0f, 0.0f };
    int bx = 0;
    int bz = 0;

    mFI_BlockKind2BkNum(&bx, &bz, mRF_BLOCKKIND_ISLAND_LEFT);
    save = &Common_Get(save.save);

    /* convert all unit island items to valid items */
    for (i = 0; i < mISL_FG_BLOCK_X_NUM; i++) {
        item_p = &save->island.fgblock[0][i].items[0][0];

        mFI_BkNum2WposXZ(&wpos.x, &wpos.z, bx + i, bz);
        wpos.x += mFI_UT_WORLDSIZE_HALF_X_F;
        wpos.z += mFI_UT_WORLDSIZE_HALF_Z_F;
        tpos.x = wpos.x;

        for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
            wpos.x = tpos.x;

            for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
                mSP_SelectRandomItemToAGB_Unit(item_p, &wpos, ut_x, ut_z);
                wpos.x += mFI_UT_WORLDSIZE_X_F;
                item_p++;
            }

            wpos.z += mFI_UT_WORLDSIZE_Z_F;
        }
    }

    /* add correctly placed signboard actor */
    for (i = 0; i < mISL_FG_BLOCK_X_NUM; i++) {
        save = Common_GetPointer(save.save);
        start_p = &save->island.fgblock[0][i].items[0][0];
        item_p = &save->island.fgblock[0][i].items[0][0];

        for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
            for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
                if (item_p[0] == COTTAGE_NPC) {
                    start_p[((ut_x - 1) & 15) + (((ut_z + 1) & 0xF) << 4)] = ACTOR_PROP_VILLAGER_SIGNBOARD;
                }

                item_p++;
            }
        }
    }

    /* remove incorrectly placed signboard actors */
    save = Common_GetPointer(save.save);
    for (i = 0; i < mISL_FG_BLOCK_X_NUM; i++) {
        start_p = &save->island.fgblock[0][i].items[0][0];
        item_p = &save->island.fgblock[0][i].items[0][0];

        for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
            for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
                if (item_p[0] == ACTOR_PROP_VILLAGER_SIGNBOARD &&
                    start_p[((ut_x + 1) & 15) + (((ut_z - 1) & 0xF) << 4)] != COTTAGE_NPC) {
                    item_p[0] = EMPTY_NO;
                }

                item_p++;
            }
        }
    }
    wpos.z = wpos.z;
}
#pragma opt_propagation reset
#else
extern void mSP_SelectRandomItemToAGB() {
    int i;
    int ut_x;
    int ut_z;
    xyz_t* wpos_p;
    mActor_name_t* start_p;
    mActor_name_t* item_p;
    xyz_t tpos;

    xyz_t wpos = { 0.0f, 0.0f, 0.0f };
    int bx = 0;
    int bz = 0;

    mFI_BlockKind2BkNum(&bx, &bz, mRF_BLOCKKIND_ISLAND_LEFT);

    /* convert all unit island items to valid items */
    for (i = 0; i < mISL_FG_BLOCK_X_NUM; i++) {
        item_p = &Save_Get(island).fgblock[0][i].items[0][0];

        mFI_BkNum2WposXZ(&wpos.x, &wpos.z, bx + i, bz);
        wpos.x += mFI_UT_WORLDSIZE_HALF_X_F;
        wpos.z += mFI_UT_WORLDSIZE_HALF_Z_F;
        tpos.x = wpos.x;

        for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
            wpos.x = tpos.x;

            for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
                mSP_SelectRandomItemToAGB_Unit(item_p, &wpos, ut_x, ut_z);
                wpos.x += mFI_UT_WORLDSIZE_X_F;
                item_p++;
            }

            wpos.z += mFI_UT_WORLDSIZE_Z_F;
        }
    }

    /* add correctly placed signboard actor */
    for (i = 0; i < mISL_FG_BLOCK_X_NUM; i++) {
        item_p = &Save_Get(island).fgblock[0][i].items[0][0];
        
        for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
            for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
                start_p = &Save_Get(island).fgblock[0][i].items[0][0];
                if (item_p[0] == COTTAGE_NPC) {
                    start_p[(((ut_x - 1) & 15) + (((ut_z + 1) & 0xF) << 4))] = ACTOR_PROP_VILLAGER_SIGNBOARD;
                }

                item_p++;
            }
        }
    }

    /* remove incorrectly placed signboard actors */
    for (i = 0; i < mISL_FG_BLOCK_X_NUM; i++) {
        item_p = &Save_Get(island).fgblock[0][i].items[0][0];
        start_p = &Save_Get(island).fgblock[0][i].items[0][0];

        for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
            for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
                if (item_p[0] == ACTOR_PROP_VILLAGER_SIGNBOARD &&
                    start_p[((ut_x + 1) & 15) + (((ut_z - 1) & 0xF) << 4)] != COTTAGE_NPC) {
                    item_p[0] = EMPTY_NO;
                }

                item_p++;
            }
        }
    }
    wpos.z = wpos.z;
}
#endif

extern const char* mSP_ShopStatus2String(int status) {
    static char dummy[] = "hahaha";

    static char* str_table[mSP_SHOP_STATUS_NUM] = { "Pre", "End", "Opn", "Rnw", "PreEv", "EndEv", "OpnEv" };

    if (status >= 0 && status < mSP_SHOP_STATUS_NUM) {
        return str_table[status];
    }

    return dummy;
}

extern mActor_name_t mSP_GetRandomStationToyItemNo() {
    /* TODO: where does this go? DnM+ indicates no unused functions after this, but data appears after str_table in
     * mSP_ShopStatus2String */
    static mActor_name_t train[2] = { FTR_START(FTR_IKE_K_KID01), FTR_START(FTR_IKE_K_KID02) };

    /* TODO: furniture item index enum/defines */
    return mRmTp_FtrIdx2FtrItemNo(0x42A + RANDOM(15), mRmTp_DIRECT_SOUTH);
}

#include "../src/game/m_item_debug.c"
