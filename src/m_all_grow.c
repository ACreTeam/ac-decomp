#include "m_all_grow.h"

#include "libultra/libultra.h"
#include "m_field_info.h"
#include "m_field_make.h"
#include "m_name_table.h"
#include "libu64/gfxprint.h"
#include "m_time.h"
#include "m_collision_bg.h"
#include "zurumode.h"
#include "m_common_data.h"
#include "m_scene_table.h"

static mActor_name_t l_tree_max_table[mAGrw_FRUIT_NUM] = {
  TREE_APPLE_FRUIT,
  TREE_CHERRY_FRUIT,
  TREE_PEAR_FRUIT,
  TREE_PEACH_FRUIT,
  TREE_ORANGE_FRUIT
};

typedef struct {
  u8 block_x;
  u8 block_z;
} mAGrw_block_c;

static int l_fossil_num_debug;
static int l_haniwa_num_debug;

static mAGrw_block_c l_fossil_block[mAGrw_FOSSIL_NUM];
static mAGrw_block_c l_haniwa_block[mAGrw_HANIWA_NUM];


static void mAGrw_ClearDebugData() {
  l_fossil_num_debug = 0;
  l_haniwa_num_debug = 0;

  bzero(l_fossil_block, mAGrw_FOSSIL_NUM * sizeof(mAGrw_block_c));
  bzero(l_haniwa_block, mAGrw_HANIWA_NUM * sizeof(mAGrw_block_c));
}

static int mAGrw_CheckRegistedData_debug(mAGrw_block_c* block_info, int num, int block_x, int block_z) {
  int res = FALSE;
  int i;

  for (i = 0; i < num; i++) {
    if (block_info->block_x == block_x && block_info->block_z == block_z) {
      res = TRUE;
    }
    
    block_info++;
  }

  return res;
}

static void mAGrw_SetBlockData_debug(mAGrw_block_c* block_info, int num, int block_x, int block_z) {
  if (mAGrw_CheckRegistedData_debug(block_info, num, block_x, block_z) == FALSE) {
    int i;

    for (i = 0; i < num; i++) {
      if (block_info->block_x == 0 && block_info->block_z == 0) {
        block_info->block_x = block_x;
        block_info->block_z = block_z;
        break;
      }
    
      block_info++;
    }
  }
}

static void mAGrw_SetDebugDataBlock(mActor_name_t* fg_items, u16* deposit, mAGrw_block_c* fossil_block_info, int fossil_max, int* fossil_num, mAGrw_block_c* haniwa_block_info, int haniwa_max, int* haniwa_num, int block_x, int block_z) {
  int ut_z;
  for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
    int ut_x;
    for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
      if (mFI_GetLineDeposit(deposit, ut_x) == TRUE) {
        mActor_name_t item = *fg_items;
        if (item == ITM_FOSSIL) {
          mAGrw_SetBlockData_debug(fossil_block_info, fossil_max, block_x, block_z);
          (*fossil_num)++;
        }
        else if (IS_ITEM_HANIWA(item)) {
          mAGrw_SetBlockData_debug(haniwa_block_info, haniwa_max, block_x, block_z);
          (*haniwa_num)++;
        }
      }

      fg_items++;
    }

    deposit++;
  }
}

static void mAGrw_SetDebugData() {
  mFM_fg_c* fg_items = Save_Get(fg[0]);
  u16* deposit = Save_Get(deposit[0]);
  int block_z;

  mAGrw_ClearDebugData();

  for (block_z = 0; block_z < FG_BLOCK_Z_NUM; block_z++) {
    int block_x;
    for (block_x = 0; block_x < FG_BLOCK_X_NUM; block_x++) {
      mAGrw_SetDebugDataBlock(fg_items[0].items[0], deposit, l_fossil_block, mAGrw_FOSSIL_NUM, &l_fossil_num_debug, l_haniwa_block, mAGrw_HANIWA_NUM, &l_haniwa_num_debug, block_x + 1, block_z + 1);
      fg_items++;
      deposit += UT_Z_NUM;
    }
  }
}

extern void mAGrw_PrintFossilHaniwa_debug(gfxprint_t* gfxprint) {
  gfxprint_color(gfxprint, 240, 50, 50, 255);
  gfxprint_locate8x8(gfxprint, 3, 17);

  gfxprint_printf(
    gfxprint, "%4d %1d%1d %1d%1d %1d%1d %1d%1d ",
    l_fossil_num_debug,
    l_fossil_block[0].block_x, l_fossil_block[0].block_z,
    l_fossil_block[1].block_x, l_fossil_block[1].block_z,
    l_fossil_block[2].block_x, l_fossil_block[2].block_z,
    l_fossil_block[3].block_x, l_fossil_block[3].block_z
  );

  gfxprint_locate8x8(gfxprint, 20, 17);
  
  gfxprint_printf(
    gfxprint, "%1d%1d %4d %1d%1d %1d%1d %1d%1d",
    l_fossil_block[4].block_x, l_fossil_block[4].block_z,
    l_haniwa_num_debug,
    l_haniwa_block[0].block_x, l_haniwa_block[0].block_z,
    l_haniwa_block[1].block_x, l_haniwa_block[1].block_z,
    l_haniwa_block[2].block_x, l_haniwa_block[2].block_z
  );
}

