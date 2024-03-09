extern Gfx int_sum_conpo02_on_model[];
extern Gfx int_sum_conpo02_evwT_model[];
extern Gfx int_sum_conpo02_p_topT_model[];
static void aSumConpo02_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumConpo02_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumConpo02_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumConpo02_dt(FTR_ACTOR* ftr_actor, u8* data);

static void aSumConpo02_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void aSumConpo02_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    (*Common_Get(clip).my_room_clip->mini_disk_common_move_proc)(ftr_actor, my_room_actor, game, 0.0f, 0.0f);
}

static void aSumConpo02_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void aSumConpo02_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumConpo02_func = {
	&aSumConpo02_ct,
	&aSumConpo02_mv,
	&aSumConpo02_dw,
	&aSumConpo02_dt,
	NULL,
};

aFTR_PROFILE iam_sum_conpo02 = {
	int_sum_conpo02_on_model,
	NULL,
	int_sum_conpo02_evwT_model,
	int_sum_conpo02_p_topT_model,
	NULL,
	NULL,
	NULL,
	NULL,
	18.0f,
	0.01f,
	aFTR_SHAPE_TYPEB_0,
	mCoBG_FTR_TYPEB_0,
	0,
	2,
	0,
	aFTR_INTERACTION_MUSIC_DISK,
	&aSumConpo02_func,
};
