static void fIFT2_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fIFT2_func = {
	NULL,
	NULL,
	&fIFT2_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_ike_fish_tro2 = {
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
	1,
	0,
	0,
	&fIFT2_func,
};
