static void aNogTriChest02_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aNogTriChest02_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aNogTriChest02_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aNogTriChest02_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aNogTriChest02_func = {
	&aNogTriChest02_ct,
	&aNogTriChest02_mv,
	&aNogTriChest02_dw,
	&aNogTriChest02_dt,
	NULL,
};

aFTR_PROFILE iam_nog_tri_chest02 = {
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
	&aNogTriChest02_func,
};
