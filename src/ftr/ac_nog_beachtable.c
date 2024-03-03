static void fNBT_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fNBT_func = {
	NULL,
	NULL,
	&fNBT_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_nog_beachtable = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	30.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	0,
	&fNBT_func,
};
