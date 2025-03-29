#include "ef_effect_control.h"

#include "m_common_data.h"

static void eWalk_Asimoto_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eWalk_Asimoto_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eWalk_Asimoto_mv(eEC_Effect_c* effect, GAME* game);
static void eWalk_Asimoto_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_walk_asimoto = {
    // clang-format off
    &eWalk_Asimoto_init,
    &eWalk_Asimoto_ct,
    &eWalk_Asimoto_mv,
    &eWalk_Asimoto_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static xyz_t eWalkAsimoto_GetMakeOffset(xyz_t pos, s16 angle_y) {
    xyz_t base_ofs = { 0.0f, 0.0f, 10.0f };

    sMath_RotateY(&base_ofs, SHORT2RAD_ANGLE2(angle_y));
    pos.x += base_ofs.x;
    pos.y += base_ofs.y;
    pos.z += base_ofs.z;
    return pos;
}

static void eWalkAsimoto_RainDay(xyz_t pos, int prio, s16 angle_y, GAME* game, u16 name, s16 arg0, s16 arg1) {
    xyz_t make_pos = eWalkAsimoto_GetMakeOffset(pos, angle_y);
    int count;

    switch (arg0) {
        case mCoBG_ATTRIBUTE_BUSH:
            count = 1;
            do {
                eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_HAPPA, make_pos, prio, angle_y, game, name, arg0, arg1);
            } while (count-- != 0);
            break;
    }
}

static void eWalkAsimoto_FineDay(xyz_t pos, int prio, s16 angle_y, GAME* game, u16 name, s16 arg0, s16 arg1) {
    xyz_t make_pos = eWalkAsimoto_GetMakeOffset(pos, angle_y);
    u32 season = Common_Get(time.season);
    int happa_count;
    int yuki_count;

    switch (season) {
        case mTM_SEASON_WINTER:
            switch (arg0) {
                case mCoBG_ATTRIBUTE_BUSH:
                    happa_count = 1;
                    do {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_HAPPA, make_pos, prio, angle_y, game, name, arg0, arg1);
                    } while (happa_count-- != 0);

                    yuki_count = 1;
                    do {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_YUKI, make_pos, prio, angle_y, game, name, arg0, 0);
                    } while (yuki_count-- != 0);
                    break;
                case mCoBG_ATTRIBUTE_GRASS1:
                case mCoBG_ATTRIBUTE_GRASS2:
                    break;
            }
            break;
        case mTM_SEASON_SPRING:
        case mTM_SEASON_SUMMER:
        case mTM_SEASON_AUTUMN:
            switch (arg0) {
                case mCoBG_ATTRIBUTE_BUSH:
                    happa_count = 1;
                    do {
                        eEC_CLIP->effect_make_proc(eEC_EFFECT_BUSH_HAPPA, make_pos, prio, angle_y, game, name, arg0, arg1);
                    } while (happa_count-- != 0);
                    break;
            }
            break;
    }
}

typedef void (*eWalkAsimoto_INIT_PROC)(xyz_t pos, int prio, s16 angle_y, GAME* game, u16 name, s16 arg0, s16 arg1);

static void eWalk_Asimoto_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    if (eEC_CLIP != NULL) {
        static eWalkAsimoto_INIT_PROC asimoto_func_table[] = {
            // clang-format off
            eWalkAsimoto_FineDay,
            eWalkAsimoto_RainDay,
            eWalkAsimoto_FineDay,
            eWalkAsimoto_FineDay,
            // @BUG - the step effect process func for 'leaves' weather is omitted
            // this bug causes ef_warau::eWU_init to be called, spawning the laughing effect instead
            #ifdef BUGFIXES
            eWalkAsimoto_FineDay,
            #endif
            // clang-format on
        };
        s16 weather = mEnv_NowWeather();

        (*asimoto_func_table[weather])(pos, prio, angle, game, item_name, arg0, arg1);
    }

    eEC_CLIP->make_effect_proc(eEC_EFFECT_WALK_ASIMOTO, pos, NULL, game, NULL, item_name, prio, 0, 0);
}

static void eWalk_Asimoto_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 0;
}

static void eWalk_Asimoto_mv(eEC_Effect_c* effect, GAME* game) {
    // nothing
}

static void eWalk_Asimoto_dw(eEC_Effect_c* effect, GAME* game) {
    // nothing
}
