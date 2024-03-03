extern aFTR_rig_c &aKonSisiodosi_sklkey;
static void aKonSisiodosi_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonSisiodosi_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c aKonSisiodosi_func = {
	&aKonSisiodosi_ct,
	&aKonSisiodosi_mv,
	NULL,
	NULL,
	NULL,
};

aFTR_PROFILE iam_kon_sisiodosi = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aKonSisiodosi_sklkey,
	NULL,
	18.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	2,
	0,
	0,
	&aKonSisiodosi_func,
};
