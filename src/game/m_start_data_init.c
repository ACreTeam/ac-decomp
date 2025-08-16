#include "m_start_data_init.h"

#include "m_all_grow.h"
#include "m_name_table.h"
#include "m_house.h"
#include "m_string.h"
#include "m_font.h"
#include "m_field_info.h"
#include "m_field_make.h"
#include "m_scene_table.h"
#include "libultra/libultra.h"
#include "m_cockroach.h"
#include "m_melody.h"
#include "m_play.h"
#include "m_npc.h"
#include "m_room_type.h"
#include "m_huusui_room.h"
#include "m_mark_room.h"
#include "m_eappli.h"
#include "m_quest.h"
#include "m_name_table.h"
#include "m_train_control.h"
#include "m_notice.h"
#include "m_event.h"
#include "m_common_data.h"
#include "m_design_ovl.h"

static void famicom_emu_initial_common_data() {
    // stubbed
}

static void decide_fruit(mActor_name_t* fruit_p) {
    *fruit_p = RANDOM(mAGrw_FRUIT_NUM) | ITM_FOOD_START;
}

static void decide_fish_location(u8* location) {
    *location = RANDOM(3);
}

static void title_game_haniwa_data_init() {
    static int haniwa_msg[4] = { mString_HANIWA_MSG0, mString_HANIWA_MSG1, mString_HANIWA_MSG2, mString_HANIWA_MSG3 };
    u8 haniwa_buf[HANIWA_MESSAGE_LEN];

    int line_len;
    int haniwa_msg_len;
    int i;
    int j;
    Haniwa_c* haniwa;
    mHm_hs_c* house;
    u8* dst;

    /* Load message line-by-line */
    dst = haniwa_buf;
    haniwa_msg_len = 0;
    for (i = 0; i < 4; i++) {

        mString_Load_StringFromRom(dst, HANIWA_MESSAGE_LEN - haniwa_msg_len, haniwa_msg[i]);
        line_len = mMl_strlen(dst, HANIWA_MESSAGE_LEN - haniwa_msg_len, CHAR_SPACE);

        if (i < 3) {
            dst[line_len] = CHAR_NEW_LINE;
            haniwa_msg_len += line_len + 1;
            dst += line_len + 1;
        }
    }

    for (i = 0; i < mHS_HOUSE_NUM; i++) {
        haniwa = &Save_Get(homes + i)->haniwa;
        house = Save_Get(homes + i);

        /* Copy default message */
        mem_copy(house->haniwa.message, haniwa_buf, HANIWA_MESSAGE_LEN);

        /* Clear held items */
        for (j = 0; j < HANIWA_ITEM_HOLD_NUM; j++) {
            haniwa->items[j].item = EMPTY_NO;
        }

        haniwa->bells = 0;
    }
}

static void mSDI_ClearMoneyPlayerHomeStationBlock() {
    static int block_num[2][2] = {
        { 2, 1 }, /* Player home */
        { 2, 0 }  /* Station */
    };

    int block_z;
    int block_x;
    mActor_name_t* items;
    u16* deposit;
    int ut_x;
    int ut_z;
    mActor_name_t item;
    int i;

    for (i = 0; i < 2; i++) {
        block_z = block_num[i][1];
        block_x = block_num[i][0];

        items = Save_Get(fg[block_z][block_x]).items[0];
        deposit = Save_Get(deposit[block_z * FG_BLOCK_X_NUM + block_x]);

        if (items != NULL) {
            for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
                for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
                    item = *items;

                    if (item >= ITM_MONEY_START && item <= ITM_MONEY_END) {
                        mPB_keep_item(item);
                        *items = EMPTY_NO;

                        if (deposit != NULL) {
                            mFI_BlockDepositOFF(deposit, ut_x, ut_z);
                        }
                    }

                    items++;
                }
            }
        }
    }
}

