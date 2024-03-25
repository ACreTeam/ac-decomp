#include "m_island.h"

#include "m_field_info.h"
#include "m_common_data.h"
#include "m_random_field.h"
#include "m_malloc.h"
#include "libultra/libultra.h"
#include "jsyswrap.h"

static Island_c l_keepIsland;
static u16 l_keepIslandComb[mISL_FG_BLOCK_X_NUM * mISL_FG_BLOCK_Z_NUM];

static u8 l_misl_count_max_table[32] = { 10, 4, 1, 10, 1, 5, 3, 10, 5, 1, 1, 1, 1, 1, 1, 1,
                                         1,  1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1 };

static u8 l_misl_count_table[32];

extern void mISL_ClearKeepIsland() {
    bzero(&l_keepIsland, sizeof(l_keepIsland));
}

extern void mISL_KeepIsland(Island_c* island) {
    if (mLd_CheckThisLand(island->landinfo.name, island->landinfo.id) == TRUE) {
        bcopy(island, &l_keepIsland, sizeof(l_keepIsland));
    }
}

static void mISL_KeepIslandComb(u16* dst, mFM_combination_c* combi, int count) {
    while (count != 0 && dst != NULL && combi != NULL) {
        count--;
        dst[0] = combi[0].combination_type;
        dst++;
        combi++;
    }
}

static void mISL_RestoreIslandComb_com(mFM_combination_c* combi, u16* src, int count) {
    while (count != 0 && src != NULL && combi != NULL) {
        count--;
        combi[0].combination_type = *src;
        combi++;
        src++;
    }
}

static void mISL_RestoreIslandComb() {
    int island_x_blocks[mISL_FG_BLOCK_X_NUM];

    mFI_GetIslandBlockNumX(island_x_blocks);

    if (island_x_blocks[0] > 0 && island_x_blocks[1] < (BLOCK_X_NUM - 1)) {
        mISL_RestoreIslandComb_com(Save_GetPointer(combi_table[mISL_BLOCK_Z][island_x_blocks[0]]), l_keepIslandComb,
                                   mISL_FG_BLOCK_X_NUM);
    }
}

extern void mISL_ChangeBG() {
    int island_x_blocks[mISL_FG_BLOCK_X_NUM];

    mFI_GetIslandBlockNumX(island_x_blocks);

    if (island_x_blocks[0] > 0 && island_x_blocks[1] < (BLOCK_X_NUM - 1)) {
        mISL_KeepIslandComb(l_keepIslandComb, Save_GetPointer(combi_table[mISL_BLOCK_Z][island_x_blocks[0]]),
                            mISL_FG_BLOCK_X_NUM);
        mRF_IslandBgData_To_VillageData();
        mFM_RestoreIslandBG(island_x_blocks, mISL_FG_BLOCK_X_NUM);
    }
}

extern void mISL_RestoreIsland() {
    Island_c* island = Save_GetPointer(island);
    Island_c* keep_island = &l_keepIsland;

    if (mLd_CheckThisLand(island->landinfo.name, island->landinfo.id) == FALSE) {
        bcopy(keep_island, island, sizeof(l_keepIsland));
        mISL_RestoreIslandComb();
    } else {
        bcopy(island, keep_island, sizeof(l_keepIsland));
    }
}

extern void mISL_init(Island_c* island) {
    mLd_ClearLandName(island->name);
    bcopy(Save_GetPointer(land_info), &island->landinfo, sizeof(mLd_land_info_c));
    mHm_InitCottage(&island->cottage);
    mNpc_DecideIslandNpc(&island->animal);
    Save_Get(island).grass_tex_type = Save_Get(bg_tex_idx);
}

static u32* mISL_GetCheckP(PersonalID_c* pid) {
    Anmmem_c* memory = Save_Get(island).animal.memories;
    u32* check_p = NULL;

    if (pid != NULL && mPr_NullCheckPersonalID(pid) == FALSE) {
        int idx = mNpc_GetAnimalMemoryIdx(pid, memory, ANIMAL_MEMORY_NUM);

        if (idx != -1) {
            check_p = &memory[idx].memuni.island.check;
        }
    }

    return check_p;
}

extern void mISL_ClearNowPlayerAction() {
    Private_c* priv = Common_Get(now_private);

    if (priv != NULL) {
        u32* check_p = mISL_GetCheckP(&priv->player_ID);

        if (check_p != NULL) {
            check_p[0] = 0;
        }

        bzero(l_misl_count_table, sizeof(l_misl_count_table));
    }
}

