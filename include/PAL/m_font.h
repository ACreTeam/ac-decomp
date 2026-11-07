#ifndef M_FONT_H
#define M_FONT_H

#include "types.h"
#include "m_lib.h"
#include "graph.h"
#include "game.h"
#include "libforest/gbi_extensions.h"
#include "charmap.h"
#include "libu64/gfxprint.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mFont_MARKTYPE_VERT_ARROW 0
#define mFont_MARKTYPE_HORI_ARROW 1
#define mFont_MARKTYPE_CURSOR 2
#define mFont_MARKTYPE_NEXT 3
#define mFont_MARKTYPE_CHOICE 4
#define mFont_MARKTYPE_TOTAL 5

#define mFont_MODE_POLY 0
#define mFont_MODE_FONT 1

enum {
    mFont_CONT_CODE_BEGIN = 0,
    mFont_CONT_CODE_LAST = mFont_CONT_CODE_BEGIN,
    mFont_CONT_CODE_CONTINUE,
    mFont_CONT_CODE_CLEAR,
    mFont_CONT_CODE_CURSOR_SET_TIME,
    mFont_CONT_CODE_BUTTON,
    mFont_CONT_CODE_COLOR,
    mFont_CONT_CODE_ABLE_CANCEL,
    mFont_CONT_CODE_UNABLE_CANCEL,
    mFont_CONT_CODE_SET_DEMO_ORDER_PLAYER,
    mFont_CONT_CODE_SET_DEMO_ORDER_NPC0,
    mFont_CONT_CODE_SET_DEMO_ORDER_NPC1,
    mFont_CONT_CODE_SET_DEMO_ORDER_NPC2,
    mFont_CONT_CODE_SET_DEMO_ORDER_QUEST,
    mFont_CONT_CODE_SET_SELECT_WINDOW,
    mFont_CONT_CODE_SET_NEXT_MESSAGE_F,
    mFont_CONT_CODE_SET_NEXT_MESSAGE_0,
    mFont_CONT_CODE_SET_NEXT_MESSAGE_1,
    mFont_CONT_CODE_SET_NEXT_MESSAGE_2,
    mFont_CONT_CODE_SET_NEXT_MESSAGE_3,
    mFont_CONT_CODE_SET_NEXT_MESSAGE_RANDOM_2,
    mFont_CONT_CODE_SET_NEXT_MESSAGE_RANDOM_3,
    mFont_CONT_CODE_SET_NEXT_MESSAGE_RANDOM_4,
    mFont_CONT_CODE_SET_SELECT_STRING_2,
    mFont_CONT_CODE_SET_SELECT_STRING_3,
    mFont_CONT_CODE_SET_SELECT_STRING_4,
    mFont_CONT_CODE_SET_FORCE_NEXT,
    mFont_CONT_CODE_PUT_STRING_PLAYER_NAME,
    mFont_CONT_CODE_PUT_STRING_TALK_NAME,
    mFont_CONT_CODE_PUT_STRING_TAIL,
    mFont_CONT_CODE_PUT_STRING_YEAR,
    mFont_CONT_CODE_PUT_STRING_MONTH,
    mFont_CONT_CODE_PUT_STRING_WEEK,
    mFont_CONT_CODE_PUT_STRING_DAY,
    mFont_CONT_CODE_PUT_STRING_HOUR,
    mFont_CONT_CODE_PUT_STRING_MIN,
    mFont_CONT_CODE_PUT_STRING_SEC,
    mFont_CONT_CODE_PUT_STRING_FREE0,
    mFont_CONT_CODE_PUT_STRING_FREE1,
    mFont_CONT_CODE_PUT_STRING_FREE2,
    mFont_CONT_CODE_PUT_STRING_FREE3,
    mFont_CONT_CODE_PUT_STRING_FREE4,
    mFont_CONT_CODE_PUT_STRING_FREE5,
    mFont_CONT_CODE_PUT_STRING_FREE6,
    mFont_CONT_CODE_PUT_STRING_FREE7,
    mFont_CONT_CODE_PUT_STRING_FREE8,
    mFont_CONT_CODE_PUT_STRING_FREE9,
    mFont_CONT_CODE_PUT_STRING_DETERMINATION,
    mFont_CONT_CODE_PUT_STRING_COUNTRY_NAME,
    mFont_CONT_CODE_PUT_STRING_RANDOM_NUMBER_2,
    mFont_CONT_CODE_PUT_STRING_ITEM0,
    mFont_CONT_CODE_PUT_STRING_ITEM1,
    mFont_CONT_CODE_PUT_STRING_ITEM2,
    mFont_CONT_CODE_PUT_STRING_ITEM3,
    mFont_CONT_CODE_PUT_STRING_ITEM4,
    mFont_CONT_CODE_PUT_STRING_FREE10,
    mFont_CONT_CODE_PUT_STRING_FREE11,
    mFont_CONT_CODE_PUT_STRING_FREE12,
    mFont_CONT_CODE_PUT_STRING_FREE13,
    mFont_CONT_CODE_PUT_STRING_FREE14,
    mFont_CONT_CODE_PUT_STRING_FREE15,
    mFont_CONT_CODE_PUT_STRING_FREE16,
    mFont_CONT_CODE_PUT_STRING_FREE17,
    mFont_CONT_CODE_PUT_STRING_FREE18,
    mFont_CONT_CODE_PUT_STRING_FREE19,
    mFont_CONT_CODE_PUT_STRING_MAIL,
    mFont_CONT_CODE_SET_PLAYER_DESTINY0,
    mFont_CONT_CODE_SET_PLAYER_DESTINY1,
    mFont_CONT_CODE_SET_PLAYER_DESTINY2,
    mFont_CONT_CODE_SET_PLAYER_DESTINY3,
    mFont_CONT_CODE_SET_PLAYER_DESTINY4,
    mFont_CONT_CODE_SET_PLAYER_DESTINY5,
    mFont_CONT_CODE_SET_PLAYER_DESTINY6,
    mFont_CONT_CODE_SET_PLAYER_DESTINY7,
    mFont_CONT_CODE_SET_PLAYER_DESTINY8,
    mFont_CONT_CODE_SET_PLAYER_DESTINY9,
    mFont_CONT_CODE_SET_MESSAGE_CONTENTS_NORMAL,
    mFont_CONT_CODE_SET_MESSAGE_CONTENTS_ANGRY,
    mFont_CONT_CODE_SET_MESSAGE_CONTENTS_SAD,
    mFont_CONT_CODE_SET_MESSAGE_CONTENTS_FUN,
    mFont_CONT_CODE_SET_MESSAGE_CONTENTS_SLEEPY,
    mFont_CONT_CODE_SET_COLOR_CHAR,
    mFont_CONT_CODE_SOUND_CUT,
    mFont_CONT_CODE_SET_LINE_OFFSET,
    mFont_CONT_CODE_SET_LINE_TYPE,
    mFont_CONT_CODE_SET_CHAR_SCALE,
    mFont_CONT_CODE_BUTTON2,
    mFont_CONT_CODE_BGM_MAKE,
    mFont_CONT_CODE_BGM_DELETE,
    mFont_CONT_CODE_MSG_TIME_END,
    mFont_CONT_CODE_SOUND_TRG_SYS,
    mFont_CONT_CODE_SET_LINE_SCALE,
    mFont_CONT_CODE_SOUND_NO_PAGE,
    mFont_CONT_CODE_VOICE_TRUE,
    mFont_CONT_CODE_VOICE_FALSE,
    mFont_CONT_CODE_SELECT_NO_B,
    mFont_CONT_CODE_GIVE_OPEN,
    mFont_CONT_CODE_GIVE_CLOSE,
    mFont_CONT_CODE_SET_MESSAGE_CONTENTS_GLOOMY,
    mFont_CONT_CODE_SELECT_NO_B_CLOSE,
    mFont_CONT_CODE_SET_NEXT_MESSAGE_RANDOM_SECTION,
    mFont_CONT_CODE_AGB_DUMMY0,
    mFont_CONT_CODE_AGB_DUMMY1,
    mFont_CONT_CODE_AGB_DUMMY2,
    mFont_CONT_CODE_SPACE,
    mFont_CONT_CODE_AGB_DUMMY3,
    mFont_CONT_CODE_AGB_DUMMY4,
    mFont_CONT_CODE_AGB_MALE_FEMALE_CHECK,
    mFont_CONT_CODE_AGB_DUMMY5,
    mFont_CONT_CODE_AGB_DUMMY6,
    mFont_CONT_CODE_AGB_DUMMY7,
    mFont_CONT_CODE_AGB_DUMMY8,
    mFont_CONT_CODE_AGB_DUMMY9,
    mFont_CONT_CODE_AGB_DUMMY10,
    mFont_CONT_CODE_PUT_STRING_ISLAND_NAME,
    mFont_CONT_CODE_SET_CURSOR_JUST,
    mFont_CONT_CODE_CLR_CURSOR_JUST,
    mFont_CONT_CODE_CUT_ARTICLE,
    mFont_CONT_CODE_CAPITAL_LETTER,
    mFont_CONT_CODE_PUT_STRING_AM_PM,
    mFont_CONT_CODE_SET_NEXT_MESSAGE_4,
    mFont_CONT_CODE_SET_NEXT_MESSAGE_5,
    mFont_CONT_CODE_SET_SELECT_STRING_5,
    mFont_CONT_CODE_SET_SELECT_STRING_6,
    mFont_CONT_CODE_9BIT,
    mFont_CONT_CODE_FONT_KIGOU,

