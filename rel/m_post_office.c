#include "m_post_office.h"

#include "m_mail.h"
#include "m_npc.h"
#include "m_handbill.h"
#include "m_museum.h"
#include "m_name_table.h"
#include "m_item_name.h"
#include "m_private.h"
#include "m_string.h"
#include "m_house.h"
#include "m_event.h"
#include "m_field_info.h"
#include "m_play.h"
#include "libultra/libultra.h"
#include "m_common_data.h"

static int mPO_keep_contents(Mail_c* mail) {
  int res = FALSE;

  int free_idx = mMl_chk_mail_free_space(Save_Get(post_office).mail, mPO_MAIL_STORAGE_SIZE);
  if (free_idx >= 0) {
    mMl_copy_mail(Save_Get(post_office).mail + free_idx, mail);
    mMl_clear_mail(mail);
    res = TRUE;
  }

  return res;
}

extern int mPO_count_mail(int house_no) {
  int used = mMl_count_use_mail_space(Save_Get(homes[house_no]).mailbox, HOME_MAILBOX_SIZE);
  Mail_c* mail = Save_Get(post_office).mail;
  int i;

  for (i = 0; i < mPO_MAIL_STORAGE_SIZE; i++) {
    if (house_no == mMl_hunt_for_send_address(mail)) {
      used++;
    }
    
    mail++;
  }

  return used;
}

extern int mPO_get_keep_mail_sum() {
  PostOffice_c* post_office = Save_GetPointer(post_office);

  return post_office->keep_mail_sum_players + post_office->keep_mail_sum_npcs;
}

static void mPO_adjust_keep_mail() {
  Mail_c* mail = Save_Get(post_office).mail;
  int i;
  s16 recipient_flags = 0;
  s16 keep_mail_player_num = 0;

  for (i = 0; i < mPO_MAIL_STORAGE_SIZE; i++) {
    if (mMl_check_not_used_mail(mail) == FALSE) {
      int house_idx = mMl_hunt_for_send_address(mail);
      if (house_idx != -1) {
        keep_mail_player_num++;
        recipient_flags |= (1 << house_idx);
      }
      else {
        mMl_clear_mail(mail);
      }
    }
    mail++;
  }

  Save_Set(post_office.mail_recipient_flags, recipient_flags);
  Save_Set(post_office.keep_mail_sum_players, keep_mail_player_num);
  Save_Set(post_office.keep_mail_sum_npcs, 0);
}

static int mPO_receipt_check_mail(Mail_c* mail) {
  int res = FALSE;

  switch (mail->header.recipient.type) {
    case mMl_NAME_TYPE_PLAYER:
    {
      int house_idx = mMl_hunt_for_send_address(mail);
      if (house_idx != -1 && mPO_count_mail(house_idx) < HOME_MAILBOX_SIZE) {
        res = mPO_keep_contents(mail);
        if (res == TRUE) {
          Save_Get(post_office.mail_recipient_flags) |= (1 << house_idx);
          Save_Get(post_office.keep_mail_sum_players)++;
        }
      }

      break;
    }

    case mMl_NAME_TYPE_NPC:
    {
      if (mNpc_ReceiveHPMail(mail) == FALSE) {
        mNpc_SendMailtoNpc(mail);
      }

      res = mPO_keep_contents(mail);
      if (res == TRUE) {
        Save_Get(post_office).keep_mail_sum_npcs++;
      }

      break;
    }

    case mMl_NAME_TYPE_MUSEUM:
    {
      mMsm_SendMuseumMail(mail);
      mMl_clear_mail(mail);
      
      Save_Get(post_office).keep_mail_sum_npcs++;
      res = TRUE;

      break;
    }
  }

  return res;
}

