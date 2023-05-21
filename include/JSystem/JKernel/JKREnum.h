#ifndef JKRENUM_H
#define JKRENUM_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum JKRExpandSwitch {
  EXPAND_SWITCH_DEFAULT, /* Do nothing? treated same as 2 */
  EXPAND_SWITCH_DECOMPRESS, /* Check for compression and decompress */
  EXPAND_SWITCH_NONE /* Do nothing */
} JKRExpandSwitch;

#ifdef __cplusplus
}
#endif

#endif
