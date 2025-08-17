#include "ac_shop_goods.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "ac_my_room.h"
#include "m_malloc.h"

static void Shop_Goods_Actor_ct(ACTOR* actorx, GAME* game);
static void Shop_Goods_Actor_dt(ACTOR* actorx, GAME* game);
static void Shop_Goods_Actor_move(ACTOR* actorx, GAME* game);
static void Shop_Goods_Actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Shop_Goods_Profile = {
    mAc_PROFILE_SHOP_GOODS,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_SHOP_GOODS,
    sizeof(SHOP_GOODS_ACTOR),
    &Shop_Goods_Actor_ct,
    &Shop_Goods_Actor_dt,
    &Shop_Goods_Actor_move,
    &Shop_Goods_Actor_draw,
    NULL,
};
// clang-format on

#define aSG_DATA_ROTATE_Y_FLAG (1 << 0)

#include "../src/actor/ac_shop_goods_data.c_inc"

#define aSG_SCALE_FLAG (1 << 0)

static s16 SG_angle_y[UT_Z_NUM][UT_X_NUM];
static SHOP_GOODS_ACTOR* Glb_shop_goods_actor;
static int picture_count;
static s16 mode;

static s16 Shop_Goods_Actor_single_get_angle_y(int ut_z, int ut_x, int layer) {
    if (layer == mCoBG_LAYER1) {
        return SG_angle_y[ut_z][ut_x];
    }

    return 0;
}

static void Shop_Goods_Actor_single_set_angle_y(int ut_z, int ut_x, int layer, s16 angle_y) {
    if (layer == mCoBG_LAYER1) {
        SG_angle_y[ut_z][ut_x] = angle_y;
    }
}

static void Shop_Goods_draw_ta_set(GAME* game) {
    OPEN_DISP(game->graph);

    gDPSetTextureAdjustMode(NEXT_POLY_OPA_DISP, G_TA_DOLPHIN);
    gDPSetTextureAdjustMode(NEXT_POLY_XLU_DISP, G_TA_DOLPHIN);

    CLOSE_DISP(game->graph);
}

static void Shop_Goods_draw_ta_clr(GAME* game) {
    OPEN_DISP(game->graph);

    gDPSetTextureAdjustMode(NEXT_POLY_OPA_DISP, G_TA_N64);
    gDPSetTextureAdjustMode(NEXT_POLY_XLU_DISP, G_TA_N64);

    CLOSE_DISP(game->graph);
}

static int Shop_Goods_Actor_drop_entry(SHOP_GOODS_ACTOR* shop_goods, mActor_name_t item, xyz_t* now_pos,
                                       xyz_t* target_pos, s16 layer, int timer, u16 flags);

static int Shop_Goods_Actor_player_drop_entry(GAME* game, mActor_name_t item, int ut_x, int ut_z, int layer,
                                              int delay_timer) {
    ACTOR* player_actor = GET_PLAYER_ACTOR_GAME_ACTOR(game);
    int res = 0;
    xyz_t now_pos;
    xyz_t target_pos;
    mActor_name_t* fg_p;

    target_pos.x = 0.0f;
    target_pos.y = 0.0f;
    target_pos.z = 0.0f;

    mFI_UtNum2CenterWpos(&target_pos, ut_x, ut_z);

    if (layer == mCoBG_LAYER0) {
        target_pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(target_pos, -1.0f);
    } else {
        target_pos.y = mCoBG_GetBgY_AngleS_FromWpos(NULL, target_pos, -1.0f);
    }

    if (layer == mCoBG_LAYER0) {
        fg_p = mFI_GetUnitFG(target_pos);
    } else {
        fg_p = mFI_GetUnitFG2(target_pos);
    }

    if (*fg_p == EMPTY_NO) {
        xyz_t_move(&now_pos, &player_actor->world.position);
        now_pos.y += 50.0f;

        if (Shop_Goods_Actor_drop_entry(Glb_shop_goods_actor, item, &now_pos, &target_pos, layer, delay_timer, 1)) {
            if (layer == mCoBG_LAYER0) {
                mFI_SetFG_common(RSV_NO, target_pos, FALSE);
            } else {
                mFI_SetFG2(RSV_NO, target_pos);
            }

            if (layer == mCoBG_LAYER1) {
                SG_angle_y[ut_z][ut_x] = 0;
            }

            res = 1;
            aMR_ThrowItem_FurnitureLock();
        }
    } else {
        res = -1;
    }

    return res;
}

