#include "ef_effect_control.h"

#include "m_common_data.h"

extern Gfx ef_hirameki01_den_modelT[];

static void eHiramekiD_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eHiramekiD_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eHiramekiD_mv(eEC_Effect_c* effect, GAME* game);
static void eHiramekiD_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_hirameki_den = {
    // clang-format off
    &eHiramekiD_init,
    &eHiramekiD_ct,
    &eHiramekiD_mv,
    &eHiramekiD_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static u8 eHiramekiD_01f_primR_envRG[2] = { 0, 255 };
static u8 eHiramekiD_01f_primGB[2] = { 100, 255 };

static void eHiramekiD_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    if (eEC_CLIP != NULL) {
        eEC_CLIP->effect_make_proc(eEC_EFFECT_HIRAMEKI_HIKARI, pos, prio, angle, game, item_name, arg0, arg1);
    }

    pos.y += 24.0f;
    eEC_CLIP->make_effect_proc(eEC_EFFECT_HIRAMEKI_DEN, pos, NULL, game, NULL, item_name, prio, 0, 0);
}

static void eHiramekiD_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 72;
    effect->offset.x = effect->offset.y = effect->offset.z = 0.0f;
    effect->scale.x = effect->scale.y = effect->scale.z = 0.007f;
}

static void eHiramekiD_mv(eEC_Effect_c* effect, GAME* game) {
    s16 timer = 72 - effect->timer;
    if (timer == 0) {
        sAdo_OngenTrgStart(0x2E, &effect->position);
    }
}

static void eHiramekiD_dw(eEC_Effect_c* effect, GAME* game) {
    xyz_t* position = &effect->position;
    xyz_t* offset = &effect->offset;
    xyz_t* scale = &effect->scale;
    s16 timer;
    u8 prim_r;
    u8 prim_g;
    u8 prim_b;
    u8 prim_a;
    u8 env_r;
    u8 env_g;

    timer = 72 - effect->timer;
    prim_a = (int)eEC_CLIP->calc_adjust_proc(timer, 64, 72, 255.0f, 0.0f);

    if (timer < 4) {
        s16 val = timer >> 1;
        s16 idx = val > 0 ? val : 0;
        u8 p_r = eHiramekiD_01f_primR_envRG[idx];
        u8 p_gb = eHiramekiD_01f_primGB[idx];

        prim_r = p_r;
        env_r = p_r;
        prim_g = p_gb;
        prim_b = p_gb;
        env_g = p_r;
    } else {
        prim_r = 255;
        prim_g = 255;
        prim_b = 100;
        env_r = 100;
        env_g = 50;
    }

    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_offset_proc(game, position, scale, offset);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, prim_r, prim_g, prim_b, prim_a);
    gDPSetEnvColor(NEXT_POLY_XLU_DISP, env_r, env_g, 0, 255);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_hirameki01_den_modelT);

    CLOSE_DISP(game->graph);
}
