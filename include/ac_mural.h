#ifndef AC_MURAL_H
#define AC_MURAL_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aML_MURAL_X_NUM 4
#define aML_MURAL_Y_NUM 4
#define aML_MURAL_NUM (aML_MURAL_X_NUM * aML_MURAL_Y_NUM)

typedef struct mural_s {
    u8 type;
    u16* pal_p;
    u8* tex_p;
} aML_mural_c;

typedef struct mural_actor_s MURAL_ACTOR;

struct mural_actor_s {
    ACTOR actor_class;
    aML_mural_c mural[aML_MURAL_NUM];
};

extern ACTOR_PROFILE Mural_Profile;

#ifdef __cplusplus
}
#endif

#endif
