#include "ef_effect_control.h"

static void eTurnFootPrint_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eTurnFootPrint_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eTurnFootPrint_mv(eEC_Effect_c* effect, GAME* game);
static void eTurnFootPrint_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_turn_footprint = {
    // clang-format off
    &eTurnFootPrint_init,
    &eTurnFootPrint_ct,
    &eTurnFootPrint_mv,
    &eTurnFootPrint_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eTurnFootPrint_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}

static void eTurnFootPrint_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eTurnFootPrint_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eTurnFootPrint_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
