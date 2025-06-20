#include "ac_needlework_indoor.h"

#include "m_malloc.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

#define aNI_GET_ACTOR() (CLIP(needlework_indoor_clip) != NULL ? CLIP(needlework_indoor_clip)->needlework_indoor_actor_p : NULL)

static void Needlework_Indoor_Actor_ct(ACTOR* actorx, GAME* game);
static void Needlework_Indoor_Actor_dt(ACTOR* actorx, GAME* game);
static void Needlework_Indoor_Actor_move(ACTOR* actorx, GAME* game);
static void Needlework_Indoor_Actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Needlework_Indoor_Profile = {
    // clang-format off
    mAc_PROFILE_NEEDLEWORK_INDOOR,
    ACTOR_PART_BG,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NEEDLEWORK_INDOOR_ACTOR),
    Needlework_Indoor_Actor_ct,
    Needlework_Indoor_Actor_dt,
    Needlework_Indoor_Actor_move,
    Needlework_Indoor_Actor_draw,
    NULL,
    // clang-format on
};

static void aNI_SetClip(ACTOR* actorx);
static void aNI_CopyClothData(int idx, mNW_original_design_c* design, int se_flag);
static void aNI_ExchangeCloth(int idx, int player_org_idx, int se_flag);
static void aNI_CopyUmbData(int idx, mNW_original_design_c* design, int se_flag);
static void aNI_ExchangeUmb(int idx, int player_org_idx, int se_flag);

static int aNI_RequestCopyClothData(int manekin_idx, mNW_original_design_c* design);
static int aNI_RequestCopyUmbData(int umbrella_idx, mNW_original_design_c* design);
static int aNI_RequestExchangeCloth(int manekin_idx, int player_org_idx);
static int aNI_RequestExchangeUmb(int umbrella_idx, int player_org_idx);

static void aNI_CopyAllData(ACTOR* actorx, GAME* game) {
    int i;

    for (i = 0; i < mNW_CLOTH_DESIGN_NUM; i++) {
        aNI_CopyClothData(i, &Save_Get(needlework).original_design[i & 3], FALSE);
    }

    for (i = 0; i < mNW_UMBRELLA_DESIGN_NUM; i++) {
        aNI_CopyUmbData(i, &Save_Get(needlework).original_design[mNW_CLOTH_DESIGN_NUM + (i & 3)], FALSE);
    }
}

static void aNI_MallocRam(ACTOR* actorx) {
    NEEDLEWORK_INDOOR_ACTOR* actor = (NEEDLEWORK_INDOOR_ACTOR*)actorx;
    int i;
    int j;

    for (i = 0; i < mNW_CLOTH_DESIGN_NUM; i++) {
        for (j = 0; j < 2; j++) {
            actor->data[j][mNW_TYPE_MANEKIN][i] =
                (mNW_original_design_c*)zelda_malloc_align(sizeof(mNW_original_design_c), 32);
        }
    }

    for (i = 0; i < mNW_UMBRELLA_DESIGN_NUM; i++) {
        for (j = 0; j < 2; j++) {
            actor->data[j][mNW_TYPE_UMBRELLA][i] =
                (mNW_original_design_c*)zelda_malloc_align(sizeof(mNW_original_design_c), 32);
        }
    }
}

static void aNI_SetMoveBg(ACTOR* actorx) {
    static mCoBG_bg_size_c l_manekin_mBgData = { 14.5f, 14.5f, 14.5f, 14.5f };
    static s16 dummy_angle = 0;

    static xyz_t manekin_pos[4] = {
        // clang-format off
        {180.0f, 40.0f, 100.0f},
        {220.0f, 40.0f, 100.0f},
        {260.0f, 40.0f, 100.0f},
        {300.0f, 40.0f, 100.0f},
        // clang-format on
    };

    static xyz_t umbrella_pos[4] = {
        // clang-format off
        {180.0f, 40.0f, 180.0f},
        {220.0f, 40.0f, 180.0f},
        {260.0f, 40.0f, 180.0f},
        {300.0f, 40.0f, 180.0f},
        // clang-format on
    };

    NEEDLEWORK_INDOOR_ACTOR* actor = (NEEDLEWORK_INDOOR_ACTOR*)actorx;
    int i;

    for (i = 0; i < mNW_CLOTH_DESIGN_NUM; i++) {
        actor->cloth_move_bg[i].pos = manekin_pos[i];
        actor->cloth_move_bg[i].regist_idx =
            mCoBG_RegistMoveBg(&actor->cloth_move_bg[i].regist, &actor->cloth_move_bg[i].pos, NULL, &dummy_angle, 40.0f,
                               &l_manekin_mBgData, NULL, NULL, NULL, mCoBG_FTR_TYPE_NUM, mCoBG_ATTRIBUTE_STONE, 40.0f);
    }

    for (i = 0; i < mNW_UMBRELLA_DESIGN_NUM; i++) {
        actor->umbrella_move_bg[i].pos = umbrella_pos[i];
        actor->umbrella_move_bg[i].regist_idx = mCoBG_RegistMoveBg(
            &actor->umbrella_move_bg[i].regist, &actor->umbrella_move_bg[i].pos, NULL, &dummy_angle, 40.0f,
            &l_manekin_mBgData, NULL, NULL, NULL, mCoBG_FTR_TYPE_NUM, mCoBG_ATTRIBUTE_STONE, 40.0f);
    }
}

