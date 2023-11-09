#include "m_name_table.h"

#include "m_actor.h"
#include "m_npc_personal_id.h"

s16 move_obj_profile_table[] = {
  mAc_PROFILE_AIRPLANE,
  mAc_PROFILE_BALL,
  mAc_PROFILE_MY_ROOM,
  mAc_PROFILE_MBG,
  mAc_PROFILE_BOXMANAGER,
  mAc_PROFILE_BOXTRICK01,
  mAc_PROFILE_ARRANGE_ROOM,
  mAc_PROFILE_ARRANGE_FURNITURE,
  mAc_PROFILE_EFFECT_CONTROL,
  mAc_PROFILE_SHOP_DESIGN,
  mAc_PROFILE_SHOP_MANEKIN,
  mAc_PROFILE_SHOP_INDOOR,
  mAc_PROFILE_SHOP_GOODS,
  mAc_PROFILE_SNOWMAN,
  mAc_PROFILE_SNOWMAN,
  mAc_PROFILE_BROKER_DESIGN,
  mAc_PROFILE_MY_INDOOR,
  mAc_PROFILE_TRAIN_WINDOW,
  mAc_PROFILE_UKI,
  mAc_PROFILE_SHOP_UMBRELLA,
  mAc_PROFILE_KAMAKURA_INDOOR,
  mAc_PROFILE_HOUSE_CLOCK
};

s16 actor_profile_table[] = {
  mAc_PROFILE_SAMPLE
};

s16 props_profile_table[] = {
  mAc_PROFILE_MAILBOX,
  mAc_PROFILE_MAILBOX,
  mAc_PROFILE_MAILBOX,
  mAc_PROFILE_MAILBOX,
  mAc_PROFILE_HANIWA,
  mAc_PROFILE_HANIWA,
  mAc_PROFILE_HANIWA,
  mAc_PROFILE_HANIWA,
  mAc_PROFILE_PSNOWMAN,
  mAc_PROFILE_PSNOWMAN,
  mAc_PROFILE_PSNOWMAN,
  mAc_PROFILE_PSNOWMAN,
  mAc_PROFILE_PSNOWMAN,
  mAc_PROFILE_PSNOWMAN,
  mAc_PROFILE_PSNOWMAN,
  mAc_PROFILE_PSNOWMAN,
  mAc_PROFILE_PSNOWMAN,
  mAc_PROFILE_TRAINDOOR,
  mAc_PROFILE_NAMEPLATE
};

u8 npc_looks_table[NPC_NUM] = {
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_GRIM_MAN,
  mNpc_LOOKS_GIRL,
  mNpc_LOOKS_KO_GIRL,
  mNpc_LOOKS_SPORT_MAN,
  mNpc_LOOKS_NANIWA_LADY,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_BOY,
  mNpc_LOOKS_KO_GIRL
};

static u8 item1_0_tableNo[] = {
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44,
  44, 44, 44, 44
};

static u8 item1_1_tableNo[] = {
  9, 9, 9, 9
};

static u8 item1_2_tableNo[] = {
  34, 33, 36, 35,
  41, 41, 41, 41,
  41, 41, 41, 41,
  41, 41, 41, 41,
  41, 41, 41, 41,
  41, 41, 41, 41,
  41, 41, 41, 41,
  41, 41, 41, 41,
  41, 41, 41, 41,
  41, 41, 41, 41,
  41, 41, 41, 41,
  19, 19, 19, 19,
  19, 19, 19, 19,
  19, 19, 19, 19,
  19, 38, 37, 40,
  39, 33, 33, 33,
  33, 33, 33, 33,
  19, 19, 19, 19,
  19, 19, 19, 19,
  42, 42, 42, 42,
  42, 42, 42, 42,
  43, 43, 43, 43,
  43, 43, 43, 43
};

static u8 item1_3_tableNo[] = {
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8,
  8, 8, 8, 8
};

static u8 item1_4_tableNo[] = {
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30, 30,
  30, 30, 30
};

static u8 item1_5_tableNo[] = {
  22, 13, 13, 13,
  13, 13, 13, 13,
  13, 13, 13, 13,
  13,  9, 21, 21,
  21, 20, 23, 29,
  25, 24, 24, 24,
  25, 25, 24, 26,
  14, 11, 19, 14,
  14, 14, 14, 47,
  47, 47, 47, 47,
  47, 47, 47, 47,
  47, 47, 47, 47,
  52
};

static u8 item1_6_tableNo[] = {
  31, 31, 31, 31,
  31, 31, 31, 31,
  31, 31, 31, 31,
  31, 31, 31, 31,
  31, 31, 31, 31,
  31, 31, 31, 31,
  31, 31, 31, 31,
  31, 31, 31, 31,
  31, 31, 31, 31,
  31, 31, 31, 31,
  31, 31, 31, 31,
  31, 31, 31, 31,
  31, 31, 31, 31,
  31, 31, 31, 31,
  31, 31, 31, 31,
  31, 31, 31, 31,
  31, 31, 31
};

