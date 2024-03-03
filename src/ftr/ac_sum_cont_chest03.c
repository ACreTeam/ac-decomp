static void aSumContChest03_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumContChest03_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumContChest03_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumContChest03_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumContChest03_func = {
	&aSumContChest03_ct,
	&aSumContChest03_mv,
	&aSumContChest03_dw,
	&aSumContChest03_dt,
	NULL,
};

aFTR_PROFILE iam_sum_cont_chest03 = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	18.0f,
	0.01f,
	aFTR_SHAPE_TYPEB_0,
	mCoBG_FTR_TYPEB_0,
	0,
	0,
	0,
	aFTR_INTERACTION_STORAGE_DRAWERS,
	&aSumContChest03_func,
};