static void mSDI_PullTreeUT(mActor_name_t* item_p) {
    mActor_name_t item = *item_p;

    if ((item >= TREE_SAPLING && item <= TREE_30000BELLS) ||
        (item >= TREE_100BELLS_SAPLING && item <= TREE_PALM_FRUIT) ||
        (item >= CEDAR_TREE_SAPLING && item <= CEDAR_TREE) || (item >= GOLD_TREE_SAPLING && item <= GOLD_TREE)) {
        *item_p = EMPTY_NO;
    }
}

static void mSDI_PullTreeBlock(mActor_name_t* items_p, int ut) {
    int i;
    for (i = ut; i < UT_TOTAL_NUM; i += UT_X_NUM) {
        mSDI_PullTreeUT(&items_p[i]);
    }
}

static void mSDI_PullTree() {
    mFM_fg_c* fg_block;
    int block_z;

    for (block_z = 0; block_z < FG_BLOCK_Z_NUM; block_z++) {
        /* Clear trees against the cliffs on the left and right town cliff borders */
        fg_block = Save_GetPointer(fg[block_z][0]);
        mSDI_PullTreeBlock(fg_block->items[0], 0);
        mSDI_PullTreeBlock((fg_block + FG_BLOCK_X_NUM - 1)->items[0], UT_X_NUM - 1);
    }
}

static void mSDI_PullTreeUnderPlayerBlock() {
    /**
     * Cleared tree diagram
     *
     * -------xx-------
     * -------xx-------
     * ----------------
     * ...
     **/

    mActor_name_t* items = &Save_Get(fg[2][2].items[0][0]);
    if (items != NULL) {
        mSDI_PullTreeUT(&items[7]);
        mSDI_PullTreeUT(&items[8]);
        mSDI_PullTreeUT(&items[16 + 7]);
        mSDI_PullTreeUT(&items[16 + 8]);
    }
}

