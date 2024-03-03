static void aKonMusya_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonMusya_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonMusya_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonMusya_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aKonMusya_func = {
	&aKonMusya_ct,
	&aKonMusya_mv,
	&aKonMusya_dw,
	&aKonMusya_dt,
	NULL,
};

aFTR_PROFILE iam_kon_musya = {
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
	&aKonMusya_func,
};
