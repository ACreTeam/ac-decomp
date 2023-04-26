#ifndef M_NPC_H
#define M_NPC_H

#include "types.h"
#include "m_npc_personal_id.h"
#include "libu64/gfxprint.h"
#include "m_actor_type.h"
#include "m_land_h.h"
#include "m_mail.h"
#include "lb_rtc.h"
#include "m_personal_id.h"
#include "m_quest.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mNpc_GET_IDX(npc_id) ((npc_id) & 0x0FFF)
#define mNpc_GET_TYPE(npc_id) ((npc_id) & 0xF000)
#define mNpc_IS_SPECIAL(npc_id) (mNpc_GET_TYPE(npc_id) == 0xD000)

#define ANIMAL_NUM_MAX 15 /* Maximum number of villagers possible in town */
#define ANIMAL_MEMORY_NUM 7
#define ANIMAL_CATCHPHRASE_LEN 10
#define ANIMAL_HP_MAIL_NUM 4
#define ANIMAL_NAME_LEN PLAYER_NAME_LEN

/* sizeof(Anmremail_c) == 0x16 */
typedef struct animal_remail_s {
  lbRTC_ymd_t date; /* date sent */
  u8 name[ANIMAL_NAME_LEN]; /* villager name */
  u8 land_name[LAND_NAME_SIZE]; /* town name */
  struct {
    u8 password_letter:1; /* is mail normal or password */
    u8 looks:7; /* personality */
  } flags;
} Anmremail_c;

/* sizeof(Anmplmail_c) == 0x104 */
typedef struct animal_player_maiL_s {
  /* 0x000 */ u8 font; /* 'font' to use for letter info */
  /* 0x001 */ u8 paper_type; 
  /* 0x002 */ mActor_name_t present;
  /* 0x004 */ u8 header_back_start; /* position for name insertion in header */
  /* 0x005 */ u8 header[MAIL_HEADER_LEN];
  /* 0x01D */ u8 body[MAIL_BODY_LEN];
  /* 0x0DD */ u8 footer[MAIL_FOOTER_LEN];
  /* 0x0FD */ u8 pad0; /* likely pad */
  /* 0x0FE */ lbRTC_ymd_t date; /* sent date */
} Anmplmail_c;

/* sizeof(Anmhome_c) == 5 */
typedef struct animal_home_s {
  /* 0x00 */ u8 type_unused; /* Likely the house type, but seems to be unused outside of SChk_Anmhome_c_sub */
  /* 0x01 */ u8 block_x; /* acre x position */
  /* 0x02 */ u8 block_z; /* acre y position */
  /* 0x03 */ u8 ut_x; /* unit x position */
  /* 0x04 */ u8 ut_z; /* unit z position */
} Anmhome_c;

/* sizeof(Anmlet_c) == 1 */
typedef struct animal_letter_info_s {
  u8 exists:1;   /* letter received by villager and exists */
  u8 password_letter:1;   /* set when the letter contains a 'key' symbol and is considered a password letter */
  u8 send_reply:1;   /* set when the villager should reply */
  u8 has_present_cloth:1;   /* set when the villager's held present shirt is from this letter */
  u8 wearing_present_cloth:1;   /* set when a villager is wearing the shirt sent with the saved letter */
  u8 bit5_7:3; /* seemingly unused */
} Anmlet_c;

/* sizeof(Anmmem_c) == 0x138 */
typedef struct animal_memory_s {
  /* 0x000 */ PersonalID_c memory_player_id; /* personal id of the player memory belongs to */
  /* 0x014 */ lbRTC_time_c last_speak_time; /* time the player last spoke to this villager */
  /* 0x01C */ u8 land_name[LAND_NAME_SIZE]; /* memory origin land name */
  /* 0x024 */ u16 land_id; /* memory origin land id */
  /* 0x028 */ u64 saved_town_tune; /* memory origin town tune */
  /* 0x030 */ s8 friendship; /* friendship with the player */
  /* 0x031 */ Anmlet_c letter_info; /* saved letter flags */
  /* 0x032 */ Anmplmail_c letter; /* saved letter */
} Anmmem_c;

