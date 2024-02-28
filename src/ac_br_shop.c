#include "ac_br_shop.h"
#include "m_common_data.h"
#include "m_name_table.h"
#include "m_player_lib.h"
#include "sys_matrix.h"

static void aBRS_actor_ct(ACTOR*, GAME*);
static void aBRS_actor_dt(ACTOR*, GAME*);
static void aBRS_actor_init(ACTOR*, GAME*);
static void aBRS_actor_draw(ACTOR*, GAME*);

ACTOR_PROFILE BrShop_Profile = {
    mAc_PROFILE_BRSHOP,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    0x5826, // fix name later
    ACTOR_OBJ_BANK_KEEP,
    sizeof(BRSHOP_ACTOR),
    aBRS_actor_ct,
    aBRS_actor_dt,
    aBRS_actor_init,
    aBRS_actor_draw,
    NULL,
};

u8 aBRS_shadow_vtx_fix_flg_table[] = { TRUE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, TRUE };

extern Vtx obj_yamishop_shadow_v[];
extern Gfx obj_yamishop_shadowT_model[];

bIT_ShadowData_c aBRS_shadow_data = {
    8, aBRS_shadow_vtx_fix_flg_table, 60.0f, obj_yamishop_shadow_v, obj_yamishop_shadowT_model,
};

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_yamishop;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_yamishop;
extern cKF_Animation_R_c cKF_ba_r_obj_s_yamishop;
extern cKF_Animation_R_c cKF_ba_r_obj_w_yamishop;

extern Gfx obj_s_yamishop_window_model[];
extern Gfx obj_w_yamishop_window_model[];

static void aBRS_set_bgOffset(STRUCTURE_ACTOR*, int);
static void aBRS_setup_action(STRUCTURE_ACTOR* actor, int type);
static void change_FGUnit(ACTOR*, int);

static void aBRS_actor_ct(ACTOR* actor, GAME* game) {
    static cKF_Skeleton_R_c* skl[] = {
        &cKF_bs_r_obj_s_yamishop,
        &cKF_bs_r_obj_w_yamishop,
    };
    GAME_PLAY* play = (GAME_PLAY*)game;
    BRSHOP_ACTOR* shop = (BRSHOP_ACTOR*)actor;
    lbRTC_time_c time;
    int action;
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR(play);
    int Px;
    int Pz;
    int x;
    int z;

    shop->structure_class.season = Common_Get(time.season);

    cKF_SkeletonInfo_R_ct(&shop->structure_class.keyframe, skl[shop->structure_class.season == mTM_SEASON_WINTER], NULL,
                          shop->structure_class.work_area, shop->structure_class.morph_area);

    aBRS_set_bgOffset(&shop->structure_class, 1);
    change_FGUnit(actor, 1);

    action = 0;
    actor->talk_distance = 80.0f;
    shop->structure_class.arg0 = 0;

    Px = player->actor_class.world.position.x;
    x = actor->world.position.x;
    z = (100.0f + actor->world.position.z);

    if (Px == x && (int)player->actor_class.world.position.z == z) {
        action = 1;
        shop->structure_class.arg0 = 1;
    } else {
        time = Save_Get(event_save_data.special.event.broker.end_time);
        if (mEv_CheckEvent(mEv_SPNPC_BROKER) != 0 && lbRTC_IsOverRTC(&time) == 0) {
            action = 1;
        } else {
            shop->structure_class.arg0 = 1;
        }
    }

    aBRS_setup_action(&shop->structure_class, action);
    cKF_SkeletonInfo_R_play(&shop->structure_class.keyframe);

    shop->structure_class.arg0_f = aBRS_ctrl_light(actor) != 0 ? 1.0f : 0.0f;
}

Door_data_c aBRS_br_shop_door_data = {
    SCENE_BROKER_SHOP, 4, FALSE, 0, { 160, 0, 280 }, EMPTY_NO, 1, { 0, 0, 0 },
};

static void aBRS_actor_dt(ACTOR* actor, GAME* game) {
    BRSHOP_ACTOR* shop = (BRSHOP_ACTOR*)actor;

    change_FGUnit(actor, 0);
    cKF_SkeletonInfo_R_dt(&shop->structure_class.keyframe);

    if (Save_Get(event_save_data.special.event.broker.used) >= 3) {
        mEv_special_event_soldout(75);
    }
}

#include "../src/ac_br_shop_move.c_inc"
#include "../src/ac_br_shop_draw.c_inc"
