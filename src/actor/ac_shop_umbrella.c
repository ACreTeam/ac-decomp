#include "ac_shop_umbrella.h"

#include "m_common_data.h"
#include "m_malloc.h"
#include "m_player_lib.h"
#include "m_rcp.h"
#include "sys_matrix.h"

extern Gfx obj_shop_umb01_model[];
extern Gfx obj_shop_umb02_model[];
extern Gfx obj_shop_umb03_model[];
extern Gfx obj_shop_umb04_model[];
extern Gfx obj_shop_umb05_model[];
extern Gfx obj_shop_umb06_model[];
extern Gfx obj_shop_umb07_model[];
extern Gfx obj_shop_umb08_model[];
extern Gfx obj_shop_umb09_model[];
extern Gfx obj_shop_umb10_model[];
extern Gfx obj_shop_umb11_model[];
extern Gfx obj_shop_umb12_model[];
extern Gfx obj_shop_umb13_model[];
extern Gfx obj_shop_umb14_model[];
extern Gfx obj_shop_umb15_model[];
extern Gfx obj_shop_umb16_model[];
extern Gfx obj_shop_umb17_model[];
extern Gfx obj_shop_umb18_model[];
extern Gfx obj_shop_umb19_model[];
extern Gfx obj_shop_umb20_model[];
extern Gfx obj_shop_umb21_model[];
extern Gfx obj_shop_umb22_model[];
extern Gfx obj_shop_umb23_model[];
extern Gfx obj_shop_umb24_model[];
extern Gfx obj_shop_umb25_model[];
extern Gfx obj_shop_umb26_model[];
extern Gfx obj_shop_umb27_model[];
extern Gfx obj_shop_umb28_model[];
extern Gfx obj_shop_umb29_model[];
extern Gfx obj_shop_umb30_model[];
extern Gfx obj_shop_umb31_model[];
extern Gfx obj_shop_umb32_model[];

// clang-format off
static Gfx* aShopUmbrella_disp_table[] = {
    obj_shop_umb01_model,
    obj_shop_umb02_model,
    obj_shop_umb03_model,
    obj_shop_umb04_model,
    obj_shop_umb05_model,
    obj_shop_umb06_model,
    obj_shop_umb07_model,
    obj_shop_umb08_model,
    obj_shop_umb09_model,
    obj_shop_umb10_model,
    obj_shop_umb11_model,
    obj_shop_umb12_model,
    obj_shop_umb13_model,
    obj_shop_umb14_model,
    obj_shop_umb15_model,
    obj_shop_umb16_model,
    obj_shop_umb17_model,
    obj_shop_umb18_model,
    obj_shop_umb19_model,
    obj_shop_umb20_model,
    obj_shop_umb21_model,
    obj_shop_umb22_model,
    obj_shop_umb23_model,
    obj_shop_umb24_model,
    obj_shop_umb25_model,
    obj_shop_umb26_model,
    obj_shop_umb27_model,
    obj_shop_umb28_model,
    obj_shop_umb29_model,
    obj_shop_umb30_model,
    obj_shop_umb31_model,
    obj_shop_umb32_model,
};
// clang-format on

extern Gfx obj_shop_umb01_modelT[];
extern Gfx obj_shop_umb02_modelT[];
extern Gfx obj_shop_umb03_modelT[];
extern Gfx obj_shop_umb04_modelT[];
extern Gfx obj_shop_umb05_modelT[];
extern Gfx obj_shop_umb06_modelT[];
extern Gfx obj_shop_umb07_modelT[];
extern Gfx obj_shop_umb08_modelT[];
extern Gfx obj_shop_umb09_modelT[];
extern Gfx obj_shop_umb10_modelT[];
extern Gfx obj_shop_umb11_modelT[];
extern Gfx obj_shop_umb12_modelT[];
extern Gfx obj_shop_umb13_modelT[];
extern Gfx obj_shop_umb14_modelT[];
extern Gfx obj_shop_umb15_modelT[];
extern Gfx obj_shop_umb16_modelT[];
extern Gfx obj_shop_umb17_modelT[];
extern Gfx obj_shop_umb18_modelT[];
extern Gfx obj_shop_umb19_modelT[];
extern Gfx obj_shop_umb20_modelT[];
extern Gfx obj_shop_umb21_modelT[];
extern Gfx obj_shop_umb22_modelT[];
extern Gfx obj_shop_umb23_modelT[];
extern Gfx obj_shop_umb24_modelT[];
extern Gfx obj_shop_umb25_modelT[];
extern Gfx obj_shop_umb26_modelT[];
extern Gfx obj_shop_umb27_modelT[];
extern Gfx obj_shop_umb28_modelT[];
extern Gfx obj_shop_umb29_modelT[];
extern Gfx obj_shop_umb30_modelT[];
extern Gfx obj_shop_umb31_modelT[];
extern Gfx obj_shop_umb32_modelT[];

