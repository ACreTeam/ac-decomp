#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 tol_hata_hata_tex_inta_ia8[];
void* tol_hata_01_evw_anime_1_tex_table[] = { tol_hata_hata_tex_inta_ia8 };

u8 tol_hata_01_evw_anime_1_anime_ptn[] = { 0 };

EVW_ANIME_TEXANIME tol_hata_01_evw_anime_1[] = { { ARRAY_COUNT(tol_hata_01_evw_anime_1_anime_ptn), 0,
                                                   tol_hata_01_evw_anime_1_tex_table, tol_hata_01_evw_anime_1_anime_ptn,
                                                   NULL } };

EVW_ANIME_SCROLL tol_hata_01_evw_anime_2[] = { { 10, 0, 16, 16 }, { 0, 0, 0, 0 } };

EVW_ANIME_DATA tol_hata_01_evw_anime[] = { { 1, EVW_ANIME_TYPE_TEXANIME, tol_hata_01_evw_anime_1 },
                                           { -2, EVW_ANIME_TYPE_SCROLL2, tol_hata_01_evw_anime_2 } };
