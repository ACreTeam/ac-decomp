#include "ef_effect_control.h"

#include "m_common_data.h"

static void eHanatiri_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eHanatiri_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eHanatiri_mv(eEC_Effect_c* effect, GAME* game);
static void eHanatiri_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_hanatiri = {
    // clang-format off
    &eHanatiri_init,
    &eHanatiri_ct,
    &eHanatiri_mv,
    &eHanatiri_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eHanatiri_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    (*eEC_CLIP->make_effect_proc)(eEC_EFFECT_HANATIRI, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eHanatiri_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    int i;

    if (effect->arg0 >= FLOWER_PANSIES0 && effect->arg0 <= FLOWER_TULIP2) {
        s16 flower_idx = effect->arg0 - FLOWER_PANSIES0;
        
        for (i = 0; i < 5; i++) {
            eEC_CLIP->effect_make_proc(eEC_EFFECT_HANABIRA, effect->position, effect->prio, 0, game, effect->item_name, flower_idx, 5);
        }
    }
    
    for (i = 0; i < 4; i++){
        eEC_CLIP->effect_make_proc(eEC_EFFECT_HANABIRA, effect->position, effect->prio, 0, game, effect->item_name, 9, 5);
    }
    
    effect->timer = 0;
}

static void eHanatiri_mv(eEC_Effect_c* effect, GAME* game) {
    // empty
}

static void eHanatiri_dw(eEC_Effect_c* effect, GAME* game) {
    // empty
}

