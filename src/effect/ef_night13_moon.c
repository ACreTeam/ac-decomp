#include "ef_effect_control.h"

static void eNight13Moon_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eNight13Moon_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eNight13Moon_mv(eEC_Effect_c* effect, GAME* game);
static void eNight13Moon_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_night13_moon = {
    // clang-format off
    &eNight13Moon_init,
    &eNight13Moon_ct,
    &eNight13Moon_mv,
    &eNight13Moon_dw,
    80,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static void eNight13Moon_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eNight13Moon_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eNight13Moon_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eNight13Moon_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