    mFont_CONT_CODE_NUM,
    mFont_CONT_CODE_END = 256
};

// TODO: figure out the other values for this
enum {
    mFont_CONT_ATTRIBUTE_0,
    mFont_CONT_ATTRIBUTE_DEMO,
    mFont_CONT_ATTRIBUTE_STRING,
    mFont_CONT_ATTRIBUTE_3,
    mFont_CONT_ATTRIBUTE_SENTENCE,
    mFont_CONT_ATTRIBUTE_CHARACTER,
    mFont_CONT_ATTRIBUTE_BGM,
    mFont_CONT_ATTRIBUTE_SE,
    mFont_CONT_ATTRIBUTE_AGB_DUMMY,
    mFont_CONT_ATTRIBUTE_9BIT,

    mFont_CONT_ATTRIBUTE_END
};

enum {
    mFont_LineType_Top,
    mFont_LineType_Center,
    mFont_LineType_Bottom,

    mFont_LineType_End
};

enum {
    mFont_BGM_QUIET,

    // TODO

    mFont_BGM_NUM = 9
};

enum {
    mFont_BGM_STOP_TYPE_NORMAL,
    mFont_BGM_STOP_TYPE_QUICK,
    mFont_BGM_STOP_TYPE_RESETTI,

    mFont_BGM_STOP_TYPE_NUM
};

