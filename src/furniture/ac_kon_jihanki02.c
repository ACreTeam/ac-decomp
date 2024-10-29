static void aKonJihanki02_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonJihanki02_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonJihanki02_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonJihanki02_dt(FTR_ACTOR* ftr_actor, u8* data);

extern Gfx int_kon_jihanki02_offT_model[];
extern Gfx int_kon_jihanki02_off_model[];
extern Gfx int_kon_jihanki02_onT_model[];
extern Gfx int_kon_jihanki02_on_model[];

static void aKonJihanki02_ct(FTR_ACTOR* ftr_actor, u8* data){

}

static void aKonJihanki02_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){
}

static void aKonJihanki02_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP,_Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(NEXT_POLY_OPA_DISP,int_kon_jihanki02_on_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP,int_kon_jihanki02_off_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP,int_kon_jihanki02_onT_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP,int_kon_jihanki02_offT_model);
    
    CLOSE_DISP(game->graph);
}

static void aKonJihanki02_dt(FTR_ACTOR* ftr_actor, u8* data){
    
}

static aFTR_vtable_c aKonJihanki02_func = {
	&aKonJihanki02_ct,
	&aKonJihanki02_mv,
	&aKonJihanki02_dw,
	&aKonJihanki02_dt,
	NULL,
};

aFTR_PROFILE iam_kon_jihanki02 = {
	NULL,
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
	&aKonJihanki02_func,
};
