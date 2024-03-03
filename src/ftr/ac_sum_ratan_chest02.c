static void aSumRatanChest02_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumRatanChest02_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumRatanChest02_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumRatanChest02_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumRatanChest02_func = {
	&aSumRatanChest02_ct,
	&aSumRatanChest02_mv,
	&aSumRatanChest02_dw,
	&aSumRatanChest02_dt,
	NULL,
};

aFTR_PROFILE iam_sum_ratan_chest02 = {
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
	&aSumRatanChest02_func,
};
