#ifndef AC_NPC_SHOP_COMMON_H
#define AC_NPC_SHOP_COMMON_H

#include "types.h"
#include "ac_npc.h"
#include "m_mail_password_check.h"
#include "m_font.h"
#include "m_player_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aNSC_MAX_TICKETS 255

#define aNSC_PW_TOWN_STR_LEN LAND_NAME_SIZE
#define aNSC_PW_RECIP_STR_LEN PLAYER_NAME_LEN

#define SELL_BUY_RATIO 4
#define aNSC_LOAN_MEDIUM 148000
#define aNSC_LOAN_LARGE 398000
#define aNSC_LOAN_UPPER 798000
#define aNSC_LOAN_STATUE 0
#define aNSC_LOAN_BASEMENT 49800

#define aNSC_PLAYER_DISTANCE (f32)60.0

enum aNSC_msg_no {
    aNSC_MSG_WAIT = -0x1,
    aNSC_MSG_REHOUSE_MEDIUM = 0x0,
    aNSC_MSG_REHOUSE_MEDIUM_1,
    aNSC_MSG_REHOUSE_MEDIUM_2,
    aNSC_MSG_MEDIUM_BUILT,
    aNSC_MSG_REHOUSE_2_OFFER,
    aNSC_MSG_REHOUSE_2_LARGe,
    aNSC_MSG_REHOUSE_2_BASEment,
    aNSC_MSG_LARGE_BUILT,
    aNSC_MSG_REHOUSE_STATUE,
    aNSC_MSG_STATUE_BUILT,
    aNSC_MSG_PALLET_SELECTED,
    aNSC_MSG_PALLET_SELECT_1,
    aNSC_MSG_PALLET_SELECT_2,
    aNSC_MSG_PALLET_SELECT_3,
    aNSC_MSG_PALLET_SELECT_4,
    aNSC_MSG_OFFER_SELL_ALL,
    aNSC_MSG_EVENT_DEPART,
    aNSC_MSG_GREET_DEPART,
    aNSC_MSG_SHOW_CLOTH,
    aNSC_MSG_CONFIRM_CLOTH,
    aNSC_MSG_CANCEL_CLOTH,
    aNSC_MSG_CANCEL,
    aNSC_MSG_START_CALL_NORMAL,
    aNSC_MSG_INTERACT_START,
    aNSC_MSG_INTERACT_CANCEL,
    aNSC_MSG_KABU_INFO,
    aNSC_MSG_SELL_START,
    aNSC_MSG_SELL_OFFER,
    aNSC_MSG_SELL_NORMAL,
    aNSC_MSG_SELL_CANCEL,
    aNSC_MSG_BUY_ONE_OFFER,
    aNSC_MSG_BUY_CANCEL,
    aNSC_MSG_THANKS,
    aNSC_MSG_INSUFFICIENT_FUNDS,
    aNSC_MSG_BUY_NORMAL,
    aNSC_MSG_SAY_GOODBYE,
    aNSC_MSG_KABU_ON_SUNDAY,
    aNSC_MSG_EVENT,
    aNSC_MSG_BREAK_BAG,
    aNSC_MSG_POCKETS_FULL,
    aNSC_MSG_SHOW_ITEM,
    aNSC_MSG_SHOW_CARPET_OFFER,
    aNSC_MSG_SHOW_CARPET_DECLINE,
    aNSC_MSG_SHOW_CATALOGUE,
    aNSC_MSG_ORDER_OFFER,
    aNSC_MSG_ORDER_UNAVAILABLE,
    aNSC_MSG_ORDER_CANCEL,
    aNSC_MSG_ORDER_CONFIRM,
    aNSC_MSG_ORDER_INSUFFICIENT_FUNDS,
    aNSC_MSG_ORDER_FULL,
    aNSC_MSG_ORDER_FURNITURE_ONLY,
    aNSC_MSG_GIVE_TICKET,
    aNSC_MSG_MAIL_TICKET,
    aNSC_MSG_TICKET_1,
    aNSC_MSG_TICKET_2,
    aNSC_MSG_TICKET_SELL_REFUSE,
    aNSC_MSG_SELL_QUEST,
    aNSC_MSG_JUNK_ACCEPT,
    aNSC_MSG_JUNK_CANCEL,
    aNSC_MSG_3B,
    aNSC_MSG_3C,
    aNSC_MSG_3D,
    aNSC_MSG_3E,
    aNSC_MSG_3F,
    aNSC_MSG_SELL_SHOVEL = 0x64,
    aNSC_MSG_SELL_NET,
    aNSC_MSG_SELL_ROD,
    aNSC_MSG_SELL_AXE,
    aNSC_MSG_SELL_SIGN,
    aNSC_MSG_MONEY_OVERFLOW = 0xc8,
    aNSC_MSG_SELL_PAINT = 0xca,
    aNSC_MSG_SELL_PAINT_CONFIRM,
    aNSC_MSG_BASEMENT_BUILT,
    aNSC_MSG_BASEMENT_PAID,
    aNSC_MSG_REHOUSE_BASEMENT = 0xd0,
    aNSC_MSG_REHOUSE_LARGE,
    aNSC_MSG_REHOUSE_UPPER = 0xd4,
    aNSC_MSG_UPPER_BUILT,
    aNSC_MSG_BUY_MANY_OFFER,
    aNSC_MSG_BUY_REFUSE_PLURAL = 0xd8,
    aNSC_MSG_BALLOON = 0xda,
    aNSC_MSG_BALLOON_DEPART = 0xdc,
    aNSC_MSG_SELL_PAPER = 0xde,
    aNSC_MSG_SELL_PAINT_FOREIGN,
    aNSC_MSG_PSWD_NO_ITEM = 0x12c,
    aNSC_MSG_PSWD_INFO = 0x12d,
    aNSC_MSG_PSWD_SAME_NAME,
    aNSC_MSG_PSWD_CONFIRM,
    aNSC_MSG_PSWD_CANCEL = 0x131,
    aNSC_MSG_PSWD_CHECK,
    aNSC_MSG_OTHER = 0x135,
    aNSC_MSG_RETURN,
    aNSC_MSG_PSWD_INVENTORY_FULL,
    aNSC_MSG_PSWD_SAY,
    aNSC_MSG_PSWD_WRONG,
    aNSC_MSG_PSWD_DECLINE,
    aNSC_MSG_PSWD_GOOD_FAMICON,
    aNSC_MSG_PSWD_GOOD_NPC,
    aNSC_MSG_PSWD_GOOD_MAGAZINE_1,
    aNSC_MSG_PSWD_CARDE,
    aNSC_MSG_PSWD_GOOD_USER,
    aNSC_MSG_PSWD_GOOD_CARDEM,
    aNSC_MSG_PSWD_FOREIGN,
    aNSC_MSG_PSWD_GOOD_MAGAZINE_2,
    aNSC_MSG_GIFT_OUT,
    aNSC_MSG_PSWD_BAD,
};

