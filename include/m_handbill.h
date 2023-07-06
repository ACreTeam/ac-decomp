#ifndef M_HANDBILL_H
#define M_HANDBILL_H

#include "types.h"
#include "m_mail.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mHandbill_HEADER_LEN MAIL_HEADER_LEN
#define mHandbill_FOOTER_LEN MAIL_FOOTER_LEN
#define mHandbill_BODY_LEN MAIL_BODY_LEN

extern void mHandbill_Load_HandbillFromRom(u8* header, int* header_back_pos, u8* footer, u8* body, int handbill_no);
extern void mHandbill_Load_HandbillFromRom2(u8* header, int header_size, int* header_back_pos, u8* footer, int footer_size, u8* body, int handbill_no);
extern void mHandbill_Set_free_str(int free_str_no, u8* str, int str_len);
extern void mHandbill_Set_free_str_art(int free_str_no, u8* str, int str_len, int article_no);

#ifdef __cplusplus
}
#endif

#endif
