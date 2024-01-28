#ifndef AC_T_UMBRELLA_H
#define AC_T_UMBRELLA_H

#include "types.h"
#include "ac_tools.h"
#include "c_keyframe.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE T_Umbrella_Profile;

typedef void (*UMBRELLA_PROC)(ACTOR*);

// Size == 0x1F4 (500)
typedef struct t_umbrella_s {
    TOOLS_ACTOR tools_class;
    UMBRELLA_PROC action_proc;
    int action;
    f32 frame;
    xyz_t scale_e;
    xyz_t scale_kasa;
    BOOL opened_fully;
} UMBRELLA_ACTOR;

typedef struct t_umbrella_data_table_s {
    int table_length;
    f32* sect_table;
    f32* scale_table;
} UMBRELLA_DATA_TABLE;

typedef struct t_umbrella_model_s {
    Gfx* model_e;
    Gfx* model_kasa;
} UMBRELLA_MODEL;

#ifdef __cplusplus
}
#endif

#endif

