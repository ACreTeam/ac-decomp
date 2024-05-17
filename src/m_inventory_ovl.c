#include "m_inventory_ovl.h"

#include "m_player_lib.h"
#include "ac_set_ovl_gyoei.h"
#include "ac_set_ovl_insect.h"
#include "m_room_type.h"
#include "m_common_data.h"

enum {
    mIV_ANIM_WALK,
    mIV_ANIM_CATCH,
    mIV_ANIM_CHANGE,
    mIV_ANIM_EAT,

    mIV_ANIM_NUM
};

enum {
    mIV_ITEM_KIND_AXE,
    mIV_ITEM_KIND_NET,
    mIV_ITEM_KIND_UMBRELLA,
    mIV_ITEM_KIND_ROD,
    mIV_ITEM_KIND_SHOVEL,

    mIV_ITEM_KIND_GOLD_AXE,
    mIV_ITEM_KIND_GOLD_NET,
    mIV_ITEM_KIND_GOLD_ROD,
    mIV_ITEM_KIND_GOLD_SHOVEL,

    mIV_ITEM_KIND_RED_BALLOON,
    mIV_ITEM_KIND_YELLOW_BALLOON,
    mIV_ITEM_KIND_BLUE_BALLOON,
    mIV_ITEM_KIND_GREEN_BALLOON,
    mIV_ITEM_KIND_PURPLE_BALLOON,
    mIV_ITEM_KIND_BUNNY_P_BALLOON,
    mIV_ITEM_KIND_BUNNY_B_BALLOON,
    mIV_ITEM_KIND_BUNNY_O_BALLOON,

    mIV_ITEM_KIND_YELLOW_PINWHEEL,
    mIV_ITEM_KIND_RED_PINWHEEL,
    mIV_ITEM_KIND_TIGER_PINWHEEL,
    mIV_ITEM_KIND_GREEN_PINWHEEL,
    mIV_ITEM_KIND_PINK_PINWHEEL,
    mIV_ITEM_KIND_STRIPED_PINWHEEL,
    mIV_ITEM_KIND_FLOWER_PINWHEEL,
    mIV_ITEM_KIND_FANCY_PINWHEEL,

    mIV_ITEM_KIND_BLUEBELL_FAN,
    mIV_ITEM_KIND_PLUM_FAN,
    mIV_ITEM_KIND_BAMBOO_FAN,
    mIV_ITEM_KIND_CLOUD_FAN,
    mIV_ITEM_KIND_MAPLE_FAN,
    mIV_ITEM_KIND_FAN_FAN,
    mIV_ITEM_KIND_FLOWER_FAN,
    mIV_ITEM_KIND_LEAF_FAN,

    mIV_ITEM_KIND_AXE_USE_1,
    mIV_ITEM_KIND_AXE_USE_2,
    mIV_ITEM_KIND_AXE_USE_3,
    mIV_ITEM_KIND_AXE_USE_4,
    mIV_ITEM_KIND_AXE_USE_5,
    mIV_ITEM_KIND_AXE_USE_6,
    mIV_ITEM_KIND_AXE_USE_7,

    mIV_ITEM_KIND_NUM
};

static int mIV_Get_pl_main_anime_index(int type) {
    static u16 player_main_animation_index_table[mIV_ANIM_NUM] = {
        mPlayer_ANIM_WALK1,
        mPlayer_ANIM_MENU_CATCH1,
        mPlayer_ANIM_MENU_CHANGE1,
        mPlayer_ANIM_EAT1,
    };

    if (type >= mIV_ANIM_WALK && type < mIV_ANIM_NUM) {
        return player_main_animation_index_table[type];
    }

    return -1;
}

// clang-format off
#define F(n) aSOG_FISH_TYPE_##n

