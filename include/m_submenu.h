#ifndef M_SUBMENU_H
#define M_SUBMENU_H

#include "types.h"
#include "m_actor_type.h"
#include "m_submenu_ovl_h.h"
#include "game_h.h"
#include "m_mail.h"
#include "m_private.h"

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

typedef struct submenu_item_s {
  mActor_name_t item;
  u8 slot_no;
} Submenu_Item_c;

typedef void (*SUBMENU_PROC)(Submenu*);
typedef void (*SUBMENU_GAME_PROC)(Submenu*, GAME*);

/* sizeof (Submenu) == 0x1B8 */
typedef struct submenu_s {
  /* 0x000 */ int mode;
  /* 0x004 */ int menu_type;
  /* 0x008 */ int current_menu_type;

  /* 0x00C */ int process_status;

  /* 0x010 */ int param0;
  /* 0x014 */ int param1;
  /* 0x018 */ void* param2;
  /* 0x01C */ int param3;

  /* 0x020 */ int wait_timer;

  /* 0x024 */ char* overlay_address;
  /* 0x028 */ char* next_overlay_address;
  /* 0x02C */ Submenu_Overlay_c* overlay;
  /* 0x030 */ SUBMENU_PROC move_proc;
  /* 0x034 */ SUBMENU_GAME_PROC draw_proc;

  /* 0x038 */ Mail_c mail; /* selected mail */
  /* 0x162 */ u8 flag; // only set to 0 or 1, checked at least once in aQMgr_actor_move_talk_sub_hand_item_wait
  /* 0x163 */ u8 after_mode; /* relates to code which runs after the submenu process */
  /* 0x164 */ u8 unk_164; // only set to 0 in mSM_move_LINKWait in AC
  /* 0x165 */ u8 disable_start_btn_flag; /* when set to TRUE, the START button input will be ignored */
  /* 0x166 */ u8 disable_start_btn_timer; /* timer for when to disable the start button ignore flag */
  /* 0x168 */ xyz_t water_pos; /* calculated to the nearest water position to the player for releasing fish */ 
  /* 0x174 */ Submenu_Item_c* item_p; /* pointer to a 'Submenu_Item_c' array, seemingly only points to Submenu::items */
  /* 0x178 */ s16 item_num; /* number of items in the item array */
  /* 0x17A */ s16 selected_item_num; /* number of selected items in the item array */
  /* 0x17C */ Submenu_Item_c items[mPr_POCKETS_SLOT_COUNT]; /* item buffer, entries are only set when an item is selected by the player */
} Submenu;

#ifdef __cplusplus
}
#endif

#endif
