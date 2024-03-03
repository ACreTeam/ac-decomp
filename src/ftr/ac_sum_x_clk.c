static void aSumXClk_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumXClk_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumXClk_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumXClk_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumXClk_func = {
	&aSumXClk_ct,
	&aSumXClk_mv,
	&aSumXClk_dw,
	&aSumXClk_dt,
	NULL,
};

aFTR_PROFILE iam_sum_x_clk = {
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
	&aSumXClk_func,
};
