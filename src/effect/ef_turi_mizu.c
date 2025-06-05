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

static void eTM_CallEffect(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    switch (arg0) {
        case 0: {
            xyz_t hane_pos;

            eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HAMON, pos, 1, angle, game, EMPTY_NO, 0, 0);

            hane_pos = pos;
            hane_pos.y += 3.0f;
            hane_pos.z += 5.0f;
            eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HANE0, hane_pos, 1, angle, game, EMPTY_NO, 0, 0);
            break;
        }

        case 1: {
            eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HAMON, pos, 1, angle, game, EMPTY_NO, 1, 0);
            break;
        }

        case 2: {
            eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HAMON, pos, 1, angle, game, EMPTY_NO, 0, 0);
            break;
        }

        case 3: {
            xyz_t hane_pos;

            eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HAMON, pos, 1, angle, game, EMPTY_NO, 0, 0);

            hane_pos = pos;
            hane_pos.y += 3.0f;
            hane_pos.z += 5.0f;
            eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HANE1, hane_pos, 1, angle, game, EMPTY_NO, 0, 0);
            break;
        }

        case 4:
        case 5:
        case 6:
        case 7: 
        case 8: {
            s16 type = arg0 - 4;
            s16 hamon_type[] = { 1, 0, 0, 1, 2 };

            eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HAMON, pos, 1, angle, game, EMPTY_NO, hamon_type[type], 0);
            eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HANE0, pos, 1, angle, game, EMPTY_NO, type, 0);
            break;
        }
    }
}

static void eTM_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    if (eEC_CLIP != NULL) {
        eTM_CallEffect(pos, prio, angle, game, item_name, arg0, arg1);
    }
    
    eEC_CLIP->make_effect_proc(eEC_EFFECT_TURI_MIZU, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eTM_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    s16 i;
    s16 n_drops = 4;
    s16* angle_p = (s16*)ct_arg;
    s16 angle = *angle_p;

    effect->effect_specific[5] = angle;
    switch (effect->arg0) {
        case 0:
        case 2:
            effect->timer = 16;
            break;
        case 1:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            if (effect->arg0 == 4) {
                n_drops = 3;
            } else if (effect->arg0 == 7 || effect->arg0 == 8) {
                n_drops = 2;
            }

            effect->timer = 20;
            for (i = 0; i < n_drops; i++) {
                effect->effect_specific[i] = RANDOM(10);
            }
            break;
    }
}

static void eTM_mv(eEC_Effect_c* effect, GAME* game) {
    s16 i;
    s16 timer = 16 - effect->timer;
    s16 n_drops = 4;
    GAME_PLAY* play = (GAME_PLAY*)game;

    // hack for 30FPS->60FPS
    if (play->game_frame & 1) {
        return;
    }

    switch (effect->arg0) {
        case 0:
        case 2:
            if (effect->timer == 1) {
                eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HAMON, effect->position, 1, effect->effect_specific[5], game, 0, 2, 0);
            }
            break;
        case 1:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            if (effect->arg0 == 4) {
                n_drops = 3;
            } else if (effect->arg0 == 7 || effect->arg0 == 8) {
                n_drops = 2;
            }

            for (i = 0; i < n_drops; i++) {
                if (effect->effect_specific[i] == timer) {
                    eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_SUITEKI, effect->position, 1, 0, game, 0, i, n_drops);
                }
            }
            break;
    }
}

static void eTM_dw(eEC_Effect_c* effect, GAME* game) {
    // nothing
}
