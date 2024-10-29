static void fTOOL_ct(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

static void fTOOL_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    // nothing
}

static void fTOOL_dt(FTR_ACTOR* ftr_actor, u8* data) {
    // nothing
}

extern Gfx obj_netT_gfx_model[];
extern Gfx obj_netT_mat_model[];

extern Gfx obj_axeT_gfx_model[];
extern Gfx obj_axeT_mat_model[];

extern Gfx obj_shovelT_gfx_model[];
extern Gfx obj_shovelT_mat_model[];

extern Gfx obj_rodT_gfx_model[];
extern Gfx obj_rodT_mat_model[];

extern Gfx obj_rod_lineT_gfx_model[];
extern Gfx obj_rod_lineT_mat_model[];

static Gfx* fTOOL_mat_table[] = {
    obj_netT_mat_model,
    obj_axeT_mat_model,
    obj_shovelT_mat_model,
    obj_rod_lineT_mat_model,
};

static Gfx* fTOOL_gfx_table[] = {
    obj_netT_gfx_model,
    obj_axeT_gfx_model,
    obj_shovelT_gfx_model,
    obj_rod_lineT_gfx_model,
};

static void fTOOL_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    int tool_idx = (ftr_actor->name - 0x463) & 3;

    OPEN_DISP(game->graph);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_OPA_DISP, fTOOL_mat_table[tool_idx]);
    gSPDisplayList(NEXT_POLY_OPA_DISP, fTOOL_gfx_table[tool_idx]);

    if (ftr_actor->name == 0x466) {
        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NEXT_POLY_XLU_DISP, obj_rodT_mat_model);
        gSPDisplayList(NEXT_POLY_XLU_DISP, obj_rodT_gfx_model);
    }

    CLOSE_DISP(game->graph);
}

static aFTR_vtable_c fTOOL_func = {
    &fTOOL_ct, &fTOOL_mv, &fTOOL_dw, &fTOOL_dt, NULL,
};

aFTR_PROFILE iam_tool = {
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
	&fTOOL_func,
    // clang-format on
};
