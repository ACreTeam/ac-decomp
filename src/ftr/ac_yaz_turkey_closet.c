static void fYTC_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fYTC_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fYTC_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fYTC_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fYTC_func = {
	&fYTC_ct,
	&fYTC_mv,
	&fYTC_dw,
	&fYTC_dt,
	NULL,
};

aFTR_PROFILE iam_yaz_turkey_closet = {
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
	&fYTC_func,
};
