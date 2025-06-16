#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

extern u8 ef_mitiyuge01_0_int_i4[];
extern u8 ef_motiyuge01_1_int_i4[];
extern u8 ef_motiyuge01_2_int_i4[];

static u8* eMotiyuge_yuge_texture_table[] = {
    ef_mitiyuge01_0_int_i4, ef_motiyuge01_1_int_i4, ef_motiyuge01_2_int_i4,
};

static void eMotiyuge_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eMotiyuge_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eMotiyuge_mv(eEC_Effect_c* effect, GAME* game);
static void eMotiyuge_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_motiyuge = {
    // clang-format off
    &eMotiyuge_init,
    &eMotiyuge_ct,
    &eMotiyuge_mv,
    &eMotiyuge_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eMotiyuge_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_MOTIYUGE, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eMotiyuge_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->effect_specific[0] = DEG2SHORT_ANGLE2(RANDOM2_F(40.0f));
    effect->effect_specific[1] = 0;
    effect->scale.x = 0.0006f;
    effect->scale.y = 0.0006f;
    effect->scale.z = 0.0006f;
    effect->timer = 30;
}

static void eMotiyuge_mv(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (effect->timer >= 24) {
        effect->scale.x = eEC_CLIP->calc_adjust_proc(effect->timer, 24, 30, 0.003f, 0.0006f);
        effect->scale.y = eEC_CLIP->calc_adjust_proc(effect->timer, 24, 30, 0.009000001f, 0.0006f);
    } else {
        effect->scale.x = eEC_CLIP->calc_adjust_proc(effect->timer, 0, 24, 0.0045000003, 0.003f);
        effect->scale.y = eEC_CLIP->calc_adjust_proc(effect->timer, 0, 24, 0.0045000003f, 0.009000001f);
    }

    if ((play->game_frame & 3) == 0) {
        if (effect->effect_specific[1] >= 2) {
            effect->effect_specific[1] = 0;
        } else {
            effect->effect_specific[1]++;
        }
    }
}

extern Gfx ef_motiyuge01_00_modelT[];

static void eMotiyuge_dw(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    u8* tex_p = eMotiyuge_yuge_texture_table[effect->effect_specific[1]];
    u8 a = (int)eEC_CLIP->calc_adjust_proc(effect->timer, 0, 16, 0.0f, 100.0f);

    OPEN_DISP(game->graph);
    
    _texture_z_light_fog_prim_xlu(game->graph);
    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, 0);
    Matrix_mult(&play->billboard_matrix, 1);
    Matrix_RotateZ(effect->effect_specific[0], 1);
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, 1);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, tex_p);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 255, a);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_motiyuge01_00_modelT);

    CLOSE_DISP(game->graph);
}
