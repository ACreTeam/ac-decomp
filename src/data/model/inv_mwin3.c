#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u16 inv_mwin_08oonamazu_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/inv_mwin_08oonamazu_pal.inc"
};

u16 inv_mwin_01funa_pal[] = {
#include "assets/inv_mwin_01funa_pal.inc"
};

u16 inv_mwin_02masu_pal[] = {
#include "assets/inv_mwin_02masu_pal.inc"
};

u16 inv_mwin_03koi_pal[] = {
#include "assets/inv_mwin_03koi_pal.inc"
};

u16 inv_mwin_04nishiki_pal[] = {
#include "assets/inv_mwin_04nishiki_pal.inc"
};

u16 inv_mwin_05nigoi_pal[] = {
#include "assets/inv_mwin_05nigoi_pal.inc"
};

u16 inv_mwin_06ugui_pal[] = {
#include "assets/inv_mwin_06ugui_pal.inc"
};

u16 inv_mwin_07namazu_pal[] = {
#include "assets/inv_mwin_07namazu_pal.inc"
};

u16 inv_mwin_09oikawa_pal[] = {
#include "assets/inv_mwin_09oikawa_pal.inc"
};

u16 inv_mwin_10tanago_pal[] = {
#include "assets/inv_mwin_10tanago_pal.inc"
};

u16 inv_mwin_11dojyou_pal[] = {
#include "assets/inv_mwin_11dojyou_pal.inc"
};

u16 inv_mwin_12gill_pal[] = {
#include "assets/inv_mwin_12gill_pal.inc"
};

u16 inv_mwin_13bass_pal[] = {
#include "assets/inv_mwin_13bass_pal.inc"
};

u16 inv_mwin_14bassm_pal[] = {
#include "assets/inv_mwin_14bassm_pal.inc"
};

u16 inv_mwin_15bassl_pal[] = {
#include "assets/inv_mwin_15bassl_pal.inc"
};

u16 inv_mwin_16raigyo_pal[] = {
#include "assets/inv_mwin_16raigyo_pal.inc"
};

u16 inv_mwin_17unagi_pal[] = {
#include "assets/inv_mwin_17unagi_pal.inc"
};

u16 inv_mwin_18donko_pal[] = {
#include "assets/inv_mwin_18donko_pal.inc"
};

u16 inv_mwin_19wakasagi_pal[] = {
#include "assets/inv_mwin_19wakasagi_pal.inc"
};

u16 inv_mwin_20ayu_pal[] = {
#include "assets/inv_mwin_20ayu_pal.inc"
};

u16 inv_mwin_21yamame_pal[] = {
#include "assets/inv_mwin_21yamame_pal.inc"
};

u16 inv_mwin_22niji_pal[] = {
#include "assets/inv_mwin_22niji_pal.inc"
};

u16 inv_mwin_23iwana_pal[] = {
#include "assets/inv_mwin_23iwana_pal.inc"
};

u16 inv_mwin_24itou_pal[] = {
#include "assets/inv_mwin_24itou_pal.inc"
};

u16 inv_mwin_25sake_pal[] = {
#include "assets/inv_mwin_25sake_pal.inc"
};

u16 inv_mwin_26kingyo_pal[] = {
#include "assets/inv_mwin_26kingyo_pal.inc"
};

u16 inv_mwin_27demekin_pal[] = {
#include "assets/inv_mwin_27demekin_pal.inc"
};

u16 inv_mwin_28gupi_pal[] = {
#include "assets/inv_mwin_28gupi_pal.inc"
};

u16 inv_mwin_29angel_pal[] = {
#include "assets/inv_mwin_29angel_pal.inc"
};

u16 inv_mwin_30pirania_pal[] = {
#include "assets/inv_mwin_30pirania_pal.inc"
};

u16 inv_mwin_31aroana_pal[] = {
#include "assets/inv_mwin_31aroana_pal.inc"
};

u16 inv_mwin_32kaseki_pal[] = {
#include "assets/inv_mwin_32kaseki_pal.inc"
};

