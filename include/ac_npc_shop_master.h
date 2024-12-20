#ifndef AC_NPC_SHOP_MASTER_H
#define AC_NPC_SHOP_MASTER_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"
#include "m_mail_password_check.h"
#include "m_private.h"

#define aNSC_MAX_TICKETS 255

#define aNSC_9C8_LEN 8
#define aNSC_9D0_LEN 8

#define SELL_BUY_RATIO 4
#define aNSC_LOAN_MEDIUM 148000
#define aNSC_LOAN_LARGE 398000
#define aNSC_LOAN_UPPER 798000
#define aNSC_LOAN_STATUE 0
#define aNSC_LOAN_BASEMENT 49800


typedef struct npc_shop_master_s NPC_SHOP_MASTER_ACTOR;

typedef void (*aNSC_PROC)(NPC_SHOP_MASTER_ACTOR*, GAME_PLAY*);

struct npc_shop_master_s {
    /* 0x000 */ NPC_ACTOR npc_class;
    /* 0x994 */ int action;
    /* 0x998 */ int next_action;
    /* 0x99C */ aNSC_PROC proc;
    /* 0x9A0 */ u16 _9A0;
    /* 0x9A2 */ u8 _9A2;
    /* 0x9A3 */ u8 _9A3;
    /* 0x9A4 */ u8 _9A4;
    /* 0x9A6 */ s16 player_angle;
    /* 0x9A8 */ u32 _9A8;
    /* 0x9AC */ u32 value;
    /* 0x9B0 */ u32 counter;
    /* 0x9B4 */ mActor_name_t sell_item;
    /* 0x9B6 */ u8 ut_x;
    /* 0x9B7 */ u8 ut_y;
    /* 0x9B8 */ u8 _9B8;
    /* 0x9B9 */ u8 _9B9;
    /* 0x9BA */ mActor_name_t order_item;
    /* 0x9BC */ u16 _9BC;
    /* 0x9BE */ u16 _9BE;
    /* 0x9C0 */ int _9C0;
    /* 0x9C4 */ int _9C4;
    /* 0x9C8 */ u8 _9C8[aNSC_9C8_LEN];
    /* 0x9D0 */ u8 _9D0[aNSC_9D0_LEN];
    /* 0x9D8 */ u8 password_str[mMpswd_PASSWORD_STR_LEN];
    /* 0x9F4 */ u16 _9F4;
    /* 0x9F6 */ u16 password_flags;
    /* 0x9F8 */ mMpswd_password_c password;
};

enum aNSC_action {
    aNSC_ACTION_GIVE_BALLOON = 0x7,
    aNSC_ACTION_MONEY_OVERFLOW = 0xd,
    aNSC_ACTION_BUY_REFUSE = 0xf,
    aNSC_ACTION_BUY_TRANSACT = 0x11,
    aNSC_ACTION_TAKE_OFF_HANDS = 0x14,
    aNSC_ACTION_BREAK_BAG = 0x16,
    aNSC_ACTION_ANYTHING_ELSE = 0x17,
    aNSC_ACTION_EXIT = 0x43,
    aNSC_ACTION_NUM
};

