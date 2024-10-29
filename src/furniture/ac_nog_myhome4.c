extern Gfx int_nog_myhome4_on_model[];
extern Gfx int_nog_myhome4_onT_model[];
extern Gfx int_nog_myhome4_off_model[];

static void fNM4_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    u16* pal_p = ftr_actor->pal_p;

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, pal_p);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_nog_myhome4_on_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_nog_myhome4_onT_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_nog_myhome4_off_model);

    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c fNM4_func = {
    &fNM2_ct, &fNM2_mv, &fNM4_dw, &fNM2_dt, NULL,
};

aFTR_PROFILE iam_nog_myhome4 = {
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
	aFTR_INTERACTION_TOGGLE,
	&fNM4_func,
    // clang-format on
};
