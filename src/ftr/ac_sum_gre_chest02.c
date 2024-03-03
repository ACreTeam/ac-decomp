static void aSumGreChest02_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumGreChest02_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumGreChest02_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumGreChest02_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumGreChest02_func = {
	&aSumGreChest02_ct,
	&aSumGreChest02_mv,
	&aSumGreChest02_dw,
	&aSumGreChest02_dt,
	NULL,
};

aFTR_PROFILE iam_sum_gre_chest02 = {
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
	aFTR_INTERACTION_STORAGE_WARDROBE,
	&aSumGreChest02_func,
};
