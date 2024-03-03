static void aKonGomi04_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonGomi04_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonGomi04_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonGomi04_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aKonGomi04_func = {
	&aKonGomi04_ct,
	&aKonGomi04_mv,
	&aKonGomi04_dw,
	&aKonGomi04_dt,
	NULL,
};

aFTR_PROFILE iam_kon_gomi04 = {
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
	0,
	&aKonGomi04_func,
};
