#include "ef_effect_control.h"

static void eFuro_Yuge_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eFuro_Yuge_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eFuro_Yuge_mv(eEC_Effect_c* effect, GAME* game);
static void eFuro_Yuge_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_furo_yuge = {
    // clang-format off
    &eFuro_Yuge_init,
    &eFuro_Yuge_ct,
    &eFuro_Yuge_mv,
    &eFuro_Yuge_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static void eFuro_Yuge_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eFuro_Yuge_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eFuro_Yuge_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eFuro_Yuge_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
