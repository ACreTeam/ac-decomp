static void fKZ_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fKZ_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fKZ_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fKZ_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fKZ_func = {
	&fKZ_ct,
	&fKZ_mv,
	&fKZ_dw,
	&fKZ_dt,
	NULL,
};

aFTR_PROFILE iam_kazaguruma = {
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
	&fKZ_func,
};
