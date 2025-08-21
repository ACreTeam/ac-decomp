#include "m_police_box.h"

#include "game.h"
#include "m_actor_type.h"
#include "libc64/qrand.h"
#include "m_common_data.h"
#include "m_name_table.h"
#include "m_field_info.h"
#include "m_field_make.h"
#include "libultra/libultra.h"
#include "m_lib.h"
#include "m_shop.h"

/**
 * @brief Copies an array of items to the lost and found.
 *
 * item_buf must have a length of at least mPB_POLICE_BOX_ITEM_STORAGE_COUNT.
 *
 * @param item_buf The array of items to copy
 **/
extern void mPB_copy_itemBuf(mActor_name_t* item_buf) {
    mActor_name_t* keep_item;
    int count;
    int i;

    keep_item = Save_Get(police_box.keep_items);
    count = 0;

    /* copy over the items */
    for (i = 0; i < mPB_POLICE_BOX_ITEM_STORAGE_COUNT; i++) {
        if (*item_buf != EMPTY_NO) {
            *keep_item = *item_buf;
            count++;
            keep_item++;
        }

        item_buf++;
    }

    /* clear out any unset items if necessary */
    for (i = count; i < mPB_POLICE_BOX_ITEM_STORAGE_COUNT; i++) {
        *keep_item++ = EMPTY_NO;
    }
}

/**
 * @brief Gets the number of used slots in the lost and found.
 *
 * @return count of used slots
 **/
extern int mPB_get_keep_item_sum() {
    mActor_name_t* keep_item = Save_Get(police_box.keep_items);
    int sum = 0;
    int i;

    for (i = 0; i < mPB_POLICE_BOX_ITEM_STORAGE_COUNT; i++) {
        if (*keep_item != EMPTY_NO) {
            sum++;
        }
        keep_item++;
    }

    return sum;
}

/**
 * @brief Adds an item to the lost and found.
 *
 * The item must be of type 'ITEM1' or 'FTR0/FTR1'.
 * If the lost and found is full, the first item in it
 * will be deleted and all subsequent items will be shifted
 * over by one.
 *
 * @param item_no The item to add
 **/
extern void mPB_keep_item(mActor_name_t item_no) {
    if (ITEM_IS_ITEM1(item_no) || ITEM_IS_FTR(item_no)) {
        int keep_item_sum = mPB_get_keep_item_sum();
        if (keep_item_sum >= mPB_POLICE_BOX_ITEM_STORAGE_COUNT) {
            /* delete the first item and move the rest down one slot */
            mActor_name_t* keep_item = Save_Get(police_box.keep_items);
            int i;

            for (i = 1; i < mPB_POLICE_BOX_ITEM_STORAGE_COUNT; i++) {
                keep_item[0] = keep_item[1];
                keep_item++;
            }

            keep_item_sum = mPB_POLICE_BOX_ITEM_STORAGE_COUNT - 1;
        }

        Save_Set(police_box.keep_items[keep_item_sum], item_no);
    }
}

/**
 * @brief Transfers all items of type 'ITEM1' and 'FTR0/FTR1' to the lost and found.
 *
 * If the number of items to add exceeds the size of the lost and found,
 * the items kept will be randomly selected by using rng to overwrite
 * previously saved items from the acre.
 *
 * Additionally, items already in the lost in found will be deleted to
 * make space for the new items if necessary.
 *
 * @param blk_x The x acre (column)
 * @param blk_z The z acre (row)
 **/
extern void mPB_keep_all_item_in_block(int blk_x, int blk_z) {
    int count;
    mActor_name_t new_items[mPB_POLICE_BOX_ITEM_STORAGE_COUNT];
    int keep_item_sum;
    mActor_name_t item;
    mActor_name_t* block_items;
    int item_type;
    int i;

    keep_item_sum = mPB_get_keep_item_sum();
    block_items = mFI_BkNumtoUtFGTop(blk_x, blk_z);
    count = 0;

    bzero(new_items, mPB_POLICE_BOX_ITEM_STORAGE_COUNT * sizeof(mActor_name_t));

    for (i = 0; i < UT_TOTAL_NUM; i++) {
        item = *block_items;

        /* only accept items in the 0x1XXX, 2XXX, and 3XXX range */
        item_type = ITEM_NAME_GET_TYPE(item);
        if (item_type == NAME_TYPE_FTR0 || item_type == NAME_TYPE_ITEM1 || item_type == NAME_TYPE_FTR1) {
            if (count < mPB_POLICE_BOX_ITEM_STORAGE_COUNT) {
                /* space is still available, so directly add it */
                new_items[count] = item;
                count++;
            } else {
                /* randomly overwrite one of the items in the lost and found */
                new_items[RANDOM(mPB_POLICE_BOX_ITEM_STORAGE_COUNT)] = item;
            }

            *block_items = EMPTY_NO;
        }
        block_items++;
    }

    if (count > 0) {
        int total_sum = count + keep_item_sum;

        if (total_sum <= mPB_POLICE_BOX_ITEM_STORAGE_COUNT) {
            mem_copy((u8*)(Save_Get(police_box.keep_items) + keep_item_sum), (u8*)new_items,
                     count * sizeof(mActor_name_t));
        } else {
            mActor_name_t* dst = Save_Get(police_box.keep_items);
            int save_count = total_sum - mPB_POLICE_BOX_ITEM_STORAGE_COUNT;
            int keep_sum = keep_item_sum - save_count;

            /* move over saved items already in lost and found */
            for (i = 0; i < keep_sum; i++) {
                dst[i] = dst[i + save_count];
            }

            /* copy newly added items */
            mem_copy((u8*)(Save_Get(police_box.keep_items) + keep_sum), (u8*)new_items, count * sizeof(mActor_name_t));
        }
    }

    /* clear buried item flags in the cleared acre */
    mFI_ClearDeposit(blk_x, blk_z);
}