// clang-format off
static Gfx* aShopUmbrella_xlu_disp_table[] = {
    obj_shop_umb01_modelT,
    obj_shop_umb02_modelT,
    obj_shop_umb03_modelT,
    obj_shop_umb04_modelT,
    obj_shop_umb05_modelT,
    obj_shop_umb06_modelT,
    obj_shop_umb07_modelT,
    obj_shop_umb08_modelT,
    obj_shop_umb09_modelT,
    obj_shop_umb10_modelT,
    obj_shop_umb11_modelT,
    obj_shop_umb12_modelT,
    obj_shop_umb13_modelT,
    obj_shop_umb14_modelT,
    obj_shop_umb15_modelT,
    obj_shop_umb16_modelT,
    obj_shop_umb17_modelT,
    obj_shop_umb18_modelT,
    obj_shop_umb19_modelT,
    obj_shop_umb20_modelT,
    obj_shop_umb21_modelT,
    obj_shop_umb22_modelT,
    obj_shop_umb23_modelT,
    obj_shop_umb24_modelT,
    obj_shop_umb25_modelT,
    obj_shop_umb26_modelT,
    obj_shop_umb27_modelT,
    obj_shop_umb28_modelT,
    obj_shop_umb29_modelT,
    obj_shop_umb30_modelT,
    obj_shop_umb31_modelT,
    obj_shop_umb32_modelT,
};
// clang-format on

static void Shop_Umbrella_Actor_ct(ACTOR* actorx, GAME* game);
static void Shop_Umbrella_Actor_dt(ACTOR* actorx, GAME* game);
static void Shop_Umbrella_Actor_move(ACTOR* actorx, GAME* game);
static void Shop_Umbrella_Actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Shop_Umbrella_Profile = {
    mAc_PROFILE_SHOP_UMBRELLA,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(SHOP_UMBRELLA_ACTOR),
    &Shop_Umbrella_Actor_ct,
    &Shop_Umbrella_Actor_dt,
    &Shop_Umbrella_Actor_move,
    &Shop_Umbrella_Actor_draw,
    NULL,
};
// clang-format on

static int aShopUmbrella_CountCurrentBlockUmbrella(xyz_t pos) {
    int ux;
    int uz;
    int bx;
    int bz;
    mActor_name_t* fg_p;
    int i;
    int count;

    ux = mFI_WposX2UtNumX(pos.x);
    uz = mFI_WposZ2UtNumZ(pos.z);
    bx = ux / UT_X_NUM;
    bz = uz / UT_Z_NUM;
    fg_p = mFI_BkNumtoUtFGTop(bx, bz);

    count = 0;
    for (i = 0; i < UT_TOTAL_NUM; i++) {
        if (ITEM_IS_UMBRELLA2(*fg_p)) {
            count++;
        }

        fg_p++;
    }

    return count;
}

