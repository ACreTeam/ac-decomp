static void aSumHalChest03_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumHalChest03_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumHalChest03_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumHalChest03_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumHalChest03_func = {
	&aSumHalChest03_ct,
	&aSumHalChest03_mv,
	&aSumHalChest03_dw,
	&aSumHalChest03_dt,
	NULL,
};

aFTR_PROFILE iam_sum_hal_chest03 = {
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
	aFTR_SHAPE_TYPEB_0,
	mCoBG_FTR_TYPEB_0,
	0,
	0,
	0,
	aFTR_INTERACTION_STORAGE_DRAWERS,
	&aSumHalChest03_func,
};