// TODO: I don't like this deviation
#if VERSION != VER_GAFE01_00
static int mSDI_StartInitNew(GAME* game, int player_no, int malloc_flag) {
    Private_c* priv;
    Animal_c* animals = Save_Get(animals);
    mActor_name_t* fruit_p = Save_GetPointer(fruit);
    int town_day;
    GAME* g = NULL;
    int i;
    int ret = TRUE;
    GAME_PLAY* play = (GAME_PLAY*)game;

    Common_Set(scene_from_title_demo, SCENE_START_DEMO);
    lbRTC_GetTime(Common_GetPointer(time.rtc_time));
    osSyncPrintf("player no -- %d\n", player_no);
    Common_Set(player_no, player_no);

    priv = Save_GetPointer(private_data[player_no]);
    Common_Set(now_private, priv);
    priv->gender = mPr_SEX_MALE;
    decide_fruit(fruit_p);
    mFM_DecideBgTexIdx(Save_GetPointer(bg_tex_idx));
    mFAs_ClearGoodField();

    if (malloc_flag == FALSE) {
        g = game;
    }

    bzero(Save_Get(deposit), sizeof(Save_Get(deposit)));
    Save_Set(dust_flag, FALSE);
    bzero(Save_GetPointer(island), sizeof(Island_c));
    mFM_InitFgCombiSaveData(g);

    /* Remove trees */
    mSDI_PullTree();
    mSDI_PullTreeUnderPlayerBlock();

    mFM_SetBlockKindLoadCombi(g);

    /* Tree -> Fruit Tree */
    mAGrw_ChangeTree2FruitTree();

    /* Tree -> Cedar Tree */
    mAGrw_ChangeTree2Cedar();

    
    priv = Save_Get(private_data);
    mMld_SetDefaultMelody();
    mLd_LandDataInit();
    mEv_ClearEventSaveInfo(Save_GetPointer(event_save_data));
    mEv_init(&play->event);
    mNpc_InitNpcAllInfo(malloc_flag);
    
    for (i = 0; i < PLAYER_NUM; i++) {
        mPr_ClearPrivateInfo(priv);

        Save_Get(homes[i]).outlook_pal = i;
        Save_Get(homes[i]).next_outlook_pal = i;
        bzero(&Save_Get(homes[i]).size_info, sizeof(mHm_rmsz_c));

        mPr_ClearMotherMailInfo(&Save_Get(mother_mail[i]));
        priv++;
    }

    mPr_InitPrivateInfo(priv - PLAYER_NUM + player_no);
    mNpc_SetRemoveAnimalNo(Save_GetPointer(remove_animal_idx), animals, -1);
    title_game_haniwa_data_init();
    mPB_police_box_init(g);
    mSN_snowman_init();
    mHS_house_init();
    mGH_animal_return_init();
    mMC_mask_cat_init();
    mDE_maskcat_init(Save_GetPointer(mask_cat));

    lbRTC_TimeCopy(Save_GetPointer(last_grow_time), &mTM_rtcTime_clear_code);
    lbRTC_TimeCopy(Save_GetPointer(treasure_buried_time), &mTM_rtcTime_clear_code);
    lbRTC_TimeCopy(Save_GetPointer(treasure_checked_time), &mTM_rtcTime_clear_code);
    lbRTC_TimeCopy(Save_GetPointer(saved_auto_nwrite_time), &mTM_rtcTime_clear_code);

    Save_Set(station_type, RANDOM(15));
    Save_Set(island.last_song_to_island, -1);
    Save_Set(island.last_song_from_island, -1);

    mPr_SetPossessionItem(Common_Get(now_private), 0, ITM_MONEY_1000, mPr_ITEM_COND_QUEST);

    town_day = RANDOM(30) + 1; /* Initial spread is [1, 30] */
    if (town_day >= 4) {
        town_day++; /* Add an extra day so that 4th of July is never chosen, so [1, 3] U [5, 31] */
    }

    Save_Set(town_day, town_day);

    mCkRh_InitGokiSaveData_AllRoom();

    mNW_InitMyOriginal();
    mNW_InitNeedleworkData();

    mEv_2nd_init(&play->event);

    mISL_init(Save_GetPointer(island));

    famicom_emu_initial_common_data();

    mRmTp_SetDefaultLightSwitchData(1); // TODO: lightswitch enum

    mFI_PullTanukiPathTrees();

    Common_Set(_2dbe1, 0);

    return ret;
}
#else
static int mSDI_StartInitNew(GAME* game, int player_no, int malloc_flag) {
    int town_day;
    Private_c* priv;
    int i;
    Private_c* priv_p;
    Animal_c* animals = Save_Get(animals);
    GAME_PLAY* play = (GAME_PLAY*)game;
    GAME* g = NULL;

    Common_Set(scene_from_title_demo, SCENE_START_DEMO);
    lbRTC_GetTime(Common_GetPointer(time.rtc_time));
    osSyncPrintf("player no -- %d\n", player_no);
    Common_Set(player_no, player_no);

    priv = Save_GetPointer(private_data[player_no]);
    Common_Set(now_private, priv);
    priv->gender = mPr_SEX_MALE;
    decide_fruit(Save_GetPointer(fruit));
    mFM_DecideBgTexIdx(Save_GetPointer(bg_tex_idx));
    mFAs_ClearGoodField();

    if (malloc_flag == FALSE) {
        g = game;
    }

    bzero(Save_Get(deposit), sizeof(Save_Get(deposit)));
    Save_Set(dust_flag, FALSE);
    bzero(Save_GetPointer(island), sizeof(Island_c));
    mFM_InitFgCombiSaveData(g);

    /* Remove trees */
    mSDI_PullTree();
    mSDI_PullTreeUnderPlayerBlock();

    mFM_SetBlockKindLoadCombi(g);

    /* Tree -> Fruit Tree */
    mAGrw_ChangeTree2FruitTree();

    /* Tree -> Cedar Tree */
    mAGrw_ChangeTree2Cedar();

    priv_p = Save_Get(private_data);

    mMld_SetDefaultMelody();
    mLd_LandDataInit();
    mEv_ClearEventSaveInfo(Save_GetPointer(event_save_data));
    mEv_init(&play->event);
    mNpc_InitNpcAllInfo(malloc_flag);

    for (i = 0; i < PLAYER_NUM; i++) {
        mPr_ClearPrivateInfo(priv_p);

        Save_Get(homes[i]).outlook_pal = i;
        Save_Get(homes[i]).next_outlook_pal = i;
        bzero(&Save_Get(homes[i]).size_info, sizeof(mHm_rmsz_c));

        mPr_ClearMotherMailInfo(&Save_Get(mother_mail[i]));
        priv_p++;
    }

    mPr_InitPrivateInfo(priv_p - PLAYER_NUM + player_no);
    mNpc_SetRemoveAnimalNo(Save_GetPointer(remove_animal_idx), animals, -1);
    title_game_haniwa_data_init();
    mPB_police_box_init(g);
    mSN_snowman_init();
    mHS_house_init();
    mGH_animal_return_init();
    mMC_mask_cat_init();
    mDE_maskcat_init(Save_GetPointer(mask_cat));

    lbRTC_TimeCopy(Save_GetPointer(last_grow_time), &mTM_rtcTime_clear_code);
    lbRTC_TimeCopy(Save_GetPointer(treasure_buried_time), &mTM_rtcTime_clear_code);
    lbRTC_TimeCopy(Save_GetPointer(treasure_checked_time), &mTM_rtcTime_clear_code);
    lbRTC_TimeCopy(Save_GetPointer(saved_auto_nwrite_time), &mTM_rtcTime_clear_code);

    Save_Set(station_type, RANDOM(15));
    Save_Set(island.last_song_to_island, -1);
    Save_Set(island.last_song_from_island, -1);

    mPr_SetPossessionItem(Common_Get(now_private), 0, ITM_MONEY_1000, mPr_ITEM_COND_QUEST);

    town_day = RANDOM(30) + 1; /* Initial spread is [1, 30] */
    if (town_day >= 4) {
        town_day++; /* Add an extra day so that 4th of July is never chosen, so [1, 3] U [5, 31] */
    }

    Save_Set(town_day, town_day);

    mCkRh_InitGokiSaveData_AllRoom();

    mNW_InitMyOriginal();
    mNW_InitNeedleworkData();

    mEv_2nd_init(&play->event);

    mISL_init(Save_GetPointer(island));

    famicom_emu_initial_common_data();

    mRmTp_SetDefaultLightSwitchData(1); // TODO: lightswitch enum

    mFI_PullTanukiPathTrees();

    Common_Set(_2dbe1, 0);

    return TRUE;
}
#endif

