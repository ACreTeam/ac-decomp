static void aKobDisksystem8_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aKobDisksystem8_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKobDisksystem8_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aKobDisksystem8_dt(FTR_ACTOR* ftr_actor, u8* data);

extern u8 int_tak_nes_ds_tex_rgb_i4[];
extern u16 int_tak_nes_cl_pal[];
extern Gfx int_tak_nes01_on_model[];
extern Gfx int_tak_nes01_onT_model[];
extern Gfx int_tak_nes01_game_on_model[];

static void aKobDisksystem8_ct(FTR_ACTOR* ftr_actor, u8* data){

}

static void aKobDisksystem8_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){
    if(Common_Get(clip).my_room_clip != NULL){
        Common_Get(clip).my_room_clip->famicom_emu_common_move_proc(ftr_actor,my_room_actor,game,0,-1);
    }
}

static void aKobDisksystem8_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP,_Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8,int_tak_nes_ds_tex_rgb_i4);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_9,int_tak_nes_cl_pal);
    gSPDisplayList(NEXT_POLY_OPA_DISP,int_tak_nes01_on_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP,int_tak_nes01_onT_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP,int_tak_nes01_game_on_model);
    CLOSE_DISP(game->graph);
}

static void aKobDisksystem8_dt(FTR_ACTOR* ftr_actor, u8* data){

}

static aFTR_vtable_c aKobDisksystem8_func = {
	&aKobDisksystem8_ct,
	&aKobDisksystem8_mv,
	&aKobDisksystem8_dw,
	&aKobDisksystem8_dt,
	NULL,
};

aFTR_PROFILE iam_kob_disksystem8 = {
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
	aFTR_INTERACTION_FAMICOM_ITEM,
	&aKobDisksystem8_func,
};
