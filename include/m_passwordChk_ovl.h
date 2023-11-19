#ifndef M_PASSWORDCHK_OVL_H
#define M_PASSWORDCHK_OVL_H

#include "types.h"
#include "m_passwordChk_ovl_h.h"
#include "m_submenu_ovl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mPC_STR_SIZE 14
#define mPC_LINE_COUNT 2

struct passwordChk_ovl_s {
  int selected_line;
  u8 _04;
  u8 _05;
  u8 line0[mPC_STR_SIZE];
  u8 line1[mPC_STR_SIZE];
};

#ifdef __cplusplus
}
#endif

#endif
