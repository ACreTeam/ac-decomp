#ifndef FAMICOM_H
#define FAMICOM_H

#include "types.h"
#include "Famicom/ks_nes.h"
#include "terminal.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FAMICOM_SAVE_HEADER_SIZE 0x40
#define FAMICOM_INTERNAL_ROM_NUM 19

#define NESTAG_CMD_SIZE 3
#define NESTAG_SIZE (NESTAG_CMD_SIZE + 1)

#define NESTAG_END "END"
#define NESTAG_VEQ "VEQ"
#define NESTAG_VNE "VNE"
#define NESTAG_GID "GID"
#define NESTAG_GNM "GNM"
#define NESTAG_CPN "CPN"
#define NESTAG_OFS "OFS" /* Offset into the shared highscore data to read/write at */
#define NESTAG_HSC "HSC"
#define NESTAG_GNO "GNO"
#define NESTAG_BBR "BBR"
#define NESTAG_QDS "QDS"
#define NESTAG_SPE "SPE"
#define NESTAG_TCS "TCS"
#define NESTAG_ICS "ICS"
#define NESTAG_ESZ "ESZ"
#define NESTAG_ROM "ROM"
#define NESTAG_MOV "MOV"
#define NESTAG_NHD "NHD"
#define NESTAG_DIF "DIF"
#define NESTAG_PAT "PAT"
#define NESTAG_PAD "PAD"
#define NESTAG_FIL "FIL"
#define NESTAG_ISZ "ISZ"
#define NESTAG_IFM "IFM"
#define NESTAG_REM "REM"
#define NESTAG_APL "APL"
#define NESTAG_FGN "FGN"

typedef void* (*MALLOC_ALIGN_FUNC)(size_t size, u32 align);
typedef void (*MALLOC_FREE_FUNC)(void* ptr);
typedef int (*MALLOC_GETMEMBLOCKSIZE_FUNC)(void* ptr);
typedef int (*MALLOC_GETTOTALFREESIZE_FUNC)();

typedef struct malloc_s {
    MALLOC_ALIGN_FUNC malloc_align;
    MALLOC_FREE_FUNC free;
    MALLOC_GETMEMBLOCKSIZE_FUNC getmemblocksize;
    MALLOC_GETTOTALFREESIZE_FUNC gettotalfreesize;
} Famicom_MallocInfo;

enum filer_demo_mode {
    FILER_DEMO_MODE_NORMAL,
    FILER_DEMO_MODE_AUTO,

    FILER_DEMO_MODE_NUM
};

#define FAMICOM_SAVE_DATA_NAME_LEN 8
#define FAMICOM_MORI_NAME_LEN 16

typedef struct FamicomSaveDataHeader {
    u8 name[FAMICOM_SAVE_DATA_NAME_LEN];
    u8 _08;
    u8 _09;
    u8 headerSize;
    u8 checksum;
    u16 size;
    u8 no_save;
    u8 _temp[FAMICOM_SAVE_HEADER_SIZE - 0x000F];
} FamicomSaveDataHeader;

enum {
    MEMCARD_COMMENT_TYPE_NONE,
    MEMCARD_COMMENT_TYPE_DEFAULT,
    MEMCARD_COMMENT_TYPE_COPY_ROM,     // converts rom's comment but converts "] ROM" to "] SAVE"
    MEMCARD_COMMENT_TYPE_COPY_EMBEDDED // uses the embedded and unique 'save' comment
};

enum {
    MEMCARD_BANNER_TYPE_NONE,
    MEMCARD_BANNER_TYPE_DEFAULT,
    MEMCARD_BANNER_TYPE_COPY_ROM,     // copies the NES rom save's banner
    MEMCARD_BANNER_TYPE_COPY_EMBEDDED // uses the embedded and unique 'save' banner
};

enum {
    MEMCARD_ICON_TYPE_NONE,
    MEMCARD_ICON_TYPE_DEFAULT,
    MEMCARD_ICON_TYPE_COPY_ROM,     // copies the NES rom save's icon
    MEMCARD_ICON_TYPE_COPY_EMBEDDED // uses the embedded and unique 'save' icon
};

enum {
    FAMICOM_RESULT_OK,
    FAMICOM_RESULT_NOSPACE,
    FAMICOM_RESULT_NOENTRY,
    FAMICOM_RESULT_BROKEN,
    FAMICOM_RESULT_WRONGDEVICE,
    FAMICOM_RESULT_WRONGENCODING,
    FAMICOM_RESULT_NOCARD,
    FAMICOM_RESULT_NOFILE
};

typedef struct MemcardGameHeader_t {
    u8 _00;
    u8 _01;
    u8 mori_name[FAMICOM_MORI_NAME_LEN];
    u16 nesrom_size;
    u16 nestags_size;
    u16 icon_format;
    u16 icon_flags;
    u16 comment_img_size; /* Size of comment + banner + icon */
    struct {
        u8 has_comment_img : 1;
        u8 comment_type : 2;
        u8 banner_type : 2;
        u8 icon_type : 2;
        u8 no_copy_flag : 1;
    } flags0;
    struct {
        u8 no_move_flag : 1;
        u8 banner_fmt : 2;
        u8 reserved : 5;
    } flags1;
    u16 pad;
} MemcardGameHeader_t;

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

typedef int (*FAMICOM_GETSAVECHAN_PROC)(int* player_no, s32* slot_card_result);

extern int famicom_getErrorChan();
extern void famicom_setCallback_getSaveChan(FAMICOM_GETSAVECHAN_PROC proc);
extern int famicom_mount_archive_end_check();
extern void famicom_mount_archive();
extern int famicom_init(int rom_idx, Famicom_MallocInfo* malloc_info, int player_no);
extern int famicom_cleanup();
extern void famicom_1frame();
extern int famicom_rom_load_check();
extern int famicom_internal_data_load();
extern int famicom_internal_data_save();
extern int famicom_external_data_save();
extern int famicom_external_data_save_check();
extern int famicom_get_disksystem_titles(int* n_games, char* title_name_bufp, int namebuf_size);

extern void nesinfo_tags_set(int rom_no);
extern void nesinfo_tag_process1(u8* save_data, int mode, u32* max_ofs_p);
extern void nesinfo_tag_process2();
extern void nesinfo_tag_process3(u8* save_data);
extern void nesinfo_update_highscore(u8* save_data, int mode);
extern int nesinfo_get_highscore_num();
extern u8* nesinfo_get_moriName();
extern void nesinfo_init();
extern void highscore_setup_flags(u8* flags);

#ifdef __cplusplus
}
#endif

#endif
