#include "ef_effect_control.h"

#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "m_debug.h"

static void eKZH_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKZH_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKZH_mv(eEC_Effect_c* effect, GAME* game);
static void eKZH_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_kaze_happa = {
    // clang-format off
    &eKZH_init,
    &eKZH_ct,
    &eKZH_mv,
    &eKZH_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

typedef struct {
    s16 angle;
    int prio;
} eKZH_dt_c;

static void eKZH_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eKZH_dt_c data;

    data.angle = angle;
    data.prio = prio;
    eEC_CLIP->make_effect_proc(eEC_EFFECT_KAZE_HAPPA, pos, NULL, game, &data, item_name, prio, 0, 0);
}

static void eKZH_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    eKZH_dt_c* data_p = (eKZH_dt_c*)ct_arg;
    GAME_PLAY* play = (GAME_PLAY*)game;

    effect->timer = 60;
    effect->effect_specific[0] = data_p->angle;
    effect->effect_specific[2] = data_p->prio;
    effect->effect_specific[3] = 0;

    effect->scale.x = 0.0048f;
    effect->scale.y = 0.0048f;
    effect->scale.z = 0.0048f;

    effect->acceleration.x = 0.0f;
    effect->acceleration.y = 0.0f;
    effect->acceleration.z = 0.0f;
    
    {
        u16 angle = data_p->angle - DIFF_SHORT_ANGLE((s16)getCamera2AngleY(play), DEG2SHORT_ANGLE2(-180.0f));

        if (angle >= DEG2SHORT_ANGLE2(90.0f) && angle <= DEG2SHORT_ANGLE2(270.0f)) {
            effect->effect_specific[1] = 1;
            effect->offset.x = 40.0f;
        } else {
            effect->effect_specific[1] = 0;
            effect->offset.x = -40.0f;
        }
    }

    effect->offset.z = 15.0f;
    effect->offset.y = 14.0f;
}

static void eKZH_mv(eEC_Effect_c* effect, GAME* game) {
    s16 counter = 60 - effect->timer;
    f32 dir = 1.0f;

    if (effect->effect_specific[1] == 1) {
        dir = -1.0f;
    }

    if (counter < 20) {
        effect->velocity.x += dir * 0.095f;
        effect->velocity.y += -0.02875f;
    } else if (counter >= 20 && counter < 40) {
        f32 angle = eEC_CLIP->calc_adjust_proc(counter, 20, 39, 0.0f, 360.0f);
        effect->effect_specific[3] = RAD2SHORT_ANGLE2(DEG2RAD(angle));
    } else if (counter >= 40) {
        f32 angle = eEC_CLIP->calc_adjust_proc(counter, 40, 59, 360.0f, 450.0f);
        effect->effect_specific[3] = RAD2SHORT_ANGLE2(DEG2RAD(angle));
        effect->velocity.x += dir * 0.095f;
        effect->velocity.y += -0.02875f;
    }

    xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
    xyz_t_add(&effect->offset, &effect->velocity, &effect->offset);
}

extern Gfx ef_kaze01_happa_modelT[];

static void eKZH_dw(eEC_Effect_c* effect, GAME* game) {
    s16 counter = 60 - effect->timer;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (counter >= 0) {
        s16 counter2 = (counter - counter) + counter; // weird... idk what they did but it's necessary
        f32 scale;

        if (counter2 <= 10) {
            scale = eEC_CLIP->calc_adjust_proc(counter, 0, 10, 0.0f, 0.0048f);
        } else if (counter2 <= 50) {
            scale = 0.0048f;
        } else {
            scale = scale = eEC_CLIP->calc_adjust_proc(counter, 52, 60, 0.0048f, 0.0f);
        }

        effect->scale.x = scale;
        effect->scale.y = scale;
        effect->scale.z = scale;

        OPEN_DISP(game->graph);

        _texture_z_light_fog_prim_xlu(game->graph);
        Matrix_translate(effect->position.x, effect->position.y, effect->position.z, 0);
        Matrix_mult(&play->billboard_matrix, 1);
        Matrix_translate(effect->offset.x + GETREG(MYKREG, 24), effect->offset.y + GETREG(MYKREG, 25), effect->offset.z + GETREG(MYKREG, 26), 1);

        if (effect->effect_specific[1] == 0) {
            Matrix_RotateZ(effect->effect_specific[3], 1);
        } else {
            Matrix_RotateZ(-effect->effect_specific[3], 1);
        }

        Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, 1);

        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_POLY_XLU_DISP, ef_kaze01_happa_modelT);

        CLOSE_DISP(game->graph);
    }
}
