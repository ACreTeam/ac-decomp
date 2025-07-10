#include "m_museum.h"

#include "libultra/libultra.h"
#include "m_font.h"
#include "m_mail.h"
#include "m_handbill.h"
#include "m_private.h"
#include "m_shop.h"
#include "m_name_table.h"
#include "m_msg.h"
#include "m_field_info.h"
#include "m_random_field_h.h"
#include "m_common_data.h"

static u8 l_museum_name_str[PLAYER_NAME_LEN] = {
    CHAR_M, CHAR_u, CHAR_s, CHAR_e, CHAR_u, CHAR_m, CHAR_SPACE, CHAR_SPACE
}; /* "Museum  " */

static u8 present_name[mIN_ITEM_NAME_LEN]; /* TODO: reversed bss order */
static Mail_c l_mmsm_mail;

extern void mMsm_ClearRecord(mMsm_record_c* record) {
    bzero(record, sizeof(mMsm_record_c));
}

extern void mMsm_GetMuseumMailName(Mail_nm_c* name) {
    mPr_ClearPersonalID(&name->personalID);
    mPr_CopyPlayerName(name->personalID.player_name, l_museum_name_str);
    name->type = mMl_NAME_TYPE_MUSEUM;
}

static void mMsm_OrderInformationMail() {
    Private_c* priv = Save_Get(private_data);
    int i;

    for (i = 0; i < PLAYER_NUM; i++) {
        if (mPr_NullCheckPersonalID(&priv->player_ID) == FALSE && mPr_CheckMuseumAddress(priv) == FALSE) {
            priv->museum_record.send_info_mail = TRUE;
        }

        priv++;
    }
}

extern void mMsm_SendInformationMail() {
    Private_c* priv = Save_Get(private_data);
    int i;

    for (i = 0; i < PLAYER_NUM; i++) {
        if (mPr_NullCheckPersonalID(&priv->player_ID) == FALSE && mPr_CheckMuseumInfoMail(priv)) {
            if (mMl_send_mail_box(&priv->player_ID, i, &l_mmsm_mail, EMPTY_NO, ITM_PAPER24, mMl_MUSEUM_INFO_MAIL_NO,
                                  l_museum_name_str, mMl_DATA2) == TRUE) {
                priv->museum_record.contacted = TRUE;
                priv->museum_record.send_info_mail = FALSE;
            }
        }

        priv++;
    }
}

static void mMsm_GetFossil(mActor_name_t* fossil) {
    static int hit_table[mMsm_FOSSIL_TYPE_NUM] = { FALSE, TRUE };

    *fossil = mSP_RandomOneFossilSelect(hit_table[RANDOM(mMsm_FOSSIL_TYPE_NUM)]);
}

static int mMsm_GetFossilMailNo(mActor_name_t fossil) {
    static int mail_no_table[25] = { 0x10E, 0x110, 0x10F, 0x111, 0x113, 0x112, 0x114, 0x116, 0x115,
                                     0x117, 0x119, 0x118, 0x11A, 0x11B, 0x11C, 0x11D, 0x11E, 0x11F,
                                     0x120, 0x121, 0x126, 0x125, 0x123, 0x124, 0x122 };

    int type = 0; // invalid item

    if (fossil >= FTR_START(FTR_DIN_TRIKERA_HEAD) && fossil <= FTR_END(FTR_DIN_TRILOBITE)) {
        type = 1; // valid fossil
    }

    return mail_no_table[type != 0 ? (fossil - FTR_START(FTR_DIN_TRIKERA_HEAD)) >> 2 : 0];
}

static void mMsm_GetRemailAddIdx(int* add, int* shift, int idx) {
    *add = (idx << 2) / 8;
    *shift = idx - (*add * 2);
}

static int mMsm_Idx2RemailKind(mMsm_remail_info_c* remail_info, int idx) {
    int kind = -1;
    int add = 0;
    int shift = 0;

    if (remail_info != NULL && idx >= 0 && idx < mMsm_REMAIL_SLOTS) {
        mMsm_GetRemailAddIdx(&add, &shift, idx);
        kind = (remail_info->types[add] >> (shift << 2)) & 7;
    }

    return kind;
}

