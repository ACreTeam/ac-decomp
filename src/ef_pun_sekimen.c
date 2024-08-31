#include "ef_effect_control.h"

#include "m_common_data.h"

static void ePunRed_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void ePunRed_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void ePunRed_mv(eEC_Effect_c* effect, GAME* game);
static void ePunRed_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_pun_sekimen = {
    // clang-format off
    &ePunRed_init,
    &ePunRed_ct,
    &ePunRed_mv,
    &ePunRed_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void ePunRed_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    xyz_t ofs;

    ofs.x = 0.0f;
    ofs.y = -2.0f;
    ofs.z = 25.0f;
    eEC_CLIP->make_effect_proc(eEC_EFFECT_PUN_SEKIMEN, pos, &ofs, game, NULL, item_name, prio, 0, 0);
}

static void ePunRed_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->scale.x = 0.0105f;
    effect->scale.y = 0.0105f;
    effect->scale.z = 0.0105f;
    effect->timer = 16;
}

static void ePunRed_mv(eEC_Effect_c* effect, GAME* game) {
    // nothing
}

extern Gfx ef_pun01_01_modelT[];

static void ePunRed_dw(eEC_Effect_c* effect, GAME* game) {
    int a;
    xyz_t* scale;
    s16 now_timer;

    scale = &effect->scale;

    now_timer = 16 - effect->timer;
    a = (u8)eEC_CLIP->calc_adjust_proc(now_timer, 8, 16, 150.0f, 0.0f);
    scale->z = scale->y = scale->x = eEC_CLIP->calc_adjust_proc(now_timer, 0, 16, 0.0105f, 0.0189f);

    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_offset_proc(game, &effect->position, scale, &effect->offset);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 0, 0, a);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_pun01_01_modelT);

    CLOSE_DISP(game->graph);
}