/* select random item function definition */
typedef mActor_name_t (*mPB_get_force_set_proc)();

/**
 * @brief Selects a random 'goods' item to add to the lost and found/
 *
 * @return The randomly selected item
 **/
static mActor_name_t mPB_get_force_set_item_goods() {
    static int category_table[mSP_KIND_MAX] = {
        mSP_KIND_FURNITURE, mSP_KIND_PAPER, mSP_KIND_CLOTH, mSP_KIND_CARPET, mSP_KIND_WALLPAPER,
    };

    static int prob_table[mSP_KIND_MAX] = {
        35, /* furniture   0-35 (36%) */
        58, /* stationery 36-58 (23%) */
        88, /* clothing   59-88 (30%) */
        94, /* carpets    89-94 (6%) */
        100 /* wallpaper  95-99 (5%) (fqrand is [min, max) so 100 is not possible) */
    };

    int category = mSP_KIND_MAX;
    mActor_name_t item = EMPTY_NO;
    int roll = (int)(fqrand() * 100.0f);
    int i;

    for (i = 0; i < mSP_KIND_MAX; i++) {
        if (roll <= prob_table[i]) {
            category = i;
            break;
        }
    }

    mSP_SelectRandomItem_New(NULL, &item, 1, NULL, 0, category_table[category], mSP_LISTTYPE_COMMON, FALSE);
    return item;
}

/**
 * @brief Selects a random tool or sapling to add to the lost and found.
 *
 * @return The randomly selected item
 **/
static mActor_name_t mPB_get_force_set_item_item() {
    static mActor_name_t category_table[6] = { ITM_NET, ITM_AXE, ITM_SHOVEL, ITM_ROD, ITM_SAPLING, ITM_CEDAR_SAPLING };

    return category_table[(int)(fqrand() * 6.0f)];
}

/**
 * @brief Selects a random flower bag to add to the lost and found.
 *
 * @return The randomly selected flower bag
 **/
static mActor_name_t mPB_get_force_set_item_flower() {
    return ITM_WHITE_PANSY_BAG + (int)(fqrand() * 8.0f);
}

/**
 * @brief Selects a random umbrella to add to the lost and found.
 *
 * @return The randomly selected umbrella
 **/
static mActor_name_t mPB_get_force_set_item_umbrella() {
    mActor_name_t umbrella;
    mSP_RandomUmbSelect(&umbrella, 1);

    return umbrella;
}

/**
 * @brief Selects a random item from a random category to add to the lost and found.
 *
 * @return The randomly selected item
 **/
static mActor_name_t mPB_get_force_set_item() {
    static mPB_get_force_set_proc force_proc[mPB_CATEGORY_NUM] = {
        &mPB_get_force_set_item_goods,
        &mPB_get_force_set_item_item,
        &mPB_get_force_set_item_flower,
        &mPB_get_force_set_item_umbrella,
    };

    static int prob_table[mPB_CATEGORY_NUM] = {
        85, /* 0-85  (86%) 'goods' */
        90, /* 86-90  (5%) 'item' */
        95, /* 91-95  (5%) 'flower' */
        100 /* 96-100 (4%) 'umbrella' (again, fqrand is [min, max) therefore 100 is never possible) */
    };

    int proc = mPB_CATEGORY_NUM;
    int roll = (int)(fqrand() * 100.0f);
    int i;

    for (i = 0; i < mPB_CATEGORY_NUM; i++) {
        if (roll <= prob_table[i]) {
            proc = i;
            break;
        }
    }

    return (*force_proc[proc])();
}

/**
 * @brief  Adds a random item to the lost and found if grow space is available.
 **/
extern void mPB_force_set_keep_item() {
    /* if lost and found item count is less-than-equal-to max grow size & 50-50 roll */
    if (mPB_get_keep_item_sum() <= mPB_MAX_GROW_SIZE && (int)qrand() >= 0) {
        mPB_keep_item(mPB_get_force_set_item());
    }
}

/**
 * @brief Initializes the police station lost and found.
 *
 * The lost and found will always start with one random common
 * priority list furniture and two random common priority list
 * shirts.
 *
 * @param game The GAME pointer to pass to mSP_SelectRandomItem_New, goes unused
 **/
extern void mPB_police_box_init(GAME* game) {
    mActor_name_t* keep_items = Save_Get(police_box.keep_items);
    int i;

    /* generate one random ABC prio furniture and two random ABC prio shirts */
    mSP_SelectRandomItem_New(game, keep_items + 0, 1, NULL, 0, mSP_KIND_FURNITURE, mSP_LISTTYPE_ABC, FALSE);
    mSP_SelectRandomItem_New(game, keep_items + 1, 2, NULL, 0, mSP_KIND_CLOTH, mSP_LISTTYPE_ABC, FALSE);

    /* clear the rest of the lost and found */
    keep_items += 3;
    for (i = 3; i < mPB_POLICE_BOX_ITEM_STORAGE_COUNT; i++) {
        *keep_items++ = EMPTY_NO;
    }
}
