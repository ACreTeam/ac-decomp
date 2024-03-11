#include "ef_effect_control.h"

static void eFootPrint_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eFootPrint_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eFootPrint_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eFootPrint_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

eEC_PROFILE_c iam_ef_footprint = {
    // clang-format off
    &eFootPrint_init,
    &eFootPrint_ct,
    &eFootPrint_mv,
    &eFootPrint_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};
