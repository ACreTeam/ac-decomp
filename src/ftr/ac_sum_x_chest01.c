static void aSumXChest01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumXChest01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumXChest01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumXChest01_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumXChest01_func = {
	&aSumXChest01_ct,
	&aSumXChest01_mv,
	&aSumXChest01_dw,
	&aSumXChest01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_x_chest01 = {
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
	&aSumXChest01_func,
};
