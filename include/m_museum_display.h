#ifndef M_MUSEUM_DISPLAY_H
#define M_MUSEUM_DISPLAY_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* TODO: these should be determined from item name indices */

#define mMmd_FOSSIL_BIT_NUM 13
#define mMmd_ART_BIT_NUM 8
#define mMmd_FISH_BIT_NUM 21
#define mMmd_INSECT_BIT_NUM 21

/* 4 bits per donatable item */
#define mMmd_BIT_INFO(info, category, index) \
  (((info).category[(index) / 2] >> (((index) & 1) << 2)) & 0x0F)

#define mMmd_ART_BIT(info, index) mMmd_BIT_INFO(info, art, index)
#define mMmd_INSECT_BIT(info, index) mMmd_BIT_INFO(info, insect, index)
#define mMmd_FISH_BIT(info, index) mMmd_BIT_INFO(info, fish, index)
#define mMmd_FOSSIL_BIT(info, index) mMmd_BIT_INFO(info, fossil, index)

/* sizeof(mMmd_info_c) == 0x3F */
typedef struct museum_display_info_s {
  /* 0x00 */ u8 fossil_bit[mMmd_FOSSIL_BIT_NUM];
  /* 0x0D */ u8 art_bit[mMmd_ART_BIT_NUM];
  /* 0x15 */ u8 fish_bit[mMmd_FISH_BIT_NUM];
  /* 0x2A */ u8 insect_bit[mMmd_INSECT_BIT_NUM];
} mMmd_info_c;

#ifdef __cplusplus
}
#endif

#endif
