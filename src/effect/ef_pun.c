#include "ef_effect_control.h"

#include "m_common_data.h"

static void ePun_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void ePun_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void ePun_mv(eEC_Effect_c* effect, GAME* game);
static void ePun_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_pun = {
    // clang-format off
    &ePun_init,
    &ePun_ct,
    &ePun_mv,
    &ePun_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void ePun_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_PUN, pos, NULL, game, &angle, item_name, prio, 0, 0);
}

static void ePun_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    s16 var = *(s16*)ct_arg;
    effect->effect_specific[0] = var;
    effect->timer = 24;
}

static void ePun_mv(eEC_Effect_c* effect, GAME* game) {
    eEC_CLIP->set_continious_env_proc(effect, 24, 44);
    
    if (effect->state == eEC_STATE_CONTINUOUS) {
        s16 timer_left = 44 - effect->timer;
        
        if (timer_left == 0) {
            effect->effect_specific[1] = RANDOM(100) & 1;
        }   
            
        if (timer_left == 8) {
            eEC_CLIP->effect_make_proc(eEC_EFFECT_PUN_YUGE, effect->position, effect->prio, effect->effect_specific[0], game, (u16)effect->item_name, effect->effect_specific[1], 0);
            
            effect->effect_specific[1] = ++effect->effect_specific[1] & 1;
            
            eEC_CLIP->effect_make_proc(eEC_EFFECT_PUN_SEKIMEN, effect->position, effect->prio, effect->effect_specific[0], game, (u16)effect->item_name, 0, 0);
        }
    }
}

static void ePun_dw(eEC_Effect_c* effect, GAME* game) {
    
}
