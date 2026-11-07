#include "m_handbill.h"

#include "jsyswrap.h"
#include "m_msg.h"
#include "m_string.h"
#include "m_font.h"
#include "m_common_data.h"
#include "libultra/libultra.h"

enum {
    mHandbill_SUPER_BUFFER_SIZE = 230,
    mHandbill_PS_BUFFER_SIZE = 237,
    mHandbill_MAIL_BUFFER_SIZE = 442,
    mHandbill_MAIL_PART_BUFFER_SIZE = 400,
    mHandbill_COMBINED_MAIL_BUFFER_SIZE = 450
};

static u32 Ps_table_rom_start;
static u32 Ps_rom_start;
static u32 Handbill_table_rom_start;
static u32 Handbill_rom_start;
static u32 Super_table_rom_start;
static u32 Super_rom_start;
static u32 Handbillz_rom_start;
static u32 Handbillz_start;

static void mHandbillz_aram_init();

extern void mHandbill_aram_init() {
    Ps_rom_start = JW_GetAramAddress(RESOURCE_PS);
    Handbill_rom_start = JW_GetAramAddress(RESOURCE_MAIL);
    Super_rom_start = JW_GetAramAddress(RESOURCE_SUPER);
    Handbillz_start = 0;

    mHandbillz_aram_init();
}

static mHandbill_Data_c mHandbill_data;

static void mHandbill_clr_force_art() {
    mHandbill_data.force_art = mHandbill_ARTICLE_DEFAULT;
}

static void mHandbill_clr_capital_flag() {
    mHandbill_data.capital_flag = FALSE;
}

static void mHandbill_load_init() {
    mHandbill_clr_force_art();
    mHandbill_clr_capital_flag();
}

static void mHandbill_Set_free_str_init(int str_no, int article_indef, int article_def, int gender) {
    mHandbill_String_c* string = &mHandbill_data.free_str[str_no];

    mem_clear(string->str, mHandbill_FREE_STR_LEN, CHAR_SPACE);
    string->article_indef = article_indef;
    string->article_def = article_def;
    string->gender = gender;
}

static void mHandbill_Set_free_str_sub(int str_no, u8* str, u32 str_len) {
    if (str_no >= mHandbill_FREE_STR0 && str_no < mHandbill_FREE_STR_NUM && str != NULL) {
        mHandbill_String_c* string = &mHandbill_data.free_str[str_no];
        u32 i = 0;
        u8 buffer[mHandbill_TAG_BUFFER_SIZE];

        mem_clear(buffer, sizeof(buffer), CHAR_SPACE);
        if (str_len > sizeof(buffer)) {
            str_len = sizeof(buffer);
        }
        bcopy(str, buffer, str_len);
        while (i < sizeof(buffer)) {
            u8* data_p = buffer + i;
            char code = *data_p;
            int code_size = mFont_CodeSize_get(data_p);
            int found = FALSE;
            if ((u8)code == CHAR_MESSAGE_TAG) {
                mFont_Get_TagGroup(data_p);
                mFont_Get_TagId(data_p);
                if (mFont_Check_TagId(data_p, 3 * sizeof(u8), mFont_TAG_GROUP_GRM, mFont_TAG_GRM_STRING_INFO)) {
                    string->gender = data_p[mFont_TAG_HEADER_SIZE];
                    string->article_indef = (s8)data_p[mFont_TAG_HEADER_SIZE + 1] + 1;
                    string->article_def = (s8)data_p[mFont_TAG_HEADER_SIZE + 2] + 1;
                    mHandbill_MoveDataCut(buffer, sizeof(buffer), i, i + code_size, sizeof(buffer),
                                          mHandbill_FILL_SPACE);
                    found = TRUE;
                }
            }
            if (!found) {
                i += code_size;
            }
        }
        bcopy(buffer, string->str, mHandbill_FREE_STR_LEN);
    }
}

extern void mHandbill_Set_free_str(int str_num, u8* str, int str_len) {
    mHandbill_Set_free_str_init(str_num, mIN_ARTICLE_NONE, mIN_ARTICLE_NONE, GENDER_UNSPECIFIED);
    mHandbill_Set_free_str_sub(str_num, str, str_len);
}

extern void mHandbill_Set_free_str_art2(int str_num, u8* str, int str_len, int article_indef, int article_def,
                                        int gender) {
    mHandbill_Set_free_str_init(str_num, article_indef, article_def, gender);
    mHandbill_Set_free_str_sub(str_num, str, str_len);
}