static int Shop_Goods_Actor_drop_entry(SHOP_GOODS_ACTOR* shop_goods, mActor_name_t item, xyz_t* now_pos,
                                       xyz_t* target_pos, s16 layer, int delay_timer, u16 flags) {
    aSG_single_draw_c* single_draw_p = shop_goods->single_draw;
    int i;
    f32 dist_xz;
    f32 dist_y;
    int res = FALSE;

    for (i = 0; i < aSG_SINGLE_DRAW_NUM; i++) {
        if (single_draw_p->counter == 0) {
            xyz_t_move(&single_draw_p->start_pos, now_pos);
            xyz_t_move(&single_draw_p->current_pos, now_pos);
            xyz_t_move(&single_draw_p->target_pos, target_pos);
            single_draw_p->item = item;
            single_draw_p->layer = layer;
            single_draw_p->angle.y = search_position_angleY(&single_draw_p->current_pos, &single_draw_p->target_pos);
            single_draw_p->flags = flags;
            single_draw_p->acceleration_y = -1.2f;
            single_draw_p->counter = 1;
            single_draw_p->_40 = 0;
            single_draw_p->delay_timer = delay_timer;

            if ((flags & 1)) {
                single_draw_p->scale = 0.0f;
            } else {
                single_draw_p->scale = 1.0f;
            }

            dist_xz = search_position_distanceXZ(&single_draw_p->target_pos, &single_draw_p->current_pos);
            dist_y = single_draw_p->target_pos.y - single_draw_p->current_pos.y;
            if (dist_xz != 0.0f) {
                f32 tmp =
                    ((single_draw_p->acceleration_y * 0.5f) + (single_draw_p->acceleration_y * 0.5f) * 28.0f) * 14.0f;

                single_draw_p->velocity_y = (dist_y - tmp) / 28.0f;
            } else {
                single_draw_p->velocity_y = 0.0f;
            }

            res = TRUE;
            break;
        }

        single_draw_p++;
    }

    return res;
}

static void Shop_Goods_Actor_drop_destruct(SHOP_GOODS_ACTOR* shop_goods) {
    int i;
    aSG_single_draw_c* single_draw_p = shop_goods->single_draw;

    for (i = 0; i < aSG_SINGLE_DRAW_NUM; i++) {
        if (single_draw_p->counter != 0) {
            if (single_draw_p->layer == mCoBG_LAYER0) {
                mFI_SetFG_common(single_draw_p->item, single_draw_p->target_pos, FALSE);
            } else {
                mFI_SetFG2(single_draw_p->item, single_draw_p->target_pos);
            }
        }

        single_draw_p++;
    }
}

