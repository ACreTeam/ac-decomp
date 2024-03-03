static void aSumXChest02_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumXChest02_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumXChest02_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumXChest02_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumXChest02_func = {
	&aSumXChest02_ct,
	&aSumXChest02_mv,
	&aSumXChest02_dw,
	&aSumXChest02_dt,
	NULL,
};

aFTR_PROFILE iam_sum_x_chest02 = {
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
	&aSumXChest02_func,
};