static int mSDI_StartInitFrom(GAME* game, int player_no, int malloc_flag) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    int res = FALSE;
    GAME* g = game;
    Animal_c* animals = Save_Get(animals);

    if (malloc_flag) {
        g = NULL;
    }

    Common_Set(scene_from_title_demo, SCENE_FG);
    lbRTC_GetTime(Common_GetPointer(time.rtc_time));

    if (mFRm_CheckSaveData() == TRUE) {
        Private_c* priv = Save_Get(private_data + player_no);

        if (mPr_CheckPrivate(priv) == TRUE) {

            if (priv->exists == TRUE) {
                Common_Set(now_private, priv);
                Common_Set(player_no, player_no);
                mFM_SetBlockKindLoadCombi(g);
                mEv_init_force(&play->event);
                mHsRm_GetHuusuiRoom(g, player_no);
                mCkRh_DecideNowGokiFamilyCount(player_no);
                mSP_ExchangeLineUp_InGame(g);
                mNpc_SetRemoveAnimalNo(Save_GetPointer(remove_animal_idx), animals, -1);
                mMkRm_MarkRoom(g);
                mRmTp_SetDefaultLightSwitchData(2); // TODO: enum
                res = TRUE;
            } else {
                /* Player loaded their player data while "out travelling" */
                Common_Set(player_decoy_flag, TRUE); // set "gyroid face" flag
                priv->exists = TRUE;
                Common_Set(now_private, priv);
                Common_Set(player_no, player_no);
                mFM_SetBlockKindLoadCombi(g);
                mEv_init_force(&play->event);
                mHsRm_GetHuusuiRoom(g, player_no);
                mCkRh_DecideNowGokiFamilyCount(player_no);
                mSP_ExchangeLineUp_InGame(g);
                mNpc_SetRemoveAnimalNo(Save_GetPointer(remove_animal_idx), animals, -1);

                /* Punish player by deleting their pockets and some pending items */
                bzero(&priv->inventory.pockets, sizeof(priv->inventory.pockets));
                priv->inventory.lotto_ticket_expiry_month = 0;
                priv->inventory.lotto_ticket_mail_storage = 0;
                priv->inventory.item_conditions = 0;
                priv->inventory.wallet = 0;
                mQst_ClearDelivery(priv->deliveries, mPr_DELIVERY_QUEST_NUM);
                mQst_ClearErrand(priv->errands, mPr_ERRAND_QUEST_NUM);

                mMkRm_MarkRoom(g);
                mRmTp_SetDefaultLightSwitchData(2); // TODO: enum
                res = TRUE;
            }
        }
    }

    return res;
}

