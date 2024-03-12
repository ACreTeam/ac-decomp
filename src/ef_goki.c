#include "ef_effect_control.h"

static void eGoki_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eGoki_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eGoki_mv(eEC_Effect_c* effect, GAME* game);
static void eGoki_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_goki = {
    // clang-format off
    &eGoki_init,
    &eGoki_ct,
    &eGoki_mv,
    &eGoki_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eGoki_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eGoki_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eGoki_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eGoki_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
