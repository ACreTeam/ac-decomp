#include "ac_douzou.h"

#include "m_time.h"
#include "m_common_data.h"
#include "m_name_table.h"
#include "m_house.h"

static void aDOU_actor_ct(ACTOR*, GAME*);
static void aDOU_actor_dt(ACTOR*, GAME*);
static void aDOU_actor_init(ACTOR*, GAME*);
static void aDOU_actor_draw(ACTOR*, GAME*);

ACTOR_PROFILE Douzou_Profile = {
    mAc_PROFILE_DOUZOU,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    DOUZOU,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(STRUCTURE_ACTOR),
    &aDOU_actor_ct,
    &aDOU_actor_dt,
    &aDOU_actor_init,
    &aDOU_actor_draw,
    NULL,
};

extern u8 obj_s_douzou_b1_tex_pic_i4[];
extern u8 obj_s_douzou_b2_tex_pic_i4[];
extern u8 obj_s_douzou_b3_tex_pic_i4[];
extern u8 obj_s_douzou_b4_tex_pic_i4[];
extern u8 obj_s_douzou_b5_tex_pic_i4[];
extern u8 obj_s_douzou_b6_tex_pic_i4[];
extern u8 obj_s_douzou_b7_tex_pic_i4[];
extern u8 obj_s_douzou_b8_tex_pic_i4[];
extern u8 obj_s_douzou_g1_tex_pic_i4[];
extern u8 obj_s_douzou_g2_tex_pic_i4[];
extern u8 obj_s_douzou_g3_tex_pic_i4[];
extern u8 obj_s_douzou_g4_tex_pic_i4[];
extern u8 obj_s_douzou_g5_tex_pic_i4[];
extern u8 obj_s_douzou_g6_tex_pic_i4[];
extern u8 obj_s_douzou_b7_tex_pic_i4[];
extern u8 obj_s_douzou_g8_tex_pic_i4[];

extern u8 obj_w_douzou_b1_tex_pic_i4[];
extern u8 obj_w_douzou_b2_tex_pic_i4[];
extern u8 obj_w_douzou_b3_tex_pic_i4[];
extern u8 obj_w_douzou_b4_tex_pic_i4[];
extern u8 obj_w_douzou_b5_tex_pic_i4[];
extern u8 obj_w_douzou_b6_tex_pic_i4[];
extern u8 obj_w_douzou_b7_tex_pic_i4[];
extern u8 obj_w_douzou_b8_tex_pic_i4[];
extern u8 obj_w_douzou_g1_tex_pic_i4[];
extern u8 obj_w_douzou_g2_tex_pic_i4[];
extern u8 obj_w_douzou_g3_tex_pic_i4[];
extern u8 obj_w_douzou_g4_tex_pic_i4[];
extern u8 obj_w_douzou_g5_tex_pic_i4[];
extern u8 obj_w_douzou_g6_tex_pic_i4[];
extern u8 obj_w_douzou_b7_tex_pic_i4[];
extern u8 obj_w_douzou_g8_tex_pic_i4[];

static u8* eye_tbl[2 * (mPr_SEX_NUM * mPr_FACE_TYPE_NUM)] = {
    obj_s_douzou_b1_tex_pic_i4, obj_s_douzou_b2_tex_pic_i4, obj_s_douzou_b3_tex_pic_i4, obj_s_douzou_b4_tex_pic_i4,
    obj_s_douzou_b5_tex_pic_i4, obj_s_douzou_b6_tex_pic_i4, obj_s_douzou_b7_tex_pic_i4, obj_s_douzou_b8_tex_pic_i4,
    obj_s_douzou_g1_tex_pic_i4, obj_s_douzou_g2_tex_pic_i4, obj_s_douzou_g3_tex_pic_i4, obj_s_douzou_g4_tex_pic_i4,
    obj_s_douzou_g5_tex_pic_i4, obj_s_douzou_g6_tex_pic_i4, obj_s_douzou_b7_tex_pic_i4, obj_s_douzou_g8_tex_pic_i4,

    obj_w_douzou_b1_tex_pic_i4, obj_w_douzou_b2_tex_pic_i4, obj_w_douzou_b3_tex_pic_i4, obj_w_douzou_b4_tex_pic_i4,
    obj_w_douzou_b5_tex_pic_i4, obj_w_douzou_b6_tex_pic_i4, obj_w_douzou_b7_tex_pic_i4, obj_w_douzou_b8_tex_pic_i4,
    obj_w_douzou_g1_tex_pic_i4, obj_w_douzou_g2_tex_pic_i4, obj_w_douzou_g3_tex_pic_i4, obj_w_douzou_g4_tex_pic_i4,
    obj_w_douzou_g5_tex_pic_i4, obj_w_douzou_g6_tex_pic_i4, obj_w_douzou_b7_tex_pic_i4, obj_w_douzou_g8_tex_pic_i4,
};

