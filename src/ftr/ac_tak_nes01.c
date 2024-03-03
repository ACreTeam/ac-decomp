static void fTakNes_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fTakNes_func = {
	NULL,
	NULL,
	&fTakNes_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_tak_nes01 = {
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
};
