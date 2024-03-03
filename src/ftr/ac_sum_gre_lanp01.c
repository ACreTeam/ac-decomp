extern Gfx int_sum_gre_lanp01_on_model[];
extern Gfx int_sum_gre_lanp01_onT_model[];
static void aSumGreLanp01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c aSumGreLanp01_func = {
	NULL,
	NULL,
	&aSumGreLanp01_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_sum_gre_lanp01 = {
	int_sum_gre_lanp01_on_model,
	int_sum_gre_lanp01_onT_model,
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
	&aSumGreLanp01_func,
};
