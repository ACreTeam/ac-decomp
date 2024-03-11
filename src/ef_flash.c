#include "ef_effect_control.h"

static void eFlash_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eFlash_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eFlash_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eFlash_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

eEC_PROFILE_c iam_ef_flash = {
    // clang-format off
    &eFlash_init,
    &eFlash_ct,
    &eFlash_mv,
    &eFlash_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static void eFlashC_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eFlashC_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eFlashC_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eFlashC_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

eEC_PROFILE_c iam_ef_flashC = {
    // clang-format off
    &eFlashC_init,
    &eFlashC_ct,
    &eFlashC_mv,
    &eFlashC_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};
