static void aSumFruittv01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumFruittv01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumFruittv01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumFruittv01_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumFruittv01_func = {
	&aSumFruittv01_ct,
	&aSumFruittv01_mv,
	&aSumFruittv01_dw,
	&aSumFruittv01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_fruittv01 = {
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
	&aSumFruittv01_func,
};
