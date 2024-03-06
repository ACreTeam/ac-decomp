static void fYC_ct(FTR_ACTOR* ftr_actor, u8* data) {
    ftr_actor->dynamic_work_s[0] = -1;
}

static void fYC_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    // nothing
}

extern Gfx int_yaz_candle_body_model[];
extern Gfx int_yaz_candle_fire_model[];

extern u8 int_yaz_candle_fire1_tex_txt[];
extern u8 int_yaz_candle_fire2_tex_txt[];

static void fYC_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    u32 ctr_ofs;
    static u8* texture_table[] = { int_yaz_candle_fire1_tex_txt, int_yaz_candle_fire2_tex_txt };

    if (ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY) {
        ctr_ofs = play->game_frame;
    } else {
        ctr_ofs = game->frame_counter;
    }

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_9, texture_table[(ctr_ofs & 2) != 0]);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_yaz_candle_body_model);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_yaz_candle_fire_model);

    CLOSE_DISP(game->graph);
}

static void fYC_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static aFTR_vtable_c fYC_func = {
    &fYC_ct, &fYC_mv, &fYC_dw, &fYC_dt, NULL,
};

aFTR_PROFILE iam_yaz_candle = {
    // clang-format off
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	42.43f,
	0.01f,
	aFTR_SHAPE_TYPEA,
	mCoBG_FTR_TYPEA,
	0,
	1,
	0,
	0,
	&fYC_func,
    // clang-format on
};
