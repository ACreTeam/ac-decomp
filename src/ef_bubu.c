#include "ef_effect_control.h"
#include "m_common_data.h"

static void eBubu_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eBubu_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eBubu_mv(eEC_Effect_c* effect, GAME* game);
static void eBubu_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_bubu = {
    // clang-format off
    &eBubu_init,
    &eBubu_ct,
    &eBubu_mv,
    &eBubu_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};
extern Gfx ef_peke01_00_modelT[];


static void eBubu_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {

    pos.y += 70.0f;
    eEC_CLIP->make_effect_proc(eEC_EFFECT_BUBU,pos,NULL,game,NULL,item_name,prio,0,0);
}

static void eBubu_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->scale.x = 0.015f;
    effect->scale.y = 0.015f;    
    effect->scale.z = 0.015f;
    sAdo_SysTrgStart(0x100A);
}

static void eBubu_mv(eEC_Effect_c* effect, GAME* game) {

}
static void eBubu_dw(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    GRAPH* graph = game->graph;

    eEC_CLIP->auto_matrix_xlu_proc(game, &effect->position, &effect->scale);

    OPEN_DISP(graph);

    gSPDisplayList(NEXT_POLY_XLU_DISP,ef_peke01_00_modelT);

    CLOSE_DISP(graph);
}
