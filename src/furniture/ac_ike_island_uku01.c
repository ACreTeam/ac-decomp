extern Gfx int_ike_island_uku01_body_model[];
static void fIIUKRR_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static void fIIUKRR_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){
    if (Common_Get(clip).my_room_clip != NULL) {
        Common_Get(clip).my_room_clip->sound_melody_proc(ftr_actor,my_room_actor,15);
    }
} 

static aFTR_vtable_c fIIUKRR_func = {
	NULL,
	&fIIUKRR_mv,
	NULL,
	NULL,
	NULL,
};

aFTR_PROFILE iam_ike_island_uku01 = {
	int_ike_island_uku01_body_model,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	15.7f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	0,
	&fIIUKRR_func,
};