extern int mAGrw_CheckKabuPeddler() {
  lbRTC_time_c peddler_spawn_time;
  lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
  lbRTC_time_c* renew_time = Save_GetPointer(all_grow_renew_time);
  int res = FALSE;
  
  if (rtc_time->weekday == lbRTC_SUNDAY) {

    lbRTC_TimeCopy(&peddler_spawn_time, rtc_time);
    peddler_spawn_time.hour = 6;
    peddler_spawn_time.min = 0;
    peddler_spawn_time.sec = 0;

    if (lbRTC_IsOverTime(&peddler_spawn_time, renew_time) == lbRTC_OVER ||
        mTM_AreTimesEqual(&mTM_rtcTime_clear_code, renew_time) == TRUE
    ) {
      res = TRUE;
    }
  }

  return res;
}

extern void mAGrw_OrderSetHaniwa() {
  Save_Set(haniwa_scheduled, TRUE);
}

extern void mAGrw_ChangeItemBlock(mActor_name_t* block_items, mActor_name_t new_item, mActor_name_t target_item, u8 possible_num) {
  int selected = RANDOM(possible_num);
  int i;

  for (i = 0; i < UT_TOTAL_NUM; i++) {
    if (*block_items == target_item) {
      if (selected <= 0) {
        *block_items = new_item;
        return;
      }

      selected--;
    }

    block_items++;
  }
}

static void mAGrw_ChangeItemBlock2(mActor_name_t* block_items, mActor_name_t new_item0, mActor_name_t new_item1, mActor_name_t target_item0, mActor_name_t target_item1, u8 possible_num) {
  int selected = RANDOM(possible_num);
  int i;

  for (i = 0; i < UT_TOTAL_NUM; i++) {
    if (*block_items == target_item0 || *block_items == target_item1) {
      if (selected <= 0) {
        if (*block_items == target_item0) {
          *block_items = new_item0;
        }
        else {
          *block_items = new_item1;
        }

        return;
      }

      selected--;
    }

    block_items++;
  }
}

static int mAGrw_CheckPutXmasTree(lbRTC_time_c* time) {
  int res = mAGrw_XMAS_PROC_CLEAR;

  if (time->month == lbRTC_DECEMBER && time->day >= 10 && time->day <= 25) {
    res = mAGrw_XMAS_PROC_SET;
  }

  return res;
}

static void mAGrw_SetXmasTreeBlock(mActor_name_t* block_items) {
  u8 exist_num = 0;
  u8 possible_num = 0;
  int i;

  for (i = 0; i < UT_TOTAL_NUM; i++) {
    if (*block_items == TREE || *block_items == CEDAR_TREE) {
      possible_num++;
    }
    else if (*block_items == TREE_LIGHTS || *block_items == CEDAR_TREE_LIGHTS) {
      exist_num++;
    }

    block_items++;
  }

  if (possible_num != 0) {
    int spawn_num = mAGrw_XMAS_LIGHTS_MAX_BLOCK - exist_num;

    if (spawn_num > 0) {
      if (possible_num < spawn_num) {
        spawn_num = possible_num;
      }

      for (i = 0; i < spawn_num; i++) {
        mAGrw_ChangeItemBlock2(block_items - UT_TOTAL_NUM, TREE_LIGHTS, CEDAR_TREE_LIGHTS, TREE, CEDAR_TREE, possible_num);
        possible_num--;
      }
    }
  }
}

static void mAGrw_ClearXmasTreeBlock(mActor_name_t* block_items) {
  int i;

  for (i = 0; i < UT_TOTAL_NUM; i++) {
    if (*block_items == TREE_LIGHTS) {
      *block_items = TREE;
    }
    else if (*block_items == CEDAR_TREE_LIGHTS) {
      *block_items = CEDAR_TREE;
    }

    block_items++;
  }
}

static void mAGrw_XmasTreeField(int type) {
  static void (*xmas_proc[mAGrw_XMAS_PROC_NUM])(mActor_name_t*) = { &mAGrw_ClearXmasTreeBlock, &mAGrw_SetXmasTreeBlock };

  mFM_fg_c* block = Save_Get(fg[0]);
  int i;

  for (i = 0; i < FG_BLOCK_TOTAL_NUM; i++) {
    (*xmas_proc[type])(block[0].items[0]);
    block++;
  }
}

