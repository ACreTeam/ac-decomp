#ifndef AC_MUSEUM_FISH_H
#define AC_MUSEUM_FISH_H

#include "types.h"
#include "m_actor.h"
#include "c_keyframe.h"
#include "libu64/u64types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Museum_Fish_Profile;

typedef struct _FISH_PRIVATE_DATA;

typedef void (*PRIV_FISH_CONSTRUCTOR)(struct _FISH_PRIVATE_DATA*, GAME*);
typedef void (*PRIV_FISH_MOVE)(struct _FISH_PRIVATE_DATA*, GAME*);
typedef void (*PRIV_FISH_DRAW)(struct _FISH_PRIVATE_DATA*, GAME*);
// typedef void (*PRIV_FISH_PROCESS)(struct _FISH_PRIVATE_DATA*, GAME*);
typedef void (*PRIV_FISH_PROCESS)(struct _FISH_PRIVATE_DATA*, GAME*);

// unsure temp structs

typedef struct _MUSEUM_FISH_INIT_DATA {
    f32 _00;
    f32 _04;
    f32 _08;
    f32 _0C;
    f32 _10;
    f32 _14;
    f32 _18;
    f32 _1C;
    f32 _20;
    f32 _24;
    f32 _28;
    s16 _2C;
    s16 _2E;
    s16 _30;
} MUSEUM_FISH_INIT_DATA; // size: 0x34

#define artificial_padding(lastOffset, currentOffset, typeOfLastMember) \
    u8 __##currentOffset##padding[currentOffset - lastOffset - sizeof(typeOfLastMember)]

#define offsetof(structName, memberName) ((size_t) & (((structName*)0)->memberName))

typedef struct _YET_SKELETON {
    cKF_SkeletonInfo_R_c _00; // offset 0, size 0x70
    Mtx _70;                  // offset 70, size
    artificial_padding(0x70, 0x2b0, Mtx);
    Mtx _2b0;
    artificial_padding(0x2b0, 0x46C, Mtx);

    void* _46C;

    artificial_padding(0x46C, 0x4F0, void*);

    s_xyz _4F0;

    artificial_padding(0x4F0, 0x514, s_xyz);

    s_xyz _514;
    artificial_padding(0x514, 0x526, s_xyz);
    s_xyz _526;
    artificial_padding(0x526, 0x538, s_xyz);
    s_xyz _538;
    // unused 2 byte padding here
    xyz_t _540;
    cKF_Skeleton_R_c* _54C;
    cKF_Animation_R_c* _550[2];
} YET_SKELETON; // size 558

typedef struct _YET_SKELETON_2 {
    YET_SKELETON _00;
    f32 _558;
    f32 _55C;
    f32 _560;
    f32 _564;
    s16 _568;
    s16 _56A;
    s16 _56C;
} YET_SKELETON_2;

typedef struct _FISH_PRIVATE_DATA {
    MUSEUM_FISH_INIT_DATA init_data;
    PRIV_FISH_PROCESS _34; // size:4
    YET_SKELETON _38;

    YET_SKELETON_2* _590;
    struct _FISH_PRIVATE_DATA* _594;
    struct _FISH_PRIVATE_DATA* _598;

    s32 _59C; // fish num
    xyz_t _5A0;
    xyz_t _5AC;
    xyz_t _5B8;
    artificial_padding(0x5B8, 0x5D0, xyz_t);
    xyz_t _5D0;
    xyz_t _5DC;
    f32 _5E8;
    f32 _5EC;
    f32 _5F0;
    f32 _5F4;
    f32 _5F8;
    f32 _5FC;
    f32 _600;
    f32 _604;
    f32 _608;
    s_xyz _60C;
    s_xyz _612;
    s_xyz _618;
    s16 _61E;
    s16 _620;
    s16 _622;
    s16 _624;
    s16 _626;
    s16 _628;
    s16 _62A;
    s16 _62C;
    s16 _62E;
    s16 _630;
    s16 _632;
    s16 _634;
    s16 _636;
    s16 _638;
    s16 _63A;
    s16 _63C;
    s16 _63E;
    s16 _640;
    s16 _642;
    s16 _644;
    s16 _646;
} MUSEUM_FISH_PRIVATE_DATA; // size 648

// Holds data for the underwater grass
typedef YET_SKELETON MUSEUM_FISH_KUSA_DATA;

