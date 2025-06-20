#include "ac_shop_manekin.h"

#include "m_common_data.h"
#include "m_malloc.h"
#include "m_player_lib.h"
#include "m_rcp.h"
#include "sys_matrix.h"

static void Shop_Manekin_Actor_ct(ACTOR* actorx, GAME* game);
static void Shop_Manekin_Actor_dt(ACTOR* actorx, GAME* game);
static void Shop_Manekin_Actor_move(ACTOR* actorx, GAME* game);
static void Shop_Manekin_Actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Shop_Manekin_Profile = {
    mAc_PROFILE_SHOP_MANEKIN,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(SHOP_MANEKIN_ACTOR),
    &Shop_Manekin_Actor_ct,
    &Shop_Manekin_Actor_dt,
    &Shop_Manekin_Actor_move,
    &Shop_Manekin_Actor_draw,
    NULL,
};
// clang-format on

static int aSM_CountCurrentBlockManekin(xyz_t pos) {
    int ux;
    int uz;
    int bx;
    int bz;
    mActor_name_t* fg_p;
    int i;
    int count;

    ux = mFI_WposX2UtNumX(pos.x);
    // @BUG - they're calling the wrong function here, should be the Z coordinate variant.
    // Effectively harmless since x & z are equivalent in GC, but a bug nonetheless.
#ifndef BUGFIXES
    uz = mFI_WposX2UtNumX(pos.z);
#else
    uz = mFI_WposZ2UtNumZ(pos.z);
#endif
    bx = ux / UT_X_NUM;
    bz = uz / UT_Z_NUM;
    fg_p = mFI_BkNumtoUtFGTop(bx, bz);

    count = 0;
    for (i = 0; i < UT_TOTAL_NUM; i++) {
        if (ITEM_IS_CLOTH(*fg_p) || *fg_p == RSV_SHOP_SOLD_CLOTH) {
            count++;
        }

        fg_p++;
    }

    return count;
}

static u8* aSM_SucureBank(size_t size, GAME* game) {
    return (u8*)zelda_malloc_align(size, 32);
}

static int aSM_SecureManakinBank(ACTOR* actorx, GAME* game) {
    SHOP_MANEKIN_ACTOR* shop_manekin = (SHOP_MANEKIN_ACTOR*)actorx;
    int count = shop_manekin->current_block_manekin_num;
    MANEKIN_ACTOR* manekin = shop_manekin->manekin_actors;
    int i;
    u8* tex_p;
    u8* pal_p;
    u32 size;

    size = (count + 1) * mNW_DESIGN_TEX_SIZE;
    tex_p = aSM_SucureBank(size, game);
    if (tex_p == NULL) {
        return FALSE;
    }

    for (i = 0; i < count; i++) {
        manekin[i].tex_p = tex_p + (i * mNW_DESIGN_TEX_SIZE);
    }
    shop_manekin->naked_tex_p = tex_p + (count * mNW_DESIGN_TEX_SIZE);

    size = (count + 1) * mNW_PALETTE_SIZE;
    pal_p = aSM_SucureBank(size, game);
    if (pal_p == NULL) {
        return FALSE;
    }

    // wtf is going on here, is this fakematch?
    for (i = 0; i < count; i++, pal_p++) {
        manekin[i].palette_p = pal_p-- + (i * mNW_PALETTE_SIZE);
    }
    shop_manekin->naked_pal_p = pal_p + (count * mNW_PALETTE_SIZE);

    return TRUE;
}

static void aSM_SearchManekinPlace(int* ux, int* uz, mActor_name_t* item, int idx, int bx, int bz) {
    mActor_name_t* fg_p = mFI_BkNumtoUtFGTop(bx, bz);
    int count = 0;
    int i;

    *ux = 0;
    *uz = 0;
    for (i = 0; i < UT_TOTAL_NUM; i++) {
        if (ITEM_IS_CLOTH(fg_p[i]) || fg_p[i] == RSV_SHOP_SOLD_CLOTH) {
            if (count == idx) {
                *ux = i % UT_X_NUM;
                *uz = i / UT_X_NUM;
                *item = fg_p[i];
                break;
            }

            count++;
        }
    }
}

static mCoBG_bg_size_c l_manekin_mBgData = { 16.0f, 16.0f, 16.0f, 16.0f };

