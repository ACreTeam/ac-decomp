#ifndef M_ACTOR_SHADOW_H
#define M_ACTOR_SHADOW_H

#include "types.h"
#include "m_actor.h"

int mActorShadow_OperateScrollLimit(int, int, int);
Gfx* mActorShadow_TileScroll2(u32 *, u32 *, int, int, int, int, int, int, u32 *, u32 *, int, int, int, int, int, int, GAME *);
void mActorShadow_AdjustRate(f32 *);
void mActorShadow_GetTimeAngleY_TimeAlpha(Shadow_Info *, GAME_PLAY *);
void mActorShadow_GetGroundAverageAngle(Shadow_Info *);
void mActorShadow_GetDistanceRate(Shadow_Info *, f32);
f32 mActorShadow_GetAbsBigger(f32, f32);
void mActorShadow_RadiusScaleRate(ACTOR *, Shadow_Info *);
void mActorShadow_GetShadowTopPos_GetSlideS(Shadow_Info *);
Gfx* mActorShadow_SetTexScroll(ACTOR *, Shadow_Info *, GAME *);
void mActorShadow_GetLastAlphaScale(f32 *, u8 *, ACTOR *, Shadow_Info *);
void mActorShadow_DrawActorShadow(ACTOR *, Shadow_Info *, GAME_PLAY *, int, xyz_t, f32);
void mActorShadow_GetShadowPosition(ACTOR *, xyz_t *);
int mActorShadow_GetShadowKind(void);
f32 mAc_GetShadowGroundY_NoneForce(const Shadow_Info *);
f32 mAc_GetShadowGroundY_Force(const Shadow_Info *);
void mAc_DecideShadowRadius_IamNotFish(Shadow_Info *, ACTOR *, f32 *);
void mAc_DecideShadowRadius_IamFish(Shadow_Info *, ACTOR *, f32 *);
void mAc_ActorShadowDraw_ShadowDrawFlagOff(ACTOR *, GAME_PLAY *, int, xyz_t, f32);
void mAc_ActorShadowDraw_ShadowDrawFlagOn(ACTOR *, GAME_PLAY *, int, xyz_t, f32);
void mAc_ActorShadowDraw(ACTOR *, GAME_PLAY *, int, xyz_t, f32);
void mActorShadow_SetForceShadowPos(ACTOR *, xyz_t *);
void mActorShadow_UnSetForceShadowPos(ACTOR *);
void mAc_NormalActorShadow(ACTOR *, GAME_PLAY *, f32);
void mAc_UnagiActorShadow(ACTOR *, GAME *, xyz_t);
void mAc_ActorShadowCircle(ACTOR *, LightsN *, GAME_PLAY *);
void mAc_ActorShadowEllipse(ACTOR *, LightsN *, GAME_PLAY *);

#endif