extern void mHandbill_Set_free_str_npc(int str_num, u8* str, int str_len, int gender) {
    mHandbill_Set_free_str_init(str_num, mIN_ARTICLE_NONE, mIN_ARTICLE_NONE, gender);
    mHandbill_Set_free_str_sub(str_num, str, str_len);
}

static void mHandbill_CopyString(u8* dst, const u8* src, int len) {
    int i;

    for (i = 0; i < len; i++) {
        *dst++ = *src++;
    }
}

extern int mHandbill_MoveDataCut(u8* data, int buf_size, int dst_idx, int src_idx, int data_len, int fill_type) {
    int new_len = data_len;

    if (dst_idx < src_idx) {
        for (; src_idx < data_len; src_idx++) {
            data[dst_idx] = data[src_idx];
            dst_idx++;
        }

        new_len -= src_idx - dst_idx;

        if (fill_type != mHandbill_FILL_NONE) {
            u8 fill_char;

            if (fill_type == mHandbill_FILL_RETURN) {
                fill_char = CHAR_NEW_LINE;
            } else {
                fill_char = CHAR_SPACE;
            }

            while (dst_idx < data_len) {
                data[dst_idx++] = fill_char;
            }
        }
    } else if (dst_idx > src_idx) {
        int move_size = data_len - src_idx;
        int i;
        u8* dst;
        u8* src;

        new_len += dst_idx - src_idx;
        if (new_len > buf_size) {
            data_len -= new_len - buf_size;
            move_size -= new_len - buf_size;
            new_len = buf_size;
        }

        dst = data + new_len - 1;
        src = data + data_len - 1;
        for (i = 0; i < move_size; i++) {
            *dst-- = *src--;
        }
    }

    return new_len;
}

static int mHandbill_Put_String_FREE(u8* str, int buf_size, int start_idx, int str_len, int str_no, int fill_type) {
    int code_size;
    mHandbill_String_c* string;
    int free_str_len;
    int cut_len;
    int article;

    if (str_no < 0 || str_no >= mHandbill_FREE_STR_NUM) {
        str_no = mHandbill_FREE_STR0;
    }
    string = &mHandbill_data.free_str[str_no];
    code_size = mFont_CodeSize_idx_get(str, start_idx);
    free_str_len = mMsg_Get_Length_String(string->str, mHandbill_FREE_STR_LEN);
    cut_len = mHandbill_MoveDataCut(str, buf_size, start_idx + free_str_len, start_idx + code_size, str_len, fill_type);
    if (cut_len >= buf_size && free_str_len > buf_size - start_idx) {
        free_str_len = buf_size - start_idx;
    }
    mHandbill_CopyString(&str[start_idx], string->str, free_str_len);
    if (mHandbill_data.force_art == mHandbill_ARTICLE_DEFAULT) {
        article = string->article_indef;
    } else if (mHandbill_data.force_art == mHandbill_ARTICLE_DEFINITE) {
        article = string->article_def;
    } else {
        article = mIN_ARTICLE_NONE;
    }
    if (article > mIN_ARTICLE_NONE) {
        u8 article_buf[mString_DEFAULT_STR_SIZE + 1];
        u8* article_buf_p = article_buf;
        int article_len;

        mString_Load_StringFromRom(article_buf_p, mString_DEFAULT_STR_SIZE, mString_ARTICLE_START + article);
        article_len = mMsg_Get_Length_String(article_buf_p, mString_DEFAULT_STR_SIZE);
        if (article_len > 0 && article_buf[article_len - 1] != CHAR_APOSTROPHE) {
            article_buf[article_len] = CHAR_SPACE;
            article_len++;
        }
        cut_len = mHandbill_MoveDataCut(str, buf_size, start_idx + article_len, start_idx, cut_len, fill_type);
        mHandbill_CopyString(&str[start_idx], article_buf_p, article_len);
    }
    if (mHandbill_data.capital_flag) {
        str[start_idx] = mFont_small_to_capital(str[start_idx]);
    }
    mHandbill_clr_force_art();
    mHandbill_clr_capital_flag();
    return cut_len;
}

static int mHandbill_Put_String_FREE0(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR0, fill_type);
}

static int mHandbill_Put_String_FREE1(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR1, fill_type);
}

static int mHandbill_Put_String_FREE2(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR2, fill_type);
}

