#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_debug.h"
#include "m_rcp.h"
#include "sys_matrix.h"

extern Gfx ef_turi_hamon01_00_modelT[];

static void eTH_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eTH_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eTH_mv(eEC_Effect_c* effect, GAME* game);
static void eTH_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_turi_hamon = {
    // clang-format off
    &eTH_init,
    &eTH_ct,
    &eTH_mv,
    &eTH_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eTH_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_TURI_HAMON, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eTH_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->effect_specific[2] = *(s16*)ct_arg;

    switch (effect->arg0) {
        case 0:
            effect->velocity.x = 0.036f;
            break;
        case 1:
            effect->velocity.x = 0.032f;
            break;
        case 2:
            effect->velocity.x = 0.024f;
            break;
        case 3:
            effect->velocity.x = 0.02f;
            break;
        case 4:
            effect->velocity.x = 0.014f;
            break;
        default:
            effect->velocity.x = ((effect->arg1 / 100.0f) * 0.06f) + 0.02f;
            break;
    }

    if (effect->velocity.x > 0.03f) {
        effect->effect_specific[0] = DEG2SHORT_ANGLE(1.1f);
        effect->effect_specific[3] = DEG2SHORT_ANGLE(1.1f);
    } else {
        effect->effect_specific[0] = DEG2SHORT_ANGLE(0.825f);
        effect->effect_specific[3] = DEG2SHORT_ANGLE(0.825f);
    }

    if (effect->arg0 == 7) {
        effect->timer = 32;
        effect->scale.x = 0.001f;
        effect->velocity.y = (GETREG(TAKREG, 0x39) * 0.1f + 3.0f) * 0.5f;
        effect->velocity.z = 1.0f / 32.0f;
    }
    if (effect->arg0 == 6) {
        effect->timer = 52;
        effect->scale.x = 0.001f;
        effect->velocity.y = 0.05f;
        effect->velocity.z = 1.0f / 52.0f;
    } else if (effect->arg0 != 4) {
        effect->timer = 32;
        effect->scale.x = 0.001f;
        effect->velocity.y = 0.125f;
        effect->velocity.z = 1.0f / 32.0f;
    } else {
        effect->timer = 52;
        effect->scale.x = 0.003f;
        effect->velocity.y = 0.35f;
        effect->velocity.z = 1.0f / 52.0f;
    }

    effect->effect_specific[1] = effect->timer;
    effect->scale.y = effect->scale.x;
    effect->scale.z = effect->scale.x;
}

static void eTH_mv(eEC_Effect_c* effect, GAME* game) {
    add_calc2(&effect->scale.x, effect->velocity.x, 1.0f - sqrtf(1.0f - effect->velocity.z), 0.005f);

    effect->effect_specific[0] =
        eEC_CLIP->calc_adjust_proc(effect->timer, 0, effect->effect_specific[1], 0.0f, effect->effect_specific[3]);

    effect->scale.y = effect->scale.x;
    effect->scale.z = effect->scale.x;

    effect->position.x += effect->velocity.y * sin_s(effect->effect_specific[2]);
    effect->position.z += effect->velocity.y * cos_s(effect->effect_specific[2]);
}

static void eTH_dw(eEC_Effect_c* effect, GAME* game) {
    xyz_t scale = effect->scale;

    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);
    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, FALSE);
    Matrix_scale(scale.x, scale.y, scale.z, TRUE);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 255, effect->effect_specific[0]);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_turi_hamon01_00_modelT);

    CLOSE_DISP(game->graph);
}
