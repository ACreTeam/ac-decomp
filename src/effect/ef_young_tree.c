#include "ef_effect_control.h"
#include "m_common_data.h"
#include "m_debug.h"
#include "m_rcp.h"
#include "sys_matrix.h"

static void eYoung_Tree_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eYoung_Tree_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eYoung_Tree_mv(eEC_Effect_c* effect, GAME* game);
static void eYoung_Tree_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_young_tree = {
    // clang-format off
    &eYoung_Tree_init,
    &eYoung_Tree_ct,
    &eYoung_Tree_mv,
    &eYoung_Tree_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eYoung_Tree_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_YOUNG_TREE, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eYoung_Tree_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    Camera2* camera = &play->camera;

    f32 dist = search_position_distance(&camera->lookat.eye, &camera->lookat.center);

    effect->scale.x = 0.010299999f;
    effect->scale.y = 0.0095f;
    effect->scale.z = 0.0095f;

    if (effect->arg0 == 2 || effect->arg0 == 1) {
        effect->velocity = ZeroVec;
        effect->velocity.y = 0.75f;
        effect->acceleration = ZeroVec;
        effect->acceleration.y = -0.05f;
        effect->timer = 40;
    } else if (effect->arg0 == 3) {
        effect->velocity = ZeroVec;
        effect->acceleration = ZeroVec;
        effect->timer = 14;
    } else {
        effect->velocity = ZeroVec;
        effect->acceleration = ZeroVec;
        effect->timer = 82;
    }
    effect->effect_specific[1] = 0;
    effect->effect_specific[2] = 0;

    xyz_t_sub(&camera->lookat.eye, &camera->lookat.center, &effect->offset);
    xyz_t_mult_v(&effect->offset, 1.0f / dist);
    effect->effect_specific[0] = Common_Get(time.season);
}

static void eYoung_Tree_mv(eEC_Effect_c* effect, GAME* game) {
    f32 fVar4;
    f32 dVar3;
    xyz_t effPos;
    xyz_t effPos2;
    s16 uVar2;

    xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
    xyz_t_add(&effect->position, &effect->velocity, &effect->position);
    if (effect->arg0 == 1) {
        effect->effect_specific[1] = effect->effect_specific[1] + 384;
    } else if (effect->arg0 == 2) {
        effect->effect_specific[1] = effect->effect_specific[1] - 384;
    } else {
        dVar3 = eEC_CLIP->calc_adjust_proc(effect->timer, 0, 0x28, 0.0f, 2184.0f);
        fVar4 = sin_s(effect->effect_specific[2]);

        effect->effect_specific[1] = dVar3 * fVar4;
        effect->effect_specific[2] = effect->effect_specific[2] + 0xC68;
        if ((effect->timer & 0x1F) == 0) {
            effPos = effect->position;
            if (Common_Get(time).term_idx == mTM_TERM_4) {
                uVar2 = 6;
            } else {
                uVar2 = 4;
            }

            if (effect->arg1 == 1) {
                uVar2 |= eEC_BUSH_HAPPA_PALM;
            } else if (effect->arg1 == 2) {
                uVar2 |= eEC_BUSH_HAPPA_CEDAR;
            } else if (effect->arg1 == 3) {
                uVar2 |= eEC_BUSH_HAPPA_PALM | eEC_BUSH_HAPPA_CEDAR;
            }

            effPos.x = effPos.x + fqrand2() * 30.0f;
            effPos.y = effPos.y + fqrand() * 30.0f;
            uVar2 |= 0x8000;

            eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_HAPPA, effPos, 2, 0, game, 0xFFFF, 0, uVar2);

            if (effect->effect_specific[0] == 3) {
                effPos2 = effect->position;
                effPos2.x = effPos2.x + fqrand2() * 30.0f;
                effPos2.y = effPos2.y + fqrand() * 30.0f;
                eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_YUKI, effPos2, 2, 0, game, 0xFFFF, 0, 0);
            }
        }
    }
}

