#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

static void eTurnFootPrint_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eTurnFootPrint_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eTurnFootPrint_mv(eEC_Effect_c* effect, GAME* game);
static void eTurnFootPrint_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_turn_footprint = {
    // clang-format off
    &eTurnFootPrint_init,
    &eTurnFootPrint_ct,
    &eTurnFootPrint_mv,
    &eTurnFootPrint_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

typedef struct {
    s16 attr;
    s16 angle;
} eTurnFootPrint_data_c;

static void eTurnFootPrint_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eTurnFootPrint_data_c data;

    data.attr = arg0;
    data.angle = angle;
    eEC_CLIP->make_effect_proc(eEC_EFFECT_TURN_FOOTPRINT, pos, NULL, game, &data, item_name, prio, 0, 0);
}

static xyz_t eTurnFootPrint_area_offset_data[3] = {
    {2.0f, 0.0f, -2.0f},
    {-2.0f, 0.0f, -2.0f},
    {0.0f, 0.0f, 2.0f},
};

static void eTurnFootPrint_GetAreaPos(xyz_t* pos, xyz_t src_pos, int area) {
    pos->x = src_pos.x + eTurnFootPrint_area_offset_data[area].x;
    pos->y = src_pos.y + eTurnFootPrint_area_offset_data[area].y;
    pos->z = src_pos.z + eTurnFootPrint_area_offset_data[area].z;
}

static void eTurnFootPrint_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    eTurnFootPrint_data_c* data = (eTurnFootPrint_data_c*)ct_arg;

    if ((Common_Get(time.season) == mTM_SEASON_WINTER || data->attr == mCoBG_ATTRIBUTE_SAND || data->attr == mCoBG_ATTRIBUTE_WAVE) &&
        ((data->attr == mCoBG_ATTRIBUTE_GRASS0 || data->attr == mCoBG_ATTRIBUTE_GRASS1 || data->attr == mCoBG_ATTRIBUTE_GRASS2 || data->attr == mCoBG_ATTRIBUTE_GRASS3) || data->attr == mCoBG_ATTRIBUTE_SAND || data->attr == mCoBG_ATTRIBUTE_WAVE)) {
        int area;
        int angle_x_total = 0;
        int angle_y_total = 0;
        int angle_z_total = 0;

        effect->position.y = mCoBG_GetBgY_AngleS_FromWpos(NULL, effect->position, 0.0f) + 2.0f;
        effect->effect_specific[2] = data->angle;
        for (area = 0; area < 3; area++) {
            xyz_t pos;
            s_xyz angle = { 0, 0, 0 };

            eTurnFootPrint_GetAreaPos(&pos, effect->position, area);
            mCoBG_GetBgY_AngleS_FromWpos(&angle, pos, 0.0f);
            angle_x_total += angle.x;
            angle_y_total += angle.y;
            angle_z_total += angle.z;
        }

        effect->effect_specific[0] = angle_x_total / 3;
        effect->effect_specific[1] = angle_z_total / 3;

        if (data->attr == mCoBG_ATTRIBUTE_SAND || data->attr == mCoBG_ATTRIBUTE_WAVE) {
            effect->effect_specific[3] = 1;
        } else {
            effect->effect_specific[3] = 0;
        }

        effect->timer = 160;
    } else {
        effect->timer = 0;
    }
}

static void eTurnFootPrint_mv(eEC_Effect_c* effect, GAME* game) {
    // nothing
}

extern Gfx ef_turn_footprint_modelT[];

static void eTurnFootPrint_dw(eEC_Effect_c* effect, GAME* game) {
    s16 counter = 160 - effect->timer;
    f32 scale = eEC_CLIP->calc_adjust_proc(counter, 2, 8, 0.0054375003f, 0.0072500003f);
    u8 a = (int)eEC_CLIP->calc_adjust_proc(counter, 118, 159, 150.0f, 0.0f);

    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);
    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_RotateX(effect->effect_specific[0], MTX_MULT);
    Matrix_RotateY(effect->effect_specific[2], MTX_MULT);
    Matrix_RotateZ(effect->effect_specific[1], MTX_MULT);
    Matrix_scale(scale, 0.0072500003f, scale, MTX_MULT);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (effect->effect_specific[3] != 0) {
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 70, 50, 50, a);
    } else {
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 0, 50, 100, a);
    }
    
    gDPSetEnvColor(NEXT_POLY_XLU_DISP, 255, 255, 255, 255);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_turn_footprint_modelT);

    CLOSE_DISP(game->graph);
}