static void aNI_SetClip(ACTOR* actorx) {
    NEEDLEWORK_INDOOR_ACTOR* actor = (NEEDLEWORK_INDOOR_ACTOR*)actorx;

    actor->clip.needlework_indoor_actor_p = actorx;
    actor->clip.request_copy_cloth_data_proc = aNI_RequestCopyClothData;
    actor->clip.request_copy_umb_data_proc = aNI_RequestCopyUmbData;
    actor->clip.request_exchange_cloth_data_proc = aNI_RequestExchangeCloth;
    actor->clip.request_exchange_umb_data_proc = aNI_RequestExchangeUmb;
    CLIP(needlework_indoor_clip) = &actor->clip;
}

static void Needlework_Indoor_Actor_ct(ACTOR* actorx, GAME* game) {
    aNI_SetClip(actorx);
    aNI_MallocRam(actorx);
    aNI_SetMoveBg(actorx);
    aNI_CopyAllData(actorx, game);
}

static void aNI_FreeRam(ACTOR* actorx) {
    NEEDLEWORK_INDOOR_ACTOR* actor = (NEEDLEWORK_INDOOR_ACTOR*)actorx;
    int i;
    int j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < mNW_DESIGN_NUM; j++) {
            zelda_free(actor->data[i][mNW_TYPE_MANEKIN][j]);
            zelda_free(actor->data[i][mNW_TYPE_UMBRELLA][j]);
        }
    }
}

static void Needlework_Indoor_Actor_dt(ACTOR* actorx, GAME* game) {
    NEEDLEWORK_INDOOR_ACTOR* actor = (NEEDLEWORK_INDOOR_ACTOR*)actorx;
    int i;

    for (i = 0; i < mNW_CLOTH_DESIGN_NUM; i++) {
        mCoBG_CrossOffMoveBg(actor->cloth_move_bg[i].regist_idx);
    }

    for (i = 0; i < mNW_UMBRELLA_DESIGN_NUM; i++) {
        mCoBG_CrossOffMoveBg(actor->umbrella_move_bg[i].regist_idx);
    }

    aNI_FreeRam(actorx);
}

extern Gfx obj_shop_manekin_model[];

static void aNI_DrawManekin(ACTOR* actorx, GAME* game) {
    NEEDLEWORK_INDOOR_ACTOR* actor = (NEEDLEWORK_INDOOR_ACTOR*)actorx;
    int i;

    for (i = 0; i < mNW_CLOTH_DESIGN_NUM; i++) {
        int idx = actor->design_buf_idx[mNW_TYPE_MANEKIN][i] & 1;
        u8* texture = actor->data[idx][mNW_TYPE_MANEKIN][i]->design.data;
        u16* palette = mNW_PaletteIdx2Palette(actor->data[idx][mNW_TYPE_MANEKIN][i]->palette);

        OPEN_DISP(game->graph);

        _texture_z_light_fog_prim(game->graph);
        Matrix_translate(actor->cloth_move_bg[i].pos.x, actor->cloth_move_bg[i].pos.y,
                          actor->cloth_move_bg[i].pos.z, MTX_LOAD);
        Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);

        gSPSegment(NEXT_POLY_OPA_DISP, ANIME_1_TXT_SEG, texture);
        gSPSegment(NEXT_POLY_OPA_DISP, ANIME_2_TXT_SEG, palette);
        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_POLY_OPA_DISP, obj_shop_manekin_model);

        CLOSE_DISP(game->graph);
    }
}

extern Gfx obj_shop_umbmy_model[];

