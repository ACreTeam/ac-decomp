#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

extern u8 ef_pun01_0_int_i4[];
extern u8 ef_pun01_1_int_i4[];
extern u8 ef_pun01_2_int_i4[];
extern u8 ef_pun01_3_int_i4[];
extern u8 ef_pun01_4_int_i4[];
extern Gfx ef_pun01_00_modelT[];

static u8* ePunYuge_yuge_texture_table[] = {
    ef_pun01_0_int_i4, ef_pun01_1_int_i4, ef_pun01_2_int_i4, ef_pun01_3_int_i4, ef_pun01_4_int_i4,
};

static void ePunYuge_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void ePunYuge_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void ePunYuge_mv(eEC_Effect_c* effect, GAME* game);
static void ePunYuge_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_pun_yuge = {
    // clang-format off
    &ePunYuge_init,
    &ePunYuge_ct,
    &ePunYuge_mv,
    &ePunYuge_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void ePunYuge_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    pos.y += 23.0f;
    eEC_CLIP->make_effect_proc(eEC_EFFECT_PUN_YUGE, pos, NULL, game, &arg0, item_name, prio, 0, 0);
}

static void ePunYuge_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->effect_specific[1] = *(s16*)ct_arg;
    effect->effect_specific[0] = eEC_CLIP->random_first_speed_proc(NULL, 1.5f, 16.0f, 0.0f);
    effect->offset.z = 10.0f;
    effect->timer = 26.0f;
    sAdo_OngenTrgStart(NA_SE_PUN_YUGE, &effect->position);
}

static void ePunYuge_mv(eEC_Effect_c* effect, GAME* game) {
    s16 elapsed_time = 26 - effect->timer;

    if (elapsed_time < 4) {
        effect->offset.y += 1.5f;
    }
}

typedef struct pun_yuge_tex_anim_s {
    u8 tex0;
    u8 tex1;
    u8 prim_f;
    u8 unused;
} ePunYuge_tex_anim_c;

static ePunYuge_tex_anim_c ePunYuge_texture_anime_idx[] = {
    { 0, 0, 0, 0 },   { 0, 0, 0, 0 }, { 0, 0, 0, 0 },   { 0, 1, 127, 0 }, { 1, 1, 255, 0 },
    { 1, 2, 127, 0 }, { 2, 2, 0, 0 }, { 2, 3, 127, 0 }, { 3, 3, 255, 0 }, { 3, 4, 127, 0 },
    { 4, 4, 0, 0 },   { 4, 4, 0, 0 }, { 4, 4, 0, 0 },
};

static u8 ePunYuge_prim_f_table[] = {
    0, 0, 0, 127, 255, 127, 0, 127, 255, 127, 0, 0, 0,
};

static void ePunYuge_dw(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    int frame;
    s16 time_elapsed = 26 - effect->timer;
    int anime_idx0;
    int anime_idx1;
    int prim_f;
    int prim_gb;
    int prim_a;
    int env_gb;

    frame = (s16)CLAMP(time_elapsed >> 1, 0, 12);
    anime_idx0 = ePunYuge_texture_anime_idx[frame].tex0;
    anime_idx1 = ePunYuge_texture_anime_idx[frame].tex1;
    prim_f = ePunYuge_prim_f_table[frame];
    prim_gb = (u8)eEC_CLIP->calc_adjust_proc(time_elapsed, 0, 8, 200.0f, 255.0f);
    prim_a = (u8)eEC_CLIP->calc_adjust_proc(time_elapsed, 12, 26, 255.0f, 0.0f);
    env_gb = (u8)eEC_CLIP->calc_adjust_proc(time_elapsed, 0, 8, 0.0f, 255.0f);

    if (frame <= 4) {
        f32 scale_y[5];

        scale_y[0] = 0.00595f;
        scale_y[1] = 0.00833f;
        scale_y[2] = 0.014161f;
        scale_y[3] = 0.00833f;
        scale_y[4] = 0.00595f;
        effect->scale.y = scale_y[frame];
        effect->scale.x = 0.00595f;
    } else {
        effect->scale.x = eEC_CLIP->calc_adjust_proc(time_elapsed, 10, 26, 0.00595f, 0.0119f);
        effect->scale.y = effect->scale.x;
    }

    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);
    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_mult(&play->billboard_matrix, MTX_MULT);
    Matrix_RotateZ(effect->effect_specific[0], MTX_MULT);
    Matrix_translate(effect->offset.x, effect->offset.y, effect->offset.z, MTX_MULT);
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, MTX_MULT);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8, ePunYuge_yuge_texture_table[anime_idx0]);
    gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_9, ePunYuge_yuge_texture_table[anime_idx1]);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, (u8)prim_f, 255, (u8)prim_gb, (u8)prim_gb, (u8)prim_a);
    gDPSetEnvColor(NEXT_POLY_XLU_DISP, 255, (u8)env_gb, (u8)env_gb, 255);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_pun01_00_modelT);

    CLOSE_DISP(game->graph);
}
