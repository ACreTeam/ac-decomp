#include "ef_effect_control.h"

#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "m_debug.h"

extern Gfx ef_daruma01_00_model[];
extern Gfx ef_daruma01_01_model[];
extern Gfx ef_daruma01_02_model[];

static Gfx* ef_yukidaruma_model_tbl[] = { ef_daruma01_00_model, ef_daruma01_01_model, ef_daruma01_02_model };

static void eYukidaruma_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eYukidaruma_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eYukidaruma_mv(eEC_Effect_c* effect, GAME* game);
static void eYukidaruma_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_yukidaruma = {
    // clang-format off
    &eYukidaruma_init,
    &eYukidaruma_ct,
    &eYukidaruma_mv,
    &eYukidaruma_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eYukidaruma_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    int count = arg0 > 66 ? 8 : 3;
    int i;

    while ((s16)count-- != 0) {
        xyz_t sub_pos = pos;

        sub_pos.x += fqrand2() * 20.0f;
        sub_pos.y += fqrand2() * 20.0f;
        sub_pos.z += fqrand2() * 20.0f;

        eEC_CLIP->effect_make_proc(eEC_EFFECT_YUKIDAMA, sub_pos, prio, 0, game, item_name, 0, 0x4000 | count);
    }

    eEC_CLIP->make_effect_proc(eEC_EFFECT_YUKIDARUMA, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eYukidaruma_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 20;
    effect->offset.x = eEC_CLIP->calc_adjust_proc(effect->arg0, 0, 100, 0.01f, 0.03f);

    effect->scale.x = effect->scale.y = effect->scale.z = effect->offset.x;
}

static void eYukidaruma_mv(eEC_Effect_c* effect, GAME* game) {
    // nothing
}

static void eYukidaruma_dw(eEC_Effect_c* effect, GAME* game) {
    int frame = (20 - effect->timer) >> 1;
    int model = frame / 3;

    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);

    if (model < ARRAY_COUNT(ef_yukidaruma_model_tbl)) {
        Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
        Matrix_scale(effect->offset.x, effect->offset.x, effect->offset.x, MTX_MULT);

        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 128, 255, 255, 255, 255);
        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_yukidaruma_model_tbl[model]);
    }

    if (frame == 3 || frame == 6 || frame == 9) {
        Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
        Matrix_scale(effect->offset.x, effect->offset.x, effect->offset.x, MTX_MULT);

        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 128, 255, 255, 255, 120);
        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_yukidaruma_model_tbl[model - 1]);
    }

    CLOSE_DISP(game->graph);
}
