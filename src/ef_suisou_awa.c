#include "ef_effect_control.h"

static void eSuisou_Awa_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSuisou_Awa_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSuisou_Awa_mv(eEC_Effect_c* effect, GAME* game);
static void eSuisou_Awa_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_suisou_awa = {
    // clang-format off
    &eSuisou_Awa_init,
    &eSuisou_Awa_ct,
    &eSuisou_Awa_mv,
    &eSuisou_Awa_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eSuisou_Awa_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eSuisou_Awa_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eSuisou_Awa_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eSuisou_Awa_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
