#include "ef_effect_control.h"

static void eHiramekiD_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eHiramekiD_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eHiramekiD_mv(eEC_Effect_c* effect, GAME* game);
static void eHiramekiD_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_hirameki_den = {
    // clang-format off
    &eHiramekiD_init,
    &eHiramekiD_ct,
    &eHiramekiD_mv,
    &eHiramekiD_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eHiramekiD_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eHiramekiD_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eHiramekiD_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eHiramekiD_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
