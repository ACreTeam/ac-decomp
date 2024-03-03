static void aKonRedclock_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonRedclock_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonRedclock_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonRedclock_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aKonRedclock_func = {
	&aKonRedclock_ct,
	&aKonRedclock_mv,
	&aKonRedclock_dw,
	&aKonRedclock_dt,
	NULL,
};

aFTR_PROFILE iam_kon_redclock = {
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
	&aKonRedclock_func,
};
