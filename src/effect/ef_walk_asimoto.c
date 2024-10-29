#include "ef_effect_control.h"

static void eWalk_Asimoto_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eWalk_Asimoto_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eWalk_Asimoto_mv(eEC_Effect_c* effect, GAME* game);
static void eWalk_Asimoto_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_walk_asimoto = {
    // clang-format off
    &eWalk_Asimoto_init,
    &eWalk_Asimoto_ct,
    &eWalk_Asimoto_mv,
    &eWalk_Asimoto_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eWalk_Asimoto_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eWalk_Asimoto_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eWalk_Asimoto_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eWalk_Asimoto_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
