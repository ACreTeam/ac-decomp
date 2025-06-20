#include "ef_effect_control.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

extern Gfx ef_amimizu01_00_modelT[];

static void eAmi_Mizu_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    if(arg0 != 1){
        pos.x += (-13.0f * sin_s(angle));
        pos.z += (-13.0f * cos_s(angle));
        pos.y += (2.0f);
    }
    else{
        pos.x += (10.0f * sin_s(angle));
        pos.z += (10.0f * cos_s(angle));
        pos.y += (2.0f);  
    }

    eEC_CLIP->make_effect_proc(eEC_EFFECT_AMI_MIZU,pos,NULL,game,NULL,item_name,prio, arg0,arg1);
}

static void eAmi_Mizu_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 10;
    if ( effect->arg0 != 2) {
        effect->offset.x = 0.0126f;
    }
    else{
        effect->offset.x = 0.01f + (0.02f * (0.01f * effect->arg1));
    }
}

static void eAmi_Mizu_mv(eEC_Effect_c* effect, GAME* game) {
    f32 adjust;

    if (effect->timer == 10) {
        f32 off_x = effect->offset.x;
        effect->scale.z = off_x;
        effect->scale.y = off_x;
        effect->scale.x = off_x;
    }
    else{
        adjust = eEC_CLIP->calc_adjust_proc(effect->timer,0, 8, 1.3f * effect->offset.x, 1.1f * effect->offset.x);
        effect->scale.z = adjust;
        effect->scale.x = adjust;
        effect->scale.y =  eEC_CLIP->calc_adjust_proc(effect->timer, 0, 8, 0.5f * effect->offset.x, 1.2f * effect->offset.x);
    }
}


static void eAmi_Mizu_dw(eEC_Effect_c* effect, GAME* game) {
    int alpha = (u8)eEC_CLIP->calc_adjust_proc(effect->timer, 0, 6, 50.0f, 155.0f);
    GRAPH* graph = game->graph;
    
    _texture_z_light_fog_prim_xlu(graph);

    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, MTX_MULT);
    
    OPEN_DISP(graph);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDPSetPrimColor(NEXT_POLY_XLU_DISP,0, 255, 0, 255, 255, alpha);
    gDPSetEnvColor(NEXT_POLY_XLU_DISP,255, 255, 255, 255);
    
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_amimizu01_00_modelT);
    CLOSE_DISP(graph);
}

eEC_PROFILE_c iam_ef_ami_mizu = {
    // clang-format off
    &eAmi_Mizu_init,
    &eAmi_Mizu_ct,
    &eAmi_Mizu_mv,
    &eAmi_Mizu_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};
