#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

extern Gfx ef_star01_00_modelT[];

static void eImpact_Star_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eImpact_Star_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eImpact_Star_mv(eEC_Effect_c* effect, GAME* game);
static void eImpact_Star_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_impact_star = {
    // clang-format off
    &eImpact_Star_init,
    &eImpact_Star_ct,
    &eImpact_Star_mv,
    &eImpact_Star_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eImpact_Star_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_IMPACT_STAR, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eImpact_Star_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    f32 mul;
    s16* angle_y_p = (s16*)ct_arg;
    
    if (effect->arg1 == 0) {
        s16 angle_y = *angle_y_p;
        s16 angle_x = DEG2SHORT_ANGLE2(-70.0f);
        
        mul = 6.0f + (f32)RANDOM_F(0.0f);
        angle_y += DEG2SHORT_ANGLE2(RANDOM_F(20.0f));
        angle_x += DEG2SHORT_ANGLE2(RANDOM_F(20.0f));
            
        effect->scale.x = 0.01f;
        effect->offset.x = 0.01f;
        effect->offset.y = 0.004f;
            
        effect->velocity.y = mul * cos_s(angle_x);
        effect->velocity.x = mul * sin_s(angle_x) * sin_s(angle_y);
        effect->velocity.z = mul * sin_s(angle_x) * cos_s(angle_y);
    } else {
        s16 angle_y = *angle_y_p + DEG2SHORT_ANGLE2(10.0f);
        s16 angle_x = DEG2SHORT_ANGLE2(-60.0f);
        
        mul = 6.0f + (f32)RANDOM_F(0.0f);
        angle_y += -DEG2SHORT_ANGLE2(RANDOM_F(20.0f));
        angle_x += -DEG2SHORT_ANGLE2(RANDOM_F(20.0f));
        
        effect->scale.x = 0.012f;
        effect->offset.x = 0.012f;
        effect->offset.y = 0.006f;

        effect->velocity.y = mul * cos_s(angle_x);
        effect->velocity.x = mul * sin_s(angle_x) * sin_s(angle_y);
        effect->velocity.z = mul * sin_s(angle_x) * cos_s(angle_y);
    }
    
    effect->effect_specific[0] = qrand();
    effect->timer = 40;
}

static void eImpact_Star_mv(eEC_Effect_c* effect, GAME* game) {
    xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
    xyz_t_add(&effect->position, &effect->velocity, &effect->position);

    effect->velocity.x *= sqrtf(0.85f);
    effect->velocity.y *= sqrtf(0.85f);
    effect->velocity.z *= sqrtf(0.85f);
}

static void eImpact_Star_dw(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    u8 alpha = (int)eEC_CLIP->calc_adjust_proc(effect->timer,0,10, 0.0f, 255.0f);
    
    effect->scale.x = eEC_CLIP->calc_adjust_proc(effect->timer, 26, 40, effect->offset.y, effect->offset.x);
    effect->scale.y= effect->scale.z= effect->scale.x;

    OPEN_DISP(game->graph);
    
    _texture_z_light_fog_prim_xlu (game->graph);
    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD); 
    Matrix_mult(&play->billboard_matrix, MTX_MULT);
    Matrix_RotateZ(effect->effect_specific[0], MTX_MULT);
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, MTX_MULT);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 100, alpha);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_star01_00_modelT);
    
    CLOSE_DISP(game->graph);
}