static void aNI_DrawUmbrella(ACTOR* actorx, GAME* game) {
    NEEDLEWORK_INDOOR_ACTOR* actor = (NEEDLEWORK_INDOOR_ACTOR*)actorx;
    int i;

    for (i = 0; i < mNW_UMBRELLA_DESIGN_NUM; i++) {
        int idx = actor->design_buf_idx[mNW_TYPE_UMBRELLA][i] & 1;
        u8* texture = actor->data[idx][mNW_TYPE_UMBRELLA][i]->design.data;
        u16* palette = mNW_PaletteIdx2Palette(actor->data[idx][mNW_TYPE_UMBRELLA][i]->palette);

        OPEN_DISP(game->graph);

        _texture_z_light_fog_prim(game->graph);
        Matrix_translate(actor->umbrella_move_bg[i].pos.x, actor->umbrella_move_bg[i].pos.y,
                          actor->umbrella_move_bg[i].pos.z, MTX_LOAD);
        Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);

        gSPSegment(NEXT_POLY_OPA_DISP, ANIME_2_TXT_SEG, texture);
        gSPSegment(NEXT_POLY_OPA_DISP, ANIME_1_TXT_SEG, palette);
        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_POLY_OPA_DISP, obj_shop_umbmy_model);

        CLOSE_DISP(game->graph);
    }
}

static void Needlework_Indoor_Actor_draw(ACTOR* actorx, GAME* game) {
    aNI_DrawManekin(actorx, game);
    aNI_DrawUmbrella(actorx, game);
}

