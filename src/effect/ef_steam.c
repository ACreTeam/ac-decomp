#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

extern u8 ef_dust01_0[];
extern u8 ef_dust01_1[];
extern u8 ef_dust01_2[];
extern u8 ef_dust01_3[];

// @ 8057cb90
static u8* Steam_tex_tbl[4] = {
    ef_dust01_0, ef_dust01_1, ef_dust01_2, ef_dust01_3
};

typedef struct {
    u8 tex0;
    u8 tex1;
} eSteam_tex_c;

// @ 8057cba0
static eSteam_tex_c Steam_tex_indx[15] = {
    {0x00, 0x01},
    {0x00, 0x01},
    {0x00, 0x01},
    {0x00, 0x01},
    {0x02, 0x01},
    {0x02, 0x01},
    {0x02, 0x01},
    {0x02, 0x01},
    {0x02, 0x03},
    {0x02, 0x03},
    {0x02, 0x03},
    {0x02, 0x03},
    {0x03, 0x03},
    {0x03, 0x03},
    {0x03, 0x03},
};

// @ 8057cbc0
static u8 Steam_plod_tbl[15] = {
    0x00, 0x40, 0x80, 0xC0, 0xFF, 0xC0, 0x80, 0x40,
    0x00, 0x40, 0x80, 0xC0, 0xFF, 0xFF, 0xFF
};

static void eSteam_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSteam_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSteam_mv(eEC_Effect_c* effect, GAME* game);
static void eSteam_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_steam = {
    // clang-format off
    &eSteam_init,
    &eSteam_ct,
    &eSteam_mv,
    &eSteam_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eSteam_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_STEAM, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eSteam_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    s16* angle_p = (s16*)ct_arg;
    f32 speed = RANDOM_F(1.0f) + 0.5f;

    effect->scale.x = 0.005f;
    effect->offset.x = 0.02f;
    effect->velocity.y = -RANDOM_F(3.0f) - 1.5f;
    effect->velocity.x = sin_s(*angle_p) * speed;
    effect->velocity.z = cos_s(*angle_p) * speed;
    effect->acceleration.y = 0.125f;
    effect->timer = 30;
}

static void eSteam_mv(eEC_Effect_c* effect, GAME* game) {
    xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
    xyz_t_add(&effect->position, &effect->velocity, &effect->position);
    effect->velocity.x *= sqrtf(0.8f);
    effect->velocity.y *= sqrtf(0.8f);
    effect->velocity.z *= sqrtf(0.8f);
}

extern Gfx ef_dust01_modelT[];

static void eSteam_dw(eEC_Effect_c* effect, GAME* game) {
    s16 counter = 30 - effect->timer;
    s16 idx = CLAMP(counter >> 1, 0, 14);
    int tex0 = Steam_tex_indx[idx].tex0;
    int tex1 = Steam_tex_indx[idx].tex1;

    effect->scale.x = eEC_CLIP->calc_adjust_proc(counter, 0, 30, 0.005f, effect->offset.x);
    effect->scale.y = effect->scale.z = effect->scale.x;

    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_proc(game, &effect->position, &effect->scale);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, Steam_tex_tbl[tex0]);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_2_TXT_SEG, Steam_tex_tbl[tex1]);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, Steam_plod_tbl[idx], 255, 255, 255, 255);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_dust01_modelT);

    CLOSE_DISP(game->graph);
}
