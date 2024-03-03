extern aFTR_rig_c &aNogKaeru_key_anime_data;
static void fNKR_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c fNKR_func = {
	NULL,
	&fNKR_mv,
	NULL,
	NULL,
	NULL,
};

aFTR_PROFILE iam_nog_kaeru = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	&aNogKaeru_key_anime_data,
	NULL,
	30.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	2,
	0,
	aFTR_INTERACTION_FISH,
	&fNKR_func,
};
