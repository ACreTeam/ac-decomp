extern Gfx int_sum_whi_mirror_evw_model[];
extern Gfx int_sum_whi_mirror_onT_model[];
static void aSumWhiMirror_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c aSumWhiMirror_func = {
	NULL,
	NULL,
	&aSumWhiMirror_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_sum_whi_mirror = {
	int_sum_whi_mirror_evw_model,
	int_sum_whi_mirror_onT_model,
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
	1,
	0,
	0,
	&aSumWhiMirror_func,
};
