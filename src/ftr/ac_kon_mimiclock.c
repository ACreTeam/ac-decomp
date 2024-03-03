static void aKonMimiclock_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonMimiclock_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonMimiclock_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonMimiclock_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aKonMimiclock_func = {
	&aKonMimiclock_ct,
	&aKonMimiclock_mv,
	&aKonMimiclock_dw,
	&aKonMimiclock_dt,
	NULL,
};

aFTR_PROFILE iam_kon_mimiclock = {
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
	2,
	0,
	0,
	&aKonMimiclock_func,
};
