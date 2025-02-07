#ifndef AC_MUSEUM_INSECT_PRIV_H
#define AC_MUSEUM_INSECT_PRIV_H

#include "ac_museum_insect.h"
#include "m_msg.h"
#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_player_lib.h"
#include "m_debug_mode.h"
#include "m_rcp.h"
#include "ac_insect_h.h"

#ifdef __cplusplus
extern "C" {
#endif

#define artificial_padding(lastOffset, currentOffset, typeOfLastMember) \
    u8 __##currentOffset##padding[currentOffset - lastOffset - sizeof(typeOfLastMember)]

struct _MUSEUM_INSECT_PRIVATE_DATA;

typedef void (*PRIV_INSECT_PROCESS)(struct _MUSEUM_INSECT_PRIVATE_DATA*, GAME*);

typedef struct _MUSEUM_INSECT_PRIVATE_DATA {
    int _00;
    artificial_padding(0, 0x14, int);
    f32 _14; // scale
    artificial_padding(0x14, 0x8c, f32);
    s16 _8C;
    s16 _8E;
    s16 _90;
    s16 _92;
} MUSEUM_INSECT_PRIVATE_DATA;

typedef struct _INSECT_DISPLAY_MSG_INFO {
    s16 insectName;
    s16 insectInfo;
} INSECT_DISPLAY_MSG_INFO;

typedef struct _MUSEUM_INSECT_ACTOR {
    ACTOR actor; // offset: 0x0
    MUSEUM_INSECT_PRIVATE_DATA privInsects[aINS_INSECT_TYPE_NUM];
    artificial_padding(0x174, 0x2F78, MUSEUM_INSECT_PRIVATE_DATA[aINS_INSECT_TYPE_NUM]);
    int _2F78;                        // offset: 0x2F78
    int _2F7C;                        // offset: 0x2F7C
    INSECT_DISPLAY_MSG_INFO _2F80[7]; // offset: 0x2F82
    s16 _2F9C[5];                     // offset: 0x2F9C
} MUSEUM_INSECT_ACTOR;

extern PRIV_INSECT_PROCESS minsect_ct[aINS_INSECT_TYPE_NUM];
extern PRIV_INSECT_PROCESS minsect_mv[aINS_INSECT_TYPE_NUM];
extern PRIV_INSECT_PROCESS minsect_dw[aINS_INSECT_TYPE_NUM];
extern f32 minsect_scale_tbl[aINS_INSECT_TYPE_NUM];
extern f32 minsect_scale_tbl[aINS_INSECT_TYPE_NUM];
extern rgba_t window_color;

// ac_museum_insect.c
int Museum_Insect_GetMsgNo(ACTOR* actorx);
int Museum_Insect_Check_Talk_Distance(GAME* game, int i);
void Museum_Insect_Set_MsgInsectInfo(ACTOR* actor, int i);
void Museum_Insect_set_talk_info(ACTOR* actor);
void Museum_Insect_Talk_process(ACTOR* actor, GAME* game);
void Museum_Insect_Actor_ct(ACTOR* actor, GAME* game);
void Museum_Insect_Actor_dt(ACTOR* actor, GAME* game);
void Museum_Insect_Actor_move(ACTOR* actor, GAME* game);
void Museum_Insect_Actor_draw(ACTOR* actor, GAME* game);

// ac_museum_insect_base.c_inc
void mID_insect_moveF(void);
void minsect_amenbo_ct(void);
void minsect_amenbo_mv(void);
void minsect_amenbo_dw(void);
void ari_alone_ct(void);
void ari_alone_make(void);
void ari_alone_dt(void);
void ari_alone_move(void);
void ari_alone_draw(void);
void minsect_ari_ct(void);
void minsect_ari_mv(void);
void minsect_ari_dw(void);
void minsect_draw_shadow(void);
void minsect_fly_BGCheck(void);
void minsect_garden_BGCheck(void);
void minsect_flower_BGCheck(void);
void minsect_goki_BGCheck(void);
void minsect_kanban_BGCheck(void);
void minsect_tree_ObjCheck(void);
void minsect_rock_ObjCheck(void);
void minsect_batta_ObjCheck(void);
void get_now_mind_flag(void);
void set_relax_active_time(MUSEUM_INSECT_PRIVATE_DATA* actor, GAME* game);

// ac_museum_insect_chou.c_inc
void minsect_chou_ct(void);
void minsect_chou_normal_process_init(void);
void minsect_chou_normal_process(void);
void minsect_chou_aim_flower_process_init(void);
void minsect_chou_aim_flower_process(void);
void minsect_chou_flower_process_init(void);
void minsect_chou_flower_process(void);
void minsect_chou_fly_process_init(void);
void minsect_chou_fly_process(void);
void minsect_chou_mv(void);
void minsect_chou_dw(void);

// ac_museum_insect_semi.c_inc
void minsect_semi_ct(void);
void mi_semi_hane_anime(void);
void mi_semi_check_player(void);
void minsect_semi_mv(void);
void minsect_semi_dw(void);

// ac_museum_insect_tonbo.c_inc
void minsect_tonbo_ct(void);
void mi_tonbo_check_player(void);
void minsect_tonbo_bg_check(void);
void minsect_tonbo_near_target_set(void);
void minsect_tonbo_rock_target_set(void);
void minsect_tonbo_suprised_rest_player(void);
void minsect_tonbo_acc_change(void);
void minsect_tonbo_max_speed_set(void);
void minsect_tonbo_aim_distance_set(void);
void minsect_tonbo_aim_angle_check(void);
void minsect_tonbo_normal_process_init(void);
void minsect_tonbo_normal_process(void);
void minsect_tonbo_aim_rock_process_init(void);
void minsect_tonbo_aim_rock_process(void);
void minsect_tonbo_rock_process_init(void);
void minsect_tonbo_rock_process(void);
void minsect_tonbo_rock_wait_process_init(void);
void minsect_tonbo_rock_wait_process(void);
void minsect_tonbo_fly_process_init(void);
void minsect_tonbo_fly_process(void);
void minsect_tonbo_mv(void);
void minsect_tonbo_dw(void);
void minsect_tonbo_MoveF(void);

// ac_museum_insect_batta.c_inc
void mi_batta_check_player(void);
void mi_batta_suzumushi_hane_anime(void);
void mi_batta_hane_anime(void);
void minsect_batta_ct(void);
void minsect_batta_normal_process_init(void);
void minsect_batta_normal_process(void);
void minsect_batta_silent_process_init(void);
void minsect_batta_silent_process(void);
void minsect_batta_jump_wait_process_init(void);
void minsect_batta_jump_wait_process(void);
void minsect_batta_jump_process_init(void);
void minsect_batta_jump_process(void);
void minsect_batta_mv(void);
void minsect_batta_dw(void);

// ac_museum_insect_tentou.c_inc
void mi_tentou_check_player(void);
void mi_tentou_kama_anime(void);
void mi_tentou_wait_init(void);
void mi_tentou_wait(void);
void mi_tentou_move_init(void);
void mi_tentou_move(void);
void mi_tentou_menace_init(void);
void mi_tentou_menace(void);
void mi_tentou_setupAction(void);
void minsect_tentou_ct(void);
void minsect_tentou_mv(void);
void minsect_tentou_dw(void);

// ac_museum_insect_hachi.c_inc
void mi_hachi_hane_anime(void);
void mi_hachi_mitu_init(void);
void mi_hachi_mitu(void);
void mi_hachi_wait_init(void);
void mi_hachi_wait(void);
void mi_hachi_move_init(void);
void mi_hachi_move(void);
void mi_hachi_setupAction(void);
void minsect_hachi_ct(void);
void minsect_hachi_mv(void);
void minsect_hachi_dw(void);

// ac_museum_insect_kabuto.c_inc
void minsect_kabuto_ct(void);
void minsect_kabuto_mv(void);
void minsect_kabuto_dw(void);

// ac_museum_insect_kuwagata.c_inc
void mi_kuwagata_rensa_init(void);
void mi_kuwagata_rensa(void);
void mi_kuwagata_wait_init(void);
void mi_kuwagata_wait(void);
void mi_kuwagata_move_init(void);
void mi_kuwagata_move(void);
void mi_kuwagata_battle_init(void);
void mi_kuwagata_battle(void);
void mi_kuwagata_menace_init(void);
void mi_kuwagata_menace(void);
void mi_kuwagata_attack_init(void);
void mi_kuwagata_attack(void);
void mi_kuwagata_setupAction(void);
void minsect_kuwagata_ct(void);
void minsect_kuwagata_mv(void);
void minsect_kuwagata_dw(void);

// ac_museum_insect_mino.c_inc
void minsect_mino_up_init(void);
void minsect_mino_up(void);
void minsect_mino_down_init(void);
void minsect_mino_down(void);
void minsect_mino_move_init(void);
void minsect_mino_move(void);
void minsect_mino_check_dush_player(void);
void minsect_mino_furiko(void);
void minsect_mino_wait_init(void);
void minsect_mino_wait(void);
void minsect_mino_hineri(void);
void minsect_mino_setupAction(void);
void minsect_mino_ct(void);
void minsect_mino_mv(void);
void minsect_mino_dw(void);

// ac_museum_insect_kumo.c_inc
void minsect_kumo_hide_init(void);
void minsect_kumo_hide(void);
void minsect_kumo_up_init(void);
void minsect_kumo_up(void);
void minsect_kumo_down_init(void);
void minsect_kumo_down(void);
void minsect_kumo_move_init(void);
void minsect_kumo_move(void);
void minsect_kumo_check_player(void);
void minsect_kumo_furiko(void);
void minsect_kumo_wait_init(void);
void minsect_kumo_wait(void);
void minsect_kumo_hineri(void);
void minsect_kumo_setupAction(void);
void minsect_kumo_ct(void);
void minsect_kumo_mv(void);
void minsect_kumo_dw(void);

// ac_museum_insect_goki.c_inc
void minsect_goki_ct(void);
void goki_player_check(void);
void goki_wall_hit_angle_corect_sub(void);
void goki_wall_hit_angle_corect(void);
void goki_set_talk_info_init(void);
void goki_talk_process(void);
void goki_talk_process_init(void);
void minsect_goki_mv(void);
void minsect_goki_dw(void);

// ac_museum_insect_genji.c_inc
void mi_genji_check_player(void);
void genji_light_ct(void);
void genji_light_make(void);
void genji_light_anime(void);
void genji_light_move(void);
void genji_light_draw(void);
void minsect_genji_ct(void);
void minsect_genji_mv(void);
void minsect_genji_dw(void);

// ac_museum_insect_dango.c_inc
void mi_dango_defence_anime(void);
void mi_dango_check_player(void);
void mi_dango_move_init(void);
void mi_dango_move(void);
void mi_dango_defence_init(void);
void mi_dango_defence(void);
void mi_dango_setupAction(void);
void minsect_dango_ct(void);
void minsect_dango_mv(void);
void minsect_dango_dw(void);

// ac_museum_insect_okera.c_inc
void mi_okera_check_player(void);
void minsect_okera_ct(void);
void okera_dig_up_process_init(void);
void okera_dig_up_process(void);
void okera_normal_process_init(void);
void okera_normal_process(void);
void okera_dig_down_process_init(void);
void okera_dig_down_process(void);
void okera_dig_wait_process_init(void);
void okera_dig_wait_process(void);
void minsect_okera_mv(void);
void minsect_okera_dw(void);

// ac_museum_insect_ka.c_inc
void minsect_ka_ct(void);
void minsect_ka_mv(void);
void minsect_ka_dw(void);

#ifdef __cplusplus
}
#endif

#endif