static void Shop_Goods_Actor_drop_move(SHOP_GOODS_ACTOR* shop_goods) {
    int i;
    aSG_single_draw_c* single_draw_p = shop_goods->single_draw;

    for (i = 0; i < aSG_SINGLE_DRAW_NUM; i++, single_draw_p++) {
        if (single_draw_p->delay_timer > 0) {
            single_draw_p->delay_timer--;
            continue;
        }

        if (single_draw_p->counter != 0) {
            f32 percent_xz = (f32)single_draw_p->counter * (1.0f / 30.0f);

            if (percent_xz > 1.0f) {
                percent_xz = 1.0f;
            } else {
                percent_xz = percent_xz;
            }

            single_draw_p->velocity_y += single_draw_p->acceleration_y * 0.5f;
            single_draw_p->current_pos.y += single_draw_p->velocity_y * 0.5f;
            single_draw_p->current_pos.x =
                single_draw_p->start_pos.x + percent_xz * (single_draw_p->target_pos.x - single_draw_p->start_pos.x);
            single_draw_p->current_pos.z =
                single_draw_p->start_pos.z + percent_xz * (single_draw_p->target_pos.z - single_draw_p->start_pos.z);

            if ((single_draw_p->flags & aSG_SCALE_FLAG)) {
                single_draw_p->scale = 0.1f + (1.0f - SQ(1.0f - (f32)single_draw_p->counter / 28.0f)) * 0.9f;
            }

            if (single_draw_p->counter == 27) {
                if (single_draw_p->item == ITM_FOOD_APPLE || single_draw_p->item == ITM_FOOD_CHERRY ||
                    single_draw_p->item == ITM_FOOD_PEAR || single_draw_p->item == ITM_FOOD_PEACH ||
                    single_draw_p->item == ITM_FOOD_ORANGE) {
                    sAdo_OngenTrgStart(0x127, &single_draw_p->current_pos);
                } else if (single_draw_p->item == ITM_MONEY_1000 || single_draw_p->item == ITM_MONEY_10000 ||
                           single_draw_p->item == ITM_MONEY_30000 || single_draw_p->item == ITM_MONEY_100) {
                    sAdo_OngenTrgStart(0x444, &single_draw_p->current_pos);
                } else {
                    sAdo_OngenTrgStart(0x128, &single_draw_p->current_pos);
                }
            }

            if (single_draw_p->current_pos.y <= single_draw_p->target_pos.y) {
                if (single_draw_p->_40 == 0) {
                    single_draw_p->flags &= ~aSG_SCALE_FLAG;
                    single_draw_p->scale = 1.0f;
                    xyz_t_move(&single_draw_p->current_pos, &single_draw_p->target_pos);
                    single_draw_p->velocity_y = -single_draw_p->velocity_y * 0.25f;
                    single_draw_p->_40++;
                    if (single_draw_p->velocity_y > 3.0f) {
                        single_draw_p->velocity_y = 3.0f;
                    }
                } else {
                    if (single_draw_p->layer == mCoBG_LAYER0) {
                        mFI_SetFG_common(single_draw_p->item, single_draw_p->target_pos, FALSE);
                    } else {
                        mFI_SetFG2(single_draw_p->item, single_draw_p->target_pos);
                    }

                    single_draw_p->counter = 0;
                    aMR_ThrowItem_FurnitureUnlock();
                }
            } else {
                single_draw_p->counter++;
            }
        }
    }
}

static void Shop_Goods_Actor_single_drawR(GAME* game, mActor_name_t item, xyz_t* pos, xyz_t* scale, s16 angle_y,
                                          int layer) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    const aSG_data_c* src_data_p = l_shop_goods_dsp_table;
    int i;

    for (i = 0; i < picture_count; i++) {
        const aSG_data_c* data_p = &src_data_p[i];
        // Global_light* glight = &((GAME_PLAY*)game)->global_light;
        LightsN* lightsN;

        if (item >= data_p->item_start && item <= data_p->item_end) {
            const aSG_data_c* data_p = &src_data_p[i];
            int xlu_flag = data_p->xlu_gfx0[mode] != NULL;
            GRAPH* graph;

            if (xlu_flag) {
                _texture_z_light_fog_prim_xlu(game->graph);
            }

            _texture_z_light_fog_prim(game->graph);

            graph = play->game.graph;
            OPEN_DISP(graph);

            lightsN = Global_light_read(&play->global_light, graph);
            LightsN_list_check(lightsN, play->global_light.list, pos);
            LightsN_disp(lightsN, play->game.graph);

            Matrix_translate(pos->x, pos->y, pos->z, MTX_LOAD);
            if ((data_p->flags & aSG_DATA_ROTATE_Y_FLAG) && layer == mCoBG_LAYER1) {
                Matrix_RotateY(angle_y, MTX_MULT);
            }
            Matrix_scale(scale->x, scale->y, scale->z, MTX_MULT);

            gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(NEXT_POLY_OPA_DISP, data_p->gfx0[mode]);

            if (data_p->gfx1[mode] != NULL) {
                gSPDisplayList(NEXT_POLY_OPA_DISP, data_p->gfx1[mode]);
            }

            if (xlu_flag != FALSE) {
                gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(NEXT_POLY_XLU_DISP, data_p->xlu_gfx0[mode]);

                if (data_p->xlu_gfx1[mode] != NULL) {
                    gSPDisplayList(NEXT_POLY_XLU_DISP, data_p->xlu_gfx1[mode]);
                }
            }

            CLOSE_DISP(graph);
            return;
        }
    }
}

static void Shop_Goods_Actor_single_draw(GAME* game, mActor_name_t item, xyz_t* pos, f32 scale, s16 angle_y,
                                         int layer) {
    xyz_t xyz_scale;

    Shop_Goods_draw_ta_set(game);
    xyz_scale.x = scale;
    xyz_scale.y = scale;
    xyz_scale.z = scale;
    Shop_Goods_Actor_single_drawR(game, item, pos, &xyz_scale, angle_y, layer);
    Shop_Goods_draw_ta_clr(game);
}

