#ifndef M_ENDEDITCHK_H
#define M_ENDEDITCHK_H

#include "types.h"
#include "m_editEndChk_ovl_h.h"
#include "m_submenu_ovl.h"

#ifdef __cplusplus
extern "C" {
#endif

/* TODO: verify these */
enum {
    mEE_TYPE_BOARD,
    mEE_TYPE_NOTICE,
    mEE_TYPE_MSCORE,
    mEE_TYPE_CPACK,
    mEE_TYPE_ORIGINAL_DESIGN,

    mEE_TYPE_NUM
};

struct end_edit_chk_s {
    u8 moving_in;
    u8 selected_answer;
    u8 question_alpha_step;
    u8 question_alpha;
    f32 scale;
};

extern void mEE_editEndChk_ovl_set_proc(Submenu* submenu);
extern void mEE_editEndChk_ovl_construct(Submenu* submenu);
extern void mEE_editEndChk_ovl_destruct(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
