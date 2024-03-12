#include "ef_effect_control.h"

static void ePunRed_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void ePunRed_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void ePunRed_mv(eEC_Effect_c* effect, GAME* game);
static void ePunRed_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_pun_sekimen = {
    // clang-format off
    &ePunRed_init,
    &ePunRed_ct,
    &ePunRed_mv,
    &ePunRed_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void ePunRed_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void ePunRed_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void ePunRed_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void ePunRed_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
