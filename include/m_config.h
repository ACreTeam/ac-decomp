#ifndef M_CONFIG_H
#define M_CONFIG_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  Config_SOUND_MODE_STEREO,
  Config_SOUND_MODE_MONO,
  Config_SOUND_MODE_HEADPHONES,

  Config_SOUND_MODE_NUM
};

enum {
  Config_VOICE_MODE_ANIMALESE,
  Config_VOICE_MODE_CLICK,
  Config_VOICE_MODE_SILENT,

  Config_VOICE_MODE_NUM
};

/* sizeof(Config_c) == 4 */
typedef struct config_s {
  /* 0x00 */ u8 sound_mode; /* mono, stereo, ... */
  /* 0x01 */ u8 voice_mode; /* silent, babblese, animalese */
  /* 0x02 */ u8 vibration_disabled; /* true/false */
  /* 0x03 */ u8 unused; /* might not exist */
} Config_c;

#ifdef __cplusplus
}
#endif

#endif
