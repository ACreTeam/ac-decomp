#include "ac_my_indoor.h"

#include "m_field_info.h"
#include "m_malloc.h"
#include "m_room_type.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "m_mark_room.h"
#include "sys_matrix.h"

enum {
    aMI_ROOM_KIND_S,
    aMI_ROOM_KIND_M,
    aMI_ROOM_KIND_L,
    aMI_ROOM_KIND_LL1,
    aMI_ROOM_KIND_LL2,
    aMI_ROOM_KIND_BASEMENT,

    aMI_ROOM_KIND_NUM
};

enum {
    aMI_ROOM_SIZE_S,
    aMI_ROOM_SIZE_M,
    aMI_ROOM_SIZE_L,

    aMI_ROOM_SIZE_NUM
};

typedef struct {
    Gfx* floor_model;
    Gfx* wall_model;
} aMI_disp_wall_floor_c;

typedef struct {
    aMI_disp_wall_floor_c main;
    aMI_disp_wall_floor_c new1;
    aMI_disp_wall_floor_c new2;
    int size;
} aMI_size_disp_data_c;

typedef struct {
    Gfx* disp;
    int _04;
} aMI_room_step_data_c;

typedef struct {
    int scene;
    s16 room_kind;
} aMI_room_kind_data_c;

extern Gfx rom_myhome1_floor_model[];
extern Gfx rom_myhome1_wall_model[];
extern Gfx rom_myhome1_floor_new_model[];
extern Gfx rom_myhome1_wall_new_model[];
extern Gfx rom_myhome1_floor_new2_model[];
extern Gfx rom_myhome1_wall_new2_model[];

extern Gfx rom_myhome2B_floor_model[];
extern Gfx rom_myhome2B_wall_model[];
extern Gfx rom_myhome2B_floor_new_model[];
extern Gfx rom_myhome2B_wall_new_model[];
extern Gfx rom_myhome2B_floor_new2_model[];
extern Gfx rom_myhome2B_wall_new2_model[];

extern Gfx rom_myhome3_floor_model[];
extern Gfx rom_myhome3_wall_model[];
extern Gfx rom_myhome3_floor_new_model[];
extern Gfx rom_myhome3_wall_new_model[];
extern Gfx rom_myhome3_floor_new2_model[];
extern Gfx rom_myhome3_wall_new2_model[];

extern Gfx rom_myhome4_1_floor_model[];
extern Gfx rom_myhome4_1_wall_model[];
extern Gfx rom_myhome4_1_floor_new_model[];
extern Gfx rom_myhome4_1_wall_new_model[];
extern Gfx rom_myhome4_1_floor_new2_model[];
extern Gfx rom_myhome4_1_wall_new2_model[];

extern Gfx rom_myhome4_2_floor_model[];
extern Gfx rom_myhome4_2_wall_model[];
extern Gfx rom_myhome4_2_floor_new_model[];
extern Gfx rom_myhome4_2_wall_new_model[];
extern Gfx rom_myhome4_2_floor_new2_model[];
extern Gfx rom_myhome4_2_wall_new2_model[];

extern Gfx rom_myhome_ug_model[];

// clang-format off
static aMI_size_disp_data_c aMI_size_dsp_table[aMI_ROOM_KIND_NUM] = {
    {
        rom_myhome1_floor_model, rom_myhome1_wall_model,
        rom_myhome1_floor_new_model, rom_myhome1_wall_new_model,
        rom_myhome1_floor_new2_model, rom_myhome1_wall_new2_model,
        aMI_ROOM_SIZE_S
    },
    {
        rom_myhome2B_floor_model, rom_myhome2B_wall_model,
        rom_myhome2B_floor_new_model, rom_myhome2B_wall_new_model,
        rom_myhome2B_floor_new2_model, rom_myhome2B_wall_new2_model,
        aMI_ROOM_SIZE_M
    },
    {
        rom_myhome3_floor_model, rom_myhome3_wall_model,
        rom_myhome3_floor_new_model, rom_myhome3_wall_new_model,
        rom_myhome3_floor_new2_model, rom_myhome3_wall_new2_model,
        aMI_ROOM_SIZE_L
    },
    {
        rom_myhome4_1_floor_model, rom_myhome4_1_wall_model,
        rom_myhome4_1_floor_new_model, rom_myhome4_1_wall_new_model,
        rom_myhome4_1_floor_new2_model, rom_myhome4_1_wall_new2_model,
        aMI_ROOM_SIZE_L
    },
    {
        rom_myhome4_2_floor_model, rom_myhome4_2_wall_model,
        rom_myhome4_2_floor_new_model, rom_myhome4_2_wall_new_model,
        rom_myhome4_2_floor_new2_model, rom_myhome4_2_wall_new2_model,
        aMI_ROOM_SIZE_M
    },
    {
        rom_myhome_ug_model, NULL,
        rom_myhome_ug_model, NULL,
        rom_myhome_ug_model, NULL,
        aMI_ROOM_SIZE_L
    },
};
// clang-format on

