#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

extern u8 ef_dust01_0[];
extern u8 ef_dust01_1[];
extern u8 ef_dust01_2[];
extern u8 ef_dust01_3[];

static u8* eTDT_texture_table[4] = {
    ef_dust01_0, ef_dust01_1, ef_dust01_2, ef_dust01_3
};

static void eTumbleDust_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eTumbleDust_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eTumbleDust_mv(eEC_Effect_c* effect, GAME* game);
static void eTumbleDust_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_tumble_dust = {
    // clang-format off
    &eTumbleDust_init,
    &eTumbleDust_ct,
    &eTumbleDust_mv,
    &eTumbleDust_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

typedef struct {
    xyz_t velocity;
    xyz_t acceleration;
    f32 scale;
    s16 _1C;
} eTumbleDust_data_c;

static void eTumbleDust_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eTumbleDust_data_c data;
    f32 angle_rad = SHORT2RAD_ANGLE2(angle);

    data.velocity.x = 0.0f;
    data.velocity.y = 0.5f;

    if (arg1 == 1) {
        data.velocity.z = 3.75f;
    } else if (arg1 == 5 || arg1 == 7) {
        data.velocity.z = 5.5f;
    } else if (arg1 == 6 || arg1 == 8) {
        data.velocity.z = 5.5f;
    } else if (arg1 == 9) {
        data.velocity.z = 3.0f;
    } else {
        data.velocity.z = 3.5f;
    }

    data.acceleration.x = 0.0f;
    data.acceleration.y = 0.05f;
    data.acceleration.z = -0.05f;
    data.scale = 0.005f;

    eEC_CLIP->vector_rotate_y_proc(&data.velocity, angle_rad);
    eEC_CLIP->vector_rotate_y_proc(&data.acceleration, angle_rad);
    eEC_CLIP->make_effect_proc(eEC_EFFECT_TUMBLE_DUST, pos, NULL, game, &data, item_name, prio, arg0, arg1);
}

static void eTumbleDust_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    eTumbleDust_data_c* data = (eTumbleDust_data_c*)ct_arg;

    effect->scale.x = data->scale;
    effect->scale.y = data->scale;
    effect->scale.z = data->scale;

    if (effect->arg1 == 0 || effect->arg1 == 2) {
        effect->offset.x = 0.015f;
    } else if (effect->arg1 == 1 || effect->arg1 == 5 || effect->arg1 == 6) {
        effect->offset.x = 0.02f;
    } else {
        effect->offset.x = 0.015f;
    }

    if (effect->arg1 == 1 || effect->arg1 == 3) {
        effect->timer = 32;
    } else if (effect->arg1 == 0 || effect->arg1 == 4) {
        effect->timer = 34;
    } else if (effect->arg1 == 7 || effect->arg1 == 8) {
        effect->timer = 36;
    } else {
        effect->timer = 30;
    }

    effect->acceleration = data->acceleration;
    effect->velocity = data->velocity;
}

static void eTumbleDust_mv(eEC_Effect_c* effect, GAME* game) {
    if (effect->timer <= 30) {
        xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
        xyz_t_add(&effect->position, &effect->velocity, &effect->position);

        // why check this again??
        if (effect->timer <= 30) {
            // @cleanup - remove the sqrtfs here, way too much unnecessary work
            effect->acceleration.y *= sqrtf(0.8f);
            effect->velocity.y *= sqrtf(0.95f);
            effect->velocity.x *= sqrtf(0.8f);
            effect->velocity.z *= sqrtf(0.8f);
        }
    }
}

typedef struct {
    u8 tex0;
    u8 tex1;
} eTumbleDust_tex_c;

// @ 8057ce40
static eTumbleDust_tex_c eTDT_2tile_texture_idx[15] = {
    {0x00, 0x00},
    {0x00, 0x00},
    {0x00, 0x01},
    {0x00, 0x01},
    {0x01, 0x01},
    {0x01, 0x01},
    {0x01, 0x02},
    {0x01, 0x02},
    {0x02, 0x02},
    {0x02, 0x02},
    {0x02, 0x03},
    {0x02, 0x03},
    {0x03, 0x03},
    {0x03, 0x03},
    {0x03, 0x03},
};

// @ 8057ce60
static u8 eTDT_prim_f[15] = {
    0xFF, 0xFF, 0x55, 0xAA, 0xFF, 0xFF, 0x55, 0xAA,
    0xFF, 0xFF, 0x55, 0xAA, 0xFF, 0xFF, 0xFF
};

extern Gfx ef_dust01_modelT[];

static void eTumbleDust_dw(eEC_Effect_c* effect, GAME* game) {
    s16 counter = 30 - effect->timer;
    int idx = MIN(MAX(counter >> 1, 0), 14);
    int tex0 = eTDT_2tile_texture_idx[idx].tex0;
    int tex1 = eTDT_2tile_texture_idx[idx].tex1;
    u8 a;

    effect->scale.x = eEC_CLIP->calc_adjust_proc(counter, 0, 30, 0.005f, effect->offset.x);
    a = (int)eEC_CLIP->calc_adjust_proc(counter, 8, 30, 255.0f, 120.0f);

    effect->scale.y = effect->scale.z = effect->scale.x;
    
    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_proc(game, &effect->position, &effect->scale);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, eTDT_texture_table[tex0]);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_2_TXT_SEG, eTDT_texture_table[tex1]);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, eTDT_prim_f[idx], 255, 255, 255, a);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_dust01_modelT);

    CLOSE_DISP(game->graph);
}
