#include "ef_effect_control.h"

#include "m_common_data.h"

static void eHanabiDummy_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eHanabiDummy_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eHanabiDummy_mv(eEC_Effect_c* effect, GAME* game);
static void eHanabiDummy_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_hanabi_dummy = {
    // clang-format off
    &eHanabiDummy_init,
    &eHanabiDummy_ct,
    &eHanabiDummy_mv,
    &eHanabiDummy_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static void eHanabiDummy_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    (*eEC_CLIP->make_effect_proc)(eEC_EFFECT_HANABI_DUMMY, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eHanabiDummy_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 0x50;
    effect->effect_specific[0] = RANDOM(6);
}

static void eHanabiDummy_mv(eEC_Effect_c* effect, GAME* game) {
    rgba_t light_color;
    s16 frames_passed = 80 - effect->timer;
    
    if (frames_passed == 10) {
        static rgba_t dummy_light[] = {
            { 50, 30, 20, 255 },
            { 20, 60, 20, 255 },
            { 40, 10, 60, 255 },
            { 40, 20, 20, 255 },
            { 20, 40, 20, 255 },
            { 60, 60, 30, 255 },
        };
        
        eEC_CLIP->decide_light_power_proc(&light_color, dummy_light[effect->effect_specific[0]], effect->position, game, 2.0f, 0.0f, 480.0f);
        if (effect->arg0 != 0) {
            light_color.r = light_color.r * 2.0f;
            light_color.g = light_color.g * 2.0f;
            light_color.b = light_color.b * 2.0f;
        }
        
        eEC_CLIP->regist_effect_light(light_color, 20, 50, TRUE);
    }
    if (frames_passed == 72) {
        xyz_t pos = effect->position;
        u16 sfx_no;

        pos.y += 200.0f;
        
        switch (effect->effect_specific[0]) {
            case 0:
            case 1:
                sfx_no = 0x210F;
                break;
            case 2:
                sfx_no = 0x2110;
                break;
            case 3:
            case 4:
                sfx_no = 0x2111;
                break;
            case 5:
                sfx_no = 0x2112;
                break;
            default:
                sfx_no = 0x210F;
                break;
        }
        
        sAdo_OngenTrgStart(sfx_no, &pos);
    }
}

static void eHanabiDummy_dw(eEC_Effect_c* effect, GAME* game) {
    // empty
}