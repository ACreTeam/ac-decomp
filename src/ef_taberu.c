#include "ef_effect_control.h"

static void eTaberu_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eTaberu_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eTaberu_mv(eEC_Effect_c* effect, GAME* game);
static void eTaberu_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_taberu = {
    // clang-format off
    &eTaberu_init,
    &eTaberu_ct,
    &eTaberu_mv,
    &eTaberu_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eTaberu_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eTaberu_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eTaberu_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eTaberu_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
