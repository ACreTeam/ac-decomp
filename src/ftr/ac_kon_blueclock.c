static void aKonBlueclock_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonBlueclock_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonBlueclock_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonBlueclock_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aKonBlueclock_func = {
	&aKonBlueclock_ct,
	&aKonBlueclock_mv,
	&aKonBlueclock_dw,
	&aKonBlueclock_dt,
	NULL,
};

aFTR_PROFILE iam_kon_blueclock = {
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
	&aKonBlueclock_func,
};
