#include "ef_effect_control.h"

static void eLove_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eLove_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eLove_mv(eEC_Effect_c* effect, GAME* game);
static void eLove_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_lovelove = {
    // clang-format off
    &eLove_init,
    &eLove_ct,
    &eLove_mv,
    &eLove_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eLove_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eLove_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eLove_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eLove_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
