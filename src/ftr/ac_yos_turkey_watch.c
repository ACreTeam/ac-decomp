static void fYTW_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fYTW_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fYTW_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fYTW_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fYTW_func = {
	&fYTW_ct,
	&fYTW_mv,
	&fYTW_dw,
	&fYTW_dt,
	NULL,
};

aFTR_PROFILE iam_yos_turkey_watch = {
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
	2,
	0,
	0,
	&fYTW_func,
};
