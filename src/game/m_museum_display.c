#include "m_museum_display.h"

#include "m_name_table.h"
#include "m_room_type.h"
#include "m_scene_table.h"
#include "m_common_data.h"

extern int mMmd_FossilInfo(int fossil_no) {
  int valid = FALSE;

  if (fossil_no >= 0 && fossil_no < mMmd_FOSSIL_NUM) {
    valid = TRUE;
  }

  if (valid) {
    return mMmd_FOSSIL_BIT(Save_Get(museum_display), fossil_no);
  }

  return 0;
}

extern int mMmd_ArtInfo(int art_no) {
  int valid = FALSE;

  if (art_no >= 0 && art_no < mMmd_ART_NUM) {
    valid = TRUE;
  }

  if (valid) {
    return mMmd_ART_BIT(Save_Get(museum_display), art_no);
  }

  return 0;
}

extern int mMmd_InsectInfo(int insect_no) {
  int valid = FALSE;

  if (insect_no >= 0 && insect_no < mMmd_INSECT_NUM) {
    valid = TRUE;
  }

  if (valid) {
    return mMmd_INSECT_BIT(Save_Get(museum_display), insect_no);
  }

  return 0;
}

extern int mMmd_FishInfo(int fish_no) {
  int valid = FALSE;

  if (fish_no >= 0 && fish_no < mMmd_FISH_NUM) {
    valid = TRUE;
  }

  if (valid) {
    return mMmd_FISH_BIT(Save_Get(museum_display), fish_no);
  }

  return 0;
}

extern void mMmd_SetFossil(int fossil_no) {
  if (fossil_no >= 0 && fossil_no < mMmd_FOSSIL_NUM && mLd_PlayerManKindCheck() == FALSE) {
    mMmd_FOSSIL_CLR(Save_Get(museum_display), fossil_no);
    mMmd_FOSSIL_SET(Save_Get(museum_display), fossil_no, Common_Get(player_no) + 1);
  }
}

extern void mMmd_SetArt(int art_no) {
  if (art_no >= 0 && art_no < mMmd_ART_NUM && mLd_PlayerManKindCheck() == FALSE) {
    mMmd_ART_CLR(Save_Get(museum_display), art_no);
    mMmd_ART_SET(Save_Get(museum_display), art_no, Common_Get(player_no) + 1);
  }
}

extern void mMmd_SetInsect(int insect_no) {
  if (insect_no >= 0 && insect_no < mMmd_INSECT_NUM && mLd_PlayerManKindCheck() == FALSE) {
    mMmd_INSECT_CLR(Save_Get(museum_display), insect_no);
    mMmd_INSECT_SET(Save_Get(museum_display), insect_no, Common_Get(player_no) + 1);
  }
}

extern void mMmd_SetFish(int fish_no) {
  if (fish_no >= 0 && fish_no < mMmd_FISH_NUM && mLd_PlayerManKindCheck() == FALSE) {
    mMmd_FISH_CLR(Save_Get(museum_display), fish_no);
    mMmd_FISH_SET(Save_Get(museum_display), fish_no, Common_Get(player_no) + 1);
  }
}

