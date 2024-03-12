#include "ef_effect_control.h"

static void eImpact_Star_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eImpact_Star_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eImpact_Star_mv(eEC_Effect_c* effect, GAME* game);
static void eImpact_Star_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_impact_star = {
    // clang-format off
    &eImpact_Star_init,
    &eImpact_Star_ct,
    &eImpact_Star_mv,
    &eImpact_Star_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eImpact_Star_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eImpact_Star_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eImpact_Star_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eImpact_Star_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