extern Gfx obj_myhome_step_down_model[];
extern Gfx obj_myhome_step_up_model[];

static aMI_room_step_data_c aMI_step_data[aMI_STEP_TYPE_NUM] = {
    { obj_myhome_step_down_model, 0 },
    { obj_myhome_step_up_model, 0 },
    { obj_myhome_step_down_model, 0 },
    { obj_myhome_step_up_model, 0 },
};

static f32 aMI_scale_x_table[aMI_STEP_TYPE_NUM] = { 1.0f, 1.0f, -1.0f, -1.0f };

static void My_Indoor_Actor_ct(ACTOR*, GAME*);
static void My_Indoor_Actor_dt(ACTOR*, GAME*);
static void My_Indoor_Actor_move(ACTOR*, GAME*);
static void My_Indoor_Actor_draw(ACTOR*, GAME*);

ACTOR_PROFILE My_Indoor_Profile = {
    mAc_PROFILE_MY_INDOOR,
    ACTOR_PART_FG,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(MY_INDOOR_ACTOR),
    &My_Indoor_Actor_ct,
    &My_Indoor_Actor_dt,
    &My_Indoor_Actor_move,
    &My_Indoor_Actor_draw,
    NULL,
};

static void aMI_DrawMyFloor(ACTOR*, GAME*);
static void aMI_DrawMyOriginalFloor(ACTOR*, GAME*);

static void aMI_DrawMyWall(ACTOR*, GAME*);
static void aMI_DrawMyOriginalWall(ACTOR*, GAME*);

static int aMI_GetPlayerRoomIdx(void) {
    mActor_name_t field_id = mFI_GetFieldId();

    if (mFI_GET_TYPE(field_id) == mFI_FIELD_PLAYER0_ROOM) {
        return (field_id - mFI_FIELD_PLAYER0_ROOM) & 3;
    }

    return 0;
}

static void* aMI_SucureBank(u32 size, GAME_PLAY* play) {
    return zelda_malloc_align(size, 32);
}

