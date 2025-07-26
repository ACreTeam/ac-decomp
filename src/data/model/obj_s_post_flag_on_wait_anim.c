#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"

extern u8 obj_s_post_flag2_TA_tex_txt[], obj_s_post_flag3_TA_tex_txt[];

void* obj_s_post_flag_on_wait1_evw_anime_2_tex_table[] = { obj_s_post_flag2_TA_tex_txt, obj_s_post_flag3_TA_tex_txt };

u8 obj_s_post_flag_on_wait1_evw_anime_2_anime_ptn[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                                        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

EVW_ANIME_TEXANIME obj_s_post_flag_on_wait1_evw_anime_2[] = {
    ARRAY_COUNT(obj_s_post_flag_on_wait1_evw_anime_2_anime_ptn),
    0,
    obj_s_post_flag_on_wait1_evw_anime_2_tex_table,
    obj_s_post_flag_on_wait1_evw_anime_2_anime_ptn,
    NULL,
};

EVW_ANIME_DATA obj_s_post_flag_on_wait1_evw_anime[] = { { -2, EVW_ANIME_TYPE_TEXANIME,
                                                          &obj_s_post_flag_on_wait1_evw_anime_2 } };
