extern Gfx int_sum_biwa01_on_model[];
extern Gfx int_sum_biwa01_onT_model[];
static void aSumBiwa01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumBiwa01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumBiwa01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumBiwa01_dt(FTR_ACTOR* ftr_actor, u8* data);

static void aSumBiwa01_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void aSumBiwa01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (Common_Get(clip).my_room_clip != NULL) {
        Common_Get(clip).my_room_clip->sound_melody_proc(ftr_actor, my_room_actor, 6);
    }
}

static void aSumBiwa01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void aSumBiwa01_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumBiwa01_func = {
	&aSumBiwa01_ct,
	&aSumBiwa01_mv,
	&aSumBiwa01_dw,
	&aSumBiwa01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_biwa01 = {
	int_sum_biwa01_on_model,
	int_sum_biwa01_onT_model,
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
	&aSumBiwa01_func,
};
