#include "m_card.h"

#include "dolphin/private/card.h"
#include "libultra/libultra.h"
#include "m_malloc.h"
#include "libc64/sleep.h"

typedef struct card_bg_info {
    int _00;
    int _04;
    int _08;
    int _0C;
    int _10;
    int _14;
    int space_proc;
    int tries;
    int _20;
    int _24;
    int _28;
} mCD_bg_info_c;

static char mCD_file_name[] = "DobutsunomoriP_MURA";
static int l_mcd_err_debug[mCD_ERROR_NUM] = { FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE };
static s32 l_mcd_err_result = CARD_RESULT_READY;
static mCD_bg_info_c l_mcd_bg_info;

static void mCD_ClearErrInfo(void) {
    bzero(l_mcd_err_debug, sizeof(l_mcd_err_debug));
    l_mcd_err_result = 0;
}

static void mCD_OnErrInfo(int err) {
    if (err >= 0 && err < mCD_ERROR_NUM) {
        l_mcd_err_debug[err] = TRUE;
    }
}

static void mCD_OffErrInfo(int err) {
    if (err >= 0 && err < mCD_ERROR_NUM) {
        l_mcd_err_debug[err] = FALSE;
    }
}

static void mCD_SetErrResult(s32 result) {
    l_mcd_err_result = result;
}

extern void mCD_PrintErrInfo(gfxprint_t* gfxprint) {
    gfxprint_color(gfxprint, 250, 100, 250, 255);
    gfxprint_locate8x8(gfxprint, 22, 3);

    if (l_mcd_err_debug[mCD_ERROR_NOT_ENABLED]) {
        gfxprint_printf(gfxprint, "N");
    }

    if (l_mcd_err_debug[mCD_ERROR_AREA]) {
        gfxprint_printf(gfxprint, "A");
    }

    if (l_mcd_err_debug[mCD_ERROR_WRITE]) {
        gfxprint_printf(gfxprint, "W");
    }

    if (l_mcd_err_debug[mCD_ERROR_READ]) {
        gfxprint_printf(gfxprint, "R");
    }

    if (l_mcd_err_debug[mCD_ERROR_CHECKSUM]) {
        gfxprint_printf(gfxprint, "C");
    }

    if (l_mcd_err_debug[mCD_ERROR_OUTDATED]) {
        gfxprint_printf(gfxprint, "O");
    }

    if (l_mcd_err_debug[mCD_ERROR_CREATE]) {
        gfxprint_printf(gfxprint, "c");
    }

    if (l_mcd_err_result != CARD_RESULT_READY) {
        gfxprint_printf(gfxprint, "%d", l_mcd_err_result);
    }
}

static void* mCD_malloc_32(u32 size) {
    return zelda_malloc_align(size, 32);
}

