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

typedef struct submenu_s Submenu;

enum {
  mSM_PROCESS_WAIT,
  mSM_PROCESS_PREWAIT,
  mSM_PROCESS_LINKWAIT,
  mSM_PROCESS_PLAY,
  mSM_PROCESS_END,

  mSM_PROCESS_NUM
};

enum {
  mSM_MOVE_OUT_RIGHT,
  mSM_MOVE_IN_RIGHT,
  
  mSM_MOVE_OUT_LEFT,
  mSM_MOVE_IN_LEFT,
  
  mSM_MOVE_OUT_TOP,
  mSM_MOVE_IN_TOP,
  
  mSM_MOVE_OUT_BOTTOM,
  mSM_MOVE_IN_BOTTOM,

  mSM_MOVE_NUM
};

enum submenu_overlay {
  mSM_OVL_NONE,
  
  mSM_OVL_INVENTORY,
  mSM_OVL_HBOARD,
  mSM_OVL_TIMEIN,
  mSM_OVL_LEDIT,
  mSM_OVL_MAP,
  mSM_OVL_NOTICE,
  mSM_OVL_REPAY,
  mSM_OVL_MSCORE,
  mSM_OVL_BIRTHDAY,
  mSM_OVL_EDITOR,
  mSM_OVL_MAILBOX,
  mSM_OVL_BOARD,
  mSM_OVL_ADDRESS,
  mSM_OVL_HANIWA,
  mSM_OVL_EDITENDCHK,
  mSM_OVL_WARNING,
  mSM_OVL_CPMAIL,
  mSM_OVL_CPWARNING,
  mSM_OVL_CPEDIT,
  mSM_OVL_CATALOG,
  mSM_OVL_MUSIC,
  mSM_OVL_BANK,
  mSM_OVL_NEEDLEWORK,
  mSM_OVL_CPORIGINAL,
  mSM_OVL_DESIGN,
  mSM_OVL_GBA,
  mSM_OVL_DIARY,
  mSM_OVL_CALENDAR,
  mSM_OVL_PASSWORDMAKE,
  mSM_OVL_PASSWORDCHK,

  mSM_OVL_NUM
};

typedef struct submenu_item_s {
  mActor_name_t item;
  u8 slot_no;
} Submenu_Item_c;

typedef void (*SUBMENU_PROC)(Submenu*);
typedef void (*SUBMENU_GAME_PROC)(Submenu*, GAME*);

/* sizeof (struct submenu_s) == 0x1B8 */
struct submenu_s {
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
};

extern void mSM_open_submenu(Submenu* submenu, int menu_type, int arg0, int arg1);
extern void load_player(Submenu* submenu);
extern void* mSM_ovlptr_dllcnv(void* vram, Submenu* submenu, int);
extern void mSM_submenu_dt(Submenu*);
extern void mSM_submenu_ovlptr_cleanup(Submenu*);
extern void mSM_submenu_ovlptr_init(GAME_PLAY*);
extern void mSM_submenu_ct(Submenu*);
extern void mSM_submenu_ctrl(GAME_PLAY*);
extern void mSM_submenu_move(Submenu*);
extern void mSM_submenu_draw(Submenu*, GAME_PLAY*);
extern int mSM_CHECK_ALL_FISH_GET();
extern int mSM_CHECK_ALL_INSECT_GET();
extern void mSM_Object_Exchange_keep_new_Menu(GAME_PLAY* play);

#ifdef __cplusplus
}
#endif

#endif