static int mMsm_GetRemailFreeIdx(mMsm_remail_info_c* remail_info) {
    int idx = -1;

    if (remail_info != NULL) {
        int i;

        for (i = 0; i < mMsm_REMAIL_SLOTS; i++) {
            int kind = mMsm_Idx2RemailKind(remail_info, i);

            if (kind == mMsm_REMAIL_KIND_CLEAR || kind >= mMsm_REMAIL_KIND_NUM) {
                idx = i;
                break;
            }
        }
    }

    return idx;
}

static void mMsm_Idx2SetRemailInfo(mMsm_remail_info_c* remail_info, int idx, int remail_type, mActor_name_t item_no) {
    int slot_idx = 0;
    int nibble = 0;

    if (remail_info != NULL && idx >= 0 && idx < mMsm_REMAIL_SLOTS) {
        int i;

        mMsm_GetRemailAddIdx(&slot_idx, &nibble, idx);
        i = slot_idx;

        if (nibble == 0) {
            u8 raw = remail_info->types[i];
            remail_info->types[i] = (raw & 0xF0) | remail_type & 7;
        } else {
            u8 raw = remail_info->types[i];
            remail_info->types[i] = (raw & 0x0F) | (remail_type & 7) << 4;
        }

        remail_info->items[idx] = item_no;
    }
}

static void mMsm_Idx2ClearRemailInfo(mMsm_remail_info_c* remail_info, int idx) {
    mMsm_Idx2SetRemailInfo(remail_info, idx, mMsm_REMAIL_KIND_CLEAR, EMPTY_NO);
}

static void mMsm_PushRemailInfo(mMsm_remail_info_c* remail_info) {
    int active = TRUE;

    if (remail_info != NULL) {
        while (active == TRUE) {
            int first_free_idx;

            active = FALSE;
            first_free_idx = mMsm_GetRemailFreeIdx(remail_info);

            if (first_free_idx != -1) {
                int used_slot_idx = first_free_idx + 1;

                /* Count up until we've found the first used slot or reach the end */
                while (used_slot_idx < mMsm_REMAIL_SLOTS) {
                    int remail_type = mMsm_Idx2RemailKind(remail_info, used_slot_idx);

                    if (remail_type > mMsm_REMAIL_KIND_CLEAR && remail_type < mMsm_REMAIL_KIND_NUM) {
                        mMsm_Idx2SetRemailInfo(remail_info, first_free_idx, remail_type,
                                               remail_info->items[used_slot_idx]);
                        mMsm_Idx2ClearRemailInfo(remail_info, used_slot_idx);
                        active = TRUE; /* Continue searching */
                        break;
                    }

                    used_slot_idx++;
                }
            }
        }
    }
}

static void mMsm_SetRemailInfo(mMsm_remail_info_c* remail_info, Private_c* priv, mActor_name_t item) {
    int kind = mMsm_REMAIL_KIND_CLEAR;

    if (item != EMPTY_NO) {
        int free_idx;
        int private_idx = mPr_GetPrivateIdx(&priv->player_ID);

        if (private_idx == -1) {
            kind = mMsm_REMAIL_KIND_FOREIGNER;
        } else {
            switch (mMmd_GetDisplayInfo(item)) {
                case mMmd_DISPLAY_CANNOT_DONATE: {
                    kind = mMsm_REMAIL_KIND_CANNOT_DONATE;
                    break;
                }

                case mMmd_DISPLAY_CAN_DONATE: {
                    kind = mMsm_REMAIL_KIND_DONATED;
                    mMmd_RequestMuseumDisplay(item);
                    break;
                }

                case mMmd_DISPLAY_ALREADY_DONATED: {
                    kind = mMsm_REMAIL_KIND_ALREADY_DONATED;
                    break;
                }
            }
        }

        free_idx = mMsm_GetRemailFreeIdx(remail_info);
        if (free_idx != -1) {
            mMsm_Idx2SetRemailInfo(remail_info, free_idx, kind, item);
        }
    }
}

