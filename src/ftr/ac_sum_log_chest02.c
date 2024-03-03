static void aSumBlaChest02_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumBlaChest02_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumBlaChest02_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumBlaChest02_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumBlaChest02_func = {
	&aSumBlaChest02_ct,
	&aSumBlaChest02_mv,
	&aSumBlaChest02_dw,
	&aSumBlaChest02_dt,
	NULL,
};

aFTR_PROFILE iam_sum_log_chest02 = {
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
	&aSumBlaChest02_func,
};
