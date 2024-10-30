#ifndef M_MUSEUM_DISPLAY_H
#define M_MUSEUM_DISPLAY_H

#include "types.h"
#include "m_actor_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/* TODO: these should be determined from item name indices */

#define mMmd_FOSSIL_BIT_NUM 13
#define mMmd_ART_BIT_NUM 8
#define mMmd_FISH_BIT_NUM 21
#define mMmd_INSECT_BIT_NUM 21

#define mMmd_FOSSIL_NUM 25
#define mMmd_ART_NUM 15
#define mMmd_INSECT_NUM 40
#define mMmd_FISH_NUM 40

enum {
    mMmd_DISPLAY_CANNOT_DONATE,   /* Item cannot be donated */
    mMmd_DISPLAY_CAN_DONATE,      /* Item can be donated */
    mMmd_DISPLAY_ALREADY_DONATED, /* Item has already been donated */

    mMmd_DISPLAY_NUM
};

enum {
    mMmd_DONATOR_NONE,
    mMmd_DONATOR_PLAYER1,
    mMmd_DONATOR_PLAYER2,
    mMmd_DONATOR_PLAYER3,
    mMmd_DONATOR_PLAYER4,
    mMmd_DONATOR_DELETED_PLAYER,

    mMmd_DONATOR_NUM
};

#define mMmd_IS_DONATED(donator) ((donator) >= mMmd_DONATOR_PLAYER1 && (donator) <= mMmd_DONATOR_DELETED_PLAYER)
#define mMmd_DONATOR_EXISTS(donator) ((donator) >= mMmd_DONATOR_PLAYER1 && (donator) <= mMmd_DONATOR_PLAYER4)
#define mMmd_DONATOR_PLR_IDX(donator) (((donator)-1) & 3)

enum {
    mMmd_CATEGORY_FOSSIL,
    mMmd_CATEGORY_ART,
    mMmd_CATEGORY_INSECT,
    mMmd_CATEGORY_FISH,

    mMmd_CATEGORY_NUM
};

/* 4 bits per donatable item */
#define mMmd_BIT_INFO(info, category, index) (((info).category##_bit[(index) >> 1] >> (((index)&1) << 2)) & 0x0F)
#define mMmd_BIT_INFO2(bitfield, index) (((bitfield)[(index) >> 1] >> (((index)&1) << 2)) & 0x0F)

#define mMmd_ART_BIT(info, index) mMmd_BIT_INFO(info, art, index)
#define mMmd_INSECT_BIT(info, index) mMmd_BIT_INFO(info, insect, index)
#define mMmd_FISH_BIT(info, index) mMmd_BIT_INFO(info, fish, index)
#define mMmd_FOSSIL_BIT(info, index) mMmd_BIT_INFO(info, fossil, index)

#define mMmd_BIT_CLR(info, category, index) ((info).category##_bit[(index) >> 1] &= ~(0b1111 << (((index)&1) * 4)))

#define mMmd_FOSSIL_CLR(info, index) mMmd_BIT_CLR(info, fossil, index)
#define mMmd_ART_CLR(info, index) mMmd_BIT_CLR(info, art, index)
#define mMmd_INSECT_CLR(info, index) mMmd_BIT_CLR(info, insect, index)
#define mMmd_FISH_CLR(info, index) mMmd_BIT_CLR(info, fish, index)

#define mMmd_BIT_SET(info, category, index, value) \
    ((info).category##_bit[(index) >> 1] |= (((value)&0b1111) << (((index)&1)) * 4))

#define mMmd_FOSSIL_SET(info, index, value) mMmd_BIT_SET(info, fossil, index, value)
#define mMmd_ART_SET(info, index, value) mMmd_BIT_SET(info, art, index, value)
#define mMmd_INSECT_SET(info, index, value) mMmd_BIT_SET(info, insect, index, value)
#define mMmd_FISH_SET(info, index, value) mMmd_BIT_SET(info, fish, index, value)

/* sizeof(mMmd_info_c) == 0x3F */
typedef struct museum_display_info_s {
    /* 0x00 */ u8 fossil_bit[mMmd_FOSSIL_BIT_NUM];
    /* 0x0D */ u8 art_bit[mMmd_ART_BIT_NUM];
    /* 0x15 */ u8 fish_bit[mMmd_FISH_BIT_NUM];
    /* 0x2A */ u8 insect_bit[mMmd_INSECT_BIT_NUM];
} mMmd_info_c;

extern int mMmd_FossilInfo(int fossil_no);
extern int mMmd_ArtInfo(int art_no);
extern int mMmd_InsectInfo(int insect_no);
extern int mMmd_FishInfo(int fish_no);
extern void mMmd_SetFossil(int fossil_no);
extern void mMmd_SetArt(int art_no);
extern void mMmd_SetInsect(int insect_no);
extern void mMmd_SetFish(int fish_no);
extern int mMmd_GetDisplayInfo(mActor_name_t item);
extern int mMmd_RequestMuseumDisplay(mActor_name_t item);
extern void mMmd_MakeMuseumDisplayData();
extern void mMmd_DeletePresentedByPlayer(u8 player_no);
extern int mMmd_CountDisplayedFossil();
extern int mMmd_CountDisplayedArt();
extern int mMmd_CountDisplayedInsect();
extern int mMmd_CountDisplayedFish();

#ifdef __cplusplus
}
#endif

#endif
