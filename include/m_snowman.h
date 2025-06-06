#ifndef M_SNOWMAN_H
#define M_SNOWMAN_H

#include "types.h"
#include "m_lib.h"
#include "m_actor_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mSN_SAVE_COUNT 3

enum {
    mSN_RESULT_PERFECT,
    mSN_RESULT_GOOD,
    mSN_RESULT_OK,
    mSN_RESULT_BAD,

    mSN_RESULT_NUM
};

/* sizeof(mSN_snowman_data_c) == 4 */
typedef struct snowman_data_s {
  /* 0x00 */ u8 exists; /* when non-zero, snowman 'exists' */
  /* 0x01 */ u8 head_size; /* size of the snowman's head */
  /* 0x02 */ u8 body_size; /* size of the snowman's body */
  /* 0x03 */ u8 score; /* score based on snowman proportions */
} mSN_snowman_data_c;

/* sizeof(mSN_snowman_save_c) == 0xC */
typedef struct snowman_save_data_s {
  /* 0x00 */ mSN_snowman_data_c snowmen_data[mSN_SAVE_COUNT];
} mSN_snowman_save_c;

/* sizeof(mSN_snowman_info_c) == 0xC */
typedef struct snowman_info_s{
  /* 0x00 */ mSN_snowman_data_c data;
  /* 0x04 */ xyz_t pos;
} mSN_snowman_info_c;

extern int mSN_check_life(mActor_name_t* ac, int idx);
extern int mSN_ClearSnowmanData(mActor_name_t* ac, int idx);
extern int mSN_ClearSnowman(mActor_name_t* ac);
extern int mSN_MeltSnowman(mActor_name_t* ac, int days);
extern int mSN_get_free_space();
extern void mSN_regist_snowman_society(mSN_snowman_info_c* info);
extern void mSN_decide_msg();
extern void mSN_snowman_init();

#ifdef __cplusplus
}
#endif

#endif
