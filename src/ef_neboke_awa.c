#include "ef_effect_control.h"

static void eSleep_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSleep_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSleep_mv(eEC_Effect_c* effect, GAME* game);
static void eSleep_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_neboke_awa = {
    // clang-format off
    &eSleep_init,
    &eSleep_ct,
    &eSleep_mv,
    &eSleep_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eSleep_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eSleep_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eSleep_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eSleep_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
