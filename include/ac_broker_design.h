#ifndef AC_BROKER_DESIGN_H
#define AC_BROKER_DESIGN_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef mActor_name_t (*aBD_GET_NO_PROC)(int ux, int uz);
typedef int (*aBD_REPORT_SALES_PROC)(int ux, int uz);

typedef struct broker_design_clip_s {
    aBD_GET_NO_PROC get_no_proc;
    aBD_REPORT_SALES_PROC report_sales_proc;
} aBD_clip_c;

typedef struct broker_design_actor_s BROKER_DESIGN_ACTOR;

struct broker_design_actor_s {
    ACTOR actor_class;
    aBD_clip_c clip;
};

extern ACTOR_PROFILE Broker_Design_Profile;

#ifdef __cplusplus
}
#endif

#endif
