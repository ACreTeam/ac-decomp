#ifndef AC_TOOLS_H
#define AC_TOOLS_H

#include "types.h"
#include "m_actor.h"
#include "libultra/ultratypes.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Tools_Profile;

typedef enum {
    TOOL_UMBRELLA0,
    TOOL_UMBRELLA1,
    TOOL_UMBRELLA2,
    TOOL_UMBRELLA3,
    TOOL_UMBRELLA4,
    TOOL_UMBRELLA5,
    TOOL_UMBRELLA6,
    TOOL_UMBRELLA7,
    TOOL_UMBRELLA8,
    TOOL_UMBRELLA9,
    TOOL_UMBRELLA10,
    TOOL_UMBRELLA11,
    TOOL_UMBRELLA12,
    TOOL_UMBRELLA13,
    TOOL_UMBRELLA14,
    TOOL_UMBRELLA15,
    TOOL_UMBRELLA16,
    TOOL_UMBRELLA17,
    TOOL_UMBRELLA18,
    TOOL_UMBRELLA19,
    TOOL_UMBRELLA20,
    TOOL_UMBRELLA21,
    TOOL_UMBRELLA22,
    TOOL_UMBRELLA23,
    TOOL_UMBRELLA24,
    TOOL_UMBRELLA25,
    TOOL_UMBRELLA26,
    TOOL_UMBRELLA27,
    TOOL_UMBRELLA28,
    TOOL_UMBRELLA29,
    TOOL_UMBRELLA30,
    TOOL_UMBRELLA31,
    TOOL_ORG_UMBRELLA0,
    TOOL_ORG_UMBRELLA1,
    TOOL_ORG_UMBRELLA2,
    TOOL_ORG_UMBRELLA3,
    TOOL_ORG_UMBRELLA4,
    TOOL_ORG_UMBRELLA5,
    TOOL_ORG_UMBRELLA6,
    TOOL_ORG_UMBRELLA7,
    TOOL_KEITAI,
    TOOL_UTIWA,
    TOOL_HANABI,
    TOOL_CRACKER,
    TOOL_PISTOL,
    TOOL_FLAG,
    TOOL_TUMBLER,
    TOOL_NPC_SAO,
    TOOL_TAMA1,
    TOOL_TAMA2,
    TOOL_TAMA3,
    TOOL_TAMA4,

    aTOL_NUM
} ToolName;

enum {
    aTOL_ACTION_WAIT,
    aTOL_ACTION_TAKEOUT,
    aTOL_ACTION_PUTAWAY,
    aTOL_ACTION_DESTRUCT,
    aTOL_ACTION_S_TAKEOUT,
    aTOL_ACTION_SPECIAL,

    aTOL_ACTION_NUM
};

typedef struct tools_s {
    /* 0x000 */ ACTOR actor_class;
    /* 0x174 */ int tool_name;
    /* 0x178 */ MtxF matrix_work;
    /* 0x1B8 */ int init_matrix;
    /* 0x1BC */ int unk1BC;
    /* 0x1C0 */ int work0;
    /* 0x1C4 */ int work1;
    /* 0x1C8 */ int work2;
} TOOLS_ACTOR;

typedef ACTOR* (*ToolBirthProc)(int kind, int mode, ACTOR* parent_actor, GAME* game, s16 arg, int* bank_id);
typedef int (*ToolChgRequestModeProc)(ACTOR* parent_actor, ACTOR* tool, int mode);

typedef struct ToolClip {
    ToolBirthProc aTOL_birth_proc;
    ToolChgRequestModeProc aTOL_chg_request_mode_proc;
    int bank_id;
} aTOL_Clip_c;

extern aTOL_Clip_c aTOL_clip;

#ifdef __cplusplus
}
#endif

#endif
