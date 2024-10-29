static void fKZ_ct(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void fKZ_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    // nothing
}

static void fKZ_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

extern Gfx obj_shop_kaza1_model[];
extern Gfx obj_shop_kaza2_model[];
extern Gfx obj_shop_kaza3_model[];
extern Gfx obj_shop_kaza4_model[];
extern Gfx obj_shop_kaza5_model[];
extern Gfx obj_shop_kaza6_model[];
extern Gfx obj_shop_kaza7_model[];
extern Gfx obj_shop_kaza8_model[];

static Gfx* fKZ_model_table[] = {
    obj_shop_kaza1_model, obj_shop_kaza2_model, obj_shop_kaza3_model, obj_shop_kaza4_model,
    obj_shop_kaza5_model, obj_shop_kaza6_model, obj_shop_kaza7_model, obj_shop_kaza8_model,
};

static void fKZ_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    int windmill_idx = (ftr_actor->name - 0x45B) & 7;

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_OPA_DISP, fKZ_model_table[windmill_idx]);

    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c fKZ_func = {
    &fKZ_ct, &fKZ_mv, &fKZ_dw, &fKZ_dt, NULL,
};

aFTR_PROFILE iam_kazaguruma = {
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
	&fKZ_func,
    // clang-format on
};
