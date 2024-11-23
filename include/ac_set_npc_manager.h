#ifndef AC_SET_NPC_MANAGER_H
#define AC_SET_NPC_MANAGER_H

#include "types.h"
#include "m_actor.h"
#include "m_field_info.h"
#include "m_npc.h"
#include "m_npc_schedule.h"
#include "m_npc_walk.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aSNMgr_EVENT_NORMAL_NPC_NUM mNpc_EVENT_NPC_NUM

enum {
    aSNMgr_SET_MODE_NONE,
    aSNMgr_SET_MODE_REGULAR,
    aSNMgr_SET_MODE_GUEST,

    aSNMgr_SET_MODE_NUM
};

typedef struct set_npc_manager_actor_s SET_NPC_MANAGER_ACTOR;

typedef struct set_npc_scope_s {
    f32 edge[2][2];
} aSNMgr_scope_c;

typedef struct set_npc_event_save_s {
    u8 animal_idx[aSNMgr_EVENT_NORMAL_NPC_NUM];
} aSNMgr_event_save_c;

typedef struct set_npc_event_info_s {
    aSNMgr_event_save_c* save_p;
    int type;
    int event_map_idx;
    int joint_npc_max;
    xyz_t pos[mNpc_EVENT_NPC_NUM];
} aSNMgr_event_info_c;

typedef struct set_npc_make_s {
    mActor_name_t name;
    mActor_name_t make_name;
    int bx;
    int bz;
    int ux;
    int uz;
    int idx;
} aSNMgr_make_c;

typedef struct set_npc_npc_info_s {
    Animal_c* animal_p;
    mNpc_NpcList_c* list_p;
    mNPS_schedule_c* schedule_p;
    mNpc_walk_c* walk_p;
    mNpcW_info_c* winfo_p[ANIMAL_NUM_MAX];
    u8 in_block_num[BLOCK_Z_NUM - 2][BLOCK_X_NUM];
    u8 to_block[ANIMAL_NUM_MAX][2];
    u32* count_p[ANIMAL_NUM_MAX];
    u16 exist;
    u16 appear;
    u16 joint_event;
    aSNMgr_make_c make[mNpc_EVENT_NPC_NUM];
    aSNMgr_event_info_c event_info;
    int timer[ANIMAL_NUM_MAX];
} aSNMgr_npc_info_c;

typedef struct set_npc_player_pos_s {
    xyz_t pos;
    int next_block[2];
    int now_block[2];
} aSNMgr_player_pos_c;

typedef void (*aSNMgr_SET_PROC)(SET_NPC_MANAGER_ACTOR*);

struct set_npc_manager_actor_s {
    ACTOR actor_class;
    int set_mode;
    aSNMgr_SET_PROC set_proc;
    aSNMgr_player_pos_c player_pos;
    aSNMgr_scope_c scope;
    aSNMgr_scope_c guest_scope;
    aSNMgr_npc_info_c npc_info;
};

extern ACTOR_PROFILE Set_Npc_Manager_Profile;

#ifdef __cplusplus
}
#endif

#endif