static void mMsm_SendResultMail() {
    static int remail_no_table[mMsm_REMAIL_KIND_NUM - 1] = { 0x22D, 0x22B, 0x22C, 0x22E };
    // static u8 present_name[mIN_ITEM_NAME_LEN]; /* TODO: reversed bss order */

    int send_num[PLAYER_NUM];
    Private_c* priv_p = Save_Get(private_data);
    Private_c* priv = priv_p;
    mActor_name_t present;
    u8 send_flags = 0b1111;
    mActor_name_t fossil = EMPTY_NO;
    mMsm_remail_info_c* remail_info;
    int idx;
    int i;

    bzero(send_num, PLAYER_NUM * sizeof(int));

    /* Send 'remail' info */
    for (i = 0; i < PLAYER_NUM; i++) {
        if (mPr_NullCheckPersonalID(&priv->player_ID) == FALSE) {
            mMsm_record_c* record = &priv->museum_record;
            if (record->contacted == TRUE) {
                int landname_len;
                mActor_name_t item;

                remail_info = &record->remail_info;
                for (idx = 0; idx < mMsm_REMAIL_SLOTS; idx++) {
                    int remail_kind;

                    present = EMPTY_NO;
                    remail_kind = mMsm_Idx2RemailKind(remail_info, idx);

                    if (remail_kind <= mMsm_REMAIL_KIND_CLEAR || remail_kind >= mMsm_REMAIL_KIND_NUM) {
                        break; /* Reached end of populated remail slots */
                    }

                    landname_len = mMsg_Get_Length_String(Save_Get(land_info.name), LAND_NAME_SIZE);
                    mHandbill_Set_free_str(mHandbill_FREE_STR0, Save_Get(land_info.name), landname_len);

                    item = remail_info->items[idx];
                    if (item != EMPTY_NO) {
                        mIN_copy_name_str(present_name, item);
                        mHandbill_Set_free_str(mHandbill_FREE_STR1, present_name, mIN_ITEM_NAME_LEN);

                        if (remail_kind != mMsm_REMAIL_KIND_DONATED) {
                            present = remail_info->items[idx];
                        }
                    }

                    if (mMl_send_mail(&priv->player_ID, i, present, ITM_PAPER24, remail_no_table[remail_kind - 1],
                                      l_museum_name_str, mMl_DATA2)) {
                        mMsm_Idx2ClearRemailInfo(remail_info, idx);
                        send_num[i]++;

                        if (send_num[i] >= mMsm_MAX_MAIL) {
                            send_flags &= ~(1 << i);
                            break;
                        }
                    } else {
                        /* If attempted mail was unable to be received, remove this player from the send pool and stop
                         * processing */
                        send_flags &= ~(1 << i);
                        break;
                    }
                }

                mMsm_PushRemailInfo(remail_info);
            } else {
                send_flags &= ~(1 << i);
            }
        } else {
            send_flags &= ~(1 << i);
        }

        priv++;
    }

    /* Send fossil mail */
    while (send_flags != 0) {
        priv = priv_p;
        for (i = 0; i < PLAYER_NUM; i++) {
            if (((send_flags >> i) & 1) == 1) {
                mMsm_record_c* record = &priv->museum_record;
                if (record->stored_fossil_num != 0) {
                    int mail_no;

                    mMsm_GetFossil(&fossil);
                    mail_no = mMsm_GetFossilMailNo(fossil);

                    if (mMl_send_mail(&priv->player_ID, i, fossil, ITM_PAPER24, mail_no, l_museum_name_str,
                                      mMl_DATA2)) {
                        record->stored_fossil_num--;
                        send_num[i]++;

                        if (send_num[i] >= mMsm_MAX_MAIL) {
                            send_flags &= ~(1 << i);
                        }
                    } else {
                        send_flags &= ~(1 << i);
                    }
                } else {
                    send_flags &= ~(1 << i);
                }
            }

            priv++;
        }
    }
}

