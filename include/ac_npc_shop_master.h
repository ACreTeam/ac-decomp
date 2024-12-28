#ifndef AC_NPC_SHOP_MASTER_H
#define AC_NPC_SHOP_MASTER_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"
#include "m_mail_password_check.h"
#include "m_private.h"
#include "ac_npc_shop_common.h"

enum aNSM_zone {
    aNSM_ZONE_0,
    aNSM_ZONE_1,
    aNSM_ZONE_2,
    aNSM_ZONE_3,

    aNSM_ZONE_NUM
};

typedef NPC_SHOP_COMMON_ACTOR NPC_SHOP_MASTER_ACTOR;

extern ACTOR_PROFILE Npc_Shop_Master_Profile;

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#endif
