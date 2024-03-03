extern Gfx int_sum_hal_lanp01_off_model[];
extern Gfx int_sum_hal_lanp01_onT_model[];
static void aSumHalLanp01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c aSumHalLanp01_func = {
	NULL,
	NULL,
	&aSumHalLanp01_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_sum_hal_lanp01 = {
	int_sum_hal_lanp01_off_model,
	int_sum_hal_lanp01_onT_model,
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
	&aSumHalLanp01_func,
};
