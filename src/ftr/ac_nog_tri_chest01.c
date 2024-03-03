static void aNogTriChest01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aNogTriChest01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aNogTriChest01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aNogTriChest01_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aNogTriChest01_func = {
	&aNogTriChest01_ct,
	&aNogTriChest01_mv,
	&aNogTriChest01_dw,
	&aNogTriChest01_dt,
	NULL,
};

aFTR_PROFILE iam_nog_tri_chest01 = {
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
	&aNogTriChest01_func,
};
