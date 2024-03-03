static void aSumBlaChest03_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumBlaChest03_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumBlaChest03_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumBlaChest03_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumBlaChest03_func = {
	&aSumBlaChest03_ct,
	&aSumBlaChest03_mv,
	&aSumBlaChest03_dw,
	&aSumBlaChest03_dt,
	NULL,
};

aFTR_PROFILE iam_sum_bla_chest03 = {
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
	&aSumBlaChest03_func,
};