static u8 item1_7_tableNo[] = {
  32, 32, 32, 32,
  32, 32, 32, 32,
  32, 32, 32, 32,
  32, 32, 32, 32,
  32, 32, 32, 32,
  32, 32, 32, 32,
  32, 32, 32, 32,
  32, 32, 32, 32,
  32, 32, 32, 32,
  32, 32, 32, 32,
  32, 32, 32, 32,
  32, 32, 32, 32,
  32, 32, 32, 32,
  32, 32, 32, 32,
  32, 32, 32, 32,
  32, 32, 32, 32,
  32, 32, 32
};

static u8 item1_8_tableNo[] = {
  1, 5, 4, 3,
  2, 6, 27, 28
};

static u8 item1_9_tableNo[] = {
  17, 17, 45, 45,
  45, 45, 45, 45,
  45, 45, 45
};

static u8 item1_A_tableNo[] = {
  48, 48, 48, 48,
  48, 48, 48, 48,
  48, 48, 48, 48,
  48, 48, 48, 48,
  48, 48, 48, 48,
  48, 48, 48, 48,
  48, 48, 48, 48,
  48, 48, 48, 48,
  48, 48, 48, 48,
  48, 48, 48, 48,
  48, 48, 48, 48,
  48, 48, 48, 48,
  48, 48, 48, 48,
  48, 48, 48
};

// ?? Shouldn't these be different from saplings?
static u8 item1_B_tableNo[] = {
  17, 17, 17, 17,
  17, 17, 17, 17,
  17, 17, 17, 17,
  17, 17, 17, 17
};

static u8 item1_C_tableNo[] = {
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49,
  49, 49, 49, 49
};

static u8 item1_D_tableNo[] = {
  18, 18, 18, 18,
  18, 18, 18, 18,
  18, 18, 18, 18,
  18, 18, 18, 18,
  18, 18, 18, 18,
  18, 18, 18, 18,
  18, 18, 18, 18,
  18, 18, 18, 18,
  18, 18, 18, 18,
  18, 18, 18, 18,
  18, 18, 18, 18,
  18
};

static u8 item1_E_tableNo[] = {
  46, 46
};

static u8 item1_F_tableNo[] = {
  7, 7, 7, 7
};

extern int mNT_get_itemTableNo(mActor_name_t item) {
  static u8* item1_tableNo[ITEM1_CAT_NUM] = {

  };

  switch (ITEM_NAME_GET_TYPE(item)) {
    case NAME_TYPE_FTR0:
    case NAME_TYPE_FTR1:
    {
      if (item >= FTR_DINO_START && item <= FTR_DINO_END) {
        return mNT_ITEM_TYPE_BONE;
      }
      else if (item >= HANIWA_START && item <= HANIWA_END) {
        return mNT_ITEM_TYPE_HANIWA;
      }
      else if (item >= ITM_DIARY_START && item <= ITM_DIARY15) {
        return mNT_ITEM_TYPE_DIARY;
      }

      return mNT_ITEM_TYPE_LEAF;
    }

    case NAME_TYPE_ITEM1:
    {
      return item1_tableNo[ITEM_NAME_GET_CAT(item)][ITEM_NAME_GET_INDEX(item)];
    }
  }

  return mNT_ITEM_TYPE_NONE;
}

extern mActor_name_t mNT_FishIdx2FishItemNo(int idx) {
  if (idx >= 0 && idx < (FISH_NUM + 2)) {
    return ITM_FISH_START + idx;
  }

  return EMPTY_NO;
}

