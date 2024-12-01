#include "ac_htable.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_malloc.h"
#include "libultra/libultra.h"

// clang-format off
static u8 aHTBL_shadow_vtx_fix_flg_tableA[] = {
    TRUE, TRUE, FALSE, FALSE,
    FALSE, TRUE, TRUE, TRUE,
    FALSE, FALSE, FALSE, TRUE,
    TRUE, TRUE, FALSE, FALSE,
    FALSE, TRUE, TRUE, TRUE,
    FALSE, FALSE, FALSE, TRUE,
    TRUE, TRUE, TRUE, TRUE,
};
// clang-format on

// clang-format off
static u8 aHTBL_shadow_vtx_fix_flg_tableB[] = {
    FALSE, TRUE, TRUE, FALSE,
    FALSE, TRUE, FALSE, TRUE,
    TRUE, FALSE, FALSE, TRUE,
    FALSE, TRUE, TRUE, FALSE,
    FALSE, TRUE, FALSE, TRUE,
    TRUE, FALSE, FALSE, TRUE,
    TRUE, TRUE, TRUE, TRUE,
};
// clang-format on

// clang-format off
static u8 aHTBL_shadow_vtx_fix_flg_tableC[] = {
    FALSE, TRUE, TRUE, FALSE,
    FALSE, TRUE, FALSE, TRUE,
    TRUE, FALSE, FALSE, TRUE,
    FALSE, TRUE, TRUE, FALSE,
    FALSE, TRUE, FALSE, TRUE,
    TRUE, FALSE, FALSE, TRUE,
    TRUE, TRUE, TRUE, TRUE,
};
// clang-format on

extern Vtx obj_e_hfes_shadow_a_v[];
extern Gfx obj_e_hfes_shadow_a_modelT[];

static bIT_ShadowData_c aHTBL_shadow_dataA = {
    ARRAY_COUNT(aHTBL_shadow_vtx_fix_flg_tableA),
    aHTBL_shadow_vtx_fix_flg_tableA,
    20.0f,
    obj_e_hfes_shadow_a_v,
    obj_e_hfes_shadow_a_modelT,
};

extern Vtx obj_e_hfes_shadow_b_v[];
extern Gfx obj_e_hfes_shadow_b_modelT[];

static bIT_ShadowData_c aHTBL_shadow_dataB = {
    ARRAY_COUNT(aHTBL_shadow_vtx_fix_flg_tableB),
    aHTBL_shadow_vtx_fix_flg_tableB,
    20.0f,
    obj_e_hfes_shadow_b_v,
    obj_e_hfes_shadow_b_modelT,
};

extern Vtx obj_e_hfes_shadow_c_v[];
extern Gfx obj_e_hfes_shadow_c_modelT[];

static bIT_ShadowData_c aHTBL_shadow_dataC = {
    ARRAY_COUNT(aHTBL_shadow_vtx_fix_flg_tableC),
    aHTBL_shadow_vtx_fix_flg_tableC,
    20.0f,
    obj_e_hfes_shadow_c_v,
    obj_e_hfes_shadow_c_modelT,
};

static bIT_ShadowData_c* aHTBL_shadow_data_table[] = {
    &aHTBL_shadow_dataA,
    &aHTBL_shadow_dataB,
    &aHTBL_shadow_dataC,
};

static void aHTBL_actor_ct(ACTOR* actorx, GAME* game);
static void aHTBL_actor_dt(ACTOR* actorx, GAME* game);
static void aHTBL_actor_init(ACTOR* actorx, GAME* game);
static void aHTBL_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Htable_Profile = {
    mAc_PROFILE_HTABLE,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    HTABLE0,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(HTABLE_ACTOR),
    &aHTBL_actor_ct,
    &aHTBL_actor_dt,
    &aHTBL_actor_init,
    &aHTBL_actor_draw,
    NULL,
};
// clang-format on

static void aHTBL_GetPlayerLookAtUnit(int* ux, int* uz, s16 angle_y, int chk_ofs) {
    // clang-format off
    static s16 unit_offset[][2] = {
        { 0, 1 }, // 0
        { 1, 1 }, // 22.5
        { 1, 1 }, // 45
        { 1, 0 }, // 67.5
        { 1, 0 }, // 90
        { 1, -1 }, // 112.5
        { 1, -1 }, // 135
        { 0, -1 }, // 157.5
        { 0, -1 }, // 180
        { -1, -1 }, // 202.5
        { -1, -1 }, // 225
        { -1, 0 }, // 247.5
        { -1, 0 }, // 270
        { -1, 1 }, // 292.5
        { -1, 1 }, // 315
        { 0, 1 }, // 337.5
    };
    // clang-format on

    static int high_offset[] = { 0, 2, -2 };
    int angle_idx = ((angle_y >> 12) & 0xF); // converts the full angle into steps of 0x1000 or 22.5 degrees

    if (chk_ofs >= 0 && chk_ofs < ARRAY_COUNT(high_offset)) {
        angle_idx = (angle_idx + high_offset[chk_ofs]) & 0xF;

        (*ux) += unit_offset[angle_idx][0];
        (*uz) += unit_offset[angle_idx][1];
    }
}