extern int mPO_receipt_proc(Mail_c* mail, int send_type) {
  int res = FALSE;

  switch (send_type) {
    case mPO_SENDTYPE_MAIL:
    {
      res = mPO_receipt_check_mail(mail);
      break;
    }

    case mPO_SENDTYPE_LEAFLET:
    {
      mMl_copy_mail(&Save_Get(post_office).leaflet, mail);
      Save_Set(post_office.leaflet_recipient_flags.leaflet_flags, 0);
      res = TRUE;
      break;
    }

    case mPO_SENDTYPE_EVENT_LEAFLET:
    {
      mMl_copy_mail(&Save_Get(post_office).event_leaflet, mail);
      Save_Set(post_office.leaflet_recipient_flags.event_flags, 0);
      res = TRUE;
      break;
    }
  }

  return res;
}

static int mPO_copy_contents(int house_no, Mail_c* mail) {
  int res = FALSE;
  int free_slot = mMl_chk_mail_free_space(Save_Get(homes[house_no]).mailbox, HOME_MAILBOX_SIZE);

  if (free_slot >= 0) {
    mMl_copy_mail(Save_Get(homes[house_no]).mailbox + free_slot, mail);
    res = TRUE;
  }

  return res;
}

static void mPO_delivery_mail_with_item(Mail_c* mail, int mail_no, mActor_name_t present, PersonalID_c* pid) {
  int header_back_start;

  mHandbill_Load_HandbillFromRom(mail->content.header, &header_back_start, mail->content.footer, mail->content.body, mail_no);
  
  mail->content.font = mMl_FONT_0;
  mail->content.header_back_start = header_back_start;
  mail->content.mail_type = 7;
  mail->content.paper_type = ITM_PAPER55;
  mail->present = present;

  mMl_set_to_plname(mail, pid);
}

static int mPO_delivery_mail_with_order_ftr_sub(int house_no, PersonalID_c* pid, mPr_catalog_order_c* order) {
  Mail_c mail;
  u8 item_name[mIN_ITEM_NAME_LEN];

  mMl_clear_mail(&mail);
  mIN_copy_name_str(item_name, order->item);
  mHandbill_Set_free_str(0, item_name, mIN_ITEM_NAME_LEN);
  mPO_delivery_mail_with_item(&mail, 0x049 + order->shop_level, order->item, pid);
  return mPO_copy_contents(house_no, &mail);
}

static void mPO_delivery_mail_with_order_ftr(int house_no, int player_no) {
  Private_c* priv = Save_GetPointer(private[player_no]);

  if (priv->exists == TRUE) {
    mPr_catalog_order_c* order = priv->catalog_orders;
    int i;

    for (i = 0; i < mPr_CATALOG_ORDER_NUM; i++) {
      if (order->item != EMPTY_NO) {
        if (mPO_delivery_mail_with_order_ftr_sub(house_no, &priv->player_ID, order) == FALSE) {
          return;
        }

        order->item = EMPTY_NO;
      }

      order++;
    }
  }
}

static void mPO_delivery_mail_with_ticket_set_free_str(lbRTC_month_t month) {
  u8 month_str[9];
  u8 day_str[4];

  int days = lbRTC_GetDaysByMonth(Common_Get(time.rtc_time.year), month);
  mString_Load_MonthStringFromRom(month_str, month);
  mString_Load_DayStringFromRom(day_str, days);
  mHandbill_Set_free_str(4, month_str, 9);
  mHandbill_Set_free_str(5, day_str, 4);
}

static int mPO_delivery_mail_with_ticket_sub(int house_no, PersonalID_c* pid, mActor_name_t present) {
  Mail_c mail;

  mMl_clear_mail(&mail);
  mPO_delivery_mail_with_item(&mail, 0x057, present, pid);
  return mPO_copy_contents(house_no, &mail);
}

