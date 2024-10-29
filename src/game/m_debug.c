#include "m_debug.h"

#include "libc64/malloc.h"

Debug_mode* debug_mode;

extern void new_Debug_mode() {
  int i;

  debug_mode = (Debug_mode*)malloc(sizeof(Debug_mode));

  debug_mode->mode = 0;
  debug_mode->type = 0;
  debug_mode->input_r = 0;
  debug_mode->old_key = 0;
  debug_mode->key_wait = 0;

  for (i = 0; i < DEBUG_REG_COUNT; i++) {
    debug_mode->r[i] = 0;
  }
}
