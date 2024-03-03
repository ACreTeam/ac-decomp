static void fTL_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fTL_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fTL_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fTL_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fTL_func = {
	&fTL_ct,
	&fTL_mv,
	&fTL_dw,
	&fTL_dt,
	NULL,
};

aFTR_PROFILE iam_tak_lion = {
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
	0,
	0,
	0,
	&fTL_func,
};
