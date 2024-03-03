static void fTSW_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fTSW_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fTSW_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fTSW_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fTSW_func = {
	&fTSW_ct,
	&fTSW_mv,
	&fTSW_dw,
	&fTSW_dt,
	NULL,
};

aFTR_PROFILE iam_tak_stew = {
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
	&fTSW_func,
};
