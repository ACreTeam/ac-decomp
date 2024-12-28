#ifndef AC_NPC_CONV_MASTER_H
#define AC_NPC_CONV_MASTER_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"
#include "m_mail_password_check.h"
#include "m_private.h"
#include "ac_npc_shop_common.h"

#ifdef __cplusplus
extern "C" {
#endif

enum aNCM_zone {
    aNCM_ZONE_0,
    aNCM_ZONE_1,
    aNCM_ZONE_2,
    aNCM_ZONE_3,

    aNCM_ZONE_NUM
};

typedef NPC_SHOP_COMMON_ACTOR NPC_CONV_MASTER_ACTOR;

extern ACTOR_PROFILE Npc_Conv_Master_Profile;

#ifdef __cplusplus
}
#endif

#endif