static void aMI_GetMyIndoorBank(ACTOR* actorx, GAME* game) {
    MY_INDOOR_ACTOR* my_indoor = (MY_INDOOR_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    int i;

    for (i = 0; i < aMI_BANK_NUM; i++) {
        my_indoor->banks[i].wall_data_p = (u8*)aMI_SucureBank(aMI_WALL_BANK_SIZE, play);
    }

    for (i = 0; i < aMI_BANK_NUM; i++) {
        my_indoor->banks[i].floor_data_p = (u8*)aMI_SucureBank(aMI_FLOOR_BANK_SIZE, play);
    }
}

static void aMI_CopyFloorTexture(ACTOR* actorx, s16 floor_idx, s16 bank_no) {
    MY_INDOOR_ACTOR* my_indoor = (MY_INDOOR_ACTOR*)actorx;
    int bank;

    if (bank_no == aMI_BANK_NUM) {
        int i;

        for (i = 0; i < aMI_BANK_NUM; i++) {
            mRmTp_CopyFloorData(my_indoor->banks[i].floor_data_p, floor_idx);
            my_indoor->banks[i].floor_draw_proc =
                FLOOR_IS_MY_ORIG(floor_idx) ? &aMI_DrawMyOriginalFloor : &aMI_DrawMyFloor;
        }
    } else {
        bank = bank_no & 1;
        mRmTp_CopyFloorData(my_indoor->banks[bank_no & 1].floor_data_p, floor_idx);
        my_indoor->banks[bank].floor_draw_proc =
            FLOOR_IS_MY_ORIG(floor_idx) ? &aMI_DrawMyOriginalFloor : &aMI_DrawMyFloor;
    }
}

static void aMI_CopyWallTexture(ACTOR* actorx, s16 wall_idx, s16 bank_no) {
    MY_INDOOR_ACTOR* my_indoor = (MY_INDOOR_ACTOR*)actorx;
    int bank;

    if (bank_no == aMI_BANK_NUM) {
        int i;

        for (i = 0; i < aMI_BANK_NUM; i++) {
            mRmTp_CopyWallData(my_indoor->banks[i].wall_data_p, wall_idx);
            my_indoor->banks[i].wall_draw_proc = WALL_IS_MY_ORIG(wall_idx) ? &aMI_DrawMyOriginalWall : &aMI_DrawMyWall;
        }
    } else {
        mRmTp_CopyWallData(my_indoor->banks[bank_no & 1].wall_data_p, wall_idx);
        my_indoor->banks[bank_no & 1].wall_draw_proc =
            WALL_IS_MY_ORIG(wall_idx) ? &aMI_DrawMyOriginalWall : &aMI_DrawMyWall;
    }
}

static void aNI_SetFloorSE(s16 floor_idx) {
    if (!(floor_idx >= 0 && floor_idx < FLOOR_PLAYER_ROOM_END) == FALSE) {
        Common_Set(floor_idx, floor_idx);
    } else {
        Common_Set(floor_idx, FLOOR_ORIGINAL_SE);
    }
}

static void aMI_MyIndoorDma(ACTOR* actorx, GAME* game) {
    MY_INDOOR_ACTOR* my_indoor = (MY_INDOOR_ACTOR*)actorx;

    aMI_CopyWallTexture(actorx, my_indoor->wall_num, aMI_BANK_NUM);
    aMI_CopyFloorTexture(actorx, my_indoor->floor_num, aMI_BANK_NUM);

    if (mSc_IS_SCENE_BASEMENT(Save_Get(scene_no))) {
        Common_Set(floor_idx, FLOOR_BASEMENT);
    } else {
        aNI_SetFloorSE(my_indoor->floor_num);
    }
}

static mActor_name_t aMI_ChangeWall(mActor_name_t item);
static mActor_name_t aMI_ChangeCarpet(mActor_name_t item);
static void aMI_IndoorDmaAgain(void);
static void aMI_Change2Default(void);
static mActor_name_t aMI_WallIdx2ChangeWall(int idx, int is_original_flag);
static mActor_name_t aMI_FloorIdx2ChangeFloor(int idx, int is_original_flag);

static void aMI_SetClipProc(ACTOR* actorx, int set_flag) {
    MY_INDOOR_ACTOR* my_indoor = (MY_INDOOR_ACTOR*)actorx;

    if (set_flag == FALSE) {
        Common_Get(clip).my_indoor_clip = NULL;
    } else {
        aMI_Clip_c* clip = &my_indoor->clip;

        Common_Get(clip).my_indoor_clip = clip;

        clip->my_indoor_actor_p = my_indoor;
        clip->change_wall_proc = &aMI_ChangeWall;
        clip->change_carpet_proc = &aMI_ChangeCarpet;
        clip->indoor_dma_again_proc = &aMI_IndoorDmaAgain;
        clip->change_2_default_proc = &aMI_Change2Default;
        clip->wall_idx_2_change_wall_proc = &aMI_WallIdx2ChangeWall;
        clip->floor_idx_2_change_floor_proc = &aMI_FloorIdx2ChangeFloor;
    }
}

static s16 aMR_GetSceneRoomKind(void) {
    static aMI_room_kind_data_c room_kind_data[] = {
        { SCENE_MY_ROOM_S, aMI_ROOM_KIND_S },
        { SCENE_MY_ROOM_M, aMI_ROOM_KIND_M },
        { SCENE_MY_ROOM_L, aMI_ROOM_KIND_L },
        { SCENE_MY_ROOM_LL1, aMI_ROOM_KIND_LL1 },
        { SCENE_MY_ROOM_LL2, aMI_ROOM_KIND_LL2 },
        { SCENE_MY_ROOM_BASEMENT_S, aMI_ROOM_KIND_BASEMENT },
        { SCENE_MY_ROOM_BASEMENT_M, aMI_ROOM_KIND_BASEMENT },
        { SCENE_MY_ROOM_BASEMENT_L, aMI_ROOM_KIND_BASEMENT },
        { SCENE_COTTAGE_MY, aMI_ROOM_KIND_L },
        { SCENE_MY_ROOM_BASEMENT_LL1, aMI_ROOM_KIND_BASEMENT },
        { -1, 0 },
    };

    aMI_room_kind_data_c* room_kind_p = room_kind_data;
    int scene = Save_Get(scene_no);

    while (room_kind_p->scene != -1) {
        if (scene == room_kind_p->scene) {
            return room_kind_p->room_kind;
        }

        room_kind_p++;
    }

    return aMI_ROOM_KIND_S;
}

static void aMI_CheckFloorWallIndex(s16* wall_idx, s16* floor_idx) {
    if (!(*floor_idx >= 0 && *floor_idx < FLOOR_ETC_START) && !FLOOR_IS_MY_ORIG(*floor_idx)) {
        *floor_idx = 0;
    }

    if (!(*wall_idx >= 0 && *wall_idx < WALL_ETC_START) && !WALL_IS_MY_ORIG(*wall_idx)) {
        *wall_idx = 0;
    }
}

static void aMI_MakeStepData(MY_INDOOR_ACTOR* my_indoor, int house_idx) {
    if (Save_Get(scene_no) == SCENE_MY_ROOM_M || Save_Get(scene_no) == SCENE_MY_ROOM_L ||
        Save_Get(scene_no) == SCENE_MY_ROOM_LL1) {
        if (Save_Get(homes[house_idx]).flags.has_basement) {
            my_indoor->room_step[0] = TRUE;
        }
    }

    if (Save_Get(scene_no) == SCENE_MY_ROOM_LL1) {
        my_indoor->room_step[1] = TRUE;
    }

    if (Save_Get(scene_no) == SCENE_MY_ROOM_LL2) {
        my_indoor->room_step[2] = TRUE;
    }

    if (mFI_GetPlayerHouseFloorNo(Save_Get(scene_no)) == 2) {
        my_indoor->room_step[3] = TRUE;
    }
}

static void aMI_InitActorMember(ACTOR* actorx, GAME* game) {
    MY_INDOOR_ACTOR* my_indoor = (MY_INDOOR_ACTOR*)actorx;
    int floor_no = mFI_GetPlayerHouseFloorNo(Save_Get(scene_no));
    int player_room_idx = aMI_GetPlayerRoomIdx();
    int now_floor_no;

    my_indoor->room_kind = aMR_GetSceneRoomKind();
    now_floor_no = mFI_GetNowPlayerHouseFloorNo();
    my_indoor->house_floor_no = now_floor_no;

    if (now_floor_no == -1) {
        my_indoor->house_floor_no = 0;
    }

    if (Save_Get(scene_no) == SCENE_COTTAGE_MY) {
        my_indoor->floor_num = Save_Get(island).cottage.room.wall_floor.flooring_idx;
        my_indoor->wall_num = Save_Get(island).cottage.room.wall_floor.wallpaper_idx;
        my_indoor->wall_is_original_design = FALSE;
        my_indoor->floor_is_original_design = FALSE;
    } else {
        my_indoor->floor_num =
            Save_Get(homes[player_room_idx]).floors[my_indoor->house_floor_no].wall_floor.flooring_idx;
        my_indoor->wall_num =
            Save_Get(homes[player_room_idx]).floors[my_indoor->house_floor_no].wall_floor.wallpaper_idx;
        my_indoor->floor_is_original_design = mRmTp_GetNowSceneOriginalFloorStatus();
        my_indoor->wall_is_original_design = mRmTp_GetNowSceneOriginalWallStatus();
    }

    aMI_CheckFloorWallIndex(&my_indoor->wall_num, &my_indoor->floor_num);
    aMI_MakeStepData(my_indoor, player_room_idx);
}

static void My_Indoor_Actor_ct(ACTOR* actorx, GAME* game) {
    MY_INDOOR_ACTOR* my_indoor = (MY_INDOOR_ACTOR*)actorx;

    aMI_InitActorMember(actorx, game);
    aMI_GetMyIndoorBank(actorx, game);
    aMI_MyIndoorDma(actorx, game);
    aMI_SetClipProc(actorx, TRUE);
}

static void My_Indoor_Actor_dt(ACTOR* actorx, GAME* game) {
    MY_INDOOR_ACTOR* my_indoor = (MY_INDOOR_ACTOR*)actorx;
    int i;

    aMI_SetClipProc(actorx, FALSE);

    for (i = 0; i < aMI_BANK_NUM; i++) {
        if (my_indoor->banks[i].wall_data_p != NULL) {
            zelda_free(my_indoor->banks[i].wall_data_p);
        }

        if (my_indoor->banks[i].floor_data_p != NULL) {
            zelda_free(my_indoor->banks[i].floor_data_p);
        }
    }
}

static void aMI_DrawMyStep(ACTOR* actorx, GAME* game) {
    static xyz_t step_draw_pos[aMI_ROOM_SIZE_NUM] = {
        { 120.0f, 40.0f, 220.0f },
        { 160.0f, 40.0f, 300.0f },
        { 200.0f, 40.0f, 380.0f },
    };

    MY_INDOOR_ACTOR* my_indoor = (MY_INDOOR_ACTOR*)actorx;
    int i;

    Global_kankyo_set_room_prim(game);
    _texture_z_light_fog_prim(game->graph);

    for (i = 0; i < aMI_STEP_TYPE_NUM; i++) {
        if (my_indoor->room_step[i] != FALSE) {
            int size = aMI_size_dsp_table[my_indoor->room_kind].size;

            if (size >= 0 && size < aMI_ROOM_SIZE_NUM) {
                GRAPH* graph = game->graph;
                xyz_t* pos = &step_draw_pos[size];

                OPEN_DISP(graph);

                Matrix_translate(pos->x, pos->y, pos->z, MTX_LOAD);
                Matrix_scale(aMI_scale_x_table[i] * 0.01f, 0.01f, 0.01f, MTX_MULT);

                gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(NEXT_POLY_OPA_DISP, aMI_step_data[i].disp);

                CLOSE_DISP(graph);
            }
        }
    }
}

static void aMI_DrawMyFloor(ACTOR* actorx, GAME* game) {
    MY_INDOOR_ACTOR* my_indoor = (MY_INDOOR_ACTOR*)actorx;
    GRAPH* graph;
    aMI_bank_c* bank = &my_indoor->banks[my_indoor->floor_bank_idx];
    u8* data_p = bank->floor_data_p;
    u8* tex0 = data_p + aMI_PAL_SIZE + 0 * aMI_TEX_SIZE;
    u8* tex1 = data_p + aMI_PAL_SIZE + 1 * aMI_TEX_SIZE;
    u8* tex2 = data_p + aMI_PAL_SIZE + 2 * aMI_TEX_SIZE;
    u8* tex3 = data_p + aMI_PAL_SIZE + 3 * aMI_TEX_SIZE;
    aMI_disp_wall_floor_c* disp_info = &aMI_size_dsp_table[my_indoor->room_kind].main;

    Global_kankyo_set_room_prim(game);

    if (disp_info->floor_model != NULL) {
        graph = game->graph;

        _texture_z_light_fog_prim(graph);
        Matrix_translate(0.0f, 0.0f, 0.0f, MTX_LOAD);
        Matrix_scale(0.0625f, 0.0625f, 0.0625f, MTX_MULT);

        OPEN_DISP(graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        // Set segment 8-B to the four floor textures
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, tex0);
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_9, tex1);
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_A, tex2);
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_B, tex3);

        // Set segment C to the palette
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_C, data_p);

        // Draw model
        gSPDisplayList(NEXT_POLY_OPA_DISP, disp_info->floor_model);

        CLOSE_DISP(graph);
    }
}