extern int mMmd_GetDisplayInfo(mActor_name_t item) {
  if (item >= FTR_START(FTR_DIN_TRIKERA_HEAD) && item <= FTR_END(FTR_DIN_TRILOBITE)) {
    int fossil_idx;
    int valid = FALSE;

    /* ??? why check this again */
    if (item >= FTR_START(FTR_DIN_TRIKERA_HEAD) && item <= FTR_END(FTR_DIN_TRILOBITE)) {
      valid = TRUE;
    }

    fossil_idx = valid != FALSE ? FTR_IDX_2_NO(item - FTR_START(FTR_DIN_TRIKERA_HEAD)) : 0;
    if (mMmd_FossilInfo(fossil_idx) >= mMmd_DONATOR_PLAYER1 && mMmd_FossilInfo(fossil_idx) <= mMmd_DONATOR_DELETED_PLAYER) {
      return mMmd_DISPLAY_ALREADY_DONATED;
    }
    else {
      return mMmd_DISPLAY_CAN_DONATE;
    }
  }
  else if (item >= FTR_START(FTR_SUM_ART01) && item <= FTR_END(FTR_SUM_ART15)) {
    int painting_idx;
    int valid = FALSE;

    /* ??? why check this again */
    if (item >= FTR_START(FTR_SUM_ART01) && item <= FTR_END(FTR_SUM_ART15)) {
      valid = TRUE;
    }

    painting_idx = valid != FALSE ? FTR_IDX_2_NO(item - FTR_START(FTR_SUM_ART01)) : 0;
    if (mMmd_ArtInfo(painting_idx) >= mMmd_DONATOR_PLAYER1 && mMmd_ArtInfo(painting_idx) <= mMmd_DONATOR_DELETED_PLAYER) {
      return mMmd_DISPLAY_ALREADY_DONATED;
    }
    else {
      return mMmd_DISPLAY_CAN_DONATE;
    }
  }
  else if (item >= ITM_INSECT00 && item < ITM_SPIRIT0) {
    int insect_idx;
    int valid = FALSE;

    /* ??? why check this again */
    if (item >= ITM_INSECT00 && item < ITM_SPIRIT0) {
      valid = TRUE;
    }

    insect_idx = valid != FALSE ? item - ITM_INSECT_START : 0;
    if (mMmd_InsectInfo(insect_idx) >= mMmd_DONATOR_PLAYER1 && mMmd_InsectInfo(insect_idx) <= mMmd_DONATOR_DELETED_PLAYER) {
      return mMmd_DISPLAY_ALREADY_DONATED;
    }
    else {
      return mMmd_DISPLAY_CAN_DONATE;
    }
  }
  else if (item >= ITM_FISH00 && item <= ITM_FISH_END) {
    int fish_idx;
    int valid = FALSE;

    /* ??? why check this again */
    if (item >= ITM_FISH00 && item <= ITM_FISH_END) {
      valid = TRUE;
    }

    fish_idx = valid != FALSE ? item - ITM_FISH_START : 0;
    if (mMmd_FishInfo(fish_idx) >= mMmd_DONATOR_PLAYER1 && mMmd_FishInfo(fish_idx) <= mMmd_DONATOR_DELETED_PLAYER) {
      return mMmd_DISPLAY_ALREADY_DONATED;
    }
    else {
      return mMmd_DISPLAY_CAN_DONATE;
    }
  }

  return mMmd_DISPLAY_CANNOT_DONATE;
}

extern int mMmd_RequestMuseumDisplay(mActor_name_t item) {
  if (mLd_PlayerManKindCheck() == FALSE) {
    if (item >= FTR_START(FTR_DIN_TRIKERA_HEAD) && item <= FTR_END(FTR_DIN_TRILOBITE)) {
      int fossil_idx;
      int valid = FALSE;

      /* ??? why check this again */
      if (item >= FTR_START(FTR_DIN_TRIKERA_HEAD) && item <= FTR_END(FTR_DIN_TRILOBITE)) {
        valid = TRUE;
      }

      fossil_idx = valid != FALSE ? FTR_IDX_2_NO(item - FTR_START(FTR_DIN_TRIKERA_HEAD)) : 0;
      if (mMmd_FossilInfo(fossil_idx) < mMmd_DONATOR_PLAYER1 || mMmd_FossilInfo(fossil_idx) > mMmd_DONATOR_DELETED_PLAYER) {
        mMmd_SetFossil(fossil_idx);
        return TRUE;
      }
    }
    else if (item >= FTR_START(FTR_SUM_ART01) && item <= FTR_END(FTR_SUM_ART15)) {
      int painting_idx;
      int valid = FALSE;

      /* ??? why check this again */
      if (item >= FTR_START(FTR_SUM_ART01) && item <= FTR_END(FTR_SUM_ART15)) {
        valid = TRUE;
      }

      painting_idx = valid != FALSE ? FTR_IDX_2_NO(item - FTR_START(FTR_SUM_ART01)) : 0;
      if (mMmd_ArtInfo(painting_idx) < mMmd_DONATOR_PLAYER1 || mMmd_ArtInfo(painting_idx) > mMmd_DONATOR_DELETED_PLAYER) {
        mMmd_SetArt(painting_idx);
        return TRUE;
      }
    }
    else if (item >= ITM_INSECT00 && item < ITM_SPIRIT0) {
      int insect_idx;
      int valid = FALSE;

      /* ??? why check this again */
      if (item >= ITM_INSECT00 && item < ITM_SPIRIT0) {
        valid = TRUE;
      }

      insect_idx = valid != FALSE ? item - ITM_INSECT_START : 0;
      if (mMmd_InsectInfo(insect_idx) < mMmd_DONATOR_PLAYER1 || mMmd_InsectInfo(insect_idx) > mMmd_DONATOR_DELETED_PLAYER) {
        mMmd_SetInsect(insect_idx);
        return TRUE;
      }
    }
    else if (item >= ITM_FISH00 && item <= ITM_FISH_END) {
      int fish_idx;
      int valid = FALSE;

      /* ??? why check this again */
      if (item >= ITM_FISH00 && item <= ITM_FISH_END) {
        valid = TRUE;
      }

      fish_idx = valid != FALSE ? item - ITM_FISH_START : 0;
      if (mMmd_FishInfo(fish_idx) < mMmd_DONATOR_PLAYER1 || mMmd_FishInfo(fish_idx) > mMmd_DONATOR_DELETED_PLAYER) {
        mMmd_SetFish(fish_idx);
        return TRUE;
      }
    }
  }

  return FALSE;
}

