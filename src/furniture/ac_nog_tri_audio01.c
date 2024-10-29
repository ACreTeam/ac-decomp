extern Gfx int_nog_tri_audio01_model[];
static void aNogTriAudio01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aNogTriAudio01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aNogTriAudio01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aNogTriAudio01_dt(FTR_ACTOR* ftr_actor, u8* data);

static void aNogTriAudio01_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void aNogTriAudio01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    (*Common_Get(clip).my_room_clip->mini_disk_common_move_proc)(ftr_actor, my_room_actor, game, 0.0f, 0.0f);
}

static void aNogTriAudio01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void aNogTriAudio01_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aNogTriAudio01_func = {
	&aNogTriAudio01_ct,
	&aNogTriAudio01_mv,
	&aNogTriAudio01_dw,
	&aNogTriAudio01_dt,
	NULL,
};

aFTR_PROFILE iam_nog_tri_audio01 = {
	int_nog_tri_audio01_model,
	NULL,
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
	&aNogTriAudio01_func,
};
