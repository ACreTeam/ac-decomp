extern Gfx int_sum_hal_mirror01_evw_model[];
extern Gfx int_sum_hal_mirror01_onT_model[];
static void aSumHalMirror01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c aSumHalMirror01_func = {
	NULL,
	NULL,
	&aSumHalMirror01_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_sum_hal_mirror01 = {
	int_sum_hal_mirror01_evw_model,
	int_sum_hal_mirror01_onT_model,
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
	&aSumHalMirror01_func,
};
