#ifndef M_CPAK_H
#define M_CPAK_H

#include "types.h"
#include "s_cpak.h"
#include "m_private.h"
#include "m_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct contpak_s {
  int _00;
  sCPk_c save_pak;
} mCPk_c;

extern int mCPk_InitPak(int pak_idx);
extern int mCPk_PakOpen(mCPk_c* cpak, int pak_idx);
extern int  mCPk_SavePak(Private_c* private_data, Animal_c* animals, mCPk_c* cpak);
extern mCPk_c* mCPk_get_pkinfo();

#ifdef __cplusplus
}
#endif

#endif
