extern Gfx int_sum_taiko01_on_model[];
static void asumtaiko01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void asumtaiko01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void asumtaiko01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void asumtaiko01_dt(FTR_ACTOR* ftr_actor, u8* data);

static void asumtaiko01_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void asumtaiko01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (Common_Get(clip).my_room_clip != NULL) {
        Common_Get(clip).my_room_clip->sound_melody_proc(ftr_actor, my_room_actor, 13);
    }
}

static void asumtaiko01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void asumtaiko01_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c asumtaiko01_func = {
	&asumtaiko01_ct,
	&asumtaiko01_mv,
	&asumtaiko01_dw,
	&asumtaiko01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_taiko01 = {
	int_sum_taiko01_on_model,
	NULL,
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
	&asumtaiko01_func,
};
