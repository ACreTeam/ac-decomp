static void aSumOldClk01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumOldClk01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumOldClk01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumOldClk01_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumOldClk01_func = {
	&aSumOldClk01_ct,
	&aSumOldClk01_mv,
	&aSumOldClk01_dw,
	&aSumOldClk01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_oldclk01 = {
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
	&aSumOldClk01_func,
};
