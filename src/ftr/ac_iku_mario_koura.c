extern Gfx int_iku_mario_koura_model[];
static void fIMKoura_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fIMKoura_func = {
	NULL,
	&fIMKoura_mv,
	NULL,
	NULL,
	NULL,
};

aFTR_PROFILE iam_iku_mario_koura = {
	int_iku_mario_koura_model,
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
	&fIMKoura_func,
};
