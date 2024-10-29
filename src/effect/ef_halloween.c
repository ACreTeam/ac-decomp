#include "ef_effect_control.h"

#include "m_common_data.h"

static void eHalloween_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eHalloween_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eHalloween_mv(eEC_Effect_c* effect, GAME* game);
static void eHalloween_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_halloween = {
    // clang-format off
    &eHalloween_init,
    &eHalloween_ct,
    &eHalloween_mv,
    &eHalloween_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eHalloween_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
   (*eEC_CLIP->make_effect_proc)(eEC_EFFECT_HALLOWEEN, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eHalloween_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 0x28;
    effect->effect_specific[0] = 0;
    sAdo_OngenTrgStart(0x107, &effect->position);
}

static void eHalloween_mv(eEC_Effect_c* effect, GAME* game) {
    if (effect->effect_specific[0] == 4) {
        s16 rnd_angle = qrand();
        xyz_t pos = effect->position;
        
        pos.x += 18.0f * sin_s(rnd_angle);
        pos.y += -25.0f + RANDOM_F(30.0f);
        pos.z += 5.0f + (18.0f * cos_s(rnd_angle));
        effect->effect_specific[0] = 0;
        eEC_CLIP->effect_make_proc(eEC_EFFECT_HALLOWEEN_SMOKE, pos, effect->prio, rnd_angle, game, effect->item_name, 0, 0);
    }
    
    effect->effect_specific[0]++;
}

static void eHalloween_dw(eEC_Effect_c* effect, GAME* game) {
    // empty
}
