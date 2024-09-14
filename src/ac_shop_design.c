#include "ac_shop_design.h"

#include "m_common_data.h"
#include "m_name_table.h"

static void Shop_Design_Actor_ct(ACTOR* actorx, GAME* game);
static void Shop_Design_Actor_dt(ACTOR* actorx, GAME* game);
static void Shop_Design_Actor_move(ACTOR* actorx, GAME* game);
static void Shop_Design_Actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Shop_Design_Profile = {
    mAc_PROFILE_SHOP_DESIGN,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(SHOP_DESIGN_ACTOR),
    &Shop_Design_Actor_ct,
    &Shop_Design_Actor_dt,
    &Shop_Design_Actor_move,
    &Shop_Design_Actor_draw,
    NULL,
};

static mActor_name_t aSD_ItemName2ReservePointName(mActor_name_t item) {
    int tanuki_shop_status = Common_Get(tanuki_shop_status);

    if (tanuki_shop_status == mSP_TANUKI_SHOP_STATUS_EVENT) {
        return RSV_SHOP_EVENT;
    }

    if (item == ITM_SIGNBOARD) {
        return RSV_SHOP_SIGNBOARD;
    }

    if (ITEM_IS_FTR(item)) {
        return RSV_SHOP_FTR;
    }

    if (item == RSV_SHOP_SOLD_FTR) {
        return RSV_SHOP_FTR;
    }

    if ((item >= ITM_PAPER_START && item <= ITM_PAPER_END) || (item >= ITM_DIARY00 && item <= ITM_DIARY15)) {
        return RSV_SHOP_PAPER;
    }

    if (item == RSV_SHOP_SOLD_PAPER) {
        return RSV_SHOP_PAPER;
    }

    if (item >= ITM_CARPET_START && item <= (ITM_CARPET_END - 4)) {
        return RSV_SHOP_CARPET;
    }

    if (item == RSV_SHOP_SOLD_CARPET) {
        return RSV_SHOP_CARPET;
    }

    if (item >= ITM_WALL_START && item <= (ITM_WALL_END - 4)) {
        return RSV_SHOP_WALL;
    }

    if (item == RSV_SHOP_SOLD_WALL) {
        return RSV_SHOP_WALL;
    }

    if (item >= ITM_CLOTH_START && item <= ITM_CLOTH_END) {
        return RSV_SHOP_CLOTH;
    }

    if (item == RSV_SHOP_SOLD_CLOTH) {
        return RSV_SHOP_CLOTH;
    }

    if (item >= ITM_TOOL_START && item <= ITM_TOOL_END) {
        if (item >= ITM_UMBRELLA_START && item <= (ITM_UMBRELLA_END - 1)) {
            return RSV_SHOP_UMBRELLA;
        }

        if (item >= ITM_RED_PAINT && item <= ITM_BROWN_PAINT) {
            return RSV_SHOP_PAINT;
        }

        /* @BUG - this is impossible to reach, maybe signboard used to be in the TOOL category before? */
        if (item == ITM_SIGNBOARD) {
            return RSV_SHOP_SIGNBOARD;
        }

        return RSV_SHOP_TOOL;
    }

    if (item == RSV_SHOP_SOLD_TOOL) {
        return RSV_SHOP_TOOL;
    }

    if (item == RSV_SHOP_SOLD_UMBRELLA) {
        return RSV_SHOP_UMBRELLA;
    }

    if (item == RSV_SHOP_SOLD_PAINT) {
        return RSV_SHOP_PAINT;
    }

    if (item == RSV_SHOP_SOLD_SIGNBOARD) {
        return RSV_SHOP_SIGNBOARD;
    }

    if ((item >= ITM_SAPLING && item <= ITM_CEDAR_SAPLING) ||
        ((item >= ITM_WHITE_PANSY_BAG && item <= ITM_YELLOW_TULIP_BAG &&
          tanuki_shop_status == mSP_TANUKI_SHOP_STATUS_HALLOWEEN))) {
        return RSV_SHOP_HALLOWEEN;
    }

    if ((item >= ITM_WHITE_PANSY_BAG && item <= ITM_YELLOW_TULIP_BAG) || item == ITM_FOOD_CANDY) {
        return RSV_SHOP_PLANT;
    }

    return EMPTY_NO;
}

