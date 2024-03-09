extern Gfx int_sum_liccapiano_on_model[];
extern Gfx int_sum_liccapiano_onT_model[];
static void aSumLiccapiano_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumLiccapiano_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumLiccapiano_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumLiccapiano_dt(FTR_ACTOR* ftr_actor, u8* data);

static void aSumLiccapiano_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void aSumLiccapiano_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (Common_Get(clip).my_room_clip != NULL) {
        Common_Get(clip).my_room_clip->sound_melody_proc(ftr_actor, my_room_actor, 4);
    }
}

static void aSumLiccapiano_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void aSumLiccapiano_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumLiccapiano_func = {
	&aSumLiccapiano_ct,
	&aSumLiccapiano_mv,
	&aSumLiccapiano_dw,
	&aSumLiccapiano_dt,
	NULL,
};

aFTR_PROFILE iam_sum_liccapiano = {
	int_sum_liccapiano_on_model,
	int_sum_liccapiano_onT_model,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	18.0f,
	0.01f,
	aFTR_SHAPE_TYPEC,
	mCoBG_FTR_TYPEC,
	0,
	0,
	0,
	0,
	&aSumLiccapiano_func,
};