static void aShopUmbrella_SearchUmbrellaPlace(int* ux, int* uz, mActor_name_t* item, int idx, int bx, int bz) {
    mActor_name_t* fg_p = mFI_BkNumtoUtFGTop(bx, bz);
    int count = 0;
    int i;

    *ux = 0;
    *uz = 0;
    for (i = 0; i < UT_TOTAL_NUM; i++) {
        if (ITEM_IS_UMBRELLA2(fg_p[i])) {
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

static mCoBG_bg_size_c l_umbrella_mBgData = { 13.0f, 13.0f, 13.0f, 13.0f };

static void aShopUmbrella_UmbrellaCt(ACTOR* actorx) {
    SHOP_UMBRELLA_ACTOR* shop_umbrella = (SHOP_UMBRELLA_ACTOR*)actorx;
    int bx = shop_umbrella->bx;
    int bz = shop_umbrella->bz;
    static s16 angle_y = 0;

    if (shop_umbrella->umbrellas != NULL) {
        aShopUmbrella_umbrella_c* umbrella = shop_umbrella->umbrellas;
        int count = shop_umbrella->umbrella_num;
        int i;

        for (i = 0; i < count; i++) {
            int* ux_p = &umbrella->ut_x;
            int* uz_p = &umbrella->ut_z;

            umbrella->state = aShopUmbrella_STATE_WAIT;
            umbrella->scale = 0.01f;
            umbrella->_1C = 0;
            aShopUmbrella_SearchUmbrellaPlace(ux_p, uz_p, &umbrella->item, i, bx, bz);
            umbrella->umbrella_idx = ITEM_IS_UMBRELLA2(umbrella->item) ? (umbrella->item - ITM_UMBRELLA_START) : 0;

            umbrella->wpos.x = bx * mFI_BK_WORLDSIZE_X_F + (*ux_p) * mFI_UT_WORLDSIZE_X_F + mFI_UT_WORLDSIZE_HALF_X_F;
            umbrella->wpos.y = 0.0f;
            umbrella->wpos.z = bz * mFI_BK_WORLDSIZE_Z_F + (*uz_p) * mFI_UT_WORLDSIZE_Z_F + mFI_UT_WORLDSIZE_HALF_Z_F;
            umbrella->wpos.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(umbrella->wpos, 0.0f);
            umbrella->move_bg_idx =
                mCoBG_RegistMoveBg(&umbrella->bg_regist, &umbrella->wpos, NULL, &angle_y, 40.0f, &l_umbrella_mBgData,
                                   NULL, NULL, NULL, mCoBG_FTR_TYPE_NUM, mCoBG_ATTRIBUTE_STONE, 40.0f);
            umbrella++;
        }
    }
}

static void aShopUmbrella_SecureUmbrellaSubActor(ACTOR* actorx) {
    SHOP_UMBRELLA_ACTOR* shop_umbrella = (SHOP_UMBRELLA_ACTOR*)actorx;
    int count = shop_umbrella->umbrella_num;
    size_t size = sizeof(aShopUmbrella_umbrella_c);
    size_t aligned_size = ALIGN_NEXT(size, 8);

    shop_umbrella->umbrellas = NULL;
    shop_umbrella->umbrellas = (aShopUmbrella_umbrella_c*)zelda_malloc(count * aligned_size);
    if (shop_umbrella->umbrellas != NULL) {
        aShopUmbrella_UmbrellaCt(actorx);
    }
}

static void aShopUmbrella_GetNowBlockNumber(ACTOR* actorx) {
    SHOP_UMBRELLA_ACTOR* shop_umbrella = (SHOP_UMBRELLA_ACTOR*)actorx;
    xyz_t pos = actorx->world.position;
    int ux = mFI_WposX2UtNumX(pos.x);
    int uz = mFI_WposX2UtNumX(pos.z); // @BUG - used X instead of Z

    shop_umbrella->bx = ux / UT_X_NUM;
    shop_umbrella->bz = uz / UT_Z_NUM;
}

static void aShopUmbrella_UmbrellaDmaAgain(void);
static void aShopUmbrella_DeleteUmbrella(int ux, int uz);

static void aShopUmbrella_SetClipProc(ACTOR* actorx, int set) {
    if (!set) {
        CLIP(shop_umbrella_clip) = NULL;
    } else {
        SHOP_UMBRELLA_ACTOR* shop_umbrella = (SHOP_UMBRELLA_ACTOR*)actorx;
        aShopUmbrella_Clip_c* clip = &shop_umbrella->clip;

        CLIP(shop_umbrella_clip) = clip;
        clip->shop_umbrella_actor_p = actorx;
        clip->umbrella_dma_again_proc = &aShopUmbrella_UmbrellaDmaAgain;
        clip->delete_umbrella_proc = &aShopUmbrella_DeleteUmbrella;
    }
}

static void Shop_Umbrella_Actor_ct(ACTOR* actorx, GAME* game) {
    SHOP_UMBRELLA_ACTOR* shop_umbrella = (SHOP_UMBRELLA_ACTOR*)actorx;

    aShopUmbrella_GetNowBlockNumber(actorx);
    shop_umbrella->umbrella_num = aShopUmbrella_CountCurrentBlockUmbrella(actorx->world.position);
    aShopUmbrella_SecureUmbrellaSubActor(actorx);
    aShopUmbrella_SetClipProc(actorx, TRUE);
}

static void Shop_Umbrella_Actor_dt(ACTOR* actorx, GAME* game) {
    SHOP_UMBRELLA_ACTOR* shop_umbrella = (SHOP_UMBRELLA_ACTOR*)actorx;
    int count = shop_umbrella->umbrella_num;
    aShopUmbrella_umbrella_c* umbrella = shop_umbrella->umbrellas;
    int i;

    for (i = 0; i < count; i++) {
        mCoBG_CrossOffMoveBg(umbrella[i].move_bg_idx);
    }

    if (shop_umbrella->umbrellas != NULL) {
        zelda_free(shop_umbrella->umbrellas);
    }

    aShopUmbrella_SetClipProc(actorx, FALSE);
}

static void Shop_Umbrella_Actor_draw(ACTOR* actorx, GAME* game) {
    SHOP_UMBRELLA_ACTOR* shop_umbrella = (SHOP_UMBRELLA_ACTOR*)actorx;
    int count = shop_umbrella->umbrella_num;
    GAME_PLAY* play = (GAME_PLAY*)game;
    aShopUmbrella_umbrella_c* umbrella = shop_umbrella->umbrellas;
    int i;

    if (umbrella != NULL) {
        for (i = 0; i < count; i++) {
            xyz_t pos = umbrella[i].wpos;
            int idx = umbrella[i].umbrella_idx;
            f32 scale = umbrella->scale; // @BUG - should access umbrella[i]
            LightsN* lights;

            _texture_z_light_fog_prim(game->graph);
            _texture_z_light_fog_prim_xlu(game->graph);

            OPEN_DISP(game->graph);

            lights = Global_light_read(&play->global_light, play->game.graph);
            LightsN_list_check(lights, play->global_light.list, &pos);
            LightsN_disp(lights, play->game.graph);
            Matrix_translate(pos.x, pos.y, pos.z, MTX_LOAD);
            Matrix_scale(scale, scale, scale, MTX_MULT);

            gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_LOAD | G_MTX_NOPUSH);
            gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_LOAD | G_MTX_NOPUSH);
            gSPDisplayList(NEXT_POLY_OPA_DISP, aShopUmbrella_disp_table[idx]);
            gSPDisplayList(NEXT_POLY_XLU_DISP, aShopUmbrella_xlu_disp_table[idx]);

            CLOSE_DISP(game->graph);
        }
    }
}

static void aShopUmbrella_ProcWait(aShopUmbrella_umbrella_c* umbrella) {
    umbrella->scale = 0.01f;
}

static void aShopUmbrella_ProcDelete(aShopUmbrella_umbrella_c* umbrella) {
    umbrella->scale -= 0.001f;

    if (umbrella->scale <= 0.0f) {
        umbrella->state = aShopUmbrella_STATE_NONE;
        mCoBG_CrossOffMoveBg(umbrella->move_bg_idx);
    }
}

static void aShopUmbrella_ProcNone(aShopUmbrella_umbrella_c* umbrella) {
    umbrella->scale = 0.0f;
}

typedef void (*aShopUmbrella_PROC)(aShopUmbrella_umbrella_c* umbrella);

static void Shop_Umbrella_Actor_move(ACTOR* actorx, GAME* game) {
    static aShopUmbrella_PROC proc_table[] = {
        &aShopUmbrella_ProcWait,
        &aShopUmbrella_ProcDelete,
        &aShopUmbrella_ProcNone,
    };

    SHOP_UMBRELLA_ACTOR* shop_umbrella = (SHOP_UMBRELLA_ACTOR*)actorx;
    int count = shop_umbrella->umbrella_num;
    aShopUmbrella_umbrella_c* umbrella = shop_umbrella->umbrellas;
    int i;

    if (umbrella != NULL) {
        for (i = 0; i < count; i++) {
            if (umbrella->state >= 0 && umbrella->state < aShopUmbrella_STATE_NUM) {
                (*proc_table[umbrella->state])(umbrella);
            }

            umbrella++;
        }
    }
}

static void aShopUmbrella_UmbrellaDmaAgain(void) {
    // nothing
}

static void aShopUmbrella_DeleteUmbrella(int ux, int uz) {
    int l_ux = ux & 0xF;
    int l_uz = uz & 0xF;

    if (CLIP(shop_umbrella_clip) != NULL) {
        ACTOR* actorx = CLIP(shop_umbrella_clip)->shop_umbrella_actor_p;

        if (actorx != NULL) {
            SHOP_UMBRELLA_ACTOR* shop_umbrella = (SHOP_UMBRELLA_ACTOR*)actorx;
            int count = shop_umbrella->umbrella_num;
            aShopUmbrella_umbrella_c* umbrella = shop_umbrella->umbrellas;
            int i;

            for (i = 0; i < count; i++) {
                if (l_ux == umbrella[i].ut_x && l_uz == umbrella[i].ut_z) {
                    umbrella[i].state = aShopUmbrella_STATE_DELETE;
                    // break;
                }
            }
        }
    }
}
