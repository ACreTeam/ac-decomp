#ifndef M_EVENT_MAP_NPC_H
#define M_EVENT_MAP_NPC_H

#include "types.h"
#include "m_actor.h"
#include "m_npc.h"
#include "ac_set_npc_manager.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    mEvMN_TYPE_FIREWORKS_SHOW,
    mEvMN_TYPE_CHERRY_BLOSSOM_FESTIVAL,
    mEvMN_TYPE_SPORTS_FAIR_FOOT_RACE,
    mEvMN_TYPE_SPORTS_FAIR_AEROBICS,
    mEvMN_TYPE_SPORTS_FAIR_BALL_TOSS,
    mEvMN_TYPE_SPORTS_FAIR_TUG_OF_WAR,
    mEvMN_TYPE_HALLOWEEN,
    mEvMN_TYPE_NEW_YEARS_DAY,
    mEvMN_TYPE_FISHING_TOURNEY_1,
    mEvMN_TYPE_FISHING_TOURNEY_2,
    mEvMN_TYPE_MORNING_AEROBICS,
    mEvMN_TYPE_HARVEST_MOON_FESTIVAL,
    mEvMN_TYPE_HARVEST_FESTIVAL,
    mEvMN_TYPE_NEW_YEARS_EVE_COUNTDOWN,
    mEvMN_TYPE_KAMAKURA,
    mEvMN_TYPE_GROUNDHOG_DAY,
    mEvMN_TYPE_METEOR_SHOWER,

    mEvMN_TYPE_NUM
};

extern int mEvMN_GetMapIdx(int event_type);
extern int mEvMN_GetEventTypeMap(void);
extern u32 mEvMN_GetEventBlockKind(int map_type);
extern int mEvMN_GetJointNpcMax(int map_type);
extern int mEvMN_GetEventSetUtInBlockMapIdx(int* block_ux, int* block_uz, int map_type, int idx);
extern int mEvMN_GetEventSetUtInBlock(mActor_name_t* actor_name, int* block_ux, int* block_uz, int event_type, int idx);
extern void mEvMN_GetNpcJointEv(aSNMgr_event_save_c* event_data, int event_type);
extern void mEvMN_SetNpcJointEv(aSNMgr_event_save_c* event_data, int event_type);
extern void mEvMN_GetEventNpcName(mActor_name_t* npc_name, int event_type, int animal_idx, int idx);
extern int mEvNM_CheckJointEvent(mActor_name_t npc_name);
extern int mEvMN_GetJointEventRandomNpc(mActor_name_t* npc_name_p);
extern int mEvMN_CheckLapPlayer(int block_ux, int block_uz);

#ifdef __cplusplus
}
#endif

#endif
