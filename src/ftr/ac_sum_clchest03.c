static void aSumClChest03_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumClChest03_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumClChest03_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumClChest03_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumClChest03_func = {
	&aSumClChest03_ct,
	&aSumClChest03_mv,
	&aSumClChest03_dw,
	&aSumClChest03_dt,
	NULL,
};

aFTR_PROFILE iam_sum_clchest03 = {
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
	aFTR_INTERACTION_STORAGE_CLOSET,
	&aSumClChest03_func,
};
