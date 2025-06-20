#include "ef_effect_control.h"
#include "evw_anime.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"


extern Gfx ef_anahikari01_01_modelT[];
extern Gfx ef_anahikari01_02_modelT[];

static Gfx* ef_anahikari_model_tbl[] = {
    ef_anahikari01_01_modelT,ef_anahikari01_02_modelT, 
};

extern EVW_ANIME_DATA ef_anahikari01_01_evw_anime;
extern EVW_ANIME_DATA ef_anahikari01_02_evw_anime;

static EVW_ANIME_DATA* ef_anahikari_anime_tbl[] = {
    &ef_anahikari01_01_evw_anime,&ef_anahikari01_02_evw_anime,
};

static void eAnahikari_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    pos.z += 4.0f;
    eEC_CLIP->make_effect_proc(eEC_EFFECT_ANAHIKARI,pos,NULL,game,NULL,item_name,prio, arg0,arg1);
}

static void eAnahikari_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 60;
    if(effect->arg0 == 0){
        effect->scale.z = 0.03f;
        effect->scale.y = 0.03f;
        effect->scale.x = 0.03f;
    }
    else{
        effect->scale.z = 0.037f;
        effect->scale.y = 0.037f;
        effect->scale.x = 0.037f;
    }
}

static void eAnahikari_mv(eEC_Effect_c* effect, GAME* game) {
    eEC_CLIP->set_continious_env_proc(effect,60,120);
} 

static void eAnahikari_dw(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play;
    int idx;
    u8 alpha;
    
    idx = effect->arg0;
    play = (GAME_PLAY*)game;

    if (mEv_CheckTitleDemo() != mEv_TITLEDEMO_STAFFROLL) {
        if (effect->state == eEC_STATE_NORMAL) {
            alpha = (int)eEC_CLIP->calc_adjust_proc(effect->timer, 0, 60, 200.0f, 0.0f);
        } else if (effect->state == eEC_STATE_FINISHED) {
            alpha = (int)eEC_CLIP->calc_adjust_proc(effect->timer, 0, 60, 0.0f, 200.0f);
        } else {
            alpha = 200;
        }

        OPEN_DISP(game->graph);
        
        _texture_z_light_fog_prim_xlu(game->graph);
        Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
        Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, MTX_MULT);
        Evw_Anime_Set(play, ef_anahikari_anime_tbl[idx]);

        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 255, alpha);
        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_anahikari_model_tbl[idx]);

        CLOSE_DISP(game->graph);
    }
}

eEC_PROFILE_c iam_ef_anahikari = {
    // clang-format off
    &eAnahikari_init,
    &eAnahikari_ct,
    &eAnahikari_mv,
    &eAnahikari_dw,
    60,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};
