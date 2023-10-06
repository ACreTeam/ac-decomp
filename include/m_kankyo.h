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

typedef void (*NATURE_PROC)(ACTOR*);

typedef struct nature_s {
  NATURE_PROC proc;
  void* arg;
} Nature;


typedef struct kankyo_s {
  /* 0x00 */ Lights sun_light;
  /* 0x0E */ u8 pad[0x1C - 0x0E];
  /* 0x1C */ Lights* lights_p;
  /* 0x20 */ u8 pad3[0x9A - 0x20];
  /* 0x9A */ u8 ambientColor[3];
  /* 0x9E */ u8 pad2[0xC0 - 0x9E];
  /* 0xC0 */ f32 unkC0;
  /* 0xC4 */ u8 unkC4;
  /* 0xC8 */ Nature nature;
} Kankyo;

extern void Global_kankyo_ct(GAME_PLAY*, Kankyo*);
extern int mEnv_NowWeather();
extern int mEnv_WindMove();
extern void mEnv_ManagePointLight(GAME_PLAY*, Kankyo*, Global_light*);
extern void Global_kankyo_set(GAME_PLAY*, Kankyo*, Global_light*);
extern void mEnv_GetShadowPrimColor_Light(u8*,u8*,u8*,GAME*);
#ifdef __cplusplus
}
#endif

#endif
