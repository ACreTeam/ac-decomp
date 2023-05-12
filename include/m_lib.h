#ifndef M_LIB_H
#define M_LIB_H

#include "types.h"
#include "m_play.h"
#include "m_actor_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define SHT_MAX 32767.0f
#define SHT_MINV (1.0f / SHT_MAX)
#define ABS(x) (((x) >= 0) ? (x) : -(x))
#define SQ(x) ((x)*(x))

typedef struct xy_s {
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

extern void mem_copy(u8* dst, u8* src, size_t size);
extern void mem_clear(u8* dst, size_t size, u8 val);
extern int mem_cmp(u8* p1, u8* p2, size_t size);

extern f32 cos_s(s16 angle);
extern f32 sin_s(s16 angle);

extern int chase_angle(s16* const pValue, const s16 target, s16 step);
extern int chase_s(s16* const pValue, const s16 target, s16 step);
extern int chase_f(f32* const pValue, const f32 target, f32 step);
extern f32 chase_xyz_t(xyz_t* const pValue, const xyz_t* const target, const f32 fraction);
extern int chase_angle2(s16* const pValue, const s16 limit, const s16 step);

extern void inter_float(f32* const pValue, const f32 arg1, const int step);
extern s16 get_random_timer(const s16 base, const s16 range);

extern void xyz_t_move(xyz_t* const dest, const xyz_t* const src);
extern void xyz_t_move_s_xyz(xyz_t* const dest, const s_xyz* const src);
extern void xyz_t_add(const xyz_t* const augend, const xyz_t* const addend, xyz_t* const total);
extern void xyz_t_sub(const xyz_t* const minuend, const xyz_t* const subtrahend, xyz_t* const diff);
extern void xyz_t_mult_v(xyz_t* const multiplicand, const f32 multiplier);

extern f32 search_position_distance(const xyz_t* const pos, const xyz_t* const target);
extern f32 search_position_distanceXZ(const xyz_t* const pos, const xyz_t* const target);
extern s16 search_position_angleY(const xyz_t* const pos, const xyz_t* const target);
extern s16 search_position_angleX(const xyz_t* const pos, const xyz_t* const target);

extern f32 add_calc(f32* pValue, f32 target, f32 fraction, f32 maxStep, f32 minStep);
extern void add_calc2(f32* pValue, f32 target, f32 fraction, f32 maxStep);
extern void add_calc0(f32* pValue, f32 fraction, f32 maxStep);

extern s16 add_calc_short_angle2(s16* pValue, s16 target, f32 fraction, s16 maxStep, s16 minStep);
extern s16 add_calc_short_angle3(s16* pValue, s16 target, f32 fraction, s16 maxStep, s16 minStep);

extern void rgba_t_move(rgba_t* dest, const rgba_t* const src);

extern int none_proc1();
extern void none_proc2(ACTOR* actor, GAME* game);

extern int _Game_play_isPause(GAME_PLAY* play);
extern f32 check_percent_abs(f32 x, f32 min, f32 max, f32 scale, int shift_by_min);
extern f32 get_percent_forAccelBrake(const f32 now, const f32 start, const f32 end, const f32 accelerateDist, const f32 brakeDist);
extern void Game_play_Projection_Trans(GAME_PLAY* const play, xyz_t* wpos, xyz_t* screen_pos);

extern f32 get_percent(const int max, const int min, const int x);

#ifdef __cplusplus
}
#endif

#endif
