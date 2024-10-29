#include "ef_effect_control.h"

static void eHiramekiH_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eHiramekiH_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eHiramekiH_mv(eEC_Effect_c* effect, GAME* game);
static void eHiramekiH_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_hirameki_hikari = {
    // clang-format off
    &eHiramekiH_init,
    &eHiramekiH_ct,
    &eHiramekiH_mv,
    &eHiramekiH_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eHiramekiH_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eHiramekiH_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eHiramekiH_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eHiramekiH_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
