#include "m_music_ovl.h"

static void mMU_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu) {
  (*submenu->overlay->move_Move_proc)(submenu, menu);
}
