static void aKonWaclock_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonWaclock_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonWaclock_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonWaclock_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aKonWaclock_func = {
	&aKonWaclock_ct,
	&aKonWaclock_mv,
	&aKonWaclock_dw,
	&aKonWaclock_dt,
	NULL,
};

aFTR_PROFILE iam_kon_waclock = {
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
	0,
	&aKonWaclock_func,
};
