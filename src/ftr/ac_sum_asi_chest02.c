static void aSumAsiChest02_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumAsiChest02_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumAsiChest02_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumAsiChest02_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumAsiChest02_func = {
	&aSumAsiChest02_ct,
	&aSumAsiChest02_mv,
	&aSumAsiChest02_dw,
	&aSumAsiChest02_dt,
	NULL,
};

aFTR_PROFILE iam_sum_asi_chest02 = {
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
	&aSumAsiChest02_func,
};
