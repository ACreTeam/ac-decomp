static void aSumFruitchest03_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumFruitchest03_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumFruitchest03_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumFruitchest03_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumFruitchest03_func = {
	&aSumFruitchest03_ct,
	&aSumFruitchest03_mv,
	&aSumFruitchest03_dw,
	&aSumFruitchest03_dt,
	NULL,
};

aFTR_PROFILE iam_sum_fruitchest03 = {
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
	&aSumFruitchest03_func,
};
