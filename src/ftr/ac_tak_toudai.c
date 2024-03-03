static void fTTD_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fTTD_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fTTD_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fTTD_func = {
	&fTTD_ct,
	&fTTD_mv,
	&fTTD_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_tak_toudai = {
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
	2,
	0,
	0,
	&fTTD_func,
};
