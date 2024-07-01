#ifndef AC_SHOP_DESIGN_H
#define AC_SHOP_DESIGN_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct shop_design_actor_s SHOP_DESIGN_ACTOR;

typedef mActor_name_t (*aSD_UNITNUM2ITEMNO_PROC)(int ut_x, int ut_z);
typedef int (*aSD_REPORTGOODSSALE_PROC)(int ut_x, int ut_z);

typedef struct shop_design_clip_s {
    SHOP_DESIGN_ACTOR* design_actor;
    aSD_UNITNUM2ITEMNO_PROC unitNum2ItemNo_proc;
    aSD_REPORTGOODSSALE_PROC reportGoodsSale_proc;
} aSD_Clip_c;

struct shop_design_actor_s {
    ACTOR actor_class;
    mActor_name_t* goods_list;
    int goods_list_count;
    int goods_list_max;
    aSD_Clip_c clip;
};

extern ACTOR_PROFILE Shop_Design_Profile;

#ifdef __cplusplus
}
#endif

#endif
