#include "ef_effect_control.h"
#include "m_common_data.h"
#include "m_rcp.h"

extern Gfx ef_w_yabu01_00_modelT[];

static void eBushYuki_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eBushYuki_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eBushYuki_mv(eEC_Effect_c* effect, GAME* game);
static void eBushYuki_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_bush_yuki = {
    // clang-format off
    &eBushYuki_init,
    &eBushYuki_ct,
    &eBushYuki_mv,
    &eBushYuki_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eBushYuki_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_BUSH_YUKI, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eBushYuki_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {

    f32 y = 1.5f + (RANDOM_F(1.5f));
    f32 initialPos = -3.0f + (6.0f * fqrand());
    effect->timer = 60;
    
    effect->position.x += initialPos; 
    effect->position.y += initialPos;

    eEC_CLIP->random_first_speed_proc(&effect->velocity,y,45.0f,45.0f);

    if (effect->arg1 == 1) {
        effect->velocity.x = RANDOM2_F(2.0f);
        effect->velocity.y = fqrand();
        effect->velocity.z = fqrand();
    }
    effect->scale.x = 0.005f;
    effect->scale.y = 0.005f;
    effect->scale.z = 0.005f;
    effect->acceleration.x = 0.0f;
    effect->acceleration.y = -0.125f;
    effect->acceleration.z = 0.0f;
}

void eBushYuki_mv(eEC_Effect_c* effect, GAME* game) {
    xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
    xyz_t_add(&effect->position, &effect->velocity, &effect->position);
}

static void eBushYuki_dw(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    GRAPH* graph;

    u8 alpha = (int)eEC_CLIP->calc_adjust_proc(60 - effect->timer, 32, 60, 200.0f, 0.0f);
    graph = game->graph;
    _texture_z_light_fog_prim_xlu(game->graph);
    eEC_CLIP->auto_matrix_xlu_proc(game, &effect->position, &effect->scale);


    
    OPEN_DISP(graph);

    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 128, 40, 40, 40, alpha);

    gSPDisplayList(NEXT_POLY_XLU_DISP,ef_w_yabu01_00_modelT);

    CLOSE_DISP(graph);

}