extern u8 obj_s_douzou_bm1_tex_pic_i4[];
extern u8 obj_s_douzou_bm2_tex_pic_i4[];
extern u8 obj_s_douzou_gm1_tex_pic_i4[];
extern u8 obj_s_douzou_gm2_tex_pic_i4[];

extern u8 obj_w_douzou_bm1_tex_pic_i4[];
extern u8 obj_w_douzou_bm2_tex_pic_i4[];
extern u8 obj_w_douzou_gm1_tex_pic_i4[];
extern u8 obj_w_douzou_gm2_tex_pic_i4[];

static u8* mouth_tbl[2 * (mPr_SEX_NUM * mPr_FACE_TYPE_NUM)] = {
    obj_s_douzou_bm2_tex_pic_i4, obj_s_douzou_bm1_tex_pic_i4, obj_s_douzou_bm1_tex_pic_i4, obj_s_douzou_bm2_tex_pic_i4,
    obj_s_douzou_bm1_tex_pic_i4, obj_s_douzou_bm1_tex_pic_i4, obj_s_douzou_bm1_tex_pic_i4, obj_s_douzou_bm2_tex_pic_i4,
    obj_s_douzou_gm1_tex_pic_i4, obj_s_douzou_gm1_tex_pic_i4, obj_s_douzou_gm1_tex_pic_i4, obj_s_douzou_gm1_tex_pic_i4,
    obj_s_douzou_gm2_tex_pic_i4, obj_s_douzou_gm1_tex_pic_i4, obj_s_douzou_gm1_tex_pic_i4, obj_s_douzou_gm1_tex_pic_i4,

    obj_w_douzou_bm2_tex_pic_i4, obj_w_douzou_bm1_tex_pic_i4, obj_w_douzou_bm1_tex_pic_i4, obj_w_douzou_bm2_tex_pic_i4,
    obj_w_douzou_bm1_tex_pic_i4, obj_w_douzou_bm1_tex_pic_i4, obj_w_douzou_bm1_tex_pic_i4, obj_w_douzou_bm2_tex_pic_i4,
    obj_w_douzou_gm1_tex_pic_i4, obj_w_douzou_gm1_tex_pic_i4, obj_w_douzou_gm1_tex_pic_i4, obj_w_douzou_gm1_tex_pic_i4,
    obj_w_douzou_gm2_tex_pic_i4, obj_w_douzou_gm1_tex_pic_i4, obj_w_douzou_gm1_tex_pic_i4, obj_w_douzou_gm1_tex_pic_i4,
};

static f32 zpostbl[mHS_HOUSE_NUM] = { 200.0f, 200.0f, 280.0f, 280.0f };
static f32 xpostbl[mHS_HOUSE_NUM] = { 0.0f, 200.0f, -40.0f, 160.0f };

extern Vtx obj_s_douzou_shadow_v[];
extern Gfx obj_s_douzou_shadow_model[];
static u8 aDOU_shadow_vtx_fix_flg_table[8] = { TRUE, FALSE, TRUE, FALSE, TRUE, FALSE, TRUE, FALSE };
static bIT_ShadowData_c aDOU_shadow_data = { 8, aDOU_shadow_vtx_fix_flg_table, 60.0f, obj_s_douzou_shadow_v,
                                             obj_s_douzou_shadow_model };

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_douzou;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_douzou;

static void aDOU_set_bgOffset(ACTOR*, int);
static void aDOU_setup_action(ACTOR*, int);
static void aDOU_keep_item(ACTOR*);

static void aDOU_actor_ct(ACTOR* actor, GAME* game) {
    static cKF_Skeleton_R_c* skl[2] = { &cKF_bs_r_obj_s_douzou, &cKF_bs_r_obj_w_douzou };

    STRUCTURE_ACTOR* douzou = (STRUCTURE_ACTOR*)actor;
    xyz_t wpos;

    douzou->season = Common_Get(time).season;
    cKF_SkeletonInfo_R_ct(&douzou->keyframe, skl[douzou->season == mTM_SEASON_WINTER], NULL, douzou->work_area,
                          douzou->morph_area);
    aDOU_set_bgOffset(actor, 1);

    wpos.x = actor->world.position.x + xpostbl[0];
    wpos.y = actor->world.position.y;
    wpos.z = actor->world.position.z + zpostbl[0];

    actor->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(wpos, 0.0f);
    actor->cull_width = 850.0f;
    actor->cull_radius = 850.0f;

    aDOU_setup_action((ACTOR*)douzou, 0);
    cKF_SkeletonInfo_R_play(&douzou->keyframe);
    aDOU_keep_item(actor);
}

static void aDOU_actor_dt(ACTOR* actor, GAME* game) {
    STRUCTURE_ACTOR* douzou = (STRUCTURE_ACTOR*)actor;

    cKF_SkeletonInfo_R_dt(&douzou->keyframe);
}

#include "../src/actor/ac_douzou_move.c_inc"
#include "../src/actor/ac_douzou_draw.c_inc"