static void aSD_MakeHukubukuroFg(void) {
    static mActor_name_t reserve_table[] = {
        RSV_SHOP_TOOL, RSV_SHOP_SIGNBOARD, RSV_SHOP_PAINT, RSV_SHOP_PAPER, RSV_SHOP_HALLOWEEN, RSV_SHOP_PLANT,
    };
    int n = Save_Get(shop).flowers_candy_grab_bag_count;
    int i;

    /* Search all reserve items */
    for (i = 0; i < ARRAY_COUNT(reserve_table); i++) {
        /* Replace all reserve items of this type to grab bags */
        while (n > 0 && mSP_SetGoods2ReservedPoint(ITM_HUKUBUKURO_BAG, reserve_table[i]) != FALSE) {
            n--;
        }
    }

    /* Search all reserve items */
    for (i = 0; i < ARRAY_COUNT(reserve_table); i++) {
        /* Replace any left with reserve RSV_SHOP_SOLD_PLANT */
        while (mSP_SetGoods2ReservedPoint(RSV_SHOP_SOLD_PLANT, reserve_table[i]) != FALSE) {}
    }
}

static void aSD_MakePlantFg_normal(void) {
    while (mSP_SetGoods2ReservedPoint(RSV_SHOP_SOLD_PLANT, RSV_SHOP_HALLOWEEN) != FALSE) {}
    while (mSP_SetGoods2ReservedPoint(RSV_SHOP_SOLD_PLANT, RSV_SHOP_PLANT) != FALSE) {}
}

static void aSD_MakePlantFg_hal(void) {
    int n = Save_Get(shop).flowers_candy_grab_bag_count;

    /* Fill plant spots with candy */
    while (n > 0 && mSP_SetGoods2ReservedPoint(ITM_FOOD_CANDY, RSV_SHOP_PLANT) != FALSE) {
        n--;
    }

    /* Clear the remaining plant reserve spots */
    while (mSP_SetGoods2ReservedPoint(RSV_SHOP_SOLD_PLANT, RSV_SHOP_PLANT) != FALSE) {}
}

static void aSD_MakePlantFg(void) {
    if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_HALLOWEEN) {
        aSD_MakePlantFg_hal();
    } else {
        aSD_MakePlantFg_normal();
    }
}

static void aSD_MakeGoodsFg(mActor_name_t* goods_p, int count) {
    int i;

    for (i = 0; i < count; i++) {
        if (goods_p[i] != EMPTY_NO) {
            mActor_name_t reserve_name = aSD_ItemName2ReservePointName(goods_p[i]);

            if (reserve_name != EMPTY_NO) {
                mSP_SetGoods2ReservedPoint(goods_p[i], reserve_name);
            }
        }
    }
}

/* Mispelling of 'rare' */
static void aSD_MakeReaGoodsFg(mActor_name_t item) {
    if (item != EMPTY_NO) {
        mSP_SetGoods2ReservedPoint(item, RSV_SHOP_RARE);
    }
}

static void aSD_MakeLotteryGoodsFg(mActor_name_t* lottery_items) {
    mSP_SetGoods2ReservedPoint(lottery_items[2], RSV_SHOP_FTR);
    mSP_SetGoods2ReservedPoint(lottery_items[0], RSV_SHOP_FTR);
    mSP_SetGoods2ReservedPoint(lottery_items[1], RSV_SHOP_FTR);
}

static mActor_name_t aSD_UnitNum2ItemNo(int ux, int uz);
static int aSD_ReportGoodsSales(int ux, int uz);

