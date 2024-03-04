static void fFC_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fFC_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fFC_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

extern u8 int_tak_nes_cl_tex[];
extern u8 int_tak_nes_bf_tex_rgb_ci4[];
extern u8 int_tak_nes_dk_tex_rgb_ci4[];
extern u8 int_tak_nes_sa_tex_rgb_ci4[];
extern u8 int_tak_nes_pb_tex_rgb_ci4[];
extern u8 int_tak_nes_t_tex_rgb_ci4[];
extern u8 int_tak_nes_g_tex_rgb_ci4[];
extern u8 int_tak_nes_po_tex_rgb_ci4[];
extern u8 int_tak_nes_bb_tex_rgb_ci4[];
extern u8 int_tak_nes_cl_tex[];
extern u8 int_tak_nes_d3_tex_rgb_ci4[];
extern u8 int_tak_nes_d2_tex_rgb_ci4[];
extern u8 int_tak_nes_so_tex_rgb_ci4[];
extern u8 int_tak_nes_eb_tex_rgb_ci4[];
extern u8 int_tak_nes_wm_tex_rgb_ci4[];
extern u8 int_tak_nes_ic_tex_rgb_ci4[];
extern u8 int_tak_nes_mb_tex_rgb_ci4[];
extern u8 int_tak_nes_sm_tex_rgb_ci4[];
extern u8 int_tak_nes_zl_tex_rgb_ci4[];
extern u8 int_tak_nes_eb_tex_rgb_ci4[];

static u8* fFC_texture_table[] = {
    int_tak_nes_cl_tex,         int_tak_nes_bf_tex_rgb_ci4, int_tak_nes_dk_tex_rgb_ci4, int_tak_nes_sa_tex_rgb_ci4,
    int_tak_nes_pb_tex_rgb_ci4, int_tak_nes_t_tex_rgb_ci4,  int_tak_nes_g_tex_rgb_ci4,  int_tak_nes_po_tex_rgb_ci4,
    int_tak_nes_bb_tex_rgb_ci4, int_tak_nes_cl_tex,         int_tak_nes_d3_tex_rgb_ci4, int_tak_nes_d2_tex_rgb_ci4,
    int_tak_nes_so_tex_rgb_ci4, int_tak_nes_eb_tex_rgb_ci4, int_tak_nes_wm_tex_rgb_ci4, int_tak_nes_ic_tex_rgb_ci4,
    int_tak_nes_mb_tex_rgb_ci4, int_tak_nes_sm_tex_rgb_ci4, int_tak_nes_zl_tex_rgb_ci4, int_tak_nes_eb_tex_rgb_ci4,
};

extern u16 int_tak_nes_cl_pal[];
extern u16 int_tak_nes_bf_tex_rgb_ci4_pal[];
extern u16 int_tak_nes_dk_tex_rgb_ci4_pal[];
extern u16 int_tak_nes_sa_tex_rgb_ci4_pal[];
extern u16 int_tak_nes_pb_tex_rgb_ci4_pal[];
extern u16 int_tak_nes_t_tex_rgb_ci4_pal[];
extern u16 int_tak_nes_g_tex_rgb_ci4_pal[];
extern u16 int_tak_nes_po_tex_rgb_ci4_pal[];
extern u16 int_tak_nes_bb_tex_rgb_ci4_pal[];
extern u16 int_tak_nes_cl_pal[];
extern u16 int_tak_nes_d3_tex_rgb_ci4_pal[];
extern u16 int_tak_nes_d2_tex_rgb_ci4_pal[];
extern u16 int_tak_nes_so_tex_rgb_ci4_pal[];
extern u16 int_tak_nes_eb_tex_rgb_ci4_pal[];
extern u16 int_tak_nes_wm_tex_rgb_ci4_pal[];
extern u16 int_tak_nes_ic_tex_rgb_ci4_pal[];
extern u16 int_tak_nes_mb_tex_rgb_ci4_pal[];
extern u16 int_tak_nes_sm_tex_rgb_ci4_pal[];
extern u16 int_tak_nes_zl_tex_rgb_ci4_pal[];
extern u16 int_tak_nes_eb_tex_rgb_ci4_pal[];

static u16* fFC_palette_table[] = {
    int_tak_nes_cl_pal,
    int_tak_nes_bf_tex_rgb_ci4_pal,
    int_tak_nes_dk_tex_rgb_ci4_pal,
    int_tak_nes_sa_tex_rgb_ci4_pal,
    int_tak_nes_pb_tex_rgb_ci4_pal,
    int_tak_nes_t_tex_rgb_ci4_pal,
    int_tak_nes_g_tex_rgb_ci4_pal,
    int_tak_nes_po_tex_rgb_ci4_pal,
    int_tak_nes_bb_tex_rgb_ci4_pal,
    int_tak_nes_cl_pal,
    int_tak_nes_d3_tex_rgb_ci4_pal,
    int_tak_nes_d2_tex_rgb_ci4_pal,
    int_tak_nes_so_tex_rgb_ci4_pal,
    int_tak_nes_eb_tex_rgb_ci4_pal,
    int_tak_nes_wm_tex_rgb_ci4_pal,
    int_tak_nes_ic_tex_rgb_ci4_pal,
    int_tak_nes_mb_tex_rgb_ci4_pal,
    int_tak_nes_sm_tex_rgb_ci4_pal,
    int_tak_nes_zl_tex_rgb_ci4_pal,
    int_tak_nes_eb_tex_rgb_ci4_pal,
};

static u8 fFC_game_table[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 14 };
static u8 fFC_agb_game_table[] = { 1, 2, 3, 4, 5, 6, 7, 0xFF, 9, 0xFF, 11, 12, 13, 14, 0xFF, 16, 17, 18, 0xFF, 0xFF };

static void fFC_ct(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void fFC_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    int ftr_idx = (ftr_actor->name >= 0x36A && ftr_actor->name <= 0x37D) ? (ftr_actor->name - 0x36A) : 0;

    (*Common_Get(clip).my_room_clip->famicom_emu_common_move_proc)(
        ftr_actor, my_room_actor, game, fFC_game_table[ftr_idx], fFC_agb_game_table[ftr_idx]);
}

extern Gfx int_tak_nes01_on_model[];
extern Gfx int_tak_nes01_onT_model[];
extern Gfx int_tak_nes01_game_on_model[];

/* @unused - this was used in DnM/DnM+ to determine which Famicom model to use */
static int fFC_reference_model_idx_table[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static void fFC_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    int ftr_idx = (ftr_actor->name >= 0x36A && ftr_actor->name <= 0x37D) ? (ftr_actor->name - 0x36A) : 0;
    u8* tex_p = fFC_texture_table[ftr_idx];
    u16* pal_p = fFC_palette_table[ftr_idx];

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, tex_p);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_9, pal_p);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_tak_nes01_on_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_tak_nes01_onT_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_tak_nes01_game_on_model);

    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c fFC_func = {
    &fFC_ct, &fFC_mv, &fFC_dw, NULL, NULL,
};

aFTR_PROFILE iam_famicom_common = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    18.0f,
    0.01f,
    aFTR_SHAPE_TYPEA,
    mCoBG_FTR_TYPEA,
    0,
    0,
    0,
    aFTR_INTERACTION_FAMICOM,
    &fFC_func,
};
