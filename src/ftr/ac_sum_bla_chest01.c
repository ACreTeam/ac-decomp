static void aSumBlaChest01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumBlaChest01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumBlaChest01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumBlaChest01_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumBlaChest01_func = {
	&aSumBlaChest01_ct,
	&aSumBlaChest01_mv,
	&aSumBlaChest01_dw,
	&aSumBlaChest01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_bla_chest01 = {
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
	aFTR_INTERACTION_STORAGE_DRAWERS,
	&aSumBlaChest01_func,
};
