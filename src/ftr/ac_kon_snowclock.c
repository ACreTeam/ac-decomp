static void aKonSnowclock_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonSnowclock_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonSnowclock_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonSnowclock_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aKonSnowclock_func = {
	&aKonSnowclock_ct,
	&aKonSnowclock_mv,
	&aKonSnowclock_dw,
	&aKonSnowclock_dt,
	NULL,
};

aFTR_PROFILE iam_kon_snowclock = {
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
	&aKonSnowclock_func,
};
