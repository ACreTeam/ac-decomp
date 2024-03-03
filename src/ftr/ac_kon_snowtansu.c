static void aKonSnowtansu_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonSnowtansu_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonSnowtansu_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonSnowtansu_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aKonSnowtansu_func = {
	&aKonSnowtansu_ct,
	&aKonSnowtansu_mv,
	&aKonSnowtansu_dw,
	&aKonSnowtansu_dt,
	NULL,
};

aFTR_PROFILE iam_kon_snowtansu = {
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
	aFTR_INTERACTION_STORAGE_DRAWERS,
	&aKonSnowtansu_func,
};
