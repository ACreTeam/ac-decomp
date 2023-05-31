#ifndef FAMICOM_H
#define FAMICOM_H

#include "types.h"

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

typedef struct famicom_common_s {

} FamicomCommon;

typedef u8 (*FAMICOM_GETSAVECHAN_PROC)(int* player_no, int* slot_card_result);
extern void famicom_setCallback_getSaveChan(FAMICOM_GETSAVECHAN_PROC getSaveChan_proc);

#ifdef __cplusplus
}
#endif

#endif