enum {
    mFont_SE_0,

    // TODO

    mFont_SE_NUM = 7
};

enum {
    mFont_TAG_GROUP_GAIJI,
    mFont_TAG_GROUP_BASE,
    mFont_TAG_GROUP_CHOICE,
    mFont_TAG_GROUP_NPC_EM,
    mFont_TAG_GROUP_STR,
    mFont_TAG_GROUP_COM,
    mFont_TAG_GROUP_MANPU,
    mFont_TAG_GROUP_TM,
    mFont_TAG_GROUP_PL_ST,
    mFont_TAG_GROUP_SPEC,
    mFont_TAG_GROUP_SOUND,
    mFont_TAG_GROUP_QUEST,
    mFont_TAG_GROUP_JUMP,
    mFont_TAG_GROUP_TALK3,
    mFont_TAG_GROUP_BODY,
    mFont_TAG_GROUP_NPC_EM_SUB,
    mFont_TAG_GROUP_MANPU_SUB,
    mFont_TAG_GROUP_TM_SUB,
    mFont_TAG_GROUP_BODY_SUB,
    mFont_TAG_GROUP_GRM,

    mFont_TAG_GROUP_NUM,
    mFont_TAG_GROUP_SYS = 0xFF
};

enum {
    mFont_TAG_HEADER_SIZE = 5,
    mFont_TAG_GRM_SEPARATOR = 0xFE
};

enum {
    mFont_TAG_GRM_ART_DEF,
    mFont_TAG_GRM_ART_NON,
    mFont_TAG_GRM_CAPITAL,
    mFont_TAG_GRM_STRING_INFO = 10,
    mFont_TAG_GRM_INFLECT_PL = 20,
    mFont_TAG_GRM_INFLECT_FREE0 = 30,
    mFont_TAG_GRM_INFLECT_FREE1,
    mFont_TAG_GRM_INFLECT_FREE2,
    mFont_TAG_GRM_INFLECT_FREE3,
    mFont_TAG_GRM_INFLECT_FREE4,
    mFont_TAG_GRM_INFLECT_FREE5,
    mFont_TAG_GRM_INFLECT_FREE6,
    mFont_TAG_GRM_INFLECT_FREE7,
    mFont_TAG_GRM_INFLECT_FREE8,
    mFont_TAG_GRM_INFLECT_FREE9,
    mFont_TAG_GRM_INFLECT_FREE10,
    mFont_TAG_GRM_INFLECT_FREE11,
    mFont_TAG_GRM_INFLECT_FREE12,
    mFont_TAG_GRM_INFLECT_FREE13,
    mFont_TAG_GRM_INFLECT_FREE14,
    mFont_TAG_GRM_INFLECT_FREE15,
    mFont_TAG_GRM_INFLECT_FREE16,
    mFont_TAG_GRM_INFLECT_FREE17,
    mFont_TAG_GRM_INFLECT_FREE18,
    mFont_TAG_GRM_INFLECT_FREE19,
    mFont_TAG_GRM_INFLECT_ITEM0,
    mFont_TAG_GRM_INFLECT_ITEM1,
    mFont_TAG_GRM_INFLECT_ITEM2,
    mFont_TAG_GRM_INFLECT_ITEM3,
    mFont_TAG_GRM_INFLECT_ITEM4,

    mFont_TAG_GRM_NUM
};

