static void aSumHalChest02_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumHalChest02_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumHalChest02_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumHalChest02_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumHalChest02_func = {
	&aSumHalChest02_ct,
	&aSumHalChest02_mv,
	&aSumHalChest02_dw,
	&aSumHalChest02_dt,
	NULL,
};

aFTR_PROFILE iam_sum_hal_chest02 = {
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
	aFTR_INTERACTION_STORAGE_CLOSET,
	&aSumHalChest02_func,
};
