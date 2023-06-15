#ifndef M_SUBMENU_H
#define M_SUBMENU_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  mSM_PROCESS_WAIT,
  mSM_PROCESS_PREWAIT,
  mSM_PROCESS_LINKWAIT,
  mSM_PROCESS_PLAY,
  mSM_PROCESS_END,

  mSM_PROCESS_NUM
};

/* sizeof (Submenu) == 0x1B8 */
typedef struct submenu_s {
  /* 0x000 */ int mode;
  /* 0x004 */ int menu_type;
  /* 0x008 */ int current_menu_type;

  /* 0x00C */ int process_status;
  /* 0x010 */ u8 _10[0x1B8 - 0x010];
  // TODO: finish
} Submenu;

#ifdef __cplusplus
}
#endif

#endif
