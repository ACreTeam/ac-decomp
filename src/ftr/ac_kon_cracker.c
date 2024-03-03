extern aFTR_rig_c &aKonCracker_sklkey;
static void aKonCracker_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonCracker_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonCracker_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonCracker_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aKonCracker_func = {
	&aKonCracker_ct,
	&aKonCracker_mv,
	&aKonCracker_dw,
	&aKonCracker_dt,
	NULL,
};

aFTR_PROFILE iam_kon_cracker = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aKonCracker_sklkey,
	NULL,
	18.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	0,
	&aKonCracker_func,
};
