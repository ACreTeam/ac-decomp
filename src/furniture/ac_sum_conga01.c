extern Gfx int_sum_conga01_on_model[];
extern Gfx int_sum_conga01_onT_model[];
static void asumconga01_ct(FTR_ACTOR* ftr_actor, u8* data);
static void asumconga01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void asumconga01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void asumconga01_dt(FTR_ACTOR* ftr_actor, u8* data);

static void asumconga01_ct(FTR_ACTOR* ftr_actor, u8* data) {
}

static void asumconga01_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){
    if (Common_Get(clip).my_room_clip != NULL) {
        Common_Get(clip).my_room_clip->sound_melody_proc(ftr_actor, my_room_actor, 14);
    }
}

static void asumconga01_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
}

static void asumconga01_dt(FTR_ACTOR* ftr_actor, u8* data) {
}

static aFTR_vtable_c asumconga01_func = {
	&asumconga01_ct,
	&asumconga01_mv,
	&asumconga01_dw,
	&asumconga01_dt,
	NULL,
};

aFTR_PROFILE iam_sum_conga01 = {
	int_sum_conga01_on_model,
	int_sum_conga01_onT_model,
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
	&asumconga01_func,
};