typedef struct _FISH_DISPLAY_MSG_INFO {
    s16 fishName;
    s16 fishInfo;
} FISH_DISPLAY_MSG_INFO;

typedef struct _MUSEUM_FISH_ACTOR {
    ACTOR actor; // offset: 0, size: 0x174
    int _174;
    MUSEUM_FISH_PRIVATE_DATA prvFish[40]; // offset: 0x178 size: 0xFB48
    MUSEUM_FISH_KUSA_DATA prvKusa[14];    // offset: 0xFCB8 size: 0x4AD0
    YET_SKELETON_2 _14788;                // offset: 0x14788 size: 0x570

    u8 _14cf8[16]; // temp

    xyz_t _14d08[2];
    int numFishDisplayed;                         // offset: 0x14d20, size: 4
    int fishDisplayMsgIter;                       // offset: 0x14d24, size: 4
    FISH_DISPLAY_MSG_INFO fishDisplayMsgInfo[10]; // offset: 0x14d28, size: 4*10

    s16 _14d50[20];
    s16 _14d78[20];
    artificial_padding(0x14d78, 0x14daa, s16[20]);

    s16 _14daa[5];
    s16 _14db4;
    s16 _14db6;      // offset: 0x14db6, size: 2
    s16 _14db8;      // offset: 0x14db8, size: 2
    s16 _14dba;      // offset: 0x14dba, size: 2
    s16 _14dbc[2];   // offset: 0x14dbc, size: 4
    s16 _14dc0;      // offset: 0x14dc0, size: 2
    s16 _14dc2;      // offset: 0x14dc2, size: 2
    s16 _14dc4;      // offset: 0x14dc4, size: 2
    s16 _14dc8;      // offset: 0x14dc8, size: 2
} MUSEUM_FISH_ACTOR; // size 14DCA

void Museum_Fish_Prv_data_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game, int fishNum, int r6);
void Museum_Fish_Actor_ct(ACTOR* actor, GAME* game);
void Museum_Fish_Actor_dt(ACTOR* actor, GAME* game);
int Museum_Fish_GetMsgNo(ACTOR* actor);
BOOL Museum_Fish_Check_Talk_Distance(GAME* gamex, int index);
void Museum_Fish_Set_MsgFishInfo(ACTOR* actor, int param2);
void Museum_Fish_set_talk_info(ACTOR* actor);
void Museum_Fish_Talk_process(ACTOR* actor, GAME* game);
void Museum_Fish_Actor_move(ACTOR* actor, GAME* game);
void Museum_Fish_Suisou_draw(ACTOR* actor, GAME* game, int r5);
int kusa_before_disp(GAME* r3, cKF_SkeletonInfo_R_c* r4, int r5, Gfx** r6, u8* r7, void* arg, s_xyz* r9, xyz_t* r10);
void Museum_Fish_Kusa_Draw(ACTOR* actor, GAME* game, int r5);
void Museum_Fish_Actor_draw(ACTOR* actor, GAME* game);
BOOL mfish_cull_check(GAME* game, xyz_t* worldPos, f32 x, f32 y, f32 _y);
void mfish_point_ligh_pos_get(ACTOR* actorx, GAME* game, int r5);
void mfish_point_light_ct(ACTOR* actor, GAME* game);
void mfish_point_light_dt(ACTOR* r30, GAME* r31);
void mfish_point_light_mv(MUSEUM_FISH_ACTOR* actor, GAME* game);
void mfish_normal_light_set(ACTOR* actor, GAME* game);

