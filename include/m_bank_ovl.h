#ifndef M_BANK_OVL_H
#define M_BANK_OVL_H

#include "types.h"
#include "m_bank_ovl_h.h"
#include "m_submenu_ovl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mBN_CURSOL_MAX 5
#define mBN_CUSROL_OK 6
#define mBN_DEPOSIT_MAX 999999999

struct bank_ovl_s {
  int player_max_bell; /* maximum amount of bells the player can hold */
  int player_bell; /* bells the player started with when opening the bank window */
  int now_bell; /* current bells the player has */
  int bank_bell; /* current bells the bank has */
  int cursol; /* cursor position */
  int bell; /* change in bells */
};

extern void mBN_bank_ovl_set_proc(Submenu* submenu);
extern void mBN_bank_ovl_construct(Submenu* submenu);
extern void mBN_bank_ovl_destruct(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
