extern Gfx int_hos_mario_hata_all_model[];
static void fHMD_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fHMD_func = {
	NULL,
	&fHMD_mv,
	NULL,
	NULL,
	NULL,
};

aFTR_PROFILE iam_hos_mario_hata = {
	int_hos_mario_hata_all_model,
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
	&fHMD_func,
};
