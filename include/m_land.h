#ifndef M_LAND_H
#define M_LAND_H

#include "types.h"
#include "m_land_h.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mLd_BITMASK 0x3000
#define mLd_CHECK_ID(id) (((id) & mLd_BITMASK) == mLd_BITMASK)
#define mLd_CHECK_LAND_ID(id) (((id) & 0xFF00) == mLd_BITMASK)

#define NATIVE 0
#define FOREIGN 1

extern void mLd_StartFlagOn();
extern int mLd_CheckStartFlag();
extern int mLd_NullCheckLandName(u8* land_name);
extern int mLd_CheckId(u16 land_id);
extern int mLd_CheckCmpLandName(u8* name_a, u8* name_b);
extern int mLd_CheckCmpLand(u8* name_a, u16 id_a, u8* name_b, u16 id_b);
extern void mLd_ClearLandName(u8* name);
extern void mLd_CopyLandName(u8* dst, u8* src);
extern int mLd_AddMuraString(u8* name, int name_len);
extern int mLd_GetLandNameStringAddMura(u8* buf);
extern void mLd_SetFreeStrLandMuraName(u8* name, int free_str_no);
extern u8* mLd_GetLandName();
extern u16 mLd_MakeLandId();
extern int mLd_PlayerManKindCheckNo(u8 player_no);
extern int mLd_PlayerManKindCheck();
extern int mLd_CheckThisLand(u8* other_name, u16 other_id);
extern void mLd_LandInfoInit();
extern void mLd_LandDataInit();

#ifdef __cplusplus
}
#endif

#endif
