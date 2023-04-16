#ifndef M_LIB_H
#define M_LIB_H

#include "types.h"

#define ABS(x) ((x) >= 0) ? (x) : -(x)
#define SQ(x) ((x)*(x))

typedef struct xy_s  {
    f32 x, y;
} xy_t;

typedef struct xyz_t {
    f32 x, y, z;
} xyz_t;

typedef struct s_xyz {
    s16 x, y, z;
} s_xyz;

typedef struct rgba_t { //can be put in other place
    u8 r, g, b, a;
} rgba_t;

extern void mem_copy(u8*, u8*, u32);
extern void mem_clear(u8*, u32, u8);
extern s32 mem_cmp(u8*, u8*, u32);

extern f32 sin_s(s16);
extern f32 cos_s(s16);

extern s32 chase_angle(s16*, s16, s16);
extern s32 chase_s(s16*, s16, s16);
extern s32 chase_f(f32*, f32, f32);
extern f32 chase_xyz_t(xyz_t*, xyz_t*, f32);
extern s32 chase_angle2(s16*, s16, s16);

extern void inter_float(f32*, f32, s32);
extern s16 get_random_timer(s16, s16);

extern void xyz_t_move(xyz_t*, xyz_t*);
extern void xyz_t_move_s_xyz(xyz_t*, s_xyz*);
extern void xyz_t_add(xyz_t*, xyz_t*, xyz_t*);
extern void xyz_t_sub(xyz_t*, xyz_t*, xyz_t*);
extern void xyz_t_mult_v(xyz_t*, f32);

extern f32 search_position_distance(xyz_t*, xyz_t*);
extern f32 search_position_distanceXZ(xyz_t*, xyz_t*);
extern s16 search_position_angleY(xyz_t*, xyz_t*);
extern s16 search_position_angleX(xyz_t*, xyz_t*);

extern void add_calc2(f32*, f32, f32, f32);
extern void add_calc0(f32*, f32, f32);

extern s16 add_calc_short_angle2(s16*, s16, f32, s16, s16);
extern s16 add_calc_short_angle3(s16*, s16, f32, s16, s16);

extern void rgba_t_move(rgba_t*, rgba_t*);

extern u32 none_proc1(void);
extern void none_proc2(void);

extern void _Game_play_isPause(u32); //IDK

//Unsure
//?? check_percent_abs();
//?? get_percent_forAccelBrake();
//void Game_play_Projection_Trans(game_play*, Vec3f*, Vec3f);
extern f32 get_percent(s32, s32, s32);
#endif