typedef struct {
    int shift_s;
    int shift_t;
} aMI_wrapmirror_shift_c;

static aMI_wrapmirror_shift_c wrapmirror_floor_shift_s[4] = {
    { 0, 32 },
    { -32, 32 },
    { 0, 0 },
    { -32, 0 },
};

static aMI_wrapmirror_shift_c wrapmirror_floor_shift_m[4] = {
    { 0, 33 },
    { 16, 33 },
    { 0, 49 },
    { 16, 49 },
};

static aMI_wrapmirror_shift_c wrapmirror_floor_shift_l[4] = {
    { 0, 32 },
    { 0, 32 },
    { 0, 32 },
    { 0, 32 },
};

static aMI_wrapmirror_shift_c* wrapmirror_floor_shift_table[] = {
    wrapmirror_floor_shift_s, wrapmirror_floor_shift_m, wrapmirror_floor_shift_l,
    wrapmirror_floor_shift_l, wrapmirror_floor_shift_m, wrapmirror_floor_shift_s,
};

typedef struct {
    int scale_s;
    int scale_t;
} aMI_wrapmirror_scale_c;

static aMI_wrapmirror_scale_c scale_floor_shift_s[4] = {
    { 0, 32 },
    { -32, 32 },
    { 0, 0 },
    { -32, 0 },
};

