#ifndef M_CONFIG_H
#define M_CONFIG_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(Config_c) == 4 */
typedef struct config_s {
  /* 0x00 */ u8 sound_mode; /* mono, stereo, ... */
  /* 0x01 */ u8 voice_mode; /* silent, babblese, animalese */
  /* 0x02 */ u8 vibration_enabled; /* true/false */
  /* 0x03 */ u8 unused; /* might not exist */
} Config_c;

#ifdef __cplusplus
}
#endif

#endif