typedef struct museum_display_fossil_data_s {
  u8 ut;
  mActor_name_t item;
  int rotation;
} mMmd_fossil_data_c;

#define mMmd_UT(x, z) ((((z) & 0xF) << 4) | ((x) & 0xF))

static mMmd_fossil_data_c mMmd_museum_fossil_data[mMmd_FOSSIL_NUM] = {
  { mMmd_UT(5, 2), FTR_START(FTR_DIN_TRIKERA_DUMMY), mRmTp_DIRECT_NORTH }, /* tricera skull */
  { mMmd_UT(1, 2), FTR_START(FTR_DIN_TRIKERA_DUMMY), mRmTp_DIRECT_NORTH }, /* tricera tail */
  { mMmd_UT(3, 2), FTR_START(FTR_DIN_TRIKERA_DUMMY), mRmTp_DIRECT_NORTH }, /* tricera torso */
  
  { mMmd_UT(9, 2), FTR_START(FTR_DIN_TREX_DUMMY), mRmTp_DIRECT_SOUTH }, /* T-rex skull */
  { mMmd_UT(13, 2), FTR_START(FTR_DIN_TREX_DUMMY), mRmTp_DIRECT_SOUTH }, /* T-rex tail */
  { mMmd_UT(11, 2), FTR_START(FTR_DIN_TREX_DUMMY), mRmTp_DIRECT_SOUTH }, /* T-rex torso */
  
  { mMmd_UT(5, 10), FTR_START(FTR_DIN_BRONT_DUMMY), mRmTp_DIRECT_NORTH }, /* apato skull */
  { mMmd_UT(1, 10), FTR_START(FTR_DIN_BRONT_DUMMY), mRmTp_DIRECT_NORTH }, /* apato tail */
  { mMmd_UT(3, 10), FTR_START(FTR_DIN_BRONT_DUMMY), mRmTp_DIRECT_NORTH }, /* apato torso  */
  
  { mMmd_UT(10, 6), FTR_START(FTR_DIN_STEGO_DUMMYA), mRmTp_DIRECT_EAST }, /* stego skull */
  { mMmd_UT(13, 5), FTR_START(FTR_DIN_STEGO_DUMMYB), mRmTp_DIRECT_SOUTH }, /* stego tail */
  { mMmd_UT(11, 5), FTR_START(FTR_DIN_STEGO_DUMMYB), mRmTp_DIRECT_SOUTH }, /* stego torso */

  { mMmd_UT(6, 6), FTR_START(FTR_DIN_PTERA_DUMMY), mRmTp_DIRECT_SOUTH }, /* ptera skull */
  { mMmd_UT(6, 5), FTR_START(FTR_DIN_PTERA_DUMMY), mRmTp_DIRECT_SOUTH }, /* ptera right wing */
  { mMmd_UT(6, 7), FTR_START(FTR_DIN_PTERA_DUMMY), mRmTp_DIRECT_SOUTH }, /* ptera left wing */

  { mMmd_UT(9, 10), FTR_START(FTR_DIN_HUTABA_DUMMY), mRmTp_DIRECT_SOUTH }, /* plesio skull */
  { mMmd_UT(11, 10), FTR_START(FTR_DIN_HUTABA_DUMMY), mRmTp_DIRECT_SOUTH }, /* plesio neck */
  { mMmd_UT(13, 10), FTR_START(FTR_DIN_HUTABA_DUMMY), mRmTp_DIRECT_SOUTH }, /* plesio torso */

  { mMmd_UT(2, 7), FTR_START(FTR_DIN_MAMMOTH_DUMMY), mRmTp_DIRECT_EAST }, /* mammoth skull */
  { mMmd_UT(2, 5), FTR_START(FTR_DIN_MAMMOTH_DUMMY), mRmTp_DIRECT_EAST }, /* mammoth torso */

  { mMmd_UT(6, 8), FTR_START(FTR_DIN_DUMMY), mRmTp_DIRECT_SOUTH }, /* amber */
  { mMmd_UT(7, 8), FTR_START(FTR_DIN_DUMMY), mRmTp_DIRECT_SOUTH }, /* dinosaur track */
  { mMmd_UT(8, 8), FTR_START(FTR_DIN_DUMMY), mRmTp_DIRECT_SOUTH }, /* ammonite */
  { mMmd_UT(9, 8), FTR_START(FTR_DIN_DUMMY), mRmTp_DIRECT_SOUTH }, /* dinosaur egg */
  { mMmd_UT(10, 8), FTR_START(FTR_DIN_DUMMY), mRmTp_DIRECT_SOUTH } /* trilobite */
};

