#include "ef_effect_control.h"

static void eMK_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eMK_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eMK_mv(eEC_Effect_c* effect, GAME* game);
static void eMK_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_muka = {
    // clang-format off
    &eMK_init,
    &eMK_ct,
    &eMK_mv,
    &eMK_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eMK_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eMK_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eMK_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eMK_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
