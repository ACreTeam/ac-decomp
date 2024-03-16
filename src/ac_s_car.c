#include "ac_s_car.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_event.h"

static void aSCR_actor_ct(ACTOR* actor, GAME* game);
static void aSCR_actor_dt(ACTOR* actor, GAME* game);
static void aSCR_actor_init(ACTOR* actor, GAME* game);
static void aSCR_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE S_Car_Profile = {
    mAc_PROFILE_S_CAR,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    DESIGNER_CAR,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(STRUCTURE_ACTOR),
    &aSCR_actor_ct,
    &aSCR_actor_dt,
    &aSCR_actor_init,
    &aSCR_actor_draw,
    NULL,
};

u8 aSCR_shadow_vtx_fix_flg_table0[24] = {
    FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,
    TRUE,  TRUE,  TRUE,  TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
};

extern Vtx obj_car_shadow_v[];
extern Gfx obj_car_shadowT_model[];
bIT_ShadowData_c aSCR_shadow_data = {
    23, aSCR_shadow_vtx_fix_flg_table0, 60.0f, obj_car_shadow_v, obj_car_shadowT_model,
};

static void aSCR_set_bgOffset(STRUCTURE_ACTOR* car, int offs);

static void aSCR_actor_ct(ACTOR* actor, GAME* game) {
    aSCR_set_bgOffset((STRUCTURE_ACTOR*)actor, 0);
}

static void aSCR_actor_dt(ACTOR* actor, GAME* game) {
    mEv_dsg_common_c* designer_common;

    designer_common = (mEv_dsg_common_c*)mEv_get_common_area(mEv_EVENT_DESIGNER, FALSE);
    if (designer_common != NULL && designer_common->_04 == 2) {
        designer_common->button_presses = 0;
    }

    if (Save_Get(event_save_data).special.event.designer.used >= 3) {
        mEv_special_event_soldout(mEv_EVENT_DESIGNER);
    }
}

#include "../src/ac_s_car_move.c_inc"

#include "../src/ac_s_car_draw.c_inc"
