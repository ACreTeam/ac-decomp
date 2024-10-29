#include "ef_effect_control.h"

#include "m_common_data.h"

#define eHanabiDummy_TIMER 80
#define eHanabiDummy_MIN_POWER 0.0f
#define eHanabiDummy_MAX_POWER 2.0f
#define eHanabiDummy_MAX_DIST (mFI_UNIT_BASE_SIZE_F * 12)

enum {
    eHanabiDummy_TYPE0,
    eHanabiDummy_TYPE1,
    eHanabiDummy_TYPE2,
    eHanabiDummy_TYPE3,
    eHanabiDummy_TYPE4,
    eHanabiDummy_TYPE5,

    eHanabiDummy_TYPE_NUM
};

#define eHanabiDummy_TYPE_ARG (effect->effect_specific[0])

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
    effect->timer = eHanabiDummy_TIMER;
    eHanabiDummy_TYPE_ARG = RANDOM(eHanabiDummy_TYPE_NUM);
}

static void eHanabiDummy_mv(eEC_Effect_c* effect, GAME* game) {
    rgba_t light_color;
    s16 frames_passed = eHanabiDummy_TIMER - effect->timer;

    if (frames_passed == 10) {
        static rgba_t dummy_light[eHanabiDummy_TYPE_NUM] = {
            { 50, 30, 20, 255 }, { 20, 60, 20, 255 }, { 40, 10, 60, 255 },
            { 40, 20, 20, 255 }, { 20, 40, 20, 255 }, { 60, 60, 30, 255 },
        };

        eEC_CLIP->decide_light_power_proc(&light_color, dummy_light[eHanabiDummy_TYPE_ARG], effect->position, game,
                                          eHanabiDummy_MAX_POWER, eHanabiDummy_MIN_POWER, eHanabiDummy_MAX_DIST);
        if (effect->arg0 != 0) {
            light_color.r = light_color.r * eHanabiDummy_MAX_POWER;
            light_color.g = light_color.g * eHanabiDummy_MAX_POWER;
            light_color.b = light_color.b * eHanabiDummy_MAX_POWER;
        }

        eEC_CLIP->regist_effect_light(light_color, 20, 50, TRUE);
    }

    if (frames_passed == 72) {
        xyz_t pos = effect->position;
        u16 sfx_no;

        pos.y += 200.0f;

        switch (eHanabiDummy_TYPE_ARG) {
            case eHanabiDummy_TYPE0:
            case eHanabiDummy_TYPE1:
                sfx_no = NA_SE_HANABI0;
                break;
            case eHanabiDummy_TYPE2:
                sfx_no = NA_SE_HANABI1;
                break;
            case eHanabiDummy_TYPE3:
            case eHanabiDummy_TYPE4:
                sfx_no = NA_SE_HANABI2;
                break;
            case eHanabiDummy_TYPE5:
                sfx_no = NA_SE_HANABI3;
                break;
            default:
                sfx_no = NA_SE_HANABI0;
                break;
        }

        sAdo_OngenTrgStart(sfx_no, &pos);
    }
}

static void eHanabiDummy_dw(eEC_Effect_c* effect, GAME* game) {
    // empty
}
