#ifndef M_FIELD_ASSESSMENT_H
#define M_FIELD_ASSESSMENT_H

#include "types.h"
#include "libu64/gfxprint.h"
#include "m_time.h"
#include "m_random_field_h.h"


#ifdef __cplusplus
extern "C" {
#endif

#define mFAs_PERFECT_DAY_STREAK_MAX 15 /* max number of perfect days in a row for golden axe reward */

#define mFAs_GRASS_OVER_NUM 5
#define mFAs_DUST_OVER_NUM 5
#define mFAs_FG_BLOCK_EXCLUDE_NUM 5 /* number of excluded block types */
#define mFAs_TREE_RANK_COUNT 5

enum {
  mFAs_FIELDRANK_ZERO,
  mFAs_FIELDRANK_ONE,
  mFAs_FIELDRANK_TWO,
  mFAs_FIELDRANK_THREE,
  mFAs_FIELDRANK_FOUR,
  mFAs_FIELDRANK_FIVE,
  mFAs_FIELDRANK_SIX,

  mFAs_FIELDRANK_NUM
};

enum {
  mFAs_CONDITION_NONE = -1,
  mFAs_CONDITION_DUST_OVER = 0,
  mFAs_CONDITION_TREE_LESS,
  mFAs_CONDITION_TREE_OVER,
  mFAs_CONDITION_GRASS_OVER,
  mFAs_CONDITION_NO_CASE,

  mFAs_CONDITION_NUM
};

/* sizeof(mFAs_GoodField_c) == 0xC */
typedef struct good_field_s {
  /* 0x00 */ lbRTC_time_c renew_time; /* time updated */
  /* 0x08 */ int perfect_day_streak; /* number of days in a row the town is "perfect" */
} mFAs_GoodField_c;


extern void mFAs_ClearGoodField();
extern int mFAs_CheckGoodField();
extern int mFAs_GetFieldRank_Condition(int* rank, int* block_x, int* block_z);
extern void mFAs_SetFieldRank();
extern int mFAs_GetFieldRank();
extern void mFAs_PrintFieldAssessment(gfxprint_t* gfxprint);

#ifdef __cplusplus
}
#endif

#endif
