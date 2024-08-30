#ifndef AC_SIGN_H
#define AC_SIGN_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int aSIGN_set_white_sign(GAME* game, const xyz_t* pos_p);
extern int aSIGN_erase_white_sign(GAME* game, const xyz_t* pos_p);

extern ACTOR_PROFILE Ac_Sign_Profile;

#ifdef __cplusplus
}
#endif

#endif
