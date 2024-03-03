static void aSumClchest01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumClchest01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumClchest01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumClchest01_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumClchest01_func = {
	&aSumClchest01_ct,
	&aSumClchest01_mv,
	&aSumClchest01_dw,
	&aSumClchest01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_classicchest01 = {
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
	1,
	0,
	aFTR_INTERACTION_STORAGE_DRAWERS,
	&aSumClchest01_func,
};
