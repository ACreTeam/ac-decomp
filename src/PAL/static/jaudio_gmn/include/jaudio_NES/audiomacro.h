#ifndef AUDIOMACRO_H
#define AUDIOMACRO_H

#include "types.h"
#include "jaudio_NES/sub_sys.h"

#define AUDIOCMD_RESET_AUDIO_HEAP_CMD(spec_id) Nap_SetS32(NA_MAKE_COMMAND(AUDIOCMD_RESET_AUDIO_HEAP, 0, 0, 0), spec_id)

#endif
