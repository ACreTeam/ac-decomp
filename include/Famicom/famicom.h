#ifndef FAMICOM_H
#define FAMICOM_H

#include "types.h"
#include "Famicom/ks_nes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void* (*MALLOC_ALIGN_FUNC)(size_t size, u32 align);
typedef void (*MALLOC_FREE_FUNC)(void* ptr);
typedef size_t (*MALLOC_GETMEMBLOCKSIZE_FUNC)(void* ptr);
typedef size_t (*MALLOC_GETTOTALFREESIZE_FUNC)();
 
typedef struct malloc_s {
  MALLOC_ALIGN_FUNC malloc_align;
  MALLOC_FREE_FUNC free;
  MALLOC_GETMEMBLOCKSIZE_FUNC getmemblocksize;
  MALLOC_GETTOTALFREESIZE_FUNC gettotalfreesize;
} Famicom_MallocInfo;

typedef struct save_data_header_s {
  u8 _temp[0x19C0];
} FamicomSaveDataHeader;

typedef struct memcard_game_header_s {
  u8 _00;
  u8 _01;
  u8 mori_name[16];
  u16 nesrom_size;
  u16 nestags_size;
  u16 icon_format;
  u16 icon_flags;
  u16 banner_size;
  u8 flags0;
  u8 flags1;
  u16 pad;
} MemcardGameHeader_t;

/* sizeof (FamicomCommon) == 0xB8 */
typedef struct famicom_common_s {
  /* 0x00 */ ksNesCommonWorkObj* wp;
  /* 0x04 */ ksNesStateObj* sp;
  /* 0x08 */ u8* nesromp;
  /* 0x0C */ u8* chrramp;
  /* 0x10 */ u8* bbramp;
  /* 0x14 */ u8* noise_bufp;
  /* 0x18 */ u8* chr_to_i8_bufp;
  /* 0x1C */ u8* result_bufp;
  /* 0x20 */ u8* highscore_flagsp;
  /* 0x24 */ u8* nesinfo_tagsp;
  /* 0x28 */ int _28;
  /* 0x2C */ u8 player_no;
  /* 0x2D */ u8 _2d;
  /* 0x2E */ u8 _2e;
  /* 0x2F */ u8 mura_save_name[33];
  /* 0x50 */ u8 famicom_save_name[33];
  /* 0x74 */ FamicomSaveDataHeader* save_data_header;
  /* 0x78 */ int _78;
  /* 0x7C */ size_t save_data_header_size;
  /* 0x80 */ size_t _80;
  /* 0x84 */ int _84;
  /* 0x88 */ u8* _88;
  /* 0x8C */ u16 _8C;
  /* 0x8E */ MemcardGameHeader_t memcard_game_header;
  /* 0xB0 */ u8* memcard_save_comment;
  /* 0xB4 */ int _b4;
} FamicomCommon;

typedef u8 (*FAMICOM_GETSAVECHAN_PROC)(int* player_no, int* slot_card_result);
extern void famicom_setCallback_getSaveChan(FAMICOM_GETSAVECHAN_PROC getSaveChan_proc);
extern int famicom_mount_archive_end_check();

#ifdef __cplusplus
}
#endif

#endif
