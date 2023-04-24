#ifndef M_SNOWMAN_H
#define M_SNOWMAN_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mSN_SAVE_COUNT 3

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

#ifdef __cplusplus
}
#endif

#endif
