#include "ef_effect_control.h"

static void eDT_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eDT_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eDT_mv(eEC_Effect_c* effect, GAME* game);
static void eDT_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_dust = {
    // clang-format off
    &eDT_init,
    &eDT_ct,
    &eDT_mv,
    &eDT_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static void eDT_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eDT_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eDT_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eDT_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