static mActor_name_t aHTBL_SearchPickUpItemLayer2(GAME* game) {
    ACTOR* player = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    int ux;
    int uz;
    xyz_t pos = player->world.position;
    xyz_t center_pos;
    s16 angle_y = player->shape_info.rotation.y;
    int i;

    if (mFI_Wpos2UtNum(&ux, &uz, pos)) {
        for (i = 0; i < 3; i++) {
            aHTBL_GetPlayerLookAtUnit(&ux, &uz, angle_y, i);
            if (mFI_UtNum2CenterWpos(&center_pos, ux, uz)) {
                f32 dx = center_pos.x - pos.x;
                f32 dz = center_pos.z - pos.z;

                if (SQ(dx) + SQ(dz) <= SQ(56.0f)) {
                    mActor_name_t* fg_p = mFI_GetUnitFG(center_pos);

                    if (fg_p != NULL && *fg_p == ITM_KNIFE_AND_FORK) {
                        return ITM_KNIFE_AND_FORK;
                    }
                }
            }
        }
    }

    return EMPTY_NO;
}

static void aHTBL_SetFork(HTABLE_ACTOR* htable) {
    int ux;
    int uz;

    if (mPr_GetPossessionItemIdxWithCond(Now_Private, ITM_KNIFE_AND_FORK, mPr_ITEM_COND_NORMAL) == -1) {
        if (mFI_Wpos2UtNum(&ux, &uz, htable->actor_class.world.position)) {
            mFI_UtNumtoFGSet_common(ITM_KNIFE_AND_FORK, ux + 1, uz + 1, TRUE);
        }
    }
}

static void aHTBL_SetClip(HTABLE_ACTOR* htable) {
    if (CLIP(htbl_clip) == NULL) {
        CLIP(htbl_clip) = (aHTBL_Clip_c*)zelda_malloc(sizeof(aHTBL_Clip_c));
        if (CLIP(htbl_clip) != NULL) {
            xyz_t pos = htable->actor_class.world.position;

            bzero(CLIP(htbl_clip), sizeof(aHTBL_Clip_c));
            pos.x += mFI_UT_WORLDSIZE_X_F;
            pos.z += mFI_UT_WORLDSIZE_Z_F;
            pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos(pos, 0.0f);
            CLIP(htbl_clip)->search_pick_up_item_layer2_proc = &aHTBL_SearchPickUpItemLayer2;
            CLIP(htbl_clip)->pickup_pos = pos;
        }
    }
}

static void aHTBL_set_bgOffset(HTABLE_ACTOR* htable);

static void aHTBL_actor_ct(ACTOR* actorx, GAME* game) {
    HTABLE_ACTOR* htable = (HTABLE_ACTOR*)actorx;

    htable->arg0 = actorx->npc_id - HTABLE0;
    aHTBL_set_bgOffset(htable);

    if (htable->arg0 == 2) {
        aHTBL_SetFork(htable);
        aHTBL_SetClip(htable);
        actorx->world.position.z += mFI_UT_WORLDSIZE_HALF_Z_F;
    }
}

static void aHTBL_actor_dt(ACTOR* actorx, GAME* game) {
    HTABLE_ACTOR* htable = (HTABLE_ACTOR*)actorx;

    if (htable->arg0 == 2 && CLIP(htbl_clip) != NULL) {
        zelda_free(CLIP(htbl_clip));
        CLIP(htbl_clip) = NULL;
    }
}

