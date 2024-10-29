#include "ef_effect_control.h"

static void eNight15Moon_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eNight15Moon_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eNight15Moon_mv(eEC_Effect_c* effect, GAME* game);
static void eNight15Moon_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_night15_moon = {
    // clang-format off
    &eNight15Moon_init,
    &eNight15Moon_ct,
    &eNight15Moon_mv,
    &eNight15Moon_dw,
    60,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static void eNight15Moon_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eNight15Moon_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eNight15Moon_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eNight15Moon_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
