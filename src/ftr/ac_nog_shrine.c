static void fNSH_ct(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void fNSH_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    // nothing
}

static void fNSH_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static Gfx* fNSH_GetTileGfx(int x0, int y0, GAME* game) {
    return two_tex_scroll_dolphin(game->graph, 0, x0, y0, 16, 16, 1, 0, 0, 0, 0);
}

extern Gfx int_nog_shrine_grass_model[];
extern Gfx int_nog_shrine_figure_model[];
extern Gfx int_nog_shrine_baseT_model[];
extern Gfx int_nog_shrine_waterT_model[];

static void fNSH_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    u32 ctr;
    Gfx* scroll_gfx;

    if (ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY) {
        ctr = play->game_frame;
    } else {
        ctr = game->frame_counter;
    }

    scroll_gfx = fNSH_GetTileGfx(ctr * 3, 0, game);

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_9, scroll_gfx);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_nog_shrine_grass_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_nog_shrine_figure_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_nog_shrine_baseT_model);
    gSPDisplayList(NEXT_POLY_XLU_DISP, int_nog_shrine_waterT_model);

    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c fNSH_func = {
    &fNSH_ct, &fNSH_mv, &fNSH_dw, &fNSH_dt, NULL,
};

aFTR_PROFILE iam_nog_shrine = {
    // clang-format off
	NULL,
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
	&fNSH_func,
    // clang-format on
};