extern void mISL_SetPlayerAction(PersonalID_c* pid, u32 action) {
    if (pid != NULL && mFI_CheckInIsland() == TRUE) {
        u32* check_p = mISL_GetCheckP(pid);

        if (check_p != NULL) {
            int i;

            for (i = 0; i < ARRAY_COUNT(l_misl_count_table); i++) {
                if (((action >> i) & 1) != 0) {
                    l_misl_count_table[i]++;
                }

                if (l_misl_count_max_table[i] <= l_misl_count_table[i]) {
                    check_p[0] |= (1 << i);
                    l_misl_count_table[i] = l_misl_count_max_table[i];
                }
            }
        }
    }
}

extern void mISL_SetNowPlayerAction(u32 action) {
    Private_c* priv = Common_Get(now_private);

    if (priv != NULL) {
        mISL_SetPlayerAction(&priv->player_ID, action);
    }
}

extern int mISL_CheckPlayerAction(PersonalID_c* pid, u32 action) {
    int res = FALSE;

    if (pid != NULL) {
        u32* check_p = mISL_GetCheckP(pid);

        if (check_p != NULL && (check_p[0] & action) != 0) {
            res = TRUE;
        }
    }

    return res;
}

extern int mISL_CheckNowPlayerAction(u32 action) {
    Private_c* priv = Common_Get(now_private);
    int res = FALSE;

    if (priv != NULL) {
        res = mISL_CheckPlayerAction(&priv->player_ID, action);
    }

    return res;
}

static void mISL_int(u32* dst, u32* src, int n) {
    int i;

    for (i = n; i != 0; i--) {
        u32 v = ((src[0] & 0xFF) << 24) | ((src[0] & 0xFF00) << 8) | ((src[0] >> 8) & 0xFF00) | ((src[0] >> 24) & 0xFF);
        src++;
        *dst++ = v;
    }
}

static void mISL_short(register u16* dst, register u16* src, register int n) {
    int i;

    for (i = n; i != 0; i--) {
        u16 v = ((src[0] & 0xFF) << 8) | ((src[0] & 0xFF00) >> 8);
        src++;
        *dst++ = v;
    }
}

static void mISL_u64(u64* dst, u64* src, int n) {
    int i;

    for (i = n; i != 0; i--) {
        u32 src_hi;
        u32 src_lo;
        u32 dst_lo;
        u32 dst_hi;

        src_hi = (u32)((src[0] >> 32) & 0xFFFFFFFF);
        src_lo = (u32)(src[0] & 0xFFFFFFFF);

        mISL_int(&dst_lo, &src_hi, 1);
        mISL_int(&dst_hi, &src_lo, 1);

        *dst = (((u64)dst_hi) << 32) | (u64)dst_lo;

        src++;
        dst++;
    }
}

static mActor_name_t l_misl_agb_npc_table[NPC_ISLANDER_NUM] = {
    NPC_BLISS,    NPC_DOBIE, NPC_OHARE, NPC_DRIFT,  NPC_JUNE,   NPC_FAITH, NPC_FLOSSIE, NPC_FLASH, NPC_MAELLE,
    NPC_ANNALISE, NPC_BUD,   NPC_ELINA, NPC_BOOMER, NPC_PIGLEG, NPC_YODEL, NPC_PLUCKY,  NPC_ROWAN, NPC_ANKHA
};

static int mISL_get_npc_idx(mActor_name_t npc_id) {
    mActor_name_t* agb_npc_table_p = l_misl_agb_npc_table;
    int res = 0;
    int i;

    if (ITEM_NAME_GET_TYPE(npc_id) == NAME_TYPE_NPC) {
        for (i = 0; i < NPC_ISLANDER_NUM; i++) {
            if (*agb_npc_table_p == npc_id) {
                res = i;
                break;
            }

            agb_npc_table_p++;
        }
    }

    return res;
}

static void mISL_get_npc_tex(u32* dst, u32* src, int idx) {
    if (idx != -1 && dst != NULL && src != NULL) {
        u32 base_addr = JW_GetAramAddress(RESOURCE_D_OBJ_NPC_STOCK_SCH);

        _JW_GetResourceAram(base_addr + idx * (1024 * sizeof(u32)), (u8*)src, 1024 * sizeof(u32));
        mISL_int(dst, src, 1024);
    }
}