enum {
    mFont_TAG_SYS_COLOR,
    mFont_TAG_SYS_SCALE,
    mFont_TAG_SYS_RUBY,
    mFont_TAG_SYS_FONT,

    mFont_TAG_SYS_NUM
};

enum {
    mFont_TAG_BASE_MSG_START,
    mFont_TAG_BASE_MSG_LAST,
    mFont_TAG_BASE_MSG_CONTINUE,
    mFont_TAG_BASE_CLR_CURSOL,
    mFont_TAG_BASE_TIME_INTERVAL,
    mFont_TAG_BASE_KANJI_COM,
    mFont_TAG_BASE_KANJI_PL_LV_SET,
    mFont_TAG_BASE_KANJI_PL_LV_INC,
    mFont_TAG_BASE_KANJI_PL_LV_DEC,
    mFont_TAG_BASE_LINE_OFFSET,
    mFont_TAG_BASE_PIX_SPACE,
    mFont_TAG_BASE_MSG_WAIT_LAST,

    mFont_TAG_BASE_NUM
};

enum {
    mFont_TAG_CHOICE_OP2,
    mFont_TAG_CHOICE_OP3,
    mFont_TAG_CHOICE_OP4,
    mFont_TAG_CHOICE_OP5,
    mFont_TAG_CHOICE_OP6,
    mFont_TAG_CHOICE_ANS0,
    mFont_TAG_CHOICE_ANS1,
    mFont_TAG_CHOICE_ANS2,
    mFont_TAG_CHOICE_ANS3,
    mFont_TAG_CHOICE_ANS4,
    mFont_TAG_CHOICE_ANS5,

    mFont_TAG_CHOICE_NUM
};

enum {
    mFont_TAG_NPC_EM_FUN,
    mFont_TAG_NPC_EM_ANGRY,
    mFont_TAG_NPC_EM_SAD,
    mFont_TAG_NPC_EM_SLEEPY,
    mFont_TAG_NPC_EM_NORMAL,
    mFont_TAG_NPC_EM_GLOOMY,
    mFont_TAG_NPC_EM_CONTINUE,

    mFont_TAG_NPC_EM_NUM
};

enum {
    mFont_TAG_COM_BUTTON,
    mFont_TAG_COM_BUTTON_NO_SE,
    mFont_TAG_COM_B_CANCEL,
    mFont_TAG_COM_B_CANCEL_CLOSE,
    mFont_TAG_COM_ABLE_CANCEL,
    mFont_TAG_COM_UNABLE_CANCEL,
    mFont_TAG_COM_OPEN_CHOICE,
    mFont_TAG_COM_FORCE_NEXT_SET,
    mFont_TAG_COM_LINE_TYPE_TOP,
    mFont_TAG_COM_LINE_TYPE_CENTER,
    mFont_TAG_COM_LINE_TYPE_BOTTOM,
    mFont_TAG_COM_GIVE_OPEN,
    mFont_TAG_COM_GIVE_CLOSE,
    mFont_TAG_COM_CURSOL_JUST_SET,
    mFont_TAG_COM_CURSOL_JUST_CLR,
    mFont_TAG_COM_DEMO_NPC0_3_1,
    mFont_TAG_COM_DEMO_NPC0_3_255,
    mFont_TAG_COM_DEMO_NPC0_4_1,
    mFont_TAG_COM_DEMO_NPC0_4_255,
    mFont_TAG_COM_START_KEY_CHK,
    mFont_TAG_COM_STOP_KEY_CHK,

    mFont_TAG_COM_NUM
};

enum {
    mFont_TAG_STR_PLAYERNAME,
    mFont_TAG_STR_NPCNAME,
    mFont_TAG_STR_TAIL,
    mFont_TAG_STR_DETERMINATION,
    mFont_TAG_STR_MAIL,
    mFont_TAG_STR_COUNTRYNAME,
    mFont_TAG_STR_ISLANDNAME,
    mFont_TAG_STR_YEAR,
    mFont_TAG_STR_MOUNTH,
    mFont_TAG_STR_WEEK,
    mFont_TAG_STR_DAY,
    mFont_TAG_STR_HOUR,
    mFont_TAG_STR_MIN,
    mFont_TAG_STR_SEC,
    mFont_TAG_STR_RANDOMNUM,
    mFont_TAG_STR_AMPM,
    mFont_TAG_STR_CAPITAL,
    mFont_TAG_STR_ARTICLECUT,
    mFont_TAG_STR_FREE0,
    mFont_TAG_STR_FREE1,
    mFont_TAG_STR_FREE2,
    mFont_TAG_STR_FREE3,
    mFont_TAG_STR_FREE4,
    mFont_TAG_STR_FREE5,
    mFont_TAG_STR_FREE6,
    mFont_TAG_STR_FREE7,
    mFont_TAG_STR_FREE8,
    mFont_TAG_STR_FREE9,
    mFont_TAG_STR_FREE10,
    mFont_TAG_STR_FREE11,
    mFont_TAG_STR_FREE12,
    mFont_TAG_STR_FREE13,
    mFont_TAG_STR_FREE14,
    mFont_TAG_STR_FREE15,
    mFont_TAG_STR_FREE16,
    mFont_TAG_STR_FREE17,
    mFont_TAG_STR_FREE18,
    mFont_TAG_STR_FREE19,
    mFont_TAG_STR_ITEM0,
    mFont_TAG_STR_ITEM1,
    mFont_TAG_STR_ITEM2,
    mFont_TAG_STR_ITEM3,
    mFont_TAG_STR_ITEM4,
    mFont_TAG_STR_NPCNAMEPERSONAL,
    mFont_TAG_STR_NPCNAMETRIBE,
    mFont_TAG_STR_OPLN,
    mFont_TAG_STR_OWNISLANDNAME,
    mFont_TAG_STR_PLCLOTHTYPE,
    mFont_TAG_STR_NPCNAMEPERSONALPASS,
    mFont_TAG_STR_NPCNAMETRIBEPASS,
    mFont_TAG_STR_TRUTHTAIL,
    mFont_TAG_STR_COUNTRYNAMEKANA,

