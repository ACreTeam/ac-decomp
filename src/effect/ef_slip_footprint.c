#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

extern Gfx ef_footprint01_02_modelT[];

static void eSlipFootPrint_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eSlipFootPrint_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eSlipFootPrint_mv(eEC_Effect_c* effect, GAME* game);
static void eSlipFootPrint_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_slip_footprint = {
    // clang-format off
    &eSlipFootPrint_init,
    &eSlipFootPrint_ct,
    &eSlipFootPrint_mv,
    &eSlipFootPrint_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static xyz_t eSlipFootPrint_area_offset_data[] = { { 2.0f, 0.0f, -2.0f },
                                                   { -2.0f, 0.0f, -2.0f },
                                                   { 0.0f, 0.0f, 2.0f } };

typedef struct {
    s16 arg0;
    s16 angle;
} eSlipFootPrint_dt_c;

static void eSlipFootPrint_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eSlipFootPrint_dt_c data;

    data.arg0 = arg0;
    data.angle = angle;

    pos.x += sin_s(angle) * 6.0f;
    pos.z += cos_s(angle) * 6.0f;

    eEC_CLIP->make_effect_proc(eEC_EFFECT_SLIP_FOOTPRINT, pos, NULL, game, &data, item_name, prio, 0, 0);
}

static void eSlipFootPrint_GetAreaPos(xyz_t* pos, xyz_t effect_pos, int area) {
    pos->x = effect_pos.x + eSlipFootPrint_area_offset_data[area].x;
    pos->y = effect_pos.y + eSlipFootPrint_area_offset_data[area].y;
    pos->z = effect_pos.z + eSlipFootPrint_area_offset_data[area].z;
}

static void eSlipFootPrint_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    eSlipFootPrint_dt_c* data = (eSlipFootPrint_dt_c*)ct_arg;

    if (Common_Get(time.season) == mTM_SEASON_WINTER || data->arg0 == mCoBG_ATTRIBUTE_SAND ||
        data->arg0 == mCoBG_ATTRIBUTE_WAVE) {
        if (data->arg0 == mCoBG_ATTRIBUTE_GRASS0 || data->arg0 == mCoBG_ATTRIBUTE_GRASS1 ||
            data->arg0 == mCoBG_ATTRIBUTE_GRASS2 || data->arg0 == mCoBG_ATTRIBUTE_GRASS3 ||
            data->arg0 == mCoBG_ATTRIBUTE_SAND || data->arg0 == mCoBG_ATTRIBUTE_WAVE) {
            int i;
            int sum_angle_x = 0;
            int sum_angle_z = 0;

            effect->position.y = 2.0f + mCoBG_GetBgY_AngleS_FromWpos(NULL, effect->position, 0.0f);
            effect->effect_specific[2] = data->angle;

            /* Get the total ground angle (x & z) in a triangle around the effect position */
            for (i = 0; i < ARRAY_COUNT(eSlipFootPrint_area_offset_data); i++) {
                xyz_t pos;
                s_xyz ground_angle = { 0, 0, 0 };

                eSlipFootPrint_GetAreaPos(&pos, effect->position, i);
                mCoBG_GetBgY_AngleS_FromWpos(&ground_angle, pos, 0.0f);
                sum_angle_x += ground_angle.x;
                sum_angle_z += ground_angle.z;
            }

            /* Average x & z rotation over the sum of all ground angles */
            effect->effect_specific[0] = sum_angle_x / ARRAY_COUNT(eSlipFootPrint_area_offset_data);
            effect->effect_specific[1] = sum_angle_z / ARRAY_COUNT(eSlipFootPrint_area_offset_data);

            if (data->arg0 == mCoBG_ATTRIBUTE_SAND || data->arg0 == mCoBG_ATTRIBUTE_WAVE) {
                effect->effect_specific[3] = TRUE;
            } else {
                effect->effect_specific[3] = FALSE;
            }

            effect->timer = 160;
            return;
        }
    }

    effect->timer = 0;
}

static void eSlipFootPrint_mv(eEC_Effect_c* effect, GAME* game) {
    return;
}

static void eSlipFootPrint_dw(eEC_Effect_c* effect, GAME* game) {
    s16 timer = 160 - effect->timer;
    f32 scale = eEC_CLIP->calc_adjust_proc(timer, 2, 8, 0.006f, 0.008f);
    u8 alpha = (int)eEC_CLIP->calc_adjust_proc(timer, 118, 158, 150.0f, 0.0f);

    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);
    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_RotateX(effect->effect_specific[0], MTX_MULT);
    Matrix_RotateY(effect->effect_specific[2], MTX_MULT);
    Matrix_RotateZ(effect->effect_specific[1], MTX_MULT);
    Matrix_scale(scale, 0.008f, scale, MTX_MULT);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (effect->effect_specific[3]) {
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 70, 50, 50, alpha);
    } else {
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 0, 50, 100, alpha);
    }
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_footprint01_02_modelT);

    CLOSE_DISP(game->graph);
}
