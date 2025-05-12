#ifndef M_CPMAIL_OVL_H
#define M_CPMAIL_OVL_H

#include "types.h"
#include "m_cpmail_ovl_h.h"
#include "m_submenu.h"
#include "m_card.h"

#ifdef __cplusplus
extern "C" {
#endif

// #define mCM_PAGE_COUNT 8
// #define mCM_MAIL_COUNT 20
// #define mCM_FOLDER_NAME_LEN 12
#define mCM_FOLDER_NAME_MAX_WIDTH 120

struct cpmail_ovl_s {
    mCD_keep_mail_c* card_mail;
    Mail_c player_mail[mPr_INVENTORY_MAIL_COUNT];
    u8 page_order[mCD_KEEP_MAIL_PAGE_COUNT];
    s16 page_move_timer;
    u8 next_page_id;
    u8 _BB3;
    u32 mark_bitfield;
    int mark_flag;
    u8 _BBC;
    u32 mark_bitfield2;
};

extern void mCM_cpmail_ovl_construct(Submenu* submenu);
extern void mCM_cpmail_ovl_destruct(Submenu* submenu);
extern void mCM_cpmail_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