static int mSDI_StartInitNewPlayer(GAME* game, int player_no, int malloc_flag) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    Animal_c* animals = Save_Get(animals);
    int res = FALSE;

    Common_Set(scene_from_title_demo, SCENE_START_DEMO2);
    lbRTC_GetTime(Common_GetPointer(time.rtc_time));

    if (mFRm_CheckSaveData() == TRUE) {
        Private_c* priv = Save_Get(private_data + player_no);

        if (mPr_CheckPrivate(priv) != TRUE) {
            mPr_InitPrivateInfo(priv);
            Common_Set(now_private, priv);
            mPr_SetPossessionItem(priv, 0, ITM_MONEY_1000, mPr_ITEM_COND_QUEST);
            Common_Set(player_no, player_no);
            Common_Get(now_private)->gender = mPr_SEX_MALE;
            mNW_InitOneMyOriginal(Common_Get(player_no));
            mCkRh_InitGokiSaveData_InitNewPlayer();

            if (malloc_flag == FALSE) {
                mFM_SetBlockKindLoadCombi(game);
                mEv_init_force(&play->event);
                mSP_ExchangeLineUp_InGame(game);
            } else {
                mFM_SetBlockKindLoadCombi(NULL);
                mEv_init_force(&play->event);
                mSP_ExchangeLineUp_InGame(NULL);
            }

            mNpc_SetRemoveAnimalNo(Save_GetPointer(remove_animal_idx), animals, -1);
            mSDI_ClearMoneyPlayerHomeStationBlock();
            mRmTp_SetDefaultLightSwitchData(1); // TODO: enum
            mFI_PullTanukiPathTrees();
            res = TRUE;
        }
    }

    return res;
}

static int mSDI_StartInitPak(GAME* game, int player_no, int malloc_flag) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    GAME* g = game;
    Animal_c* animals = Save_Get(animals);
    int res = FALSE;

    if (malloc_flag == TRUE) {
        g = NULL;
    }

    if (player_no < mPr_PLAYER_NUM) {
        Common_Set(scene_from_title_demo, SCENE_FG);
    }

    if (mFRm_CheckSaveData() == TRUE) {
        mFM_SetBlockKindLoadCombi(g);
        mEv_init_force(&play->event);
        mHsRm_GetHuusuiRoom(g, player_no);
        mCkRh_DecideNowGokiFamilyCount(player_no);
        mSP_ExchangeLineUp_InGame(g);
        mNpc_SetRemoveAnimalNo(Save_GetPointer(remove_animal_idx), animals, -1);
        mNpc_SetReturnAnimal(mNpc_GetInAnimalP());
        mNpc_SendRegisteredGoodbyMail();
        mMkRm_MarkRoom(g);
        mEv_SetGateway();
        mRmTp_SetDefaultLightSwitchData(2); // TODO: enum
        res = TRUE;
    }

    return res;
}

static int mSDI_StartInitErr(GAME* game, int player_no, int malloc_flag) {
    return TRUE;
}