u8 inv_mwin_08oonamazu_tex[] = {
#include "assets/inv_mwin_08oonamazu_tex.inc"
};

u8 inv_mwin_01funa_tex[] = {
#include "assets/inv_mwin_01funa_tex.inc"
};

u8 inv_mwin_02masu_tex[] = {
#include "assets/inv_mwin_02masu_tex.inc"
};

u8 inv_mwin_03koi_tex[] = {
#include "assets/inv_mwin_03koi_tex.inc"
};

u8 inv_mwin_04nishiki_tex[] = {
#include "assets/inv_mwin_04nishiki_tex.inc"
};

u8 inv_mwin_05nigoi_tex[] = {
#include "assets/inv_mwin_05nigoi_tex.inc"
};

u8 inv_mwin_06ugui_tex[] = {
#include "assets/inv_mwin_06ugui_tex.inc"
};

u8 inv_mwin_07namazu_tex[] = {
#include "assets/inv_mwin_07namazu_tex.inc"
};

u8 inv_mwin_09oikawa_tex[] = {
#include "assets/inv_mwin_09oikawa_tex.inc"
};

u8 inv_mwin_10tanago_tex[] = {
#include "assets/inv_mwin_10tanago_tex.inc"
};

u8 inv_mwin_11dojyou_tex[] = {
#include "assets/inv_mwin_11dojyou_tex.inc"
};

u8 inv_mwin_12gill_tex[] = {
#include "assets/inv_mwin_12gill_tex.inc"
};

u8 inv_mwin_13bass_tex[] = {
#include "assets/inv_mwin_13bass_tex.inc"
};

u8 inv_mwin_14bassm_tex[] = {
#include "assets/inv_mwin_14bassm_tex.inc"
};

u8 inv_mwin_15bassl_tex[] = {
#include "assets/inv_mwin_15bassl_tex.inc"
};

u8 inv_mwin_16raigyo_tex[] = {
#include "assets/inv_mwin_16raigyo_tex.inc"
};

u8 inv_mwin_17unagi_tex[] = {
#include "assets/inv_mwin_17unagi_tex.inc"
};

u8 inv_mwin_18donko_tex[] = {
#include "assets/inv_mwin_18donko_tex.inc"
};

u8 inv_mwin_19wakasagi_tex[] = {
#include "assets/inv_mwin_19wakasagi_tex.inc"
};

u8 inv_mwin_20ayu_tex[] = {
#include "assets/inv_mwin_20ayu_tex.inc"
};

u8 inv_mwin_21yamame_tex[] = {
#include "assets/inv_mwin_21yamame_tex.inc"
};

u8 inv_mwin_22niji_tex[] = {
#include "assets/inv_mwin_22niji_tex.inc"
};

u8 inv_mwin_23iwana_tex[] = {
#include "assets/inv_mwin_23iwana_tex.inc"
};

u8 inv_mwin_24itou_tex[] = {
#include "assets/inv_mwin_24itou_tex.inc"
};

u8 inv_mwin_25sake_tex[] = {
#include "assets/inv_mwin_25sake_tex.inc"
};

u8 inv_mwin_26kingyo_tex[] = {
#include "assets/inv_mwin_26kingyo_tex.inc"
};

u8 inv_mwin_27demekin_tex[] = {
#include "assets/inv_mwin_27demekin_tex.inc"
};

u8 inv_mwin_28gupi_tex[] = {
#include "assets/inv_mwin_28gupi_tex.inc"
};

u8 inv_mwin_29angel_tex[] = {
#include "assets/inv_mwin_29angel_tex.inc"
};

u8 inv_mwin_30pirania_tex[] = {
#include "assets/inv_mwin_30pirania_tex.inc"
};

u8 inv_mwin_31aroana_tex[] = {
#include "assets/inv_mwin_31aroana_tex.inc"
};

u8 inv_mwin_32kaseki_tex[] = {
#include "assets/inv_mwin_32kaseki_tex.inc"
};
