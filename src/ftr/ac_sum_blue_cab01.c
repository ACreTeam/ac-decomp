static void aSumBlueCab01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumBlueCab01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumBlueCab01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumBlueCab01_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumBlueCab01_func = {
	&aSumBlueCab01_ct,
	&aSumBlueCab01_mv,
	&aSumBlueCab01_dw,
	&aSumBlueCab01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_blue_cab01 = {
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
	2,
	0,
	aFTR_INTERACTION_STORAGE_WARDROBE,
	&aSumBlueCab01_func,
};
