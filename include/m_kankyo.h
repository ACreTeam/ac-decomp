#ifndef M_KANKYO_H
#define M_KANKYO_H

#include "types.h"

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

extern int mEnv_NowWeather();

#ifdef __cplusplus
}
#endif

#endif
