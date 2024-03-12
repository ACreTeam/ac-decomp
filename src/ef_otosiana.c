#include "ef_effect_control.h"

static void eOtosiana_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eOtosiana_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eOtosiana_mv(eEC_Effect_c* effect, GAME* game);
static void eOtosiana_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_otosiana = {
    // clang-format off
    &eOtosiana_init,
    &eOtosiana_ct,
    &eOtosiana_mv,
    &eOtosiana_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eOtosiana_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eOtosiana_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eOtosiana_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eOtosiana_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
