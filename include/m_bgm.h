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
extern void mBGMPsComp_make_ps_quietField(u16 stop_type);
extern void mBGMPsComp_delete_ps_quietField();
extern void mBGMPsComp_make_ps_co_quiet(u16 stop_type, s16 frames);
extern void mBGMPsComp_volume_talk_start();
extern void mBGMPsComp_volume_talk_end();
extern void mBGMForce_inform_end();

#ifdef __cplusplus
}
#endif

#endif
