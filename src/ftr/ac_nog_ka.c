extern aFTR_rig_c &aNogKa_key_anime_data;
static void fNKA_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fNKA_func = {
	NULL,
	&fNKA_mv,
	NULL,
	NULL,
	NULL,
};

aFTR_PROFILE iam_nog_ka = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aNogKa_key_anime_data,
	NULL,
	30.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	2,
	0,
	aFTR_INTERACTION_INSECT,
	&fNKA_func,
};
