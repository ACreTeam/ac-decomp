static void aSumfruitclk_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumfruitclk_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumfruitclk_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumfruitclk_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumfruitclk_func = {
	&aSumfruitclk_ct,
	&aSumfruitclk_mv,
	&aSumfruitclk_dw,
	&aSumfruitclk_dt,
	NULL,
};

aFTR_PROFILE iam_sum_fruitclk = {
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
	&aSumfruitclk_func,
};