static aMI_wrapmirror_scale_c scale_floor_shift_m[4] = {
    { 0, 33 },
    { 16, 33 },
    { 0, 17 },
    { 16, 17 },
};

static aMI_wrapmirror_scale_c scale_floor_shift_l[4] = {
    { 0, 32 },
    { 0, 32 },
    { 0, 32 },
    { 0, 32 },
};

static aMI_wrapmirror_scale_c* scale_floor_shift_table[] = {
    scale_floor_shift_s, scale_floor_shift_m, scale_floor_shift_l,
    scale_floor_shift_l, scale_floor_shift_m, scale_floor_shift_s,
};

static aMI_wrapmirror_shift_c wrapmirror_wall_shift_s[2] = {
    { 0, 32 },
    { 0, 32 },
};

static aMI_wrapmirror_shift_c wrapmirror_wall_shift_m[2] = {
    { 0, 32 },
    { 0, 32 },
};

static aMI_wrapmirror_shift_c wrapmirror_wall_shift_l[2] = {
    { 0, 32 },
    { 0, 32 },
};

static aMI_wrapmirror_shift_c* wrapmirror_wall_shift_table[] = {
    wrapmirror_wall_shift_s, wrapmirror_wall_shift_m, wrapmirror_wall_shift_l,
    wrapmirror_wall_shift_l, wrapmirror_wall_shift_m, wrapmirror_wall_shift_s,
};

static aMI_wrapmirror_scale_c scale_wall_shift_s[2] = {
    { 0, 32 },
    { 0, 32 },
};

