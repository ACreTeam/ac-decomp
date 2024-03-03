static void aSumContChest02_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumContChest02_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumContChest02_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumContChest02_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumContChest02_func = {
	&aSumContChest02_ct,
	&aSumContChest02_mv,
	&aSumContChest02_dw,
	&aSumContChest02_dt,
	NULL,
};

aFTR_PROFILE iam_sum_cont_chest02 = {
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
	aFTR_INTERACTION_STORAGE_WARDROBE,
	&aSumContChest02_func,
};