extern void mSDI_StartInitAfter(GAME* game, int renew_mode, int malloc_flag) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    Animal_c* animals = Save_Get(animals);

    Common_Set(house_owner_name, -1);
    mEA_InitLetterCardE();
    Common_Set(last_field_id, -1);
    mHm_SetNowHome();
    mNpc_RenewalAnimalMemory();
    mNpc_ForceRemove();
    mTM_renewal_renew_time();
    mEv_ClearEventInfo();
    mEnv_DecideWeather_NormalGameStart();
    mMl_start_send_mail();
    mPO_first_work(play);
    mTM_set_season();
    mAGrw_ClearAllShine_Stone();
    mAGrw_RestoreStoneShine(Common_Get(player_no));
    mFAs_SetFieldRank();
    mEv_2nd_init(&play->event);
    mNpc_Grow();
    Kabu_manager();
    mNpc_InitNpcData();
    mNpc_InitNpcList(Common_Get(npclist), ANIMAL_NUM_MAX);
    mNpc_SetNpcList(Common_Get(npclist), animals, ANIMAL_NUM_MAX, malloc_flag);
    mNpc_InitNpcList(Common_Get(island_npclist), 1);
    mNpc_ClearTalkInfo();

    if (renew_mode == 1) {
        mFM_RenewalReserve();
    }

    mNpc_ChangePresentCloth();
    mQst_ClearNotSaveQuest(Common_GetPointer(quest));
    mGH_check_delete();
    mMC_check_delete();
    mFM_SetIslandNpcRoomData(game, malloc_flag);
    mCD_calendar_wellcome_on();
    mPr_SetItemCollectBit(FTR_START(FTR_SUM_CASSE01));
    mPr_SetItemCollectBit(FTR_START(FTR_NOG_COLLEGENOTE));
    mPr_SetItemCollectBit(FTR_START(FTR_NOG_MIKANBOX));
    mNPS_set_all_schedule_area();
    mNpcW_InitNpcWalk(Common_GetPointer(npc_walk));
    mHm_CheckRehouseOrder();
    decide_fish_location(Common_GetPointer(fish_location));
    mTRC_init(game);
    Common_Set(goki_shocked_flag, FALSE);
    mNtc_auto_nwrite_time_ct();
    mPr_SendMailFromMother();
    mNpc_Remail();
    mPr_SendForeingerAnimalMail(Common_Get(now_private));
    mPr_StartSetCompleteTalkInfo();
    mMsm_SendInformationMail();
    mMsm_SendCompMail();
    mFI_SetFirstSetShell();
    mMsr_FirstClearMushroom();
    mSN_decide_msg();
    mPr_RenewalMapInfo(Common_Get(now_private)->maps, mPr_FOREIGN_MAP_COUNT, Save_GetPointer(land_info));
    mSP_SetTanukiShopStatus();
    mEnv_DecideTodayWindPowerRange();
    mFI_SetClimate(mFI_CLIMATE_0);
    mISL_RestoreIsland();
    mNpc_SendHPMail();
}

typedef int (*mSDI_INIT_PROC)(GAME*, int, int);

extern int mSDI_StartInitBefore(GAME* game, int player_no, int init_mode, int malloc_flag) {
    static mSDI_INIT_PROC init_proc[mSDI_INIT_MODE_NUM] = { &mSDI_StartInitNew, &mSDI_StartInitNewPlayer,
                                                            &mSDI_StartInitFrom, &mSDI_StartInitPak,
                                                            &mSDI_StartInitErr };

    mEv_UnSetGateway();
    return (*init_proc[init_mode])(game, player_no, malloc_flag);
}

extern int mSDI_StartDataInit(GAME* game, int player_no, int init_mode) {
    static int renew_reserve_mode_table[mSDI_INIT_MODE_NUM] = { TRUE, FALSE, FALSE, FALSE, FALSE };

    int res;

    if (init_mode < mSDI_INIT_MODE_NEW || init_mode >= mSDI_INIT_MODE_NUM) {
        init_mode = mSDI_INIT_MODE_NEW;
    }

    res = mSDI_StartInitBefore(game, player_no, init_mode, mSDI_MALLOC_FLAG_ZELDA);
    if (res == TRUE) {
        mSDI_StartInitAfter(game, renew_reserve_mode_table[init_mode], mSDI_MALLOC_FLAG_ZELDA);
    }

    return res;
}
