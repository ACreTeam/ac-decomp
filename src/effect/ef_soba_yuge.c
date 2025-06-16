#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_debug.h"
#include "sys_math3d.h"

extern Gfx ef_dust01_modelT[];
extern Gfx ef_dust01_stew_modelT[];

extern u8 ef_dust01_0[];
extern u8 ef_dust01_1[];
extern u8 ef_dust01_2[];
extern u8 ef_dust01_3[];

static u8* eSoba_Yuge_texture_table[] = {
    ef_dust01_0,
    ef_dust01_1,
    ef_dust01_2,
    ef_dust01_3,
};

static void eSoba_Yuge_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSoba_Yuge_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSoba_Yuge_mv(eEC_Effect_c* effect, GAME* game);
static void eSoba_Yuge_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_soba_yuge = {
    // clang-format off
    &eSoba_Yuge_init,
    &eSoba_Yuge_ct,
    &eSoba_Yuge_mv,
    &eSoba_Yuge_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

typedef struct {
    u8 tex0;
    u8 tex1;
} eSoba_Yuge_2tile_c;

// clang-format off
static eSoba_Yuge_2tile_c eSoba_Yuge_2tile_texture_idx[] = {
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 1},
    {0, 1},
    {0, 1},
    {1, 1},
    {1, 2},
    {1, 2},
    {1, 2},
    {2, 2},
    {2, 3},
    {2, 3},
    {2, 3},
    {3, 3},
    {3, 3},
    {3, 3},
    {3, 3},
    {3, 3},
};

static u8 eSoba_Yuge_prim_f[] = { 
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

static void eSoba_Yuge_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_SOBA_YUGE, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eSoba_Yuge_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    s16 rand = qrand();

    effect->position.y += GETREG(TAKREG, 0x34) + 1.0f;

    effect->scale.x = effect->scale.y = effect->scale.z = GETREG(TAKREG, 0x37) * 0.0001f + 0.001f;

    effect->timer = 44;

    effect->acceleration = ZeroVec;
    effect->acceleration.y = GETREG(TAKREG, 0x32) * 0.001f + 0.017f;

    effect->velocity = ZeroVec;

    effect->position.x += effect->arg0 * sin_s(rand);
    effect->position.z += effect->arg0 * cos_s(rand);
}

static void eSoba_Yuge_mv(eEC_Effect_c* effect, GAME* game) {
    xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
    xyz_t_add(&effect->position, &effect->velocity, &effect->position);

    effect->velocity.y *= GETREG(TAKREG, 0x39) * 0.001f + 0.95f;
}

static void eSoba_Yuge_dw(eEC_Effect_c* effect, GAME* game) {
    int alpha;
    s16 timer = 44 - effect->timer;
    s16 idx = CLAMP(timer >> 1, 0, 22);
    int texIdx1 = eSoba_Yuge_2tile_texture_idx[idx].tex0;
    int texIdx2 = eSoba_Yuge_2tile_texture_idx[idx].tex1;

    if (effect->arg1 == 0) {
        effect->scale.x = eEC_CLIP->calc_adjust_proc(timer, 0, 44, GETREG(TAKREG, 0x37) * 0.0001f + 0.001f,
                                                     GETREG(TAKREG, 0x38) * 0.0001f + 0.005f);
    } else {
        effect->scale.x = eEC_CLIP->calc_adjust_proc(timer, 0, 44, 0.001f, 0.01f);
    }
    effect->scale.y = effect->scale.z = effect->scale.x;

    if (effect->arg1 == 0) {
        alpha = eEC_CLIP->calc_adjust_proc(timer, 0, 44, GETREG(TAKREG, 0x35) + 130.0f, GETREG(TAKREG, 0x36) + 10.0f);
    } else {
        alpha = eEC_CLIP->calc_adjust_proc(timer, 0, 44, GETREG(TAKREG, 0x35) + 190.0f, GETREG(TAKREG, 0x36) + 10.0f);
    }

    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_proc(game, &effect->position, &effect->scale);

    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, eSoba_Yuge_texture_table[texIdx1]);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_2_TXT_SEG, eSoba_Yuge_texture_table[texIdx2]);

    if (effect->arg1 == 0) {
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, eSoba_Yuge_prim_f[idx], 255, 255, 255, alpha);
    } else {
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, eSoba_Yuge_prim_f[idx], 255, 200, 130, alpha);
    }

    if (effect->arg1 == 0) {
        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_dust01_modelT);
    } else {
        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_dust01_stew_modelT);
    }

    CLOSE_DISP(game->graph);
}
