#include "ac_police_box.h"

#include "m_name_table.h"
#include "bg_item_h.h"
#include "m_common_data.h"
#include "m_house.h"
#include "m_player_lib.h"
#include "m_demo.h"
#include "ac_intro_demo.h"
#include "m_bgm.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "libforest/gbi_extensions.h"

static void aPBOX_actor_ct(ACTOR* actor, GAME* game);
static void aPBOX_actor_init(ACTOR* actor, GAME* game);
static void aPBOX_actor_draw(ACTOR* actor, GAME* game);

// clang-format off
ACTOR_PROFILE Police_Box_Profile = {
    mAc_PROFILE_POLICE_BOX,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    POLICE_STATION,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(STRUCTURE_ACTOR),
    &aPBOX_actor_ct,
    mActor_NONE_PROC1,
    &aPBOX_actor_init,
    &aPBOX_actor_draw,
    NULL
};
// clang-format on

// clang-format off
static u8 aPBOX_shadow_vtx_fix_flg_table0[] = {
    TRUE, FALSE, TRUE, FALSE,
    TRUE, FALSE, TRUE, FALSE,
    TRUE, FALSE, FALSE, TRUE,
    TRUE, FALSE, FALSE, TRUE,
    TRUE, FALSE, FALSE, TRUE
};
// clang-format on

extern Vtx obj_s_kouban_shadow_v[];
extern Gfx obj_s_kouban_shadow_model[];

// clang-format off
static bIT_ShadowData_c aPBOX_shadow_data = {
    20,
    aPBOX_shadow_vtx_fix_flg_table0,
    60.0f,
    obj_s_kouban_shadow_v,
    obj_s_kouban_shadow_model
};
// clang-format on

// clang-format off
static Door_data_c aPBOX_police_box_enter_data = {
    SCENE_POLICE_BOX,
    mSc_DIRECT_NORTH,
    FALSE,
    0,
    { 200, 0, 380 },
    EMPTY_NO,
    1,
    { 0, 0, 0 },
};
// clang-format on

static void aPBOX_set_bgOffset(STRUCTURE_ACTOR* shop, int idx);
static int aPBOX_ctrl_light(STRUCTURE_ACTOR* shop);

static void aPBOX_actor_ct(ACTOR* actor, GAME* game) {
    STRUCTURE_ACTOR* box;

    box = (STRUCTURE_ACTOR*)actor;

    box->season = Common_Get(time.season);
    aPBOX_set_bgOffset(box, 0);

    if (aPBOX_ctrl_light(box) != FALSE) {
        box->action = DEG2SHORT_ANGLE(90.0f) - 1; // 0x3FFF
    } else {
        box->action = DEG2SHORT_ANGLE(0.0f);
    }
}

#include "../src/ac_police_box_move.c_inc"

#include "../src/ac_police_box_draw.c_inc"
