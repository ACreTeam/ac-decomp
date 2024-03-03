extern Gfx int_sum_bla_lanp_on_model[];
extern Gfx int_sum_bla_lanp_onT_model[];
static void aSumBlaLanp_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c aSumBlaLanp_func = {
	NULL,
	NULL,
	&aSumBlaLanp_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_sum_bla_lanp = {
	int_sum_bla_lanp_on_model,
	int_sum_bla_lanp_onT_model,
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
	&aSumBlaLanp_func,
};