    mFont_TAG_STR_NUM
};

enum {
    mFont_TAG_PLST_DESTINY0,
    mFont_TAG_PLST_DESTINY1,
    mFont_TAG_PLST_DESTINY2,
    mFont_TAG_PLST_DESTINY3,
    mFont_TAG_PLST_DESTINY4,
    mFont_TAG_PLST_DESTINY5,
    mFont_TAG_PLST_DEMOPL_0_2,
    mFont_TAG_PLST_DEMOPL_0_253,
    mFont_TAG_PLST_DEMOPL_0_254,
    mFont_TAG_PLST_DEMOPL_0_255,

    mFont_TAG_PLST_NUM
};

enum {
    mFont_TAG_SPEC_VOICEFALSE,
    mFont_TAG_SPEC_VOICETRUE,
    mFont_TAG_SPEC_DEMONPC0_1_4,
    mFont_TAG_SPEC_DEMONPC0_7_1,
    mFont_TAG_SPEC_DEMONPC0_9_0,
    mFont_TAG_SPEC_DEMONPC0_9_1,
    mFont_TAG_SPEC_DEMONPC0_9_2,
    mFont_TAG_SPEC_DEMONPC0_9_3,
    mFont_TAG_SPEC_DEMONPC0_9_4,
    mFont_TAG_SPEC_DEMONPC0_9_5,
    mFont_TAG_SPEC_DEMONPC0_9_6,
    mFont_TAG_SPEC_DEMONPC0_9_7,

    mFont_TAG_SPEC_NUM
};

enum {
    mFont_TAG_QUEST_DEMOQ_2,
    mFont_TAG_QUEST_DEMOQ_3,
    mFont_TAG_QUEST_DEMOQ_9,
    mFont_TAG_QUEST_FRIENDUP,
    mFont_TAG_QUEST_FRIENDDOWN,
    mFont_TAG_QUEST_DEMOQ_0_2,
    mFont_TAG_QUEST_GIVEMAP,
    mFont_TAG_QUEST_DEMOQ_0_1,
    mFont_TAG_QUEST_DEMOQ_0_2B,
    mFont_TAG_QUEST_DEMOQ_0_3,
    mFont_TAG_QUEST_DEMOQ_0_4,
    mFont_TAG_QUEST_DEMOQ_0_5,
    mFont_TAG_QUEST_DEMOQ_0_6,
    mFont_TAG_QUEST_DEMOQ_0_7,
    mFont_TAG_QUEST_DEMOQ_0_8,
    mFont_TAG_QUEST_DEMOQ_0_9,
    mFont_TAG_QUEST_DEMOQ_0_10,
    mFont_TAG_QUEST_DEMOQ_0_11,
    mFont_TAG_QUEST_DEMOQ_0_12,
    mFont_TAG_QUEST_DEMOQ_1_1,
    mFont_TAG_QUEST_DEMOQ_1_2,
    mFont_TAG_QUEST_DEMOQ_4_1,
    mFont_TAG_QUEST_DEMOQ_6_1,
    mFont_TAG_QUEST_DEMOQ_7_1,
    mFont_TAG_QUEST_DEMOQ_8_1,
    mFont_TAG_QUEST_DEMOQ_8_2,
    mFont_TAG_QUEST_NNKC,

    mFont_TAG_QUEST_NUM
};

