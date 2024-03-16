#ifndef M_HANDBILL_H
#define M_HANDBILL_H

#include "types.h"
#include "m_mail.h"
#include "m_item_name.h"
#include "m_handbill_data.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mHandbill_HEADER_LEN MAIL_HEADER_LEN
#define mHandbill_FOOTER_LEN MAIL_FOOTER_LEN
#define mHandbill_BODY_LEN MAIL_BODY_LEN

#define mHandbill_FREE_STR_LEN mIN_ITEM_NAME_LEN

#define mHandbill_MAIL_NUM 982

enum {
    mHandbill_FREE_STR0,
    mHandbill_FREE_STR1,
    mHandbill_FREE_STR2,
    mHandbill_FREE_STR3,
    mHandbill_FREE_STR4,
    mHandbill_FREE_STR5,
    mHandbill_FREE_STR6,
    mHandbill_FREE_STR7,
    mHandbill_FREE_STR8,
    mHandbill_FREE_STR9,
    mHandbill_FREE_STR10,
    mHandbill_FREE_STR11,
    mHandbill_FREE_STR12,
    mHandbill_FREE_STR13,
    mHandbill_FREE_STR14,
    mHandbill_FREE_STR15,
    mHandbill_FREE_STR16,
    mHandbill_FREE_STR17,
    mHandbill_FREE_STR18,
    mHandbill_FREE_STR19,

    mHandbill_FREE_STR_NUM
};

enum {
    mHandbill_FILL_NONE,
    mHandbill_FILL_RETURN,
    mHandbill_FILL_SPACE,

    mHandbill_FILL_NUM
};

typedef struct handbill_data_s mHandbill_Data_c;

struct handbill_data_s {
    u8 free_str[mHandbill_FREE_STR_NUM][mHandbill_FREE_STR_LEN];
    int free_str_art[mHandbill_FREE_STR_NUM];
    int force_art;
    int capital_flag;
};

extern void mHandbill_aram_init();
extern void mHandbill_Set_free_str(int str_num, u8* str, int str_len);
extern void mHandbill_Set_free_str_art(int str_num, u8* str, int str_len, int article);
extern int mHandbill_MoveDataCut(u8* data, int buf_size, int dst_idx, int src_idx, int data_len, int fill_type);
extern void mHandbill_Load_HandbillFromRom(u8* header, int* header_back_start, u8* footer, u8* body, int mail_no);
extern void mHandbill_Load_HandbillFromRom2(u8* header, int header_size, int* header_back_start, u8* footer,
                                            int footer_size, u8* body, int mail_no);

enum {
    mHandbillz_TYPE_SUPER,
    mHandbillz_TYPE_MAILA,
    mHandbillz_TYPE_MAILB,
    mHandbillz_TYPE_MAILC,
    mHandbillz_TYPE_PS,

    mHandbillz_TYPE_NUM
};

typedef struct mHandbillz_info_s {
    u8* super_buf_p;
    size_t super_buf_size;

    u8* mail_buf_p;
    size_t mail_buf_size;

    u8* ps_buf_p;
    size_t ps_buf_size;

    int super_no;
    int maila_no;
    int mailb_no;
    int mailc_no;
    int ps_no;

    int header_back_start;
} mHandbillz_Info_c;

extern int mHandbillz_load(mHandbillz_Info_c* info);

#ifdef __cplusplus
}
#endif

#endif
