static void fNBT_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);

extern Gfx int_nog_beachtable_bodyT_model[];
extern Gfx int_nog_beachtable_bubbleT_model[];
extern Gfx int_nog_beachtable_glassT_model[];

static void fNBT_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){
    GAME_PLAY* play = (GAME_PLAY*)game;
    
    Gfx*  gfx = fFTR_GetTwoTileGfx(16, 16, 0, 1, 16, 16, 0, 0, play, ftr_actor, 0);

    if(gfx != NULL){
        OPEN_DISP(game->graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPDisplayList(NEXT_POLY_OPA_DISP,int_nog_beachtable_bodyT_model);
        gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_9, gfx);

        gSPDisplayList(NEXT_POLY_XLU_DISP,int_nog_beachtable_glassT_model);
        gSPDisplayList(NEXT_POLY_XLU_DISP,int_nog_beachtable_bubbleT_model);
        CLOSE_DISP(game->graph);
    }
}

static aFTR_vtable_c fNBT_func = {
	NULL,
	NULL,
	&fNBT_dw,
	NULL,
	NULL,
};

aFTR_PROFILE iam_nog_beachtable = {
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
	0,
	&fNBT_func,
};
