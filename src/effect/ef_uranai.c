#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"

extern Gfx ef_uranai01_00_modelT[];
extern EVW_ANIME_DATA ef_uranai01_00_evw_anime;

static void eUranai_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eUranai_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eUranai_mv(eEC_Effect_c* effect, GAME* game);
static void eUranai_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_uranai = {
    // clang-format off
    &eUranai_init,
    &eUranai_ct,
    &eUranai_mv,
    &eUranai_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eUranai_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_URANAI, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eUranai_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->scale.x = 0.01f;
    effect->scale.y = 0.01f;
    effect->scale.z = 0.01f;
    effect->offset = ZeroVec;
    effect->timer = 80;

    sAdo_OngenTrgStart(NA_SE_AXE_BALL_HIT, &effect->position);
}

static void eUranai_mv(eEC_Effect_c* effect, GAME* game) {
    if (effect->timer >= 70) {
        effect->scale.x = 0.01f;
        effect->scale.y = 0.01f;
        effect->scale.z = 0.01f;
    } else {
        effect->scale.x = eEC_CLIP->calc_adjust_proc(effect->timer, 0, 70, 0.0139999999f, 0.01f);
        effect->scale.y = eEC_CLIP->calc_adjust_proc(effect->timer, 0, 70, 0.012f, 0.01f);
        effect->scale.z = 0.01f;
    }
}

static void eUranai_dw(eEC_Effect_c* effect, GAME* game) {
    u8 r, g, b, a;
    GRAPH* graph;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (effect->timer >= 70) {
        r = 255;
        g = 0;
        b = 100;
        a = (s8)eEC_CLIP->calc_adjust_proc(effect->timer, 70, 80, 255.0f, 0.0f);
    } else {
        r = 255;
        g = 0;
        b = (s8)eEC_CLIP->calc_adjust_proc(effect->timer, 0, 70, 255.0f, 100.0f);
        a = (s8)eEC_CLIP->calc_adjust_proc(effect->timer, 0, 70, 0.0f, 255.0f);
    }

    graph = game->graph;
    _texture_z_light_fog_prim_xlu(graph);
    Evw_Anime_Set(play, &ef_uranai01_00_evw_anime);

    OPEN_DISP(graph);

    eEC_CLIP->auto_matrix_xlu_offset_proc(game, &effect->position, &effect->scale, &effect->offset);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, r, g, b, a);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_uranai01_00_modelT);

    CLOSE_DISP(graph);
}
