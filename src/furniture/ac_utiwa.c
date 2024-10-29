static void fUW_ct(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void fUW_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    // nothing
}

static void fUW_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

extern Gfx obj_shop_utiwa1_mat_model[];
extern Gfx obj_shop_utiwa2_mat_model[];
extern Gfx obj_shop_utiwa3_mat_model[];
extern Gfx obj_shop_utiwa4_mat_model[];
extern Gfx obj_shop_utiwa5_mat_model[];
extern Gfx obj_shop_utiwa6_mat_model[];
extern Gfx obj_shop_utiwa7_mat_model[];
extern Gfx obj_shop_utiwa8_mat_model[];

static Gfx* fUW_mat_table[] = {
    obj_shop_utiwa1_mat_model, obj_shop_utiwa2_mat_model, obj_shop_utiwa3_mat_model, obj_shop_utiwa4_mat_model,
    obj_shop_utiwa5_mat_model, obj_shop_utiwa6_mat_model, obj_shop_utiwa7_mat_model, obj_shop_utiwa8_mat_model,
};

extern Gfx obj_shop_utiwa1_gfx_model[];
extern Gfx obj_shop_utiwa2_gfx_model[];
extern Gfx obj_shop_utiwa3_gfx_model[];
extern Gfx obj_shop_utiwa4_gfx_model[];
extern Gfx obj_shop_utiwa5_gfx_model[];
extern Gfx obj_shop_utiwa6_gfx_model[];
extern Gfx obj_shop_utiwa7_gfx_model[];
extern Gfx obj_shop_utiwa8_gfx_model[];

static Gfx* fUW_gfx_table[] = {
    obj_shop_utiwa1_gfx_model, obj_shop_utiwa2_gfx_model, obj_shop_utiwa3_gfx_model, obj_shop_utiwa4_gfx_model,
    obj_shop_utiwa5_gfx_model, obj_shop_utiwa6_gfx_model, obj_shop_utiwa7_gfx_model, obj_shop_utiwa8_gfx_model,
};

static void fUW_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    int utiwa_idx = (ftr_actor->name - 0x453) & 7;

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_OPA_DISP, fUW_mat_table[utiwa_idx]);
    gSPDisplayList(NEXT_POLY_OPA_DISP, fUW_gfx_table[utiwa_idx]);

    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c fUW_func = {
    &fUW_ct, &fUW_mv, &fUW_dw, &fUW_dt, NULL,
};

aFTR_PROFILE iam_utiwa = {
    // clang-format off
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	15.7f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	0,
	&fUW_func,
    // clang-format on
};
