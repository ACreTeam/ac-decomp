#include "ef_effect_control.h"

#include "m_common_data.h"
#include "sys_matrix.h"

static void eKasamizu_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKasamizu_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKasamizu_mv(eEC_Effect_c* effect, GAME* game);
static void eKasamizu_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_kasamizu = {
    // clang-format off
    &eKasamizu_init,
    &eKasamizu_ct,
    &eKasamizu_mv,
    &eKasamizu_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eKasamizu_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_KASAMIZU, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eKasamizu_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    static xyz_t base_offset = {0, 45.0f, -20.0f};
    xyz_t pos;
    s16 angle = *(s16*)ct_arg;
    Matrix_RotateY(angle, MTX_LOAD);
    Matrix_Position(&base_offset, &pos);
    xyz_t_add(&effect->position, &pos, &effect->position);
    effect->effect_specific[0] = angle;
    effect->timer = 24;
}

static void eKasamizu_mv(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    if (eEC_CLIP != (eEC_EffectControl_Clip_c*)0) {
        int mEnv_NowWeather();
        if (mEnv_NowWeather() == mEnv_WEATHER_RAIN && play->game_frame & 1) {
            xyz_t pos = effect->position;
            eEC_CLIP->effect_make_proc(eEC_EFFECT_KASAMIZUTAMA, pos, effect->prio, effect->effect_specific[0], game,
                                       effect->item_name, 0, 0);
        }
    }
}

static void eKasamizu_dw(eEC_Effect_c* effect, GAME* game) {
    // Nothing
}
