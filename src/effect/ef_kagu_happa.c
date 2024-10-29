#include "ef_effect_control.h"

static void eKagu_Happa_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKagu_Happa_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKagu_Happa_mv(eEC_Effect_c* effect, GAME* game);
static void eKagu_Happa_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_kagu_happa = {
    // clang-format off
    &eKagu_Happa_init,
    &eKagu_Happa_ct,
    &eKagu_Happa_mv,
    &eKagu_Happa_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eKagu_Happa_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eKagu_Happa_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eKagu_Happa_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eKagu_Happa_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
