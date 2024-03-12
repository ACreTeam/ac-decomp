#include "ef_effect_control.h"

static void eYajirushi_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eYajirushi_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eYajirushi_mv(eEC_Effect_c* effect, GAME* game);
static void eYajirushi_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_yajirushi = {
    // clang-format off
    &eYajirushi_init,
    &eYajirushi_ct,
    &eYajirushi_mv,
    &eYajirushi_dw,
    6,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eYajirushi_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eYajirushi_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eYajirushi_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eYajirushi_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