extern void mAGrw_SetXmasTree() {
  if (Save_Get(scene_no) == SCENE_FG) {
    int type = mAGrw_CheckPutXmasTree(Common_GetPointer(time.rtc_time));
    mAGrw_XmasTreeField(type);
  }
}

extern void mAGrw_RenewalFgItem(lbRTC_time_c* time) {
  if (Save_Get(scene_no) == SCENE_FG) {
    int haniwa_scheduled = Save_Get(haniwa_scheduled);

    mAGrw_RenewalFgItem_ovl(time, &haniwa_scheduled);
    Save_Set(haniwa_scheduled, haniwa_scheduled);

    if (ZURUMODE2_ENABLED()) {
      mAGrw_SetDebugData();
    }
  }
}

static void mAGrw_ChangeTree2OtherBlock(mActor_name_t* block_items, mActor_name_t other, mActor_name_t tree, int change_num) {
  u8 count = mFI_GetItemNumInBlock(tree, block_items);

  while (change_num > 0 && count != 0) {
    mAGrw_ChangeItemBlock(block_items, other, tree, count);
    count--;
    change_num--;
  }
}

static void mAGrw_ChangeTree2FruitTreeBlock(mActor_name_t* block_items, mActor_name_t fruit_tree) {
  mAGrw_ChangeTree2OtherBlock(block_items, fruit_tree, TREE, 1);
}

static void mAGrw_ChangeTree2FruitTreeLine(mFM_fg_c* fg_blocks, mActor_name_t fruit_tree) {
  int block0 = RANDOM(FG_BLOCK_X_NUM);
  int block1 = RANDOM(FG_BLOCK_X_NUM - 1);

  if (block1 == block0) {
    block1++;
  }

  mAGrw_ChangeTree2FruitTreeBlock(fg_blocks[block0].items[0], fruit_tree);
  mAGrw_ChangeTree2FruitTreeBlock(fg_blocks[block1].items[0], fruit_tree);
}

extern void mAGrw_ChangeTree2FruitTree() {
  int fruit = Save_Get(fruit) - ITM_FOOD_START;
  mActor_name_t fruit_tree;
  int block_z;
  
  if (fruit < mAGrw_FRUIT_APPLE || fruit >= mAGrw_FRUIT_NUM) {
    fruit = mAGrw_FRUIT_APPLE;
  }

  fruit_tree = l_tree_max_table[fruit];
  for (block_z = 0; block_z < FG_BLOCK_Z_NUM; block_z++) {
    mAGrw_ChangeTree2FruitTreeLine(Save_Get(fg[block_z]), fruit_tree);
  }
}

extern void mAGrw_ChangeTree2Cedar() {
  static int cedar_max_table[(mAGrw_CEDAR_BLOCK_Z_MAX + 1) - mAGrw_CEDAR_BLOCK_Z_MIN] = {
    6, // A
    4, // B
    2, // C
    0  // D
  };
  
  mFM_fg_c* fg_block = Save_Get(fg[0]);
  int block_z;
  int block_x;

  for (block_z = mAGrw_CEDAR_BLOCK_Z_MIN; block_z < mAGrw_CEDAR_BLOCK_Z_MAX; block_z++) {
    for (block_x = 0; block_x < FG_BLOCK_X_NUM; block_x++) {
      mAGrw_ChangeTree2OtherBlock(fg_block[0].items[0], CEDAR_TREE, TREE, cedar_max_table[block_z]);
      fg_block++;
    }
  }
}

extern void mAGrw_ChangeCedar2Tree() {
  mFM_fg_c* fg_block = Save_Get(fg[1]);
  xyz_t wpos = { 0.0f, 0.0f, 0.0f };
  mActor_name_t* items;
  int block_z;
  int block_x;

  for (block_z = 0; block_z < mAGrw_CEDAR_BLOCK_Z_MAX - 1; block_z++) {
    for (block_x = 0; block_x < FG_BLOCK_X_NUM; block_x++) {
      xyz_t centered_wpos;
      
      mFI_BkNum2WposXZ(&wpos.x, &wpos.z, block_x + 1, block_z + 2);
      items = fg_block->items[0];

      wpos.x += mFI_UT_WORLDSIZE_X_F / 2.0f;
      wpos.z += mFI_UT_WORLDSIZE_Z_F / 2.0f;
      centered_wpos = wpos;

      if (fg_block != NULL) {
        int ut_x;
        int ut_z;
        
        /* Iterate through all units in the acre */
        for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
          centered_wpos.x = wpos.x;
          for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
            if (*items == CEDAR_TREE && mCoBG_GetLayer(&centered_wpos) == mCoBG_LAYER0) {
              *items = TREE;
            }

            centered_wpos.x += mFI_UT_WORLDSIZE_X_F;
            items++;
          }

          centered_wpos.z += mFI_UT_WORLDSIZE_Z_F;
        }
      }

      fg_block++;
    }
  }
}
