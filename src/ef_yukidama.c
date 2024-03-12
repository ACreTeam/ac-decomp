#include "ef_effect_control.h"

#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "m_debug.h"

static void eYukidama_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eYukidama_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eYukidama_mv(eEC_Effect_c* effect, GAME* game);
static void eYukidama_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_yukidama = {
    // clang-format off
    &eYukidama_init,
    &eYukidama_ct,
    &eYukidama_mv,
    &eYukidama_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

typedef struct ykd_speed_data_s {
    f32 range_y;
    f32 base_y;
    f32 base_z;
    f32 vel_z;
} eYukidama_spd_data_c;

static void eYukidama_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_YUKIDAMA, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eYukidama_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    static eYukidama_spd_data_c ykd_spd_data[] = {
        { 1.5f, 1.25f, 1.0f, 1.75f }, { 2.0f, 1.35f, 1.0f, 1.6f }, { 2.0f, 1.35f, 1.0f, 2.0f },
        { 1.5f, 1.85f, 1.5f, 0.0f },  { 2.0f, 2.5f, 1.0f, 0.0f },
    };

    static s16 yukidama_vec_angle[] = {
        DEG2SHORT_ANGLE(0.0f),        DEG2SHORT_ANGLE(9.997559f),  DEG2SHORT_ANGLE(65.994873f),
        DEG2SHORT_ANGLE(29.998169f),  DEG2SHORT_ANGLE(325.00305f), DEG2SHORT_ANGLE(306.002197f),
        DEG2SHORT_ANGLE(119.998169f), DEG2SHORT_ANGLE(90.0f),      DEG2SHORT_ANGLE(280.003052f),
        DEG2SHORT_ANGLE(234.003296f),
    };

    s16* angle_p = (s16*)ct_arg;
    s16 angle;

    effect->timer = 50;
    effect->effect_specific[2] = (effect->arg1 >> 12) & 0xF;
    effect->effect_specific[3] = effect->arg1 & 0x0FFF;
    effect->effect_specific[0] = 0;
    effect->effect_specific[1] = TRUE;

    if (effect->effect_specific[2] == 0) {
        effect->scale.x = effect->scale.y = effect->scale.z = 0.007f;
    } else {
        effect->scale.x = effect->scale.y = effect->scale.z = 0.006f;
    }

    effect->acceleration.x = 0.0f;
    effect->acceleration.y = -0.3f;
    effect->acceleration.z = 0.0f;

    effect->velocity.y =
        ykd_spd_data[effect->effect_specific[2]].base_y + RANDOM_F(ykd_spd_data[effect->effect_specific[2]].range_y);
    effect->velocity.z = ykd_spd_data[effect->effect_specific[2]].base_z;

    angle = *angle_p + yukidama_vec_angle[effect->effect_specific[3]];
    eEC_CLIP->vector_rotate_y_proc(&effect->velocity, ((f32)(int)angle) * 0.0000958738f);

    effect->velocity.x += ykd_spd_data[effect->effect_specific[2]].vel_z * sin_s(*angle_p);
    effect->velocity.z += ykd_spd_data[effect->effect_specific[2]].vel_z * cos_s(*angle_p);

    effect->position.x += fqrand2() * 6.0f;
    effect->position.z += fqrand2() * 6.0f;

    effect->offset.y = mCoBG_GetBgY_AngleS_FromWpos(NULL, effect->position, 0.0f);
    effect->offset.y += 3.0f;
}

static void eYukidama_mv(eEC_Effect_c* effect, GAME* game) {
    if (effect->effect_specific[0] == 0) {
        effect->offset.z = effect->offset.y;
        effect->offset.y = mCoBG_GetBgY_AngleS_FromWpos(NULL, effect->position, 0.0f);
        effect->offset.y += 3.0f;
        effect->offset.x = effect->position.y;

        xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
        xyz_t_add(&effect->position, &effect->velocity, &effect->position);
    }

    if ((effect->position.y <= effect->offset.y && effect->offset.x > effect->offset.y) ||
        (effect->offset.y > effect->offset.x && effect->offset.z <= effect->offset.x)) {
        /* If deltaY > velocityY */
        if ((effect->position.y - effect->offset.y) > effect->velocity.y) {
            if (effect->effect_specific[0] == 0) {
                u32 attr = mCoBG_Wpos2Attribute(effect->position, NULL);

                if (mCoBG_CheckWaterAttribute(attr)) {
                    xyz_t pos = effect->position;

                    pos.y = mCoBG_GetWaterHeight_File(effect->position, __FILE__, 220);
                    pos.z += 14.0f;

                    eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HAMON, pos, effect->prio, 0, game, effect->item_name, 2,
                                               0);
                }
            }

            effect->position.y = effect->offset.y;
        }

        if (effect->effect_specific[1] == TRUE) {
            if (effect->effect_specific[0] < 6) {
                effect->effect_specific[0]++;
                effect->effect_specific[1] = FALSE;
            } else {
                effect->timer = 0;
            }
        } else {
            effect->effect_specific[1] = TRUE;
        }
    }
}

extern u8 ef_koke_yuki01_0_inta_ia8[];
extern u8 ef_koke_yuki01_1_inta_ia8[];
extern u8 ef_koke_yuki01_2_inta_ia8[];
extern u8 ef_koke_yuki01_3_inta_ia8[];

extern Gfx ef_koke_yuki01_00_modelT[];

static void eYukidama_dw(eEC_Effect_c* effect, GAME* game) {
    static u8* yukidama_tex_tbl[] = {
        ef_koke_yuki01_0_inta_ia8,
        ef_koke_yuki01_1_inta_ia8,
        ef_koke_yuki01_2_inta_ia8,
        ef_koke_yuki01_3_inta_ia8,
    };

    s16 tex_idx = CLAMP(effect->effect_specific[0] >> 1, 0, 3);

    effect->scale.x = eEC_CLIP->calc_adjust_proc(effect->timer, 10, 30, 0.0035f, 0.007f);
    effect->scale.y = effect->scale.z = effect->scale.x;

    _texture_z_light_fog_prim_xlu(game->graph);

    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_proc(game, &effect->position, &effect->scale);
    gSPSegment(NEXT_POLY_XLU_DISP, G_MWO_SEGMENT_8, yukidama_tex_tbl[tex_idx]);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_koke_yuki01_00_modelT);

    CLOSE_DISP(game->graph);
}
