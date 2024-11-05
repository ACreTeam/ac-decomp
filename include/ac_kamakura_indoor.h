#ifndef AC_KAMAKURA_INDOOR_H
#define AC_KAMAKURA_INDOOR_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aKI_CANDLE_NUM 2

typedef struct kamakura_indoor_candle_ring_s {
    rgba_t color;
    f32 scale;
} aKI_candle_ring_c;

typedef struct kamakura_indoor_candle_fire_s {
    u8* tex_p;
    rgba_t color;
} aKI_candle_fire_c;

typedef struct kamakura_indoor_mochi_s {
    int move_bg_idx;
    mCoBG_bg_regist_c bg_regist;
    xyz_t pos;
    xyz_t old_pos;
    s16 angle_y;
    f32 scale_rate;
} aKI_mochi_c;

typedef struct kamakura_indoor_actor_s KAMAKURA_INDOOR_ACTOR;

struct kamakura_indoor_actor_s {
    ACTOR actor_class;
    aKI_candle_ring_c candle_ring[aKI_CANDLE_NUM];
    aKI_candle_fire_c candle_fire[aKI_CANDLE_NUM];
    aKI_mochi_c mochi;
    u8 _1E0[0x200 - 0x1E0];
};

extern ACTOR_PROFILE Kamakura_Indoor_Profile;

#ifdef __cplusplus
}
#endif

#endif
