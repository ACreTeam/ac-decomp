#include "ef_effect_control.h"
#include "m_common_data.h"
#include "m_debug.h"

// Furo Yuge == Bath Steam

#define EFFECT_STAGE1 41
#define EFFECT_FADEOUT 3
#define EFFECT_LIFETIME (EFFECT_STAGE1 + EFFECT_FADEOUT)

static void eFuro_Yuge_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eFuro_Yuge_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eFuro_Yuge_mv(eEC_Effect_c* effect, GAME* game);
static void eFuro_Yuge_dw(eEC_Effect_c* effect, GAME* game);

// clang-format off

extern Gfx ef_dust01_0[], ef_dust01_1[], ef_dust01_2[], ef_dust01_3[], ef_dust01_modelT[];

Gfx* eFuro_Yuge_texture_table[] = { 
    ef_dust01_0, 
    ef_dust01_1, 
    ef_dust01_2, 
    ef_dust01_3 
};

eEC_PROFILE_c iam_ef_furo_yuge = {
    &eFuro_Yuge_init,
    &eFuro_Yuge_ct,
    &eFuro_Yuge_mv,
    &eFuro_Yuge_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
};

u8 eFuro_Yuge_2tile_texture_idx[][2] = {
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 0 },
    { 0, 1 },
    { 0, 1 },
    { 0, 1 },
    { 1, 1 },
    { 1, 2 },
    { 1, 2 },
    { 1, 2 },
    { 2, 2 },
    { 2, 3 },
    { 2, 3 },
    { 2, 3 },
    { 3, 3 },
    { 3, 3 },
    { 3, 3 },
    { 3, 3 },
    { 3, 3 }
};

u8 eFuro_Yuge_prim_f[] = { 
    0,
    0,
    0,
    0,
    0,
    0,
    64,
    128,
    192,
    0,
    64,
    128,
    192,
    0,
    64,
    128,
    192,
    0,
    0,
    0,
    0,
    0
};

// clang-format on

static void eFuro_Yuge_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_FURO_YUGE, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eFuro_Yuge_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    qrand();
    effect->position.y += GETREG(TAKREG, 0x34) + 1.f;
    effect->scale.x = effect->scale.y = effect->scale.z = GETREG(TAKREG, 0x37) * 0.0001f + 0.001f;
    effect->timer = EFFECT_LIFETIME;
    effect->acceleration = ZeroVec;
    effect->acceleration.y = GETREG(TAKREG, 0x32) * 0.001f + 0.05f;
    effect->velocity = ZeroVec;
    effect->position.x += RANDOM2_F(effect->arg0);
    effect->position.z += RANDOM2_F(effect->arg0);
}

static void eFuro_Yuge_mv(eEC_Effect_c* effect, GAME* game) {
    xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
    xyz_t_add(&effect->position, &effect->velocity, &effect->position);
    effect->velocity.y *= GETREG(TAKREG, 0x39) * 0.001f + 0.9f;
}

static void eFuro_Yuge_dw(eEC_Effect_c* effect, GAME* game) {
    int opacity;
    s16 frames_alive = EFFECT_LIFETIME - effect->timer;
    s16 half_timer = CLAMP(frames_alive >> 1, 0, EFFECT_LIFETIME / 2);
    int texIdx1 = eFuro_Yuge_2tile_texture_idx[half_timer][0];
    int texIdx2 = eFuro_Yuge_2tile_texture_idx[half_timer][1];

    effect->scale.x =
        eEC_CLIP->calc_adjust_proc(frames_alive, 0, EFFECT_LIFETIME, GETREG(TAKREG, 0x37) * 0.0001f + 0.0015f,
                                   GETREG(TAKREG, 0x38) * 0.0001f + 0.009f);
    effect->scale.y = effect->scale.z = effect->scale.x;

    if (frames_alive < EFFECT_STAGE1) {
        opacity = eEC_CLIP->calc_adjust_proc(frames_alive, 0, EFFECT_STAGE1, GETREG(TAKREG, 0x35) + 50.f,
                                             GETREG(TAKREG, 0x36) + 80.f);
    } else {
        opacity =
            eEC_CLIP->calc_adjust_proc(frames_alive, EFFECT_STAGE1, EFFECT_LIFETIME, GETREG(TAKREG, 0x36) + 80.f, 0.0f);
    }

    OPEN_DISP(game->graph);
    eEC_CLIP->auto_matrix_xlu_proc(game, &effect->position, &effect->scale);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, eFuro_Yuge_texture_table[texIdx1]);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_2_TXT_SEG, eFuro_Yuge_texture_table[texIdx2]);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, eFuro_Yuge_prim_f[half_timer], 255, 255, 255, opacity);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_dust01_modelT);
    CLOSE_DISP(game->graph);
}
