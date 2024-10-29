extern Gfx int_sum_lv_stereo_on_model[];
extern Gfx int_sum_lv_stereo_onT_model[];
static void aSumLv_Stereo_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumLv_Stereo_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumLv_Stereo_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumLv_Stereo_dt(FTR_ACTOR* ftr_actor, u8* data);

static void aSumLv_Stereo_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void aSumLv_Stereo_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    (*Common_Get(clip).my_room_clip->mini_disk_common_move_proc)(ftr_actor, my_room_actor, game, 0.0f, 0.0f);
}

static void aSumLv_Stereo_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void aSumLv_Stereo_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumLv_Stereo_func = {
	&aSumLv_Stereo_ct,
	&aSumLv_Stereo_mv,
	&aSumLv_Stereo_dw,
	&aSumLv_Stereo_dt,
	NULL,
};

aFTR_PROFILE iam_sum_lv_stereo = {
	int_sum_lv_stereo_on_model,
	int_sum_lv_stereo_onT_model,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	18.0f,
	0.01f,
	aFTR_SHAPE_TYPEB_0,
	mCoBG_FTR_TYPEB_0,
	0,
	0,
	0,
	aFTR_INTERACTION_MUSIC_DISK,
	&aSumLv_Stereo_func,
};
