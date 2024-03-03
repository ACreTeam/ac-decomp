extern Gfx sugi_barbecue_model[];
extern Gfx sugi_barbecue_b_model[];
static void gSBBQ_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

static aFTR_vtable_c gSBBQ_func = {
	NULL,
	&gSBBQ_mv,
	NULL,
	NULL,
	NULL,
};

aFTR_PROFILE iam_sugi_barbecue = {
	sugi_barbecue_model,
	sugi_barbecue_b_model,
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
	&gSBBQ_func,
};
