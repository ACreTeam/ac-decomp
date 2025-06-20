#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_debug.h"

static void eFootPrint_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eFootPrint_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eFootPrint_mv(eEC_Effect_c* effect, GAME* game);
static void eFootPrint_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_footprint = {
    // clang-format off
    &eFootPrint_init,
    &eFootPrint_ct,
    &eFootPrint_mv,
    &eFootPrint_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

typedef struct footprint_data_s {
    s16 attr;
    s16 angle;
} eFootPrint_data_c;

static void eFootPrint_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eFootPrint_data_c data;

    data.attr = arg0;
    data.angle = angle;
    (*eEC_CLIP->make_effect_proc)(eEC_EFFECT_FOOTPRINT, pos, NULL, game, &data, item_name, prio, arg0, arg1);
}

static xyz_t eFootPrint_area_offset_data[] = { { 2.0f, 0.0f, -2.0f }, { -2.0f, 0.0f, -2.0f }, { 0.0f, 0.0f, 2.0f } };

static void eFootPrint_GetAreaPos(xyz_t* pos, xyz_t effect_pos, int area) {
    pos->x = effect_pos.x + eFootPrint_area_offset_data[area].x;
    pos->y = effect_pos.y + eFootPrint_area_offset_data[area].y;
    pos->z = effect_pos.z + eFootPrint_area_offset_data[area].z;
}

static void eFootPrint_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    eFootPrint_data_c* data = (eFootPrint_data_c*)ct_arg;

    if (Common_Get(time.season) == mTM_SEASON_WINTER || data->attr == mCoBG_ATTRIBUTE_SAND ||
        data->attr == mCoBG_ATTRIBUTE_WAVE) {
        if (data->attr == mCoBG_ATTRIBUTE_GRASS0 || data->attr == mCoBG_ATTRIBUTE_GRASS1 ||
            data->attr == mCoBG_ATTRIBUTE_GRASS2 || data->attr == mCoBG_ATTRIBUTE_GRASS3 ||
            data->attr == mCoBG_ATTRIBUTE_SAND || data->attr == mCoBG_ATTRIBUTE_WAVE) {
            int i;
            int sum_angle_x = 0;
            int sum_angle_z = 0;

            effect->position.y = 2.0f + mCoBG_GetShadowBgY_AngleS_FromWpos(NULL, effect->position, 0.0f);
            effect->effect_specific[2] = data->angle;

            /* Get the total ground angle (x & z) in a triangle around the effect position */
            for (i = 0; i < ARRAY_COUNT(eFootPrint_area_offset_data); i++) {
                xyz_t pos;
                s_xyz ground_angle = { 0, 0, 0 };

                eFootPrint_GetAreaPos(&pos, effect->position, i);
                mCoBG_GetBgY_AngleS_FromWpos(&ground_angle, pos, 0.0f);
                sum_angle_x += ground_angle.x;
                sum_angle_z += ground_angle.z;
            }

            /* Average x & z rotation over the sum of all ground angles */
            effect->effect_specific[0] = sum_angle_x / ARRAY_COUNT(eFootPrint_area_offset_data);
            effect->effect_specific[1] = sum_angle_z / ARRAY_COUNT(eFootPrint_area_offset_data);

            if (data->attr == mCoBG_ATTRIBUTE_SAND || data->attr == mCoBG_ATTRIBUTE_WAVE) {
                effect->effect_specific[3] = TRUE;
                if (data->attr == mCoBG_ATTRIBUTE_WAVE) {
                    (*eEC_CLIP->effect_make_proc)(eEC_EFFECT_TURI_HAMON, effect->position, effect->prio, 0, game,
                                                  effect->item_name, 2, 0);
                }
            } else {
                effect->effect_specific[3] = FALSE;
            }

            effect->timer = 160;
            return;
        }
    }

    effect->timer = 0;
}

static void eFootPrint_mv(eEC_Effect_c* effect, GAME* game) {
    if (effect->arg0 == mCoBG_ATTRIBUTE_WAVE && effect->timer == 150) {
        (*eEC_CLIP->effect_make_proc)(eEC_EFFECT_TURI_HAMON, effect->position, effect->prio, 0, game, effect->item_name,
                                      2, 0);
    }
}

extern Gfx ef_footprint01_00_modelT[];

static void eFootPrint_dw(eEC_Effect_c* effect, GAME* game) {
    u8 alpha = (int)(*eEC_CLIP->calc_adjust_proc)(160 - effect->timer, 118, 159, 150.0f, 0.0f);
    f32 scale;

    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);
    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_RotateX(effect->effect_specific[0], MTX_MULT);
    Matrix_RotateY(effect->effect_specific[2], MTX_MULT);
    Matrix_RotateZ(effect->effect_specific[1], MTX_MULT);
    scale = (1.0f + ((f32)(int)GETREG(MYKREG, 27)) * 0.01f) * 0.005f;
    Matrix_scale(scale, scale, 0.0075f, MTX_MULT);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (effect->effect_specific[3]) {
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 70, 50, 50, alpha);
    } else {
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 0, 50, 100, alpha);
    }
    gDPSetEnvColor(NEXT_POLY_XLU_DISP, 255, 255, 255, 255);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_footprint01_00_modelT);

    CLOSE_DISP(game->graph);
}
