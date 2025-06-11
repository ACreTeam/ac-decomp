#include "ef_effect_control.h"

#include "m_common_data.h"

static void eNebo_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eNebo_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eNebo_mv(eEC_Effect_c* effect, GAME* game);
static void eNebo_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_neboke = {
    // clang-format off
    &eNebo_init,
    &eNebo_ct,
    &eNebo_mv,
    &eNebo_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eNebo_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_NEBOKE, pos, NULL, game, &angle, item_name, prio, 0, 0);
}

static void eNebo_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 112;
    effect->effect_specific[0] = *(s16*)ct_arg;
}

static void eNebo_mv(eEC_Effect_c* effect, GAME* game) {
    s16 timer;

    eEC_CLIP->set_continious_env_proc(effect, 112, 120);

    if (effect->state == eEC_STATE_NORMAL) {
        timer = 112 - effect->timer;
        if (timer == 16) {
            eEC_CLIP->effect_make_proc(eEC_EFFECT_NEBOKE_AKUBI, effect->position, effect->prio,
                                       effect->effect_specific[0], game, (u16)effect->item_name, 0, 0);
        } else if (timer == 44) {
            eEC_CLIP->effect_make_proc(eEC_EFFECT_NEBOKE_AKUBI, effect->position, effect->prio,
                                       effect->effect_specific[0], game, (u16)effect->item_name, 1, 0);
        }
    } else if (effect->state == eEC_STATE_CONTINUOUS) {
        timer = 120 - effect->timer;
        switch (timer) {
            case 46:
            case 74:
                eEC_CLIP->effect_make_proc(eEC_EFFECT_NEBOKE_AWA, effect->position, effect->prio,
                                           effect->effect_specific[0], game, (u16)effect->item_name, 1, 0);
        }
    }
}

static void eNebo_dw(eEC_Effect_c* effect, GAME* game) {
    return;
}
