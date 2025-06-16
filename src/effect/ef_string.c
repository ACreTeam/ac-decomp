#include "ef_effect_control.h"

#include "m_common_data.h"
#include "m_font.h"
#include "main.h"

static void eString_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eString_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eString_mv(eEC_Effect_c* effect, GAME* game);
static void eString_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_string = {
    // clang-format off
    &eString_init,
    &eString_ct,
    &eString_mv,
    &eString_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eString_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_STRING, pos, NULL, game, &arg0, item_name, prio, 0, 0);
}

static void eString_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 20;
    effect->effect_specific[0] = *(s16*)ct_arg;
}

static void eString_mv(eEC_Effect_c* effect, GAME* game) {
    // nothing
}

typedef struct {
    u8* message;
    int message_len;
    rgba_t color;
} eString_class_c;

// @ 8057cc00
static u8 eString_string1[10] = {
    0x02, 0x03, 0x15, 0x04, 0x08, 0x14, 0x01, 0x96,
    0xE9, 0x21
};

// @ 8057cc0c
static eString_class_c eString_string1_class = {eString_string1, sizeof(eString_string1), {0xFF, 0xC8, 0xC8, 0xC8}};

// @ 8057cc18
static u8 eString_string2[9] = {
    0x0C, 0xF4, 0x15, 0x18, 0xCC, 0x12, 0x7D, 0x60,
    0x21
};

// @ 8057cc24
static eString_class_c eString_string2_class = {eString_string2, sizeof(eString_string2), {0xFF, 0xC8, 0xC8, 0xC8}};

// @ 8057cc30
static eString_class_c* eString_string_table[2] = {
    &eString_string1_class, &eString_string2_class
};

static void eString_dw(eEC_Effect_c* effect, GAME* game) {
    if (effect->effect_specific[0] < 2) {
        eString_class_c* string_p = eString_string_table[effect->effect_specific[0]];
        u8* str_p = string_p->message;
        int len = string_p->message_len;
        f32 len_f = (f32)len;
        f32 x = (SCREEN_WIDTH_F - len_f) * 0.5f;
        rgba_t color = string_p->color;

        mFont_SetMatrix(game->graph, mFont_MODE_FONT);
        mFont_SetLineStrings_AndSpace(game, str_p, len, x, 162.0f, color.r, color.g, color.b, color.a, FALSE, TRUE, 0, 1.0f, 1.0f, mFont_MODE_FONT);
        mFont_UnSetMatrix(game->graph, mFont_MODE_FONT);
    }
}
