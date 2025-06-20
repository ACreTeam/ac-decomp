#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_rcp.h"
#include "sys_matrix.h"

static void eDig_Hole_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eDig_Hole_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eDig_Hole_mv(eEC_Effect_c* effect, GAME* game);
static void eDig_Hole_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_dig_hole = {
    // clang-format off
    &eDig_Hole_init,
    &eDig_Hole_ct,
    &eDig_Hole_mv,
    &eDig_Hole_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

typedef struct dig_hole_init_data_s {
    s16 type;
    s16 angle_y;
    s16 goal_angle_x;
    s16 timer;
} eDig_Hole_init_data_c;

static void eDig_Hole_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR(play);

    pos.x += player->actor_class.world.position.x + sin_s(angle) * 30.0f;
    pos.z += player->actor_class.world.position.z + cos_s(angle) * 30.0f;
    pos.x /= 2.0f;
    pos.z /= 2.0f;

    eEC_CLIP->make_effect_proc(eEC_EFFECT_DIG_HOLE, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eDig_Hole_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    static xyz_t fill_hole_pos_tbl[] = {
        { 0.0f, 0.0f, -21.0f },
        { 11.0f, 0.0f, -14.0f },
        { -3.0f, 0.0f, -8.0f },
    };

    static eDig_Hole_init_data_c init_data[] = {
        { 0, DEG2SHORT_ANGLE2(180.0f), DEG2SHORT_ANGLE2(179.0f), 36 },
        { 0, DEG2SHORT_ANGLE2(60.0f), DEG2SHORT_ANGLE2(179.0f), 36 },
        { 0, DEG2SHORT_ANGLE2(300.0f) + 1, DEG2SHORT_ANGLE2(179.0f), 36 },
        { 1, DEG2SHORT_ANGLE2(270.0f), DEG2SHORT_ANGLE2(179.0f), 58 },
        { 1, DEG2SHORT_ANGLE2(270.0f), DEG2SHORT_ANGLE2(179.0f), 46 },
        { 1, DEG2SHORT_ANGLE2(270.0f), DEG2SHORT_ANGLE2(150.0f), 34 },
    };

    s16* angle_p = (s16*)ct_arg;

    effect->effect_specific[0] = *angle_p;
    effect->effect_specific[4] = init_data[effect->arg1].type;
    effect->effect_specific[0] += init_data[effect->arg1].angle_y;
    effect->effect_specific[3] = init_data[effect->arg1].goal_angle_x;
    effect->effect_specific[2] = init_data[effect->arg1].timer;
    effect->effect_specific[1] = 0;

    effect->scale = ZeroVec;

    if (effect->effect_specific[4] == 1) {
        xyz_t pos = fill_hole_pos_tbl[effect->arg1 - 3];

        eEC_CLIP->vector_rotate_y_proc(&pos, SHORTANGLE2RAD(effect->effect_specific[0]));
        effect->position.x += pos.x;
        effect->position.y += 10.0f;
        effect->position.z += pos.z;

        eEC_CLIP->effect_make_proc(eEC_EFFECT_DIG_MUD, effect->position, effect->prio, effect->effect_specific[0], game,
                                   effect->item_name, effect->arg0, 6);
    } else {
        effect->position.x += 5.0f * sin_s(effect->effect_specific[0]);
        effect->position.y += 10.0f;
        effect->position.z += 5.0f * cos_s(effect->effect_specific[0]);
    }

    if (effect->arg0 == mCoBG_ATTRIBUTE_WAVE) {
        int i;
        s16 mizutama_arg1;
        s16 mizutama_angle = *angle_p;
        s16 angle;
        xyz_t pos = effect->position;

        pos.y = 21.0f;

        if (effect->arg1 <= 2) {
            mizutama_arg1 = 0x4000 | (effect->arg1 << 1);
        } else {
            mizutama_arg1 = 0x4000 | (5 << 1);
        }

        for (i = 0; i < 2; i++) {
            pos.x = effect->position.x + RANDOM2_F(10.0f);
            pos.z = effect->position.z + RANDOM2_F(10.0f);

            if (effect->arg1 > 2) {
                angle = mizutama_angle + (s16)(int)(RANDOM2_F(150.0f) * 182.04445f);
            } else {
                angle = mizutama_angle + (s16)(int)(RANDOM2_F(90.0f) * 182.04445f);
            }

            mizutama_angle = angle;
            eEC_CLIP->effect_make_proc(eEC_EFFECT_MIZUTAMA, pos, effect->prio, mizutama_angle, game, effect->item_name,
                                       effect->arg0, mizutama_arg1);
        }
    }

    effect->timer = effect->effect_specific[2];
}

static void eDig_Hole_mv(eEC_Effect_c* effect, GAME* game) {
    if (effect->timer > (effect->effect_specific[2] - 6)) {
        effect->scale.x += 0.00108333334f;
        effect->scale.y = effect->scale.z = effect->scale.x;
    } else if (effect->timer < 6 && effect->effect_specific[4] == 1) {
        effect->scale.x -= 0.00108333334f;
        effect->scale.y = effect->scale.z = effect->scale.x;
    } else if (effect->effect_specific[4] == 1 || effect->timer <= (effect->effect_specific[2] - 8)) {
        add_calc_short_angle2(&effect->effect_specific[1], effect->effect_specific[3], 1.0f - sqrtf(0.8f), 1820, 91);
    }

    if (effect->timer == (effect->effect_specific[2] - 8)) {
        f32 speed;

        if (effect->arg1 == 0 || effect->arg1 == 1 || effect->arg1 == 2) {
            speed = 0.15f;
        } else {
            speed = 0.75f;
        }

        effect->velocity.y = 1.0f;
        effect->velocity.x = speed * sin_s(effect->effect_specific[0]);
        effect->velocity.z = speed * cos_s(effect->effect_specific[0]);

        effect->acceleration.y = -0.1f;
    }

    if (effect->effect_specific[4] == 0 || effect->timer > (effect->effect_specific[2] - 30)) {
        xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
        xyz_t_add(&effect->position, &effect->velocity, &effect->position);
    }
}

extern Gfx ef_anahori01_00_model[];
extern Gfx ef_anahori01_01_model[];
extern Gfx ef_anahori01_02_model[];

static void eDig_Hole_dw(eEC_Effect_c* effect, GAME* game) {
    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);
    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_RotateY(effect->effect_specific[0], MTX_MULT);
    Matrix_RotateX(effect->effect_specific[1], MTX_MULT);
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, MTX_MULT);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if (effect->effect_specific[4] == 0) {
        u8 a = (int)eEC_CLIP->calc_adjust_proc(effect->timer, 0, 10, 0.0f, 255.0f);

        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 255, a);
    } else {
        gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 255, 255);
    }

    switch (effect->arg0) {
        case mCoBG_ATTRIBUTE_GRASS0:
        case mCoBG_ATTRIBUTE_GRASS1:
        case mCoBG_ATTRIBUTE_GRASS2:
            if (effect->effect_specific[4] == 0) {
                gSPDisplayList(NEXT_POLY_XLU_DISP, ef_anahori01_00_model);
            } else {
                gSPDisplayList(NEXT_POLY_XLU_DISP, ef_anahori01_01_model);
            }
            break;
        case mCoBG_ATTRIBUTE_WAVE:
        case mCoBG_ATTRIBUTE_SAND:
            gSPDisplayList(NEXT_POLY_XLU_DISP, ef_anahori01_02_model);
            break;
        default:
            gSPDisplayList(NEXT_POLY_XLU_DISP, ef_anahori01_01_model);
            break;
    }

    CLOSE_DISP(game->graph);
}
