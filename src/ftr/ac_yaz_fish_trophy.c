static void fYFT_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fYFT_func = {
	NULL,
	NULL,
	&fYFT_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_yaz_fish_trophy = {
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
	&fYFT_func,
};
