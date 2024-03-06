extern Gfx int_tak_nes_af_tex_rgb_ci4[];
extern u16 int_tak_nes_af_tex_rgb_ci4_pal[];
extern Gfx int_tak_nes01_on_model[];
extern Gfx int_tak_nes01_onT_model[];
extern Gfx int_tak_nes01_game_on_model[];

static void fTakNes_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, int_tak_nes_af_tex_rgb_ci4);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_9, int_tak_nes_af_tex_rgb_ci4_pal);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_tak_nes01_on_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_tak_nes01_onT_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_tak_nes01_game_on_model);

    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c fTakNes_func = {
    NULL, NULL, &fTakNes_dw, NULL, NULL,
};

aFTR_PROFILE iam_tak_nes01 = {
    // clang-format off
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	40.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	0,
	&fTakNes_func,
    // clang-format on
};
