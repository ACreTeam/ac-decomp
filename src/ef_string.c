#include "ef_effect_control.h"

static void eString_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eString_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eString_mv(eEC_Effect_c* effect, GAME* game);
static void eString_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_string = {
    // clang-format off
    &eString_init,
    &eString_ct,
    &eString_mv,
    &eString_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eString_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eString_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eString_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eString_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
