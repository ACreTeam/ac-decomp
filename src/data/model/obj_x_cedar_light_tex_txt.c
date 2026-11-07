#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

#if VERSION == VER_GAFP01_00
extern u16 obj_x_cedar_light_pal[];
extern u8 obj_w_cedar_leaf_tex_txt[];
extern u8 obj_w_cedar_cutS_tex_txt[];
extern u8 obj_w_cedar_cutL_tex_txt[];
extern u8 obj_x_cedar_light_tex_txt[];

#if GAME_LANGUAGE == GAME_LANG_EN
u16 obj_x_cedar_light_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_cedar_light_pal.inc"
};

u8 obj_w_cedar_leaf_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_w_cedar_leaf_tex_txt.inc"
};

u8 obj_w_cedar_cutS_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_w_cedar_cutS_tex_txt.inc"
};

u8 obj_w_cedar_cutL_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_w_cedar_cutL_tex_txt.inc"
};

u8 obj_x_cedar_light_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_x_cedar_light_tex_txt.inc"
};

#elif GAME_LANGUAGE == GAME_LANG_FR
u16 obj_x_cedar_light_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_cedar_light_pal.inc"
};

u8 obj_w_cedar_leaf_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_w_cedar_leaf_tex_txt.inc"
};

u8 obj_w_cedar_cutS_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_w_cedar_cutS_tex_txt.inc"
};

u8 obj_w_cedar_cutL_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_w_cedar_cutL_tex_txt.inc"
};

u8 obj_x_cedar_light_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_x_cedar_light_tex_txt.inc"
};

#elif GAME_LANGUAGE == GAME_LANG_DE || GAME_LANGUAGE == GAME_LANG_IT || GAME_LANGUAGE == GAME_LANG_ES
u16 obj_x_cedar_light_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_cedar_light_pal.inc"
};

u8 obj_w_cedar_leaf_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_w_cedar_leaf_tex_txt.inc"
};

u8 obj_w_cedar_cutS_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_w_cedar_cutS_tex_txt.inc"
};

u8 obj_w_cedar_cutL_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_w_cedar_cutL_tex_txt.inc"
};

u8 obj_x_cedar_light_tex_txt[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_x_cedar_light_tex_txt.inc"
};

#endif
#else
u16 obj_cedar_light_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/obj_cedar_light_pal.inc"
};

u8 obj_w_cedar_leaf_tex_txt[] = {
#include "assets/obj_w_cedar_leaf_tex_txt.inc"
};

u8 obj_w_cedar_cutS_tex_txt[] = {
#include "assets/obj_w_cedar_cutS_tex_txt.inc"
};

u8 obj_w_cedar_cutL_tex_txt[] = {
#include "assets/obj_w_cedar_cutL_tex_txt.inc"
};

u8 obj_x_cedar_light_tex_txt[] = {
#include "assets/obj_x_cedar_light_tex_txt.inc"
};
#endif