static void aSD_SetClipProc(ACTOR* actorx, int clear) {
    SHOP_DESIGN_ACTOR* shop_design = (SHOP_DESIGN_ACTOR*)actorx;

    if (clear) {
        Common_Get(clip).shop_design_clip = NULL;
    } else {
        Common_Get(clip).shop_design_clip = &shop_design->clip;
        shop_design->clip.design_actor = shop_design;
        shop_design->clip.unitNum2ItemNo_proc = &aSD_UnitNum2ItemNo;
        shop_design->clip.reportGoodsSale_proc = &aSD_ReportGoodsSales;
    }
}

static void aSD_GetGoodsInfo(SHOP_DESIGN_ACTOR* shop_design) {
    if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_EVENT) {
        int count = 0;
        int i;

        shop_design->goods_list = Save_Get(event_save_data).special.event.bargin.items;
        shop_design->goods_list_max = mEv_BARGIN_ITEM_NUM;
        for (i = 0; i < mEv_BARGIN_ITEM_NUM; i++) {
            if (shop_design->goods_list[i] != EMPTY_NO) {
                count++;
            }
        }
        shop_design->goods_list_count = count;
    } else {
        shop_design->goods_list = Save_Get(shop).items;
        shop_design->goods_list_count = mSP_CountElementInGoodsList();
        shop_design->goods_list_max = mSP_GOODS_COUNT;
    }

    /* Check if player is from a different town and, if so, set the flag for Nookington's */
    mSP_SetNewVisitor();
}

static void aSD_SetReservedPointFill000(void) {
    mActor_name_t* fg_p = mFI_BkNumtoUtFGTop(0, 0);
    int i;

    for (i = 0; i < UT_TOTAL_NUM; i++) {
        if (fg_p[i] >= RSV_SHOP_PAPER && fg_p[i] <= RSV_SHOP_SIGNBOARD) {
            fg_p[i] = RSV_NO; // TODO: I suppose RSV_NO is actually called 'FILL000'
        }
    }
}

static void Shop_Design_Actor_ct(ACTOR* actorx, GAME* game) {
    SHOP_DESIGN_ACTOR* shop_design = (SHOP_DESIGN_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    int scene_no = Save_Get(scene_no);

    actorx->actor_specific = -1; // no valid shop type
    if (scene_no == SCENE_SHOP0) {
        actorx->actor_specific = 0;
    } else if (scene_no == SCENE_CONVENI) {
        actorx->actor_specific = 1;
    } else if (scene_no == SCENE_SUPER) {
        actorx->actor_specific = 2;
    } else if (scene_no == SCENE_DEPART) {
        actorx->actor_specific = 3;
    }

    /* Check if the shop is currently having the monthly lottery raffle */
    if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI && actorx->actor_specific != -1) {
        /* garagara likely referes to ガラガラ抽選 or 'raffle drum/rattle lottery' */
        static xyz_t garagara_set_table[] = {
            { 160.0f, 60.0f, 190.0f }, /* Nook's Cranny */
            { 240.0f, 60.0f, 190.0f }, /* Nook 'n' Go */
            { 240.0f, 60.0f, 350.0f }, /* Nookway */
            { 240.0f, 60.0f, 350.0f }, /* Nookington's */
            { 160.0f, 60.0f, 180.0f }, /* Nookington's 2nd floor? */
        };

        /* Make the raffle drum actor */
        Actor_info_make_actor(&play->actor_info, game, mAc_PROFILE_GARAGARA,
                              garagara_set_table[actorx->actor_specific].x,
                              garagara_set_table[actorx->actor_specific].y,
                              garagara_set_table[actorx->actor_specific].z, 0, 0, 0, -1, -1, -1, EMPTY_NO, 0, -1, -1);
    }

    if (scene_no == SCENE_SHOP0 || scene_no == SCENE_CONVENI || scene_no == SCENE_SUPER || scene_no == SCENE_DEPART ||
        scene_no == SCENE_DEPART_2) {
        aSD_GetGoodsInfo(shop_design);
        if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_FUKUBIKI) {
            aSD_MakeLotteryGoodsFg(Save_Get(shop).lottery_items);
        } else {
            aSD_MakeGoodsFg(shop_design->goods_list, shop_design->goods_list_count);
            if (Common_Get(tanuki_shop_status) != mSP_TANUKI_SHOP_STATUS_EVENT) {
                aSD_MakeReaGoodsFg(Save_Get(shop).rare_item);
                if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_HUKUBUKURO_SALE) {
                    aSD_MakeHukubukuroFg();
                } else {
                    aSD_MakePlantFg();
                }
            }
        }

        aSD_SetReservedPointFill000();
        aSD_SetClipProc(actorx, FALSE);
    }
}

