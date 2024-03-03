extern Gfx int_sum_whi_lanp_on_model[];
extern Gfx int_sum_whi_lanp_onT_model[];
static void aSumWhiLanp_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c aSumWhiLanp_func = {
	NULL,
	NULL,
	&aSumWhiLanp_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_sum_whi_lanp = {
	int_sum_whi_lanp_on_model,
	int_sum_whi_lanp_onT_model,
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
	&aSumWhiLanp_func,
};
