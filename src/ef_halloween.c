#include "ef_effect_control.h"

static void eHalloween_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eHalloween_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eHalloween_mv(eEC_Effect_c* effect, GAME* game);
static void eHalloween_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_halloween = {
    // clang-format off
    &eHalloween_init,
    &eHalloween_ct,
    &eHalloween_mv,
    &eHalloween_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eHalloween_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eHalloween_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eHalloween_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eHalloween_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
