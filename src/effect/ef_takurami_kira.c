#include "ef_effect_control.h"

#include "m_common_data.h"

extern Gfx ef_takurami01_kira_modelT[];
extern Gfx ef_takurami01_normal_render_mode[];

static void eTMK_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eTMK_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eTMK_mv(eEC_Effect_c* effect, GAME* game);
static void eTMK_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_takurami_kira = {
    // clang-format off
    &eTMK_init,
    &eTMK_ct,
    &eTMK_mv,
    &eTMK_dw,
    eEC_IMMEDIATE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eTMK_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    xyz_t ofs;
    s16 angle_y = (s16)getCamera2AngleY((GAME_PLAY*)game) + DEG2SHORT_ANGLE2(180.0f);
    u16 angle_diff = DIFF_USHORT_ANGLE(angle, angle_y);

    if (angle_diff <= DEG2SHORT_ANGLE2(60.0f)) {
        ofs.x = 6.0f;
        ofs.z = 14.0f;
        ofs.y = -8.0f;
    } else if (angle_diff <= DEG2SHORT_ANGLE2(120.005f)) {
        ofs.x = 13.0f;
        ofs.z = 14.0f;
        ofs.y = -8.0f;
    } else if (angle_diff <= DEG2SHORT_ANGLE2(180.0f)) {
        ofs.x = 13.0f;
        ofs.z = -14.0f;
        ofs.y = -3.0f;
    } else if (angle_diff <= DEG2SHORT_ANGLE2(240.0f)) {
        ofs.x = -13.0f;
        ofs.z = -14.0f;
        ofs.y = -3.0f;
    } else if (angle_diff <= DEG2SHORT_ANGLE2(300.005f)) {
        ofs.x = -13.0f;
        ofs.z = 14.0f;
        ofs.y = -8.0f;
    } else {
        ofs.x = 7.0f;
        ofs.z = 14.0f;
        ofs.y = -8.0f;
    }

    eEC_CLIP->make_effect_proc(eEC_EFFECT_TAKURAMI_KIRA, pos, &ofs, game, NULL, item_name, prio, 0, 0);
}

static void eTMK_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 30;

    effect->scale.x = 0.0f;
    effect->scale.y = 0.0f;
    effect->scale.z = 0.0f;
}

static void eTMK_mv(eEC_Effect_c* effect, GAME* game) {
    f32 scale;
    s16 timer = 30 - effect->timer;

    if (timer < 10) {
        scale = eEC_CLIP->calc_adjust_proc(timer, 0, 10, 0.0f, 0.009f);
        effect->scale.x = scale;
        effect->scale.y = scale;
        effect->scale.z = scale;
    } else {
        scale = eEC_CLIP->calc_adjust_proc(timer, 11, 29, 0.009f, 0.0f);
        effect->scale.x = scale;
        effect->scale.y = scale;
        effect->scale.z = scale;
    }
}

static void eTMK_dw(eEC_Effect_c* effect, GAME* game) {
    eEC_CLIP->auto_matrix_xlu_offset_proc(game, &effect->position, &effect->scale, &effect->offset);

    OPEN_DISP(game->graph);

    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 255, 255);
    gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8, ef_takurami01_normal_render_mode);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_takurami01_kira_modelT);

    CLOSE_DISP(game->graph);
}