extern Gfx ef_w_young_palm_modelT[];
extern Gfx ef_s_young_palm_modelT[];
extern Gfx ef_w_young_cedar_modelT[];
extern Gfx ef_s_young_cedar_modelT[];
extern Gfx ef_w_youngtree_00_modelT[];
extern Gfx ef_f_youngtree_00_modelT[];
extern Gfx ef_s_youngtree_00_modelT[];

static void eYoung_Tree_dw(eEC_Effect_c* effect, GAME* game) {
    GRAPH* graph;
    mFM_field_pal_c* field_pal = mFI_GetFieldPal();
    u16* cedar_pal = field_pal->cedar_tree_pal;
    u16* palm_pal = field_pal->palm_tree_pal;
    u16* golden_pal = field_pal->golden_tree_pal;
    s16 remain = 0x28 - effect->timer;
    u8 alpha;

    if (effect->arg0 == 2 || effect->arg0 == 1) {
        alpha = (int)eEC_CLIP->calc_adjust_proc(remain, 0, 0x28, 255.0f, 0.0f);
    } else {
        alpha = (int)eEC_CLIP->calc_adjust_proc(effect->timer, 0, 8, 0.0f, 255.0f);
    }

    graph = game->graph;
    _texture_z_light_fog_prim_xlu(graph);
    Matrix_translate(effect->position.x, effect->position.y + 3.0f, effect->position.z + 3.0f, 0);

    if (effect->arg1 == 0 || effect->arg1 == 3) {
        Matrix_RotateVector(effect->effect_specific[1], &effect->offset, 1);
    } else if (effect->arg1 == 1) {
        Matrix_translate(0.0f, (f32)GETREG(TAKREG, 20) + 5.0f, 0.0f, 1);
        Matrix_RotateVector(effect->effect_specific[1], &effect->offset, 1);
        Matrix_translate(0.0f, -5.0f - (f32)GETREG(TAKREG, 20), 0.0f, 1);
    } else {
        Matrix_translate(0.0f, 15.0f, 0.0f, 1);
        Matrix_RotateVector(effect->effect_specific[1], &effect->offset, 1);
        Matrix_translate(0.0f, -15.0f, 0.0f, 1);
    }
    Matrix_scale(effect->scale.x, effect->scale.y, effect->scale.z, 1);

    OPEN_DISP(graph);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if (effect->arg1 == 0) {
        gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, cedar_pal);
    } else if (effect->arg1 == 3) {
        gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, golden_pal);
    } else {
        gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, palm_pal);
    }

    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 255, alpha);
    gDPSetTextureAdjustMode(NEXT_POLY_XLU_DISP, G_TA_DOLPHIN);

    if (effect->arg1 == 1) {
        if (effect->effect_specific[0] == 3) {
            gSPDisplayList(NEXT_POLY_XLU_DISP, &ef_w_young_palm_modelT);
        } else {
            gSPDisplayList(NEXT_POLY_XLU_DISP, &ef_s_young_palm_modelT);
        }
    } else if (effect->arg1 == 2) {
        if (effect->effect_specific[0] == 3) {
            gSPDisplayList(NEXT_POLY_XLU_DISP, &ef_w_young_cedar_modelT);
        } else {
            gSPDisplayList(NEXT_POLY_XLU_DISP, &ef_s_young_cedar_modelT);
        }
    } else if (effect->effect_specific[0] == 3) {
        gSPDisplayList(NEXT_POLY_XLU_DISP, &ef_w_youngtree_00_modelT);
    } else if (Common_Get(time).term_idx == mTM_TERM_4) {
        gSPDisplayList(NEXT_POLY_XLU_DISP, &ef_f_youngtree_00_modelT);
    } else {
        gSPDisplayList(NEXT_POLY_XLU_DISP, &ef_s_youngtree_00_modelT);
    }

    gDPSetTextureAdjustMode(NEXT_POLY_XLU_DISP, G_TA_N64);
    CLOSE_DISP(graph);
}