static void mISL_get_npc_pal(u16* dst, u16* src, int idx) {
    if (idx != -1 && dst != NULL && src != NULL) {
        u32 base_addr = JW_GetAramAddress(RESOURCE_D_OBJ_NPC_STOCK_SCL);

        _JW_GetResourceAram(base_addr + idx * (16 * sizeof(u16)), (u8*)src, 16 * sizeof(u16));
        mISL_short(dst, src, 16);
    }
}

static void mISL_get_earth_tex(u32* dst, u32* src, int idx) {
    if (idx < mFM_BG_TEX_NUM && dst != NULL && src != NULL) {
        u32 base_addr = JW_GetAramAddress(RESOURCE_D_BG_ISLAND_SCH);

        _JW_GetResourceAram(base_addr + idx * (1024 * sizeof(u32)), (u8*)src, 1024 * sizeof(u32));
        mISL_int(dst, src, 1024);
    }
}

static void mISL_gc_to_agb_iandinfo(mISL_landinfo_agb_c* agb, mLd_land_info_c* gc) {
    bcopy(gc->name, agb->name, LAND_NAME_SIZE);
    agb->exists = gc->exists;
    mISL_short(&agb->id, &gc->id, 1);
}

static void mISL_agb_to_gc_iandinfo(mLd_land_info_c* gc, mISL_landinfo_agb_c* agb) {
    bcopy(agb->name, gc->name, LAND_NAME_SIZE);
    gc->exists = agb->exists;
    mISL_short(&gc->id, &agb->id, 1);
}

static void mISL_gc_to_agb_fg(mActor_name_t* agb, mActor_name_t* gc) {
    mISL_short(agb, gc, UT_TOTAL_NUM);
}

static void mISL_gc_to_agb_fg2(mActor_name_t* agb, mActor_name_t* gc) {
    int i;

    for (i = 0; i < UT_TOTAL_NUM; i++) {
        mActor_name_t item;

        if (*gc == 0xF123) {
            item = COTTAGE_MY;
        } else if (*gc == 0xF124) {
            item = COTTAGE_NPC;
        } else if (*gc == 0xF122) {
            item = FLAG;
        } else if (*gc == 0xF128) {
            item = BOAT;
        } else if (*gc >= HOLE_START && *gc <= HOLE_END) {
            item = EMPTY_NO;
        } else if (*gc == 0xF11F) {
            item = ACTOR_PROP_VILLAGER_SIGNBOARD;
        } else {
            item = *gc;
        }

        mISL_short(agb, &item, 1);
        agb++;
        gc++;
    }
}

static void mISL_agb_to_gc_fg(mActor_name_t* gc, mActor_name_t* agb) {
    mISL_short(gc, agb, UT_TOTAL_NUM);
}

static void mISL_gc_to_agb_fgblock(mFM_fg_c* agb, mFM_fg_c* gc) {
    int i;

    for (i = 0; i < mISL_FG_BLOCK_X_NUM; i++) {
        mISL_gc_to_agb_fg2(agb->items[0], gc->items[0]);
        agb++;
        gc++;
    }
}

static void mISL_agb_to_gc_fgblock(mFM_fg_c* gc, mFM_fg_c* agb) {
    int i;

    for (i = 0; i < mISL_FG_BLOCK_X_NUM; i++) {
        mISL_agb_to_gc_fg(gc->items[0], agb->items[0]);
        agb++;
        gc++;
    }
}

static void mISL_gc_to_agb_layer(mHm_lyr_c* agb, mHm_lyr_c* gc) {
    int i;

    for (i = 0; i < mHm_LAYER_NUM; i++) {
        mISL_gc_to_agb_fg(agb->items[0], gc->items[0]);
        mISL_u64(&agb->ftr_switch, &gc->ftr_switch, 1);
        mISL_int(agb->haniwa_step, gc->haniwa_step, ARRAY_COUNT(agb->haniwa_step));

        agb++;
        gc++;
    }
}

static void mISL_gc_to_agb_fllot_bit(u32* agb, mHm_fllot_bit_c* gc) {
    mHm_fllot_bit_c tmp[4];

    bzero(tmp, sizeof(tmp));
    tmp[0].wall_original = gc->wall_original;
    tmp[0].floor_original = gc->floor_original;
    mISL_int(agb, (u32*)tmp, 1);
}