static int mHandbill_Put_String_FREE3(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR3, fill_type);
}

static int mHandbill_Put_String_FREE4(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR4, fill_type);
}

static int mHandbill_Put_String_FREE5(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR5, fill_type);
}

static int mHandbill_Put_String_FREE6(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR6, fill_type);
}

static int mHandbill_Put_String_FREE7(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR7, fill_type);
}

static int mHandbill_Put_String_FREE8(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR8, fill_type);
}

static int mHandbill_Put_String_FREE9(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR9, fill_type);
}

static int mHandbill_Put_String_FREE10(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR10, fill_type);
}

static int mHandbill_Put_String_FREE11(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR11, fill_type);
}

static int mHandbill_Put_String_FREE12(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR12, fill_type);
}

static int mHandbill_Put_String_FREE13(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR13, fill_type);
}

static int mHandbill_Put_String_FREE14(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR14, fill_type);
}

static int mHandbill_Put_String_FREE15(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR15, fill_type);
}

static int mHandbill_Put_String_FREE16(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR16, fill_type);
}

static int mHandbill_Put_String_FREE17(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR17, fill_type);
}

static int mHandbill_Put_String_FREE18(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR18, fill_type);
}

static int mHandbill_Put_String_FREE19(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE(buf, buf_size, start_idx, str_len, mHandbill_FREE_STR19, fill_type);
}

static int mHandbill_Cut_Article(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    int code_size = mFont_CodeSize_idx_get(buf, start_idx);

    mHandbill_data.force_art = mHandbill_ARTICLE_SUPPRESS;
    return mHandbill_MoveDataCut(buf, buf_size, start_idx, start_idx + code_size, str_len,
                                 fill_type); // remove the control code characters
}

static int mHandbill_Capital_Letter(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    int code_size = mFont_CodeSize_idx_get(buf, start_idx);

    mHandbill_data.capital_flag = TRUE;
    return mHandbill_MoveDataCut(buf, buf_size, start_idx, start_idx + code_size, str_len,
                                 fill_type); // remove the control code characters
}

typedef int (*mHandbill_PUT_STRING_PROC)(u8*, int, int, int, int);

static int mHandbill_ContPut_String(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    static const mHandbill_PUT_STRING_PROC proc[mFont_CONT_CODE_NUM] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &mHandbill_Put_String_FREE0,
        &mHandbill_Put_String_FREE1,
        &mHandbill_Put_String_FREE2,
        &mHandbill_Put_String_FREE3,
        &mHandbill_Put_String_FREE4,
        &mHandbill_Put_String_FREE5,
        &mHandbill_Put_String_FREE6,
        &mHandbill_Put_String_FREE7,
        &mHandbill_Put_String_FREE8,
        &mHandbill_Put_String_FREE9,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &mHandbill_Put_String_FREE10,
        &mHandbill_Put_String_FREE11,
        &mHandbill_Put_String_FREE12,
        &mHandbill_Put_String_FREE13,
        &mHandbill_Put_String_FREE14,
        &mHandbill_Put_String_FREE15,
        &mHandbill_Put_String_FREE16,
        &mHandbill_Put_String_FREE17,
        &mHandbill_Put_String_FREE18,
        &mHandbill_Put_String_FREE19,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &mHandbill_Cut_Article,
        &mHandbill_Capital_Letter,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };

    int type = buf[start_idx + 1];
    if (type >= mFont_CONT_CODE_BEGIN && type < mFont_CONT_CODE_NUM) {
        mHandbill_PUT_STRING_PROC p = proc[type];

        if (p != NULL) {
            return (*p)(buf, buf_size, start_idx, str_len, fill_type);
        }
    }

    return str_len;
}