enum {
    mFont_TAG_JUMP_NEXTFORCE,
    mFont_TAG_JUMP_NEXTRANDSEC,
    mFont_TAG_JUMP_NEXTRAND2,
    mFont_TAG_JUMP_NEXTRAND3,
    mFont_TAG_JUMP_NEXTRAND4,
    mFont_TAG_JUMP_IFSJ,
    mFont_TAG_JUMP_IFJJ,
    mFont_TAG_JUMP_IFSX,
    mFont_TAG_JUMP_IFTL,
    mFont_TAG_JUMP_IFHL,
    mFont_TAG_JUMP_IFBL,
    mFont_TAG_JUMP_IFIL,
    mFont_TAG_JUMP_IFIC,
    mFont_TAG_JUMP_IFFFC,
    mFont_TAG_JUMP_IFPN,
    mFont_TAG_JUMP_IFDJ,
    mFont_TAG_JUMP_IFKJ,
    mFont_TAG_JUMP_IFGK,
    mFont_TAG_JUMP_IFMT,
    mFont_TAG_JUMP_IFDA,
    mFont_TAG_JUMP_IFTM,
    mFont_TAG_JUMP_IFWJ,
    mFont_TAG_JUMP_IFHF,
    mFont_TAG_JUMP_IFMD,
    mFont_TAG_JUMP_IFSD,
    mFont_TAG_JUMP_IFPL,
    mFont_TAG_JUMP_IFMO,
    mFont_TAG_JUMP_CHKBKEY,
    mFont_TAG_JUMP_CHKALLKEY,
    mFont_TAG_JUMP_HAPPY,

    mFont_TAG_JUMP_NUM
};

enum {
    mFont_TAG_TALK3_3PBJ,
    mFont_TAG_TALK3_QUEST_7_2,
    mFont_TAG_TALK3_DEMONPC0_5_2,
    mFont_TAG_TALK3_DEMONPC0_5_1,
    mFont_TAG_TALK3_DEMONPC2_5_2,
    mFont_TAG_TALK3_DEMONPC2_5_1,
    mFont_TAG_TALK3_DEMOQ_9_5,
    mFont_TAG_TALK3_DEMONPC0_5_3,
    mFont_TAG_TALK3_DEMONPC0_6_2,
    mFont_TAG_TALK3_DEMONPC0_6_1,

    mFont_TAG_TALK3_NUM
};

enum {
    mFont_TAG_BODY_DEMONPC0_5_1,
    mFont_TAG_BODY_DEMONPC0_5_2,
    mFont_TAG_BODY_DEMONPC0_5_3,
    mFont_TAG_BODY_DEMONPC0_6_1,
    mFont_TAG_BODY_DEMONPC0_6_2,
    mFont_TAG_BODY_DEMONPC0_6_3,

    mFont_TAG_BODY_NUM
};

enum {
    mFont_TAG_NPC_EM_SUB_FUN,
    mFont_TAG_NPC_EM_SUB_ANGRY,
    mFont_TAG_NPC_EM_SUB_SAD,
    mFont_TAG_NPC_EM_SUB_SLEEPY,
    mFont_TAG_NPC_EM_SUB_NORMAL,
    mFont_TAG_NPC_EM_SUB_GLOOMY,
    mFont_TAG_NPC_EM_SUB_CONTINUE,

    mFont_TAG_NPC_EM_SUB_NUM
};

enum {
    mFont_TAG_BODY_SUB_DEMONPC2_5_1,
    mFont_TAG_BODY_SUB_DEMONPC2_5_2,
    mFont_TAG_BODY_SUB_DEMONPC2_5_3,
    mFont_TAG_BODY_SUB_DEMONPC2_6_1,
    mFont_TAG_BODY_SUB_DEMONPC2_6_2,
    mFont_TAG_BODY_SUB_DEMONPC2_6_3,

    mFont_TAG_BODY_SUB_NUM
};

enum {
    mFont_TAG_SOUND_VOICENORMAL,
    mFont_TAG_SOUND_VOICEANGRY,
    mFont_TAG_SOUND_VOICESAD,
    mFont_TAG_SOUND_VOICEFUN,
    mFont_TAG_SOUND_VOICESLEEPY,
    mFont_TAG_SOUND_VOICEGLOOMY,
    mFont_TAG_SOUND_MINDON,
    mFont_TAG_SOUND_MINDOFF,
    mFont_TAG_SOUND_SE_0,
    mFont_TAG_SOUND_SE_1,
    mFont_TAG_SOUND_SE_2,
    mFont_TAG_SOUND_SE_3,
    mFont_TAG_SOUND_SE_4,
    mFont_TAG_SOUND_SE_5,
    mFont_TAG_SOUND_SE_6,
    mFont_TAG_SOUND_SE_7,
    mFont_TAG_SOUND_SE_8,
    mFont_TAG_SOUND_NOSEPAGE,
    mFont_TAG_SOUND_BGMDELETE,
    mFont_TAG_SOUND_BGMMAKE,

    mFont_TAG_SOUND_NUM
};

