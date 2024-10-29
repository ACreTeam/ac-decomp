#include "ef_effect_control.h"

static void eKT_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKT_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKT_mv(eEC_Effect_c* effect, GAME* game);
static void eKT_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_kantanhu = {
    // clang-format off
    &eKT_init,
    &eKT_ct,
    &eKT_mv,
    &eKT_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eKT_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eKT_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eKT_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eKT_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
