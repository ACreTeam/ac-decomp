static void aKonsnowtv_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonsnowtv_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonsnowtv_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonsnowtv_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aKonsnowtv_func = {
	&aKonsnowtv_ct,
	&aKonsnowtv_mv,
	&aKonsnowtv_dw,
	&aKonsnowtv_dt,
	NULL,
};

aFTR_PROFILE iam_kon_snowtv = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	18.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	aFTR_INTERACTION_START_DISABLED,
	&aKonsnowtv_func,
};
