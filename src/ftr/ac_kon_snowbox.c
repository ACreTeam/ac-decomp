static void aKonSnowbox_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonSnowbox_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonSnowbox_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonSnowbox_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aKonSnowbox_func = {
	&aKonSnowbox_ct,
	&aKonSnowbox_mv,
	&aKonSnowbox_dw,
	&aKonSnowbox_dt,
	NULL,
};

aFTR_PROFILE iam_kon_snowbox = {
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
	&aKonSnowbox_func,
};
