#ifndef AC_FURNITURE_H
#define AC_FURNITURE_H

#include "types.h"
#include "m_collision_bg.h"
#include "c_keyframe.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct furniture_actor_s FTR_ACTOR;

enum {
    aFTR_SHAPE_TYPEB_90,  /* 2x1 (facing up)*/
    aFTR_SHAPE_TYPEB_180, /* 2x1 [- *] */
    aFTR_SHAPE_TYPEB_270, /* 2x1 (facing down) */
    aFTR_SHAPE_TYPEB_0,   /* 2x1 [* -] */
    aFTR_SHAPE_TYPEA,     /* 1x1 */
    aFTR_SHAPE_TYPEC,     /* 2x2 */

    aFTR_SHAPE_TYPE_NUM
};

enum {
    aFTR_INTERACTION_STORAGE_DRAWERS,  // dressers
    aFTR_INTERACTION_STORAGE_WARDROBE, // double doors
    aFTR_INTERACTION_STORAGE_CLOSET,   // single door
    aFTR_INTERACTION_MUSIC_DISK,
    aFTR_INTERACTION_NO_COLLISION,
    aFTR_INTERACTION_HANIWA,
    aFTR_INTERACTION_FISH,
    aFTR_INTERACTION_INSECT,
    aFTR_INTERACTION_MANNEKIN,
    aFTR_INTERACTION_UMBRELLA,
    aFTR_INTERACTION_FOSSIL,
    aFTR_INTERACTION_FAMICOM,
    aFTR_INTERACTION_START_DISABLED, // mainly used for TVs to be off when placed
    // there may be more types, but I didn't see any

    aFTR_INTERACTION_NUM
};

enum {
    aFTR_CONTACT_ACTION_CHAIR_UNIDIRECTIONAL,   // only can sit from the front
    aFTR_CONTACT_ACTION_CHAIR_MULTIDIRECTIONAL, // can sit from any direction
    aFTR_CONTACT_ACTION_CHAIR_SOFA,             // cam sit anywhere from the front
    aFTR_CONTACT_ACTION_BED_SINGLE,             // single bed (can't roll)
    aFTR_CONTACT_ACTION_BED_DOUBLE,             // double bed (can roll)

    aFTR_CONTACT_ACTION_NUM
};

typedef void (*aFTR_FTR_CT_PROC)(FTR_ACTOR*, u8*);
typedef void (*aFTR_FTR_MOVE_PROC)(FTR_ACTOR*, ACTOR*, GAME*, u8*);
typedef void (*aFTR_FTR_DRAW_PROC)(FTR_ACTOR*, ACTOR*, GAME*, u8*);
typedef void (*aFTR_FTR_DT_PROC)(FTR_ACTOR*, u8*);
typedef void (*aFTR_FTR_DMA_PROC)(mActor_name_t, u8*);

typedef struct ftr_vtbl_s {
    aFTR_FTR_CT_PROC ct_proc;
    aFTR_FTR_MOVE_PROC move_proc;
    aFTR_FTR_DRAW_PROC draw_proc;
    aFTR_FTR_DT_PROC dt_proc;
    aFTR_FTR_DMA_PROC dma_proc;
} aFTR_vtable_c;

typedef struct ftr_rig_s {
    cKF_Skeleton_R_c* skeleton;
    cKF_Animation_R_c* animation;
    f32 speed;
} aFTR_rig_c;

typedef struct ftr_tex_animation_s {
    u8** animation;
    int animation_count;
} aFTR_tex_anim_c;

typedef struct ftr_profile_s {
    Gfx* opaque0;
    Gfx* opaque1;
    Gfx* translucent0;
    Gfx* translucent1;
    u8* texture;
    u16* palette;
    aFTR_rig_c* rig;
    aFTR_tex_anim_c* tex_anim;
    f32 height;
    f32 scale;
    u8 shape;              /* aFTR_SHAPE_TYPE* */
    u8 move_bg_type;       /* mCoBG_FTR_TYPE* */
    u8 check_rotation;     /* when non-zero extra checks are performed for items in the way during rotation? */
    u8 kankyo_map;         /* lighting map */
    u8 contact_action;     /* action on contact */
    u16 interaction_type;  /* action when interacting */
    aFTR_vtable_c* vtable; /* unique furniture functions */
} aFTR_PROFILE;

typedef struct furniture_collision_s {
    f32 start[2];           /* starting xz pos */
    f32 end[2];             /* ending xz pos */
    f32 normal[2];          /* xz normal */
    f32 height;             /* collision y */
    f32 edge_contact_ratio; /* percentage of the xz collision in contact with edge to count as collision */
} aFTR_collision_c;

struct furniture_actor_s {
    u16 name;
    s16 ctr_type; // 0 = GAME's frame counter, 1 = GAME_PLAY's frame counter
    int id;
    xyz_t position;
    xyz_t last_position;
    xyz_t target_position;
    int target_distance; /* distance to target position */
    f32 player_distance; /* distance to the player */
    f32 angle_y;         /* current Y angle */
    f32 angle_y_target;  /* goal Y angle */
    s16 state;
    u8 shape_type;          /* current size & shape (rotation) */
    u8 original_shape_type; /* original size & shape (rotation) */
    xyz_t base_position;
    aFTR_collision_c edge_collision[4]; /* collision for each edge */
    s16 collision_direction;
    int move_bg_idx;
    mCoBG_bg_regist_c bg_register;
    mCoBG_bg_contact_c bg_contact;
    s16 s_angle_y; /* current Y angle but 'binangle' format */
    f32 collision_scale;
    u8 switch_bit;          /* furniture on/off state */
    u8 switch_changed_flag; /* signal that the on/off state is toggled */
    s8 haniwa_step;
    s16 haniwa_state;
    cKF_SkeletonInfo_R_c keyframe; /* for actor animations */
    s_xyz joint[9];
    s_xyz morph[9];
    Mtx skeleton_mtx[2][12];
    cKF_TextureAnimation_c tex_animation; /* used for texture animations like TVs */
    xyz_t scale;
    f32 birth_scale_modifier; /* modifies scale for "birth" animation */
    s16 birth_anim_counter;
    s16 birth_anim_step;
    s16 rotation_delay_timer;
    s16 dynamic_work_s[5]; /* reserved for any use by each unique furniture actor */
    f32 dynamic_work_f[2]; /* reserved for any use by each unique furniture actor */
    s16 layer;             /* layer the furniture actor resides on */
    s16 _83E;
    s16 open_music_disk; /* set when a music player is interacted with */
    s16 dust_timer;
    mActor_name_t items[mCoBG_LAYER_NUM - 1]; /* used for holding items (music players & wardrobes)  */
    int _84C;
    u16* pal_p; /* used for furniture actors with dynamic palettes such as the structure model items */
    int _854;
};

#ifdef __cplusplus
}
#endif

#endif
