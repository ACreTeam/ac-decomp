#ifndef BG_POST_ITEM_H
#define BG_POST_ITEM_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE BgPostItem_Profile;

typedef struct bg_post_item_s {
    ACTOR actor_class;
    u8 keep_mail_sum;
    u8 update_mail_flag;
} BG_POST_ITEM_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

