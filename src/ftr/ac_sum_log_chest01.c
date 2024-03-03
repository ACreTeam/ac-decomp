static void aSumLogChest01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumLogChest01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumLogChest01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumLogChest01_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumLogChest01_func = {
	&aSumLogChest01_ct,
	&aSumLogChest01_mv,
	&aSumLogChest01_dw,
	&aSumLogChest01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_log_chest01 = {
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
	&aSumLogChest01_func,
};
