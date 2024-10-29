static void aKonMusya_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKonMusya_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonMusya_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKonMusya_dt(FTR_ACTOR* ftr_actor, u8* data);

extern Gfx int_kon_musya_atama_onT_model[];
extern Gfx int_kon_musya_atama_on_model[];
extern Gfx int_kon_musya_dou_onT_model[];
extern Gfx int_kon_musya_hako_on_model[];
extern Gfx int_kon_musya_tare_onT_model[];

static void aKonMusya_ct(FTR_ACTOR* ftr_actor, u8* data){ 

}

static void aKonMusya_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){
}

static void aKonMusya_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP,_Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPDisplayList(NEXT_POLY_OPA_DISP,int_kon_musya_hako_on_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP,int_kon_musya_atama_on_model);
 
    gSPDisplayList(NEXT_POLY_OPA_DISP,int_kon_musya_tare_onT_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP,int_kon_musya_dou_onT_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP,int_kon_musya_atama_onT_model);

    CLOSE_DISP(game->graph);
} 

static void aKonMusya_dt(FTR_ACTOR* ftr_actor, u8* data){ 
    
}

static aFTR_vtable_c aKonMusya_func = {
	&aKonMusya_ct,
	&aKonMusya_mv,
	&aKonMusya_dw,
	&aKonMusya_dt,
	NULL,
};

aFTR_PROFILE iam_kon_musya = {
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
	&aKonMusya_func,
};
