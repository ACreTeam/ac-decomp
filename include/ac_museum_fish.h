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

// unsure temp structs

typedef struct _YET_SKELETON {
    cKF_SkeletonInfo_R_c _00;
    Mtx _70;
    u8 padding[0x200];
    Mtx _2b0;
} YET_SKELETON;

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

typedef struct _FISH_PRIVATE_DATA {
    MUSEUM_FISH_INIT_DATA init_data;
    void* _34; // function pointer to dummy_process function
    YET_SKELETON _38;
    void* _4A4;
    void* _584;
    void* _588;
    void* _590;
    s32 _59C; // fish num
    xyz_t _5A0;
    f32 _5AC;
    f32 _5B0;
    f32 _5B4;
    f32 _5D0;
    f32 _5D4;
    f32 _5D8;
    xyz_t _5DC;
    f32 _5E8;
    f32 _5EC;
    f32 _5F0;
    f32 _5F4;
    s_xz _60C;
    s_xz _612;
    s16 _61C;
    s16 _622;
    s16 _624;
    s16 _626;
    s16 _62C;
    s16 _62E;
    s16 _630;
    s16 _632;
    s16 _634;
    s16 _636;
    s16 _640;
} MUSEUM_FISH_PRIVATE_DATA;

typedef struct _MUSEUM_FISH_PRIVATE_DATA2 {
    cKF_SkeletonInfo_R_c _00;
    s_xyz _4F0;
    s_xyz _514;
    s16 _538;
    s16 _53A;
    s16 _53C;
    float _540;
    float _548;
    void* _54C;
} MUSEUM_FISH_PRIVATE_DATA2;

typedef struct _FISH_DISPLAY_MSG_INFO {
    s16 fishName;
    s16 fishInfo;
} FISH_DISPLAY_MSG_INFO;

typedef struct _MUSEUM_FISH_ACTOR {
    ACTOR actor;                          // offset: 0, size: 0x174
    MUSEUM_FISH_PRIVATE_DATA prvFish[40]; // offset: 0x264 size: 0x648 * 40
    MUSEUM_FISH_PRIVATE_DATA2 prvFish2[14];
    s16 _101f0;
    s16 _101f4;
    void* _14788;
    xyz_t _14d08;
    xyz_t _14d14;
    int numFishDisplayed;                         // offset: 0x14d20, size: 4
    int fishDisplayMsgIter;                       // offset: 0x14d24, size: 4
    FISH_DISPLAY_MSG_INFO fishDisplayMsgInfo[10]; // offset: 0x14d28, size: 4*10

    s16 _14d50[0x10];
    s16 _14d78[0x10];
    s16 _14db4;
    s16 _14db6; // offset: 0x14db6, size: 2
    s16 _14db8; // offset: 0x14db8, size: 2
    s16 _14dba; // offset: 0x14dba, size: 2
    s16 _14dbc; // offset: 0x14dbc, size: 2
    s16 _14dbe; // offset: 0x14dbe, size: 2
    s16 _14dc0; // offset: 0x14dc0, size: 2
    s16 _14dc2; // offset: 0x14dc2, size: 2
    s16 _14dc4; // offset: 0x14dc4, size: 2
    s16 _14dc8; // offset: 0x14dc8, size: 2
} MUSEUM_FISH_ACTOR;

void Museum_Fish_Prv_data_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game, int fishNum, int r6);
void Museum_Fish_Actor_ct(ACTOR* actor, GAME* game);
void Museum_Fish_Actor_dt(ACTOR* actor, GAME* game);
int Museum_Fish_GetMsgNo(ACTOR* actor);
BOOL Museum_Fish_Check_Talk_Distance(GAME* gamex, int index);
void Museum_Fish_Set_MsgFishInfo();
void Museum_Fish_set_talk_info();
void Museum_Fish_Talk_process();
void Museum_Fish_Actor_move(ACTOR* actor, GAME* game);
void Museum_Fish_Suisou_draw(MUSEUM_FISH_ACTOR* actor, GAME* game, int r5);
void kusa_before_disp();
void Museum_Fish_Kusa_Draw(ACTOR* actor, GAME* game);
void Museum_Fish_Actor_draw(ACTOR* actor, GAME* game);
BOOL mfish_cull_check(GAME* game, xyz_t* worldPos, f32 x, f32 y, f32 _y);
void mfish_point_ligh_pos_get();
void mfish_point_light_ct(ACTOR* actor, GAME* game);
void mfish_point_light_dt(ACTOR* r30, GAME* r31);
void mfish_point_light_mv(ACTOR* actor, GAME* game);
void mfish_normal_light_set();

