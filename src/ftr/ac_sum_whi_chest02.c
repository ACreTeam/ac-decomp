static void aSumWhiChest02_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumWhiChest02_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumWhiChest02_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumWhiChest02_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumWhiChest02_func = {
	&aSumWhiChest02_ct,
	&aSumWhiChest02_mv,
	&aSumWhiChest02_dw,
	&aSumWhiChest02_dt,
	NULL,
};

aFTR_PROFILE iam_sum_whi_chest02 = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	27.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	aFTR_INTERACTION_STORAGE_WARDROBE,
	&aSumWhiChest02_func,
};
