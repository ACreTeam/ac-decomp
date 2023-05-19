#ifndef M_KANKYO_H
#define M_KANKYO_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

enum weather {
  mEv_WEATHER_CLEAR,
  mEv_WEATHER_RAIN,
  mEv_WEATHER_SNOW,
  mEv_WEATHER_SAKURA,
  mEv_WEATHER_LEAVES,
  
  mEv_WEATHER_NUM
};

extern int mEnv_NowWeather();

#ifdef __cplusplus
}
#endif

#endif
