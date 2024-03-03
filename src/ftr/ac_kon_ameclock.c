static void aKonAmeclock_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonAmeclock_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonAmeclock_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonAmeclock_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aKonAmeclock_func = {
	&aKonAmeclock_ct,
	&aKonAmeclock_mv,
	&aKonAmeclock_dw,
	&aKonAmeclock_dt,
	NULL,
};

aFTR_PROFILE iam_kon_ameclock = {
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
	&aKonAmeclock_func,
};
