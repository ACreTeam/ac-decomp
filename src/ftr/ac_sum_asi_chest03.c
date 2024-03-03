static void aSumAsiChest03_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumAsiChest03_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumAsiChest03_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumAsiChest03_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumAsiChest03_func = {
	&aSumAsiChest03_ct,
	&aSumAsiChest03_mv,
	&aSumAsiChest03_dw,
	&aSumAsiChest03_dt,
	NULL,
};

aFTR_PROFILE iam_sum_asi_chest03 = {
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
	&aSumAsiChest03_func,
};
