static void aKonAtqclock_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonAtqclock_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonAtqclock_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonAtqclock_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aKonAtqclock_func = {
	&aKonAtqclock_ct,
	&aKonAtqclock_mv,
	&aKonAtqclock_dw,
	&aKonAtqclock_dt,
	NULL,
};

aFTR_PROFILE iam_kon_atqclock = {
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
	&aKonAtqclock_func,
};
