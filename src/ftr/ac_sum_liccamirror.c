extern Gfx int_sum_liccamirror_on_model[];
extern Gfx int_sum_liccamirror_onT_model[];
static void aSumLiccaMirror_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c aSumLiccaMirror_func = {
	NULL,
	NULL,
	&aSumLiccaMirror_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_sum_liccamirror = {
	int_sum_liccamirror_on_model,
	int_sum_liccamirror_onT_model,
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
	&aSumLiccaMirror_func,
};