static void Shop_Goods_Actor_drop_draw(ACTOR* actorx, GAME* game) {
    SHOP_GOODS_ACTOR* shop_goods = (SHOP_GOODS_ACTOR*)actorx;
    int i;
    aSG_single_draw_c* single_draw_p = shop_goods->single_draw;

    for (i = 0; i < aSG_SINGLE_DRAW_NUM; i++) {
        if (single_draw_p->counter != 0) {
            int ut_x;
            int ut_z;
            s16 angle_y;

            if (mFI_Wpos2UtNum(&ut_x, &ut_z, single_draw_p->target_pos)) {
                angle_y = SG_angle_y[ut_z][ut_x];
            } else {
                angle_y = 0;
            }

            Shop_Goods_Actor_single_draw(game, single_draw_p->item, &single_draw_p->current_pos,
                                         single_draw_p->scale * 0.01f, angle_y, single_draw_p->layer);
        }

        single_draw_p++;
    }
}

static int aSG_CountPictureKind(void) {
    const aSG_data_c* data_p = l_shop_goods_dsp_table;
    int count = 0;

    for (data_p; data_p->item_start != EMPTY_NO || data_p->item_end != EMPTY_NO; data_p++) {
        count++;
    }

    return count;
}

static void Shop_Goods_Actor_ct(ACTOR* actorx, GAME* game) {
    SHOP_GOODS_ACTOR* shop_goods = (SHOP_GOODS_ACTOR*)actorx;
    int i;

    shop_goods->picture_count = aSG_CountPictureKind();
    picture_count = shop_goods->picture_count;

    mFI_Wpos2BlockNum(&shop_goods->bx, &shop_goods->bz, actorx->world.position);
    shop_goods->bx_pos = (f32)shop_goods->bx * mFI_BK_WORLDSIZE_X_F;
    shop_goods->bz_pos = (f32)shop_goods->bz * mFI_BK_WORLDSIZE_Z_F;

    shop_goods->mode = actorx->actor_specific;
    mode = shop_goods->mode;

    for (i = 0; i < aSG_SINGLE_DRAW_NUM; i++) {
        shop_goods->single_draw[i].counter = 0;
    }

    Glb_shop_goods_actor = shop_goods;

    if (Common_Get(clip).shop_goods_clip == NULL) {
        Common_Get(clip).shop_goods_clip = (aSG_Clip_c*)zelda_malloc(sizeof(aSG_Clip_c));
        Common_Get(clip).shop_goods_clip->single_draw_proc = &Shop_Goods_Actor_single_draw;
        Common_Get(clip).shop_goods_clip->player_drop_entry_proc = &Shop_Goods_Actor_player_drop_entry;
        Common_Get(clip).shop_goods_clip->single_get_angle_y_proc = &Shop_Goods_Actor_single_get_angle_y;
        Common_Get(clip).shop_goods_clip->single_set_angle_y_proc = &Shop_Goods_Actor_single_set_angle_y;
    }
}

static void Shop_Goods_Actor_dt(ACTOR* actorx, GAME* game) {
    SHOP_GOODS_ACTOR* shop_goods = (SHOP_GOODS_ACTOR*)actorx;

    Shop_Goods_Actor_drop_destruct(shop_goods);
    if (Common_Get(clip).shop_goods_clip != NULL) {
        zelda_free(Common_Get(clip).shop_goods_clip);
/* @BUG - shouldn't shop_goods_clip get set to NULL? */
#ifdef BUGFIXES
        Common_Get(clip).shop_goods_clip = NULL;
#endif
    }
}

static void Shop_Goods_Actor_move(ACTOR* actorx, GAME* game) {
    SHOP_GOODS_ACTOR* shop_goods = (SHOP_GOODS_ACTOR*)actorx;

    Shop_Goods_Actor_drop_move(shop_goods);
}

