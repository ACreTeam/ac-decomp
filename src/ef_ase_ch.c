#include "ef_effect_control.h"
#include "m_common_data.h"

static void eASC_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eASC_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eASC_mv(eEC_Effect_c* effect, GAME* game);
static void eASC_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_ase_ch = {
    // clang-format off
    &eASC_init,
    &eASC_ct,
    &eASC_mv,
    &eASC_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};
extern Gfx ef_ase01_00_modelT[];

static f32 eASC_scale_table[] = {
    0.00027000002f, 0.00027000002f, 0.00027000002f, 0.00054000004f, 0.0010800001f,0.0016200001f,
    0.0021600001f,0.0027f,0.00135f,0.00054000004f,
};

static void eASC_DecideASCeDirect(xyz_t* vec){
    eEC_CLIP->random_first_speed_proc(vec,2.7f, 180.0f, 0.0f);
} 

static void eASC_SetAseGravity(xyz_t* acc) {
    acc->x = 0.0f;
    acc->y = -0.057499997f;
    acc->z = 0.0f;
}

static void eASC_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_ASE_CH,pos,NULL,game,NULL,item_name,prio,0,0);
}

static void eASC_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 20;
    eASC_DecideASCeDirect(&effect->velocity);
    eASC_SetAseGravity(&effect->acceleration);
    effect->scale.x = 0.0027f;
    effect->scale.y = 0.0027f;   
    effect->scale.z = 0.0027f;

}

static void eASC_mv(eEC_Effect_c* effect, GAME* game) {
    xyz_t_add(&effect->velocity,&effect->acceleration,&effect->velocity);
    xyz_t_add(&effect->position,&effect->velocity,&effect->position);
}

static void eASC_dw(eEC_Effect_c* effect, GAME* game) {
    xyz_t* pos = &effect->position;
    xyz_t* scale = &effect->scale;

    s16 val = (20 - effect->timer) >> 1;
    s16 idx = CLAMP(val, 0, 10);
    GRAPH* graph = game->graph;

    effect->scale.x = eASC_scale_table[idx];
    effect->scale.y = eASC_scale_table[idx]; 
    effect->scale.z = eASC_scale_table[idx];
    
    OPEN_DISP(game->graph);
    
    eEC_CLIP->auto_matrix_xlu_proc(game, pos, scale); 
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_ase01_00_modelT);

    CLOSE_DISP(game->graph);
}