enum {
    mFont_TEX_TYPE_FONT1,

    mFont_TEX_TYPE_NUM
};

#define mFont_CHAR_FLAG_CUT 1
#define mFont_CHAR_FLAG_USE_POLY 2
#define mFont_CHAR_FLAG_SCALE 4
#define mFont_CHAR_FLAG_SCALE_RESET 8

/* sizeof(struct font_char_s) == 0x40 */
typedef struct font_char_s {
    /* 0x00 */ u8* char_p;
    /* 0x04 */ s8 len;
    /* 0x05 */ u8 flags;
    /* 0x06 */ u8 pad0[2];
    /* 0x08 */ xy_t position;
    /* 0x10 */ xy_t scale;
    /* 0x18 */ xy_t inv_scale;
    /* 0x20 */ xy_t scaled_size;
    /* 0x28 */ xy_t inv_scaled_size;
    /* 0x30 */ f32 ofs_y;
    /* 0x34 */ rgba_t color;
    /* 0x38 */ u8 color_ctr;
    /* 0x39 */ u8 pad1[3];
    /* 0x3C */ f32 width;
} mFontChar;

#define mFont_SENTENCE_FLAG_CUT (1 << 0)
#define mFont_SENTENCE_FLAG_REVERT (1 << 1)
#define mFont_SENTENCE_FLAG_USE_POLY (1 << 2)
#define mFont_SENTENCE_FLAG_3 (1 << 3)
#define mFont_SENTENCE_FLAG_NO_COMBINE (1 << 4)
#define mFont_SENTENCE_FLAG_NO_COLOR (1 << 5)
#define mFont_SENTENCE_SKIP_DRAW_NEW_LINE (1 << 6)
#define mFont_SENTENCE_FLAG_VOICE_SE (1 << 7)
#define mFont_SENTENCE_FLAG_8 (1 << 8)
#define mFont_SENTENCE_FLAG_FONT_KIGOU (1 << 9)
#define mFont_SENTENCE_FLAG_10 (1 << 10)
#define mFont_SENTENCE_FLAG_11 (1 << 11)

/* sizeof(struct font_sentence_s) == 0xA4 */
typedef struct font_sentence_s {
    /* 0x00 */ u8* sentence_p;
    /* 0x04 */ int len;
    /* 0x08 */ u32 flags;
    /* 0x0C */ xy_t position;
    /* 0x14 */ int line_type;
    /* 0x18 */ rgba_t color;
    /* 0x1C */ xy_t scale;
    /* 0x24 */ xy_t inv_scale;
    /* 0x2C */ int now_idx;
    /* 0x30 */ f32 offset;
    /* 0x34 */ f32 width;
    /* 0x38 */ f32 line_scale;
    /* 0x3C */ f32 inv_line_scale;
    /* 0x40 */ int se_pos;
    /* 0x44 */ s16 se_character_id;
    /* 0x46 */ u8 voice_idx;
    /* 0x47 */ u8 voice2_idx;
    /* 0x48 */ u8 voice3_idx;
    /* 0x49 */ u8 pad[3];
    /* 0x4C */ mFontChar character;
} mFontSentence;

#define mFont_TEX_CHAR_WIDTH 12
#define mFont_TEX_CHAR_HEIGHT 16

#define mFont_TEX_CHAR_WIDTH_HIRES 24
#define mFont_TEX_CHAR_HEIGHT_HIRES 32

#define mFont_TEX_CHAR_WIDTH_F32 12.0f
#define mFont_TEX_CHAR_HEIGHT_F32 16.0f

#define mFont_TEX_CHAR_WIDTH_F32_HIRES 24.0f
#define mFont_TEX_CHAR_HEIGHT_F32_HIRES 32.0f

#define mFont_SCALE_F 16.0f

typedef void (*mFont_ControlCodeCharFunc)(mFontChar*, Gfx**);
typedef void (*mFont_ControlCodeSentenceFunc)(mFontSentence*, Gfx**);

extern void mFont_ct();
extern int mFont_UnintToString(u8* str, int figure, u32 num, int figure_start, int left_cut, int fill_zero,
                               int separator);
