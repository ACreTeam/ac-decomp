#ifndef M_CLIP_H
#define M_CLIP_H

#include "types.h"
#include "ac_gyoei_h.h"
#include "ac_insect_h.h"
#include "ac_structure.h"
#include "ac_animal_logo.h"
#include "ef_effect_control.h"
#include "m_demo.h"
#include "bg_item_h.h"
#include "ac_weather.h"
#include "ac_npc.h"
#include "ac_tools.h"
#include "ac_aprilfool_control.h"
#include "ac_groundhog_control.h"
#include "ac_event_manager.h"
#include "ac_shop_manekin.h"
#include "ac_shop_indoor.h"
#include "ac_my_room.h"
#include "ac_my_indoor.h"
#include "ac_arrange_room.h"
#include "ac_shop_umbrella.h"
#include "ac_handOverItem.h"
#include "ac_quest_manager_clip.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*CLIP_NONE_PROC)();

/* sizeof(Clip_c) == 0x104 */
typedef struct clip_s {
  /* 0x000 */ void* _000[(0x020 - 0x000) / sizeof(void*)];
  /* 0x020 */ int arrange_ftr_num;
  /* 0x024 */ void* _024[(0x040 - 0x024) / sizeof(void*)];
  /* 0x040 */ aNPC_Clip_c* npc_clip;
  /* 0x044 */ void* _044[(0x060 - 0x044) / sizeof(void*)];
  /* 0x060 */ aSM_Clip_c* shop_manekin_clip;
  /* 0x064 */ void* _064;
  /* 0x068 */ CLIP_NONE_PROC _068;
  /* 0x06C */ aQMgr_Clip_c* quest_manager_clip;
  /* 0x070 */ aSI_Clip_c* shop_indoor_clip;
  /* 0x074 */ bIT_Clip_c* bg_item_clip;
  /* 0x078 */ aWeather_Clip_c* weather_clip;
  /* 0x07C */ aINS_Clip_c* insect_clip;
  /* 0x080 */ aMR_Clip_c* my_room_clip;
  /* 0x084 */ void* _084;
  /* 0x088 */ aHOI_Clip_c* handOverItem_clip;
  /* 0x08C */ aSTR_Clip_c* structure_clip;
  /* 0x090 */ eEC_EffectControl_Clip_c* effect_clip;
  /* 0x094 */ aTOL_Clip_c* tools_clip;
  /* 0x098 */ void* _098;
  /* 0x09C */ aMI_Clip_c* my_indoor_clip;
  /* 0x0A0 */ mDemo_Clip_c* demo_clip; /* can be multiple clip classes */
  /* 0x0A4 */ mDemo_Clip_c* demo_clip2; /* can be multiple clip classes */
  /* 0x0A8 */ void* _0A8;
  /* 0x0AC */ aGYO_Clip_c* gyo_clip;
  /* 0x0B0 */ void* _0B0;
  /* 0x0B4 */ void* _0B4;
  /* 0x0B8 */ aShopUmbrella_Clip_c* shop_umbrella_clip;
  /* 0x0BC */ aAR_Clip_c* arrange_room_clip;
  /* 0x0C0 */ void* _0C0;
  /* 0x0C4 */ void* _0C4;
  /* 0x0C8 */ void* shrine_clip;
  /* 0x0CC */ void* _0CC;
  /* 0x0D0 */ void* _0D0;
  /* 0x0D4 */ CLIP_NONE_PROC ball_redma_proc; /* removed in DnM+ */
  /* 0x0D8 */ void* _0D8;
  /* 0x0DC */ aAL_Clip_c* animal_logo_clip;
  /* 0x0E0 */ void* _0E0;
  /* 0x0E4 */ void* _0E4;
  /* 0x0E8 */ void* _0E8;
  /* 0x0EC */ aAPC_Clip_c* aprilfool_control_clip;
  /* 0x0F0 */ aEvMgr_Clip_c* event_manager_clip;
  /* 0x0F4 */ aGHC_Clip_c* groundhog_control_clip;
  /* 0x0F8 */ void* _0F8;
  /* 0x0FC */ void* _0FC;
  /* 0x100 */ void* _100;
} Clip_c;

extern void clip_clear();

#ifdef __cplusplus
}
#endif

#endif
