#include "ef_effect_control.h"
#include "game_h.h"
#include "libc64/qrand.h"
#include "libu64/u64types.h"
#include "m_common_data.h"
#include <string.h>

static void eTM_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eTM_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eTM_mv(eEC_Effect_c* effect, GAME* game);
static void eTM_dw(eEC_Effect_c* effect, GAME* game);
static void eTM_CallEffect(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);

eEC_PROFILE_c iam_ef_turi_mizu = {
    // clang-format off
    &eTM_init,
    &eTM_ct,
    &eTM_mv,
    &eTM_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};


static void eTM_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    if (eEC_CLIP != NULL) {
        eTM_CallEffect(pos, prio, angle, game, item_name, arg0, arg1);
    }
    
    eEC_CLIP->make_effect_proc(eEC_EFFECT_TURI_MIZU, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eTM_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    // TODO
}

static void eTM_mv(eEC_Effect_c* effect, GAME* game) {
    // TODO
}

static void eTM_dw(eEC_Effect_c* effect, GAME* game) {
    // TODO
}
static void eTM_CallEffect(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    // TODO
}