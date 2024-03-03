static void aSumTv02_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumTv02_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumTv02_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumTv02_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumTv02_func = {
	&aSumTv02_ct,
	&aSumTv02_mv,
	&aSumTv02_dw,
	&aSumTv02_dt,
	NULL,
};

aFTR_PROFILE iam_sum_tv02 = {
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
	aFTR_SHAPE_TYPEB_0,
	mCoBG_FTR_TYPEB_0,
	0,
	0,
	0,
	aFTR_INTERACTION_START_DISABLED,
	&aSumTv02_func,
};