static void mISL_agb_to_gc_fllot_bit(mHm_fllot_bit_c* gc, u32* agb) {
    mHm_fllot_bit_c tmp[4];

    bzero(tmp, sizeof(tmp));
    mISL_int((u32*)tmp, agb, 1);

/* @BUG - devs made an oopsie and reused GC here */
#ifndef BUGFIXES
    gc->wall_original = (u32)gc->wall_original;
    gc->floor_original = (u32)gc->floor_original;
#else
    gc->wall_original = agb->wall_original;
    gc->floor_original = agb->floor_original;
#endif
}

static void mISL_gc_to_agb_cottage_floor(mISL_flr_agb_c* agb, mHm_flr_c* gc) {
    mISL_gc_to_agb_layer(agb->layers, &gc->layer_main);
    bcopy(&gc->wall_floor, &agb->wall_floor, sizeof(gc->wall_floor));
    bcopy(&gc->tempo_beat, &agb->tempo_beat, sizeof(gc->tempo_beat));
    mISL_gc_to_agb_fllot_bit(&agb->floor_bit_info, &gc->floor_bit_info);
}

static void mISL_agb_to_gc_cottage_floor(mHm_flr_c* gc, mISL_flr_agb_c* agb) {
    mISL_gc_to_agb_layer(&gc->layer_main, agb->layers);
    bcopy(&agb->wall_floor, &gc->wall_floor, sizeof(gc->wall_floor));
    bcopy(&agb->tempo_beat, &gc->tempo_beat, sizeof(gc->tempo_beat));
    mISL_agb_to_gc_fllot_bit(&gc->floor_bit_info, &agb->floor_bit_info);
}

static void mISL_gc_to_agb_ymd(lbRTC_ymd_c* agb, lbRTC_ymd_c* gc) {
    mISL_short(&agb->year, &gc->year, 1);
    agb->month = gc->month;
    agb->day = gc->day;
}

static void mISL_gc_to_agb_time(lbRTC_time_c* agb, lbRTC_time_c* gc) {
    agb->sec = gc->sec;
    agb->min = gc->min;
    agb->hour = gc->hour;
    agb->day = gc->day;
    agb->weekday = gc->weekday;
    agb->month = gc->month;
    mISL_short(&agb->year, &gc->year, 1);
}

static void mISL_gc_to_agb_goki(mHm_goki_c* agb, mHm_goki_c* gc) {
    mISL_gc_to_agb_time(&agb->time, &gc->time);
    agb->num = gc->num;
}

static void mISL_agb_to_gc_goki(mHm_goki_c* gc, mHm_goki_c* agb) {
    mISL_gc_to_agb_time(&gc->time, &agb->time);
    gc->num = agb->num;
}

static void mISL_gc_to_agb_cottage(mISL_cottage_agb_c* agb, mHm_cottage_c* gc) {
    bcopy(&gc->unused_wall_floor, &agb->unused_wall_floor, sizeof(gc->unused_wall_floor));
    bcopy(gc->unk_2, agb->unk_2, sizeof(gc->unk_2));
    mISL_gc_to_agb_cottage_floor(&agb->room, &gc->room);
    agb->unk_8B8 = gc->unk_4;
    agb->unk_8B9 = gc->unk_5;
    mISL_gc_to_agb_goki(&agb->goki, &gc->goki);
    mISL_int(agb->music_box, gc->music_box, 2);
}

static void mISL_agb_to_gc_cottage(mHm_cottage_c* gc, mISL_cottage_agb_c* agb) {
    bcopy(&agb->unused_wall_floor, &gc->unused_wall_floor, sizeof(gc->unused_wall_floor));
    bcopy(agb->unk_2, gc->unk_2, sizeof(gc->unk_2));
    gc->unk_4 = agb->unk_8B8;
    gc->unk_5 = agb->unk_8B9;
    mISL_agb_to_gc_cottage_floor(&gc->room, &agb->room);
    mISL_agb_to_gc_goki(&gc->goki, &agb->goki);
    mISL_int(gc->music_box, agb->music_box, 2);
}

static void mISL_gc_to_agb_mail(mISL_Anmplmail_agb_c* agb, Anmplmail_c* gc) {
    agb->font = gc->font;
    agb->paper_type = gc->paper_type;
    agb->present = gc->present;
    agb->header_back_start = gc->header_back_start;
    bcopy(gc->header, agb->header, MAIL_HEADER_LEN);
    bcopy(gc->body, agb->body, MAIL_BODY_LEN);
    bcopy(gc->footer, agb->footer, MAIL_FOOTER_LEN);
    mISL_gc_to_agb_ymd(&agb->date, &gc->date);
}

