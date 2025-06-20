#include "ef_effect_control.h"

#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_rcp.h"

static void eKL_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKL_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKL_mv(eEC_Effect_c* effect, GAME* game);
static void eKL_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_killer = {
    // clang-format off
    &eKL_init,
    &eKL_ct,
    &eKL_mv,
    &eKL_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static void eKL_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    (*eEC_CLIP->make_effect_proc)(eEC_EFFECT_KILLER, pos, NULL, game, NULL, item_name, prio, angle, arg1);
}

static void eKL_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    static xyz_t xyz0 = { 0.0f, 0.0f, 0.0f };

    effect->acceleration = xyz0;
    effect->velocity = xyz0;
    effect->velocity.x = sin_s(effect->arg0) * 2.0f;
    effect->velocity.z = cos_s(effect->arg0) * 2.0f;
    effect->timer = 360;

    switch (Save_Get(scene_no)) {
        case SCENE_MY_ROOM_S:
            effect->offset.x = 40.0f;
            effect->offset.z = 40.0f;
            effect->offset.y = 200.0f;
            effect->scale.x = 360.0f;
            break;
        case SCENE_NPC_HOUSE:
        case SCENE_MY_ROOM_M:
        case SCENE_MY_ROOM_LL2:
        case SCENE_COTTAGE_NPC:
            effect->offset.x = 40.0f;
            effect->offset.z = 40.0f;
            effect->offset.y = 280.0f;
            effect->scale.x = 440.0f;
            break;
        case SCENE_MY_ROOM_L:
        case SCENE_MY_ROOM_LL1:
        case SCENE_MY_ROOM_BASEMENT_S:
        case SCENE_MY_ROOM_BASEMENT_M:
        case SCENE_MY_ROOM_BASEMENT_L:
        case SCENE_MY_ROOM_BASEMENT_LL1:
        case SCENE_COTTAGE_MY:
            effect->offset.x = 40.0f;
            effect->offset.z = 40.0f;
            effect->offset.y = 360.0f;
            effect->scale.x = 520.0f;
            break;
        default:
            effect->offset.x = 0.0f;
            effect->offset.y = 0.0f;
            effect->offset.z = 0.0f;
            effect->scale.x = 0.0f;
            break;
    }

    {
        if (ABS(effect->arg0 & 0xFFFF) <= 15) {
            if (ABS(effect->position.z - effect->scale.x) <= 21.0f) {
                effect->timer = 0;
                return;
            }
        } else if (ABS((effect->arg0 & 0xFFFF) - (u16)DEG2SHORT_ANGLE(90.0f)) <= 15) {
            if (ABS(effect->position.x - effect->offset.y) <= 21.0f) {
                effect->timer = 0;
                return;
            }
        } else if (ABS((effect->arg0 & 0xFFFF) - (u16)DEG2SHORT_ANGLE(180.0f)) <= 15) {
            if (ABS(effect->position.z - effect->offset.z) <= 21.0f) {
                effect->timer = 0;
                return;
            }
        } else if (ABS((effect->arg0 & 0xFFFF) - (u16)DEG2SHORT_ANGLE(270.0f)) <= 15) {
            if (ABS(effect->position.x - effect->offset.x) <= 21.0f) {
                effect->timer = 0;
                return;
            }
        } else {
            return;
        }

        sAdo_OngenTrgStart(0x44F, &effect->position);
        effect->effect_specific[0] = 0;
    }
}

static void eKL_mv(eEC_Effect_c* effect, GAME* game) {
    xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
    xyz_t_add(&effect->position, &effect->velocity, &effect->position);

    if (effect->position.x < effect->offset.x || effect->position.z < effect->offset.z ||
        effect->position.x > effect->offset.y || effect->position.z > effect->scale.x) {
        effect->timer = 0;
        effect->scale.z = 0.0f;
    } else {
        f32 dist = 1000.0f;

        if (ABS(effect->position.x - effect->offset.x) < 16.0f) {
            dist = ABS(effect->position.x - effect->offset.x);
        } else if (ABS(effect->position.z - effect->offset.z) < 16.0f) {
            dist = ABS(effect->position.z - effect->offset.z);
        } else if (ABS(effect->position.x - effect->offset.y) < 16.0f) {
            dist = ABS(effect->position.x - effect->offset.y);
        } else if (ABS(effect->position.z - effect->scale.x) < 16.0f) {
            dist = ABS(effect->position.z - effect->scale.x);
        }

        if (dist < 20.0f) {
            effect->scale.z = dist / 16.0f;

            if (effect->effect_specific[0] == 0) {
                effect->velocity.x *= 0.5f;
                effect->velocity.z *= 0.5f;
                effect->effect_specific[0] = 1;
            }
        } else {
            effect->scale.z = 1.0f;
        }
    }
}

extern Gfx act_killer_model[];

static void eKL_dw(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    Matrix_translate(effect->position.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_RotateY(effect->arg0, MTX_MULT);
    Matrix_scale(0.01f, 0.01f, effect->scale.z * 0.01f, MTX_MULT);
    _texture_z_light_fog_prim(game->graph);

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_OPA_DISP, act_killer_model);

    CLOSE_DISP(game->graph);
}
