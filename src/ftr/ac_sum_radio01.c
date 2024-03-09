extern Gfx int_sum_radio01_on_model[];
extern Gfx int_sum_radio01_onT_model[];
static void aSumRadio01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumRadio01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumRadio01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumRadio01_dt(FTR_ACTOR* ftr_actor, u8* data);

static void aSumRadio01_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void aSumRadio01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (Common_Get(clip).my_room_clip != NULL) {
        (*Common_Get(clip).my_room_clip->mini_disk_common_move_proc)(ftr_actor, my_room_actor, game, 0.0f, 0.0f);
    }
}

static void aSumRadio01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void aSumRadio01_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumRadio01_func = {
	&aSumRadio01_ct,
	&aSumRadio01_mv,
	&aSumRadio01_dw,
	&aSumRadio01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_radio01 = {
	int_sum_radio01_on_model,
	int_sum_radio01_onT_model,
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
	&aSumRadio01_func,
};
