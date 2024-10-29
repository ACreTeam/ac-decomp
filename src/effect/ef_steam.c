#include "ef_effect_control.h"

static void eSteam_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSteam_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSteam_mv(eEC_Effect_c* effect, GAME* game);
static void eSteam_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_steam = {
    // clang-format off
    &eSteam_init,
    &eSteam_ct,
    &eSteam_mv,
    &eSteam_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eSteam_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eSteam_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eSteam_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eSteam_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