static void Shop_Design_Actor_dt(ACTOR* actorx, GAME* game) {
    aSD_SetClipProc(actorx, TRUE);
}

static void Shop_Design_Actor_draw(ACTOR* actorx, GAME* game) {
    // nothing
}

static void Shop_Design_Actor_move(ACTOR* actorx, GAME* game) {
    // nothing
}

static mActor_name_t aSD_UnitNum2ItemNo(int ux, int uz) {
    int bx = ux / UT_X_NUM;
    int bz = uz / UT_Z_NUM;
    mActor_name_t* fg_p = mFI_BkNumtoUtFGTop(bx, bz);
    int local_ux = ux - bx * UT_X_NUM;
    int local_uz = uz - bz * UT_Z_NUM;
    mActor_name_t item = fg_p[local_ux + local_uz * UT_X_NUM];

    if ((item >= RSV_SHOP_FE0D && item <= RSV_SHOP_SOLD_SIGNBOARD)) {
        return RSV_NO;
    }

    if (
        // clang-format off
        ITEM_IS_FTR(item) ||
        (item >= ITM_PAPER_START && item <= ITM_PAPER_END) ||
        (item >= ITM_CARPET_START && item <= ITM_CARPET_END - 4) ||
        (item >= ITM_WALL_START && item <= ITM_WALL_END - 4) ||
        (item >= ITM_CLOTH_START && item <= ITM_CLOTH_END) ||
        (item >= ITM_TOOL_START && item <= ITM_TOOL_END) ||
        (item >= ITM_SAPLING && item <= ITM_CEDAR_SAPLING) ||
        (item >= ITM_WHITE_PANSY_BAG && item <= ITM_YELLOW_TULIP_BAG) ||
        (item >= ITM_DIARY00 && item <= ITM_DIARY15) ||
        (item == ITM_FOOD_CANDY) ||
        (item == RSV_FE1F) ||
        (item == ITM_HUKUBUKURO_BAG) ||
        (item == ITM_SIGNBOARD)
        // clang-format on
    ) {
        if (item == RSV_FE1F) {
            if (Common_Get(clip).my_room_clip != NULL) {
                mActor_name_t ftr_item;

                Common_Get(clip).my_room_clip->unitNum2ftrItemNoftrId_proc(&ftr_item, NULL, ux, uz, mCoBG_LAYER0);
                return ftr_item;
            } else {
                return RSV_NO;
            }
        } else {
            return item;
        }
    } else {
        return RSV_NO;
    }
}