f32 Rnd_EX_f(f32 v1);
f32 Rnd_EX_fx(f32 v1);
void mfish_base_FishMove();
int mfish_PosWallCheck(MUSEUM_FISH_PRIVATE_DATA* priv, xyz_t* pos);
void mfish_WallCheck();
s16 mfish_get_hide_camera_angle(MUSEUM_FISH_PRIVATE_DATA* priv);
void mfish_dummy_process_init();
void mfish_dummy_process();
void mfish_normal_process_init();
void mfish_normal_process();
void mfish_turn_process_init();
void mfish_turn_process();
void mfish_peck_process_init();
void mfish_peck_process();
void mfish_ground_peck_process_init();
void mfish_ground_peck_process();
void mfish_base_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_base_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_onefish_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_onefish_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
int mfish_before_disp(GAME*, cKF_SkeletonInfo_R_c*, int, Gfx**, u8*, void*, s_xyz*, xyz_t*);
void mfish_onefish_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_ani_base_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_ani_base_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_ani_base_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void Museum_Fish_BigFishObjCheck();
void Museum_Fish_ObjBGCheck();
void Museum_Fish_DonkoBGCheck();
void Museum_Fish_objchk_pos_set();
void Museum_Fish_BGCheck();
void Museum_Fish_Kusa_Check();
void Museum_Fish_Object_Check();
void mfish_body_wind_anime_play();
void mfish_get_player_angle();
void mfish_peck_check();
void mfish_peck_wall_check();
void mfish_ground_peck_before_check();
void mfish_get_player_area();
void mfish_get_flow_vec(xyz_t* pos, MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_get_escape_angle();
void mfish_move_smooth();
void mfish_hamon_make();
void mfish_afish_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_afish_dummy_process_init();
void mfish_afish_dummy_process();
void mfish_afish_normal_process_init();
void mfish_afish_normal_process();
void mfish_afish_turn_process_init();
void mfish_afish_turn_process();
void mfish_afish_base_FishMove();
void mfish_afish_base_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_afish_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_afish_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_aroana_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_aroana_dummy_process_init();
void mfish_aroana_dummy_process();
void mfish_aroana_normal_process_init();
void mfish_aroana_normal_process();
void mfish_aroana_turn_process_init();
void mfish_aroana_turn_process();
void mfish_aroana_long_move_process_init();
void mfish_aroana_long_move_process();
void mfish_aroana_base_FishMove();
void mfish_aroana_base_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_aroana_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_aroana_before_disp();
void mfish_aroana_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_tail_anim_set();
void mfish_koi_move_smooth();
void mfish_koi_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_dummy_process_init();
void mfish_koi_dummy_process();
void mfish_koi_normal_process_init();
void mfish_koi_normal_process();
void mfish_koi_turn_process_init();
void mfish_koi_turn_process();
void mfish_koi_peck_process_init();
void mfish_koi_peck_process();
void mfish_koi_long_move_process_init();
void mfish_koi_long_move_process();
void mfish_koi_base_FishMove();
void mfish_koi_base_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_koi_before_disp();
void mfish_koi_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kaseki_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kaseki_normal_init();
void mfish_kaseki_normal();
void mfish_kaseki_move_wall_smooth();
void mfish_kaseki_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kaseki_before_disp();
void mfish_kaseki_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_bass_tail_anim_set();
void mfish_bass_base_FishMove();
void mfish_bass_dummy_process_init();
void mfish_bass_dummy_process();
void mfish_bass_normal_process_init();
void mfish_bass_normal_process();
void mfish_bass_turn_process_init();
void mfish_bass_turn_process();
void mfish_bass_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_bass_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_bass_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_seafish_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_seafish_normal_init();
void mfish_seafish_normal();
void mfish_seafish_turn_init();
void mfish_seafish_turn();
void mfish_seafish_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_seafish_before_disp();
void mfish_seafish_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_tai_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_tai_normal_init();
void mfish_tai_normal();
void mfish_tai_turn_init();
void mfish_tai_turn();
void mfish_tai_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_tai_before_disp();
void mfish_tai_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_small_fish_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_sfish_normal_init();
void mfish_sfish_normal();
void mfish_sfish_turn_init();
void mfish_sfish_turn();
void mfish_small_fish_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_sfish_before_disp();
void mfish_small_fish_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_gupi_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_gupi_normal_init();
void mfish_gupi_normal();
void mfish_gupi_turn_init();
void mfish_gupi_turn();
void mfish_gupi_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_gupi_before_disp();
void mfish_gupi_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_medaka_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_medaka_normal_init();
void mfish_medaka_normal();
void mfish_medaka_turn_init();
void mfish_medaka_turn();
void mfish_medaka_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_medaka_before_disp();
void mfish_medaka_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kingyo_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kingyo_normal_init();
void mfish_kingyo_normal();
void mfish_kingyo_turn_init();
void mfish_kingyo_turn();
void mfish_kingyo_peck_init();
void mfish_kingyo_peck();
void mfish_kingyo_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kingyo_before_disp();
void mfish_kingyo_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_dojou_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_dojou_normal_init();
void mfish_dojou_normal();
void mfish_dojou_turn_init();
void mfish_dojou_turn();
void mfish_dojou_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_dojou_before_disp();
void mfish_dojou_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_donko_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_donko_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_donko_before_disp();
void mfish_donko_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_big_fish_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_big_fish_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_bfish_before_disp();
void mfish_big_fish_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_ito_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_ito_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_ito_before_disp();
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
void mfish_unagi_before_disp();
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
void mfish_namazu_before_disp();
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
void mfish_zarigani_before_disp();
void mfish_zarigani_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kurage_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kurage_normal_init();
void mfish_kurage_normal();
void mfish_kurage_turn_init();
void mfish_kurage_turn();
void mfish_kurage_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kurage_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_hasu_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_hasu_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_hasu_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kaeru_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void mfish_kaeru_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);
void hasu_before_disp();
void hasu_after_disp();
void mfish_kaeru_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game);

#ifdef __cplusplus
}
#endif

#endif
