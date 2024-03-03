static void aKonGrclock_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonGrclock_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonGrclock_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonGrclock_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aKonGrclock_func = {
	&aKonGrclock_ct,
	&aKonGrclock_mv,
	&aKonGrclock_dw,
	&aKonGrclock_dt,
	NULL,
};

aFTR_PROFILE iam_kon_grclock = {
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
	&aKonGrclock_func,
};