extern mActor_name_t bg_item_fg_sub(mActor_name_t item, s16 flag) {
  // TODO: tree type enum
  static mActor_name_t cnvfg[mNT_TREE_SIZE_NUM][mNT_TREE_TYPE_NUM] = {
    { TREE_STUMP004, TREE_PALM_STUMP004, CEDAR_TREE_STUMP004, GOLD_TREE_STUMP004 },
    { TREE_STUMP003, TREE_PALM_STUMP003, CEDAR_TREE_STUMP003, GOLD_TREE_STUMP003 },
    { TREE_STUMP002, TREE_PALM_STUMP002, CEDAR_TREE_STUMP002, GOLD_TREE_STUMP002 },
    { TREE_STUMP001, TREE_PALM_STUMP001, CEDAR_TREE_STUMP001, GOLD_TREE_STUMP001 }
  };

  int tree_type = FGTreeType_check(item);
  mActor_name_t conv = item;

  if (flag == 0) {
    if (
      item == TREE ||
      item == TREE_1000BELLS ||
      item == TREE_10000BELLS ||
      item == TREE_30000BELLS ||
      item == TREE_100BELLS ||
      item == CEDAR_TREE ||
      item == GOLD_TREE_SHOVEL ||
      item == GOLD_TREE ||
      item == TREE_APPLE_NOFRUIT_0 ||
      item == TREE_APPLE_NOFRUIT_1 ||
      item == TREE_APPLE_NOFRUIT_2 ||
      item == TREE_APPLE_FRUIT ||
      item == TREE_ORANGE_NOFRUIT_0 ||
      item == TREE_ORANGE_NOFRUIT_1 ||
      item == TREE_ORANGE_NOFRUIT_2 ||
      item == TREE_ORANGE_FRUIT ||
      item == TREE_PEACH_NOFRUIT_0 ||
      item == TREE_PEACH_NOFRUIT_1 ||
      item == TREE_PEACH_NOFRUIT_2 ||
      item == TREE_PEACH_FRUIT ||
      item == TREE_PEAR_NOFRUIT_0 ||
      item == TREE_PEAR_NOFRUIT_1 ||
      item == TREE_PEAR_NOFRUIT_2 ||
      item == TREE_PEAR_FRUIT ||
      item == TREE_CHERRY_NOFRUIT_0 ||
      item == TREE_CHERRY_NOFRUIT_1 ||
      item == TREE_CHERRY_NOFRUIT_2 ||
      item == TREE_CHERRY_FRUIT ||
      item == TREE_PALM_NOFRUIT_0 ||
      item == TREE_PALM_NOFRUIT_1 ||
      item == TREE_PALM_NOFRUIT_2 ||
      item == TREE_PALM_FRUIT ||
      item == TREE_BEES ||
      item == TREE_FTR ||
      item == TREE_LIGHTS ||
      item == TREE_PRESENT ||
      item == TREE_BELLS ||
      item == CEDAR_TREE_BELLS ||
      item == CEDAR_TREE_FTR ||
      item == CEDAR_TREE_BEES ||
      item == CEDAR_TREE_LIGHTS ||
      item == GOLD_TREE_BELLS ||
      item == GOLD_TREE_FTR ||
      item == GOLD_TREE_BEES
    ) {
      conv = cnvfg[mNT_TREE_SIZE_FULL][tree_type];
    }
    else if (
      item == TREE_S2 ||
      item == TREE_APPLE_S2 ||
      item == TREE_ORANGE_S2 ||
      item == TREE_PEACH_S2 ||
      item == TREE_PEAR_S2 ||
      item == TREE_CHERRY_S2 ||
      item == TREE_1000BELLS_S2 ||
      item == TREE_10000BELLS_S2 ||
      item == TREE_30000BELLS_S2 ||
      item == TREE_100BELLS_S2 ||
      item == TREE_PALM_S2 ||
      item == CEDAR_TREE_S2 ||
      item == GOLD_TREE_S2
    ) {
      conv = cnvfg[mNT_TREE_SIZE_S2][tree_type]; 
    }
    else if (
      item == TREE_S1 ||
      item == TREE_APPLE_S1 ||
      item == TREE_ORANGE_S1 ||
      item == TREE_PEACH_S1 ||
      item == TREE_PEAR_S1 ||
      item == TREE_CHERRY_S1 ||
      item == TREE_1000BELLS_S1 ||
      item == TREE_10000BELLS_S1 ||
      item == TREE_30000BELLS_S1 ||
      item == TREE_100BELLS_S1 ||
      item == TREE_PALM_S1 ||
      item == CEDAR_TREE_S1 ||
      item == GOLD_TREE_S1
    ) {
      conv = cnvfg[mNT_TREE_SIZE_S1][tree_type]; 
    }
    else if (
      item == TREE_S0 ||
      item == TREE_APPLE_S0 ||
      item == TREE_ORANGE_S0 ||
      item == TREE_PEACH_S0 ||
      item == TREE_PEAR_S0 ||
      item == TREE_CHERRY_S0 ||
      item == TREE_1000BELLS_S0 ||
      item == TREE_10000BELLS_S0 ||
      item == TREE_30000BELLS_S0 ||
      item == TREE_100BELLS_S0 ||
      item == TREE_PALM_S0 ||
      item == CEDAR_TREE_S0 ||
      item == GOLD_TREE_S0
    ) {
      conv = cnvfg[mNT_TREE_SIZE_S0][tree_type]; 
    }
  }

  return conv;
}

extern mNT_offset_table_c* obj_hight_table_item0_nogrow(mActor_name_t item) {
  static mNT_offset_table_c height_table[3] = {

  };

  mNT_offset_table_c* table = &height_table[0];

  if (
    item == FENCE0 ||
    item == FENCE1 ||
    item == MESSAGE_BOARD0 ||
    item == MESSAGE_BOARD1 ||
    item == WOOD_FENCE
  ) {
    table = &height_table[1];
  }
  else if (
    item == MAP_BOARD0 ||
    item == MAP_BOARD1 ||
    item == MUSIC_BOARD0 ||
    item == MUSIC_BOARD1
  ) {
    table = &height_table[2];
  }

  return height_table;
}

extern mActor_name_t bg_item_fg_sub_tree_grow(mActor_name_t item, int past_days, int check_plant) {
  
}
