#include "ef_effect_control.h"

static void eTM_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eTM_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eTM_mv(eEC_Effect_c* effect, GAME* game);
static void eTM_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_takurami = {
    // clang-format off
    &eTM_init,
    &eTM_ct,
    &eTM_mv,
    &eTM_dw,
    eEC_IGNORE_DEATH,
    eEC_EFFECT_TAKURAMI_KIRA,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eTM_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eTM_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eTM_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eTM_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
