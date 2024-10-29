#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_debug.h"

extern u8 ef_mogura01_01_tex[];
extern u8 ef_mogura01_02_tex[];
extern u8 ef_mogura01_03_tex[];
extern u8 ef_mogura01_04_tex[];

extern u8 ef_anahori02_01_tex[];
extern u8 ef_anahori02_02_tex[];
extern u8 ef_anahori02_03_tex[];
extern u8 ef_anahori02_04_tex[];

extern u8 ef_anahori03_01_tex[];
extern u8 ef_anahori03_02_tex[];
extern u8 ef_anahori03_03_tex[];
extern u8 ef_anahori03_04_tex[];

static u8* eDig_Mud_tex_tbl[] = {
    ef_anahori02_01_tex,
    ef_anahori02_02_tex,
    ef_anahori02_03_tex,
    ef_anahori02_04_tex,
};

static u8* eDig_Mud_Sand_tex_tbl[] = {
    ef_anahori03_01_tex,
    ef_anahori03_02_tex,
    ef_anahori03_03_tex,
    ef_anahori03_04_tex,
};

static u8* eDig_Mud_Mogura_tex_tbl[] = {
    ef_mogura01_02_tex,
    ef_mogura01_03_tex,
    ef_mogura01_01_tex,
    ef_mogura01_04_tex,
};

static void eDig_Mud_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eDig_Mud_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eDig_Mud_mv(eEC_Effect_c* effect, GAME* game);
static void eDig_Mud_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_dig_mud = {
    // clang-format off
    &eDig_Mud_init,
    &eDig_Mud_ct,
    &eDig_Mud_mv,
    &eDig_Mud_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eDig_Mud_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_DIG_MUD, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eDig_Mud_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    s16* angle_p = (s16*)ct_arg;
    s16 angle_y = *angle_p;
    s16 angle_x = (s16)(int)((-60.0f + RANDOM2_F(20.0f)) * 182.04445f);
    f32 cos_x = cos_s(angle_x);
    f32 speed = -3.5f + RANDOM2_F(4.5f) * 0.5f;

    if ((effect->arg1 & 0x8000)) {
        effect->effect_specific[1] = 1;
        effect->arg1 &= ~0x8000;
    } else {
        effect->effect_specific[1] = 0;
    }

    if ((effect->arg1 & 0x4000)) {
        effect->scale.x = effect->scale.y = effect->scale.z = (0.5f + GETREG(TAKREG, 15) * 0.01f) * 0.01f;
        effect->effect_specific[2] = 1;
        effect->arg1 &= ~0x4000;
    } else {
        effect->scale.x = effect->scale.y = effect->scale.z = 0.01f;
        effect->effect_specific[2] = 0;
    }

    if (effect->arg1 == 0 || effect->arg1 == 3) {
        effect->effect_specific[0] = 32;
    } else if (effect->arg1 == 1 || effect->arg1 == 4) {
        effect->effect_specific[0] = 30;
    } else {
        effect->effect_specific[0] = 28;
    }

    if (effect->arg1 < 3) {
        angle_y += (int)((30.0f + RANDOM2_F(20.0f)) * 182.04445f);

        effect->velocity.x = (speed * cos_x) * sin_s(angle_y);
        effect->velocity.y = speed * sin_s(angle_x);
        effect->velocity.z = (speed * cos_x) * cos_s(angle_y);
    } else if (effect->arg1 < 6) {
        angle_y += (s16)(int)((120.0f * effect->arg1) * 182.04445f);

        effect->velocity.x = 0.4f * sin_s(angle_y);
        effect->velocity.y = 1.75f + fqrand();
        effect->velocity.z = 0.4f * cos_s(angle_y);
    } else if (effect->arg1 != 8) {
        effect->velocity.x = sin_s(angle_y);
        effect->velocity.y = 2.0f + fqrand();
        effect->velocity.z = cos_s(angle_y);
    } else {
        effect->velocity.x = 0.0f;
        effect->velocity.y = 2.0f + fqrand();
        effect->velocity.z = 0.0f;
    }

    effect->acceleration.y = -0.175f;
    effect->timer = effect->effect_specific[0];
}

static void eDig_Mud_mv(eEC_Effect_c* effect, GAME* game) {
    xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
    xyz_t_add(&effect->position, &effect->velocity, &effect->position);

    if (effect->timer < 18) {
        if (effect->effect_specific[2] != 1) {
            eEC_CLIP->calc_adjust_proc(effect->timer, 0, 18, 0.012f, 0.010f);
        } else {
            eEC_CLIP->calc_adjust_proc(effect->timer, 0, 18, 0.006f, 0.005f);
        }
    }
}

extern Gfx ef_anahori02_00_modelT[];
extern Gfx ef_anahori03_00_modelT[];
extern Gfx ef_mogura01_00_modelT[];

static void eDig_Mud_dw(eEC_Effect_c* effect, GAME* game) {
    int tex_idx;

    if (effect->timer > 18) {
        tex_idx = 0;
    } else if (effect->timer > 14) {
        tex_idx = 1;
    } else if (effect->timer > 10) {
        tex_idx = 2;
    } else {
        tex_idx = 3;
    }

    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_proc(game, &effect->position, &effect->scale);

    if (effect->effect_specific[1] == 1) {
        gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, eDig_Mud_Mogura_tex_tbl[tex_idx]);
        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_mogura01_00_modelT);
    } else if (effect->arg0 == mCoBG_ATTRIBUTE_SAND || effect->arg0 == mCoBG_ATTRIBUTE_WAVE) {
        gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, eDig_Mud_Sand_tex_tbl[tex_idx]);
        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_anahori03_00_modelT);
    } else {
        gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, eDig_Mud_tex_tbl[tex_idx]);
        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_anahori02_00_modelT);
    }

    CLOSE_DISP(game->graph);
}
