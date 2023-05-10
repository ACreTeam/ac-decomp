#ifndef M_ITEM_NAME_H
#define M_ITEM_NAME_H

#include "types.h"
#include "m_actor_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mIN_ITEM_NAME_LEN 16

extern void mIN_copy_name_str(u8* str, mActor_name_t item_no);
extern int mIN_get_item_article(mActor_name_t item_no);

#ifdef __cplusplus
}
#endif

#endif
