extern Gfx int_tak_table02_onT_model[];

aFTR_PROFILE iam_tak_table02 = {
	int_tak_table02_onT_model,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
#if VERSION >= VER_GAFU01_00
	31.0f,
#else
	30.0f,
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
