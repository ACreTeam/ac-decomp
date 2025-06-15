#include "audio.h"
#include "ef_effect_control.h"

#include "graph.h"
#include "libu64/u64types.h"
#include "m_common_data.h"
#include "m_lib.h"
#include "m_rcp.h"
#include "sys_math3d.h"
#include "sys_matrix.h"

extern Gfx ef_situren01_00_modelT[];
extern Gfx ef_situren01_01_modelT[];
extern Gfx ef_situren01_02_modelT[];

static void eSN_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSN_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSN_mv(eEC_Effect_c* effect, GAME* game);
static void eSN_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_situren = {
    // clang-format off
    &eSN_init,
    &eSN_ct,
    &eSN_mv,
    &eSN_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eSN_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    xyz_t vec = { 0.0f, 10.0f, 7.0f };

    sMath_RotateY(&vec, SHORT2RAD_ANGLE2(angle));
    pos.x += vec.x;
    pos.y += vec.y;
    pos.z += vec.z;

    eEC_CLIP->make_effect_proc(eEC_EFFECT_SITUREN, pos, NULL, game, NULL, item_name, prio, 0, 0);
}

static void eSN_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 128;

    effect->scale = ZeroVec;
    effect->offset = ZeroVec;

    effect->effect_specific[0] = 0;

    sAdo_OngenTrgStart(0x13d, &effect->position);
}

static void eSN_mv(eEC_Effect_c* effect, GAME* game) {
    s16 timer = 128 - effect->timer;

    effect->effect_specific[0] += DEG2SHORT_ANGLE2(30.94f);

    if (timer < 8) {
        effect->position.y += 1.6f;
    }
}

static void eSN_dw(eEC_Effect_c* effect, GAME* game) {
    Gfx* gfx;
    s16 angle, timer;
    f32 s, c, temp1, temp2, temp3;
    u8 alpha;

    angle = effect->effect_specific[0];
    timer = 128 - effect->timer;

    s = sin_s(angle);
    c = cos_s(angle);

    temp1 = eEC_CLIP->calc_adjust_proc(timer, 0, 6, 0.0f, 0.0075f);
    temp2 = eEC_CLIP->calc_adjust_proc(timer, 0, 42, 1.4f, 1.0f);
    temp3 = eEC_CLIP->calc_adjust_proc(timer, 0, 42, 0.6f, 1.0f);
    alpha = (int)eEC_CLIP->calc_adjust_proc(timer, 108, 128, 255.0f, 0.0f);

    effect->scale.x = temp1 * (temp3 + ((s + 1.0f) * 0.5f * (temp2 - temp3)));
    effect->scale.y = temp1 * (temp3 + ((c + 1.0f) * 0.5f * (temp2 - temp3)));
    effect->scale.z = 0.0075f;

    if (timer == 60) {
        gfx = ef_situren01_01_modelT;
    } else if (timer > 60) {
        gfx = ef_situren01_02_modelT;
    } else {
        gfx = ef_situren01_00_modelT;
    }

    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);

    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, FALSE);
    Matrix_mult(&((GAME_PLAY*)game)->billboard_matrix, TRUE);
    Matrix_translate(effect->offset.x, effect->offset.y, effect->offset.z, TRUE);
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, TRUE);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 200, 255, alpha);
    gSPDisplayList(NEXT_POLY_XLU_DISP, gfx);

    CLOSE_DISP(game->graph);
}