static int mHandbill_Str_Capital(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Capital_Letter(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Str_ArticleCut(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Cut_Article(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Str_Free0(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE0(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Str_Free1(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE1(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Str_Free2(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE2(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Str_Free3(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE3(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Str_Free4(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE4(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Str_Free5(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE5(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Str_Free6(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE6(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Str_Free7(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE7(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Str_Free8(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE8(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Str_Free9(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE9(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Str_Free10(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE10(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Str_Free11(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE11(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Str_Free12(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE12(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Str_Free13(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE13(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Str_Free14(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE14(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Str_Free15(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE15(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Str_Free16(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE16(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Str_Free17(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE17(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Str_Free18(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE18(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Str_Free19(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Put_String_FREE19(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_InflectGender(u8* data, int buf_size, int start_idx, int len, int fill_type, int gender) {
    u8* tag = data + start_idx;
    u8* alternatives = tag + mFont_TAG_HEADER_SIZE;
    int tag_size = mFont_Get_TagSize(tag);
    int alternatives_len = tag_size - mFont_TAG_HEADER_SIZE;
    int i;
    int variant;
    u8* form;
    u8* form_p;
    int form_len;

    if (gender == GENDER_UNSPECIFIED) {
        gender = GENDER_DEFAULT;
    }

    for (i = 0, variant = 0; variant < gender && i < alternatives_len; i++) {
        if (alternatives[i] == mFont_TAG_GRM_SEPARATOR) {
            variant++;
        }
    }

    form = alternatives + i;
    form_p = form;
    for (form_len = 0; i < alternatives_len; i++) {
        if (*form_p == mFont_TAG_GRM_SEPARATOR) {
            break;
        }
        form_p++;
        form_len++;
    }

    mHandbill_CopyString(tag, form, form_len);
    return mHandbill_MoveDataCut(data, buf_size, start_idx + form_len, start_idx + tag_size, len, fill_type);
}

static int mHandbill_Grm_ArtDef(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    int code_size = mFont_CodeSize_idx_get(buf, start_idx);

    mHandbill_data.force_art = mHandbill_ARTICLE_DEFINITE;
    return mHandbill_MoveDataCut(buf, buf_size, start_idx, start_idx + code_size, str_len, fill_type);
}

static int mHandbill_Grm_ArtNon(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Str_ArticleCut(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Grm_Capital(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_Str_Capital(buf, buf_size, start_idx, str_len, fill_type);
}

static int mHandbill_Grm_InflectPl(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    Private_c* player = Common_Get(now_private);
    int gender;

    if (player != NULL) {
        if (player->gender == mPr_SEX_MALE) {
            gender = mPr_SEX_MALE;
        } else {
            gender = mPr_SEX_FEMALE;
        }
    } else {
        gender = mPr_SEX_FEMALE;
    }
    return mHandbill_InflectGender(buf, buf_size, start_idx, str_len, fill_type, gender);
}

static int mHandbill_Grm_InflectFree0(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_InflectGender(buf, buf_size, start_idx, str_len, fill_type,
                                   mHandbill_data.free_str[mHandbill_FREE_STR0].gender);
}

static int mHandbill_Grm_InflectFree1(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_InflectGender(buf, buf_size, start_idx, str_len, fill_type,
                                   mHandbill_data.free_str[mHandbill_FREE_STR1].gender);
}

static int mHandbill_Grm_InflectFree2(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_InflectGender(buf, buf_size, start_idx, str_len, fill_type,
                                   mHandbill_data.free_str[mHandbill_FREE_STR2].gender);
}

static int mHandbill_Grm_InflectFree3(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_InflectGender(buf, buf_size, start_idx, str_len, fill_type,
                                   mHandbill_data.free_str[mHandbill_FREE_STR3].gender);
}

static int mHandbill_Grm_InflectFree4(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_InflectGender(buf, buf_size, start_idx, str_len, fill_type,
                                   mHandbill_data.free_str[mHandbill_FREE_STR4].gender);
}

static int mHandbill_Grm_InflectFree5(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_InflectGender(buf, buf_size, start_idx, str_len, fill_type,
                                   mHandbill_data.free_str[mHandbill_FREE_STR5].gender);
}

static int mHandbill_Grm_InflectFree6(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_InflectGender(buf, buf_size, start_idx, str_len, fill_type,
                                   mHandbill_data.free_str[mHandbill_FREE_STR6].gender);
}

static int mHandbill_Grm_InflectFree7(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_InflectGender(buf, buf_size, start_idx, str_len, fill_type,
                                   mHandbill_data.free_str[mHandbill_FREE_STR7].gender);
}

static int mHandbill_Grm_InflectFree8(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_InflectGender(buf, buf_size, start_idx, str_len, fill_type,
                                   mHandbill_data.free_str[mHandbill_FREE_STR8].gender);
}

static int mHandbill_Grm_InflectFree9(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_InflectGender(buf, buf_size, start_idx, str_len, fill_type,
                                   mHandbill_data.free_str[mHandbill_FREE_STR9].gender);
}

static int mHandbill_Grm_InflectFree10(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_InflectGender(buf, buf_size, start_idx, str_len, fill_type,
                                   mHandbill_data.free_str[mHandbill_FREE_STR10].gender);
}

static int mHandbill_Grm_InflectFree11(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_InflectGender(buf, buf_size, start_idx, str_len, fill_type,
                                   mHandbill_data.free_str[mHandbill_FREE_STR11].gender);
}

static int mHandbill_Grm_InflectFree12(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_InflectGender(buf, buf_size, start_idx, str_len, fill_type,
                                   mHandbill_data.free_str[mHandbill_FREE_STR12].gender);
}

static int mHandbill_Grm_InflectFree13(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_InflectGender(buf, buf_size, start_idx, str_len, fill_type,
                                   mHandbill_data.free_str[mHandbill_FREE_STR13].gender);
}

static int mHandbill_Grm_InflectFree14(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_InflectGender(buf, buf_size, start_idx, str_len, fill_type,
                                   mHandbill_data.free_str[mHandbill_FREE_STR14].gender);
}

static int mHandbill_Grm_InflectFree15(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_InflectGender(buf, buf_size, start_idx, str_len, fill_type,
                                   mHandbill_data.free_str[mHandbill_FREE_STR15].gender);
}

static int mHandbill_Grm_InflectFree16(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_InflectGender(buf, buf_size, start_idx, str_len, fill_type,
                                   mHandbill_data.free_str[mHandbill_FREE_STR16].gender);
}

static int mHandbill_Grm_InflectFree17(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_InflectGender(buf, buf_size, start_idx, str_len, fill_type,
                                   mHandbill_data.free_str[mHandbill_FREE_STR17].gender);
}

static int mHandbill_Grm_InflectFree18(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_InflectGender(buf, buf_size, start_idx, str_len, fill_type,
                                   mHandbill_data.free_str[mHandbill_FREE_STR18].gender);
}

static int mHandbill_Grm_InflectFree19(u8* buf, int buf_size, int start_idx, int str_len, int fill_type) {
    return mHandbill_InflectGender(buf, buf_size, start_idx, str_len, fill_type,
                                   mHandbill_data.free_str[mHandbill_FREE_STR19].gender);
}

static int mHandbill_TagPut_String(u8* buf, int buf_size, int* start_idx, int str_len, int fill_type) {
    static const mHandbill_PUT_STRING_PROC str_proc[mFont_TAG_STR_NUM] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &mHandbill_Str_Capital,
        &mHandbill_Str_ArticleCut,
        &mHandbill_Str_Free0,
        &mHandbill_Str_Free1,
        &mHandbill_Str_Free2,
        &mHandbill_Str_Free3,
        &mHandbill_Str_Free4,
        &mHandbill_Str_Free5,
        &mHandbill_Str_Free6,
        &mHandbill_Str_Free7,
        &mHandbill_Str_Free8,
        &mHandbill_Str_Free9,
        &mHandbill_Str_Free10,
        &mHandbill_Str_Free11,
        &mHandbill_Str_Free12,
        &mHandbill_Str_Free13,
        &mHandbill_Str_Free14,
        &mHandbill_Str_Free15,
        &mHandbill_Str_Free16,
        &mHandbill_Str_Free17,
        &mHandbill_Str_Free18,
        &mHandbill_Str_Free19,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };

    static const mHandbill_PUT_STRING_PROC grm_proc[mFont_TAG_GRM_NUM] = {
        &mHandbill_Grm_ArtDef,
        &mHandbill_Grm_ArtNon,
        &mHandbill_Grm_Capital,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &mHandbill_Grm_InflectPl,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        &mHandbill_Grm_InflectFree0,
        &mHandbill_Grm_InflectFree1,
        &mHandbill_Grm_InflectFree2,
        &mHandbill_Grm_InflectFree3,
        &mHandbill_Grm_InflectFree4,
        &mHandbill_Grm_InflectFree5,
        &mHandbill_Grm_InflectFree6,
        &mHandbill_Grm_InflectFree7,
        &mHandbill_Grm_InflectFree8,
        &mHandbill_Grm_InflectFree9,
        &mHandbill_Grm_InflectFree10,
        &mHandbill_Grm_InflectFree11,
        &mHandbill_Grm_InflectFree12,
        &mHandbill_Grm_InflectFree13,
        &mHandbill_Grm_InflectFree14,
        &mHandbill_Grm_InflectFree15,
        &mHandbill_Grm_InflectFree16,
        &mHandbill_Grm_InflectFree17,
        &mHandbill_Grm_InflectFree18,
        &mHandbill_Grm_InflectFree19,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };

    u8* src = buf + *start_idx;
    int group = mFont_Get_TagGroup(src);
    int id = mFont_Get_TagId(src);
    mHandbill_PUT_STRING_PROC p = NULL;

    if (group == mFont_TAG_GROUP_STR) {
        int size = mFont_Get_TagSize(src); // @unused
        p = str_proc[id];
    } else if (group == mFont_TAG_GROUP_GRM) {
        p = grm_proc[id];
    }

    if (p != NULL) {
        return (*p)(buf, buf_size, *start_idx, str_len, fill_type);
    } else {
        int size = mFont_Get_TagSize(src);

        *start_idx += size;
    }

    return str_len;
}

static int mHandbill_Change_ControlCode(u8* buf, int buf_size, int str_len, int fill_type) {
    int pos = 0;
    int len = str_len;

    while (pos < len && pos < buf_size) {
        if (buf[pos] == CHAR_CONTROL_CODE) {
            len = mHandbill_ContPut_String(buf, buf_size, pos, len, fill_type);
        } else if (buf[pos] == CHAR_MESSAGE_TAG) {
            len = mHandbill_TagPut_String(buf, buf_size, &pos, len, fill_type);
        } else {
            pos++;
        }
    }

    return len;
}

static void mHandbill_Change_ControlCode2(u8* buf, int buf_size, int str_len, int* header_back_start, int fill_type) {
    int now_str_len;

    int pos = 0;
    int len = str_len;

    while (pos < len && pos < buf_size) {
        if (buf[pos] == CHAR_CONTROL_CODE) {
            now_str_len = len;
            len = mHandbill_ContPut_String(buf, buf_size, pos, len, fill_type);

            if (pos < *header_back_start) {
                *header_back_start += len - now_str_len;
            }
        } else if (buf[pos] == CHAR_MESSAGE_TAG) {
            now_str_len = len;
            len = mHandbill_TagPut_String(buf, buf_size, &pos, len, fill_type);

            if (pos < *header_back_start) {
                *header_back_start += len - now_str_len;
            }
        } else {
            pos++;
        }
    }
}

static void mHandbill_CheckSuperStringBorderAndCopy(u8* dst, int dst_size, int* header_back_start, u8* src,
                                                    int src_size) {
    int i;
    int lines;
    int dst_pos;
    int char_size;
    int newline;

    lines = 0;
    dst_pos = 0;

    for (i = 0, char_size = 0; i < src_size; i++) {
        newline = FALSE;
        if (char_size > 0) {
            char_size--;
        } else {
            newline = *src == CHAR_NEW_LINE;
            if (newline) {
                *header_back_start = i;
                lines++;
            } else if (*src == CHAR_CONTROL_CODE || *src == CHAR_MESSAGE_TAG) {
                char_size = mFont_CodeSize_get(src) - 1;
            }
        }

        if (newline == FALSE && dst_pos < dst_size) {
            *dst = *src;
            dst++;
            dst_pos++;
        }

        src++;
    }

    if (lines == 0) {
        *header_back_start = 0;
    } else if (lines != 1) {
        *header_back_start = src_size;
    }
}

static void mHandbill_Load_SuperStringFromRom(u8* buf, u32 buf_size, int* header_back_start, int super_no) {
    u8 tmp_buf[mHandbill_SUPER_BUFFER_SIZE];
    mMsg_bmg_info_c bmg_info;
    int tmp_header_back_start;

    mem_clear(buf, buf_size, CHAR_SPACE);
    mem_clear(tmp_buf, sizeof(tmp_buf), CHAR_SPACE);
    mMsgLoad_bmg_init(&bmg_info, Super_rom_start, super_no, tmp_buf, sizeof(tmp_buf));
    mMsgLoad_bmg_load(&bmg_info);
    mMsgLoad_clr_buff(CHAR_SPACE);
    mHandbill_CheckSuperStringBorderAndCopy(mMsgLoad_get_buff(), mMsgLoad_get_buffSize(), &tmp_header_back_start,
                                            tmp_buf, bmg_info.load_size);
    mHandbill_Change_ControlCode2(mMsgLoad_get_buff(), mMsgLoad_get_buffSize(), bmg_info.load_size - 1,
                                  &tmp_header_back_start, mHandbill_FILL_SPACE);
    bcopy(mMsgLoad_get_buff(), buf, buf_size);
    *header_back_start = tmp_header_back_start;
}

static void mHandbill_Load_PsStringFromRom(u8* buf, u32 buf_size, int ps_no) {
    u8 tmp_buf[mHandbill_PS_BUFFER_SIZE];
    mMsg_bmg_info_c bmg_info;

    mem_clear(buf, buf_size, CHAR_SPACE);
    mem_clear(tmp_buf, sizeof(tmp_buf), CHAR_SPACE);
    mMsgLoad_bmg_init(&bmg_info, Ps_rom_start, ps_no, tmp_buf, sizeof(tmp_buf));
    mMsgLoad_bmg_load(&bmg_info);
    mHandbill_Change_ControlCode(tmp_buf, sizeof(tmp_buf), bmg_info.load_size, mHandbill_FILL_SPACE);
    bcopy(tmp_buf, buf, buf_size);
}

static void mHandbill_Load_MailFromRom(u8* buf, int mail_no) {
    u8 tmp_buf[mHandbill_MAIL_BUFFER_SIZE];
    mMsg_bmg_info_c bmg_info;

    mem_clear(tmp_buf, sizeof(tmp_buf), CHAR_NEW_LINE);
    mMsgLoad_bmg_init(&bmg_info, Handbill_rom_start, mail_no, tmp_buf, sizeof(tmp_buf));
    mMsgLoad_bmg_load(&bmg_info);
    mHandbill_Change_ControlCode(tmp_buf, sizeof(tmp_buf), bmg_info.load_size, mHandbill_FILL_RETURN);
    mFont_CopyStrings(buf, tmp_buf, mHandbill_BODY_LEN);
}

extern void mHandbill_Load_HandbillFromRom(u8* header, int* header_back_start, u8* footer, u8* body, int mail_no) {
    mHandbill_load_init();
    mHandbill_Load_SuperStringFromRom(header, mHandbill_HEADER_LEN, header_back_start, mail_no);
    mHandbill_Load_PsStringFromRom(footer, mHandbill_FOOTER_LEN, mail_no);
    mHandbill_Load_MailFromRom(body, mail_no);
}

extern void mHandbill_Load_HandbillFromRom2(u8* header, int header_size, int* header_back_start, u8* footer,
                                            int footer_size, u8* body, int mail_no) {
    mHandbill_load_init();
    mHandbill_Load_SuperStringFromRom(header, header_size, header_back_start, mail_no);
    mHandbill_Load_PsStringFromRom(footer, footer_size, mail_no);
    mHandbill_Load_MailFromRom(body, mail_no);
}

static u32 mHandbillz_table_pos[mHandbillz_TYPE_NUM];
static u32 mHandbillz_data_pos[mHandbillz_TYPE_NUM];

static void mHandbillz_aram_init() {
    mHandbillz_data_pos[mHandbillz_TYPE_SUPER] = JW_GetAramAddress(RESOURCE_SUPERZ);
    mHandbillz_data_pos[mHandbillz_TYPE_MAILA] = JW_GetAramAddress(RESOURCE_MAILA);
    mHandbillz_data_pos[mHandbillz_TYPE_MAILB] = JW_GetAramAddress(RESOURCE_MAILB);
    mHandbillz_data_pos[mHandbillz_TYPE_MAILC] = JW_GetAramAddress(RESOURCE_MAILC);
    mHandbillz_data_pos[mHandbillz_TYPE_PS] = JW_GetAramAddress(RESOURCE_PSZ);
}

static int mHandbillz_super_load(mHandbillz_Info_c* info) {
    u8 tmp_buf[mHandbill_SUPER_BUFFER_SIZE];
    mMsg_bmg_info_c bmg_info;
    int tmp_header_back_start;

    mem_clear(tmp_buf, sizeof(tmp_buf), CHAR_SPACE);
    mMsgLoad_bmg_init(&bmg_info, mHandbillz_data_pos[mHandbillz_TYPE_SUPER], info->super_no, tmp_buf, sizeof(tmp_buf));
    mMsgLoad_bmg_load(&bmg_info);
    mMsgLoad_clr_buff(CHAR_SPACE);
    mHandbill_CheckSuperStringBorderAndCopy(mMsgLoad_get_buff(), mMsgLoad_get_buffSize(), &tmp_header_back_start,
                                            tmp_buf, bmg_info.load_size);
    mHandbill_Change_ControlCode2(mMsgLoad_get_buff(), mMsgLoad_get_buffSize(), bmg_info.load_size - 1,
                                  &tmp_header_back_start, mHandbill_FILL_SPACE);
    mem_clear(info->super_buf_p, info->super_buf_size, CHAR_SPACE);
    bcopy(mMsgLoad_get_buff(), info->super_buf_p, info->super_buf_size);
    info->header_back_start = tmp_header_back_start;
    return TRUE;
}

static int mHandbillz_mail_load(mHandbillz_Info_c* info) {
    mMsg_bmg_info_c bmg_info;
    int dma_info[3];
    u8 tmp_buf[mHandbill_MAIL_PART_BUFFER_SIZE];
    u8 mail_buf[mHandbill_COMBINED_MAIL_BUFFER_SIZE];
    int success = TRUE;
    u32 total_size;
    u32 current_size;
    int i;

    dma_info[mHandbillz_TYPE_MAILA - 1] = info->maila_no;
    dma_info[mHandbillz_TYPE_MAILB - 1] = info->mailb_no;
    dma_info[mHandbillz_TYPE_MAILC - 1] = info->mailc_no;
    mem_clear(info->mail_buf_p, info->mail_buf_size, CHAR_NEW_LINE);
    mem_clear(mail_buf, sizeof(mail_buf), CHAR_NEW_LINE);

    for (i = 0, total_size = 0; i < ARRAY_COUNT(dma_info); i++) {
        u32 load_size;

        mMsgLoad_bmg_init(&bmg_info, mHandbillz_data_pos[mHandbillz_TYPE_MAILA + i], dma_info[i], tmp_buf,
                          sizeof(tmp_buf));
        mMsgLoad_bmg_load(&bmg_info);
        current_size = total_size + bmg_info.load_size;

        if (current_size < sizeof(mail_buf)) {
            load_size = bmg_info.load_size;
        } else {
            load_size = info->mail_buf_size - total_size;
            success = FALSE;
        }

        bcopy(tmp_buf, mail_buf + total_size, load_size);
        total_size = current_size;
    }

    if (success) {
        u32 size;
        u32 processed_size;

        processed_size = mHandbill_Change_ControlCode(mail_buf, sizeof(mail_buf), total_size, mHandbill_FILL_RETURN);

        if (processed_size < info->mail_buf_size) {
            size = processed_size;
        } else {
            size = info->mail_buf_size;
            for (i = info->mail_buf_size; i < (int)sizeof(mail_buf); i++) {
                if (mail_buf[i] != CHAR_NEW_LINE) {
                    success = FALSE;
                    break;
                }
            }
        }

        bcopy(mail_buf, info->mail_buf_p, size);
    }

    return success;
}

static int mHandbillz_ps_load(mHandbillz_Info_c* info) {
    mMsg_bmg_info_c bmg_info;
    u8 tmp_buf[mHandbill_PS_BUFFER_SIZE];
    int ret;
    u32 copy_size;

    mem_clear(tmp_buf, sizeof(tmp_buf), CHAR_SPACE);
    mMsgLoad_bmg_init(&bmg_info, mHandbillz_data_pos[mHandbillz_TYPE_PS], info->ps_no, tmp_buf, sizeof(tmp_buf));
    ret = mMsgLoad_bmg_load(&bmg_info);
    mHandbill_Change_ControlCode(tmp_buf, sizeof(tmp_buf), bmg_info.load_size, mHandbill_FILL_SPACE);
    copy_size = info->ps_buf_size;
    if (copy_size > sizeof(tmp_buf)) {
        copy_size = sizeof(tmp_buf);
    }
    mem_clear(info->ps_buf_p, info->ps_buf_size, CHAR_SPACE);
    bcopy(tmp_buf, info->ps_buf_p, copy_size);
    return ret;
}

extern int mHandbillz_load(mHandbillz_Info_c* info) {
    int super_res;
    int mail_res;
    int ps_res;
    int res;

    mHandbill_load_init();

    super_res = mHandbillz_super_load(info);
    mail_res = mHandbillz_mail_load(info);
    ps_res = mHandbillz_ps_load(info);
    res = FALSE;

    if (super_res && mail_res && ps_res) {
        res = TRUE;
    }

    return res;
}
