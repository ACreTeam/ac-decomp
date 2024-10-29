#include "m_bg_item.h"

#include "m_common_data.h"
#include "m_name_table.h"

static BI_PROC mBI_make_proc;

static ACTOR* mBI_search_bg_item(Actor_info* info) {
  static const s16 name_data[] = {
    mAc_PROFILE_BGCHERRYITEM,
    mAc_PROFILE_BGITEM,
    mAc_PROFILE_BGWINTERITEM,
    mAc_PROFILE_BGXMASITEM
  };
  
  ACTOR* actor;
  int i;

  for (i = 0; i < 4; i++) {
    actor = Actor_info_name_search(info,name_data[i], ACTOR_PART_ITEM);
    if (actor != NULL) {
      break;
    }
  }

  return actor;
}

static void mBI_make_bg_item(GAME_PLAY* play) {
  if (mBI_search_bg_item(&play->actor_info) == NULL) {
    Actor_info_make_actor(
      &play->actor_info,
      &play->game,
      Common_Get(bg_item_profile),
      0.0f, 0.0f, 0.0f,
      0, 0, 0,
      -1, -1,
      -1,
      EMPTY_NO,
      -1,
      -1,
      -1
    );
    
    mBI_make_proc = NULL;
  }
}

extern void mBI_change_bg_item(GAME_PLAY* play) {
  ACTOR* actor = mBI_search_bg_item(&play->actor_info);
  
  if (actor != NULL) {
    Actor_delete(actor);
    mBI_make_proc = mBI_make_bg_item;
    Common_Set(bg_item_profile, Common_Get(time.bgitem_profile));
  }
}

extern void mBI_ct() {
  mBI_make_proc = NULL;
}

extern void mBI_move(GAME_PLAY* play) {
  if (mBI_make_proc != NULL) {
    (*mBI_make_proc)(play);
  }
}