static aMI_wrapmirror_scale_c scale_wall_shift_m[2] = {
    { 0, 32 },
    { 0, 32 },
};

static aMI_wrapmirror_scale_c scale_wall_shift_l[2] = {
    { 0, 32 },
    { 0, 32 },
};

static aMI_wrapmirror_scale_c* scale_wall_shift_table[] = {
    scale_wall_shift_s, scale_wall_shift_m, scale_wall_shift_l,
    scale_wall_shift_l, scale_wall_shift_m, scale_wall_shift_s,
};

/* @unused int aMI_GetTextureMode(...?) */

static void aMI_DrawMyOriginalFloor(ACTOR* actorx, GAME* game) {
    MY_INDOOR_ACTOR* my_indoor = (MY_INDOOR_ACTOR*)actorx;
    aMI_disp_wall_floor_c* disp;
    GRAPH* graph;
    aMI_bank_c* bank = &my_indoor->banks[my_indoor->floor_bank_idx];
    u8* data_p = bank->floor_data_p;
    u8* tex0 = data_p + aMI_PAL_SIZE + 0 * aMI_TEX_SIZE;
    u8* tex1 = data_p + aMI_PAL_SIZE + 1 * aMI_TEX_SIZE;
    u8* tex2 = data_p + aMI_PAL_SIZE + 2 * aMI_TEX_SIZE;
    u8* tex3 = data_p + aMI_PAL_SIZE + 3 * aMI_TEX_SIZE;

    if (my_indoor->floor_is_original_design == FALSE) {
        disp = &aMI_size_dsp_table[my_indoor->room_kind].new1;
    } else {
        disp = &aMI_size_dsp_table[my_indoor->room_kind].new2;
    }

    Global_kankyo_set_room_prim(game);

    if (disp->floor_model != NULL) {
        graph = game->graph;

        _texture_z_light_fog_prim(graph);
        Matrix_translate(0.0f, 0.0f, 0.0f, MTX_LOAD);
        Matrix_scale(0.0625f, 0.0625f, 0.0625f, MTX_MULT);

        OPEN_DISP(graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        // Set segment 8-B to the four floor textures
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, tex0);
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_9, tex1);
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_A, tex2);
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_B, tex3);

        // Set segment C to the palette
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_C, data_p);

        // Draw model
        gSPDisplayList(NEXT_POLY_OPA_DISP, disp->floor_model);

        CLOSE_DISP(graph);
    }
}

static void aMI_DrawMyWall(ACTOR* actorx, GAME* game) {
    MY_INDOOR_ACTOR* my_indoor = (MY_INDOOR_ACTOR*)actorx;
    GRAPH* graph;
    aMI_bank_c* bank = &my_indoor->banks[my_indoor->wall_bank_idx];
    u8* data_p = bank->wall_data_p;
    int room_kind = my_indoor->room_kind;
    u8* tex0 = data_p + aMI_PAL_SIZE + 0 * aMI_TEX_SIZE;
    u8* tex1 = data_p + aMI_PAL_SIZE + 1 * aMI_TEX_SIZE;
    aMI_disp_wall_floor_c* disp_info = &aMI_size_dsp_table[my_indoor->room_kind].main;

    Global_kankyo_set_room_prim(game);

    if (disp_info->wall_model != NULL) {
        graph = game->graph;

        _texture_z_light_fog_prim(graph);
        Matrix_translate(0.0f, 0.0f, 0.0f, MTX_LOAD);
        Matrix_scale(0.0625f, 0.0625f, 0.0625f, MTX_MULT);

        OPEN_DISP(graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        // Set segment 8-9 to the two wall textures
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, tex0);
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_9, tex1);

        // Set segment A to the palette
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_A, data_p);

        // Draw model
        gSPDisplayList(NEXT_POLY_OPA_DISP, disp_info->wall_model);

        CLOSE_DISP(graph);
    }
}

static void aMI_DrawMyOriginalWall(ACTOR* actorx, GAME* game) {
    MY_INDOOR_ACTOR* my_indoor = (MY_INDOOR_ACTOR*)actorx;
    aMI_disp_wall_floor_c* disp;
    GRAPH* graph;
    aMI_bank_c* bank = &my_indoor->banks[my_indoor->wall_bank_idx];
    u8* data_p = bank->wall_data_p;
    u8* tex0 = data_p + aMI_PAL_SIZE + 0 * aMI_TEX_SIZE;
    u8* tex1 = data_p + aMI_PAL_SIZE + 1 * aMI_TEX_SIZE;

    if (my_indoor->wall_is_original_design == FALSE) {
        disp = &aMI_size_dsp_table[my_indoor->room_kind].new1;
    } else {
        disp = &aMI_size_dsp_table[my_indoor->room_kind].new2;
    }

    Global_kankyo_set_room_prim(game);

    if (disp->wall_model != NULL) {
        graph = game->graph;

        _texture_z_light_fog_prim(graph);
        Matrix_translate(0.0f, 0.0f, 0.0f, MTX_LOAD);
        Matrix_scale(0.0625f, 0.0625f, 0.0625f, MTX_MULT);

        OPEN_DISP(graph);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        // Set segment 8-9 to the two wall textures
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_8, tex0);
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_9, tex1);

        // Set segment A to the palette
        gSPSegment(NEXT_POLY_OPA_DISP, G_MWO_SEGMENT_A, data_p);

        // Draw model
        gSPDisplayList(NEXT_POLY_OPA_DISP, disp->wall_model);

        CLOSE_DISP(graph);
    }
}

