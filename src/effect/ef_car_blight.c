#include "ef_effect_control.h"
#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "m_debug_mode.h"

static void eCar_Blight_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eCar_Blight_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eCar_Blight_mv(eEC_Effect_c* effect, GAME* game);
static void eCar_Blight_dw(eEC_Effect_c* effect, GAME* game);

xyz_t light_make_pos[] = {
    {0.0f,30.0f,0.0f},
    {20.0f,20.0f,0.0f},
    {40.0f,10.0f,0.0f},
    {-10.0f, 60.0f, 0.0f},
    {10.0f,50.0f,0.0f},
    {30.0f,40.0f,0.0f},
    {50.0f,30.0f,0.0f},
    {0.0f,80.0f,0.0f},
    {20.0f,70.0f,0.0f},
    {40.0f, 60.0f,0.0f},
    {60.0f,50.0f,0.0f},
    {30.0f,90.0f,0.0f},
    {50.0f,80.0f,0.0f},
    {70.0f,70.0f,0.0f},
    {90.0f,60.0f,0.0f},
    {100.0f, 80.0f,0.0f},
};

eEC_PROFILE_c iam_ef_car_blight = {
    // clang-format off
    &eCar_Blight_init,
    &eCar_Blight_ct,
    &eCar_Blight_mv,
    &eCar_Blight_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};


extern Gfx ef_car01_modelT[];

static void eCar_Blight_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_CAR_BLIGHT, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eCar_Blight_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 42;
    effect->scale.x = 0.01f;
    effect->scale.y = 0.01f;    
    effect->scale.z = 0.01f;
    effect->effect_specific[0] = 0;
}

static int eCar_Blight_light_control(eEC_Effect_c* effect){
    int base = RANDOM(16.0f); 
    int i;
    int specific = (u8)effect->effect_specific[0];
    int check = effect->effect_specific[0];

    while (specific == 0){
        i = 1 << base;

        if((i & check)){
            if(base > 15){
                base = 0;
            }
            else{
                base++;
            }
        }
        else {
            effect->effect_specific[0] &= i;
            return base;
        }
    };

    return 0;

}

static void eCar_Blight_mv(eEC_Effect_c* effect, GAME* game) {
    if(!(effect->timer & 3)){
        xyz_t pos = light_make_pos[eCar_Blight_light_control(effect)];
        pos.x += (effect->position.x - 50.0f);
        pos.y += (effect->position.y);
        pos.z += (effect->position.z + 50.0f);
        eEC_CLIP->effect_make_proc(eEC_EFFECT_CAR_LIGHT, pos, effect->prio,0, game, effect->item_name,0,0);
    }
}

static void eCar_Blight_dw(eEC_Effect_c* effect, GAME* game) {
    GRAPH* graph;
    GAME_PLAY* play;
    f32 scaleFact;
    Gfx* gfx;
    int timer;
    
    play = (GAME_PLAY*)game;
    timer =  42 - effect->timer;

    if(effect->arg0 == 0){
        graph = game->graph;

        _texture_z_light_fog_prim_xlu(graph); 
        Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);

        scaleFact = 1.0f + (0.01f * (f32)(int)GETREG(MYKREG,27));
        Matrix_scale(effect->scale.x * scaleFact, effect->scale.y * scaleFact, effect->scale.z * scaleFact, MTX_MULT);
        Setpos_HiliteReflect_xlu_init(&effect->position, play);

        gfx = two_tex_scroll_dolphin(game->graph,0, timer * 3, timer * 7, 16, 16, 1,timer * 3, timer * -7, 16,16);

        if(gfx != NULL){
            OPEN_DISP(graph);
            gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8, gfx);
            
            gfx = two_tex_scroll_dolphin(game->graph,0, timer * 3, timer * 3, 16, 16, 1,timer * 3, timer * -7, 16,16);
            if(gfx != NULL){
                gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_9, gfx); 

                gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            
                gSPDisplayList(NEXT_POLY_XLU_DISP, ef_car01_modelT);
            }

            CLOSE_DISP(graph);
        }
    }
}
