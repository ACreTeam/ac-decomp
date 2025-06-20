#include "ef_effect_control.h"

#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_rcp.h"

static void eTL_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eTL_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eTL_mv(eEC_Effect_c* effect, GAME* game);
static void eTL_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_tent_lamp = {
    // clang-format off
    &eTL_init,
    &eTL_ct,
    &eTL_mv,
    &eTL_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static void eTL_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    (*eEC_CLIP->make_effect_proc)(eEC_EFFECT_TENT_LAMP, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static s16 eTL_GetNiceSwitchStat() {
    if (Common_Get(time.now_sec) >= (5 * mTM_SECONDS_IN_HOUR) &&
        Common_Get(time.now_sec) < (18 * mTM_SECONDS_IN_HOUR)) {
        return FALSE;
    }

    return TRUE;
}

static void eTL_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    effect->timer = 100;
    if (eTL_GetNiceSwitchStat() == TRUE) {
        mEnv_RequestChangeLightON(play, mRmTp_LIGHT_SWITCH_HOUSE0_BASEMENT, FALSE);
        effect->offset.x = 1.0f;
    } else {
        mEnv_RequestChangeLightOFF(play, mRmTp_LIGHT_SWITCH_HOUSE0_BASEMENT, 0.5f);
        effect->offset.x = 0.0f;
    }
}

static void eTL_mv(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    f32 target;
    int nice_switch_state = eTL_GetNiceSwitchStat();

    (*eEC_CLIP->set_continious_env_proc)(effect, 100, 100);

    if (nice_switch_state == TRUE) {
        mEnv_RequestChangeLightON(play, mRmTp_LIGHT_SWITCH_HOUSE0_BASEMENT, FALSE);
        target = 1.0f;
    } else {
        mEnv_RequestChangeLightOFF(play, mRmTp_LIGHT_SWITCH_HOUSE0_BASEMENT, 0.01f);
        target = 0.0f;
    }

    add_calc(&effect->offset.x, target, 0.015f, 0.1f, 0.001f);
}

extern Gfx obj_tent_lamp_model[];

static void eTL_dw(eEC_Effect_c* effect, GAME* game) {
    int l = (int)(255.0f + effect->offset.x * -255.0f);

    _texture_z_light_fog_prim(game->graph);

    OPEN_DISP(game->graph);

    Matrix_translate(0.0f, 0.0f, 0.0f, MTX_LOAD);
    Matrix_scale(0.05f, 0.05f, 0.05f, MTX_MULT);

    gDPSetPrimColor(NEXT_POLY_OPA_DISP, 0, l, 255, 255, 255, 255);
    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_OPA_DISP, obj_tent_lamp_model);

    CLOSE_DISP(game->graph);
}
