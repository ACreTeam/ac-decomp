extern Gfx int_sum_cello01_on_model[];
extern Gfx int_sum_cello01_onT_model[];
static void aSumCello01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumCello01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumCello01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumCello01_dt(FTR_ACTOR* ftr_actor, u8* data);

static void aSumCello01_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void aSumCello01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (Common_Get(clip).my_room_clip != NULL) {
        Common_Get(clip).my_room_clip->sound_melody_proc(ftr_actor, my_room_actor, 10);
    }
}

static void aSumCello01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void aSumCello01_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumCello01_func = {
	&aSumCello01_ct,
	&aSumCello01_mv,
	&aSumCello01_dw,
	&aSumCello01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_cello01 = {
	int_sum_cello01_on_model,
	int_sum_cello01_onT_model,
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
	&aSumCello01_func,
};