enum aNSC_wait_type {

    aNSC_WAIT_TYPE_REHOUSE,
    aNSC_WAIT_TYPE_DONE_REHOUSE,
    aNSC_WAIT_TYPE_BALLOON,
    aNSC_WAIT_TYPE_3,
    aNSC_WAIT_TYPE_HRATALK,

    aNSC_WAIT_TYPE_NUM
};

enum aNSC_buy_outcome {
    aNSC_BUY_OUTCOME_BREAK_BAG,
    aNSC_BUY_OUTCOME_NORMAL,
    aNSC_BUY_OUTCOME_CANCEL,
    aNSC_BUY_OUTCOME_MONEY_OVERFLOW,  
    aNSC_BUY_OUTCOME_NUM
};

enum aNSC_check_buy {
    aNSC_CHECK_BUY_NORMAL_SUB,
    aNSC_CHECK_BUY_NONE_SELECTED,
    aNSC_CHECK_BUY_NO_SUNDAY_TURNIPS,
    aNSC_CHECK_BUY_REFUSE_QUEST_COND,
    aNSC_CHECK_BUY_TAKE_OFF_HANDS,
    aNSC_CHECK_BUY_OFFER_BUY_ALL,
    aNSC_CHECK_BUY_PLURAL,
    aNSC_CHECK_BUY_NORMAL,

    aNSC_RES_NUM
};