static void mPO_delivery_mail_with_ticket(int house_no, int player_no) {
  mActor_name_t ticket;
  Private_c* priv = Save_GetPointer(private[player_no]);

  if (priv->exists == TRUE) {
    int ticket_num = priv->inventory.lotto_ticket_mail_storage;

    if (ticket_num != 0) {
      int minus_ticket;
      mActor_name_t ticket_id;
      lbRTC_month_t ticket_month = priv->inventory.lotto_ticket_expiry_month;
      
      mPO_delivery_mail_with_ticket_set_free_str(ticket_month);
      ticket = ITM_TICKET_START + (ticket_month - 1) * 8;

      for (ticket_num; ticket_num != 0; ticket_num -= minus_ticket) {
        minus_ticket = ticket_num < 5 ? ticket_num : 5;
        ticket_id = ticket + minus_ticket - 1;
        if (mPO_delivery_mail_with_ticket_sub(house_no, &priv->player_ID, ticket_id) == FALSE) {
          break;
        }
      }
    }

    priv->inventory.lotto_ticket_mail_storage = ticket_num;
  }
}

static int mPO_delivery_mail_sub(int house_no) {
  PostOffice_c* post_office;
  Mail_c* po_mail;
  int i;
  int res = TRUE;

  po_mail = Save_Get(post_office).mail;
  post_office = Save_GetPointer(post_office);

  for (i = 0; i < mPO_MAIL_STORAGE_SIZE; i++, po_mail++) {
    if (mMl_check_not_used_mail(po_mail) == FALSE) {
      int dst_house_no = mMl_hunt_for_send_address(po_mail);
      if (dst_house_no != -1) {
        if (house_no == mPO_DELIVER_ALL_HOUSES || dst_house_no == house_no) {
          if (mPO_copy_contents(dst_house_no, po_mail) == TRUE) {
            post_office->keep_mail_sum_players--;
            mMl_clear_mail(po_mail);
          }
          else {
            res = FALSE; // failed to deliver the mail, house mailbox is likely full
          }
        }
      }
      else {
        switch (po_mail->header.recipient.type) {
          case mMl_NAME_TYPE_PLAYER:
            post_office->keep_mail_sum_players--;
            break;
        }

        mMl_clear_mail(po_mail);
      }
    }
  }

  Save_Set(post_office.keep_mail_sum_npcs, 0);
  return res;
}

static void mPO_delivery_one_address_mail(int house_no) {
  if (mPO_delivery_mail_sub(house_no) == TRUE) {
    s16 mask = (1 << house_no) ^ 0b1111;
    Save_Get(post_office.mail_recipient_flags) &= mask; // clear out delivered houses
  }
}

static void mPO_delivery_one_address_special_mail(int house_no) {
  int player_no = mHS_get_pl_no(house_no);

  mPO_delivery_mail_with_ticket(house_no, player_no);
  mPO_delivery_mail_with_order_ftr(house_no, player_no);
}

static void mPO_delivery_one_address_leaflet(s16* leaflet_received_flags, Mail_c* leaflet, int house_no) {
  if ((((*leaflet_received_flags) >> house_no) & 1) == FALSE) {
    mHm_hs_c* house = Save_GetPointer(homes[house_no]);

    if (house->ownerID.land_id == 0xFFFF) {
      *leaflet_received_flags |= (1 << house_no); // unclaimed houses are marked "received"
    }
    else {
      int player_no = mHS_get_pl_no(house_no);
      if (player_no < mPr_FOREIGNER && mEv_ArbeitPlayer(player_no) == FALSE) {
        mMl_set_to_plname(leaflet, &house->ownerID);
        if (mPO_copy_contents(house_no, leaflet) == TRUE) {
          *leaflet_received_flags |= (1 << house_no);
        }
      }
    }
  }
}

