#include "m_item_debug.h"

#include "libultra/libultra.h"
#include "game.h"
#include "m_room_type.h"
#include "padmgr.h"
#include "m_name_table.h"
#include "m_private.h"
#include "m_common_data.h"

typedef struct item_debug_s {
  int enabled;
  int category;
  int index;
} ItemDebug_c;

static char* mItemDebug_category_name_table[mItemDebug_CATEGORY_NUM] = {
  "\xC5\xBC", // untranslated JP
  "FTR",
  "PPR",
  "MNY",
  "TOL",
  "FSH",
  "CLT",
  "ELS",
  "CPT",
  "WLL",
  "FOD",
  "PLT",
  "MSC",
  "DST",
  "LOT",
  "IST",
  "HPY",
  "KAB"
};

static mActor_name_t mItemDebug_category_start_no_table[mItemDebug_CATEGORY_NUM] = {
  EMPTY_NO,
  FTR0_NO_START,
  ITM_PAPER_START,
  ITM_MONEY_START,
  ITM_TOOL_START,
  ITM_FISH_START,
  ITM_CLOTH_START,
  ITM_ETC_START,
  ITM_CARPET_START,
  ITM_WALL_START,
  ITM_FOOD_START,
  ITM_ENV_START,
  ITM_MINIDISK_START,
  ITM_DIARY_START,
  ITM_TICKET_START,
  ITM_INSECT_START,
  ITM_HUKUBUKURO_START,
  ITM_KABU_START
};

static int mItemDebug_category_max_table[mItemDebug_CATEGORY_NUM] = {
  0,
  FTR_NUM,
  PAPER_NUM,
  MONEY_NUM,
  TOOL_NUM,
  FISH_NUM,
  CLOTH_NUM,
  ETC_NUM,
  CARPET_NUM,
  WALL_NUM,
  FRUIT_NUM,
  PLANT_NUM,
  MINIDISK_NUM,
  DIARY_NUM,
  TICKET_NUM,
  INSECT_NUM,
  HUKUBUKURO_NUM,
  KABU_NUM
};

/* @unused ? mItemDebug_ItemDebugCt(...) */

static int mItemDebug_FurnitureCanUse(int ftr_idx) {
  if (ftr_idx >= 0 && ftr_idx < FTR_NUM) {
    u8* birth_info_p = mRmTp_CheckFtrBirthInfoTop();

    if (birth_info_p[ftr_idx] == mRmTp_BIRTH_TYPE_UNOBTAINABLE || birth_info_p[ftr_idx] == mRmTp_BIRTH_TYPE_MY_ORIGINAL) {
      return FALSE;
    }

    return TRUE;
  }

  return FALSE;
}

static ItemDebug_c l_mItemDebug_work_data;

extern void mItemDebug_ItemDebugMain() {
  if ((gamePT->pads[PAD2].on.button & BUTTON_START) == BUTTON_START) {
    l_mItemDebug_work_data.enabled = (l_mItemDebug_work_data.enabled + 1) & 1;

    if (l_mItemDebug_work_data.enabled != FALSE) {
      bzero(&l_mItemDebug_work_data, sizeof(ItemDebug_c));
      l_mItemDebug_work_data.enabled = TRUE;
    }
    else {
      bzero(&l_mItemDebug_work_data, sizeof(ItemDebug_c));
    }
  }

  if (l_mItemDebug_work_data.enabled != FALSE) {
    int category;

    if ((gamePT->pads[PAD2].on.button & BUTTON_DUP) == BUTTON_DUP) {
      l_mItemDebug_work_data.index = 0;
      l_mItemDebug_work_data.category++;

      if (l_mItemDebug_work_data.category > mItemDebug_CATEGORY_KAB) {
        l_mItemDebug_work_data.category = 0;
      }
    }

    category = l_mItemDebug_work_data.category;
    if (category != mItemDebug_CATEGORY_NONE) {
      if ((gamePT->pads[PAD2].on.button & BUTTON_DRIGHT) == BUTTON_DRIGHT) {
        /* Holding B increments by 10, holding A increments by 100 */
        if ((gamePT->pads[PAD2].now.button & BUTTON_B) == BUTTON_B) {
          l_mItemDebug_work_data.index += 10;
        }
        else if ((gamePT->pads[PAD2].now.button & BUTTON_A) == BUTTON_A) {
          l_mItemDebug_work_data.index += 100;
        }
        else {
          l_mItemDebug_work_data.index++;
        }

        if (l_mItemDebug_work_data.index > mItemDebug_category_max_table[category] - 1) {
          l_mItemDebug_work_data.index = 0;
        }
      }
      else if ((gamePT->pads[PAD2].on.button & BUTTON_DLEFT) == BUTTON_DLEFT) {
        /* Holding B increments by 10, holding A increments by 100 */
        if ((gamePT->pads[PAD2].now.button & BUTTON_B) == BUTTON_B) {
          l_mItemDebug_work_data.index -= 10;
        }
        else if ((gamePT->pads[PAD2].now.button & BUTTON_A) == BUTTON_A) {
          l_mItemDebug_work_data.index -= 100;
        }
        else {
          l_mItemDebug_work_data.index--;
        }

        if (l_mItemDebug_work_data.index < 0) {
          l_mItemDebug_work_data.index = 0;
        }
      }
    }

    if ((gamePT->pads[PAD2].on.button & BUTTON_DDOWN) == BUTTON_DDOWN && category != mItemDebug_CATEGORY_NONE) {
      int slot_idx = mPr_GetPossessionItemIdxWithCond(Common_Get(now_private), EMPTY_NO, mPr_ITEM_COND_NORMAL);
      mActor_name_t item;

      if (category != mItemDebug_CATEGORY_FTR) {
        item = mItemDebug_category_start_no_table[category] + l_mItemDebug_work_data.index;
      }
      else {
        if (mItemDebug_FurnitureCanUse(l_mItemDebug_work_data.index)) {
          item = mRmTp_FtrIdx2FtrItemNo(l_mItemDebug_work_data.index, mRmTp_DIRECT_SOUTH);
        }
        else {
          return;
        }
      }

      if (slot_idx != -1) {
        mPr_SetPossessionItem(Common_Get(now_private), slot_idx, item, mPr_ITEM_COND_NORMAL);
      }
    }
  }
}

extern void mItemDebug_ItemDebugDraw(gfxprint_t* gfxprint) {
  int category = l_mItemDebug_work_data.category;

  if (l_mItemDebug_work_data.enabled != FALSE) {
    gfxprint_color(gfxprint, 225, 225, 255, 255);
    gfxprint_locate8x8(gfxprint, 3, 20);
    
    if (category != mItemDebug_CATEGORY_NONE) {
      if (category == mItemDebug_CATEGORY_FTR) {
        if (mItemDebug_FurnitureCanUse(l_mItemDebug_work_data.index)) {
          gfxprint_printf(gfxprint, "%s:%d", mItemDebug_category_name_table[category], l_mItemDebug_work_data.index);
        }
        else {
          gfxprint_printf(gfxprint, "%s:---(%d)", mItemDebug_category_name_table[category], l_mItemDebug_work_data.index);
        }
      }
      else {
        gfxprint_printf(gfxprint, "%s:%d", mItemDebug_category_name_table[category], l_mItemDebug_work_data.index);
      }
    }
    else {
      gfxprint_printf(gfxprint, "\xC5\xBC");
    }
  }
}
