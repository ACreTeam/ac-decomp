#ifndef M_MONUMENT_H
#define M_MONUMENT_H

#include "types.h"
#include "m_name_table.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mMM_MONUMENT_MAX 5
#define mMM_MONUMENT_MAX_PER_ACRE 3
#define mMM_MONUMENT_SET_COUNT 3

enum {
    mMM_MONUMENT_SET_A,
    mMM_MONUMENT_SET_B,
    mMM_MONUMENT_SET_C,
    mMM_MONUMENT_SET_D,
    mMM_MONUMENT_SET_E,

    mMM_MONUMENT_SET_NUM
};

typedef struct monument_order_s {
    u8 bx;
    u8 bz;
    u8 ux;
    u8 uz;
    mActor_name_t name;
    u16 pad;
} mMM_order_c;

#define mMM_ORDER_PENDING 0
#define mMM_ORDER_NONE 1

extern int mMM_check_order(void);
extern int mMM_set_order(mMM_order_c* order);
extern void mMM_clear_order(void);
extern int mMM_set_monument(void);
extern int mMM_clear_monument(mMM_order_c* order);
extern int mMM_make_candidate_place_list(mMM_order_c* order, int count);
extern int mMM_get_monument_price(mActor_name_t monument);
extern mActor_name_t mMM_get_monument_name(int idx);
extern int mMM_get_monument_idx(mActor_name_t monument);
extern mActor_name_t mMM_check_monument_in_npc_house_block(ACTOR* actorx);
extern void mMM_set_monument_name_str(mActor_name_t monument, int str_no);

#ifdef __cplusplus
}
#endif

#endif
