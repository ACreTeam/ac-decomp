#ifndef M_KANKYO_H
#define M_KANKYO_H

#include "types.h"
#include "m_lights.h"
#include "game.h"

#ifdef __cplusplus
extern "C" {
#endif

enum weather {
  mEnv_WEATHER_CLEAR,
  mEnv_WEATHER_RAIN,
  mEnv_WEATHER_SNOW,
  mEnv_WEATHER_SAKURA,
  mEnv_WEATHER_LEAVES,
  
  mEnv_WEATHER_NUM
};

enum weather_intensity {
  mEnv_WEATHER_INTENSITY_NONE,
  mEnv_WEATHER_INTENSITY_LIGHT,
  mEnv_WEATHER_INTENSITY_NORMAL,
  mEnv_WEATHER_INTENSITY_HEAVY,

  mEnv_WEATHER_INTENSITY_NUM,
};

#define mEnv_SAVE_GET_WEATHER_TYPE(w) (((w) & 0xF0) >> 4)
#define mEnv_SAVE_GET_WEATHER_INTENSITY(w) ((w) & 0xF)

typedef struct base_light_s {
  u8 ambient_color[3];
  s8 sun_dir[3];
  u8 sun_color[3];
  s8 moon_dir[3];
  u8 moon_color[3];
  u8 fog_color[3];
  s16 fog_near;
  s16 fog_far;
  u8 shadow_color[3];
  u8 room_color[3];
  u8 sun_color_window[3];
  u8 moon_color_window[3];
    u8 background_color[3];
} BaseLight;

typedef struct add_light_info_s {
  s16 ambient_color[3];
  s16 diffuse_color[3];
  s16 fog_color[3];
  s16 fog_near;
  s16 fog_far;
} AddLightInfo;

typedef void (*NATURE_PROC)(ACTOR*);

typedef struct nature_s {
  NATURE_PROC proc;
  void* arg;
} Nature;

typedef struct kankyo_s {
  /* 0x00 */ Lights sun_light;
  /* 0x0E */ Lights moon_light;
  /* 0x1C */ Lights* lamp_light;
  /* 0x20 */ Lights point_light;
  /* 0x2E */ u8 _2E[0x78 - 0x2e];
  /* 0x78 */ AddLightInfo add_light_info; /* extra values added to specific light parameters */
  /* 0x90 */ int _90;
  /* 0x94 */ BaseLight base_light;
  /* 0xBA */ u8 _BA[0xC0 - 0xBA];
  /* 0xC0 */ f32 shadow_pos;
  /* 0xC4 */ u8 shadow_alpha;
  /* 0xC5 */ u8 countdown_timer;
  /* 0xC8 */ Nature nature;
} Kankyo;

extern void Global_kankyo_ct(GAME_PLAY*, Kankyo*);
extern int mEnv_NowWeather();
extern int mEnv_WindMove();
extern void mEnv_ManagePointLight(GAME_PLAY*, Kankyo*, Global_light*);
extern void Global_kankyo_set(GAME_PLAY*, Kankyo*, Global_light*);
extern void mEnv_GetShadowPrimColor_Light(u8*,u8*,u8*,GAME*);
extern f32 mKK_windowlight_alpha_get();
#ifdef __cplusplus
}
#endif

#endif