static void My_Indoor_Actor_draw(ACTOR* actorx, GAME* game) {
    MY_INDOOR_ACTOR* my_indoor = (MY_INDOOR_ACTOR*)actorx;

    // Draw the wall
    (*my_indoor->banks[my_indoor->wall_bank_idx & 1].wall_draw_proc)(actorx, game);

    // Draw the floor
    (*my_indoor->banks[my_indoor->floor_bank_idx & 1].floor_draw_proc)(actorx, game);

    // Draw stairs
    aMI_DrawMyStep(actorx, game);
}

static void aMI_Change2ReservedWall(ACTOR* actorx, GAME* game) {
    MY_INDOOR_ACTOR* my_indoor = (MY_INDOOR_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (my_indoor->wall_reserve.reserve_flag && play->submenu.process_status == mSM_PROCESS_WAIT) {
        my_indoor->wall_reserve.reserve_flag = FALSE;

        if (Common_Get(field_type) == mFI_FIELDTYPE2_PLAYER_ROOM) {
            int player_room_idx = aMI_GetPlayerRoomIdx();
            int bank_idx = my_indoor->wall_bank_idx;

            my_indoor->wall_num = my_indoor->wall_reserve.idx;
            my_indoor->wall_bank_idx = (bank_idx ^ 1) & 1;
            my_indoor->wall_is_original_design = my_indoor->wall_reserve.is_original_flag;

            aMI_CopyWallTexture(actorx, my_indoor->wall_num, my_indoor->wall_bank_idx);

            if (Save_Get(scene_no) == SCENE_COTTAGE_MY) {
                Save_Get(island).cottage.room.wall_floor.wallpaper_idx = my_indoor->wall_num;
            } else {
                Save_Get(homes[player_room_idx]).floors[my_indoor->house_floor_no].wall_floor.wallpaper_idx =
                    my_indoor->wall_num;
                mRmTp_SetNowSceneOriginalWallStatus((u8)my_indoor->wall_is_original_design);
            }

            mMkRm_ReportChangePlayerRoom();
            sAdo_SysTrgStart(0x11B);
        }
    }
}

static void aMI_Change2ReservedFloor(ACTOR* actorx, GAME* game) {
    MY_INDOOR_ACTOR* my_indoor = (MY_INDOOR_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (my_indoor->floor_reserve.reserve_flag && play->submenu.process_status == mSM_PROCESS_WAIT) {
        my_indoor->floor_reserve.reserve_flag = FALSE;

        if (Common_Get(field_type) == mFI_FIELDTYPE2_PLAYER_ROOM) {
            int player_room_idx = aMI_GetPlayerRoomIdx();
            int bank_idx = my_indoor->floor_bank_idx;

            my_indoor->floor_num = my_indoor->floor_reserve.idx;
            my_indoor->floor_bank_idx = (bank_idx ^ 1) & 1;
            my_indoor->floor_is_original_design = my_indoor->floor_reserve.is_original_flag;

            aMI_CopyFloorTexture(actorx, my_indoor->floor_num, my_indoor->floor_bank_idx);

            if (Save_Get(scene_no) == SCENE_COTTAGE_MY) {
                Save_Get(island).cottage.room.wall_floor.flooring_idx = my_indoor->floor_num;
            } else {
                Save_Get(homes[player_room_idx]).floors[my_indoor->house_floor_no].wall_floor.flooring_idx =
                    my_indoor->floor_num;
                mRmTp_SetNowSceneOriginalFloorStatus(my_indoor->floor_is_original_design);
            }

            aNI_SetFloorSE(my_indoor->floor_num);
            sAdo_SysTrgStart(0x11B);
            mMkRm_ReportChangePlayerRoom();
        }
    }
}

static void My_Indoor_Actor_move(ACTOR* actorx, GAME* game) {
    aMI_Change2ReservedWall(actorx, game);
    aMI_Change2ReservedFloor(actorx, game);
}

static mActor_name_t aMI_ChangeCarpet(mActor_name_t item) {
    mActor_name_t old_floor;

    // Do not allow changing the floor in the basement
    if (mFI_GetNowPlayerHouseFloorNo() == 2) {
        return EMPTY_NO;
    }

    if (Common_Get(clip).my_indoor_clip != NULL &&
        (item >= ITM_CARPET00 && item < (ITM_CARPET00 + FLOOR_PLAYER_ROOM_END))) {
        MY_INDOOR_ACTOR* my_indoor = Common_Get(clip).my_indoor_clip->my_indoor_actor_p;

        if (my_indoor != NULL && my_indoor->floor_reserve.reserve_flag == FALSE) {
            old_floor = ITM_CARPET00 + my_indoor->floor_num;
            my_indoor->floor_reserve.reserve_flag = TRUE;
            my_indoor->floor_reserve.idx = item - ITM_CARPET00;
            my_indoor->floor_reserve.is_original_flag = FALSE;

            return old_floor;
        }
    }

    return EMPTY_NO;
}

static mActor_name_t aMI_FloorIdx2ChangeFloor(int idx, int is_original_flag) {
    MY_INDOOR_ACTOR* my_indoor = Common_Get(clip).my_indoor_clip->my_indoor_actor_p;
    mActor_name_t old_floor;

    if (my_indoor != NULL) {
        old_floor = ITM_CARPET00 + my_indoor->floor_num;

        if (mFI_GetNowPlayerHouseFloorNo() != 2 && my_indoor->floor_reserve.reserve_flag == FALSE) {
            my_indoor->floor_reserve.reserve_flag = TRUE;
            my_indoor->floor_reserve.idx = idx;
            my_indoor->floor_reserve.is_original_flag = is_original_flag;

            // Don't give 'original design' items back
            if (FLOOR_IS_MY_ORIG(my_indoor->floor_num)) {
                return EMPTY_NO;
            }

            return old_floor;
        }
    }

    return EMPTY_NO;
}

static mActor_name_t aMI_ChangeWall(mActor_name_t item) {
    mActor_name_t old_wall;

    // Do not allow changing the wall in the basement
    if (mFI_GetNowPlayerHouseFloorNo() == 2) {
        return EMPTY_NO;
    }

    if (Common_Get(clip).my_indoor_clip != NULL) {
        MY_INDOOR_ACTOR* my_indoor = Common_Get(clip).my_indoor_clip->my_indoor_actor_p;

        if (my_indoor != NULL && (item >= ITM_WALL00 && item < (ITM_WALL00 + WALL_ETC_END)) &&
            my_indoor->wall_reserve.reserve_flag == FALSE) {
            old_wall = ITM_WALL00 + my_indoor->wall_num;
            my_indoor->wall_reserve.reserve_flag = TRUE;
            my_indoor->wall_reserve.idx = item - ITM_WALL00;
            my_indoor->wall_reserve.is_original_flag = FALSE;

            return old_wall;
        }
    }

    return EMPTY_NO;
}

static mActor_name_t aMI_WallIdx2ChangeWall(int idx, int is_original_flag) {
    MY_INDOOR_ACTOR* my_indoor = Common_Get(clip).my_indoor_clip->my_indoor_actor_p;
    mActor_name_t wall_floor;

    if (my_indoor != NULL) {
        wall_floor = ITM_WALL00 + my_indoor->wall_num;

        if (mFI_GetNowPlayerHouseFloorNo() != 2 && my_indoor->wall_reserve.reserve_flag == FALSE) {
            my_indoor->wall_reserve.reserve_flag = TRUE;
            my_indoor->wall_reserve.idx = idx;
            my_indoor->wall_reserve.is_original_flag = is_original_flag;

            // Don't give 'original design' items back
            if (WALL_IS_MY_ORIG(my_indoor->wall_num)) {
                return EMPTY_NO;
            }

            return wall_floor;
        }
    }

    return EMPTY_NO;
}

static void aMI_Change2Default(void) {
    aMI_ChangeWall(ITM_WALL00);
    aMI_ChangeCarpet(ITM_CARPET00);
}

static void aMI_IndoorDmaAgain(void) {
    if (Common_Get(clip).my_indoor_clip != NULL) {
        ACTOR* actorx = (ACTOR*)Common_Get(clip).my_indoor_clip->my_indoor_actor_p;
        MY_INDOOR_ACTOR* my_indoor = (MY_INDOOR_ACTOR*)actorx;

        if (my_indoor != NULL) {
            aMI_CopyWallTexture(actorx, my_indoor->wall_num, aMI_BANK_NUM);
            aMI_CopyFloorTexture(actorx, my_indoor->floor_num, aMI_BANK_NUM);
        }
    }
}
