static void fSKP_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    // nothing
}

static Gfx* fSKP_GetTwoTileGfx(int x0, int y0, int x1, int y1, GAME* game) {
    return two_tex_scroll_dolphin(game->graph, 0, x0, y0, 16, 16, 1, x1, y1, 16, 16);
}

extern Gfx sugi_kpool_model[];
extern Gfx sugi_kpool_t_model[];
extern Gfx sugi_kpool_w_model[];
extern EVW_ANIME_DATA int_sugi_kpool_evw_anime;

static void fSKP_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    u32 ctr_ofs;
    Gfx* scroll_gfx;

    if (ftr_actor->ctr_type == aFTR_CTR_TYPE_GAME_PLAY) {
        ctr_ofs = play->game_frame;
    } else {
        ctr_ofs = game->frame_counter;
    }

    /* This scroll gfx goes unused lol... */
    scroll_gfx = fSKP_GetTwoTileGfx((-ctr_ofs * -1), 0, 0, (-ctr_ofs * -1) * 2, game);

    if (scroll_gfx != NULL) {
        OPEN_DISP(game->graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_POLY_OPA_DISP, sugi_kpool_t_model);
        gDPSetPrimColor(NEXT_POLY_XLU_DISP,      /* cmd */
                        0,                       /* m */
                        (160 + GETREG(CRV, 47)), /* l */
                        (55 + GETREG(CRV, 48)),  /* r */
                        (255 + GETREG(CRV, 49)), /* g */
                        (255 + GETREG(CRV, 50)), /* b */
                        (200 + GETREG(CRV, 51))  /* a */
        );
        gDPSetEnvColor(NEXT_POLY_XLU_DISP,      /* cmd */
                       (0 + GETREG(CRV, 52)),   /* r */
                       (155 + GETREG(CRV, 53)), /* g */
                       (205 + GETREG(CRV, 54)), /* b */
                       (255 + GETREG(CRV, 55))  /* a */
        );
        Evw_Anime_Set(play, &int_sugi_kpool_evw_anime); // scroll next texture
        gSPDisplayList(NEXT_POLY_XLU_DISP, sugi_kpool_w_model);
        gSPDisplayList(NEXT_POLY_XLU_DISP, sugi_kpool_model);

        CLOSE_DISP(game->graph);
    }
}

static aFTR_vtable_c fSKP_func = {
    NULL, &fSKP_mv, &fSKP_dw, NULL, NULL,
};

aFTR_PROFILE iam_sugi_kpool = {
    // clang-format off
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	41.0f,
	0.01f,
	aFTR_SHAPE_TYPEC,
	mCoBG_FTR_TYPEC,
	0,
	0,
	0,
	0,
	&fSKP_func,
    // clang-format on
};