/* Fish collection layout */
static u8 mIV_fish_collect_list[] = {
    F(CRUCIAN_CARP), F(BROOK_TROUT),     F(CARP),             F(KOI),       F(BARBEL_STEED),  F(DACE),          F(CATFISH),         F(GIANT_CATFISH),
    F(PALE_CHUB),    F(BITTERLING),      F(LOACH),            F(BLUEGILL),  F(SMALL_BASS),    F(BASS),          F(LARGE_BASS),      F(GIANT_SNAKEHEAD),
    F(EEL),          F(FRESHWATER_GOBY), F(POND_SMELT),       F(SWEETFISH), F(CHERRY_SALMON), F(RAINBOW_TROUT), F(LARGE_CHAR),      F(STRINGFISH),
    F(SALMON),       F(GOLDFISH),        F(POPEYED_GOLDFISH), F(GUPPY),     F(ANGELFISH),     F(PIRANHA),       F(AROWANA),         F(COELACANTH),
    F(CRAWFISH),     F(FROG),            F(KILLIFISH),        F(JELLYFISH), F(SEA_BASS),      F(RED_SNAPPER),   F(BARRED_KNIFEJAW), F(ARAPAIMA),
};
#undef F
// clang-format on

// clang-format off
#define I(n) aSOI_INSECT_TYPE_##n

/* Insect collection layout */
static u8 mIV_insect_collect_list[] = {
    I(COMMON_BUTTERFLY), I(YELLOW_BUTTERFLY), I(TIGER_BUTTERFLY),  I(PURPLE_BUTTERFLY), I(BROWN_CICADA),     I(ROBUST_CICADA),  I(WALKER_CICADA),    I(EVENING_CICADA),
    I(RED_DRAGONFLY),    I(COMMON_DRAGONFLY), I(DARNER_DRAGONFLY), I(BANDED_DRAGONFLY), I(CRICKET),          I(GRASSHOPPER),    I(PINE_CRICKET),     I(BELL_CRICKET),
    I(LADYBUG),          I(SPOTTED_LADYBUG),  I(MANTIS),           I(LONG_LOCUST),      I(MIGRATORY_LOCUST), I(COCKROACH),      I(BEE),              I(FIREFLY),
    I(DRONE_BEETLE),     I(LONGHORN_BEETLE),  I(JEWEL_BEETLE),     I(DYNASTID_BEETLE),  I(FLAT_STAG_BEETLE), I(SAW_STAG_BEETLE), I(MOUNTAIN_BEETLE), I(GIANT_BEETLE),
    I(POND_SKATER),      I(ANT),              I(PILL_BUG),         I(MOSQUITO),         I(MOLE_CRICKET),     I(SPIDER),          I(SNAIL),           I(BAGWORM),
};
#undef I
// clang-format on

static mActor_name_t mIV_set_collect_itemNo(int type, int page) {
    if (type == mIV_PAGE_INSECT_COLLECTION) {
        int insect_no = mIV_insect_collect_list[type];
        int bit = mRmTp_FtrItemNo2FtrIdx(FTR_INSECT_START + FTR_NO_2_IDX(insect_no));

        if (Now_Private->furniture_collected_bitfield[bit >> 5] & (1 << (bit & 31)) != 0) {
            return ITM_INSECT_START + insect_no;
        } else {
            return EMPTY_NO;
        }
    } else {
        int fish_no = mIV_fish_collect_list[type];
        int bit = FTR_IDX_2_NO(FTR_NO_2_IDX(0x31A) + FTR_NO_2_IDX(fish_no));

        if (Now_Private->furniture_collected_bitfield[bit >> 5] & (1 << (bit & 31)) != 0) {
            return mNT_FishIdx2FishItemNo(fish_no);
        } else {
            return EMPTY_NO;
        }
    }
}