extern void mMsm_SendMuseumMail(Mail_c* mail) {
    Mail_nm_c* sender_name;
    Private_c* priv = NULL;

    if (mail != NULL && Common_Get(now_private) != NULL && mail->header.sender.type == mMl_NAME_TYPE_PLAYER) {
        sender_name = &mail->header.sender;

        if (mPr_NullCheckPersonalID(&sender_name->personalID) == FALSE) {
            if (mPr_CheckCmpPersonalID(&sender_name->personalID, &Common_Get(now_private)->player_ID) == TRUE) {
                priv = Common_Get(now_private);
            } else {
                int priv_idx = mPr_GetPrivateIdx(&sender_name->personalID);

                if (priv_idx != -1) {
                    priv = Save_Get(private_data + priv_idx);
                }
            }

            if (priv != NULL) {
                mActor_name_t present = mail->present;

                if (present != EMPTY_NO && present != RSV_NO) {
                    mMsm_record_c* record = &priv->museum_record;

                    if (present == ITM_FOSSIL) {
                        u8 stored_fossils = record->stored_fossil_num;

                        if (stored_fossils < mMsm_REMAIL_SLOTS) {
                            record->stored_fossil_num = stored_fossils + 1;
                        }
                    } else {
                        mMsm_SetRemailInfo(&record->remail_info, priv, present);
                        record->remail_pending = TRUE;
                    }
                }
            }
        }
    }
}

extern int mMsm_GetDepositAbleNum(mActor_name_t* fg_items, mCoBG_Collision_u* col_data) {
    int depositable_num = 0;
    int i;

    if (fg_items != NULL && col_data != NULL) {
        for (i = 0; i < UT_TOTAL_NUM; i++) {
            if (*fg_items == EMPTY_NO && mCoBG_CheckHole_OrgAttr(col_data->data.unit_attribute)) {
                depositable_num++;
            }

            fg_items++;
            col_data++;
        }
    }

    return depositable_num;
}

static int mMsm_GetDepositAbleNum_cancel(mActor_name_t* fg_items, mCoBG_Collision_u* col_data, u16* cancel_ut) {
    int depositable_num = 0;
    int ut_z;

    if (fg_items != NULL && col_data != NULL) {
        for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
            int ut_x;
            for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
                if ((((*cancel_ut) >> ut_x) & 1) != TRUE && *fg_items == EMPTY_NO &&
                    mCoBG_CheckHole_OrgAttr(col_data->data.unit_attribute)) {
                    depositable_num++;
                }

                fg_items++;
                col_data++;
            }

            cancel_ut++;
        }
    }

    return depositable_num;
}

extern void mMsm_DepositItemBlock_cancel(mActor_name_t* fg_items, mActor_name_t deposit_item,
                                         mCoBG_Collision_u* col_data, u16* deposit, u16* cancel_ut, u8 valid_ut_count) {
    int deposit_idx = RANDOM(valid_ut_count);
    int ut_z;

    for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
        int ut_x;

        for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
            if ((((*cancel_ut) >> ut_x) & 1) != TRUE && *fg_items == EMPTY_NO &&
                mCoBG_CheckHole_OrgAttr(col_data->data.unit_attribute)) {
                if (deposit_idx == 0) {
                    *fg_items = deposit_item;
                    ut_z = UT_Z_NUM; // break out of outer loop
                    *deposit |= (1 << ut_x);
                    break;
                } else {
                    deposit_idx--;
                }
            }

            fg_items++;
            col_data++;
        }

        deposit++;
        cancel_ut++;
    }
}

