#include "ef_effect_control.h"

#include "m_common_data.h"

static void eTaberu_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eTaberu_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eTaberu_mv(eEC_Effect_c* effect, GAME* game);
static void eTaberu_dw(eEC_Effect_c* effect, GAME* game);

extern Gfx ef_taberu01_00_modelT[];
extern Gfx ef_taberu01_01_modelT[];
extern Gfx ef_taberu01_02_modelT[];
extern Gfx ef_taberu01_03_modelT[];

static Gfx* eTaberu_model_table[] = {
    ef_taberu01_00_modelT,
    ef_taberu01_01_modelT,
    ef_taberu01_02_modelT,
    ef_taberu01_03_modelT,
};

eEC_PROFILE_c iam_ef_taberu = {
    // clang-format off
    &eTaberu_init,
    &eTaberu_ct,
    &eTaberu_mv,
    &eTaberu_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eTaberu_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    xyz_t ofs;

    ofs.x = 0.0f;
    ofs.y = 0.0f;
    ofs.z = 0.0f;

    eEC_CLIP->make_effect_proc(eEC_EFFECT_TABERU, pos, &ofs, game, &angle, item_name, prio, 0, 0);
}

static void eTaberu_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    s16 angle = *(s16*)ct_arg;

    if (effect->item_name == SP_NPC_ARTIST) {
        effect->position.x += sin_s(angle) * 15.0f;
        effect->position.y += -15.0f;
        effect->position.z += cos_s(angle) * 15.0f;
    } else {
        effect->position.x += sin_s(angle) * 13.0f;
        effect->position.y += -10.0f;
        effect->position.z += cos_s(angle) * 13.0f;
    }

    effect->scale.x = 0.0045f;
    effect->scale.y = 0.0045f;
    effect->scale.z = 0.0045f;

    effect->effect_specific[0] = 0;

    effect->timer = 44;
}

static void eTaberu_mv(eEC_Effect_c* effect, GAME* game) {
    effect->effect_specific[0] += 1;
}

static void eTaberu_dw(eEC_Effect_c* effect, GAME* game) {
    s16 idx = ((u16)effect->effect_specific[0] >> 2) & 3;

    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_offset_proc(game, &effect->position, &effect->scale, &effect->offset);

    gSPDisplayList(NEXT_POLY_XLU_DISP, eTaberu_model_table[idx]);

    CLOSE_DISP(game->graph);
}