enum aNSC_msg_no {
    aNSC_MSG_WAIT = -0x1,
    aNSC_MSG_REHOUSE_MEDIUM = 0x0,
    aNSC_MSG_REHOUSE_MEDIUM_1 = 0x1,
    aNSC_MSG_REHOUSE_MEDIUM_2 = 0x2,
    aNSC_MSG_MEDIUM_BUILT = 0x3,
    aNSC_MSG_REHOUSE_2_OFFER = 0x4,
    aNSC_MSG_REHOUSE_2_LARGe = 0x5,
    aNSC_MSG_REHOUSE_2_BASEment = 0x6,
    aNSC_MSG_LARGE_BUILT = 0x7,
    aNSC_MSG_REHOUSE_STATUE = 0x8,
    aNSC_MSG_STATUE_BUILT = 0x9,
    aNSC_MSG_PALLET_SELECTED = 0xa,
    aNSC_MSG_PALLET_SELECT_1 = 0xb,
    aNSC_MSG_PALLET_SELECT_2 = 0xc,
    aNSC_MSG_PALLET_SELECT_3 = 0xd,
    aNSC_MSG_PALLET_SELECT_4 = 0xe,
    aNSC_MSG_OFFER_SELL_ALL = 0xf,
    aNSC_MSG_EVENT_DEPART = 0x10,
    aNSC_MSG_GREET_DEPART = 0x11,
    aNSC_MSG_SHOW_CLOTH = 0x12,
    aNSC_MSG_CONFIRM_CLOTH = 0x13,
    aNSC_MSG_CANCEL_CLOTH = 0x14,
    aNSC_MSG_CANCEL = 0x15,
    aNSC_MSG_START_CALL_NORMAL = 0x16,
    aNSC_MSG_INTERACT_START = 0x17,
    aNSC_MSG_INTERACT_CANCEl = 0x18,
    aNSC_MSG_KABU_INFO = 0x19,
    aNSC_MSG_SELL_START = 0x1a,
    aNSC_MSG_SELL_OFFER = 0x1b,
    aNSC_MSG_SELL_NORMAL = 0x1c,
    aNSC_MSG_SELL_CANCEL = 0x1d,
    aNSC_MSG_BUY_ONE_OFFER = 0x1e,
    aNSC_MSG_BUY_CANCEL = 0x1f,
    aNSC_MSG_THANKS = 0x20,
    aNSC_MSG_INSUFFICIENT_FUNDS = 0x21,
    aNSC_MSG_BUY_NORMAL = 0x22,
    aNSC_MSG_SAY_GOODBYE = 0x23,
    aNSC_MSG_KABU_ON_SUNDAY = 0x24,
    aNSC_MSG_EVENT = 0x25,
    aNSC_MSG_BREAK_BAG = 0x26,
    aNSC_MSG_POCKETS_FULL = 0x27,
    aNSC_MSG_SHOW_ITEM = 0x28,
    aNSC_MSG_SHOW_CARPET_OFFER = 0x29,
    aNSC_MSG_SHOW_CARPET_DECLINE = 0x2a,
    aNSC_MSG_SHOW_CATALOGUE = 0x2b,
    aNSC_MSG_ORDER_OFFER = 0x2c,
    aNSC_MSG_ORDER_UNAVAILABLE = 0x2d,
    aNSC_MSG_ORDER_CANCEL = 0x2e,
    aNSC_MSG_ORDER_CONFIRM = 0x2f,
    aNSC_MSG_ORDER_INSUFFICIENT_FUNDS = 0x30,
    aNSC_MSG_ORDER_FULL = 0x31,
    aNSC_MSG_ORDER_FURNITURE_ONLY = 0x32,
    aNSC_MSG_GIVE_TICKET = 0x33,
    aNSC_MSG_MAIL_TICKET = 0x34,
    aNSC_MSG_TICKET_1 = 0x35,
    aNSC_MSG_TICKET_2 = 0x36,
    aNSC_MSG_TICKET_SELL_REFUSE = 0x37,
    aNSC_MSG_SELL_QUEST = 0x38,
    aNSC_MSG_JUNK_ACCEPT = 0x39,
    aNSC_MSG_JUNK_CANCEL = 0x3a,
    aNSC_MSG_SELL_SHOVEL = 0x64,
    aNSC_MSG_SELL_NET = 0x65,
    aNSC_MSG_SELL_ROD = 0x66,
    aNSC_MSG_SELL_AXE = 0x67,
    aNSC_MSG_SELL_SIGN = 0x68,
    aNSC_MSG_MONEY_OVERFLOW = 0xc8,
    aNSC_MSG_SELL_PAINT = 0xca,
    ansc_msg_sell_paint_confirm = 0xcb,
    aNSC_MSG_BASEMENT_BUILT = 0xcc,
    aNSC_MSG_BASEMENT_PAID = 0xcd,
    aNSC_MSG_REHOUSE_BASEMENT = 0xd0,
    aNSC_MSG_REHOUSE_LARGE = 0xd1,
    aNSC_MSG_REHOUSE_UPPER = 0xd4,
    aNSC_MSG_UPPER_BUILT = 0xd5,
    aNSC_MSG_BUY_MANY_OFFER = 0xd6,
    aNSC_MSG_BUY_REFUSE = 0xd8,
    aNSC_MSG_BALLOON = 0xda,
    aNSC_MSG_BALLOON_DEPART = 0xdc,
    aNSC_MSG_SELL_PAPER = 0xde,
    aNSC_MSG_SELL_PAINT_FOREIGN = 0xdf,
    aNSC_MSG_PSWD_NO_ITEM = 0x12c,
    aNSC_MSG_PSWD_INFO = 0x12d,
    aNSC_MSG_PSWD_SAME_NAME = 0x12e,
    aNSC_MSG_PSWD_CONFIRM = 0x12f,
    aNSC_MSG_PSWD_CANCEL = 0x131,
    aNSC_MSG_PSWD_CHECK = 0x132,
    aNSC_MSG_OTHER = 0x135,
    aNSC_MSG_RETURN = 0x136,
    aNSC_MSG_PSWD_INVENTORY_FULL = 0x137,
    aNSC_MSG_PSWD_SAY = 0x138,
    aNSC_MSG_PSWD_WRONG = 0x139,
    aNSC_MSG_PSWD_DECLINE = 0x13a,
    aNSC_MSG_PSWD_GOOD_FAMICON = 0x13b,
    aNSC_MSG_PSWD_GOOD_NPC = 0x13c,
    aNSC_MSG_PSWD_GOOD_MAGAZINE_1 = 0x13d,
    aNSC_MSG_PSWD_CARDE = 0x13e,
    aNSC_MSG_PSWD_GOOD_USER = 0x13f,
    aNSC_MSG_PSWD_GOOD_CARDEM = 0x140,
    aNSC_MSG_PSWD_GOOD_MAGAZINE_2 = 0x142,
    aNSC_MSG_PSWD_BAD = 0x144,
    aNSC_MSG_PSWD_FOREIGN = 0x141,
    aNSC_MSG_GIFT_OUT = 0x143,
    aNSC_MSG_TAKE_OFF_HANDS= 0x108a,

