static void aSumOkiagari01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumOkiagari01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumOkiagari01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c aSumOkiagari01_func = {
	&aSumOkiagari01_ct,
	&aSumOkiagari01_mv,
	&aSumOkiagari01_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_sum_okiagari01 = {
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
	&aSumOkiagari01_func,
};
