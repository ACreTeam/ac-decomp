#ifndef S_CPAK_H
#define S_CPAK_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct save_pak_s {
  u8 unused[0x54];
} sCPk_c;

extern int sCPk_PakOpen(sCPk_c* s_pak);

#ifdef __cplusplus
}
#endif

#endif
