static void fYTCST_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fYTCST_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fYTCST_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fYTCST_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c fYTCST_func = {
	&fYTCST_ct,
	&fYTCST_mv,
	&fYTCST_dw,
	&fYTCST_dt,
	NULL,
};

aFTR_PROFILE iam_yaz_turkey_chest = {
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
	&fYTCST_func,
};
