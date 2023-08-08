#ifndef AC_T_PISTOL_H
#define AC_T_PISTOL_H

#include "types.h"
#include "m_actor.h"
#include "libultra/ultratypes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*PISTOL_PROC)(ACTOR*);

typedef struct t_pistol_s{
    ACTOR actor_class;
    int unk174;
    MtxF matrix_work;
    int enable;
    int unk1BC;
    int process_id;
    u8 pad2[0x8];
    PISTOL_PROC proc; 
    int current_id;
}PISTOL_ACTOR;


extern ACTOR_PROFILE T_Pistol_Profile;

#ifdef __cplusplus
}
#endif

#endif

