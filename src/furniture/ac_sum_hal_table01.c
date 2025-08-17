extern Gfx int_sum_hal_table01_on_model[];
extern Gfx int_sum_hal_table01_onT_model[];

aFTR_PROFILE iam_sum_hal_table01 = {
	int_sum_hal_table01_on_model,
	int_sum_hal_table01_onT_model,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
#if VERSION >= VER_GAFU01_00
	33.0f,
#else
	32.0f,
#endif
	0.01f,
	aFTR_SHAPE_TYPEC,
	mCoBG_FTR_TYPEC,
	0,
	0,
	0,
	0,
	NULL,
};
