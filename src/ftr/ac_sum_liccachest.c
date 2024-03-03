static void aSumLiccachest_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumLiccachest_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumLiccachest_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumLiccachest_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumLiccachest_func = {
	&aSumLiccachest_ct,
	&aSumLiccachest_mv,
	&aSumLiccachest_dw,
	&aSumLiccachest_dt,
	NULL,
};

aFTR_PROFILE iam_sum_liccachest = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	40.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	aFTR_INTERACTION_STORAGE_WARDROBE,
	&aSumLiccachest_func,
};
