#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_debug.h"
#include "m_rcp.h"
#include "sys_matrix.h"

extern Gfx ef_namida01_modelT[];

static void eNamida_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eNamida_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eNamida_mv(eEC_Effect_c* effect, GAME* game);
static void eNamida_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_namida = {
    // clang-format off
    &eNamida_init,
    &eNamida_ct,
    &eNamida_mv,
    &eNamida_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

typedef struct {
    s16 angle;
    s16 arg0;
} eNamida_dt_c;

static void eNamida_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    xyz_t ofs;
    eNamida_dt_c data;

    data.angle = angle;
    data.arg0 = arg0;

    ofs.x = GETREG(MYKREG, 0x18);
    ofs.y = GETREG(MYKREG, 0x19);
    ofs.z = GETREG(MYKREG, 0x1a) + 10.0f;

    eEC_CLIP->make_effect_proc(eEC_EFFECT_NAMIDA, pos, &ofs, game, &data, item_name, prio, 0, 0);
}

static void eNamida_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    eNamida_dt_c* data = (eNamida_dt_c*)ct_arg;

    effect->timer = 30;

    effect->effect_specific[0] = data->angle;
    effect->effect_specific[1] = data->arg0;

    eEC_CLIP->random_first_speed_proc(&effect->velocity, 1.85f, 40.0f, 40.0f);
    if (effect->effect_specific[1] == 0) {
        sMath_RotateZ(&effect->velocity, DEG2RAD(55.0f));
    } else if (effect->effect_specific[1] == 1) {
        sMath_RotateZ(&effect->velocity, DEG2RAD(-55.0f));
    }

    effect->acceleration.x = 0.0f;
    effect->acceleration.y = -0.0675f;
    effect->acceleration.z = 0.0f;

    effect->scale.x = 0.0f;
    effect->scale.y = 0.0f;
    effect->scale.z = 0.0f;
}

static void eNamida_mv(eEC_Effect_c* effect, GAME* game) {
    s16 timer = 30 - effect->timer;

    xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
    xyz_t_add(&effect->offset, &effect->velocity, &effect->offset);

    if (timer < 20) {
        effect->scale.x = eEC_CLIP->calc_adjust_proc(timer, 0, 18, 0.0f, 0.0027f);
    } else {
        effect->scale.x = eEC_CLIP->calc_adjust_proc(timer, 20, 30, 0.0027f, 0.0f);
    }
    effect->scale.y = effect->scale.x;
    effect->scale.z = effect->scale.x;
}

static void eNamida_dw(eEC_Effect_c* effect, GAME* game) {
    s16 angle = effect->effect_specific[0];
    xyz_t vec = effect->offset;

    sMath_RotateY(&vec, SHORT2RAD_ANGLE2(angle));

    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);

    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_translate(vec.x, vec.y, vec.z, MTX_MULT);
    Matrix_mult(&((GAME_PLAY*)game)->billboard_matrix, MTX_MULT);
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, MTX_MULT);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_namida01_modelT);

    CLOSE_DISP(game->graph);
}
