#ifndef EF_EFFECT_CONTROL_H
#define EF_EFFECT_CONTROL_H

#include "types.h"
#include "m_lib.h"
#include "m_actor.h"
#include "m_lights.h"

#ifdef __cplusplus
extern "C" {
#endif

#define eEC_EFFECT_ACTIVE_MAX 100

#define eEC_IMMEDIATE_DEATH -1
#define eEC_IGNORE_DEATH -2

#define eEC_NO_CHILD_ID 0xFF

#define eEC_DEFAULT_DEATH_DIST (800.0f)
#define eEC_IGNORE_DEATH_DIST (-1000.203064f) // ignore death range check when set to this

#define eEC_BUSH_HAPPA_TREE (0 << 13)
#define eEC_BUSH_HAPPA_PALM (1 << 13)
#define eEC_BUSH_HAPPA_CEDAR (2 << 13)
#define eEC_BUSH_HAPPA_GOLD (3 << 13)

enum effect_type {
    eEC_EFFECT_SHOCK,
    eEC_EFFECT_DUST,
    eEC_EFFECT_MUKA,
    eEC_EFFECT_WARAU,
    eEC_EFFECT_HA,
    eEC_EFFECT_SIBUKI,
    eEC_EFFECT_GIMONHU,
    eEC_EFFECT_KANTANHU,
    eEC_EFFECT_ASE,
    eEC_EFFECT_ASE_CH,
    eEC_EFFECT_KANGAERU,
    eEC_EFFECT_OTIKOMI,
    eEC_EFFECT_BURUBURU,
    eEC_EFFECT_SIAWASE_HIKARI,
    eEC_EFFECT_SIAWASE_HANA,
    eEC_EFFECT_SIAWASE_HANA_CH,
    eEC_EFFECT_TAKURAMI,
    eEC_EFFECT_TAKURAMI_KIRA,
    eEC_EFFECT_KAZE,
    eEC_EFFECT_KAZE_HAPPA,
    eEC_EFFECT_LOVELOVE,
    eEC_EFFECT_LOVELOVE_HEART,
    eEC_EFFECT_PUN,
    eEC_EFFECT_PUN_YUGE,
    eEC_EFFECT_PUN_SEKIMEN,
    eEC_EFFECT_NAKU,
    eEC_EFFECT_NAMIDA,
    eEC_EFFECT_HIRAMEKI_DEN,
    eEC_EFFECT_HIRAMEKI_HIKARI,
    eEC_EFFECT_SITUREN,
    eEC_EFFECT_ASE2,
    eEC_EFFECT_DASH_ASIMOTO,
    eEC_EFFECT_KONPU,
    eEC_EFFECT_LOVELOVE2,
    eEC_EFFECT_KPUN,
    eEC_EFFECT_KISHA_KEMURI,
    eEC_EFFECT_NEBOKE,
    eEC_EFFECT_NEBOKE_AWA,
    eEC_EFFECT_HANABI_YANAGI,
    eEC_EFFECT_HANABI_BOTAN1,
    eEC_EFFECT_HANABI_BOTAN2,
    eEC_EFFECT_HANABI_HOSHI,
    eEC_EFFECT_HANABI_SET,
    eEC_EFFECT_HANABI_SWITCH,
    eEC_EFFECT_FOOTPRINT,
    eEC_EFFECT_TURN_FOOTPRINT,
    eEC_EFFECT_BUBU,
    eEC_EFFECT_TURN_ASIMOTO,
    eEC_EFFECT_STRING,
    eEC_EFFECT_YUKIHANE,
    eEC_EFFECT_ANAHIKARI,
    eEC_EFFECT_BUSH_HAPPA,
    eEC_EFFECT_BUSH_YUKI,
    eEC_EFFECT_TUMBLE,
    eEC_EFFECT_TUMBLE_BODYPRINT,
    eEC_EFFECT_SLIP,
    eEC_EFFECT_TUMBLE_DUST,
    eEC_EFFECT_SWING_NET,
    eEC_EFFECT_AMI_MIZU,
    eEC_EFFECT_MIZUTAMA,
    eEC_EFFECT_YUKIDAMA,
    eEC_EFFECT_KIKUZU,
    eEC_EFFECT_SWING_AXE,
    eEC_EFFECT_STEAM,
    eEC_EFFECT_NIGHT15_MOON,
    eEC_EFFECT_NIGHT13_MOON,
    eEC_EFFECT_NEBOKE_AKUBI,
    eEC_EFFECT_SLIP_FOOTPRINT,
    eEC_EFFECT_WALK_ASIMOTO,
    eEC_EFFECT_TURI_HAMON,
    eEC_EFFECT_TURI_MIZU,
    eEC_EFFECT_TURI_HANE0,
    eEC_EFFECT_TURI_HANE1,
    eEC_EFFECT_TURI_SUITEKI,
    eEC_EFFECT_ONGEN,
    eEC_EFFECT_IMPACT_STAR,
    eEC_EFFECT_SANDSPLASH,
    eEC_EFFECT_YOUNG_TREE,
    eEC_EFFECT_SWING_ROD,
    eEC_EFFECT_DOYON,
    eEC_EFFECT_KAGU_HAPPA,
    eEC_EFFECT_HANABI_DUMMY,
    eEC_EFFECT_DIG_HOLE,
    eEC_EFFECT_DIG_SCOOP,
    eEC_EFFECT_DIG_MUD,
    eEC_EFFECT_KIGAE,
    eEC_EFFECT_KIGAE_LIGHT,
    eEC_EFFECT_TAPE,
    eEC_EFFECT_CLACKER,
    eEC_EFFECT_KAMIFUBUKI,
    eEC_EFFECT_CAR_BLIGHT,
    eEC_EFFECT_TAMAIRE,
    eEC_EFFECT_CAR_LIGHT,
    eEC_EFFECT_RESET_HOLE,
    eEC_EFFECT_GOKI,
    eEC_EFFECT_HANABIRA,
    eEC_EFFECT_WAIT_ASIMOTO,
    eEC_EFFECT_OTOSIANA,
    eEC_EFFECT_IKIGIRE,
    eEC_EFFECT_YUKIDARUMA,
    eEC_EFFECT_KYOUSOU_ONPU,
    eEC_EFFECT_DOUZOU_LIGHT,
    eEC_EFFECT_HALLOWEEN_SMOKE,
    eEC_EFFECT_HALLOWEEN,
    eEC_EFFECT_MOTIYUGE,
    eEC_EFFECT_TABERU,
    eEC_EFFECT_KASAMIZU,
    eEC_EFFECT_KASAMIZUTAMA,
    eEC_EFFECT_HANATIRI,
    eEC_EFFECT_URANAI,
    eEC_EFFECT_SUISOU_AWA,
    eEC_EFFECT_BREAK_AXE,
    eEC_EFFECT_YAJIRUSHI,
    eEC_EFFECT_SOBA_YUGE,
    eEC_EFFECT_FURO_YUGE,
    eEC_EFFECT_SHOOTING,
    eEC_EFFECT_SHOOTING_SET,
    eEC_EFFECT_SHOOTING_KIRA,
    eEC_EFFECT_COIN,
    eEC_EFFECT_TENT_LAMP,
    eEC_EFFECT_FLASH,
    eEC_EFFECT_FLASHC,
    eEC_EFFECT_KILLER,
    eEC_EFFECT_MAKE_HEM,
    eEC_EFFECT_MAKE_HEM_KIRA,
    eEC_EFFECT_MAKE_HEM_LIGHT,

    eEC_EFFECT_NUM
};

typedef struct effect_profile_s eEC_PROFILE_c;

extern eEC_PROFILE_c iam_ef_ami_mizu;
extern eEC_PROFILE_c iam_ef_anahikari;
extern eEC_PROFILE_c iam_ef_ase;
extern eEC_PROFILE_c iam_ef_ase2;
extern eEC_PROFILE_c iam_ef_ase_ch;
extern eEC_PROFILE_c iam_ef_break_axe;
extern eEC_PROFILE_c iam_ef_bubu;
extern eEC_PROFILE_c iam_ef_buruburu;
extern eEC_PROFILE_c iam_ef_bush_happa;
extern eEC_PROFILE_c iam_ef_bush_yuki;
extern eEC_PROFILE_c iam_ef_car_blight;
extern eEC_PROFILE_c iam_ef_car_light;
extern eEC_PROFILE_c iam_ef_clacker;
extern eEC_PROFILE_c iam_ef_coin;
extern eEC_PROFILE_c iam_ef_dash_asimoto;
extern eEC_PROFILE_c iam_ef_dig_hole;
extern eEC_PROFILE_c iam_ef_dig_mud;
extern eEC_PROFILE_c iam_ef_dig_scoop;
extern eEC_PROFILE_c iam_ef_douzou_light;
extern eEC_PROFILE_c iam_ef_doyon;
extern eEC_PROFILE_c iam_ef_dust;
extern eEC_PROFILE_c iam_ef_flash;
extern eEC_PROFILE_c iam_ef_flashC;
extern eEC_PROFILE_c iam_ef_footprint;
extern eEC_PROFILE_c iam_ef_furo_yuge;
extern eEC_PROFILE_c iam_ef_gimonhu;
extern eEC_PROFILE_c iam_ef_goki;
extern eEC_PROFILE_c iam_ef_ha;
extern eEC_PROFILE_c iam_ef_halloween;
extern eEC_PROFILE_c iam_ef_halloween_smoke;
extern eEC_PROFILE_c iam_ef_hanabi_botan1;
extern eEC_PROFILE_c iam_ef_hanabi_botan2;
extern eEC_PROFILE_c iam_ef_hanabi_dummy;
extern eEC_PROFILE_c iam_ef_hanabi_hoshi;
extern eEC_PROFILE_c iam_ef_hanabi_set;
extern eEC_PROFILE_c iam_ef_hanabi_switch;
extern eEC_PROFILE_c iam_ef_hanabi_yanagi;
extern eEC_PROFILE_c iam_ef_hanabira;
extern eEC_PROFILE_c iam_ef_hanatiri;
extern eEC_PROFILE_c iam_ef_hirameki_den;
extern eEC_PROFILE_c iam_ef_hirameki_hikari;
extern eEC_PROFILE_c iam_ef_ikigire;
extern eEC_PROFILE_c iam_ef_impact_star;
extern eEC_PROFILE_c iam_ef_kagu_happa;
extern eEC_PROFILE_c iam_ef_kamifubuki;
extern eEC_PROFILE_c iam_ef_kangaeru;
extern eEC_PROFILE_c iam_ef_kantanhu;
extern eEC_PROFILE_c iam_ef_kasamizu;
extern eEC_PROFILE_c iam_ef_kasamizutama;
extern eEC_PROFILE_c iam_ef_kaze;
extern eEC_PROFILE_c iam_ef_kaze_happa;
extern eEC_PROFILE_c iam_ef_kigae;
extern eEC_PROFILE_c iam_ef_kigae_light;
extern eEC_PROFILE_c iam_ef_kikuzu;
extern eEC_PROFILE_c iam_ef_killer;
extern eEC_PROFILE_c iam_ef_kisha_kemuri;
extern eEC_PROFILE_c iam_ef_konpu;
extern eEC_PROFILE_c iam_ef_kpun;
extern eEC_PROFILE_c iam_ef_kyousou_onpu;
extern eEC_PROFILE_c iam_ef_lovelove;
extern eEC_PROFILE_c iam_ef_lovelove2;
extern eEC_PROFILE_c iam_ef_lovelove_heart;
extern eEC_PROFILE_c iam_ef_make_hem;
extern eEC_PROFILE_c iam_ef_make_hem_kira;
extern eEC_PROFILE_c iam_ef_make_hem_light;
extern eEC_PROFILE_c iam_ef_mizutama;
extern eEC_PROFILE_c iam_ef_motiyuge;
extern eEC_PROFILE_c iam_ef_muka;
extern eEC_PROFILE_c iam_ef_naku;
extern eEC_PROFILE_c iam_ef_namida;
extern eEC_PROFILE_c iam_ef_neboke;
extern eEC_PROFILE_c iam_ef_neboke_akubi;
extern eEC_PROFILE_c iam_ef_neboke_awa;
extern eEC_PROFILE_c iam_ef_night13_moon;
extern eEC_PROFILE_c iam_ef_night15_moon;
extern eEC_PROFILE_c iam_ef_ongen;
extern eEC_PROFILE_c iam_ef_otikomi;
extern eEC_PROFILE_c iam_ef_otosiana;
extern eEC_PROFILE_c iam_ef_pun;
extern eEC_PROFILE_c iam_ef_pun_sekimen;
extern eEC_PROFILE_c iam_ef_pun_yuge;
extern eEC_PROFILE_c iam_ef_reset_hole;
extern eEC_PROFILE_c iam_ef_sandsplash;
extern eEC_PROFILE_c iam_ef_shock;
extern eEC_PROFILE_c iam_ef_shooting;
extern eEC_PROFILE_c iam_ef_shooting_kira;
extern eEC_PROFILE_c iam_ef_shooting_set;
extern eEC_PROFILE_c iam_ef_siawase_hana;
extern eEC_PROFILE_c iam_ef_siawase_hana_ch;
extern eEC_PROFILE_c iam_ef_siawase_hikari;
extern eEC_PROFILE_c iam_ef_sibuki;
extern eEC_PROFILE_c iam_ef_situren;
extern eEC_PROFILE_c iam_ef_slip;
extern eEC_PROFILE_c iam_ef_slip_footprint;
extern eEC_PROFILE_c iam_ef_soba_yuge;
extern eEC_PROFILE_c iam_ef_steam;
extern eEC_PROFILE_c iam_ef_string;
extern eEC_PROFILE_c iam_ef_suisou_awa;
extern eEC_PROFILE_c iam_ef_swing_axe;
extern eEC_PROFILE_c iam_ef_swing_net;
extern eEC_PROFILE_c iam_ef_swing_rod;
extern eEC_PROFILE_c iam_ef_taberu;
extern eEC_PROFILE_c iam_ef_takurami;
extern eEC_PROFILE_c iam_ef_takurami_kira;
extern eEC_PROFILE_c iam_ef_tamaire;
extern eEC_PROFILE_c iam_ef_tape;
extern eEC_PROFILE_c iam_ef_tent_lamp;
extern eEC_PROFILE_c iam_ef_tumble;
extern eEC_PROFILE_c iam_ef_tumble_bodyprint;
extern eEC_PROFILE_c iam_ef_tumble_dust;
extern eEC_PROFILE_c iam_ef_turi_hamon;
extern eEC_PROFILE_c iam_ef_turi_hane0;
extern eEC_PROFILE_c iam_ef_turi_hane1;
extern eEC_PROFILE_c iam_ef_turi_mizu;
extern eEC_PROFILE_c iam_ef_turi_suiteki;
extern eEC_PROFILE_c iam_ef_turn_asimoto;
extern eEC_PROFILE_c iam_ef_turn_footprint;
extern eEC_PROFILE_c iam_ef_uranai;
extern eEC_PROFILE_c iam_ef_wait_asimoto;
extern eEC_PROFILE_c iam_ef_walk_asimoto;
extern eEC_PROFILE_c iam_ef_warau;
extern eEC_PROFILE_c iam_ef_yajirushi;
extern eEC_PROFILE_c iam_ef_young_tree;
extern eEC_PROFILE_c iam_ef_yukidama;
extern eEC_PROFILE_c iam_ef_yukidaruma;
extern eEC_PROFILE_c iam_ef_yukihane;

enum {
    eEC_LIGHT_COLOR_DISABLED,
    eEC_LIGHT_COLOR_INCREASING,
    eEC_LIGHT_COLOR_MAXIMUM,
    eEC_LIGHT_COLOR_DECREASING,

    eEC_LIGHT_COLOR_NUM
};

enum {
    eEC_STATE_NORMAL,     // playing
    eEC_STATE_CONTINUOUS, // continuously playing
    eEC_STATE_FINISHED,   // finished playing

    eEC_STATE_NUM
};

typedef struct effect_s eEC_Effect_c;

struct effect_s {
    /* 0x00 */ s16 timer;
    /* 0x02 */ s16 name;
    /* 0x04 */ s16 prog_idx;
    /* 0x06 */ s16 arg0;
    /* 0x08 */ s16 arg1;
    /* 0x0A */ s16 _0A;
    /* 0x0C */ u16 item_name;
    /* 0x0E */ u8 prio;
    /* 0x0F */ u8 state;
    /* 0x10 */ xyz_t position;
    /* 0x1C */ xyz_t velocity;
    /* 0x28 */ xyz_t acceleration;
    /* 0x34 */ xyz_t scale;
    /* 0x40 */ xyz_t offset;
    /* 0x4C */ s16 effect_specific[6];
};

typedef void (*eEC_EFFECT_INIT_PROC)(xyz_t, int, s16, GAME*, u16, s16, s16);
typedef void (*eEC_EFFECT_CT_PROC)(eEC_Effect_c*, GAME*, void*);
typedef void (*eEC_EFFECT_MOVE_PROC)(eEC_Effect_c*, GAME*);
typedef void (*eEC_EFFECT_DRAW_PROC)(eEC_Effect_c*, GAME*);

struct effect_profile_s {
    eEC_EFFECT_INIT_PROC init_proc;
    eEC_EFFECT_CT_PROC ct_proc;
    eEC_EFFECT_MOVE_PROC move_proc;
    eEC_EFFECT_DRAW_PROC draw_proc;
    s16 n_frames;
    s16 child_effect_id;
    f32 max_dist;
};

typedef struct morph_data_s {
    u8 start_frame;
    u8 end_frame;
    u8 morph_flag;
    f32 start_val;
    f32 end_val;
} eEC_morph_data_c;

typedef struct light_data_s {
    s16 ctr;
    rgba_t start_color;
    rgba_t target_color;
    s16 max_frame;
    s16 n_frames;
    int light_state;
    int shadow_flag;
} eEC_light_data_c;

typedef void (*eEC_NAME2EFFECTMAKE_PROC)(int effect_id, xyz_t position, int prio, s16 angle, GAME* game, u16 item_name,
                                         s16 arg0, s16 arg1);
typedef void (*eEC_NAME2EFFECTKILL_PROC)(int effect_id, u16 item_name);
typedef void (*eEC_NAME2EFFECTKILLALL_PROC)(u16 item_name);
typedef void (*eEC_VECTORROTATEY_PROC)(xyz_t* ofs, f32 rot_rad);
typedef s16 (*eEC_RANDOMFIRSTSPEED_PROC)(xyz_t* speed, f32 y, f32 max_z, f32 max_x);
typedef void (*eEC_SETCONTINIOUSENV_PROC)(eEC_Effect_c* effect, s16 unused, s16 timer);
typedef f32 (*eEC_CALCADJUST_PROC)(s16 now_timer, s16 start_timer, s16 end_timer, f32 start_val, f32 end_val);
typedef void (*eEC_AUTOMATRIXXLU_PROC)(GAME* game, xyz_t* pos, xyz_t* scale);
typedef void (*eEC_AUTOMATRIXXLU_OFFSET_PROC)(GAME* game, xyz_t* pos, xyz_t* scale, xyz_t* offset);
typedef eEC_Effect_c* (*eEC_MAKEEFFECT_PROC)(s16 effect_id, xyz_t pos, xyz_t* ofs, GAME* game, void* ct_arg,
                                             u16 item_name, int prio, s16 arg0, s16 arg1);
typedef void (*eEC_MORPHCOMBINE_PROC)(u8* result, eEC_morph_data_c* morph_data, s16 now_timer);
typedef void (*eEC_REGISTEFFECTLIGHT_PROC)(rgba_t color, s16 max_frames, s16 n_frames, int shadow_flag);
typedef void (*eEC_DECIDELIGHTPOWER_PROC)(rgba_t* result_color, rgba_t base_color, xyz_t pos, GAME* game, f32 max_power,
                                          f32 min_power, f32 max_dist);
typedef int (*eEC_CHECKLOOKATBLOCK_PROC)(xyz_t pos);
typedef int (*eEC_EFFECTLIGHTSTATUS_PROC)(rgba_t* color, int* shadow_flag); // returns eEC_LIGHT_COLOR_*
typedef int (*eEC_SPECIALBLOCKCENTERPOS_PROC)(xyz_t* pos, u32 block_kind);

typedef struct effect_control_clip_s {
    /* 0x00 */ eEC_NAME2EFFECTMAKE_PROC effect_make_proc;
    /* 0x04 */ eEC_NAME2EFFECTKILL_PROC effect_kill_proc;
    /* 0x08 */ eEC_VECTORROTATEY_PROC vector_rotate_y_proc;
    /* 0x0C */ eEC_RANDOMFIRSTSPEED_PROC random_first_speed_proc;
    /* 0x10 */ eEC_SETCONTINIOUSENV_PROC set_continious_env_proc;
    /* 0x14 */ eEC_CALCADJUST_PROC calc_adjust_proc;
    /* 0x18 */ eEC_AUTOMATRIXXLU_PROC auto_matrix_xlu_proc;
    /* 0x1C */ eEC_AUTOMATRIXXLU_OFFSET_PROC auto_matrix_xlu_offset_proc;
    /* 0x20 */ void* _20; // unused in AC
    /* 0x24 */ void* _24; // unused in AC
    /* 0x28 */ eEC_MAKEEFFECT_PROC make_effect_proc;
    /* 0x2C */ eEC_MORPHCOMBINE_PROC morph_combine_proc;
    /* 0x30 */ eEC_REGISTEFFECTLIGHT_PROC regist_effect_light;
    /* 0x34 */ eEC_DECIDELIGHTPOWER_PROC decide_light_power_proc;
    /* 0x38 */ eEC_CHECKLOOKATBLOCK_PROC check_lookat_block_proc;
    /* 0x3C */ eEC_EFFECTLIGHTSTATUS_PROC effect_light_status;
    /* 0x40 */ eEC_SPECIALBLOCKCENTERPOS_PROC special_block_center_pos_proc;
    /* 0x44 */ eEC_NAME2EFFECTKILLALL_PROC effect_kill_all_proc;
} eEC_EffectControl_Clip_c;

typedef struct effect_control_s EFFECT_CONTROL_ACTOR;

// almost entirely scrapped in AC (functionally scrapped?)
typedef struct effect_prog_info_s {
    u8 _00[0x18]; // scrapped
    s16 end_frame;
    u8 _1A[0x06]; // scrapped
} eEC_program_info_c;

typedef struct effect_work_s {
    u8 _0000[0x004C - 0x0000];
    eEC_program_info_c program_info[6];
    u8 _010C[0x01D0 - 0x010C];
    int active_effect_num;
    eEC_Effect_c effects[eEC_EFFECT_ACTIVE_MAX];
    u8 effect_active_flags[eEC_EFFECT_ACTIVE_MAX];
    Lights light_info;
    Light_list* light_list;
} eEC_work_c;

struct effect_control_s {
    ACTOR actor_class;
    eEC_EffectControl_Clip_c clip;
};

extern int eMH_special_point_light_num;

extern ACTOR_PROFILE Effect_Control_Profile;

/* NOTE: you must include 'm_common_data.h' to use this macro */
#define eEC_CLIP (Common_Get(clip).effect_clip)

#ifdef __cplusplus
}
#endif

#endif