static void aSG_DrawGoods(GRAPH* graph, Global_light* glight, SHOP_GOODS_ACTOR* shop_goods, int bx, int bz, int ux,
                          int uz, const aSG_data_c* data_p, int layer) {
    xyz_t pos;
    int mode = shop_goods->mode;
    Gfx* gfx0 = data_p->gfx0[mode];
    Gfx* gfx1 = data_p->gfx1[mode];
    Gfx* xlu_gfx0 = data_p->xlu_gfx0[mode];
    Gfx* xlu_gfx1 = data_p->xlu_gfx1[mode];
    LightsN* lightsN;

    mFI_BkandUtNum2CenterWpos(&pos, bx, bz, ux, uz);
    if (layer == mCoBG_LAYER0) {
        pos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(pos, 0.0f);
    } else {
        pos.y = mCoBG_GetBgY_AngleS_FromWpos(NULL, pos, 0.0f);
    }

    OPEN_DISP(graph);

    lightsN = Global_light_read(glight, graph);
    LightsN_list_check(lightsN, glight->list, &pos);
    LightsN_disp(lightsN, graph);

    if (gfx0 != NULL || xlu_gfx0 != NULL) {
        Matrix_translate(pos.x, pos.y, pos.z, MTX_LOAD);
        if ((data_p->flags & aSG_DATA_ROTATE_Y_FLAG) && layer == mCoBG_LAYER1) {
            Matrix_RotateY(SG_angle_y[uz][ux], MTX_MULT);
        }
        Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);

        if (gfx0 != NULL) {
            _texture_z_light_fog_prim(graph);

            gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(NEXT_POLY_OPA_DISP, gfx0);

            if (gfx1 != NULL) {
                gSPDisplayList(NEXT_POLY_OPA_DISP, gfx1);
            }
        }

        if (xlu_gfx0 != NULL) {
            _texture_z_light_fog_prim_xlu(graph);
            gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(NEXT_POLY_XLU_DISP, xlu_gfx0);

            if (xlu_gfx1 != NULL) {
                gSPDisplayList(NEXT_POLY_XLU_DISP, xlu_gfx1);
            }
        }
    }

    CLOSE_DISP(graph);
}

static void aSG_DrawGoodsPicture(ACTOR* actorx, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    Global_light* glight = &play->global_light;
    SHOP_GOODS_ACTOR* shop_goods = (SHOP_GOODS_ACTOR*)actorx;
    const aSG_data_c* data_p = l_shop_goods_dsp_table;
    int picture_count = shop_goods->picture_count;
    int bx = shop_goods->bx;
    int bz = shop_goods->bz;
    mActor_name_t* fg_p = mFI_BkNumtoUtFGTop(bx, bz);
    mActor_name_t* fg2_p = mFI_BkNum2UtFGTop_layer(bx, bz, mCoBG_LAYER1);
    s16 mode = shop_goods->mode;
    int ux;
    int uz;
    int i;

    if (fg_p != NULL) {
        for (uz = 0; uz < UT_Z_NUM; uz++) {
            for (ux = 0; ux < UT_X_NUM; ux++) {
                if (*fg_p != RSV_NO) {
                    for (i = 0; i < picture_count; i++) {
                        if (*fg_p >= data_p[i].item_start && *fg_p <= data_p[i].item_end) {
                            aSG_DrawGoods(game->graph, glight, shop_goods, bx, bz, ux, uz, &data_p[i], mCoBG_LAYER0);
                            break;
                        }
                    }
                }

                fg_p++;
            }
        }
    }

    if (mode == 1 && fg2_p != NULL) {
        for (uz = 0; uz < UT_Z_NUM; uz++) {
            for (ux = 0; ux < UT_X_NUM; ux++) {
                if (*fg2_p != RSV_NO) {
                    for (i = 0; i < picture_count; i++) {
                        if (*fg2_p >= data_p[i].item_start && *fg2_p <= data_p[i].item_end) {
                            aSG_DrawGoods(game->graph, glight, shop_goods, bx, bz, ux, uz, &data_p[i], mCoBG_LAYER1);
                            break;
                        }
                    }
                }

                fg2_p++;
            }
        }
    }
}

static void Shop_Goods_Actor_draw(ACTOR* actorx, GAME* game) {
    _texture_z_light_fog_prim(game->graph);
    Shop_Goods_draw_ta_set(game);
    aSG_DrawGoodsPicture(actorx, game);
    Shop_Goods_draw_ta_clr(game);
    Shop_Goods_Actor_drop_draw(actorx, game);
}
