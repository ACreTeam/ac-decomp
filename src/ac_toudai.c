#include "ac_toudai.h"

#include "m_name_table.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "bg_item.h"
#include "m_player_lib.h"
#include "m_common_data.h"
#include "m_bgm.h"
#include "m_soncho.h"

static void aTOU_actor_ct(ACTOR*, GAME*);
static void aTOU_actor_dt(ACTOR*, GAME*);
static void aTOU_actor_init(ACTOR*, GAME*);
static void aTOU_actor_draw(ACTOR*, GAME*);

ACTOR_PROFILE Toudai_Profile = {
    mAc_PROFILE_TOUDAI,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    TOUDAI,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(TOUDAI_ACTOR),
    aTOU_actor_ct,
    aTOU_actor_dt,
    aTOU_actor_init,
    aTOU_actor_draw,
    NULL,
};

extern Vtx obj_s_toudai_shadow_v[];
extern Gfx obj_s_toudai_shadow_1_model[];

u8 aTOU_shadow_vtx_fix_flg_table[] = {
    1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0,
};

bIT_ShadowData_c aTOU_shadow_data = {
    10, aTOU_shadow_vtx_fix_flg_table, 60.0f, obj_s_toudai_shadow_v, obj_s_toudai_shadow_1_model,
};

static void aTOU_set_bgOffset(TOUDAI_ACTOR*, int);
static void aTOU_setup_action(ACTOR*, int);

static void aTOU_fgunit_on(ACTOR* actor) {
    TOUDAI_ACTOR* light = (TOUDAI_ACTOR*)actor;

    xyz_t pos;
    int i;
    mActor_name_t* nameptr;

    xyz_t_move(&pos, &light->actor_class.home.position);

    pos.x -= 40.0f;
    pos.z -= 80.0f;
    for (i = 0; i < 2; i++) {
        nameptr = mFI_GetUnitFG(pos);
        if (nameptr != NULL) {
            if (mSN_ClearSnowman(nameptr) == 0) {
                if (((*nameptr >= 0x2A) && (*nameptr <= 0x42)) || (*nameptr == 0x5C)) {
                    mPB_keep_item(bg_item_fg_sub_dig2take_conv(*nameptr));
                    mFI_SetFG_common(RSV_NO, pos, 1);
                    mFI_Wpos2DepositOFF(pos);
                } else {
                    mFI_Wpos2DepositOFF(pos);
                    mPB_keep_item(*nameptr);
                    mFI_SetFG_common(RSV_NO, pos, 1);
                }
            } else {
                mFI_SetFG_common(RSV_NO, pos, 1);
            }
        }
        pos.x += 40.0f;
    }
}

static void aTOU_fgunit_off(ACTOR* actor) {
    TOUDAI_ACTOR* light = (TOUDAI_ACTOR*)actor;

    int i;
    xyz_t pos;

    xyz_t_move(&pos, &light->actor_class.home.position);

    pos.x -= 40.0f;
    pos.z -= 80.0f;
    for (i = 0; i < 2; i++) {
        mFI_SetFG_common(EMPTY_NO, pos, 1);
        pos.x += 40.0f;
    }
}

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_toudai;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_toudai;

static void aTOU_actor_ct(ACTOR* actor, GAME* game) {
    static cKF_Skeleton_R_c* skl[] = { &cKF_bs_r_obj_s_toudai, &cKF_bs_r_obj_w_toudai };
    TOUDAI_ACTOR* light = (TOUDAI_ACTOR*)actor;

    light->season = Common_Get(time.season);
    cKF_SkeletonInfo_R_ct(&light->keyframe, skl[light->season == mTM_SEASON_WINTER], NULL, light->work, light->target);
    aTOU_set_bgOffset(light, 1);
    aTOU_fgunit_on(actor);
    aTOU_setup_action(actor, 0);
    cKF_SkeletonInfo_R_play(&light->keyframe);
    actor->world.position.x -= 20.0f;
    actor->world.position.z -= 20.0f;
}

static void aTOU_actor_dt(ACTOR* actor, GAME* game) {
    TOUDAI_ACTOR* light = (TOUDAI_ACTOR*)actor;

    aTOU_fgunit_off(&light->actor_class);
    cKF_SkeletonInfo_R_dt(&light->keyframe);
    light->actor_class.world.position.x += 20.0f;
    light->actor_class.world.position.z += 20.0f;
}

#include "../src/ac_toudai_move.c_inc"

#include "../src/ac_toudai_draw.c_inc"
