static void aSumTv01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumTv01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumTv01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumTv01_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumTv01_func = {
	&aSumTv01_ct,
	&aSumTv01_mv,
	&aSumTv01_dw,
	&aSumTv01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_tv01 = {
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
	aFTR_INTERACTION_START_DISABLED,
	&aSumTv01_func,
};