static void mPO_delivery_one_address_event_leaflet(int house_no) {
  Mail_c* ev_leaflet = &Save_Get(post_office).event_leaflet;
  int special_type = mEv_get_special_event_type();
  int leaflet_event_type;

  switch (ev_leaflet->content.mail_type) {
    case mMl_TYPE_SHOP_SALE_LEAFLET:
      leaflet_event_type = mEv_EVENT_SHOP_SALE;
      break;

    case mMl_TYPE_BROKER_SALE_LEAFLET:
      leaflet_event_type = mEv_EVENT_BROKER_SALE;
      break;

    default:
      leaflet_event_type = -1;
      break;
  }

  if (leaflet_event_type == special_type) {
    mPO_delivery_one_address_leaflet(&Save_Get(post_office).leaflet_recipient_flags.event_flags, ev_leaflet, house_no);
  }
}

extern int mPO_delivery_one_address(int house_no) {
  mPO_delivery_one_address_mail(house_no);
  mPO_delivery_one_address_leaflet(&Save_Get(post_office).leaflet_recipient_flags.leaflet_flags, &Save_Get(post_office).leaflet, house_no);
  mPO_delivery_one_address_event_leaflet(house_no);
}

static void mPO_delivery_mail() {
  mPO_delivery_mail_sub(mPO_DELIVER_ALL_HOUSES);
  mPO_adjust_keep_mail();
}

static void mPO_delivery_leaflet() {
  int house_no;

  for (house_no = 0; house_no < mHS_HOUSE_NUM; house_no++) {
    mPO_delivery_one_address_leaflet(&Save_Get(post_office).leaflet_recipient_flags.leaflet_flags, &Save_Get(post_office).leaflet, house_no);
    mPO_delivery_one_address_event_leaflet(house_no);
  }
}

extern void mPO_delivery_all_address_proc() {
  mPO_delivery_mail();
  mPO_delivery_leaflet();
}

static int mPO_make_post_man(GAME_PLAY* play) {
  static int bx_add[2] = { -1, 1 };
  static int ux_table[2] = { UT_X_NUM - 1, 0 };

  int pl_block_x;
  int pl_block_z;
  u32 block_kind;

  int po_block_x;
  int po_block_z;
  int res = FALSE;

  if (Save_Get(scene_no) == SCENE_FG) {
    mFI_BlockKind2BkNum(&pl_block_x, &pl_block_z, mRF_BLOCKKIND_PLAYER);
    block_kind = mFI_BkNum2BlockKind(play->block_table.block_x, play->block_table.block_z);

    if (block_kind != mRF_BLOCKKIND_NONE) {
      if ((block_kind & mRF_BLOCKKIND_PLAYER) != 0) {
        int bx_add_idx;
        int spawned_postman;

        mFI_BlockKind2BkNum(&po_block_x, &po_block_z, mRF_BLOCKKIND_POSTOFFICE);
        bx_add_idx = pl_block_x >= po_block_x ? 0 : 1;
        spawned_postman = (*Common_Get(clip).npc_clip->setupActor_proc)(play, SP_NPC_POST_MAN, -1, -1, 0, play->block_table.block_x + bx_add[bx_add_idx], play->block_table.block_z, ux_table[bx_add_idx], 7);

        if (spawned_postman == TRUE) {
          res = TRUE;
        }
      }
      else if ((block_kind & mRF_BLOCKKIND_POSTOFFICE) != 0) {
        if (Common_Get(force_mail_delivery_flag) == TRUE) {
          int post_utx;
          int post_utz;
          int spawned_postman;
          ACTOR* post_office_structure = Actor_info_fgName_search(&play->actor_info, POST_OFFICE, ACTOR_PART_ITEM);

          if (post_office_structure != NULL) {
            mFI_Wpos2UtNum_inBlock(&post_utx, &post_utz, post_office_structure->world.position);
            spawned_postman = (*Common_Get(clip).npc_clip->setupActor_proc)(play, SP_NPC_POST_MAN, -1, -1, 1, play->block_table.block_x, play->block_table.block_z, post_utx - 3, post_utz);

            if (spawned_postman == TRUE) {
              res = TRUE;
            }
          }
        }
      }
      else {
        mPO_delivery_all_address_proc();
        res = TRUE;
      }
    }
    else {
      mPO_delivery_all_address_proc();
      res = TRUE;
    }
  }
  else {
    mPO_delivery_all_address_proc();
    res = TRUE;
  }

  return res;
}

