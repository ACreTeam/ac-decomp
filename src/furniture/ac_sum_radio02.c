extern Gfx int_sum_radio02_on_model[];
extern Gfx int_sum_radio02_onT_model[];
static void aSumRadio02_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumRadio02_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumRadio02_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumRadio02_dt(FTR_ACTOR* ftr_actor, u8* data);

static void aSumRadio02_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void aSumRadio02_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (Common_Get(clip).my_room_clip != NULL) {
        (*Common_Get(clip).my_room_clip->mini_disk_common_move_proc)(ftr_actor, my_room_actor, game, 0.0f, 0.0f);
    }
}

static void aSumRadio02_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void aSumRadio02_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumRadio02_func = {
	&aSumRadio02_ct,
	&aSumRadio02_mv,
	&aSumRadio02_dw,
	&aSumRadio02_dt,
	NULL,
};

aFTR_PROFILE iam_sum_radio02 = {
	int_sum_radio02_on_model,
	int_sum_radio02_onT_model,
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
	aFTR_INTERACTION_MUSIC_DISK,
	&aSumRadio02_func,
};
