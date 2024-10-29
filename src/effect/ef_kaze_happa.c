#include "ef_effect_control.h"

static void eKZH_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKZH_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKZH_mv(eEC_Effect_c* effect, GAME* game);
static void eKZH_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_kaze_happa = {
    // clang-format off
    &eKZH_init,
    &eKZH_ct,
    &eKZH_mv,
    &eKZH_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eKZH_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eKZH_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eKZH_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eKZH_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
