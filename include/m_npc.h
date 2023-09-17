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
#include "m_lib.h"
#include "m_private_h.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mNpc_GET_IDX(npc_id) ((npc_id) & 0x0FFF)
#define mNpc_GET_TYPE(npc_id) ((npc_id) & 0xF000)
#define mNpc_IS_SPECIAL(npc_id) (mNpc_GET_TYPE(npc_id) == 0xD000)

#define NPC_NUM 236

#define ANIMAL_NUM_MAX 15 /* Maximum number of villagers possible in town */
#define ANIMAL_MEMORY_NUM 7
#define ANIMAL_CATCHPHRASE_LEN 10
#define ANIMAL_HP_MAIL_NUM 4
#define ANIMAL_NAME_LEN PLAYER_NAME_LEN

#define mNpc_ISLAND_FTR_SAVE_NUM 4

enum {
  mNpc_MOOD_0,
  mNpc_MOOD_1,
  mNpc_MOOD_2,
  mNpc_MOOD_3,
  mNpc_MOOD_4,
  mNpc_MOOD_5,
  mNpc_MOOD_6,
  mNpc_MOOD_7,
  mNpc_MOOD_8,

  mNpc_MOOD_NUM
};

/* sizeof(Anmremail_c) == 0x16 */
typedef struct animal_remail_s {
  lbRTC_ymd_c date; /* date sent */
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
  /* 0x0FE */ lbRTC_ymd_c date; /* sent date */
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

/* sizeof(Anmlnd_c) == 0xA */
typedef struct animal_land_mem_s {
  /* 0x00 */ u8 name[LAND_NAME_SIZE];
  /* 0x08 */ u16 id;
} Anmlnd_c;

/* sizeof(memuni_U) == 0x12 */
typedef union {
  Anmlnd_c land; /* size = 0xA */
  u32 check; /* size = 4 */
} memuni_u;

/* sizeof(Anmmem_c) == 0x138 */
typedef struct animal_memory_s {
  /* 0x000 */ PersonalID_c memory_player_id; /* personal id of the player memory belongs to */
  /* 0x014 */ lbRTC_time_c last_speak_time; /* time the player last spoke to this villager */
  /* 0x01C */ memuni_u memuni; /* union between town NPC land memory & islander player action memory */
  /* 0x028 */ u64 saved_town_tune; /* memory origin town tune */
  /* 0x030 */ s8 friendship; /* friendship with the player */
  /* 0x031 */ Anmlet_c letter_info; /* saved letter flags */
  /* 0x032 */ Anmplmail_c letter; /* saved letter */
} Anmmem_c;

/* sizeof(anmuni) == 8 */
typedef union {
  u8 previous_land_name[LAND_NAME_SIZE];
  mActor_name_t island_ftr[mNpc_ISLAND_FTR_SAVE_NUM];
} anmuni_u;

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
  /* 0x8D8 */ anmuni_u anmuni; /* name of the last town the villager lived in or saved island ftr */
  /* 0x8E0 */ u16 previous_land_id; /* id of the previous town the villager lived in */
  /* 0x8E2 */ u8 mood; /* probably called 'feel' based on code */
  /* 0x8E3 */ u8 mood_time; /* probably called 'feel_tim' based on code */
  /* 0x8E4 */ mActor_name_t cloth; /* shirt the villager is wearing */
  /* 0x8E6 */ u16 remove_info; /* info about villager moving between towns? kinda stubbed */
  /* 0x8E8 */ u8 is_home; /* TRUE when the villager is home, otherwise FALSE */
  /* 0x8E9 */ u8 moved_in; /* TRUE when the villager moved in after town creation, FALSE if they started out in town */
  /* 0x8EA */ u8 removing; /* TRUE when the villager is leaving town, FALSE otherwise */
  /* 0x8EB */ s8 cloth_original_id; /* 0xFF when not wearing an Able Sister's pattern, otherwise 0-3 indicating which pattern */
  /* 0x8EC */ s8 umbrella_id; /* 0xFF when no umbrella, 0-31 when a standard umbrella, 32-35 when using an Able Sister's pattern
  /* 0x8ED */ u8 unk_8ED; /* Exists according to mISL_gc_to_agb_animal, but seems unused in practice */
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

typedef struct demo_npc_s {
  mActor_name_t npc_name; /* villager id, E0XX */
  u32 block_x, block_z; /* spawn acre */
  u32 ut_x, ut_z; /* spawn unit in acre */
} mNpc_demo_npc_c;

typedef struct {
  u8 type;
  u8 palette;
  u8 wall_id;
  u8 floor_id;
  mActor_name_t main_layer_id;
  mActor_name_t secondary_layer_id;
} mNpc_NpcHouseData_c;

typedef struct npc_conversation_s {
  u8 beesting:1; // talk to player about their beesting
  u8 unk:7;
} mNpc_NpcConversation_c;

typedef struct npc_list_s {
  mActor_name_t name;
  mActor_name_t field_name;
  xyz_t house_position;
  xyz_t position;
  u8 appear_flag;
  mNpc_NpcConversation_c conversation_flags;
  mQst_base_c quest_info;
  mNpc_NpcHouseData_c house_data;
  mActor_name_t reward_furniture;
} mNpc_NpcList_c;

/* anm_id could also just be a Animal_c pointer */
extern void mNpc_GetNpcWorldNameAnm(u8* name, AnmPersonalID_c* anm_id);
extern int mNpc_CheckFreeAnimalPersonalID(AnmPersonalID_c* anm_id);
extern void mNpc_SetAnimalTitleDemo(mNpc_demo_npc_c* demo_npc, Animal_c* animal, GAME* game);
extern void mNpc_SetNpcList(mNpc_NpcList_c* npc_list, Animal_c* animal, int max, int unused);
extern void mNpc_ClearCacheName();
extern void mNpc_ClearInAnimal();
extern void mNpc_FirstClearGoodbyMail();
extern void mNpc_ClearIslandNpcRoomData();
extern void mNpc_CopyAnimalPersonalID(AnmPersonalID_c* dst, AnmPersonalID_c* src);
extern AnmPersonalID_c* mNpc_GetOtherAnimalPersonalID(AnmPersonalID_c* ids, int num_ids);
extern void mNpc_ClearEventNpc();
extern void mNpc_ClearMaskNpc();
extern int mNpc_SearchAnimalinfo(Animal_c* animal, mActor_name_t npc_name, int count);
extern int mNpc_RegistEventNpc(mActor_name_t actor_name, mActor_name_t tex_name, mActor_name_t npc_name, mActor_name_t cloth_name);
extern void mNpc_ClearAnimalInfo(Animal_c* animal_p);
extern Animal_c* mNpc_GetInAnimalP();
extern int mNpc_GetLooks2Sex(int looks);
extern int mNpc_CheckFreeAnimalInfo(Animal_c* animal);
extern int mNpc_GetFriendAnimalNum(Private_c* private_p);
extern int mNpc_GetLooks(mActor_name_t npc_name);
extern void mNpc_LoadNpcNameString(u8* buf, u8 idx);
extern u8 mNpc_GetPaperType();
extern void mMl_set_mail_name_npcinfo(Mail_nm_c* mail_name, AnmPersonalID_c* anm_pid);
extern int mNpc_ReceiveHPMail(Mail_c* hp_mail);
extern void mNpc_SendMailtoNpc(Mail_c* mail);
extern void mNpc_SetNpcinfo(ACTOR* actor, s8 npc_info_idx);
extern void mNpc_InitNpcAllInfo(int malloc_flag);
extern void mNpc_SetRemoveAnimalNo(u8* remove_animal_no, Animal_c* animals, int remove_no);
extern void mNpc_ClearAnimalPersonalID(AnmPersonalID_c* id);
extern int mNpc_CheckCmpAnimalPersonalID(AnmPersonalID_c* id0, AnmPersonalID_c* id1);
extern int mNpc_SearchAnimalPersonalID(AnmPersonalID_c* id);
extern void mNpc_GetActorWorldName(u8* buf, mActor_name_t id);
extern u8 mNpc_CheckNormalMail_length(int* len, u8* body);
extern mActor_name_t mNpc_GetNpcFurniture(AnmPersonalID_c* pid);
extern void mNpc_GetNpcWorldNameTableNo(u8* buf, mActor_name_t name_id);
extern void mNpc_GetRandomAnimalName(u8* buf);

extern void mNpc_PrintRemoveInfo(gfxprint_t* gfxprint);
extern void mNpc_PrintFriendship_fdebug(gfxprint_t* gfxprint);

#ifdef __cplusplus
}
#endif

#endif
