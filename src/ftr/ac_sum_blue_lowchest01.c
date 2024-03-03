static void aSumBlueLowChest01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumBlueLowChest01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumBlueLowChest01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumBlueLowChest01_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumBlueLowChest01_func = {
	&aSumBlueLowChest01_ct,
	&aSumBlueLowChest01_mv,
	&aSumBlueLowChest01_dw,
	&aSumBlueLowChest01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_blue_lowchest01 = {
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
	&aSumBlueLowChest01_func,
};
