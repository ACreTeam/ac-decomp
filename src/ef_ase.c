#include "ef_effect_control.h"
#include "m_common_data.h"

static void eAS_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eAS_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eAS_mv(eEC_Effect_c* effect, GAME* game);
static void eAS_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_ase = {
    // clang-format off
    &eAS_init,
    &eAS_ct,
    &eAS_mv,
    &eAS_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};
static void eAS_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    xyz_t offs;

    offs.x = 0.0f;
    offs.y = 15.0f;
    offs.z = 0.0f;
    eEC_CLIP->make_effect_proc(eEC_EFFECT_ASE,pos,&offs,game,NULL,item_name,prio,0,0);
}

static void eAS_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 26;
}

static void eAS_mv(eEC_Effect_c* effect, GAME* game) {
    int prio;
    int name;   
    GAME_PLAY* play = (GAME_PLAY*)game;
  
    name = effect->item_name;
    prio = effect->prio;
    eEC_CLIP->set_continious_env_proc(effect,26,52);

    if((eEC_CLIP != NULL) && (effect->timer & 1)){
        eEC_CLIP->effect_make_proc(eEC_EFFECT_ASE_CH,effect->position,prio,0,&play->game,name,0,0);
    }
}

static void eAS_dw(eEC_Effect_c* effect, GAME* game) {

} 