extern void mMsm_DepositItemBlock(mActor_name_t* fg_items, mActor_name_t item, int block_x, int block_z, u16* deposit,
                                  u8 valid_ut_count) {
    mCoBG_Collision_u* col_data = mFI_GetBkNum2ColTop(block_x, block_z);
    int deposit_idx = RANDOM(valid_ut_count);
    int ut;

    for (ut = 0; ut < UT_TOTAL_NUM; ut++) {
        if (*fg_items == EMPTY_NO && mCoBG_CheckHole_OrgAttr(col_data->data.unit_attribute)) {
            if (deposit_idx == 0) {
                int ut_x = ut & (UT_X_NUM - 1);
                int ut_z = ut >> 4;

                if (item != ITM_PITFALL) {
                    *fg_items = item;
                    deposit[ut_z] |= (1 << ut_x);
                } else {
                    int hole_num = mCoBG_BnumUnum2HoleNumber(block_x, block_z, ut_x, ut_z);

                    if (hole_num != -1) {
                        *fg_items = BURIED_PITFALL_HOLE_START + hole_num;
                    }
                }

                break;
            } else {
                deposit_idx--;
            }
        }

        fg_items++;
        col_data++;
    }
}

static void mMsm_DepositFossilBlock(mActor_name_t* fg_items, mCoBG_Collision_u* col_data, u16* deposit, u16* cancel,
                                    u8 valid_ut_count) {
    mMsm_DepositItemBlock_cancel(fg_items, ITM_FOSSIL, col_data, deposit, cancel, valid_ut_count);
}

static void mMsm_DepositFossilBlockLine(int line, u16* cancel_ut) {
    /* NOTE: line is a column (of Z-acres, for example the 1 column) */

    int depositable_acres;
    u8 depositable_line[FG_BLOCK_Z_NUM];
    u16* cancel_ut_p;
    int block_x = line + 1;
    int block_z;

    cancel_ut_p = cancel_ut;
    depositable_acres = 0;
    bzero(depositable_line, FG_BLOCK_Z_NUM * sizeof(u8));

    for (block_z = 0; block_z < FG_BLOCK_Z_NUM; block_z++) {
        int bad_acre = mFI_CheckBlockKind_OR(block_x, block_z + 1,
                                             mRF_BLOCKKIND_PLAYER | mRF_BLOCKKIND_SHRINE | mRF_BLOCKKIND_STATION |
                                                 mRF_BLOCKKIND_POOL | mRF_BLOCKKIND_DUMP);

        if (bad_acre == FALSE) {
            depositable_line[block_z] = mMsm_GetDepositAbleNum_cancel(
                Save_Get(fg[block_z][line]).items[0], mFI_GetBkNum2ColTop(block_x, block_z + 1), cancel_ut);

            if (depositable_line[block_z] != 0) {
                depositable_acres++;
            }
        }

        cancel_ut += UT_Z_NUM * FG_BLOCK_X_NUM;
    }

    if (depositable_acres > 0) {
        int selected_z_acre;

        cancel_ut = cancel_ut_p;
        selected_z_acre = RANDOM(depositable_acres);

        for (block_z = 0; block_z < FG_BLOCK_Z_NUM; block_z++) {
            if (depositable_line[block_z] != 0) {
                if (selected_z_acre == 0) {
                    mMsm_DepositFossilBlock(
                        Save_Get(fg[block_z][line]).items[0], mFI_GetBkNum2ColTop(block_x, block_z + 1),
                        Save_Get(deposit[line + block_z * FG_BLOCK_X_NUM]), cancel_ut, depositable_line[block_z]);
                    return;
                } else {
                    selected_z_acre--;
                }
            }

            cancel_ut += UT_Z_NUM * FG_BLOCK_X_NUM;
        }
    }
}

extern int mMsm_RecordDepositFossil(u8* record, mActor_name_t item, int block_x) {
    int res = FALSE;

    if (item == ITM_FOSSIL) {
        *record |= (1 << block_x);
        res = TRUE;
    }

    return res;
}

extern u8 mMsm_GetDepositBlockNum(u8 record) {
    u8 deposit_block_num = 0;
    int block_x;

    for (block_x = 0; block_x < FG_BLOCK_X_NUM; block_x++) {
        if (((record >> (block_x + 1)) & 1) == TRUE) {
            deposit_block_num++;
        }
    }

    return deposit_block_num;
}

