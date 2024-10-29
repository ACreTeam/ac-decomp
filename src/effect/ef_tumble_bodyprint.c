#include "ef_effect_control.h"

static void eTumbleBodyPrint_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eTumbleBodyPrint_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eTumbleBodyPrint_mv(eEC_Effect_c* effect, GAME* game);
static void eTumbleBodyPrint_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_tumble_bodyprint = {
    // clang-format off
    &eTumbleBodyPrint_init,
    &eTumbleBodyPrint_ct,
    &eTumbleBodyPrint_mv,
    &eTumbleBodyPrint_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eTumbleBodyPrint_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eTumbleBodyPrint_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eTumbleBodyPrint_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eTumbleBodyPrint_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