static void mISL_agb_to_gc_mail(Anmplmail_c* gc, mISL_Anmplmail_agb_c* agb) {
    gc->font = agb->font;
    gc->paper_type = agb->paper_type;
    gc->present = agb->present;
    gc->header_back_start = agb->header_back_start;
    bcopy(agb->header, gc->header, MAIL_HEADER_LEN);
    bcopy(agb->body, gc->body, MAIL_BODY_LEN);
    bcopy(agb->footer, gc->footer, MAIL_FOOTER_LEN);
    mISL_gc_to_agb_ymd(&gc->date, &agb->date);
}

static void mIS_gc_to_agb_anmpersonal(AnmPersonalID_c* agb, AnmPersonalID_c* gc) {
    mISL_short(&agb->npc_id, &gc->npc_id, 1);
    mISL_short(&agb->land_id, &gc->land_id, 1);
    bcopy(gc->land_name, agb->land_name, LAND_NAME_SIZE);
    agb->name_id = gc->name_id;
    agb->looks = gc->looks;
}

static void mIS_agb_to_gc_anmpersonal(AnmPersonalID_c* gc, AnmPersonalID_c* agb) {
    mISL_short(&gc->npc_id, &agb->npc_id, 1);
    mISL_short(&gc->land_id, &agb->land_id, 1);
    bcopy(agb->land_name, gc->land_name, LAND_NAME_SIZE);
    gc->name_id = agb->name_id;
    gc->looks = agb->looks;
}

static void mISL_gc_to_agb_personal(PersonalID_c* agb, PersonalID_c* gc) {
    bcopy(gc->player_name, agb->player_name, PLAYER_NAME_LEN);
    bcopy(gc->land_name, agb->land_name, LAND_NAME_SIZE);
    mISL_short(&agb->player_id, &gc->player_id, 1);
    mISL_short(&agb->land_id, &gc->land_id, 1);
}

static void mISL_gc_to_agb_memuni(memuni_u* agb, memuni_u* gc) {
    mISL_int((u32*)agb, (u32*)gc, sizeof(memuni_u) / sizeof(u32));
}

static void mISL_agb_to_gc_memuni(memuni_u* gc, memuni_u* agb) {
    mISL_int((u32*)gc, (u32*)agb, sizeof(memuni_u) / sizeof(u32));
}

static void mISL_gc_to_agb_memletter(u32* agb, Anmlet_c* gc) {
    Anmlet_c t[4];

    bzero(t, sizeof(t));
    t[0].exists = gc->exists;
    t[0].cond = gc->cond;
    t[0].send_reply = gc->send_reply;
    t[0].has_present_cloth = gc->has_present_cloth;
    t[0].wearing_present_cloth = gc->wearing_present_cloth;
    mISL_int(agb, (u32*)t, 1);
}

static void mISL_agb_to_gc_memletter(Anmlet_c* gc, u32* agb) {
    Anmlet_c t[4];

    bzero(t, sizeof(t));
    mISL_int((u32*)t, agb, 1);
    gc->exists = t[0].exists;
    gc->cond = t[0].cond;
    gc->send_reply = t[0].send_reply;
    gc->has_present_cloth = t[0].has_present_cloth;
    gc->wearing_present_cloth = t[0].wearing_present_cloth;
}

static void mISL_gc_to_agb_memory(mISL_Anmmem_agb_c* agb, Anmmem_c* gc) {
    mISL_gc_to_agb_personal(&agb->player_id, &gc->memory_player_id);
    mISL_gc_to_agb_time(&agb->last_speak_time, &gc->last_speak_time);
    mISL_gc_to_agb_memuni(&agb->memuni, &gc->memuni);
/* @BUG - devs forgot to save this, but remembered to restore it */
#ifdef BUGFIXES
    mISL_u64(&agb->saved_town_tune, &gc->saved_town_tune, 1);
#endif
    agb->friendship = gc->friendship;
    mISL_gc_to_agb_memletter(&agb->letter_info, &gc->letter_info);
    mISL_gc_to_agb_mail(&agb->letter, &gc->letter);
}

