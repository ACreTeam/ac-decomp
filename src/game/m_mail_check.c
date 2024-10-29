#include "m_mail_check.h"

#include "m_mail_check_ovl.h"

extern int mMC_get_mail_hit_rate(int* len, u8* str, GAME* game) {
  return mMck_check_key_hit(len, str);
}
