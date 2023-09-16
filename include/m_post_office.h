#ifndef M_POST_OFFICE_H
#define M_POST_OFFICE_H

#include "types.h"
#include "m_mail.h"
#include "lb_rtc.h"
#include "m_play_h.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mPO_MAIL_STORAGE_SIZE 5
#define mPO_DELIVER_ALL_HOUSES -1

#define mPO_KEEP_MAIL_PLAYERS_MAX 10

enum {
  mPO_SENDTYPE_MAIL,
  mPO_SENDTYPE_LEAFLET,
  mPO_SENDTYPE_EVENT_LEAFLET,

  mPO_SENDTYPE_NUM
};

/* sizeof(PostOffice_c) == 0x83C */
typedef struct post_office_s {
  /* 0x000 */ s16 keep_mail_sum_players; /* sum of stored mail from players, see mPO_get_keep_mail_sum */
  /* 0x002 */ s16 keep_mail_sum_npcs; /* sum of stored mail from NPCs, see mPO_get_keep_mail_sum */
  /* 0x004 */ s16 mail_recipient_flags; /* flags to keep track of which players will receive mail */
  /* 0x006 */ u16 unused_6; /* definitely here, as Mail_c has 2 byte alignment */
  /* 0x008 */ Mail_c mail[mPO_MAIL_STORAGE_SIZE];
  /* 0x5DA */ Mail_c leaflet;
  /* 0x704 */ Mail_c event_leaflet;

  /* certainly a union based on code usage */
  /* 0x830 */ union {
    /* 0x830 */ int raw; /* used in mPO_post_office_init */
    struct {
      /* 0x830 */ s16 leaflet_flags; /* bitfield of players who will receive the current 'leaflet' */
      /* 0x832 */ s16 event_flags; /* bitfield of players who will receive the current 'event leaflet' */
    };
  } leaflet_recipient_flags; /* similar to mail_recipient_flags, just for 'leaflets' */

  /* 0x834 */ lbRTC_time_c delivery_time; /* time when Pete should 'deliver' the mail */
} PostOffice_c;

extern int mPO_count_mail(int house_no);
extern int mPO_get_keep_mail_sum();
extern int mPO_receipt_proc(Mail_c* mail, int send_type);
extern int mPO_delivery_one_address(int house_no);
extern void mPO_delivery_all_address_proc();
extern void mPO_business_proc(GAME_PLAY* play);
extern void mPO_first_work();
extern void mPO_post_office_init();

#ifdef __cplusplus
}
#endif

#endif