static int mIV_get_player_item_anime_id(void) {
    mActor_name_t item = Now_Private->equipment;

    if (item >= ITM_NET && item <= ITM_NET) {
        return mIV_ITEM_KIND_NET;
    }

    if (item == ITM_AXE) {
        return mIV_ITEM_KIND_AXE;
    }

    if (item == ITM_GOLDEN_AXE) {
        return mIV_ITEM_KIND_GOLD_AXE;
    }

    if (item == ITM_AXE_USE_1) {
        return mIV_ITEM_KIND_AXE_USE_1;
    }

    if (item == ITM_AXE_USE_2) {
        return mIV_ITEM_KIND_AXE_USE_2;
    }

    if (item == ITM_AXE_USE_3) {
        return mIV_ITEM_KIND_AXE_USE_3;
    }

    if (item == ITM_AXE_USE_4) {
        return mIV_ITEM_KIND_AXE_USE_4;
    }

    if (item == ITM_AXE_USE_5) {
        return mIV_ITEM_KIND_AXE_USE_5;
    }

    if (item == ITM_AXE_USE_6) {
        return mIV_ITEM_KIND_AXE_USE_6;
    }

    if (item == ITM_AXE_USE_7) {
        return mIV_ITEM_KIND_AXE_USE_7;
    }

    if (item >= ITM_ROD && item <= ITM_ROD) {
        return mIV_ITEM_KIND_ROD;
    }

    if (item >= ITM_UMBRELLA_START && item <= ITM_MY_ORG_UMBRELLA7) {
        return mIV_ITEM_KIND_UMBRELLA;
    }

    if (item >= ITM_SHOVEL && item <= ITM_SHOVEL) {
        return mIV_ITEM_KIND_SHOVEL;
    }

    /* duplicate golden axe check */
    if (item >= ITM_GOLDEN_AXE && item <= ITM_GOLDEN_AXE) {
        return mIV_ITEM_KIND_GOLD_AXE;
    }

    if (item >= ITM_GOLDEN_NET && item <= ITM_GOLDEN_NET) {
        return mIV_ITEM_KIND_GOLD_NET;
    }

    if (item >= ITM_GOLDEN_ROD && item <= ITM_GOLDEN_ROD) {
        return mIV_ITEM_KIND_GOLD_ROD;
    }

    if (item >= ITM_GOLDEN_SHOVEL && item <= ITM_GOLDEN_SHOVEL) {
        return mIV_ITEM_KIND_GOLD_SHOVEL;
    }

    if (item == ITM_RED_BALLOON) {
        return mIV_ITEM_KIND_RED_BALLOON;
    }

    if (item == ITM_YELLOW_BALLOON) {
        return mIV_ITEM_KIND_YELLOW_BALLOON;
    }

    if (item == ITM_BLUE_BALLOON) {
        return mIV_ITEM_KIND_BLUE_BALLOON;
    }

    if (item == ITM_GREEN_BALLOON) {
        return mIV_ITEM_KIND_GREEN_BALLOON;
    }

    if (item == ITM_PURPLE_BALLOON) {
        return mIV_ITEM_KIND_PURPLE_BALLOON;
    }

    if (item == ITM_BUNNY_P_BALLOON) {
        return mIV_ITEM_KIND_BUNNY_P_BALLOON;
    }

    if (item == ITM_BUNNY_B_BALLOON) {
        return mIV_ITEM_KIND_BUNNY_B_BALLOON;
    }

    if (item == ITM_BUNNY_O_BALLOON) {
        return mIV_ITEM_KIND_BUNNY_O_BALLOON;
    }

    if (item == ITM_YELLOW_PINWHEEL) {
        return mIV_ITEM_KIND_YELLOW_PINWHEEL;
    }

    if (item == ITM_RED_PINWHEEL) {
        return mIV_ITEM_KIND_RED_PINWHEEL;
    }

    if (item == ITM_TIGER_PINWHEEL) {
        return mIV_ITEM_KIND_TIGER_PINWHEEL;
    }

    if (item == ITM_GREEN_PINWHEEL) {
        return mIV_ITEM_KIND_GREEN_PINWHEEL;
    }

    if (item == ITM_PINK_PINWHEEL) {
        return mIV_ITEM_KIND_PINK_PINWHEEL;
    }

    if (item == ITM_STRIPED_PINWHEEL) {
        return mIV_ITEM_KIND_STRIPED_PINWHEEL;
    }

    if (item == ITM_FLOWER_PINWHEEL) {
        return mIV_ITEM_KIND_FLOWER_PINWHEEL;
    }

    if (item == ITM_FANCY_PINWHEEL) {
        return mIV_ITEM_KIND_FANCY_PINWHEEL;
    }

    if (item == ITM_BLUEBELL_FAN) {
        return mIV_ITEM_KIND_BLUEBELL_FAN;
    }

    if (item == ITM_PLUM_FAN) {
        return mIV_ITEM_KIND_PLUM_FAN;
    }

    if (item == ITM_BAMBOO_FAN) {
        return mIV_ITEM_KIND_BAMBOO_FAN;
    }

    if (item == ITM_CLOUD_FAN) {
        return mIV_ITEM_KIND_CLOUD_FAN;
    }

    if (item == ITM_MAPLE_FAN) {
        return mIV_ITEM_KIND_MAPLE_FAN;
    }

    if (item == ITM_FAN_FAN) {
        return mIV_ITEM_KIND_FAN_FAN;
    }

    if (item == ITM_FLOWER_FAN) {
        return mIV_ITEM_KIND_FLOWER_FAN;
    }

    if (item == ITM_LEAF_FAN) {
        return mIV_ITEM_KIND_LEAF_FAN;
    }

    return mIV_ITEM_KIND_NUM; /* No animation */
}