static void mMmd_MuseumFossilProcess_MakeFgData() {
  mMmd_fossil_data_c* fossil_data = mMmd_museum_fossil_data;
  mActor_name_t* fossil_fg = mFI_BkNumtoUtFGTop(0, 0);
  int fossil_ut;
  int rotation;
  int fossil_idx;
  int item;

  if (fossil_fg != NULL) {
    for (fossil_idx = 0; fossil_idx < mMmd_FOSSIL_NUM; fossil_idx++) {
      rotation = fossil_data[fossil_idx].rotation & 3;
      fossil_ut = fossil_data[fossil_idx].ut;

      if (mMmd_FossilInfo(fossil_idx)) {
        int valid = FALSE;

        if (fossil_idx >= 0 && fossil_idx < mMmd_FOSSIL_NUM) {
          valid = TRUE;
        }

        /* TODO: this might be a fake match */
        item = FTR_START(FTR_DIN_TRIKERA_HEAD);
        if (valid) {
          mActor_name_t fossil_ftr_idx = FTR_START(FTR_DIN_TRIKERA_HEAD) + (mActor_name_t)FTR_NO_2_IDX(fossil_idx);
          item = fossil_ftr_idx;
        }
        //item = (valid != FALSE ? (mActor_name_t)(FTR_DINO_TRICERA_SKULL + (mActor_name_t)FTR_NO_2_IDX(fossil_idx)) : FTR_DINO_TRICERA_SKULL);
        fossil_fg[fossil_ut] = (mActor_name_t)item + rotation;
      }
      else {
        fossil_fg[fossil_ut] = fossil_data[fossil_idx].item + rotation;
      }
    }
  }
}

static void mMmd_dummy_process() { }

typedef void (*mMmd_DISPLAY_PROC)();

typedef struct museum_display_scene_process_s {
  int scene_no;
  mMmd_DISPLAY_PROC display_proc;
} mMmd_scene_process_c;

