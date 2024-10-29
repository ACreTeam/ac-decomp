static void aFmanekin_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aFmanekin_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aFmanekin_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aFmanekin_dt(FTR_ACTOR* ftr_actor, u8* data);
static void aFmanekin_dma(mActor_name_t ftr_name, u8* data);

extern Gfx obj_shop_manekin_model[];

static void aFmanekin_ct(FTR_ACTOR* ftr_actor, u8* data) {
    
}
static void aFmanekin_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {

    GRAPH* graph = game->graph;
    
    OPEN_DISP(graph);
    
    
    gSPSegment(NEXT_POLY_OPA_DISP,8,data);
    gSPSegment(NEXT_POLY_OPA_DISP,9,data+0x200);

    gSPDisplayList(NEXT_POLY_OPA_DISP,obj_shop_manekin_model);

    CLOSE_DISP(graph);
}

static void aFmanekin_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){

}

static void aFmanekin_dt(FTR_ACTOR* ftr_actor, u8* data){

}

static void aFmanekin_dma(mActor_name_t ftr_name, u8* data){
    mPlib_Load_PlayerTexAndPallet(data,data+0x200, ((ftr_name >= FTR_CLOTH_START) && (ftr_name <= FTR_CLOTH_END)) ? (ftr_name - FTR_CLOTH_START) >> 2 : 0);
}

static aFTR_vtable_c aFmanekin_func = {
	&aFmanekin_ct,
	&aFmanekin_mv,
	&aFmanekin_dw,
	&aFmanekin_dt,
	&aFmanekin_dma,
};

aFTR_PROFILE iam_fmanekin = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	30.0f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	0,
	0,
	aFTR_INTERACTION_MANNEKIN,
	&aFmanekin_func,
};
