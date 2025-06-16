#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

static void eTumbleBodyPrint_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eTumbleBodyPrint_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eTumbleBodyPrint_mv(eEC_Effect_c* effect, GAME* game);
static void eTumbleBodyPrint_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_tumble_bodyprint = {
    // clang-format off
    &eTumbleBodyPrint_init,
    &eTumbleBodyPrint_ct,
    &eTumbleBodyPrint_mv,
    &eTumbleBodyPrint_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eTumbleBodyPrint_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_TUMBLE_BODYPRINT, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eTumbleBodyPrint_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    s16* angle_p = (s16*)ct_arg;
    s16 angle = *angle_p;
    s_xyz ground_angle;

    if ((Common_Get(time.season) == mTM_SEASON_WINTER &&
         (effect->arg0 == mCoBG_ATTRIBUTE_GRASS0 || effect->arg0 == mCoBG_ATTRIBUTE_GRASS1 ||
          effect->arg0 == mCoBG_ATTRIBUTE_GRASS2 || effect->arg0 == mCoBG_ATTRIBUTE_GRASS3)) ||
        effect->arg0 == mCoBG_ATTRIBUTE_SAND || effect->arg0 == mCoBG_ATTRIBUTE_WAVE) {
        effect->scale.x = effect->scale.y = effect->scale.z = 0.016f;
        effect->position.y = mCoBG_GetBgY_AngleS_FromWpos(&ground_angle, effect->position, 0.0f);
        effect->position.y += 0.6f;
        effect->position.x += sin_s(angle) * 7.0f;
        effect->position.z += cos_s(angle) * 7.0f;

        if (ground_angle.x != 0 || ground_angle.z != 0) {
            effect->position.y += (cos_s(angle) * -tan_s(ground_angle.x) + sin_s(angle) * tan_s(ground_angle.z)) * 7.0f + 1.4f;
        }

        effect->effect_specific[1] = angle;
        effect->effect_specific[0] = ground_angle.x;
        effect->effect_specific[2] = ground_angle.z;
        effect->effect_specific[4] = 0;

        if (effect->arg0 == mCoBG_ATTRIBUTE_SAND || effect->arg0 == mCoBG_ATTRIBUTE_WAVE) {
            effect->timer = 600;
            effect->effect_specific[3] = 1;
        } else {
            effect->timer = 800;
            effect->effect_specific[3] = 0;
        }
    } else {
        effect->timer = 0;
    }
}

static void eTumbleBodyPrint_mv(eEC_Effect_c* effect, GAME* game) {
    mActor_name_t* fg_p = mFI_GetUnitFG(effect->position);

    if (effect->scale.x < 0.021f) {
        effect->scale.x += 0.0005f;
        effect->scale.z = effect->scale.x;
    }

    if (effect->effect_specific[4] != 1 && fg_p != NULL && (ITEM_IS_HOLE(*fg_p) || *fg_p == HOLE_SHINE)) {
        effect->effect_specific[4] = 1;
    }

    if (effect->effect_specific[4] == 1 && effect->timer >= 70) {
        effect->timer -= 70;
    }
}

extern Gfx ef_bodyprint01_00_modelT[];

static void eTumbleBodyPrint_dw(eEC_Effect_c* effect, GAME* game) {
    s16 counter = 800 - effect->timer;
    u8 a;

    if (effect->effect_specific[3] != 0) {
        a = (int)eEC_CLIP->calc_adjust_proc(counter, 360, 600, 150.0f, 0.0f);
    } else {
        a = (int)eEC_CLIP->calc_adjust_proc(counter, 500, 799, 150.0f, 0.0f);
    }

    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);
    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, 0);
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, 1);
    Matrix_RotateZ(effect->effect_specific[2], 1);
    Matrix_RotateX(effect->effect_specific[0], 1);
    Matrix_RotateY(effect->effect_specific[1], 1);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (effect->effect_specific[3] != 0) {
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 70, 50, 50, a);
    } else {
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 0, 50, 100, a);
    }

    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_bodyprint01_00_modelT);

    CLOSE_DISP(game->graph);
}
