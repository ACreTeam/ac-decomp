static void aSumBlueBureau01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumBlueBureau01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumBlueBureau01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumBlueBureau01_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumBlueBureau01_func = {
	&aSumBlueBureau01_ct,
	&aSumBlueBureau01_mv,
	&aSumBlueBureau01_dw,
	&aSumBlueBureau01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_blue_bureau01 = {
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
	&aSumBlueBureau01_func,
};