static void Needlework_Indoor_Actor_move(ACTOR* actorx, GAME* game) {
    NEEDLEWORK_INDOOR_ACTOR* actor = (NEEDLEWORK_INDOOR_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    Submenu* submenu = &play->submenu;

    if (submenu->process_status == mSM_PROCESS_WAIT) {
        if (actor->clip.copy_cloth_data_requested == TRUE) {
            aNI_CopyClothData(actor->clip.copy_cloth_data_idx, actor->clip.copy_cloth_data_design_p, TRUE);
            actor->clip.copy_cloth_data_requested = FALSE;
        }

        if (actor->clip.exchange_cloth_data_requested == TRUE) {
            aNI_ExchangeCloth(actor->clip.exchange_cloth_data_idx, actor->clip.exchange_cloth_data_player_org_idx, TRUE);
            actor->clip.exchange_cloth_data_requested = FALSE;
        }

        if (actor->clip.copy_umb_data_requested == TRUE) {
            aNI_CopyUmbData(actor->clip.copy_umb_data_idx, actor->clip.copy_umb_data_design_p, TRUE);
            actor->clip.copy_umb_data_requested = FALSE;
        }

        if (actor->clip.exchange_umb_data_requested == TRUE) {
            aNI_ExchangeUmb(actor->clip.exchange_umb_data_idx, actor->clip.exchange_umb_data_player_org_idx, TRUE);
            actor->clip.exchange_umb_data_requested = FALSE;
        }
    }
}

static int aNI_RequestCopyClothData(int manekin_idx, mNW_original_design_c* design) {
    if (aNI_GET_ACTOR() != NULL) {
        NEEDLEWORK_INDOOR_ACTOR* actor = (NEEDLEWORK_INDOOR_ACTOR*)aNI_GET_ACTOR();

        if (actor->clip.copy_cloth_data_requested == FALSE) {
            actor->clip.copy_cloth_data_idx = manekin_idx;
            actor->clip.copy_cloth_data_design_p = design;
            actor->clip.copy_cloth_data_requested = TRUE;
            return TRUE;
        }
    }

    return FALSE;
}

static void aNI_CopyClothData(int idx, mNW_original_design_c* design, int se_flag) {
    idx &= 3;

    if (aNI_GET_ACTOR() != NULL) {
        NEEDLEWORK_INDOOR_ACTOR* actor = (NEEDLEWORK_INDOOR_ACTOR*)aNI_GET_ACTOR();
        int buf_idx;
        
        actor->design_buf_idx[mNW_TYPE_MANEKIN][idx] = (actor->design_buf_idx[mNW_TYPE_MANEKIN][idx] + 1) & 1;
        buf_idx = actor->design_buf_idx[mNW_TYPE_MANEKIN][idx];
        mNW_CopyOriginalTextureClass(actor->data[buf_idx][mNW_TYPE_MANEKIN][idx & 3], design);
        mNW_CopyOriginalTextureClass(&Save_Get(needlework).original_design[idx & 3], design);

        if (se_flag == TRUE) {
            sAdo_SysTrgStart(NA_SE_461);
        }
    }
}

static int aNI_RequestExchangeCloth(int manekin_idx, int player_org_idx) {
    if (aNI_GET_ACTOR() != NULL) {
        NEEDLEWORK_INDOOR_ACTOR* actor = (NEEDLEWORK_INDOOR_ACTOR*)aNI_GET_ACTOR();

        if (actor->clip.exchange_cloth_data_requested == FALSE) {
            actor->clip.exchange_cloth_data_idx = manekin_idx;
            actor->clip.exchange_cloth_data_player_org_idx = player_org_idx;
            actor->clip.exchange_cloth_data_requested = TRUE;
            return TRUE;
        }
    }

    return FALSE;
}

static void aNI_ExchangeCloth(int idx, int player_org_idx, int se_flag) {
    NEEDLEWORK_INDOOR_ACTOR* actor;
    int buf_idx;
    int tmp_idx;

    idx &= 3;
    tmp_idx = idx & 3;
    if (aNI_GET_ACTOR() != NULL) {
        actor = (NEEDLEWORK_INDOOR_ACTOR*)aNI_GET_ACTOR();
        buf_idx = actor->design_buf_idx[mNW_TYPE_MANEKIN][idx];

        aNI_CopyClothData(idx, &Now_Private->my_org[player_org_idx & 7], FALSE);
        mNW_CopyOriginalTextureClass(&Now_Private->my_org[player_org_idx & 7], actor->data[buf_idx][mNW_TYPE_MANEKIN][tmp_idx]);

        if (se_flag == TRUE) {
            sAdo_SysTrgStart(NA_SE_461);
        }
    }
}

static int aNI_RequestCopyUmbData(int umbrella_idx, mNW_original_design_c* design) {
    if (aNI_GET_ACTOR() != NULL) {
        NEEDLEWORK_INDOOR_ACTOR* actor = (NEEDLEWORK_INDOOR_ACTOR*)aNI_GET_ACTOR();

        if (actor->clip.copy_umb_data_requested == FALSE) {
            actor->clip.copy_umb_data_idx = umbrella_idx;
            actor->clip.copy_umb_data_design_p = design;
            actor->clip.copy_umb_data_requested = TRUE;
            return TRUE;
        }
    }

    return FALSE;
}

static void aNI_CopyUmbData(int idx, mNW_original_design_c* design, int se_flag) {
    idx &= 3;

    if (aNI_GET_ACTOR() != NULL) {
        NEEDLEWORK_INDOOR_ACTOR* actor = (NEEDLEWORK_INDOOR_ACTOR*)aNI_GET_ACTOR();
        int buf_idx;
        
        actor->design_buf_idx[mNW_TYPE_UMBRELLA][idx] = (actor->design_buf_idx[mNW_TYPE_UMBRELLA][idx] + 1) & 1;
        buf_idx = actor->design_buf_idx[mNW_TYPE_UMBRELLA][idx];
        mNW_CopyOriginalTextureClass(actor->data[buf_idx][mNW_TYPE_UMBRELLA][idx & 3], design);
        mNW_CopyOriginalTextureClass(&Save_Get(needlework).original_design[mNW_CLOTH_DESIGN_NUM + (idx & 3)], design);

        if (se_flag == TRUE) {
            sAdo_SysTrgStart(NA_SE_461);
        }
    }
}

static int aNI_RequestExchangeUmb(int umbrella_idx, int player_org_idx) {
    if (aNI_GET_ACTOR() != NULL) {
        NEEDLEWORK_INDOOR_ACTOR* actor = (NEEDLEWORK_INDOOR_ACTOR*)aNI_GET_ACTOR();

        if (actor->clip.exchange_umb_data_requested == FALSE) {
            actor->clip.exchange_umb_data_idx = umbrella_idx;
            actor->clip.exchange_umb_data_player_org_idx = player_org_idx;
            actor->clip.exchange_umb_data_requested = TRUE;
            return TRUE;
        }
    }

    return FALSE;
}

static void aNI_ExchangeUmb(int idx, int player_org_idx, int se_flag) {
    NEEDLEWORK_INDOOR_ACTOR* actor;
    int buf_idx;
    int tmp_idx;

    idx &= 3;
    tmp_idx = idx & 3;
    if (aNI_GET_ACTOR() != NULL) {
        actor = (NEEDLEWORK_INDOOR_ACTOR*)aNI_GET_ACTOR();
        buf_idx = actor->design_buf_idx[mNW_TYPE_UMBRELLA][idx];

        aNI_CopyUmbData(idx, &Now_Private->my_org[player_org_idx & 7], FALSE);
        mNW_CopyOriginalTextureClass(&Now_Private->my_org[player_org_idx & 7], actor->data[buf_idx][mNW_TYPE_UMBRELLA][tmp_idx]);

        if (se_flag == TRUE) {
            sAdo_SysTrgStart(NA_SE_461);
        }
    }
}
