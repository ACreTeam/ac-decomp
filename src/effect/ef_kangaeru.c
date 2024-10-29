#include "ef_effect_control.h"

static void eKG_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKG_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKG_mv(eEC_Effect_c* effect, GAME* game);
static void eKG_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_kangaeru = {
    // clang-format off
    &eKG_init,
    &eKG_ct,
    &eKG_mv,
    &eKG_dw,
    7,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eKG_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eKG_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eKG_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eKG_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
