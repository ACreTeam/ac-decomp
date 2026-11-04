#ifndef FAMICOMPRIV_H
#define FAMICOMPRIV_H

#include "types.h"
#include "Famicom/famicom.h"
#include "Famicom/ks_nes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof (FamicomCommon) == 0xB8 */
typedef struct FamicomCommon {
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
    /* 0x2C */ u8 nesrom_memcard; // TRUE: rom is loaded from memcard, FALSE: rom is loaded internally
    /* 0x2D */ u8 rom_no;
    /* 0x2E */ s8 save_pl_no;
    /* 0x2F */ u8 mura_save_name[33];
    /* 0x50 */ u8 famicom_save_name[33];
    /* 0x74 */ FamicomSaveDataHeader* save_data_header;
    /* 0x78 */ u8* internal_save_datap;
    /* 0x7C */ size_t save_data_total_size;
    /* 0x80 */ size_t save_data_single_size;
    /* 0x84 */ int _84;
    /* 0x88 */ u8* save_data_name;
    /* 0x8C */ u8 _8C;
    /* 0x8D */ u8 low_res_mode;
    /* 0x8E */ MemcardGameHeader_t memcard_game_header;
    /* 0xB0 */ u8* memcard_save_comment;
    /* 0xB4 */ size_t unused_save_data_start_ofs;
} FamicomCommon;

extern Famicom_MallocInfo* my_malloc_current;
extern u8 save_game_image;
extern u8** nesrom_filename_ptrs;

extern u32 nesinfo_tags_size;
extern u8* nesinfo_tags_start;
extern u8* nesinfo_tags_end;

extern u32 nesinfo_data_size;
extern u8* nesinfo_data_start;
extern u8* nesinfo_data_end;

extern u8 InputValid[];
extern u32 InputData[];
extern u32 InputButton[];
extern u32 InputTrigger[];
extern u32 InputRepeat[];
extern u32 InputRepeatCount[];

extern u8 tcs_bad;
extern u8 ics_bad;

extern FamicomCommon famicomCommon;

#ifdef __cplusplus
}
#endif

#endif /* FAMICOMPRIV_H */
