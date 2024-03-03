static void aNogTriChest03_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aNogTriChest03_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aNogTriChest03_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aNogTriChest03_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aNogTriChest03_func = {
	&aNogTriChest03_ct,
	&aNogTriChest03_mv,
	&aNogTriChest03_dw,
	&aNogTriChest03_dt,
	NULL,
};

aFTR_PROFILE iam_nog_tri_chest03 = {
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
	aFTR_INTERACTION_STORAGE_CLOSET,
	&aNogTriChest03_func,
};
