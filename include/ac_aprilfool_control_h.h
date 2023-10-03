#ifndef AC_APRILFOOL_CONTROL_H_H
#define AC_APRILFOOL_CONTROL_H_H

#include "types.h"
#include "m_private.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct aprilfool_event_save_data_s {
  u16 talk_bitfield[PLAYER_NUM];
} aAPC_event_save_data_c;

#ifdef __cplusplus
}
#endif

#endif
