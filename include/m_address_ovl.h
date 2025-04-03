#ifndef M_ADDRESS_OVL_H
#define M_ADDRESS_OVL_H

#include "types.h"
#include "m_address_ovl_h.h"
#include "m_submenu_ovl.h"
#include "m_mail.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    mAD_PAGE_PLAYER,
    mAD_PAGE_NPC0,
    mAD_PAGE_NPC1,

    mAD_PAGE_NUM
};

enum {
    mAD_PROC_REFUSE,
    mAD_PROC_START,
    mAD_PROC_SELECT,
    mAD_PROC_TURN_PAGE,
    mAD_PROC_TURN_PAGE2,

    mAD_PROC_NUM
};

enum {
    mAD_OPEN_ADDRESS,
    mAD_OPEN_WAIT,

    mAD_OPEN_NUM
};

#define mAD_PAGE_MAX_ENTRIES 8

struct address_ovl_s {
    u8 page_bitfield;
    u8 page_count;
    u8 proc_idx;
    u8 curIdx;
    u8 nextIdx;
    u8 selected_entry;
    u8 show_museum_address;
    u8 editor_move_down;
    u8 page_entry_count[mAD_PAGE_NUM];
    f32 pos_x;
    f32 speed_x;
    f32 pile[mAD_PAGE_NUM];
    f32 goal_pile[mAD_PAGE_NUM];
    Mail_nm_c player_mail_name[PLAYER_NUM + 1]; // last entry is the museum name
    Mail_nm_c animal_mail_name[ANIMAL_NUM_MAX];
    Gfx* display_list; // set to the beginning of the address display list data for drawing over editor etc
};

extern void mAD_address_ovl_construct(Submenu* submenu);
extern void mAD_address_ovl_destruct(Submenu* submenu);
extern void mAD_address_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