static int mCD_check_card_common(s32* result, s32 req_sector_size, s32 chan) {
    s32 mem_size = 0;
    s32 sector_size = 0;
    int res = mCD_RESULT_BUSY;

    *result = CARDProbeEx(chan, &mem_size, &sector_size);

    if (*result == CARD_RESULT_READY && sector_size == req_sector_size) {
        res = mCD_RESULT_SUCCESS;
    } else if (*result != CARD_RESULT_BUSY) {
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_check_card(s32* result, s32 req_sector_size, s32 chan) {
    int ms = 0;
    int check_common_res = mCD_RESULT_BUSY;
    int res = mCD_RESULT_ERROR;

    while (check_common_res == mCD_RESULT_BUSY && ms < 500) {
        check_common_res = mCD_check_card_common(result, req_sector_size, chan);

        if (check_common_res == mCD_RESULT_BUSY) {
            msleep(1);
            ms++;
        }
    }

    if (check_common_res == mCD_RESULT_SUCCESS) {
        res = mCD_RESULT_SUCCESS;
    }

    return res;
}

static int mCD_check_sector_size(s32 req_sector_size, s32 chan) {
    s32 mem_size = 0;
    s32 sector_size = 0;
    s32 result = CARD_RESULT_BUSY;
    int ms = 0;
    int res = mCD_RESULT_BUSY;

    while (result == CARD_RESULT_BUSY && ms < 500) {
        result = CARDProbeEx(chan, &mem_size, &sector_size);

        if (result == CARD_RESULT_BUSY) {
            msleep(1);
            ms++;
        }
    }

    if (result == CARD_RESULT_READY) {
        if (req_sector_size == sector_size) {
            res = mCD_RESULT_SUCCESS;
        } else {
            res = mCD_RESULT_BUSY;
        }
    }

    return res;
}

static int mCD_get_file_num_common(s32 chan) {
    CARDFileInfo fileInfo;
    s32 num = 0;
    s32 file_no;

    for (file_no = 0; file_no < CARD_MAX_FILE; file_no++) {
        s32 result = CARDFastOpen(chan, file_no, &fileInfo);

        if (result == CARD_RESULT_READY) {
            num++;
            CARDClose(&fileInfo);
        }
    }

    return num;
}

static int mCD_get_file_num(void* workArea, s32 chan) {
    int num = 0;
    s32 result;

    if (workArea != NULL && mCD_check_card(&result, mCD_MEMCARD_SECTORSIZE, chan) == mCD_RESULT_SUCCESS) {
        result = CARDMount(chan, workArea, NULL);

        if (result == CARD_RESULT_READY || result == CARD_RESULT_BROKEN) {
            result = CARDCheck(chan);
            num = mCD_get_file_num_common(chan);
            CARDUnmount(chan);
        } else if (result == CARD_RESULT_ENCODING) {
            CARDUnmount(chan);
        }
    }

    return num;
}

extern void mCD_init_card(void) {
    CARDInit();
}

static void mCD_ClearCardBgInfo(mCD_bg_info_c* bg_info) {
    bzero(bg_info, sizeof(mCD_bg_info_c));
}

static void mCD_StartSetCardBgInfo(void) {
    mCD_ClearCardBgInfo(&l_mcd_bg_info);
}

static int mCD_get_space_bg_get_slot(s32* freeBlocks, mCD_bg_info_c* bg_info, s32 chan, s32* result, void* workArea) {
    int res;

    bg_info->tries++;
    res = mCD_check_card_common(result, mCD_MEMCARD_SECTORSIZE, chan);
    if (res == mCD_RESULT_SUCCESS && workArea != NULL) {
        *freeBlocks = 0;
        *result = CARDMountAsync(chan, workArea, NULL, NULL);

        if (*result == CARD_RESULT_ENCODING) {
            CARDUnmount(chan);
            res = mCD_RESULT_ERROR;
        } else if (*result != CARD_RESULT_READY && *result != CARD_RESULT_BROKEN) {
            res = mCD_RESULT_ERROR;
        }

        bg_info->tries = 0;
    } else if (res != mCD_RESULT_BUSY) {
        *freeBlocks = 0;
        res = mCD_RESULT_ERROR;
        bg_info->tries = 0;
    } else if (bg_info->tries >= 100) {
        *freeBlocks = 0;
        res = mCD_RESULT_ERROR;
        bg_info->tries = 0;
    }

    return res;
}

static int mCD_get_space_bg_main(s32* freeBlocks, mCD_bg_info_c* bg_info, s32 chan, s32* result, void* workArea) {
    int res = mCD_RESULT_BUSY;

    *result = CARDGetResultCode(chan);
    if (*result == CARD_RESULT_READY || *result == CARD_RESULT_BROKEN) {
        *result = CARDCheck(chan);

        if (*result == CARD_RESULT_READY) {
            s32 freeFiles;

            *result = CARDFreeBlocks(chan, freeBlocks, &freeFiles);
            if (*result == CARD_RESULT_READY) {
                res = mCD_RESULT_SUCCESS;
            } else {
                res = mCD_RESULT_ERROR;
            }
        } else {
            res = mCD_RESULT_ERROR;
        }

        CARDUnmount(chan);
    } else if (*result != CARD_RESULT_BUSY) {
        if (*result == CARD_RESULT_ENCODING) {
            CARDUnmount(chan);
        }

        res = mCD_RESULT_ERROR;
    }

    return res;
}

typedef int (*mCD_GET_SPACE_BG_PROC)(s32*, mCD_bg_info_c*, s32, s32*, void*);
static int mCD_get_space_bg(s32* freeBlocks, s32 chan, s32* result, void* workArea) {
    static mCD_GET_SPACE_BG_PROC get_proc[mCD_SPACE_BG_NUM] = { &mCD_get_space_bg_get_slot, &mCD_get_space_bg_main };
    mCD_bg_info_c* bg_info = &l_mcd_bg_info;
    u8 proc_type = bg_info->space_proc;
    int res = mCD_RESULT_BUSY;

    *freeBlocks = 0;
    if (proc_type < mCD_SPACE_BG_NUM) {
        int proc_res = (*get_proc[proc_type])(freeBlocks, bg_info, chan, result, workArea);

        if (proc_res == mCD_RESULT_SUCCESS) {
            bg_info->space_proc++;

            if (bg_info->space_proc >= mCD_SPACE_BG_NUM) {
                res = mCD_RESULT_SUCCESS;
                mCD_ClearCardBgInfo(bg_info);
            }
        } else if (proc_res != mCD_RESULT_BUSY) {
            res = mCD_RESULT_ERROR;
            mCD_ClearCardBgInfo(bg_info);
        }
    } else {
        res = mCD_RESULT_ERROR;
        mCD_ClearCardBgInfo(bg_info);
    }

    return res;
}

static void mCD_close_and_unmount(CARDFileInfo* fileInfo, s32 chan) {
    CARDClose(fileInfo);
    CARDUnmount(chan);
}

static int mCD_bg_check_slot(mCD_bg_info_c* bg_info, s32 chan, s32* result) {
    int res = mCD_RESULT_BUSY;
    int common_res = mCD_check_card_common(result, mCD_MEMCARD_SECTORSIZE, chan);

    bg_info->tries++;
    if (common_res == mCD_RESULT_SUCCESS) {
        bg_info->space_proc++;
        bg_info->tries = 0;
        res = mCD_RESULT_SUCCESS;
    } else if (common_res != mCD_RESULT_BUSY || bg_info->tries >= 100) {
        bg_info->tries = 0;
        res = mCD_RESULT_ERROR;
    }

    return res;
}

static int mCD_bg_init_com(mCD_bg_info_c* bg_info, s32 chan, s32* result, void** workArea_p, void** read_p, int read) {
    int res;

    *workArea_p = mCD_malloc_32(CARD_WORKAREA_SIZE);
    if (read == TRUE) {
        *read_p = mCD_malloc_32(mCD_MEMCARD_SECTORSIZE);
    }

    if (*workArea_p != NULL && (read == FALSE || (read == TRUE && *read_p != NULL))) {
        *result = CARDMountAsync(chan, *workArea_p, NULL, NULL);

        if (*result == CARD_RESULT_READY) {
            bg_info->space_proc++;
            res = mCD_RESULT_SUCCESS;
        } else if (*result == CARD_RESULT_BROKEN) {
            *result = CARDCheckAsync(chan, NULL);

            if (*result == CARD_RESULT_READY) {
                bg_info->space_proc++;
                res = mCD_RESULT_SUCCESS;
            } else {
                if (*result == CARD_RESULT_BROKEN || *result == CARD_RESULT_ENCODING) {
                    CARDUnmount(chan);
                }

                res = mCD_RESULT_ERROR;
            }
        } else {
            if (*result == CARD_RESULT_ENCODING) {
                CARDUnmount(chan);
            }

            res = mCD_RESULT_ERROR;
        }
    } else {
        res = mCD_RESULT_ERROR;
    }

    return res;
}
