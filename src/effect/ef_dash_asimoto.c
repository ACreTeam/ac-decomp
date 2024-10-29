#include "ef_effect_control.h"

#include "m_common_data.h"

static void eDashAsimoto_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eDashAsimoto_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eDashAsimoto_mv(eEC_Effect_c* effect, GAME* game);
static void eDashAsimoto_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_dash_asimoto = {
    // clang-format off
    &eDashAsimoto_init,
    &eDashAsimoto_ct,
    &eDashAsimoto_mv,
    &eDashAsimoto_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static xyz_t eDahsAsimoto_GetMakeOffset(xyz_t pos, s16 angle_y) {
    xyz_t base_ofs = { 0.0f, 0.0f, 10.0f };

    sMath_RotateY(&base_ofs, SHORTANGLE2RAD(angle_y));
    xyz_t_add(&pos, &base_ofs, &pos);
    return pos;
}

static void eDashAsimoto_Hanabira_Make(eEC_Effect_c* effect, GAME* game) {
    mActor_name_t* item_p = mFI_GetUnitFG(effect->position);

    if (item_p != NULL && *item_p >= FLOWER_PANSIES0 && *item_p <= FLOWER_TULIP2) {
        int i;

        for (i = 0; i < 2; i++) {
            eEC_CLIP->effect_make_proc(eEC_EFFECT_HANABIRA, effect->position, effect->prio, 0, game, effect->item_name,
                                       *item_p - FLOWER_PANSIES0, 0);
        }
    }
}

static void eDashAsimoto_RainDay(eEC_Effect_c* effect, GAME* game) {
    xyz_t pos = effect->position;
    xyz_t bush_pos;
    xyz_t ofs;
    int i;

    ofs = eDahsAsimoto_GetMakeOffset(pos, effect->effect_specific[0]);
    bush_pos = ofs;

    switch (effect->arg0) {
        case mCoBG_ATTRIBUTE_BUSH:
            i = 2;
            do {
                eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_HAPPA, bush_pos, effect->prio, effect->effect_specific[0],
                                           game, effect->item_name, effect->arg0, 1);
            } while (i-- != 0);
            break;
        case mCoBG_ATTRIBUTE_FLOOR:
            break;
        case mCoBG_ATTRIBUTE_WAVE:
            eEC_CLIP->effect_make_proc(eEC_EFFECT_SIBUKI, effect->position, effect->prio, effect->effect_specific[0],
                                       game, effect->item_name, effect->arg0, 1);
            break;
        default:
            eEC_CLIP->effect_make_proc(eEC_EFFECT_SIBUKI, effect->position, effect->prio, effect->effect_specific[0],
                                       game, effect->item_name, effect->arg0, 0);
            break;
    }
}

static void eDashAsimoto_FineDay(eEC_Effect_c* effect, GAME* game) {
    xyz_t pos = effect->position;
    xyz_t bush_pos;
    xyz_t ofs;
    int season;
    int i;

    ofs = eDahsAsimoto_GetMakeOffset(pos, effect->effect_specific[0]);
    bush_pos = ofs;
    season = Common_Get(time.season);

    switch (season) {
        case mTM_SEASON_WINTER: {
            switch (effect->arg0) {
                case mCoBG_ATTRIBUTE_GRASS0:
                case mCoBG_ATTRIBUTE_GRASS1:
                case mCoBG_ATTRIBUTE_GRASS2:
                case mCoBG_ATTRIBUTE_GRASS3:
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_YUKIHANE, effect->position, effect->prio,
                                               effect->effect_specific[0], game, effect->item_name, effect->arg0,
                                               effect->arg1);
                    break;
                case mCoBG_ATTRIBUTE_BUSH:
                    i = 2;
                    do {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_HAPPA, bush_pos, effect->prio,
                                                   effect->effect_specific[0], game, effect->item_name, effect->arg0,
                                                   1);
                    } while (i-- != 0);

                    i = 2;
                    do {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_YUKI, bush_pos, effect->prio,
                                                   effect->effect_specific[0], game, effect->item_name, effect->arg0,
                                                   0);
                    } while (i-- != 0);
                    break;
                case mCoBG_ATTRIBUTE_FLOOR:
                    break;
                case mCoBG_ATTRIBUTE_SAND:
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_SANDSPLASH, effect->position, effect->prio,
                                               effect->effect_specific[0], game, effect->item_name, effect->arg0, 0);
                    break;
                case mCoBG_ATTRIBUTE_WAVE:
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_SIBUKI, effect->position, effect->prio,
                                               effect->effect_specific[0], game, effect->item_name, effect->arg0, 1);
                    break;
                default:
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_DUST, effect->position, effect->prio,
                                               effect->effect_specific[0], game, effect->item_name, effect->arg0, 8);
                    break;
            }
            break;
        }

        default: {
            switch (effect->arg0) {
                case mCoBG_ATTRIBUTE_BUSH:
                    i = 2;
                    do {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_HAPPA, bush_pos, effect->prio,
                                                   effect->effect_specific[0], game, effect->item_name, effect->arg0,
                                                   1);
                    } while (i-- != 0);
                    break;
                case mCoBG_ATTRIBUTE_FLOOR:
                    break;
                case mCoBG_ATTRIBUTE_SAND:
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_SANDSPLASH, effect->position, effect->prio,
                                               effect->effect_specific[0], game, effect->item_name, effect->arg0, 0);
                    break;
                case mCoBG_ATTRIBUTE_WAVE:
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_SIBUKI, effect->position, effect->prio,
                                               effect->effect_specific[0], game, effect->item_name, effect->arg0, 1);
                    break;
                default:
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_DUST, effect->position, effect->prio,
                                               effect->effect_specific[0], game, effect->item_name, effect->arg0, 8);
                    break;
            }
            break;
        }
    }
}

static void eDashAsimoto_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_DASH_ASIMOTO, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

typedef void (*eDashAsimoto_PROC)(eEC_Effect_c*, GAME*);

static void eDashAsimoto_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // clang-format off
    static eDashAsimoto_PROC asimoto_func_table[mEnv_WEATHER_NUM] = {
        &eDashAsimoto_FineDay,
        &eDashAsimoto_RainDay,
        &eDashAsimoto_FineDay,
        &eDashAsimoto_FineDay,
        /* @BUG - the step effect process func for 'leaves' weather is left as NULL */
        #ifdef BUGFIXES
        &eDashAsimoto_FineDay,
        #else
        NULL,
        #endif
    };
    // clang-format on
    s16 weather = mEnv_NowWeather();
    s16* angle_p = (s16*)ct_arg;

    effect->timer = 0;
    eDashAsimoto_Hanabira_Make(effect, game);
    effect->effect_specific[0] = *angle_p;
    (*asimoto_func_table[weather])(effect, game);
}

static void eDashAsimoto_mv(eEC_Effect_c* effect, GAME* game) {
    // empty
}

static void eDashAsimoto_dw(eEC_Effect_c* effect, GAME* game) {
    // empty
}
