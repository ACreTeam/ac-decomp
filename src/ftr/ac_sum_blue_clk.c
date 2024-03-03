static void aSumBlueClk_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumBlueClk_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumBlueClk_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumBlueClk_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumBlueClk_func = {
	&aSumBlueClk_ct,
	&aSumBlueClk_mv,
	&aSumBlueClk_dw,
	&aSumBlueClk_dt,
	NULL,
};

aFTR_PROFILE iam_sum_blue_clk = {
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
	&aSumBlueClk_func,
};