enum aNSC_tanni_str {
    aNSC_TANNI_STR_00,
    aNSC_TANNI_STR_COMMOD,
    aNSC_TANNI_STR_CLOTH,
    aNSC_TANNI_03,
    aNSC_TANNI_STR_KABU,
    aNSC_TANNI_STR_FAUNA,
    aNSC_TANNI_STR_SAPPLING,
    aNSC_TANNI_STR_DIARY,
    aNSC_TANNI_STR_08,
    aNSC_TANNI_STR_09,

    aNSC_TANNI_STR_NUM
};

enum check_password_result {
    aNSC_PSW_RES_0,
    aNSC_PSW_GOOD_FAMICON,
    aNSC_PSW_GOOD_NPC,
    aNSC_PSW_GOOD_MAGAZINE_1,
    aNSC_PSW_CARDE = 4,
    aNSC_PSW_GOOD_USER,
    aNSC_PSW_GOOD_CARDEM,
    aNSC_PSW_GOOD_MAGAZINE_2,
    aNSC_PSW_BAD = 8,
    aNSC_PSW_RES_9 = 9,

    aNSC_PSW_NUM
};

enum aNSC_request_show_type {
    aNSC_REQUEST_SHOW_TYPE_WALL,
    aNSC_REQUEST_SHOW_TYPE_CARPET
};

enum {
    aNSC_DAY_NORMAL,
    aNSC_DAY_FUKUBIKI,

    aNSC_DAY_NUM
};

typedef struct aNSC_animation_data_s {
    int anim;
    int talk_flag;
} aNSC_animation_data;

typedef struct npc_shop_common_actor_s NPC_SHOP_COMMON_ACTOR;

typedef void (*aNSC_PROC)(ACTOR*, GAME*);

typedef void (*aNSC_INIT_PROC)(NPC_SHOP_COMMON_ACTOR*, GAME_PLAY*);
typedef int (*aNSC_PC_CHECK_PASSWORD_PROC)(mMpswd_password_c*);
typedef void (*aNSC_ITEM_SELL_PROC)(NPC_SHOP_COMMON_ACTOR*, mActor_name_t);
typedef void (*aNSC_ACTION_PROC)(NPC_SHOP_COMMON_ACTOR*, GAME_PLAY*);
typedef void (*aNSC_TALK_PROC)(NPC_SHOP_COMMON_ACTOR*, GAME_PLAY*);
typedef void (*aNSC_TALK_REQ_PROC)(NPC_SHOP_COMMON_ACTOR*, PLAYER_ACTOR*);

struct npc_shop_common_actor_s {
    /* 0x000 */ NPC_ACTOR npc_class;
    /* 0x994 */ int action;
    /* 0x998 */ int next_action;
    /* 0x99C */ aNSC_ACTION_PROC proc;
    /* 0x9A0 */ u16 _9A0;
    /* 0x9A2 */ u8 zone;
    /* 0x9A3 */ u8 next_zone;
    /* 0x9A4 */ u8 player_zone;
    /* 0x9A5 */ u8 sale_type;
    /* 0x9A6 */ s16 player_angle;
    /* 0x9A8 */ u32 money;
    /* 0x9AC */ u32 value;
    /* 0x9B0 */ u32 counter;
    /* 0x9B4 */ mActor_name_t sell_item;
    /* 0x9B6 */ u8 ut_x;
    /* 0x9B7 */ u8 ut_z;
    /* 0x9B8 */ u8 is_selling;
    /* 0x9B9 */ u8 _9B9;
    /* 0x9BA */ mActor_name_t order_item;
    /* 0x9BC */ u16 player_cloth;
    /* 0x9BE */ u16 change_cloth;
    /* 0x9C0 */ int talk_start_tim;
    /* 0x9C4 */ int msg_no;
    /* 0x9C8 */ u8 pw_town_str[aNSC_PW_TOWN_STR_LEN];
    /* 0x9D0 */ u8 pw_recip_str[aNSC_PW_RECIP_STR_LEN];
    /* 0x9D8 */ u8 password_str[mMpswd_PASSWORD_STR_LEN];
    /* 0x9F4 */ u16 pw_item;
    /* 0x9F6 */ u16 password_flags;
    /* 0x9F8 */ mMpswd_password_c password;
};

#ifdef __cplusplus
}
#endif

#endif
