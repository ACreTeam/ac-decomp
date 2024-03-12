#include "ef_effect_control.h"

static void eShootingSet_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eShootingSet_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eShootingSet_mv(eEC_Effect_c* effect, GAME* game);
static void eShootingSet_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_shooting_set = {
    // clang-format off
    &eShootingSet_init,
    &eShootingSet_ct,
    &eShootingSet_mv,
    &eShootingSet_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static void eShootingSet_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eShootingSet_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eShootingSet_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eShootingSet_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
