static void aSumFruitchest01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumFruitchest01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumFruitchest01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumFruitchest01_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumFruitchest01_func = {
	&aSumFruitchest01_ct,
	&aSumFruitchest01_mv,
	&aSumFruitchest01_dw,
	&aSumFruitchest01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_fruitchest01 = {
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
	&aSumFruitchest01_func,
};
