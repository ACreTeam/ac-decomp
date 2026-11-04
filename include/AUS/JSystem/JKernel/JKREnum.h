#ifndef JKRENUM_H
#define JKRENUM_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define JKRCOMPRESSION_NONE 0
#define JKRCOMPRESSION_YAY0 1
#define JKRCOMPRESSION_YAZ0 2
#define JKRCOMPRESSION_ASR 3

typedef enum JKRExpandSwitch {
    EXPAND_SWITCH_DEFAULT,    /* Do nothing? treated same as 2 */
    EXPAND_SWITCH_DECOMPRESS, /* Check for compression and decompress */
    EXPAND_SWITCH_NONE        /* Do nothing */
} JKRExpandSwitch;

#ifdef __cplusplus
}
#endif

#endif
