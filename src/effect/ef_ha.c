#include "ef_effect_control.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_debug.h"

#define EFFECT_LIFETIME 56

static void eHA_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eHA_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eHA_mv(eEC_Effect_c* effect, GAME* game);
static void eHA_dw(eEC_Effect_c* effect, GAME* game);
extern Gfx ef_ha01_00_modelT[];
eEC_PROFILE_c iam_ef_ha = {
    // clang-format off
    &eHA_init,
    &eHA_ct,
    &eHA_mv,
    &eHA_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

s16 eHA_angle_z_data[] = { DEG2SHORT_ANGLE2(45.f), DEG2SHORT_ANGLE2(315.f) };

static void eHA_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_HA, pos, NULL, game, &angle, item_name, prio, 0, 0);
}

static void eHA_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    s16* ang_p = (s16*)ct_arg;
    u16 angle = *ang_p - (s16)((s16)getCamera2AngleY(play) + DEG2SHORT_ANGLE2(180));

    effect->scale.x = 0.0067f;
    effect->scale.y = 0.0067f;
    effect->scale.z = 0.0067f;
    effect->timer = EFFECT_LIFETIME;
    effect->offset.y += 12.f;
    if (angle >= (u16)DEG2SHORT_ANGLE2(180)) {
        effect->effect_specific[0] = 0;
        effect->offset.x += -16.f;
    } else {
        effect->effect_specific[0] = 1;
        effect->offset.x += 16.f;
    }
}

static void eHA_mv(eEC_Effect_c* effect, GAME* game) {
    if (effect->timer == EFFECT_LIFETIME) {
        sAdo_OngenTrgStart(NA_SE_2C, &effect->position);
    }
}

static void eHA_dw(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    s16 v = effect->effect_specific[0];
    int opacity = (u8)eEC_CLIP->calc_adjust_proc(EFFECT_LIFETIME - effect->timer, 24, EFFECT_LIFETIME, 255.f, 0.f);
    OPEN_DISP(game->graph);
    _texture_z_light_fog_prim_xlu(game->graph);
    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_mult(&play->billboard_matrix, MTX_MULT);
    Matrix_translate(effect->offset.x + GETREG(MYKREG, 0x18), effect->offset.y + GETREG(MYKREG, 0x19),
                     effect->offset.z + GETREG(MYKREG, 0x1a), MTX_MULT);
    Matrix_RotateZ(eHA_angle_z_data[v], MTX_MULT);
    Matrix_scale(effect->scale.x * (GETREG(MYKREG, 0x1b) * 0.01f + 1.f),
                 effect->scale.y * (GETREG(MYKREG, 0x1b) * 0.01f + 1.f),
                 effect->scale.z * (GETREG(MYKREG, 0x1b) * 0.01f + 1.f), MTX_MULT);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 128, 255, 255, 255, (u8)opacity);
    gDPSetEnvColor(NEXT_POLY_XLU_DISP, 0, 0, 255, 255);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_ha01_00_modelT);
    CLOSE_DISP(game->graph);
}
