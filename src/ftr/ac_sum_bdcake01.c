static void aSB_SumBdcake01Ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSB_SumBdcake01Move(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSB_SumBdcake01Draw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c sum_bdcake01_func = {
	&aSB_SumBdcake01Ct,
	&aSB_SumBdcake01Move,
	&aSB_SumBdcake01Draw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_sum_bdcake01 = {
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
	&sum_bdcake01_func,
};
