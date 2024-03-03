static void aSumWhiChest01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumWhiChest01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumWhiChest01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumWhiChest01_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumWhiChest01_func = {
	&aSumWhiChest01_ct,
	&aSumWhiChest01_mv,
	&aSumWhiChest01_dw,
	&aSumWhiChest01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_whi_chest01 = {
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
	aFTR_INTERACTION_STORAGE_DRAWERS,
	&aSumWhiChest01_func,
};
