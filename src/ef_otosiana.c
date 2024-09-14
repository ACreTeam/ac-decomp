#include "ef_effect_control.h"

#include "m_common_data.h"

static void eOtosiana_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eOtosiana_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eOtosiana_mv(eEC_Effect_c* effect, GAME* game);
static void eOtosiana_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_otosiana = {
    // clang-format off
    &eOtosiana_init,
    &eOtosiana_ct,
    &eOtosiana_mv,
    &eOtosiana_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eOtosiana_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    (*eEC_CLIP->make_effect_proc)(eEC_EFFECT_OTOSIANA, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eOtosiana_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 16;
}

static void eOtosiana_mv(eEC_Effect_c* effect, GAME* game) {
    static s16 angle_tbl[] = { DEG2SHORT_ANGLE2(0.0f), DEG2SHORT_ANGLE2(135.0f), DEG2SHORT_ANGLE2(270.0f) };

    if ((s16)(effect->timer & 7) == 0) {
        int i;

        for (i = 0; i < 3; i++) {
            xyz_t pos = effect->position;
            s16 angle = angle_tbl[i];

            if ((effect->timer & 15) == 0) {
                angle += DEG2SHORT_ANGLE2(180.0f);
            }

            eEC_CLIP->effect_make_proc(eEC_EFFECT_DIG_MUD, pos, effect->prio, angle, game, effect->item_name,
                                       effect->arg0, 7);
        }
    }
}

static void eOtosiana_dw(eEC_Effect_c* effect, GAME* game) {
    // Nothing
}