/* sizeof(AnmHPMail_c) == 0x1C */
typedef struct animal_password_mail_s {
  /* 0x00 */ lbRTC_time_c receive_time;
  /* 0x08 */ u8 password[20]; /* TODO: this should not be a hardcoded length */
} AnmHPMail_c;

/* sizeof(Animal_c) == 0x988 */
typedef struct animal_s {
  /* 0x000 */ AnmPersonalID_c id; /* this villager's ID */
  /* 0x010 */ Anmmem_c memories[ANIMAL_MEMORY_NUM]; /* memories of players who've spoken to this villager */
  /* 0x898 */ Anmhome_c home_info; /* home position info */
  /* 0x89D */ u8 catchphrase[ANIMAL_CATCHPHRASE_LEN]; /* may be called 'word_ending' */
  /* 0x8A8 */ mQst_contest_c contest_quest; /* current contest quest information */
  /* 0x8D0 */ u8 parent_name[PLAYER_NAME_LEN]; /* name of the player who 'spawned' the villager in, unsure why this is tracked */
  /* 0x8D8 */ u8 previous_land_name[LAND_NAME_SIZE]; /* name of the last town the villager lived in */
  /* 0x8E0 */ u16 previous_land_id; /* id of the previous town the villager lived in */
  /* 0x8E2 */ u8 mood; /* probably called 'feel' based on code */
  /* 0x8E3 */ u8 mood_time; /* probably called 'feel_tim' based on code */
  /* 0x8E4 */ mActor_name_t cloth; /* shirt the villager is wearing */
  /* 0x8E6 */ u16 remove_info; /* info about villager moving between towns? kinda stubbed */
  /* 0x8E8 */ u8 is_home; /* TRUE when the villager is home, otherwise FALSE */
  /* 0x8E9 */ u8 moved_in; /* TRUE when the villager moved in after town creation, FALSE if they started out in town */
  /* 0x8EA */ u8 removing; /* TRUE when the villager is leaving town, FALSE otherwise */
  /* 0x8EB */ s8 cloth_original_id; /* 0xFF when not wearing an Able Sister's pattern, otherwise 0-3 indicating which pattern */
  /* 0x8EC */ s8 umbrella_id; /* 0xFF when no umbrella, 0-31 when a standard umbrella, 32-35 when using an Able Sister's pattern */
  /* 0x8EE */ mActor_name_t present_cloth; /* The most recently received shirt from a letter which the villager may change into */
  /* 0x8F0 */ u8 animal_relations[ANIMAL_NUM_MAX]; /* relationships between all villagers in town, starts at 128 which is neutral */
  /* 0x900 */ AnmHPMail_c hp_mail[ANIMAL_HP_MAIL_NUM]; /* mail password info storage */
  /* 0x000 */ u8 unused[24]; /* unknown usage/unused */
} Animal_c;

/*
  Struct for keeping track of an event where a villager can briefly return to your town after
  moving away to another town. The time limit seems to be 60 days, and the villager will only
  appear once per player during that time if the player talks to them.
*/

/* sizeof(Anmret_c) == 0xC */
typedef struct animal_return_s {
  /* 0x00 */ mActor_name_t npc_id; /* id of the villager who left */
  /* 0x02 */ u8 talk_bit; /* which players have already interacted with this villager */
  /* 0x03 */ u8 exist; /* if the villager exists */
  /* 0x04 */ lbRTC_time_c renew_time; /* time that this struct was updated */
} Anmret_c;

extern void mNpc_PrintRemoveInfo(gfxprint_t* gfxprint);
extern void mNpc_PrintFriendship_fdebug(gfxprint_t* gfxprint);

#ifdef __cplusplus
}
#endif

#endif
