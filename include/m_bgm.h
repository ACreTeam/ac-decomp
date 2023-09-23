#ifndef M_BGM_H
#define M_BGM_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void mBGM_ct();
extern void mBGM_reset();
extern void mBGMPsComp_make_ps_lost_fanfare(u8 bgm_no, u16 unk);
extern void mBGMPsComp_scene_mode(int scene_mode);
extern void mBGMPsComp_make_ps_wipe(u16 ps_wipe);
extern void mBGMPsComp_delete_ps_demo(u8 bgm_num, u16 stop_type);
extern void mBGMPsComp_make_ps_demo(u8 bgm_no, u16 stop_type);
extern void mBGMPsComp_museum_status(int museum_status);

#ifdef __cplusplus
}
#endif

#endif
