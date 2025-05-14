#include "ef_effect_control.h"

#include "m_common_data.h"
#include "sys_math.h"

static void eIkigire_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eIkigire_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eIkigire_mv(eEC_Effect_c* effect, GAME* game);
static void eIkigire_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_ikigire = {
    // clang-format off
    &eIkigire_init,
    &eIkigire_ct,
    &eIkigire_mv,
    &eIkigire_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eIkigire_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    s16 _angle = angle;

    if (eEC_CLIP) {
        _angle += (s16)DEG2SHORT_ANGLE2(RANDOM2_F(90.0f));

        pos.x += sin_s(_angle) * 5.0f;
        pos.z += cos_s(_angle) * 5.0f;

        eEC_CLIP->effect_make_proc(eEC_EFFECT_DUST, pos, prio, _angle, game, item_name, 0, 0);
    }

    eEC_CLIP->make_effect_proc(eEC_EFFECT_IKIGIRE, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eIkigire_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 0;
}

static void eIkigire_mv(eEC_Effect_c* effect, GAME* game) {
    return;
}

static void eIkigire_dw(eEC_Effect_c* effect, GAME* game) {
    return;
}