static void mISL_agb_to_gc_memory(Anmmem_c* gc, mISL_Anmmem_agb_c* agb) {
    mISL_gc_to_agb_personal(&gc->memory_player_id, &agb->player_id);
    mISL_gc_to_agb_time(&gc->last_speak_time, &agb->last_speak_time);
    mISL_agb_to_gc_memuni(&gc->memuni, &agb->memuni);
    mISL_u64(&gc->saved_town_tune, &agb->saved_town_tune, 1);
    gc->friendship = agb->friendship;
    mISL_agb_to_gc_memletter(&gc->letter_info, &agb->letter_info);
    mISL_agb_to_gc_mail(&gc->letter, &agb->letter);
}

static void mISL_gc_to_agb_qclass(mISL_quest_base_c* agb, mQst_base_c* gc) {
    mQst_base_c t;

    bzero(&t, sizeof(t));
    t.quest_type = gc->quest_type;
    t.quest_kind = gc->quest_kind;
    t.time_limit_enabled = gc->time_limit_enabled;
    t.progress = gc->progress;
    t.give_reward = gc->give_reward;
    mISL_int(&agb->info, (u32*)&t, 1);
    mISL_gc_to_agb_time(&agb->time_limit, &gc->time_limit);
}

static void mISL_agb_to_gc_qclass(mQst_base_c* gc, mISL_quest_base_c* agb) {
    mQst_base_c t;

    bzero(&t, sizeof(t));
    mISL_int((u32*)&t, &agb->info, 1);
    gc->quest_type = t.quest_type;
    gc->quest_kind = t.quest_kind;
    gc->time_limit_enabled = t.time_limit_enabled;
    gc->progress = t.progress;
    gc->give_reward = t.give_reward;
    mISL_gc_to_agb_time(&gc->time_limit, &agb->time_limit);
}

static void mISL_gc_to_agb_qdata(mQst_contest_info_u* agb, mQst_contest_info_u* gc) {
    mISL_int((u32*)agb, (u32*)gc, sizeof(mQst_contest_info_u) / sizeof(u32));
}

static void mISL_agb_to_gc_qdata(mQst_contest_info_u* gc, mQst_contest_info_u* agb) {
    mISL_int((u32*)gc, (u32*)agb, sizeof(mQst_contest_info_u) / sizeof(u32));
}

static void mISL_gc_to_agb_quest(mISL_quest_contest_c* agb, mQst_contest_c* gc) {
    mISL_gc_to_agb_qclass(&agb->base, &gc->base);
    mISL_short(&agb->requested_item, &gc->requested_item, 1);
    mISL_gc_to_agb_personal(&agb->player_id, &gc->player_id);
    agb->type = gc->type;
    mISL_gc_to_agb_qdata(&agb->info, &gc->info);
}

static void mISL_agb_to_gc_quest(mQst_contest_c* gc, mISL_quest_contest_c* agb) {
    mISL_agb_to_gc_qclass(&gc->base, &agb->base);
    mISL_short(&gc->requested_item, &agb->requested_item, 1);
    mISL_gc_to_agb_personal(&agb->player_id, &gc->player_id);
    gc->type = agb->type;
    mISL_agb_to_gc_qdata(&gc->info, &agb->info);
}

static void mISL_gc_to_agb_anmuni(anmuni_u* agb, anmuni_u* gc) {
    mISL_int((u32*)agb, (u32*)gc, sizeof(anmuni_u) / sizeof(u32));
}

static void mISL_agb_to_gc_anmuni(anmuni_u* gc, anmuni_u* agb) {
    mISL_int((u32*)gc, (u32*)agb, sizeof(anmuni_u) / sizeof(u32));
}

static void mISL_gc_to_agb_hp_mail(AnmHPMail_c* agb, AnmHPMail_c* gc) {
    mISL_gc_to_agb_time(&agb->receive_time, &gc->receive_time);
    bcopy(gc->password, agb->password, sizeof(gc->password));
}

static void mISL_agb_to_gc_hp_mail(AnmHPMail_c* gc, AnmHPMail_c* agb) {
    mISL_gc_to_agb_time(&gc->receive_time, &agb->receive_time);
    bcopy(agb->password, gc->password, sizeof(gc->password));
}

