#include "ef_effect_control.h"
#include "m_common_data.h"
#include "m_player_lib.h"

static void eHanabiSet_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eHanabiSet_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eHanabiSet_mv(eEC_Effect_c* effect, GAME* game);
static void eHanabiSet_dw(eEC_Effect_c* effect, GAME* game);

#define EFFECT_LIFETIME 200

eEC_PROFILE_c iam_ef_hanabi_set = {
    // clang-format off
    &eHanabiSet_init,
    &eHanabiSet_ct,
    &eHanabiSet_mv,
    &eHanabiSet_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

typedef struct {
    s16 frame;
    s16 effect_id;
} eHanabiSet_sqdt;

typedef struct {
    eHanabiSet_sqdt* frame_effects;
    int count;
} eHanabiSet_set;

eHanabiSet_sqdt eHanabiSet_sqdt1[] = { { 0, eEC_EFFECT_HANABI_HOSHI },
                                       { 30, eEC_EFFECT_HANABI_HOSHI },
                                       { 50, eEC_EFFECT_HANABI_HOSHI },
                                       { 120, eEC_EFFECT_HANABI_BOTAN1 },
                                       { 190, eEC_EFFECT_HANABI_BOTAN1 } };

eHanabiSet_set eHanabiSet_set1 = { eHanabiSet_sqdt1, ARRAY_COUNT(eHanabiSet_sqdt1) };

eHanabiSet_sqdt eHanabiSet_sqdt2[] = { { 0, eEC_EFFECT_HANABI_BOTAN1 },
                                       { 50, eEC_EFFECT_HANABI_BOTAN1 },
                                       { 80, eEC_EFFECT_HANABI_BOTAN1 },
                                       { 140, eEC_EFFECT_HANABI_BOTAN2 },
                                       { 190, eEC_EFFECT_HANABI_BOTAN2 } };

eHanabiSet_set eHanabiSet_set2 = { eHanabiSet_sqdt2, ARRAY_COUNT(eHanabiSet_sqdt2) };

eHanabiSet_sqdt eHanabiSet_sqdt3[] = { { 0, eEC_EFFECT_HANABI_YANAGI },
                                       { 50, eEC_EFFECT_HANABI_YANAGI },
                                       { 80, eEC_EFFECT_HANABI_YANAGI },
                                       { 140, eEC_EFFECT_HANABI_BOTAN2 },
                                       { 190, eEC_EFFECT_HANABI_BOTAN2 } };

eHanabiSet_set eHanabiSet_set3 = { eHanabiSet_sqdt3, ARRAY_COUNT(eHanabiSet_sqdt3) };

eHanabiSet_sqdt eHanabiSet_sqdt4[] = { { 0, eEC_EFFECT_HANABI_HOSHI },
                                       { 50, eEC_EFFECT_HANABI_YANAGI },
                                       { 80, eEC_EFFECT_HANABI_YANAGI },
                                       { 140, eEC_EFFECT_HANABI_BOTAN1 },
                                       { 190, eEC_EFFECT_HANABI_BOTAN1 } };

eHanabiSet_set eHanabiSet_set4 = { eHanabiSet_sqdt4, ARRAY_COUNT(eHanabiSet_sqdt4) };

eHanabiSet_sqdt eHanabiSet_sqdt5[] = { { 0, eEC_EFFECT_HANABI_HOSHI },    { 20, eEC_EFFECT_HANABI_HOSHI },
                                       { 50, eEC_EFFECT_HANABI_BOTAN2 },  { 90, eEC_EFFECT_HANABI_BOTAN2 },
                                       { 140, eEC_EFFECT_HANABI_HOSHI },  { 160, eEC_EFFECT_HANABI_BOTAN1 },
                                       { 170, eEC_EFFECT_HANABI_BOTAN1 }, { 170, eEC_EFFECT_HANABI_BOTAN1 } };

eHanabiSet_set eHanabiSet_set5 = { eHanabiSet_sqdt5, ARRAY_COUNT(eHanabiSet_sqdt5) };

eHanabiSet_sqdt eHanabiSet_sqdt6[] = { { 0, eEC_EFFECT_HANABI_BOTAN1 },   { 20, eEC_EFFECT_HANABI_BOTAN2 },
                                       { 50, eEC_EFFECT_HANABI_BOTAN2 },  { 90, eEC_EFFECT_HANABI_YANAGI },
                                       { 140, eEC_EFFECT_HANABI_YANAGI }, { 160, eEC_EFFECT_HANABI_HOSHI },
                                       { 170, eEC_EFFECT_HANABI_BOTAN2 }, { 170, eEC_EFFECT_HANABI_BOTAN2 } };

eHanabiSet_set eHanabiSet_set6 = { eHanabiSet_sqdt6, ARRAY_COUNT(eHanabiSet_sqdt6) };

eHanabiSet_sqdt eHanabiSet_sqdt7[] = { { 0, eEC_EFFECT_HANABI_BOTAN2 },   { 20, eEC_EFFECT_HANABI_BOTAN2 },
                                       { 50, eEC_EFFECT_HANABI_HOSHI },   { 90, eEC_EFFECT_HANABI_HOSHI },
                                       { 140, eEC_EFFECT_HANABI_YANAGI }, { 160, eEC_EFFECT_HANABI_YANAGI },
                                       { 170, eEC_EFFECT_HANABI_YANAGI }, { 170, eEC_EFFECT_HANABI_YANAGI } };

eHanabiSet_set eHanabiSet_set7 = { eHanabiSet_sqdt7, ARRAY_COUNT(eHanabiSet_sqdt7) };

eHanabiSet_sqdt eHanabiSet_sqdt8[] = { { 0, eEC_EFFECT_HANABI_YANAGI },   { 10, eEC_EFFECT_HANABI_YANAGI },
                                       { 20, eEC_EFFECT_HANABI_YANAGI },  { 30, eEC_EFFECT_HANABI_YANAGI },
                                       { 140, eEC_EFFECT_HANABI_BOTAN2 }, { 160, eEC_EFFECT_HANABI_BOTAN2 },
                                       { 170, eEC_EFFECT_HANABI_BOTAN2 }, { 190, eEC_EFFECT_HANABI_BOTAN2 } };

eHanabiSet_set eHanabiSet_set8 = { eHanabiSet_sqdt8, ARRAY_COUNT(eHanabiSet_sqdt8) };

eHanabiSet_set* eHanabiSet_set_table[] = { &eHanabiSet_set1, &eHanabiSet_set2, &eHanabiSet_set3, &eHanabiSet_set4,
                                           &eHanabiSet_set5, &eHanabiSet_set6, &eHanabiSet_set7, &eHanabiSet_set8 };

static void eHanabiSet_SearchNicePos(xyz_t* outPos, GAME* game) {
    PLAYER_ACTOR* player = GET_PLAYER_ACTOR_GAME(game);
    xyz_t zerovec = { 0.f, 0.f, 0.f };
    *outPos = zerovec;
    if (player) {
        xyz_t playerPos = player->actor_class.world.position;
        xyz_t wpos = { 0.f, 0.f, 0.f };
        int bx, bz;
        if (mFI_BlockKind2BkNum(&bx, &bz, mRF_BLOCKKIND_POOL) && mFI_BkNum2WposXZ(&wpos.x, &wpos.z, bx, bz)) {
            wpos.x += 320.f;
            wpos.y = 0.f;
            wpos.z += 320.f;
            outPos->x = (wpos.x + playerPos.x) * 0.5f;
            outPos->y = mFI_BkNum2BaseHeight(bx, bz) + 20.f;
            outPos->z = (wpos.z + playerPos.z) * 0.5f - 40.f;
        }
    }
}

static void eHanabiSet_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    xyz_t outPos;
    eHanabiSet_SearchNicePos(&outPos, game);
    eEC_CLIP->make_effect_proc(eEC_EFFECT_HANABI_SET, outPos, NULL, game, NULL, item_name, prio, 0, 0);
}

