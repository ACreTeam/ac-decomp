#include "ef_effect_control.h"

static void eMH_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eMH_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eMH_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eMH_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

eEC_PROFILE_c iam_ef_make_hem = {
    // clang-format off
    &eMH_init,
    &eMH_ct,
    &eMH_mv,
    &eMH_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static void eMHK_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eMHK_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eMHK_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eMHK_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

eEC_PROFILE_c iam_ef_make_hem_kira = {
    // clang-format off
    &eMHK_init,
    &eMHK_ct,
    &eMHK_mv,
    &eMHK_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static void eMHL_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eMHL_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eMHL_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eMHL_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

eEC_PROFILE_c iam_ef_make_hem_light = {
    // clang-format off
    &eMHL_init,
    &eMHL_ct,
    &eMHL_mv,
    &eMHL_dw,
    195,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};
