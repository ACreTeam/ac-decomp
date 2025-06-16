#include "ef_effect_control.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

static void eKPun_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKPun_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKPun_mv(eEC_Effect_c* effect, GAME* game);
static void eKPun_dw(eEC_Effect_c* effect, GAME* game);

extern u8 ef_pun01_0_int_i4[];
extern u8 ef_pun01_1_int_i4[];
extern u8 ef_pun01_2_int_i4[];
extern u8 ef_pun01_3_int_i4[];
extern u8 ef_pun01_4_int_i4[];
extern Gfx ef_pun01_00_modelT[];

static u8* eKPun_yuge_texture_table[] = {
    ef_pun01_0_int_i4, ef_pun01_1_int_i4, ef_pun01_2_int_i4, ef_pun01_3_int_i4, ef_pun01_4_int_i4,
};

eEC_PROFILE_c iam_ef_kpun = {
    // clang-format off
    &eKPun_init,
    &eKPun_ct,
    &eKPun_mv,
    &eKPun_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

xyz_t random_start_place_offset[10] = {
    {  3.0f, 0.0f,  4.0f },
    { -4.0f, 0.0f, -1.0f },
    {  1.0f, 0.0f,  1.0f },
    {  2.0f, 0.0f,  4.0f },
    { -2.0f, 0.0f,  2.0f },
    {  3.0f, 0.0f, -4.0f },
    {  2.0f, 0.0f,  4.0f },
    {  1.0f, 0.0f, -3.0f },
    { -2.0f, 0.0f,  1.0f },
    {  3.0f, 0.0f, -5.0f },
};

typedef struct {
    u8 tex0;
    u8 tex1;
    u8 l;
    u8 _03;
} eKPun_tex_c;

static eKPun_tex_c eKPun_texture_anime_idx[13] = {
    {0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00},
    {0x00, 0x01, 0x7F, 0x00},
    {0x01, 0x01, 0xFF, 0x00},
    {0x01, 0x02, 0x7F, 0x00},
    {0x02, 0x02, 0x00, 0x00},
    {0x02, 0x03, 0x7F, 0x00},
    {0x03, 0x03, 0xFF, 0x00},
    {0x03, 0x04, 0x7F, 0x00},
    {0x04, 0x04, 0x00, 0x00},
    {0x04, 0x04, 0x00, 0x00},
    {0x04, 0x04, 0x00, 0x00},
};

static u8 eKPun_prim_f_table[13] = {
    0x00, 0x00, 0x00, 0x7F, 0xFF, 0x7F, 0x00, 0x7F,
    0xFF, 0x7F, 0x00, 0x00, 0x00
};

// unmatched: 
static void eKPun_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    int rng = RANDOM(10);
    xyz_t sp1C = { 0.0f, 0.0f, 5.0f };
    
    pos.x += random_start_place_offset[rng].x;
    pos.y += 23.0f;
    pos.z += random_start_place_offset[rng].z;
    sMath_RotateY(&sp1C, SHORT2RAD_ANGLE2(angle));
    pos.x += sp1C.x;
    pos.y += sp1C.y;
    pos.z += sp1C.z;

    common_data.clip.effect_clip->make_effect_proc(eEC_EFFECT_KPUN, pos, NULL, game, NULL, item_name, prio, 0, 0);
}

static void eKPun_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->effect_specific[0] = common_data.clip.effect_clip->random_first_speed_proc(NULL, 3.0f, 14.0f, 0.0f);
    effect->offset.z = -6.0f;
    effect->timer = 0x1A;
    sAdo_OngenTrgStart(0x13E, &effect->position);
}

static void eKPun_mv(eEC_Effect_c* effect, GAME* game) {
    if ((s16) (0x1A - effect->timer) < 4) {
        effect->offset.y += 3.0f;
    }
}

static void eKPun_dw(eEC_Effect_c* effect, GAME* game) {
    s16 counter = 26 - effect->timer;
    s16 idx = CLAMP(counter >> 1, 0, 12);
    xyz_t* pos_p = &effect->position;
    xyz_t* scale_p = &effect->scale;
    xyz_t* offset_p = &effect->offset;
    GAME_PLAY* play = (GAME_PLAY*)game;
    int tex0;
    int tex1;
    u8 prim_f;
    u8 prim_gb;
    u8 prim_a;
    u8 env_gb;

    tex0 = eKPun_texture_anime_idx[idx].tex0;
    tex1 = eKPun_texture_anime_idx[idx].tex1;
    prim_f = eKPun_prim_f_table[idx];
    prim_gb = (int)eEC_CLIP->calc_adjust_proc(counter, 0, 8, 200.0f, 255.0f);
    prim_a = (int)eEC_CLIP->calc_adjust_proc(counter, 12, 26, 255.0f, 0.0f);
    env_gb = (int)eEC_CLIP->calc_adjust_proc(counter, 0, 8, 0.0f, 255.0f);

    if (counter <= 8) {
        static f32 scale_y_table[5] = { 0.0085f, 0.014450001530f, 0.0289000030f, 0.014450001530f, 0.0085f };
        
        effect->scale.y = scale_y_table[idx];
        effect->scale.x = 0.0085f;
    } else {
        effect->scale.x = eEC_CLIP->calc_adjust_proc(counter, 10, 26, 0.0085f, 0.017f);
        effect->scale.y = effect->scale.x;
    }

    OPEN_DISP(game->graph);
    _texture_z_light_fog_prim_xlu(game->graph);
    Matrix_translate(pos_p->x, pos_p->y, pos_p->z, 0);
    Matrix_mult(&play->billboard_matrix, 1);
    Matrix_RotateZ(effect->effect_specific[0], 1);
    Matrix_translate(offset_p->x, offset_p->y, offset_p->z, 1);
    Matrix_scale(scale_p->x, scale_p->y, scale_p->z, 1);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, eKPun_yuge_texture_table[tex0]);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_2_TXT_SEG, eKPun_yuge_texture_table[tex1]);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, prim_f, 255, prim_gb, prim_gb, prim_a);
    gDPSetEnvColor(NEXT_POLY_XLU_DISP, 255, env_gb, env_gb, 255);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_pun01_00_modelT);
    
    CLOSE_DISP(game->graph);
}