extern int mFont_char_save_data_check(u8 c);
extern u8 mFont_small_to_capital(u8 small);
extern int mFont_GetCodeWidth(u8 c, int cut);
extern int mFont_GetCodeWidthB(u8 c, int cut, int no_offset);
extern float mFont_GetCodeWidthF(u8 c, int cut);
extern float mFont_GetCodeWidthFB(u8 c, int cut, int no_offset);
extern int mFont_GetStringWidth(u8* str, int len, int cut);
extern int mFont_GetStringWidth2(u8* str, int len, int cut);
extern float mFont_GetStringWidth2F(const u8* str, int len, int cut);
extern int mFontW_CodeSize_get(const u16* code_p);
extern int mFont_GetCodeWidthW(u16 c, int cut);
extern float mFont_GetCodeWidthWF(u16 c, int cut);
extern int mFont_GetStringWidthW(const u16* str, int len, int cut);
extern void mFont_CopyStringsW(u16* dst, const u16* src, int len);
extern void mFont_ClearStringsW(u16* str, int len, u16 c);
extern int mFont_CodeSize_get(const u8* str);
extern int mFont_CodeSize_idx_get(const u8* str, int idx);
extern int mFont_cont_attr_get(int cont_code);
extern void mFont_gppSetMode(Gfx** gfx_pp);
extern void mFont_SetMode(GRAPH* graph, int mode);
extern void mFont_SetPrimColor(GRAPH* graph, int r, int g, int b, int a, int mode);
extern void mFont_SetCombineMode(GRAPH* graph, int revert_flag, int mode);
extern f32 mFont_SetVertexRectangle(GAME* game, f32 x, f32 y, int s, int t, f32 scale_x, f32 scale_y, int mode);
extern f32 mFont_SetLineStrings_AndSpace(GAME* game, u8* str, int len, f32 x, f32 y, int r, int g, int b, int a,
                                         int flag_revert, int flag_cut, int unused, f32 scale_x, f32 scale_y, int mode);
extern f32 mFont_SetLineStrings(GAME* game, u8* str, int len, f32 x, f32 y, int r, int g, int b, int a, int flag_revert,
                                int flag_cut, f32 scale_x, f32 scale_y, int mode);
extern f32 mFont_SetLineStringsW(GAME* game, u16* str, int len, f32 x, f32 y, int r, int g, int b, int a,
                                 int flag_revert, int flag_cut, f32 scale_x, f32 scale_y, int mode);
extern void mFont_CulcOrthoMatrix(Mtx* m);
extern void mFont_SetMatrix(GRAPH* graph, int mode);
extern void mFont_UnSetMatrix(GRAPH* graph, int mode);
extern void mFont_Main_start(GRAPH* graph);
extern void mFontSentence_set(mFontSentence* this, u8* sentence_p, int len, u32 flags, const xy_t* pos, int line_type,
                              const xy_t* scale, const rgba_t* color, int se_voice_pos, u8 voice_idx, u8 voice2_idx, u8 voice3_idx, s16 voice_se_character_idx);
extern void mFontSentence_gppDraw(mFontSentence* this, GAME* game, Gfx** gfx_pp);
extern f32 mFont_SetMarkChar(GAME* game, u8 mark_type, f32 x, f32 y, int r, int g, int b, int a, int revert_flag,
                             f32 scale_x, f32 scale_y, int mode);
extern void mFont_gppSetRectMode(Gfx** gfx_pp);
extern void mFont_Change_RubyToKana(u8* str, int len);

extern void mFont_KanjiLevel_debug(gfxprint_t* gfxprint);
extern int mFont_GetKanjiLevel_debug(void);
extern void mFont_CopyStrings(u8* dst, u8* src, int len);

extern int mFont_Check_Tag(u8 c);
extern u8 mFont_Get_TagSize(const u8* str);
extern int mFont_Get_TagGroup(const u8* str);
extern int mFont_Get_TagId(const u8* str);
extern int mFont_Check_TagId(const u8* str, int args, int group, int id);
extern u8 mFont_Get_TagPrmU8(const u8* str);
extern u16 mFont_Get_TagPrmU16(const u8* str);
extern void mFont_Get_TagPrmU16U16(const u8* str, u16* prm0, u16* prm1);
extern void mFont_Get_TagPrmU16U16U16(const u8* str, u16* prm0, u16* prm1, u16* prm2);
extern void mFont_Get_TagPrmU16U16U16U16(const u8* str, u16* prm0, u16* prm1, u16* prm2, u16* prm3);
extern void mFont_Get_TagPrmU8U16(const u8* str, u8* prm0, u16* prm1);
extern void mFont_Get_TagPrmU8U16U16(const u8* str, u8* prm0, u16* prm1, u16* prm2);

extern int mFont_Check_Cont(u8 c);
extern int mFont_Check_ContId(const u8* str, int cont_id);
extern u8 mFont_Get_ContPrmU8(const u8* str);

extern void mFont_CurrentScale_init(void);
extern void mFont_CurrentScale_pop(void);
extern void mFont_CurrentScale_push(void);
extern void mFont_CurrentScale_set(float scale);
extern float mFont_CurrentScale_get(void);

extern void mFont_CurrentColor_init(void);
extern void mFont_CurrentColor_pop(void);
extern void mFont_CurrentColor_push(void);
extern void mFont_CurrentColor_set(u32 color);
extern int mFont_CurrentColor_get(rgba_t* color);

#ifdef __cplusplus
}
#endif

#endif
