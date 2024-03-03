extern Gfx int_sum_harp_on_model[];
extern Gfx int_sum_harp_onT_model[];
static void aSumHarp_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumHarp_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumHarp_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumHarp_dt(FTR_ACTOR* ftr_actor, u8* data);

static aFTR_vtable_c aSumHarp_func = {
	&aSumHarp_ct,
	&aSumHarp_mv,
	&aSumHarp_dw,
	&aSumHarp_dt,
	NULL,
};

aFTR_PROFILE iam_sum_harp = {
	int_sum_harp_on_model,
	int_sum_harp_onT_model,
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
	&aSumHarp_func,
};