static mMmd_scene_process_c mMmd_scene_process_data[mMmd_CATEGORY_NUM + 1] = {
  { SCENE_MUSEUM_ROOM_PAINTING, &mMmd_dummy_process },
  { SCENE_MUSEUM_ROOM_FOSSIL, &mMmd_MuseumFossilProcess_MakeFgData },
  { SCENE_MUSEUM_ROOM_INSECT, &mMmd_dummy_process },
  { SCENE_MUSEUM_ROOM_FISH, &mMmd_dummy_process },
  { -1, NULL }
};

extern void mMmd_MakeMuseumDisplayData() {
  int scene_no = Save_Get(scene_no);
  int i = 0;

  while (mMmd_scene_process_data[i].scene_no != -1) {
    if (scene_no == mMmd_scene_process_data[i].scene_no) {
      (*mMmd_scene_process_data[i].display_proc)();
      break;
    }

    i++;
  }
}

extern void mMmd_DeletePresentedByPlayer(u8 player_no) {
  int search_no = player_no + 1;

  if (player_no < PLAYER_NUM) {
    int i;

    for (i = 0; i < mMmd_ART_NUM; i++) {
      int donator = mMmd_ArtInfo(i);
      if (donator == search_no) {
        mMmd_ART_CLR(Save_Get(museum_display), i);
        mMmd_ART_SET(Save_Get(museum_display), i, mMmd_DONATOR_DELETED_PLAYER);
      }
    }

    for (i = 0; i < mMmd_FOSSIL_NUM; i++) {
      int donator = mMmd_FossilInfo(i);
      if (donator == search_no) {
        mMmd_FOSSIL_CLR(Save_Get(museum_display), i);
        mMmd_FOSSIL_SET(Save_Get(museum_display), i, mMmd_DONATOR_DELETED_PLAYER);
      }
    }

    for (i = 0; i < mMmd_INSECT_NUM; i++) {
      int donator = mMmd_InsectInfo(i);
      if (donator == search_no) {
        mMmd_INSECT_CLR(Save_Get(museum_display), i);
        mMmd_INSECT_SET(Save_Get(museum_display), i, mMmd_DONATOR_DELETED_PLAYER);
      }
    }

    for (i = 0; i < mMmd_FISH_NUM; i++) {
      int donator = mMmd_FishInfo(i);
      if (donator == search_no) {
        mMmd_FISH_CLR(Save_Get(museum_display), i);
        mMmd_FISH_SET(Save_Get(museum_display), i, mMmd_DONATOR_DELETED_PLAYER);
      }
    }
  }
}

extern int mMmd_CountDisplayedFossil() {
  int i;
  int displayed = 0;
  
  for (i = 0; i < mMmd_FOSSIL_NUM; i++) {
    int donator = mMmd_FossilInfo(i);

    if (donator >= mMmd_DONATOR_PLAYER1 && donator <= mMmd_DONATOR_DELETED_PLAYER) {
      displayed++;
    }
  }

  return displayed;
}

extern int mMmd_CountDisplayedArt() {
  int i;
  int displayed = 0;
  
  for (i = 0; i < mMmd_ART_NUM; i++) {
    int donator = mMmd_ArtInfo(i);

    if (donator >= mMmd_DONATOR_PLAYER1 && donator <= mMmd_DONATOR_DELETED_PLAYER) {
      displayed++;
    }
  }

  return displayed;
}

extern int mMmd_CountDisplayedInsect() {
  int i;
  int displayed = 0;
  
  for (i = 0; i < mMmd_INSECT_NUM; i++) {
    int donator = mMmd_InsectInfo(i);

    if (donator >= mMmd_DONATOR_PLAYER1 && donator <= mMmd_DONATOR_DELETED_PLAYER) {
      displayed++;
    }
  }

  return displayed;
}

extern int mMmd_CountDisplayedFish() {
  int i;
  int displayed = 0;
  
  for (i = 0; i < mMmd_FISH_NUM; i++) {
    int donator = mMmd_FishInfo(i);

    if (donator >= mMmd_DONATOR_PLAYER1 && donator <= mMmd_DONATOR_DELETED_PLAYER) {
      displayed++;
    }
  }

  return displayed;
}