static void mISL_gc_to_agb_animal(mISL_Animal_agb_c* agb, Animal_c* gc) {
    int i;

    mIS_gc_to_agb_anmpersonal(&agb->id, &gc->id);
    for (i = 0; i < ANIMAL_MEMORY_NUM; i++) {
        mISL_gc_to_agb_memory(&agb->memories[i], &gc->memories[i]);
    }

    bcopy(&gc->home_info, &agb->home_info, sizeof(Anmhome_c));
    bcopy(gc->catchphrase, agb->catchphrase, ANIMAL_CATCHPHRASE_LEN);
    mISL_gc_to_agb_quest(&agb->contest_quest, &gc->contest_quest);
    bcopy(gc->parent_name, agb->parent_name, PLAYER_NAME_LEN);
    mISL_gc_to_agb_anmuni(&agb->anmuni, &gc->anmuni);
    agb->mood = gc->mood;
    agb->mood_time = gc->mood_time;
    mISL_short(&agb->cloth, &gc->cloth, 1);
    mISL_short(&agb->remove_info, &gc->remove_info, 1);
    agb->is_home = gc->is_home;
    agb->moved_in = gc->moved_in;
    agb->removing = gc->removing;
    agb->cloth_original_id = gc->cloth_original_id;
    agb->umbrella_id = gc->umbrella_id;
    agb->unk_932 = gc->unk_8ED;
    mISL_short(&agb->present_cloth, &gc->present_cloth, 1);
    bcopy(gc->animal_relations, agb->animal_relations, ANIMAL_NUM_MAX);

    for (i = 0; i < ANIMAL_HP_MAIL_NUM; i++) {
        mISL_gc_to_agb_hp_mail(&agb->hp_mail[i], &gc->hp_mail[i]);
    }
}

static void mISL_agb_to_gc_animal(Animal_c* gc, mISL_Animal_agb_c* agb) {
    int i;

    mIS_agb_to_gc_anmpersonal(&gc->id, &agb->id);
    for (i = 0; i < ANIMAL_MEMORY_NUM; i++) {
        mISL_agb_to_gc_memory(&gc->memories[i], &agb->memories[i]);
    }

    bcopy(&agb->home_info, &gc->home_info, sizeof(Anmhome_c));
    bcopy(agb->catchphrase, gc->catchphrase, ANIMAL_CATCHPHRASE_LEN);
    mISL_agb_to_gc_quest(&gc->contest_quest, &agb->contest_quest);
    bcopy(agb->parent_name, gc->parent_name, PLAYER_NAME_LEN);
    mISL_agb_to_gc_anmuni(&gc->anmuni, &agb->anmuni);
    gc->mood = agb->mood;
    gc->mood_time = agb->mood_time;
    mISL_short(&gc->cloth, &agb->cloth, 1);
    mISL_short(&gc->remove_info, &agb->remove_info, 1);
    gc->is_home = agb->is_home;
    gc->moved_in = agb->moved_in;
    gc->removing = agb->removing;
    gc->cloth_original_id = agb->cloth_original_id;
    gc->umbrella_id = agb->umbrella_id;
    gc->unk_8ED = agb->unk_932;
    mISL_short(&gc->present_cloth, &agb->present_cloth, 1);
    bcopy(agb->animal_relations, gc->animal_relations, ANIMAL_NUM_MAX);

    for (i = 0; i < ANIMAL_HP_MAIL_NUM; i++) {
        mISL_agb_to_gc_hp_mail(&gc->hp_mail[i], &agb->hp_mail[i]);
    }
}

static int mISL_ReturnCheckSum(u8* data, int size) {
    int checksum = 0;
    int i;

    for (i = size; i != 0; i--) {
        checksum += *data++;
    }

    return checksum;
}

static u8 mISL_GetFlatCheckSum(u8* data, int size, u8 now_checksum, int ignored_section_checksum) {
    int checksum = mISL_ReturnCheckSum(data, size);
    u8 diff = (u8)(checksum - now_checksum) - ignored_section_checksum;

    diff = ~diff;
    diff = diff + 1;

    return diff;
}