f32 Rnd_EX_f(f32 v1);
f32 Rnd_EX_fx(f32 v1);
void mfish_base_FishMove(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
int mfish_PosWallCheck(MUSEUM_FISH_PRIVATE_DATA* priv, xyz_t* pos);
BOOL mfish_WallCheck(MUSEUM_FISH_PRIVATE_DATA* priv);
s16 mfish_get_hide_camera_angle(MUSEUM_FISH_PRIVATE_DATA* priv);
void mfish_dummy_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_dummy_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_normal_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_normal_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_turn_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_turn_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_peck_process_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_peck_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_ground_peck_process_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_ground_peck_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_base_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_base_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_onefish_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_onefish_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_before_disp(GAME*, cKF_SkeletonInfo_R_c*, int, Gfx**, u8*, void*, s_xyz*, xyz_t*);
void mfish_onefish_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_ani_base_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_ani_base_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_ani_base_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void Museum_Fish_BigFishObjCheck(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void Museum_Fish_ObjBGCheck(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex, f32 f1, f32 f2);
void Museum_Fish_DonkoBGCheck(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void Museum_Fish_objchk_pos_set(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void Museum_Fish_BGCheck(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void Museum_Fish_Kusa_Check(MUSEUM_FISH_ACTOR* actor, GAME* game);
void Museum_Fish_Object_Check(MUSEUM_FISH_ACTOR* actor, GAME* game);
void mfish_body_wind_anime_play(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_get_player_angle(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game, s16* atanx, s16* atany, f32* distance);
BOOL mfish_peck_check(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_peck_wall_check(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_ground_peck_before_check(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_get_player_area(MUSEUM_FISH_ACTOR* actor, GAME* game);
void mfish_get_flow_vec(xyz_t* pos, MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
s16 mfish_get_escape_angle(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_move_smooth(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_hamon_make(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

void mfish_afish_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_afish_dummy_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_afish_dummy_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_afish_normal_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_afish_normal_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_afish_turn_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_afish_turn_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_afish_base_FishMove(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_afish_base_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_afish_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_afish_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

void mfish_aroana_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_aroana_dummy_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_aroana_dummy_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex);
void mfish_aroana_normal_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_aroana_normal_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_aroana_turn_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_aroana_turn_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_aroana_long_move_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_aroana_long_move_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_aroana_base_FishMove(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_aroana_base_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_aroana_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_aroana_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_num, Gfx** joint_m, u8* joint_f,
                              void* arg, s_xyz* joint1, xyz_t* trans);
void mfish_aroana_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

void mfish_koi_tail_anim_set(MUSEUM_FISH_PRIVATE_DATA* actor, s32 r4);
void mfish_koi_move_smooth(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_koi_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_dummy_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_koi_dummy_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_normal_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_koi_normal_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_turn_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_koi_turn_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_peck_process_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_peck_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_long_move_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_koi_long_move_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_base_FishMove(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_base_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_koi_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_num, Gfx** joint_m, u8* joint_f,
                           void* arg, s_xyz* joint1, xyz_t* trans);
void mfish_koi_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

void mfish_kaseki_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kaseki_normal_init();
void mfish_kaseki_normal();
void mfish_kaseki_move_wall_smooth();
void mfish_kaseki_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_kaseki_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_num, Gfx** joint_m, u8* joint_f,
                              void* arg, s_xyz* joint1, xyz_t* trans);
void mfish_kaseki_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

void mfish_bass_tail_anim_set(MUSEUM_FISH_PRIVATE_DATA* actor, s32 r4);
void mfish_bass_base_FishMove(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_bass_dummy_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_bass_dummy_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_bass_normal_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_bass_normal_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_bass_turn_process_init(MUSEUM_FISH_PRIVATE_DATA* actor);
void mfish_bass_turn_process(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_bass_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_bass_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_bass_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

void mfish_seafish_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_seafish_normal_init();
void mfish_seafish_normal(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_seafish_turn_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_seafish_turn(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_seafish_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_seafish_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_num, Gfx** joint_m, u8* joint_f,
                               void* arg, s_xyz* joint1, xyz_t* trans);
void mfish_seafish_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

void mfish_tai_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_tai_normal_init();
void mfish_tai_normal();
void mfish_tai_turn_init();
void mfish_tai_turn();
void mfish_tai_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_tai_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_num, Gfx** joint_m, u8* joint_f,
                           void* arg, s_xyz* joint1, xyz_t* trans);
void mfish_tai_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

void mfish_small_fish_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_sfish_normal_init();
void mfish_sfish_normal();
void mfish_sfish_turn_init();
void mfish_sfish_turn();
void mfish_small_fish_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_sfish_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_num, Gfx** joint_m, u8* joint_f,
                             void* arg, s_xyz* joint1, xyz_t* trans);
void mfish_small_fish_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

void mfish_gupi_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_gupi_normal_init();
void mfish_gupi_normal();
void mfish_gupi_turn_init();
void mfish_gupi_turn();
void mfish_gupi_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_gupi_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_num, Gfx** joint_m, u8* joint_f,
                            void* arg, s_xyz* joint1, xyz_t* trans);
void mfish_gupi_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

void mfish_medaka_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_medaka_normal_init();
void mfish_medaka_normal();
void mfish_medaka_turn_init();
void mfish_medaka_turn();
void mfish_medaka_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_medaka_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_num, Gfx** joint_m, u8* joint_f,
                              void* arg, s_xyz* joint1, xyz_t* trans);
void mfish_medaka_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

void mfish_kingyo_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kingyo_normal_init();
void mfish_kingyo_normal();
void mfish_kingyo_turn_init();
void mfish_kingyo_turn();
void mfish_kingyo_peck_init();
void mfish_kingyo_peck();
void mfish_kingyo_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_kingyo_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_num, Gfx** joint_m, u8* joint_f,
                              void* arg, s_xyz* joint1, xyz_t* trans);
void mfish_kingyo_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

void mfish_dojou_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_dojou_normal_init();
void mfish_dojou_normal();
void mfish_dojou_turn_init();
void mfish_dojou_turn();
void mfish_dojou_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_dojou_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_num, Gfx** joint_m, u8* joint_f,
                             void* arg, s_xyz* joint1, xyz_t* trans);
void mfish_dojou_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

void mfish_donko_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_donko_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_donko_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_num, Gfx** joint_m, u8* joint_f,
                             void* arg, s_xyz* joint1, xyz_t* trans);
void mfish_donko_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

void mfish_big_fish_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_big_fish_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_bfish_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_num, Gfx** joint_m, u8* joint_f,
                             void* arg, s_xyz* joint1, xyz_t* trans);
void mfish_big_fish_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

void mfish_ito_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_ito_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_ito_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_num, Gfx** joint_m, u8* joint_f,
                           void* arg, s_xyz* joint1, xyz_t* trans);
void mfish_ito_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

void mfish_unagi_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_unagi_get_next_rail_type();
void mfish_unagi_aim_wind_angle_calc();
void mfish_unagi_rail_move_init();
void mfish_unagi_rail_move();
void mfish_unagi_normal_to_reverse_init();
void mfish_unagi_normal_to_reverse();
void mfish_unagi_rail_move_reverse_init();
void mfish_unagi_rail_move_reverse();
void mfish_unagi_reverse_to_normal_init();
void mfish_unagi_reverse_to_normal();
void mfish_unagi_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_unagi_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_num, Gfx** joint_m, u8* joint_f,
                             void* arg, s_xyz* joint1, xyz_t* trans);
void mfish_unagi_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

void mfish_namazu_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_namazu_body_wind_anime_play();
void mfish_namazu_normal_process_init();
void mfish_namazu_normal_process();
void mfish_namazu_dummy_process_init();
void mfish_namazu_dummy_process();
void mfish_namazu_turn_process_init();
void mfish_namazu_turn_process();
void mfish_namazu_ground_sweep_process_init();
void mfish_namazu_ground_sweep_process();
void mfish_namazu_base_FishMove();
void mfish_namazu_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_namazu_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_num, Gfx** joint_m, u8* joint_f,
                              void* arg, s_xyz* joint1, xyz_t* trans);
void mfish_namazu_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

void mfish_zarigani_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_zarigani_normal_process_init();
void mfish_zarigani_normal_process();
void mfish_zarigani_wait_process_init();
void mfish_zarigani_wait_process();
void mfish_zarigani_stand_process_init();
void mfish_zarigani_stand_process();
void mfish_zarigani_jump_process_init();
void mfish_zarigani_jump_process();
void mfish_zarigani_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
BOOL mfish_zarigani_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_num, Gfx** joint_m, u8* joint_f,
                                void* arg, s_xyz* joint1, xyz_t* trans);
void mfish_zarigani_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

void mfish_kurage_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kurage_normal_init();
void mfish_kurage_normal();
void mfish_kurage_turn_init();
void mfish_kurage_turn();
void mfish_kurage_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kurage_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

void mfish_hasu_ct(YET_SKELETON_2* actor, GAME* game);
void mfish_hasu_mv();
void mfish_hasu_dw();
void mfish_kaeru_ct();
void mfish_kaeru_mv();
BOOL hasu_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_num, Gfx** joint_m, u8* joint_f, void* arg,
                      s_xyz* joint1, xyz_t* trans);
BOOL hasu_after_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_num, Gfx** joint_m, u8* joint_f, void* arg,
                     s_xyz* joint1, xyz_t* trans);
void mfish_kaeru_dw();

#ifdef __cplusplus
}
#endif

#endif
