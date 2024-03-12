#include "ef_effect_control.h"

static void eBreak_Axe_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eBreak_Axe_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eBreak_Axe_mv(eEC_Effect_c* effect, GAME* game);
static void eBreak_Axe_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_break_axe = {
    // clang-format off
    &eBreak_Axe_init,
    &eBreak_Axe_ct,
    &eBreak_Axe_mv,
    &eBreak_Axe_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eBreak_Axe_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eBreak_Axe_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eBreak_Axe_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eBreak_Axe_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