extern void mISL_gc_to_agb(Island_agb_c* agb, Island_c* gc) {
    int npc_idx;
    u32* temp;

    if (agb != NULL) {
        bcopy(gc->name, agb->name, mISL_ISLAND_NAME_LEN);
        agb->in_use = FALSE;
        mISL_gc_to_agb_iandinfo(&agb->landinfo, &gc->landinfo);
        mISL_gc_to_agb_fgblock(agb->fgblock[0], gc->fgblock[0]);
        mISL_gc_to_agb_cottage(&agb->cottage, &gc->cottage);
        bcopy(&gc->flag_design, &agb->flag_design, sizeof(mNW_original_design_c));
        mISL_gc_to_agb_animal(&agb->animal, &gc->animal);
        mISL_short(agb->deposit[0], gc->deposit[0], sizeof(gc->deposit) / sizeof(u16));
        bcopy(gc->bg_data, agb->bg_data, sizeof(gc->bg_data));
        mISL_gc_to_agb_time(&agb->renew_time, &gc->renew_time);

        if (Common_Get(island_weather) == mEnv_WEATHER_RAIN) {
            agb->weather = mEnv_WEATHER_RAIN;
        } else {
            agb->weather = mEnv_WEATHER_CLEAR;
        }

        npc_idx = mISL_get_npc_idx(Save_Get(island).animal.id.npc_id);
        mISL_int((u32*)&agb->npc_idx, (u32*)&npc_idx, 1);
        temp = (u32*)zelda_malloc_align(0x1000, 32);
        agb->grass_tex_type = gc->grass_tex_type;

        if (temp != NULL) {
            bzero(temp, 0x1000);
            mISL_get_npc_tex(agb->npc_tex, temp, npc_idx);
            bzero(temp, 0x1000);
            mISL_get_npc_pal(agb->npc_pal, (u16*)temp, npc_idx);
            bzero(temp, 0x1000);
            mISL_get_earth_tex(agb->earth_tex, temp, agb->grass_tex_type);
            zelda_free(temp);
        }

        agb->last_song_to_island = gc->last_song_to_island;
        agb->last_song_from_island = gc->last_song_from_island;
        // remove the land info portion from the checksum as it can change
        agb->checksum = mISL_GetFlatCheckSum((u8*)agb, sizeof(Island_agb_c), agb->checksum,
                                             mISL_ReturnCheckSum((u8*)&agb->landinfo, 16));
    }
}

static void mISL_toHole(mActor_name_t* fg, u16* deposit, int bx, int bz) {
    int ut_x;
    int ut_z;

    for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
        for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
            if (*fg == ITM_PITFALL && (((*deposit) >> ut_x) & 1) != 0) {
                int hole_no = mCoBG_BnumUnum2HoleNumber(bx, bz, ut_x, ut_z);

                if (hole_no < 0 || hole_no >= 25) {
                    hole_no = 0;
                }

                fg[0] = BURIED_PITFALL_START + hole_no;
                deposit[0] &= ~(1 << ut_x);
            }

            fg++;
        }

        deposit++;
    }
}

/* @nonmatching */
#ifndef MUST_MATCH
extern void mISL_agb_to_gc(Island_c* gc, Island_agb_c* agb) {
    int island_x_blocks[mISL_FG_BLOCK_X_NUM];
    int i;

    if (agb != NULL) {
        bcopy(agb->name, gc->name, mISL_ISLAND_NAME_LEN);
        mISL_agb_to_gc_iandinfo(&gc->landinfo, &agb->landinfo);
        mISL_agb_to_gc_fgblock(gc->fgblock[0], agb->fgblock[0]);
        mISL_agb_to_gc_cottage(&gc->cottage, &agb->cottage);
        bcopy(&agb->flag_design, &gc->flag_design, sizeof(mNW_original_design_c));
        mISL_agb_to_gc_animal(&gc->animal, &agb->animal);
        mISL_short((u16*)gc->deposit, (u16*)agb->deposit, sizeof(gc->deposit) / sizeof(u16));
        bcopy(agb->bg_data, gc->bg_data, sizeof(gc->bg_data));
        mISL_gc_to_agb_time(&gc->renew_time, &agb->renew_time);
        gc->last_song_to_island = agb->last_song_to_island;
        gc->last_song_from_island = agb->last_song_from_island;

        if (mFI_CheckFieldData() == TRUE) {
            bzero(island_x_blocks, sizeof(island_x_blocks));
            mFI_GetIslandBlockNumX(island_x_blocks);

            for (i = 0; i < mISL_FG_BLOCK_X_NUM; i++) {
                int idx = i + island_x_blocks[0];
                mActor_name_t* fg_p = &gc->fgblock[0][i].items[0][0];
                u16* deposit_p = (u16*)&gc->deposit[(u16)i]; // the access to deposit is strange, casting to u16 is
                                                             // incorrect but it makes all other instructions correct

                mISL_toHole(fg_p, deposit_p, idx, mISL_BLOCK_Z);
            }
        }
    }
}
#else
extern asm void mISL_agb_to_gc(Island_c* gc, Island_agb_c* agb) {
#include "asm/803b5948.s"
}
#endif