static void eHanabiSet_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    int f = RANDOM(1000.f) % 4;
    int hourEndMinusOne = mEv_get_end_time(mEv_EVENT_FIREWORKS_SHOW) - 1;
    lbRTC_hour_t hour = Common_Get(time.rtc_time.hour);
    effect->timer = EFFECT_LIFETIME;
    if (hour > hourEndMinusOne && hour <= mEv_get_end_time(mEv_EVENT_FIREWORKS_SHOW)) {
        effect->effect_specific[1] = TRUE;
        effect->effect_specific[0] = f + 4;
    } else {
        effect->effect_specific[1] = FALSE;
        effect->effect_specific[0] = f;
    }
}

static void eHanabiSet_mv(eEC_Effect_c* effect, GAME* game) {
    s16 alive_frames = EFFECT_LIFETIME - effect->timer;
    int idx = effect->effect_specific[0];
    eHanabiSet_set* set = eHanabiSet_set_table[idx];
    eHanabiSet_sqdt* frame_effect = set->frame_effects;
    int i;
    int count = set->count;
    eHanabiSet_SearchNicePos(&effect->position, game);
    for (i = 0; i < count; frame_effect++, i++) {
        if (frame_effect->frame == alive_frames) {
            xyz_t effect_position = effect->position;
            int effect_id = frame_effect->effect_id;
            int bx, bz;
            s16 arg = 0;
            if (effect->effect_specific[1] == 1) {
                arg = 1;
            }
            effect_position.x += RANDOM_F(250.f) - 125.f;
            effect_position.z += RANDOM_F(250.f) - 125.f;
            mFI_Wpos2BlockNum(&bx, &bz, effect_position);
            if (!eEC_CLIP->check_lookat_block_proc(effect->position) ||
                mFI_CheckBlockKind_OR(bx, bz, mRF_BLOCKKIND_SLOPE | mRF_BLOCKKIND_CLIFF)) {
                effect_id = eEC_EFFECT_HANABI_DUMMY;
            }
            eEC_CLIP->effect_make_proc(effect_id, effect_position, effect->prio, 0, game,
                                       (mActor_name_t)effect->item_name, arg, 0);
        }
    }
}

static void eHanabiSet_dw(eEC_Effect_c* effect, GAME* game) {
    return;
}