extern void mMsm_DepositFossil(u8 deposit_record, int fossil_count, u16* cancel_ut, int send_order_info) {
    int deposit_count;
    u16* cancel_ut_p = cancel_ut;
    u8 already_deposited = mMsm_GetDepositBlockNum(deposit_record);
    u8 available_blocks;

    if (fossil_count < mMsm_DEPOSIT_FOSSIL_MAX) {
        deposit_count = mMsm_DEPOSIT_FOSSIL_MAX - fossil_count;
        available_blocks = FG_BLOCK_X_NUM - already_deposited;

        while (deposit_count > 0 && available_blocks != 0) {
            int selected_row;
            int block_x;

            cancel_ut = cancel_ut_p;
            selected_row = RANDOM(available_blocks);

            for (block_x = 0; block_x < FG_BLOCK_X_NUM; block_x++) {
                if (((deposit_record >> (block_x + 1)) & 1) == FALSE) {
                    if (selected_row <= 0) {
                        mMsm_DepositFossilBlockLine(block_x, cancel_ut);
                        available_blocks--;
                        deposit_record |= (1 << (block_x + 1));
                        break;
                    } else {
                        selected_row--;
                    }
                }

                cancel_ut += UT_Z_NUM;
            }

            deposit_count--;
        }

        if (send_order_info) {
            mMsm_OrderInformationMail();
        }
    }

    mMsm_SendResultMail();
    mMsm_SendInformationMail();
}

static void mMsm_SetPrivateCompMail(Private_c* priv, int flag) {
    if (priv != NULL) {
        priv->state_flags |= flag;
    }
}

static int mMsm_CheckSendCompMail() {
    Private_c* priv = Save_Get(private_data);
    int res = FALSE;
    int i;

    for (i = 0; i < PLAYER_NUM; i++) {
        if (mPr_NullCheckPersonalID(&priv->player_ID) == FALSE &&
            (priv->state_flags & mPr_FLAG_MUSEUM_COMP_HANDBILL_SCHEDULED)) {
            res = TRUE;
            break;
        }

        priv++;
    }

    return res;
}

static void mMsm_SetSendCompMail() {
    Private_c* priv = Save_Get(private_data);
    int i;

    for (i = 0; i < PLAYER_NUM; i++) {
        if (mPr_NullCheckPersonalID(&priv->player_ID) == FALSE) {
            mMsm_SetPrivateCompMail(priv, mPr_FLAG_MUSEUM_COMP_HANDBILL_SCHEDULED);
        }

        priv++;
    }
}

extern void mMsm_SetCompMail() {
    if (mMsm_CheckSendCompMail() == FALSE && mMmd_CountDisplayedFossil() == mMmd_FOSSIL_NUM &&
        mMmd_CountDisplayedArt() == mMmd_ART_NUM && mMmd_CountDisplayedInsect() == mMmd_INSECT_NUM &&
        mMmd_CountDisplayedFish() == mMmd_FISH_NUM) {
        mMsm_SetSendCompMail();
    }
}

extern void mMsm_SendCompMail() {
    Private_c* priv = Save_Get(private_data);
    int state_flags;
    int i;

    for (i = 0; i < PLAYER_NUM; i++) {
        state_flags = priv->state_flags;
        if (mPr_NullCheckPersonalID(&priv->player_ID) == FALSE) {
            /* Send completion letter & reward if scheduled but not yet received. */

            if ((state_flags & mPr_FLAG_MUSEUM_COMP_HANDBILL_SCHEDULED) != 0 &&
                (state_flags & mPr_FLAG_MUSEUM_COMP_HANDBILL_RECEIVED) == 0) {
                int land_name_len = mMsg_Get_Length_String(Save_Get(land_info.name), LAND_NAME_SIZE);

                mHandbill_Set_free_str(mHandbill_FREE_STR0, Save_Get(land_info.name), land_name_len);

                if (mMl_send_mail_postoffice(&priv->player_ID, i, FTR_START(FTR_NOG_MUSEUM), ITM_PAPER24, 0x22F,
                                             l_museum_name_str, mMl_DATA2, mMl_TYPE_MAIL) == TRUE) {
                    mMsm_SetPrivateCompMail(priv, mPr_FLAG_MUSEUM_COMP_HANDBILL_RECEIVED);
                }
            }
        }

        priv++;
    }
}
