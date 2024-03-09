static void fIJT_ct(FTR_ACTOR* ftr_actor, u8* data);
static void fIJT_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fIJT_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void fIJT_dt(FTR_ACTOR* ftr_actor, u8* data);

extern u8 int_ike_jny_truthface1_TA_tex_txt[];
extern u8 int_ike_jny_truthface2_TA_tex_txt[];

extern Gfx int_ike_jny_truth01_body_model[];

static void fIJT_ct(FTR_ACTOR* ftr_actor, u8* data){
    ftr_actor->dynamic_work_s[0] = 0;
    ftr_actor->dynamic_work_s[1] = 0;
}

static void fIJT_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){
    GAME_PLAY* play = (GAME_PLAY*)game;
    PLAYER_ACTOR* player;

    player = GET_PLAYER_ACTOR(play);
    if (ftr_actor->dynamic_work_s[1] == 0){
        if (ftr_actor->switch_changed_flag != 0){
            aMR_SetSurprise(my_room_actor, player->actor_class.shape_info.rotation.y);
            ftr_actor->dynamic_work_s[0] = 0x32;
            ftr_actor->dynamic_work_s[1] = 1;
        }
    }
    else{
        ftr_actor->dynamic_work_s[0]--;
        if (ftr_actor->dynamic_work_s[0] == 0x14){
            mVibctl_entry(100, 1, 1, 13, 0, 7, 7, 0.0f);
        }
        if (ftr_actor->dynamic_work_s[0] < 0){
            ftr_actor->dynamic_work_s[0] = 0;
            ftr_actor->dynamic_work_s[1] = 0;
        }
    }
}

static void fIJT_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data){
    static u8* tex_table[] = {
    	int_ike_jny_truthface1_TA_tex_txt,int_ike_jny_truthface2_TA_tex_txt,
    };
    int idx;
    
    OPEN_DISP(game->graph);
    
    idx = ftr_actor->dynamic_work_s[1] & 1;
    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8,tex_table[idx]);
    gSPDisplayList(NEXT_POLY_OPA_DISP,int_ike_jny_truth01_body_model);
    
    CLOSE_DISP(game->graph);
}

static void fIJT_dt(FTR_ACTOR* ftr_actor, u8* data){

}

static aFTR_vtable_c fIJT_func = {
	&fIJT_ct,
	&fIJT_mv,
	&fIJT_dw,
	&fIJT_dt,
	NULL,
};

aFTR_PROFILE iam_ike_jny_truth01 = {
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
	aFTR_SHAPE_TYPEB_0,
	mCoBG_FTR_TYPEB_0,
	0,
	0,
	0,
	0,
	&fIJT_func,
};
