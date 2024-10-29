extern Gfx int_tak_megami_on_model[];
extern Gfx int_tak_megami_onT_model[];
extern Gfx int_tak_megami_offT_model[];

static void fTM_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_tak_megami_on_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_tak_megami_onT_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_tak_megami_offT_model);

    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c fTM_func = {
    NULL, NULL, &fTM_dw, NULL, NULL,
};

aFTR_PROFILE iam_tak_megami = {
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
	&fTM_func,
    // clang-format on
};
