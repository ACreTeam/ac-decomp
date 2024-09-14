#ifndef M_PRIVATE_H_H
#define M_PRIVATE_H_H

#include "types.h"
#include "m_actor_type.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct private_s Private_c;

typedef struct private_cloth_s {
    u16 idx;
    mActor_name_t item;
} mPr_cloth_c;

#ifdef __cplusplus
}
#endif

#endif
