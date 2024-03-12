#include "ef_effect_control.h"

static void eCar_Light_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eCar_Light_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eCar_Light_mv(eEC_Effect_c* effect, GAME* game);
static void eCar_Light_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_car_light = {
    // clang-format off
    &eCar_Light_init,
    &eCar_Light_ct,
    &eCar_Light_mv,
    &eCar_Light_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eCar_Light_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eCar_Light_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eCar_Light_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eCar_Light_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