static void mPO_set_next_delivery_time(lbRTC_time_c* time) {
  if (time->hour < 9) {
    time->hour = 9;
  }
  else if (time->hour < 17) {
    time->hour = 17;
  }
  else {
    lbRTC_Add_DD(time, 1);
    time->hour = 9;
  }

  time->min = 0;
  time->sec = 0;
  lbRTC_TimeCopy(&Save_Get(post_office).delivery_time, time);
}

static void mPO_delivery_proc(GAME_PLAY* play) {
  lbRTC_time_c time;

  lbRTC_TimeCopy(&time, Common_GetPointer(time.rtc_time));

  if ((lbRTC_IsOverTime(&Save_Get(post_office).delivery_time, &time) == lbRTC_OVER || Common_Get(force_mail_delivery_flag) == TRUE) &&
      (mPO_make_post_man(play) == TRUE)
  ) {
    mPO_set_next_delivery_time(&time);
    Common_Set(force_mail_delivery_flag, FALSE);
  }
}

static void mPO_first_delivery_proc() {
  int deliver = FALSE;
  lbRTC_time_c time;

  lbRTC_TimeCopy(&time, Common_GetPointer(time.rtc_time));

  if (lbRTC_IsOverTime(&Save_Get(post_office).delivery_time, &time) == lbRTC_OVER || Common_Get(force_mail_delivery_flag) == TRUE) {
    deliver = TRUE;
    mPO_set_next_delivery_time(&time);
    Common_Set(force_mail_delivery_flag, FALSE);
  }

  if (deliver == TRUE) {
    mPO_delivery_mail();
  }

  if (mLd_PlayerManKindCheck() == FALSE) {
    int house_no = mHS_get_arrange_idx(Common_Get(player_no));
    mPO_delivery_one_address_special_mail(house_no);
  }

  if (deliver == TRUE) {
    mPO_delivery_leaflet();
  }
}

extern void mPO_business_proc(GAME_PLAY* play) {
  if ((Common_Get(clip).demo_clip == NULL && Common_Get(clip).demo_clip2 == NULL) ||
      (Common_Get(clip).demo_clip != NULL && Common_Get(clip).demo_clip->type == mDemo_CLIP_TYPE_INTRO_DEMO)
  ) {
    int scene = Save_Get(scene_no);

    switch (scene) {
      default:
        mPO_delivery_proc(play);
        break;

      case SCENE_PLAYERSELECT:
      case SCENE_PLAYERSELECT_2:
      case SCENE_PLAYERSELECT_3:
      case SCENE_PLAYERSELECT_SAVE:
      case SCENE_TITLE_DEMO:
        return;
    }
  }
}

extern void mPO_first_work() {
  lbRTC_time_c* time = &Save_Get(save_check).time;
  if (mTM_AreTimesEqual(time, &mTM_rtcTime_clear_code) == FALSE && lbRTC_IsOverRTC(time) == FALSE) {
    Common_Set(force_mail_delivery_flag, TRUE);
  }

  mPO_first_delivery_proc();
  mPO_adjust_keep_mail();
}

extern void mPO_post_office_init() {
  bzero(Save_GetPointer(post_office), sizeof(PostOffice_c));
  mMl_clear_mail_box(Save_Get(post_office).mail, mPO_MAIL_STORAGE_SIZE);
  mMl_clear_mail(&Save_Get(post_office).leaflet);
  mMl_clear_mail(&Save_Get(post_office).event_leaflet);
  Save_Get(post_office).leaflet_recipient_flags.raw = 0x000F000F;
  lbRTC_TimeCopy(&Save_Get(post_office).delivery_time, Common_GetPointer(time.rtc_time));
}