static void aHTBL_set_bgOffset(HTABLE_ACTOR* htable) {
    // clang-format off
    static const mCoBG_OffsetTable_c rewrite_dataA[] = {
        { mCoBG_ATTRIBUTE_NONE, 2, 0, 2, 2, 2, 1 },
        { mCoBG_ATTRIBUTE_NONE, 2, 2, 2, 2, 0, 1 },
        { mCoBG_ATTRIBUTE_NONE, 0, 0, 0, 0, 0, 0 },
        { mCoBG_ATTRIBUTE_NONE, 2, 2, 0, 2, 2, 1 },
        { mCoBG_ATTRIBUTE_NONE, 2, 2, 2, 2, 2, 0 },
        { mCoBG_ATTRIBUTE_NONE, 2, 2, 2, 2, 0, 1 },
        { mCoBG_ATTRIBUTE_NONE, 0, 0, 0, 0, 0, 0 },
        { mCoBG_ATTRIBUTE_NONE, 2, 2, 0, 2, 2, 1 },
        { mCoBG_ATTRIBUTE_NONE, 2, 2, 2, 0, 2, 1 },
    };
    // clang-format on

    // clang-format off
    static const mCoBG_OffsetTable_c rewrite_dataB[] = {
        { mCoBG_ATTRIBUTE_NONE, 0, 0, 0, 0, 0, 0 },
        { mCoBG_ATTRIBUTE_NONE, 2, 0, 2, 2, 2, 1 },
        { mCoBG_ATTRIBUTE_NONE, 2, 2, 2, 2, 0, 1 },
        { mCoBG_ATTRIBUTE_NONE, 2, 0, 2, 2, 2, 1 },
        { mCoBG_ATTRIBUTE_NONE, 2, 2, 2, 2, 2, 0 },
        { mCoBG_ATTRIBUTE_NONE, 2, 2, 2, 0, 2, 1 },
        { mCoBG_ATTRIBUTE_NONE, 2, 2, 0, 2, 2, 1 },
        { mCoBG_ATTRIBUTE_NONE, 2, 2, 2, 0, 2, 1 },
        { mCoBG_ATTRIBUTE_NONE, 0, 0, 0, 0, 0, 0 },
    };
    // clang-format on

    // clang-format off
    static const mCoBG_OffsetTable_c rewrite_dataC[] = {
        { mCoBG_ATTRIBUTE_NONE, 2, 2, 2, 2, 2, 0 },
    };
    // clang-format on

    int type = htable->arg0;
    int j;
    int i;
    int idx = 0;
    xyz_t pos;

    switch (type) {
        case 0:
            for (i = -1; i <= 1; i++) {
                for (j = -1; j <= 1; j++) {
                    pos = htable->actor_class.world.position;
                    pos.x += (f32)j * mFI_UT_WORLDSIZE_X_F;
                    pos.z += (f32)i * mFI_UT_WORLDSIZE_Z_F;
                    mCoBG_SetPluss5PointOffset_file(pos, rewrite_dataA[idx], __FILE__, 422);
                    idx++;
                }
            }
            break;
        case 1:
            for (i = -1; i <= 1; i++) {
                for (j = -1; j <= 1; j++) {
                    pos = htable->actor_class.world.position;
                    pos.x += (f32)j * mFI_UT_WORLDSIZE_X_F;
                    pos.z += (f32)i * mFI_UT_WORLDSIZE_Z_F;
                    mCoBG_SetPluss5PointOffset_file(pos, rewrite_dataB[idx], __FILE__, 436);
                    idx++;
                }
            }
            break;
        case 2:
            for (i = 0; i <= 1; i++) {
                for (j = -1; j <= 1; j++) {
                    pos = htable->actor_class.world.position;
                    pos.x += (f32)j * mFI_UT_WORLDSIZE_X_F;
                    pos.z += (f32)i * mFI_UT_WORLDSIZE_Z_F;
                    mCoBG_SetPluss5PointOffset_file(pos, rewrite_dataC[0], __FILE__, 450);
                }
            }
            break;
    }
}

static void aHTBL_actor_move(ACTOR* actorx, GAME* game) {
    if (CLIP(htbl_clip) != NULL && CLIP(htbl_clip)->pickup_counter != 0) {
        if (CLIP(htbl_clip)->pickup_counter == 1) {
            int ux;
            int uz;

            if (mFI_Wpos2UtNum(&ux, &uz, CLIP(htbl_clip)->pickup_pos)) {
                mFI_UtNumtoFGSet_common(RSV_NO, ux, uz, TRUE);
            }
        }

        CLIP(htbl_clip)->pickup_counter--;
    }
}

static void aHTBL_actor_init(ACTOR* actorx, GAME* game) {
    mFI_SetFG_common(DUMMY_HTABLE, actorx->home.position, FALSE);
    aHTBL_actor_move(actorx, game);
    actorx->mv_proc = &aHTBL_actor_move;
}

extern Gfx obj_e_hfes_a_model[];
extern Gfx obj_e_hfes_b_model[];
extern Gfx obj_e_hfes_c_model[];

extern Gfx obj_e_hfes_a_modelT[];
extern Gfx obj_e_hfes_b_modelT[];
extern Gfx obj_e_hfes_c_modelT[];

static Gfx* aHTBL_displaylist_table_opa[] = {
    obj_e_hfes_a_model,
    obj_e_hfes_b_model,
    obj_e_hfes_c_model,
};

static Gfx* aHTBL_displaylist_table_xlu[] = {
    obj_e_hfes_a_modelT,
    obj_e_hfes_b_modelT,
    obj_e_hfes_c_modelT,
};

static void aHTBL_actor_draw(ACTOR* actorx, GAME* game) {
    GRAPH* graph = game->graph;
    HTABLE_ACTOR* htable = (HTABLE_ACTOR*)actorx;
    int type = htable->arg0;

    _texture_z_light_fog_prim_npc(graph);
    _texture_z_light_fog_prim_xlu(graph);
    _texture_z_light_fog_prim_shadow(graph);

    OPEN_DISP(graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_OPA_DISP, aHTBL_displaylist_table_opa[type]);
    gSPDisplayList(NEXT_POLY_XLU_DISP, aHTBL_displaylist_table_xlu[type]);

    CLOSE_DISP(graph);

    CLIP(bg_item_clip)->draw_shadow_proc(game, aHTBL_shadow_data_table[type], TRUE);
}
