#include "ef_effect_control.h"

#include "m_common_data.h"

extern u8 ef_dust01_0[];
extern u8 ef_dust01_1[];
extern u8 ef_dust01_2[];
extern u8 ef_dust01_3[];

static u8* eDT_texture_table[] = {
    ef_dust01_0,
    ef_dust01_1,
    ef_dust01_2,
    ef_dust01_3,
};

static void eDT_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eDT_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eDT_mv(eEC_Effect_c* effect, GAME* game);
static void eDT_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_dust = {
    // clang-format off
    &eDT_init,
    &eDT_ct,
    &eDT_mv,
    &eDT_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static rgba_t eDT_prim_table[] = {
    // clang-format off
    {255, 255, 255, 255},
    {255, 255, 255, 255},
    {255, 255, 255, 255},
    {255, 255, 255, 255},
    {255, 255, 255, 255},
    {230, 150, 100, 255},
    {100, 100, 255, 255},
    {230, 230, 100, 255},
    {255, 255, 255, 255},
    {255, 255, 255, 255},
    // clang-format on
};

typedef struct {
    xyz_t velocity;
    xyz_t acceleration;
    f32 scale;
    s16 angle_y;
} eDT_data_c;

static void eDT_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eDT_data_c data;
    f32 rad_angle_y = SHORT2RAD_ANGLE2(angle);

    data.velocity.x = 0.0f;

    if (arg1 != 4) {
        data.velocity.y = 1.0f;
    } else {
        data.velocity.y = 0.0f;
        pos.y += 5.0f;
    }

    if (arg1 == 8) {
        data.velocity.z = -2.0f;
    } else if (arg1 == 1) {
        data.velocity.z = -1.5f;
    } else if (arg1 == 2) {
        data.velocity.z = -1.0f;
    } else if (arg1 == 3 || arg1 == 5) {
        data.velocity.z = 0.0f;
    } else if (arg1 == 0) {
        data.velocity.z = 0.5f;
        pos.x += 15.0f * sin_s(angle);
        pos.z += 15.0f * cos_s(angle);
        pos.y += -15.0f;
    } else if (arg1 == 9) {
        data.velocity.z = 0.75f;
        pos.x += 25.0f * sin_s(angle);
        pos.z += 25.0f * cos_s(angle);
    } else {
        data.velocity.z = 0.25f;
    }

    if (arg1 == 4) {
        data.acceleration.x = 0.0f;
        data.acceleration.y = 0.1f;
        data.acceleration.z = 0.0f;
    } else if (arg1 == 0) {
        data.acceleration = ZeroVec;
    } else {
        data.acceleration.x = 0.0f;
        data.acceleration.y = -0.05f;
        data.acceleration.z = 0.075f;
    }

    if (arg1 == 4) {
        data.scale = 0.015f;
    } else if (arg1 == 0 || arg1 == 9) {
        data.scale = 0.007f;
    } else {
        data.scale = 0.01f;
    }

    eEC_CLIP->vector_rotate_y_proc(&data.velocity, rad_angle_y);
    eEC_CLIP->vector_rotate_y_proc(&data.acceleration, rad_angle_y);
    eEC_CLIP->make_effect_proc(eEC_EFFECT_DUST, pos, NULL, game, &data, item_name, prio, arg0, arg1);
}

static void eDT_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    eDT_data_c* data = (eDT_data_c*)ct_arg;

    effect->scale.x = data->scale;
    effect->scale.y = data->scale;
    effect->scale.z = data->scale;
    effect->timer = 18;
    effect->acceleration = data->acceleration;
    effect->velocity = data->velocity;
}

static void eDT_mv(eEC_Effect_c* effect, GAME* game) {
    if (effect->arg1 == 4) {
        s16 counter = 18 - effect->timer;

        effect->scale.x = eEC_CLIP->calc_adjust_proc(counter, 0, 17, 0.012f, 0.015f);
        effect->scale.y = effect->scale.x;
        effect->scale.z = effect->scale.x;
    } else if (effect->arg1 == 0 || effect->arg1 == 9) {
        effect->velocity.x *= sqrtf(0.85f);
        effect->velocity.y *= sqrtf(0.85f);
        effect->velocity.z *= sqrtf(0.85f);
    }

    xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
    xyz_t_add(&effect->position, &effect->velocity, &effect->position);
}

typedef struct {
    u8 tex0;
    u8 tex1;
} eDT_2tile_c;

static eDT_2tile_c eDT_2tile_texture_idx[] = {
    {0, 0},
    {0, 1},
    {1, 1},
    {1, 2},
    {2, 2},
    {2, 3},
    {3, 3},
    {3, 3},
    {3, 3},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
};

static u8 eDT_AlphaPtn[18] = {
    0xFF, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8, 0xC8,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,
};

static u8 eDT_prim_f[18] = {
    0x00, 0x80, 0xFF, 0x80, 0x00, 0x80, 0xFF, 0x80,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00,
};

extern Gfx ef_dust01_modelT[];

static void eDT_dw(eEC_Effect_c* effect, GAME* game) {
    s16 counter = (18 - effect->timer) >> 1;
    xyz_t* pos = &effect->position;
    xyz_t* scale = &effect->scale;
    int tex0;
    int tex1;

    counter = CLAMP(counter, 0, 9);

    
    tex0 = eDT_2tile_texture_idx[counter].tex0;
    tex1 = eDT_2tile_texture_idx[counter].tex1;
    
    OPEN_DISP(game->graph);
    
    eEC_CLIP->auto_matrix_xlu_proc(game, &effect->position, &effect->scale);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, eDT_texture_table[tex0]);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_2_TXT_SEG, eDT_texture_table[tex1]);

    if (effect->arg1 >= 0 && effect->arg1 < 10) {
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, eDT_prim_f[counter], eDT_prim_table[effect->arg1].r, eDT_prim_table[effect->arg1].g, eDT_prim_table[effect->arg1].b, eDT_AlphaPtn[counter]);
    } else {
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, eDT_prim_f[counter], 255, 255, 255, eDT_AlphaPtn[counter]);
    }

    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_dust01_modelT);

    CLOSE_DISP(game->graph);
}
