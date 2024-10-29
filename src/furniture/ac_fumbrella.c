static void aFU_ct(FTR_ACTOR* ftr_actor, u8* data);
static void aFU_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aFU_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data);
static void aFU_dt(FTR_ACTOR* ftr_actor, u8* data);
static void aFU_dma(mActor_name_t ftr_name, u8* data);

extern Gfx obj_shop_umb01_model[];
extern Gfx obj_shop_umb01_modelT[];
extern Gfx obj_shop_umb02_model[];
extern Gfx obj_shop_umb02_modelT[];

extern Gfx obj_shop_umb03_model[];
extern Gfx obj_shop_umb03_modelT[];
extern Gfx obj_shop_umb04_model[];
extern Gfx obj_shop_umb04_modelT[];

extern Gfx obj_shop_umb05_model[];
extern Gfx obj_shop_umb05_modelT[];
extern Gfx obj_shop_umb06_model[];
extern Gfx obj_shop_umb06_modelT[];

extern Gfx obj_shop_umb07_model[];
extern Gfx obj_shop_umb07_modelT[];
extern Gfx obj_shop_umb08_model[];
extern Gfx obj_shop_umb08_modelT[];

extern Gfx obj_shop_umb09_model[];
extern Gfx obj_shop_umb09_modelT[];
extern Gfx obj_shop_umb10_model[];
extern Gfx obj_shop_umb10_modelT[];

extern Gfx obj_shop_umb11_model[];
extern Gfx obj_shop_umb11_modelT[];
extern Gfx obj_shop_umb12_model[];
extern Gfx obj_shop_umb12_modelT[];

extern Gfx obj_shop_umb13_model[];
extern Gfx obj_shop_umb13_modelT[];
extern Gfx obj_shop_umb14_model[];
extern Gfx obj_shop_umb14_modelT[];

extern Gfx obj_shop_umb15_model[];
extern Gfx obj_shop_umb15_modelT[];
extern Gfx obj_shop_umb16_model[];
extern Gfx obj_shop_umb16_modelT[];

extern Gfx obj_shop_umb17_model[];
extern Gfx obj_shop_umb17_modelT[];
extern Gfx obj_shop_umb18_model[];
extern Gfx obj_shop_umb18_modelT[];

extern Gfx obj_shop_umb19_model[];
extern Gfx obj_shop_umb19_modelT[];
extern Gfx obj_shop_umb20_model[];
extern Gfx obj_shop_umb20_modelT[];

extern Gfx obj_shop_umb21_model[];
extern Gfx obj_shop_umb21_modelT[];
extern Gfx obj_shop_umb22_model[];
extern Gfx obj_shop_umb22_modelT[];

extern Gfx obj_shop_umb23_model[];
extern Gfx obj_shop_umb23_modelT[];
extern Gfx obj_shop_umb24_model[];
extern Gfx obj_shop_umb24_modelT[];

extern Gfx obj_shop_umb25_model[];
extern Gfx obj_shop_umb25_modelT[];
extern Gfx obj_shop_umb26_model[];
extern Gfx obj_shop_umb26_modelT[];

extern Gfx obj_shop_umb27_model[];
extern Gfx obj_shop_umb27_modelT[];
extern Gfx obj_shop_umb28_model[];
extern Gfx obj_shop_umb28_modelT[];

extern Gfx obj_shop_umb29_model[];
extern Gfx obj_shop_umb29_modelT[];
extern Gfx obj_shop_umb30_model[];
extern Gfx obj_shop_umb30_modelT[];

extern Gfx obj_shop_umb31_model[];
extern Gfx obj_shop_umb31_modelT[];
extern Gfx obj_shop_umb32_model[];
extern Gfx obj_shop_umb32_modelT[];

typedef struct furniture_ambrella_data_s {
    Gfx* opaque;
    Gfx* trans;
} aFU_Data_c;

static aFU_Data_c aFU_data[] = {
    obj_shop_umb01_model,  obj_shop_umb01_modelT, obj_shop_umb02_model,  obj_shop_umb02_modelT, obj_shop_umb03_model,
    obj_shop_umb03_modelT, obj_shop_umb04_model,  obj_shop_umb04_modelT, obj_shop_umb05_model,  obj_shop_umb05_modelT,
    obj_shop_umb06_model,  obj_shop_umb06_modelT, obj_shop_umb07_model,  obj_shop_umb07_modelT, obj_shop_umb08_model,
    obj_shop_umb08_modelT, obj_shop_umb09_model,  obj_shop_umb09_modelT, obj_shop_umb10_model,  obj_shop_umb10_modelT,
    obj_shop_umb11_model,  obj_shop_umb11_modelT, obj_shop_umb12_model,  obj_shop_umb12_modelT, obj_shop_umb13_model,
    obj_shop_umb13_modelT, obj_shop_umb14_model,  obj_shop_umb14_modelT, obj_shop_umb15_model,  obj_shop_umb15_modelT,
    obj_shop_umb16_model,  obj_shop_umb16_modelT, obj_shop_umb17_model,  obj_shop_umb17_modelT, obj_shop_umb18_model,
    obj_shop_umb18_modelT, obj_shop_umb19_model,  obj_shop_umb19_modelT, obj_shop_umb20_model,  obj_shop_umb20_modelT,
    obj_shop_umb21_model,  obj_shop_umb21_modelT, obj_shop_umb22_model,  obj_shop_umb22_modelT, obj_shop_umb23_model,
    obj_shop_umb23_modelT, obj_shop_umb24_model,  obj_shop_umb24_modelT, obj_shop_umb25_model,  obj_shop_umb25_modelT,
    obj_shop_umb26_model,  obj_shop_umb26_modelT, obj_shop_umb27_model,  obj_shop_umb27_modelT, obj_shop_umb28_model,
    obj_shop_umb28_modelT, obj_shop_umb29_model,  obj_shop_umb29_modelT, obj_shop_umb30_model,  obj_shop_umb30_modelT,
    obj_shop_umb31_model,  obj_shop_umb31_modelT, obj_shop_umb32_model,  obj_shop_umb32_modelT,
};

static void aFU_ct(FTR_ACTOR* ftr_actor, u8* data) {

}

static void aFU_dw(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {
    if (ftr_actor != NULL) {
        int idx;
        Gfx* gfx;
        OPEN_DISP(game->graph);

        idx = ((ftr_actor->name - 0x342) & 0x1F);

        gSPDisplayList(NEXT_POLY_OPA_DISP, aFU_data[idx].opaque);

        gSPDisplayList(NEXT_POLY_XLU_DISP, aFU_data[idx].trans);

        CLOSE_DISP(game->graph);
    }
}

static void aFU_mv(FTR_ACTOR* ftr_actor, ACTOR* my_room_actor, GAME* game, u8* data) {

}

static void aFU_dt(FTR_ACTOR* ftr_actor, u8* data) {

}

static void aFU_dma(mActor_name_t ftr_name, u8* data) {

}

static aFTR_vtable_c aFU_func = {
	&aFU_ct,
	&aFU_mv,
	&aFU_dw,
	&aFU_dt,
	&aFU_dma,
};

aFTR_PROFILE iam_fumbrella = {
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
	aFTR_INTERACTION_UMBRELLA,
	&aFU_func,
};
