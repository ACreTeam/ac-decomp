#include "ef_effect_control.h"
#include "m_common_data.h"

static void eCar_Light_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eCar_Light_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eCar_Light_mv(eEC_Effect_c* effect, GAME* game);
static void eCar_Light_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_car_light = {
    // clang-format off
    &eCar_Light_init,
    &eCar_Light_ct,
    &eCar_Light_mv,
    &eCar_Light_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};
extern Gfx ef_carhosi01_00_modelT[];

static void eCar_Light_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1){
    eEC_CLIP->make_effect_proc(eEC_EFFECT_CAR_LIGHT, pos, NULL, game, NULL, item_name, prio, arg0, arg1);

};

static void eCar_Light_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg){
    effect->timer = 24;
};

static void eCar_Light_mv(eEC_Effect_c* effect, GAME* game){

    if(effect->timer > 12){
        effect->scale.x = eEC_CLIP->calc_adjust_proc(effect->timer, 12,24, 0.015f, 0.0f);
    }
    else{
        effect->scale.x = eEC_CLIP->calc_adjust_proc(effect->timer, 0,12, 0.0f, 0.015f);
    }

    effect->scale.y = effect->scale.z = effect->scale.x;
};

static void eCar_Light_dw(eEC_Effect_c* effect, GAME* game){
    
    OPEN_DISP(game->graph);
    eEC_CLIP->auto_matrix_xlu_proc(game, &effect->position, &effect->scale);

    gDPSetEnvColor(NEXT_POLY_XLU_DISP, 255, 255, 0,255);

    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_carhosi01_00_modelT);

    CLOSE_DISP(game->graph);
};
