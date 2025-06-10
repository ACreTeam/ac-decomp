#include "ef_effect_control.h"

#include "m_common_data.h"

extern Gfx ef_muka01_00_modelT[];

static void eMK_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eMK_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eMK_mv(eEC_Effect_c* effect, GAME* game);
static void eMK_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_muka = {
    // clang-format off
    &eMK_init,
    &eMK_ct,
    &eMK_mv,
    &eMK_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eMK_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_MUKA, pos, NULL, game, &angle, item_name, prio, 0, 0);
}

static void eMK_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    s16 angle, angle_y;

    effect->scale.x = 0.0075f;
    effect->scale.y = 0.0075f;
    effect->scale.z = 0.0075f;

    angle_y = (s16)getCamera2AngleY((GAME_PLAY*)game);
    angle = *(s16*)ct_arg;
    if (DIFF_USHORT_ANGLE(angle, (s16)(angle_y + DEG2SHORT_ANGLE(180.0f))) > DEG2SHORT_ANGLE2(180.0f)) {
        effect->offset.x = -10.0f;
    } else {
        effect->offset.x = 10.0f;
    }
    effect->offset.y = 9.0f;
    effect->offset.z = 23.0f;

    effect->timer = 40;

    sAdo_OngenTrgStart(0x137, &effect->position);
}

static void eMK_mv(eEC_Effect_c* effect, GAME* game) {
    return;
}

static void eMK_dw(eEC_Effect_c* effect, GAME* game) {
    s16 timer = 40 - effect->timer;
    u8 prim_g = (int)eEC_CLIP->calc_adjust_proc(timer, 0, 20, 255.0f, 50.0f);
    u8 prim_a = (int)eEC_CLIP->calc_adjust_proc(timer, 20, 41, 255.0f, 0.0f);
    u8 env_r = (int)eEC_CLIP->calc_adjust_proc(timer, 0, 20, 255.0f, 100.0f);

    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_offset_proc(game, &effect->position, &effect->scale, &effect->offset);

    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 128, 255, prim_g, 50, prim_a);
    gDPSetEnvColor(NEXT_POLY_XLU_DISP, env_r, 30, 30, 255);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_muka01_00_modelT);

    CLOSE_DISP(game->graph);
}