static void aSM_ManekinCt(ACTOR* actorx) {
    SHOP_MANEKIN_ACTOR* shop_manekin = (SHOP_MANEKIN_ACTOR*)actorx;
    int bx = shop_manekin->now_block_x;
    int bz = shop_manekin->now_block_z;
    static s16 angle_y = 0;

    if (shop_manekin->manekin_actors != NULL) {
        MANEKIN_ACTOR* manekin = shop_manekin->manekin_actors;
        int count = shop_manekin->current_block_manekin_num;
        int i;

        for (i = 0; i < count; i++) {
            int* ux_p = &manekin->ut_x;
            int* uz_p = &manekin->ut_z;

            manekin->naked = FALSE;
            manekin->tex_p = NULL;
            manekin->palette_p = NULL;
            aSM_SearchManekinPlace(ux_p, uz_p, &manekin->item, i, bx, bz);
            if (manekin->item == RSV_SHOP_SOLD_CLOTH) {
                manekin->item = ITM_CLOTH_START;
                manekin->naked = TRUE;
            }

            manekin->wpos.x = bx * mFI_BK_WORLDSIZE_X_F + (*ux_p) * mFI_UT_WORLDSIZE_X_F + mFI_UT_WORLDSIZE_HALF_X_F;
            manekin->wpos.y = 0.0f;
            manekin->wpos.z = bz * mFI_BK_WORLDSIZE_Z_F + (*uz_p) * mFI_UT_WORLDSIZE_Z_F + mFI_UT_WORLDSIZE_HALF_Z_F;
            manekin->wpos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(manekin->wpos, 0.0f);
            manekin->move_bg_num = mCoBG_RegistMoveBg(&manekin->bg_regist, &manekin->wpos, NULL, &angle_y, 40.0f, &l_manekin_mBgData, NULL, NULL, NULL, mCoBG_FTR_TYPE_NUM, mCoBG_ATTRIBUTE_STONE, 40.0f);
            manekin++;
        }
    }
}

static void aSM_SecureManekinSubActor(ACTOR* actorx) {
    SHOP_MANEKIN_ACTOR* shop_manekin = (SHOP_MANEKIN_ACTOR*)actorx;
    int count = shop_manekin->current_block_manekin_num;
    size_t size = sizeof(MANEKIN_ACTOR);
    size_t aligned_size = ALIGN_NEXT(size, 8);

    shop_manekin->manekin_actors = NULL;
    shop_manekin->manekin_actors = (MANEKIN_ACTOR*)zelda_malloc(count * aligned_size);
    if (shop_manekin->manekin_actors != NULL) {
        aSM_ManekinCt(actorx);
    }
}

static void aSM_GetNowBlockNumber(ACTOR* actorx) {
    SHOP_MANEKIN_ACTOR* shop_manekin = (SHOP_MANEKIN_ACTOR*)actorx;
    xyz_t pos = actorx->world.position;
    int ux = mFI_WposX2UtNumX(pos.x);
    int uz = mFI_WposX2UtNumX(pos.z); // @BUG - again, using X instead of Z

    shop_manekin->now_block_x = ux / UT_X_NUM;
    shop_manekin->now_block_z = uz / UT_Z_NUM;
}

static void aSM_DmaManekinTexPal(ACTOR* actorx) {
    SHOP_MANEKIN_ACTOR* shop_manekin = (SHOP_MANEKIN_ACTOR*)actorx;
    MANEKIN_ACTOR* manekin = shop_manekin->manekin_actors;
    int count = shop_manekin->current_block_manekin_num;
    int i;

    if (manekin != NULL) {
        for (i = 0; i < count; i++) {
            u8* tex_p = manekin[i].tex_p;
            u8* pal_p = manekin[i].palette_p;
            int idx = ITEM_IS_CLOTH(manekin[i].item) != FALSE ? (manekin[i].item - ITM_CLOTH_START) : 0;

            mPlib_Load_PlayerTexAndPallet(tex_p, pal_p, idx);
        }
    }

    mPlib_Load_PlayerTexAndPallet(shop_manekin->naked_tex_p, shop_manekin->naked_pal_p, ITM_CLOTH_MANEKIN - ITM_CLOTH_START);
}

static void aSM_ManekinDmaAgain(void);
static void aSM_Change2NakedManekin(int ux, int uz);
static void aSM_Naked2Cloth(int ux, int uz);

static void aSM_SetClipProc(ACTOR* actorx, int free) {
    if (free) {
        CLIP(shop_manekin_clip) = NULL;
    } else {
        SHOP_MANEKIN_ACTOR* shop_manekin = (SHOP_MANEKIN_ACTOR*)actorx;
        aSM_Clip_c* clip = &shop_manekin->clip;

        CLIP(shop_manekin_clip) = clip;
        clip->shop_manekin_actor_p = actorx;
        clip->manekin_dma_again_proc = &aSM_ManekinDmaAgain;
        clip->change2naked_manekin_proc = &aSM_Change2NakedManekin;
        clip->naked2cloth_proc = &aSM_Naked2Cloth;
    }
}

static void Shop_Manekin_Actor_ct(ACTOR* actorx, GAME* game) {
    SHOP_MANEKIN_ACTOR* shop_manekin = (SHOP_MANEKIN_ACTOR*)actorx;

    shop_manekin->naked_tex_p = NULL;
    shop_manekin->naked_pal_p = NULL;
    aSM_GetNowBlockNumber(actorx);
    shop_manekin->current_block_manekin_num = aSM_CountCurrentBlockManekin(actorx->world.position);
    aSM_SecureManekinSubActor(actorx);
    aSM_SecureManakinBank(actorx, game);
    aSM_DmaManekinTexPal(actorx);
    aSM_SetClipProc(actorx, FALSE);
}