static int aSD_ReportGoodsSales(int ux, int uz) {
    mActor_name_t item = aSD_UnitNum2ItemNo(ux, uz);
    u32 price = mSP_ItemNo2ItemPrice(item);
    mActor_name_t rsv_item = EMPTY_NO;

    if (Common_Get(clip).shop_design_clip != NULL) {
        SHOP_DESIGN_ACTOR* shop_design = Common_Get(clip).shop_design_clip->design_actor;

        mSP_PlusSales(price);
        if (item == ITM_HUKUBUKURO_BAG) {
            mSP_ShopSaleReport(item, shop_design->goods_list, shop_design->goods_list_max, RSV_SHOP_SOLD_PLANT);
            mFI_UtNumtoFGSet_common(RSV_SHOP_SOLD_PLANT, ux, uz, FALSE);
            return FALSE;
        } else if ((item >= ITM_SAPLING && item <= ITM_CEDAR_SAPLING) ||
                   (item >= ITM_WHITE_PANSY_BAG && item <= ITM_YELLOW_TULIP_BAG) || item == ITM_FOOD_CANDY) {
            if (mSP_ShopSaleReport(item, shop_design->goods_list, shop_design->goods_list_max, RSV_SHOP_SOLD_PLANT)) {
                return TRUE;
            } else {
                mFI_UtNumtoFGSet_common(RSV_SHOP_SOLD_PLANT, ux, uz, FALSE);
                return FALSE;
            }
        } else if (item >= ITM_CLOTH_START && item <= ITM_CLOTH_END) {
            mSP_ShopSaleReport(item, shop_design->goods_list, shop_design->goods_list_max, RSV_SHOP_SOLD_CLOTH);
            Common_Get(clip).shop_manekin_clip->change2naked_manekin_proc(ux, uz);
            mFI_UtNumtoFGSet_common(RSV_NO, ux, uz, FALSE);
            return FALSE;
        } else if (ITEM_IS_FTR(item) && Common_Get(clip).my_room_clip != NULL) {
            mActor_name_t ftr_item;
            int ftrID;

            Common_Get(clip).my_room_clip->unitNum2ftrItemNoftrId_proc(&ftr_item, &ftrID, ux, uz, mCoBG_LAYER0);
            Common_Get(clip).my_room_clip->ftrId2extinguishFtr_proc(ftrID);
            if (item == Save_Get(shop).rare_item) {
                rsv_item = RSV_SHOP_SOLD_RARE;
            } else {
                rsv_item = RSV_SHOP_SOLD_FTR;
            }
        }

        if (item >= ITM_CARPET_START && item <= (ITM_CARPET_END - 4)) {
            rsv_item = RSV_SHOP_SOLD_CARPET;
        }

        if (item >= ITM_WALL_START && item <= (ITM_WALL_END - 4)) {
            rsv_item = RSV_SHOP_SOLD_WALL;
        }

        if (item == ITM_SIGNBOARD) {
            rsv_item = RSV_SHOP_SOLD_SIGNBOARD;
        }

        if (item >= ITM_TOOL_START && item <= ITM_TOOL_END) {
            if (item >= ITM_UMBRELLA_START && item <= (ITM_UMBRELLA_END - 1)) {
                if (Common_Get(clip).shop_umbrella_clip != NULL) {
                    Common_Get(clip).shop_umbrella_clip->delete_umbrella_proc(ux, uz);
                }

                rsv_item = RSV_SHOP_SOLD_UMBRELLA;
            } else if (item >= ITM_RED_PAINT && item <= ITM_BROWN_PAINT) {
                rsv_item = RSV_SHOP_SOLD_PAINT;
            } else if (item == ITM_SIGNBOARD) {
                rsv_item = RSV_SHOP_SOLD_SIGNBOARD;
            } else {
                rsv_item = RSV_SHOP_SOLD_TOOL;
            }
        }

        if (item >= ITM_PAPER_START && item <= ITM_PAPER_END) {
            return TRUE;
        }

        if (item >= ITM_DIARY00 && item <= ITM_DIARY15) {
            rsv_item = RSV_SHOP_SOLD_PAPER;
        }

        if (Common_Get(tanuki_shop_status) == mSP_TANUKI_SHOP_STATUS_EVENT && mEv_CheckEvent(mEv_SPNPC_SHOP) == FALSE) {
            return FALSE;
        }

        if (rsv_item != EMPTY_NO) {
            if (mSP_ShopSaleReport(item, shop_design->goods_list, shop_design->goods_list_max, rsv_item)) {
                return TRUE;
            }

            mFI_UtNumtoFGSet_common(rsv_item, ux, uz, FALSE);
        }

        return FALSE;
    } else {
        return FALSE;
    }
}
