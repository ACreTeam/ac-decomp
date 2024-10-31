#ifndef M_LEDIT_OVL_H
#define M_LEDIT_OVL_H

#include "types.h"
#include "m_submenu.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    mLE_TYPE_PLAYER_NAME,
    mLE_TYPE_COUNTRY_NAME,
    mLE_TYPE_EPHRASE,
    mLE_TYPE_RESET,
    mLE_TYPE_REQUEST,
    mLE_TYPE_MYORIGINAL_NAME,
    mLE_TYPE_ISLAND_NAME,

    mLE_TYPE_NUM
};

extern void mLE_ledit_ovl_construct(Submenu* submenu);
extern void mLE_ledit_ovl_destruct(Submenu* submenu);
extern void mLE_ledit_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
