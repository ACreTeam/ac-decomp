#ifndef M_HOME_H
#define M_HOME_H

#include "types.h"
#include "m_home_h.h"
#include "m_field_make.h"
#include "m_actor_type.h"
#include "m_personal_id.h"
#include "audio.h"
#include "lb_rtc.h"
#include "m_mail.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void mHm_ClearHomeInfo(int home_no);
extern void mHm_ClearAllHomeInfo();
extern void mHm_SetNowHome();
extern void mHm_SetDefaultPlayerRoomData(int home_no);
extern void mHm_InitHomeInfo(mHm_hs_c* home, int player_no);
extern void mHm_CheckRehouseOrder();
extern int mHm_KeepHouseSize(u8 player_no);
extern int mHm_CheckKeepHouseSize(u8 player_no);
extern int mHm_SetBasement(u8 home_no);
extern void mHm_InitCottage(mHm_cottage_c* cottage);

#ifdef __cplusplus
}
#endif

#endif
