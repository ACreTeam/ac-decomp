#include "ef_effect_control.h"

static void eKONP_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKONP_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKONP_mv(eEC_Effect_c* effect, GAME* game);
static void eKONP_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_konpu = {
    // clang-format off
    &eKONP_init,
    &eKONP_ct,
    &eKONP_mv,
    &eKONP_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eKONP_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eKONP_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eKONP_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eKONP_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