    aNSC_MSG_NUM
};

enum aNSC_wait_type {

    aNSC_WAIT_TYPE_REHOUSE = 0x0,
    aNSC_WAIT_TYPE_DONE_REHOUSE = 0x1,
    aNSC_WAIT_TYPE_BALLOON = 0x2,
    aNSC_WAIT_TYPE_3 = 0x3,
    aNSC_WAIT_TYPE_HRATALK = 0x4,

    aNSC_WAIT_TYPE_NUM
};

enum aNSC_buy_outcome {
    aNSC_BUY_OUTCOME_BREAK_BAG = 0x0,
    aNSC_BUY_OUTCOME_NORMAL = 0x1,
    aNSC_BUY_OUTCOME_CANCEL = 0x2,
    aNSC_BUY_OUTCOME_MONEY_OVERFLOW = 0x3,  
    aNSC_BUY_OUTCOME_NUM
};

enum aNSC_check_buy {
    aNSC_CHECK_BUY_NORMAL_SUB,
    aNSC_CHECK_BUY_NONE_SELECTED,
    aNSC_CHECK_BUY_NO_SUNDAY_TURNIPS,
    aNSC_CHECK_BUY_REFUSE_QUEST_COND,
    aNSC_CHECK_BUY_TAKE_OFF_HANDS,
    aNSC_CHECK_BUY_OFFER_BUY_ALL,
    aNSC_CHECK_BUY_TURNIPS,
    aNSC_CHECK_BUY_NORMAL,

    aNSC_RES_NUM
};

enum aNSC_tanni_str {
    aNSC_TANNI_STR_COMMOD = 0x1,
    aNSC_TANNI_STR_CLOTH = 0x2,
    aNSC_TANNI_STR_KABU = 0x4,
    aNSC_TANNI_STR_FAUNA = 0x5,
    aNSC_TANNI_STR_SAPPLING = 0x7,
    aNSC_TANNI_STR_DIARY = 0x9,

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

typedef struct aNSC_animation_data_s {
    int anim;
    int talk_flag;
} aNSC_animation_data;

ACTOR_PROFILE Npc_Shop_Master_Profile = {
    mAc_PROFILE_NPC_SHOP_MASTER,    
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_SHOP_MASTER,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_SHOP_MASTER_ACTOR),
};


#define aNSC_PLAYER_DISTANCE (f32)60.0

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

extern void aNSC_setupAction(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY* game, int p3);
int aNSC_check_buy_item_sub(u32 *p1, mActor_name_t itm_name);
int aNSC_check_buy_paper(u32 *p1, mActor_name_t itm_name);
void aNSC_init_proc(NPC_SHOP_MASTER_ACTOR *shop_master, GAME_PLAY * game, int p3);

#endif

