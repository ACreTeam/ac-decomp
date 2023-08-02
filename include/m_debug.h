#ifndef M_DEBUG_H
#define M_DEBUG_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  DEBUG_REG_START = 0,
  DEBUG_REG_REG = DEBUG_REG_START,
  DEBUG_REG_SREG,
  DEBUG_REG_OREG,
  DEBUG_REG_PREG,
  DEBUG_REG_QREG,
  DEBUG_REG_MREG,
  DEBUG_REG_SBREG,
  DEBUG_REG_DREG,
  DEBUG_REG_UREG,
  DEBUG_REG_IREG,
  DEBUG_REG_ZREG,
  DEBUG_REG_CRV,
  DEBUG_REG_NS1,
  DEBUG_REG_SND,
  DEBUG_REG_XREG,
  DEBUG_REG_CRV2,
  DEBUG_REG_DEMOREG,
  DEBUG_REG_TREG,
  DEBUG_REG_WREG,
  DEBUG_REG_AREG,
  DEBUG_REG_VREG,
  DEBUG_REG_HREG,
  DEBUG_REG_GREG,
  DEBUG_REG_mREG,
  DEBUG_REG_nREG,
  DEBUG_REG_BREG,
  DEBUG_REG_DORO,
  DEBUG_REG_kREG,
  DEBUG_REG_BAK,
  DEBUG_REG_PLAYERREG,
  DEBUG_REG_NMREG,
  
  DEBUG_REG_NIIREG,
  DEBUG_REG_GENREG,
  DEBUG_REG_MYKREG,
  DEBUG_REG_CAMREG,
  DEBUG_REG_SAKREG,
  DEBUG_REG_TAKREG,
  DEBUG_REG_PL2REG,

  DEBUG_REG_MAX
} DEBUG_REG;

#define DEBUG_REG_SIZE 16
#define DEBUG_REG_GROUP 6

#define DEBUG_REG_COUNT (DEBUG_REG_SIZE * DEBUG_REG_GROUP * DEBUG_REG_MAX)

typedef struct debug_mode_s {
  u8 mode;
  u8 type;
  s8 input_r;
  s8 key_wait;

  int old_key;
  int __pad[3];

  s16 r[DEBUG_REG_SIZE * DEBUG_REG_GROUP * DEBUG_REG_MAX];
} Debug_mode;

extern Debug_mode* debug_mode;

#define REGADDR(reg, idx) (debug_mode->r[DEBUG_REG_SIZE * DEBUG_REG_GROUP * DEBUG_REG_##reg + (idx)])

#define GETREG(reg, idx) ((s16)(REGADDR(reg, idx)))
#define SETREG(reg, idx, val) (REGADDR(reg, idx) = (val))

extern void new_Debug_mode();
#ifdef __cplusplus
};
#endif

#endif
