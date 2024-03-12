#include "ef_effect_control.h"

static void eShootingKira_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eShootingKira_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eShootingKira_mv(eEC_Effect_c* effect, GAME* game);
static void eShootingKira_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_shooting_kira = {
    // clang-format off
    &eShootingKira_init,
    &eShootingKira_ct,
    &eShootingKira_mv,
    &eShootingKira_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eShootingKira_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eShootingKira_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eShootingKira_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eShootingKira_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