static int mIV_ChangeIndex_mIV_to_mPlib(s16 idx) {
    static s8 data[] = {
        mPlayer_ITEM_KIND_AXE,
        mPlayer_ITEM_KIND_NET,
        mPlayer_ITEM_KIND_UMBRELLA00,
        mPlayer_ITEM_KIND_ROD,
        mPlayer_ITEM_KIND_SHOVEL,

        mPlayer_ITEM_KIND_GOLD_AXE,
        mPlayer_ITEM_KIND_GOLD_NET,
        mPlayer_ITEM_KIND_GOLD_ROD,
        mPlayer_ITEM_KIND_GOLD_SHOVEL,

        mPlayer_ITEM_KIND_RED_BALLOON,
        mPlayer_ITEM_KIND_YELLOW_BALLOON,
        mPlayer_ITEM_KIND_BLUE_BALLOON,
        mPlayer_ITEM_KIND_GREEN_BALLOON,
        mPlayer_ITEM_KIND_PURPLE_BALLOON,
        mPlayer_ITEM_KIND_BUNNY_P_BALLOON,
        mPlayer_ITEM_KIND_BUNNY_B_BALLOON,
        mPlayer_ITEM_KIND_BUNNY_O_BALLOON,

        mPlayer_ITEM_KIND_YELLOW_PINWHEEL,
        mPlayer_ITEM_KIND_RED_PINWHEEL,
        mPlayer_ITEM_KIND_TIGER_PINWHEEL,
        mPlayer_ITEM_KIND_GREEN_PINWHEEL,
        mPlayer_ITEM_KIND_PINK_PINWHEEL,
        mPlayer_ITEM_KIND_STRIPED_PINWHEEL,
        mPlayer_ITEM_KIND_FLOWER_PINWHEEL,
        mPlayer_ITEM_KIND_FANCY_PINWHEEL,

        mPlayer_ITEM_KIND_BLUEBELL_FAN,
        mPlayer_ITEM_KIND_PLUM_FAN,
        mPlayer_ITEM_KIND_BAMBOO_FAN,
        mPlayer_ITEM_KIND_CLOUD_FAN,
        mPlayer_ITEM_KIND_MAPLE_FAN,
        mPlayer_ITEM_KIND_FAN_FAN,
        mPlayer_ITEM_KIND_FLOWER_FAN,
        mPlayer_ITEM_KIND_LEAF_FAN,

        mPlayer_ITEM_KIND_AXE_USE_1,
        mPlayer_ITEM_KIND_AXE_USE_2,
        mPlayer_ITEM_KIND_AXE_USE_3,
        mPlayer_ITEM_KIND_AXE_USE_4,
        mPlayer_ITEM_KIND_AXE_USE_5,
        mPlayer_ITEM_KIND_AXE_USE_6,
        mPlayer_ITEM_KIND_AXE_USE_7,
    };

    if (idx >= 0 && idx < mIV_ITEM_KIND_NUM) {
        return data[idx];
    }

    return -1;
}

static int mIV_Get_player_item_shape_index(int idx) {
    if (idx >= 0 && idx < mIV_ITEM_KIND_NUM) {}
}