static void Shop_Manekin_Actor_dt(ACTOR* actorx, GAME* game) {
    SHOP_MANEKIN_ACTOR* shop_manekin = (SHOP_MANEKIN_ACTOR*)actorx;
    int count = shop_manekin->current_block_manekin_num;
    MANEKIN_ACTOR* manekin = shop_manekin->manekin_actors;
    int i;

    for (i = 0; i < count; i++) {
        mCoBG_CrossOffMoveBg(manekin[i].move_bg_num);
    }

    if (shop_manekin->manekin_actors != NULL) {
        zelda_free(shop_manekin->manekin_actors);
    }

    aSM_SetClipProc(actorx, TRUE);
}

extern Gfx obj_shop_manekin_model[];

static void Shop_Manekin_Actor_draw(ACTOR* actorx, GAME* game) {
    SHOP_MANEKIN_ACTOR* shop_manekin = (SHOP_MANEKIN_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    int count = shop_manekin->current_block_manekin_num;
    MANEKIN_ACTOR* manekin = shop_manekin->manekin_actors;
    LightsN* lights;
    int i;

    if (manekin != NULL) {
        for (i = 0; i < count; i++) {
            xyz_t pos = manekin[i].wpos;

            OPEN_DISP(game->graph);

            _texture_z_light_fog_prim(game->graph);
            Matrix_translate(pos.x, pos.y, pos.z, MTX_LOAD);
            Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);
            lights = Global_light_read(&play->global_light, game->graph);
            LightsN_list_check(lights, play->global_light.list, &pos);
            LightsN_disp(lights, game->graph);

            if (manekin[i].naked) {
                gSPSegment(NEXT_POLY_OPA_DISP, ANIME_1_TXT_SEG, shop_manekin->naked_tex_p);
                gSPSegment(NEXT_POLY_OPA_DISP, ANIME_2_TXT_SEG, shop_manekin->naked_pal_p);
            } else {
                gSPSegment(NEXT_POLY_OPA_DISP, ANIME_1_TXT_SEG, manekin[i].tex_p);
                gSPSegment(NEXT_POLY_OPA_DISP, ANIME_2_TXT_SEG, manekin[i].palette_p);
            }

            gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_LOAD | G_MTX_NOPUSH);
            gSPDisplayList(NEXT_POLY_OPA_DISP, obj_shop_manekin_model);

            CLOSE_DISP(game->graph);
        }
    }
}

static void Shop_Manekin_Actor_move(ACTOR* actorx, GAME* game) {
    // nothing
}

static void aSM_ManekinDmaAgain(void) {
    if (CLIP(shop_manekin_clip) != NULL) {
        ACTOR* actorx = CLIP(shop_manekin_clip)->shop_manekin_actor_p;

        if (actorx != NULL) {
            SHOP_MANEKIN_ACTOR* shop_manekin = (SHOP_MANEKIN_ACTOR*)actorx;
            int count = shop_manekin->current_block_manekin_num;
            MANEKIN_ACTOR* manekin = shop_manekin->manekin_actors;
            int i;

            for (i = 0; i < count; i++) {
                u8* tex_p = manekin[i].tex_p;
                u8* pal_p = manekin[i].palette_p;
                int idx = ITEM_IS_CLOTH(manekin[i].item) != FALSE ? (manekin[i].item - ITM_CLOTH_START) : 0;

                mPlib_Load_PlayerTexAndPallet(tex_p, pal_p, idx);
            }

            mPlib_Load_PlayerTexAndPallet(shop_manekin->naked_tex_p, shop_manekin->naked_pal_p, ITM_CLOTH_MANEKIN - ITM_CLOTH_START);
        }
    }
}

static void aSM_Change2NakedManekin(int ux, int uz) {
    ux %= UT_X_NUM;
    uz %= UT_Z_NUM;

    if (CLIP(shop_manekin_clip) != NULL) {
        ACTOR* actorx = CLIP(shop_manekin_clip)->shop_manekin_actor_p;

        if (actorx != NULL) {
            SHOP_MANEKIN_ACTOR* shop_manekin = (SHOP_MANEKIN_ACTOR*)actorx;
            int count = shop_manekin->current_block_manekin_num;
            MANEKIN_ACTOR* manekin = shop_manekin->manekin_actors;
            int i;

            for (i = 0; i < count; i++) {
                if (manekin->ut_x == ux && manekin->ut_z == uz) {
                    manekin->naked = TRUE;
                    break;
                }

                manekin++;
            }
        }
    }
}

static void aSM_Naked2Cloth(int ux, int uz) {
        ux %= UT_X_NUM;
    uz %= UT_Z_NUM;

    if (CLIP(shop_manekin_clip) != NULL) {
        ACTOR* actorx = CLIP(shop_manekin_clip)->shop_manekin_actor_p;

        if (actorx != NULL) {
            SHOP_MANEKIN_ACTOR* shop_manekin = (SHOP_MANEKIN_ACTOR*)actorx;
            int count = shop_manekin->current_block_manekin_num;
            MANEKIN_ACTOR* manekin = shop_manekin->manekin_actors;
            int i;

            for (i = 0; i < count; i++) {
                if (manekin->ut_x == ux && manekin->ut_z == uz) {
                    manekin->naked = FALSE;
                    break;
                }

                manekin++;
            }
        }
    }
}
