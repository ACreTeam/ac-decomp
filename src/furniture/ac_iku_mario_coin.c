static void fIMC_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (aFTR_CAN_PLAY_SE(ftr_actor)) {
        if (ftr_actor->switch_changed_flag == TRUE) {
            sAdo_OngenTrgStart(0x17A, &ftr_actor->position);
        }
    }
}

extern u16 int_iku_mario_coin_a_pal[];
extern u16 int_iku_mario_coin_b_pal[];
extern u16 int_iku_mario_coin_c_pal[];

static u16* fIMC_palette_table[] = {
    // clang-format off
	int_iku_mario_coin_a_pal,
	int_iku_mario_coin_a_pal,
	int_iku_mario_coin_a_pal,
	int_iku_mario_coin_a_pal,
	int_iku_mario_coin_b_pal,
	int_iku_mario_coin_c_pal,
	int_iku_mario_coin_b_pal,
    // clang-format on
};

extern Gfx int_iku_mario_coin_model[];

static void fIMC_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    u32 ctr_ofs;

    if (ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY) {
        ctr_ofs = play->game_frame;
    } else {
        ctr_ofs = game->frame_counter;
    }

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_9,
               fIMC_palette_table[(ctr_ofs / 8) % ARRAY_COUNT(fIMC_palette_table)]);
    gSPDisplayList(NEXT_POLY_OPA_DISP, int_iku_mario_coin_model);

    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c fIMC_func = {
    NULL, &fIMC_mv, &fIMC_dw, NULL, NULL,
};

aFTR_PROFILE iam_iku_mario_coin = {
    // clang-format off
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
	&fIMC_func,
	// clang-format off
};
