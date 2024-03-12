#include "ef_effect_control.h"

static void eCar_Blight_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eCar_Blight_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eCar_Blight_mv(eEC_Effect_c* effect, GAME* game);
static void eCar_Blight_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_car_blight = {
    // clang-format off
    &eCar_Blight_init,
    &eCar_Blight_ct,
    &eCar_Blight_mv,
    &eCar_Blight_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eCar_Blight_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eCar_Blight_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eCar_Blight_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eCar_Blight_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
