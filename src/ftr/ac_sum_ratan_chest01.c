static void aSumRatanChest01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumRatanChest01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumRatanChest01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumRatanChest01_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumRatanChest01_func = {
	&aSumRatanChest01_ct,
	&aSumRatanChest01_mv,
	&aSumRatanChest01_dw,
	&aSumRatanChest01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_ratan_chest01 = {
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
	&aSumRatanChest01_func,
};
