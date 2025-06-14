#include "ef_effect_control.h"

#include "m_common_data.h"

extern Gfx ef_takurami01_yoko_modelT[];
extern Gfx ef_takurami01_yoko_modelT2[];

static void eTM_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eTM_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eTM_mv(eEC_Effect_c* effect, GAME* game);
static void eTM_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_takurami = {
    // clang-format off
    &eTM_init,
    &eTM_ct,
    &eTM_mv,
    &eTM_dw,
    eEC_IGNORE_DEATH,
    eEC_EFFECT_TAKURAMI_KIRA,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static Gfx* eTM_direct2disp[] = { ef_takurami01_yoko_modelT, ef_takurami01_yoko_modelT2 };

typedef struct {
    int prio;
    s16 angle;
    u16 item_name;
} eTM_data_c;

static void eTM_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eTM_data_c ct_arg;
    xyz_t ofs;
    xyz_t vec = { 0.0f, 0.0f, 6.9f };

    sMath_RotateY(&vec, SHORT2RAD_ANGLE2(angle));
    pos.x += vec.x;
    pos.y += vec.y;
    pos.z += vec.z;

    ofs.x = 0.0f;
    ofs.y = 0.0f;
    ofs.z = 0.0f;

    ct_arg.angle = angle;
    ct_arg.prio = prio;
    ct_arg.item_name = item_name;

    eEC_CLIP->make_effect_proc(eEC_EFFECT_TAKURAMI, pos, &ofs, game, &ct_arg, item_name, prio, 0, 0);
}

static void eTM_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    s16 angle_y, angle;
    u16 angle_diff;

    angle_y = (s16)getCamera2AngleY((GAME_PLAY*)game) + DEG2SHORT_ANGLE(180.0f);
    angle = ((eTM_data_c*)ct_arg)->angle;
    angle_diff = angle - angle_y;

    effect->acceleration.x = effect->position.x;
    effect->acceleration.y = effect->position.y;
    effect->acceleration.z = effect->position.z;

    effect->position.y += -3.0f;
    effect->position.z += 10.0f;

    effect->scale.x = 0.0f;
    effect->scale.y = 0.020000001f;
    effect->scale.z = 0.017f;

    effect->timer = 54;

    effect->effect_specific[2] = ((eTM_data_c*)ct_arg)->prio;
    effect->effect_specific[1] = ((eTM_data_c*)ct_arg)->angle;
    effect->effect_specific[3] = ((eTM_data_c*)ct_arg)->item_name;

    if (angle_diff >= DEG2SHORT_ANGLE2(180.0f)) {
        effect->effect_specific[0] = 0;
        effect->offset.x += 15.0f;
    } else {
        effect->effect_specific[0] = 1;
        effect->offset.x += -15.0f;
    }
    effect->offset.z = 15.0f;
}

static void eTM_mv(eEC_Effect_c* effect, GAME* game) {
    int prio;
    s16 angle;
    u16 item_name;

    s16 timer = 54 - effect->timer;

    if (timer == 0) {
        sAdo_OngenTrgStart(0x117, &effect->position);
    }

    if (timer == 10) {
        angle = effect->effect_specific[1];
        prio = effect->effect_specific[2];
        item_name = effect->effect_specific[3];
        if (eEC_CLIP != NULL) {
            eEC_CLIP->effect_make_proc(eEC_EFFECT_TAKURAMI_KIRA, effect->acceleration, prio, angle, game, item_name, 0,
                                       0);
        }
    }
}

static void eTM_dw(eEC_Effect_c* effect, GAME* game) {
    s16 timer = 54 - effect->timer;
    s16 idx = effect->effect_specific[0];
    u8 alpha;

    effect->scale.x = eEC_CLIP->calc_adjust_proc(timer, 0, 8, 0.0f, 0.017f);

    alpha = (int)eEC_CLIP->calc_adjust_proc(timer, 46, 54, 200.0f, 0.0f);

    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_offset_proc(game, &effect->position, &effect->scale, &effect->offset);

    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 0, 0, 0, alpha);
    gSPDisplayList(NEXT_POLY_XLU_DISP, eTM_direct2disp[idx]);

    CLOSE_DISP(game->graph);
}
