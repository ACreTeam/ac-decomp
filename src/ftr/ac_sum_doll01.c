extern Gfx int_sum_doll01_on_model[];
extern Gfx int_sum_doll01_onT_model[];
static void aSumDoll01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c aSumDoll01_func = {
	NULL,
	NULL,
	&aSumDoll01_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_sum_doll01 = {
	int_sum_doll01_on_model,
	int_sum_doll01_onT_model,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	18.0f,
	0.01f,
	aFTR_SHAPE_TYPEC,
	mCoBG_FTR_TYPEC,
	0,
	0,
	0,
	0,
	&aSumDoll01_func,
};
