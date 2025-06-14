#include "ef_effect_control.h"

#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "m_debug.h"

static void eKZ_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKZ_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKZ_mv(eEC_Effect_c* effect, GAME* game);
static void eKZ_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_kaze = {
    // clang-format off
    &eKZ_init,
    &eKZ_ct,
    &eKZ_mv,
    &eKZ_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

typedef struct {
    s16 angle;
} eKZ_dt_c;

static void eKZ_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eKZ_dt_c data;

    data.angle = angle;
    eEC_CLIP->make_effect_proc(eEC_EFFECT_KAZE, pos, NULL, game, &data, item_name, prio, 0, 0);
}

static void eKZ_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    eKZ_dt_c* data_p = (eKZ_dt_c*)ct_arg;
    GAME_PLAY* play = (GAME_PLAY*)game;
    u16 angle = data_p->angle - DIFF_SHORT_ANGLE((s16)getCamera2AngleY(play), DEG2SHORT_ANGLE2(-180.0f));

    effect->effect_specific[1] = angle;
    effect->offset.x = 0.0f;
    effect->offset.y = -3.0f;
    effect->offset.z = 24.0f;

    effect->timer = 100;
    
    if (angle >= DEG2SHORT_ANGLE2(90.0f) && angle <= DEG2SHORT_ANGLE2(270.0f)) {
        effect->effect_specific[0] = 1;
    } else {
        effect->effect_specific[0] = 0;
    }

    effect->scale.x = 0.063f;
    effect->scale.y = 0.021f;
    effect->scale.z = 0.021f;
    sAdo_OngenTrgStart(NA_SE_KAZE, &effect->position);
}

static void eKZ_mv(eEC_Effect_c* effect, GAME* game) {
    if (effect->timer == 64 && eEC_CLIP != NULL) {
        xyz_t pos = effect->position;

        pos.y += -10.0f;
        pos.z += 10.0f;

        eEC_CLIP->effect_make_proc(eEC_EFFECT_KAZE_HAPPA, pos, effect->prio, effect->effect_specific[1], game, effect->item_name, 0, 0);
    }
}

extern EVW_ANIME_DATA ef_kaze01_evw_anime;
extern Gfx ef_kaze01_modelT[];
extern Gfx ef_kaze01_modelT2[];

static void eKZ_dw(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    s16 counter = 100 - effect->timer;
    u8 a;
    f32 scale;

    if (counter <= 9) {
        a = (int)eEC_CLIP->calc_adjust_proc(counter, 0, 18, 0.0f, 150.0f);
    } else if (counter < 80) {
        a = 150;
    } else {
        a = (int)eEC_CLIP->calc_adjust_proc(counter, 80, 98, 150.0f, 0.0f);
    }

    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);
    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, 0);
    Matrix_mult(&play->billboard_matrix, 1);
    Matrix_translate(effect->offset.x, effect->offset.y, effect->offset.z, 1);

    if (effect->effect_specific[0] == 0) {
        Matrix_RotateZ(DEG2SHORT_ANGLE2(-11.25f), 1);
    } else {
        Matrix_RotateZ(DEG2SHORT_ANGLE2(11.25f), 1);
    }

    scale = GETREG(MYKREG, 27) * 0.01f + 1.0f;
    Matrix_scale(effect->scale.x * scale, effect->scale.y * scale, effect->scale.z * scale, 1);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    Evw_Anime_Set(play, &ef_kaze01_evw_anime);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 255, a);
    if (effect->effect_specific[0] == 0) {
        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_kaze01_modelT);
    } else {
        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_kaze01_modelT2);
    }

    CLOSE_DISP(game->graph);
}
