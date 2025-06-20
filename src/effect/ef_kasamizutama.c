#include "ef_effect_control.h"

#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_rcp.h"


static f32 eKasamizutama_scale_table[] = {
    0.0f, 0.1f, 0.3f, 0.5f, 0.7f, 0.9f, 1.0f, 0.9f, 0.7f, 0.5f
};

extern Gfx ef_koke_suiteki01_0_int_i4[];
extern Gfx ef_koke_suiteki01_00_modelT[];

static void eKasamizutama_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKasamizutama_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKasamizutama_mv(eEC_Effect_c* effect, GAME* game);
static void eKasamizutama_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_kasamizutama = {
    // clang-format off
    &eKasamizutama_init,
    &eKasamizutama_ct,
    &eKasamizutama_mv,
    &eKasamizutama_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eKasamizutama_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_KASAMIZUTAMA, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eKasamizutama_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    s16 angle = *(s16*)ct_arg;
    s16 rand = qrand();
    s16 rand_angle = DEG2SHORT_ANGLE2(45.0f) + DEG2SHORT_ANGLE2(RANDOM_F(45.0f));
    xyz_t pos;
    f32 sin = 2.5f * sin_s(rand_angle);
    
    Matrix_RotateY(angle, MTX_LOAD);
    Matrix_RotateX(DEG2SHORT_ANGLE2(-45.0f), MTX_MULT);
    
    pos.x = (sin) * sin_s(rand);
    pos.y = 2.5f * cos_s(rand_angle);
    pos.z = (sin) * cos_s(rand);
    
    Matrix_Position(&pos, &effect->velocity);
    
    effect->acceleration = ZeroVec;
    effect->acceleration.y = -0.105f;
    effect->timer = 20;
}

static void eKasamizutama_mv(eEC_Effect_c* effect, GAME* game) {
    xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
    xyz_t_add(&effect->position, &effect->velocity, &effect->position);
}

static void eKasamizutama_dw(eEC_Effect_c* effect, GAME* game) {
    s16 remain = 20 - effect->timer;
    s16 frame = remain >> 1;
    
    effect->scale.x = effect->scale.y = effect->scale.z = eKasamizutama_scale_table[frame] * 0.005f;
    _texture_z_light_fog_prim_xlu(game->graph);

    OPEN_DISP(game->graph);
    
    eEC_CLIP->auto_matrix_xlu_proc(game, &effect->position, &effect->scale);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, ef_koke_suiteki01_0_int_i4);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_koke_suiteki01_00_modelT);
    
    CLOSE_DISP(game->graph);
}
