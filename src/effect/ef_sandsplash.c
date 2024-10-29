#include "ef_effect_control.h"

static void eSandsplash_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSandsplash_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSandsplash_mv(eEC_Effect_c* effect, GAME* game);
static void eSandsplash_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_sandsplash = {
    // clang-format off
    &eSandsplash_init,
    &eSandsplash_ct,
    &eSandsplash_mv,
    &eSandsplash_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eSandsplash_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eSandsplash_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eSandsplash_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eSandsplash_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
