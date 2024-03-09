extern Gfx int_sum_timpani01_on_model[];
static void aSumTimpani01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aSumTimpani01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumTimpani01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aSumTimpani01_dt(FTR_ACTOR* ftr_actor, u8* data);

static void aSumTimpani01_ct(FTR_ACTOR* ftr_actor, u8* data){
}

static void aSumTimpani01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (Common_Get(clip).my_room_clip != NULL) {
        Common_Get(clip).my_room_clip->sound_melody_proc(ftr_actor, my_room_actor, 7);
    }
}

static void aSumTimpani01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void aSumTimpani01_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c aSumTimpani01_func = {
	&aSumTimpani01_ct,
	&aSumTimpani01_mv,
	&aSumTimpani01_dw,
	&aSumTimpani01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_timpani01 = {
	int_sum_timpani01_on_model,
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
	&aSumTimpani01_func,
};
