extern Gfx int_sum_saiconpo_on_model[];
static void aSumSaiconpo_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumSaiconpo_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumSaiconpo_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumSaiconpo_dt(FTR_ACTOR* ftr_actor, u8* data);

static void aSumSaiconpo_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void aSumSaiconpo_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (Common_Get(clip).my_room_clip != NULL) {
        (*Common_Get(clip).my_room_clip->mini_disk_common_move_proc)(ftr_actor, my_room_actor, game, 0.0f, 0.0f);
    }
}

static void aSumSaiconpo_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void aSumSaiconpo_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumSaiconpo_func = {
	&aSumSaiconpo_ct,
	&aSumSaiconpo_mv,
	&aSumSaiconpo_dw,
	&aSumSaiconpo_dt,
	NULL,
};

aFTR_PROFILE iam_sum_saiconpo = {
	int_sum_saiconpo_on_model,
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
	&aSumSaiconpo_func,
};
