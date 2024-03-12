#include "ef_effect_control.h"

static void eOMN_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eOMN_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eOMN_mv(eEC_Effect_c* effect, GAME* game);
static void eOMN_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_otikomi = {
    // clang-format off
    &eOMN_init,
    &eOMN_ct,
    &eOMN_mv,
    &eOMN_dw,
    10,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eOMN_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eOMN_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eOMN_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eOMN_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
