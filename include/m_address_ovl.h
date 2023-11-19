#ifndef M_ADDRESS_OVL_H
#define M_ADDRESS_OVL_H

#include "types.h"
#include "m_address_ovl_h.h"
#include "m_submenu_ovl.h"
#include "m_mail.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mAD_PAGE_NUM 3

struct address_ovl_s {
  u8 _00;
  u8 _01;
  u8 command;
  u8 _03;
  u8 _04;
  u8 selected_entry;
  u8 show_museum_address;
  u8 _07;
  u8 page_entry_count[mAD_PAGE_NUM];
  f32 _0C;
  f32 _10;
  f32 _14[mAD_PAGE_NUM];
  f32 _20[mAD_PAGE_NUM];
  Mail_nm_c player_mail_name[PLAYER_NUM + 1]; // last entry is the museum name
  Mail_nm_c animal_mail_name[ANIMAL_NUM_MAX];
  Gfx* display_list; // set to the beginning of the address display list data for drawing over editor etc
};

#ifdef __cplusplus
}
#endif

#endif
