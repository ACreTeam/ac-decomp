static void aSumHalClk01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumHalClk01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumHalClk01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumHalClk01_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumHalClk01_func = {
	&aSumHalClk01_ct,
	&aSumHalClk01_mv,
	&aSumHalClk01_dw,
	&aSumHalClk01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_hal_clk01 = {
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
	&aSumHalClk01_func,
};
