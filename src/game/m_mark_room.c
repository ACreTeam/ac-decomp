#include "m_mark_room.h"

#include "m_house.h"
#include "m_common_data.h"
#include "m_scene_table.h"
#include "m_handbill.h"

static int mMkRm_GetMarkOrder(int player_no) {
  if (mEv_CheckArbeit() == FALSE && player_no < PLAYER_NUM) {
    int arrange_idx = mHS_get_arrange_idx(player_no);
    mHm_hs_c* house = Save_GetPointer(homes[arrange_idx]);
    lbRTC_time_c now_time = Common_Get(time.rtc_time);

    lbRTC_year_t year = Save_Get(homes[arrange_idx]).hra_mark_time.year;
    lbRTC_month_t month = Save_Get(homes[arrange_idx]).hra_mark_time.month;
    lbRTC_day_t day = Save_Get(homes[arrange_idx]).hra_mark_time.day;

    if (
      year != now_time.year ||
      month != now_time.month ||
      day != now_time.day
    ) {
      return TRUE;
    }
  }

  return FALSE;
}

static void mMkRm_ReportMarkEnd(int player_no) {
  if (player_no < PLAYER_NUM) {
    int arrange_idx = mHS_get_arrange_idx(player_no);
    lbRTC_time_c now_time = Common_Get(time.rtc_time);

    Save_Get(homes[arrange_idx]).hra_mark_time.year = now_time.year;
    Save_Get(homes[arrange_idx]).hra_mark_time.month = now_time.month;
    Save_Get(homes[arrange_idx]).hra_mark_time.day = now_time.day;
    Save_Get(homes[arrange_idx]).flags.house_updated = FALSE;
  }
}

extern void mMkRm_ReportChangePlayerRoom() {
  int player_no = Common_Get(player_no);

  if (Save_Get(scene_no) == SCENE_COTTAGE_MY || mSc_IS_SCENE_BASEMENT(Save_Get(scene_no))) {
    return;
  }
      
  if (player_no < PLAYER_NUM) {
    int arrange_idx = mHS_get_arrange_idx(player_no);
    mActor_name_t field_id = mFI_GetFieldId();
      
    if (mFI_GET_TYPE(field_id) == mFI_FIELD_PLAYER0_ROOM && (mActor_name_t)(field_id - mFI_FIELD_PLAYER0_ROOM) == arrange_idx) {
      lbRTC_time_c now_time = Common_Get(time.rtc_time);

      Save_Get(homes[arrange_idx]).flags.house_updated = TRUE;
      Save_Get(homes[arrange_idx]).hra_mark_time.year = now_time.year;
      Save_Get(homes[arrange_idx]).hra_mark_time.month = now_time.month;
      Save_Get(homes[arrange_idx]).hra_mark_time.day = now_time.day;
    }
  }
}

static int mMkRm_NoMarkLetter(int arrange_idx, int handbill_no) {
  int free_idx = mMl_chk_mail_free_space(Save_Get(homes[arrange_idx]).mailbox, HOME_MAILBOX_SIZE);

  if (free_idx >= 0) {
    Mail_c mail;
    int header_back_start;

    mMl_clear_mail(&mail);
    mHandbill_Load_HandbillFromRom(mail.content.header, &header_back_start, mail.content.footer, mail.content.body, handbill_no);
    mail.content.font = mMl_FONT_RECV;
    mail.content.header_back_start = header_back_start;
    mail.content.mail_type = mMl_TYPE_HRA;
    mail.content.paper_type = 51; /* wing paper */
    mMl_set_to_plname(&mail, &Common_Get(now_private)->player_ID);
    mMl_copy_mail(Save_Get(homes[arrange_idx]).mailbox + free_idx, &mail);

    return TRUE;
  }

  return FALSE;
}

static void mMkRm_NoMarkLetter_Hint(int arrange_idx, int player_no) {
  u32* hint_info_bitfield = &Save_Get(homes[arrange_idx]).hra_mark_info;
  int free_hint_num = 0;
  int i;

  #ifndef IMPROVEMENTS
  u32 all_mark = 0;
  for (i = 0; i < mMkRm_HINT_NUM; i++) {
    all_mark |= (1 << i); // ???
  }
  #else
  u32 all_mark = (1 << mMkRm_HINT_NUM) - 1; // lol
  #endif


  if (hint_info_bitfield[0] == all_mark) {
    hint_info_bitfield[0] = 0; // clear all hints
    free_hint_num = mMkRm_HINT_NUM;
  }
  else {
    for (i = 0; i < mMkRm_HINT_NUM; i++) {
      if (((hint_info_bitfield[0] >> i) & 1) == 0) {
        free_hint_num++;
      }
    }
  }

  if (free_hint_num != 0) {
    int selected_hint = RANDOM(free_hint_num);
    int n = 0;

    for (i = 0; i < mMkRm_HINT_NUM; i++) {
      if (((hint_info_bitfield[0] >> i) & 1) == 0) {
        if (n == selected_hint) {
          if (mMkRm_NoMarkLetter(arrange_idx, 0x1DC + i)) {
            hint_info_bitfield[0] |= (1 << i);
            mMkRm_ReportMarkEnd(player_no);
          }

          break;
        }
        else {
          n++;
        }
      }
    }
  }
}

extern void mMkRm_MarkRoom(GAME* game) {
  int player_no = Common_Get(player_no);
  int arrange_idx = 0;
  int i;

  if (player_no < PLAYER_NUM) {
    if (mEv_CheckArbeit() == FALSE) {
      mHm_flg_c* flags;

      arrange_idx = mHS_get_arrange_idx(player_no);
      flags = &Save_Get(homes[arrange_idx]).flags;

      if (flags->hra_member == FALSE) {
        /* Send welcome letter & save HRA member status */
        if (mMkRm_NoMarkLetter(arrange_idx, 0x1EF)) {
          flags->hra_member = TRUE;
          mMkRm_ReportMarkEnd(player_no);

          return;
        }

        return;
      }
    }

    if (mMkRm_GetMarkOrder(player_no)) {
      if (Save_Get(homes[arrange_idx]).flags.house_updated == TRUE) {
        mMkRm_MarkRoomOvl(player_no);
        mMkRm_ReportMarkEnd(player_no);
      }
      else {
        int rng = RANDOM(10);

        if (rng == 5 || rng == 9) {
          mMkRm_NoMarkLetter_Hint(arrange_idx, player_no);
          mMkRm_ReportMarkEnd(player_no);
        }
      }
    }
  }
}
