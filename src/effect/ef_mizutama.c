#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"

static void eMizutama_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eMizutama_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eMizutama_mv(eEC_Effect_c* effect, GAME* game);
static void eMizutama_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_mizutama = {
    // clang-format off
    &eMizutama_init,
    &eMizutama_ct,
    &eMizutama_mv,
    &eMizutama_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

typedef struct {
    f32 rng_y;
    f32 base_y;
    f32 base_z;
    f32 relative_z;
} eMizutama_spd_data_c;

static void eMizutama_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_MIZUTAMA, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eMizutama_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // @ 8057c630
    static eMizutama_spd_data_c mzt_spd_data[6] = {
        {2.0f, 1.5f, 1.5f, 2.0f},
        {1.75f, 2.0f, 1.5f, 1.75f},
        {1.75f, 2.0f, 1.5f, 2.25f},
        {1.25f, 1.35f, 2.5f, 0.0f},
        {1.5f, 3.0f, 1.0f, 0.0f},
        {2.0f, 3.0f, 1.0f, 0.0f},
    };

    // @ 8057c690
    static s16 mizutama_vec_angle[11] = {
        0x0000, 0x071C, 0x2EEE, 0x1555, 0xE71D, 0xD99A, 0x5555, 0x4000,
        0xC71D, 0xA667, 0xC000
    };

    s16* angle_p = (s16*)ct_arg;
    s16 angle = *angle_p;

    effect->timer = 50;
    effect->effect_specific[2] = ((u16)effect->arg1 >> 12) & 0xF;
    effect->effect_specific[3] = effect->arg1 & 0x0FFF;
    effect->effect_specific[0] = 0;
    effect->effect_specific[1] = 1;

    effect->scale.x = effect->scale.y = effect->scale.z = 0.008f;
    effect->acceleration.x = 0.0f;
    effect->acceleration.y = -0.375f;
    effect->acceleration.z = 0.0f;

    effect->velocity.y = mzt_spd_data[effect->effect_specific[2]].base_y + RANDOM_F(mzt_spd_data[effect->effect_specific[2]].rng_y);
    effect->velocity.z = mzt_spd_data[effect->effect_specific[2]].base_z;
    angle = *angle_p + mizutama_vec_angle[effect->effect_specific[3]];
    eEC_CLIP->vector_rotate_y_proc(&effect->velocity, SHORT2RAD_ANGLE2(angle));
    effect->velocity.x += sin_s(*angle_p) * mzt_spd_data[effect->effect_specific[2]].relative_z;
    effect->velocity.z += cos_s(*angle_p) * mzt_spd_data[effect->effect_specific[2]].relative_z;
    
    effect->position.x += RANDOM2_F(6.0f);
    effect->position.z += RANDOM2_F(6.0f);

    effect->offset.y = mCoBG_GetBgY_AngleS_FromWpos(NULL, effect->position, 0.0f);
    effect->offset.y += 3.0f;
}

static void eMizutama_mv(eEC_Effect_c* effect, GAME* game) {
    if (effect->effect_specific[0] == 0) {
        effect->offset.z = effect->offset.y;
        effect->offset.y = mCoBG_GetBgY_AngleS_FromWpos(NULL, effect->position, 0.0f);
        effect->offset.y += 3.0f;
        effect->offset.x = effect->position.y;

        xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
        xyz_t_add(&effect->position, &effect->velocity, &effect->position);
    }

    if ((effect->position.y <= effect->offset.y && effect->offset.x > effect->offset.y) || (effect->offset.y > effect->offset.x && effect->offset.z <= effect->offset.x)) {
        if (effect->position.y - effect->offset.y > effect->velocity.y) {
            if (effect->effect_specific[0] == 0) {
                u32 attr = mCoBG_Wpos2Attribute(effect->position, NULL);

                if (mCoBG_CheckWaterAttribute(attr)) {
                    xyz_t pos = effect->position;

                    pos.y = mCoBG_GetWaterHeight_File(effect->position, __FILE__, 214);
                    pos.z += 14.0f;
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HAMON, pos, effect->prio, 0, game, effect->item_name, 2, 0);
                }
            }

            effect->position.y = effect->offset.y;
        }

        if (effect->effect_specific[1] == 1) {
            if (effect->effect_specific[0] < 6) {
                effect->effect_specific[0]++;
                effect->effect_specific[1] = 0;
            } else {
                effect->timer = 0;
            }
        } else {
            effect->effect_specific[1] = 1;
        }
    }
}

extern u8 ef_koke_suiteki01_0_int_i4[];
extern u8 ef_koke_suiteki01_1_int_i4[];
extern u8 ef_koke_suiteki01_2_int_i4[];
extern u8 ef_koke_suiteki01_3_int_i4[];
extern Gfx ef_koke_suiteki01_00_modelT[];

static void eMizutama_dw(eEC_Effect_c* effect, GAME* game) {
    static u8* mizutama_tex_tbl[] = {
        ef_koke_suiteki01_0_int_i4, ef_koke_suiteki01_1_int_i4, ef_koke_suiteki01_2_int_i4, ef_koke_suiteki01_3_int_i4,
    };

    s16 idx = CLAMP(effect->effect_specific[0] >> 1, 0, 3);

    effect->scale.x = eEC_CLIP->calc_adjust_proc(effect->timer, 0, 40, 0.004f, 0.008f);
    effect->scale.y = effect->scale.z = effect->scale.x;

    _texture_z_light_fog_prim_xlu(game->graph);
    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_proc(game, &effect->position, &effect->scale);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, mizutama_tex_tbl[idx]);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_koke_suiteki01_00_modelT);

    CLOSE_DISP(game->graph);
}
