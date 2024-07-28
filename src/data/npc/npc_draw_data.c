#include "ac_npc.h"

extern cKF_Skeleton_R_c cKF_bs_r_cat_1;
extern unsigned short cat_1_pal[];
extern unsigned char cat_1_eye1_TA_tex_txt[];
extern unsigned char cat_1_eye2_TA_tex_txt[];
extern unsigned char cat_1_eye3_TA_tex_txt[];
extern unsigned char cat_1_eye4_TA_tex_txt[];
extern unsigned char cat_1_eye5_TA_tex_txt[];
extern unsigned char cat_1_eye6_TA_tex_txt[];
extern unsigned char cat_1_eye7_TA_tex_txt[];
extern unsigned char cat_1_eye8_TA_tex_txt[];
extern unsigned char cat_1_mouth1_TA_tex_txt[];
extern unsigned char cat_1_mouth2_TA_tex_txt[];
extern unsigned char cat_1_mouth3_TA_tex_txt[];
extern unsigned char cat_1_mouth4_TA_tex_txt[];
extern unsigned char cat_1_mouth5_TA_tex_txt[];
extern unsigned char cat_1_mouth6_TA_tex_txt[];
extern unsigned char cat_1_tmem_txt[];
extern unsigned short cat_2_pal[];
extern unsigned char cat_2_eye1_TA_tex_txt[];
extern unsigned char cat_2_eye2_TA_tex_txt[];
extern unsigned char cat_2_eye3_TA_tex_txt[];
extern unsigned char cat_2_eye4_TA_tex_txt[];
extern unsigned char cat_2_eye5_TA_tex_txt[];
extern unsigned char cat_2_eye6_TA_tex_txt[];
extern unsigned char cat_2_eye7_TA_tex_txt[];
extern unsigned char cat_2_eye8_TA_tex_txt[];
extern unsigned char cat_2_mouth1_TA_tex_txt[];
extern unsigned char cat_2_mouth2_TA_tex_txt[];
extern unsigned char cat_2_mouth3_TA_tex_txt[];
extern unsigned char cat_2_mouth4_TA_tex_txt[];
extern unsigned char cat_2_mouth5_TA_tex_txt[];
extern unsigned char cat_2_mouth6_TA_tex_txt[];
extern unsigned char cat_2_tmem_txt[];
extern unsigned short cat_3_pal[];
extern unsigned char cat_3_eye1_TA_tex_txt[];
extern unsigned char cat_3_eye2_TA_tex_txt[];
extern unsigned char cat_3_eye3_TA_tex_txt[];
extern unsigned char cat_3_eye4_TA_tex_txt[];
extern unsigned char cat_3_eye5_TA_tex_txt[];
extern unsigned char cat_3_eye6_TA_tex_txt[];
extern unsigned char cat_3_eye7_TA_tex_txt[];
extern unsigned char cat_3_eye8_TA_tex_txt[];
extern unsigned char cat_3_mouth1_TA_tex_txt[];
extern unsigned char cat_3_mouth2_TA_tex_txt[];
extern unsigned char cat_3_mouth3_TA_tex_txt[];
extern unsigned char cat_3_mouth4_TA_tex_txt[];
extern unsigned char cat_3_mouth5_TA_tex_txt[];
extern unsigned char cat_3_mouth6_TA_tex_txt[];
extern unsigned char cat_3_tmem_txt[];
extern unsigned short cat_4_pal[];
extern unsigned char cat_4_eye1_TA_tex_txt[];
extern unsigned char cat_4_eye2_TA_tex_txt[];
extern unsigned char cat_4_eye3_TA_tex_txt[];
extern unsigned char cat_4_eye4_TA_tex_txt[];
extern unsigned char cat_4_eye5_TA_tex_txt[];
extern unsigned char cat_4_eye6_TA_tex_txt[];
extern unsigned char cat_4_eye7_TA_tex_txt[];
extern unsigned char cat_4_eye8_TA_tex_txt[];
extern unsigned char cat_4_mouth1_TA_tex_txt[];
extern unsigned char cat_4_mouth2_TA_tex_txt[];
extern unsigned char cat_4_mouth3_TA_tex_txt[];
extern unsigned char cat_4_mouth4_TA_tex_txt[];
extern unsigned char cat_4_mouth5_TA_tex_txt[];
extern unsigned char cat_4_mouth6_TA_tex_txt[];
extern unsigned char cat_4_tmem_txt[];
extern unsigned short cat_5_pal[];
extern unsigned char cat_5_eye1_TA_tex_txt[];
extern unsigned char cat_5_eye2_TA_tex_txt[];
extern unsigned char cat_5_eye3_TA_tex_txt[];
extern unsigned char cat_5_eye4_TA_tex_txt[];
extern unsigned char cat_5_eye5_TA_tex_txt[];
extern unsigned char cat_5_eye6_TA_tex_txt[];
extern unsigned char cat_5_eye7_TA_tex_txt[];
extern unsigned char cat_5_eye8_TA_tex_txt[];
extern unsigned char cat_5_mouth1_TA_tex_txt[];
extern unsigned char cat_5_mouth2_TA_tex_txt[];
extern unsigned char cat_5_mouth3_TA_tex_txt[];
extern unsigned char cat_5_mouth4_TA_tex_txt[];
extern unsigned char cat_5_mouth5_TA_tex_txt[];
extern unsigned char cat_5_mouth6_TA_tex_txt[];
extern unsigned char cat_5_tmem_txt[];
extern unsigned short cat_6_pal[];
extern unsigned char cat_6_eye1_TA_tex_txt[];
extern unsigned char cat_6_eye2_TA_tex_txt[];
extern unsigned char cat_6_eye3_TA_tex_txt[];
extern unsigned char cat_6_eye4_TA_tex_txt[];
extern unsigned char cat_6_eye5_TA_tex_txt[];
extern unsigned char cat_6_eye6_TA_tex_txt[];
extern unsigned char cat_6_eye7_TA_tex_txt[];
extern unsigned char cat_6_eye8_TA_tex_txt[];
extern unsigned char cat_6_mouth1_TA_tex_txt[];
extern unsigned char cat_6_mouth2_TA_tex_txt[];
extern unsigned char cat_6_mouth3_TA_tex_txt[];
extern unsigned char cat_6_mouth4_TA_tex_txt[];
extern unsigned char cat_6_mouth5_TA_tex_txt[];
extern unsigned char cat_6_mouth6_TA_tex_txt[];
extern unsigned char cat_6_tmem_txt[];
extern unsigned short cat_7_pal[];
extern unsigned char cat_7_eye1_TA_tex_txt[];
extern unsigned char cat_7_eye2_TA_tex_txt[];
extern unsigned char cat_7_eye3_TA_tex_txt[];
extern unsigned char cat_7_eye4_TA_tex_txt[];
extern unsigned char cat_7_eye5_TA_tex_txt[];
extern unsigned char cat_7_eye6_TA_tex_txt[];
extern unsigned char cat_7_eye7_TA_tex_txt[];
extern unsigned char cat_7_eye8_TA_tex_txt[];
extern unsigned char cat_7_mouth1_TA_tex_txt[];
extern unsigned char cat_7_mouth2_TA_tex_txt[];
extern unsigned char cat_7_mouth3_TA_tex_txt[];
extern unsigned char cat_7_mouth4_TA_tex_txt[];
extern unsigned char cat_7_mouth5_TA_tex_txt[];
extern unsigned char cat_7_mouth6_TA_tex_txt[];
extern unsigned char cat_7_tmem_txt[];
extern unsigned short cat_8_pal[];
extern unsigned char cat_8_eye1_TA_tex_txt[];
extern unsigned char cat_8_eye2_TA_tex_txt[];
extern unsigned char cat_8_eye3_TA_tex_txt[];
extern unsigned char cat_8_eye4_TA_tex_txt[];
extern unsigned char cat_8_eye5_TA_tex_txt[];
extern unsigned char cat_8_eye6_TA_tex_txt[];
extern unsigned char cat_8_eye7_TA_tex_txt[];
extern unsigned char cat_8_eye8_TA_tex_txt[];
extern unsigned char cat_8_mouth1_TA_tex_txt[];
extern unsigned char cat_8_mouth2_TA_tex_txt[];
extern unsigned char cat_8_mouth3_TA_tex_txt[];
extern unsigned char cat_8_mouth4_TA_tex_txt[];
extern unsigned char cat_8_mouth5_TA_tex_txt[];
extern unsigned char cat_8_mouth6_TA_tex_txt[];
extern unsigned char cat_8_tmem_txt[];
extern unsigned short cat_9_pal[];
extern unsigned char cat_9_eye1_TA_tex_txt[];
extern unsigned char cat_9_eye2_TA_tex_txt[];
extern unsigned char cat_9_eye3_TA_tex_txt[];
extern unsigned char cat_9_eye4_TA_tex_txt[];
extern unsigned char cat_9_eye5_TA_tex_txt[];
extern unsigned char cat_9_eye6_TA_tex_txt[];
extern unsigned char cat_9_eye7_TA_tex_txt[];
extern unsigned char cat_9_eye8_TA_tex_txt[];
extern unsigned char cat_9_mouth1_TA_tex_txt[];
extern unsigned char cat_9_mouth2_TA_tex_txt[];
extern unsigned char cat_9_mouth3_TA_tex_txt[];
extern unsigned char cat_9_mouth4_TA_tex_txt[];
extern unsigned char cat_9_mouth5_TA_tex_txt[];
extern unsigned char cat_9_mouth6_TA_tex_txt[];
extern unsigned char cat_9_tmem_txt[];
extern unsigned short cat_10_pal[];
extern unsigned char cat_10_eye1_TA_tex_txt[];
extern unsigned char cat_10_eye2_TA_tex_txt[];
extern unsigned char cat_10_eye3_TA_tex_txt[];
extern unsigned char cat_10_eye4_TA_tex_txt[];
extern unsigned char cat_10_eye5_TA_tex_txt[];
extern unsigned char cat_10_eye6_TA_tex_txt[];
extern unsigned char cat_10_eye7_TA_tex_txt[];
extern unsigned char cat_10_eye8_TA_tex_txt[];
extern unsigned char cat_10_mouth1_TA_tex_txt[];
extern unsigned char cat_10_mouth2_TA_tex_txt[];
extern unsigned char cat_10_mouth3_TA_tex_txt[];
extern unsigned char cat_10_mouth4_TA_tex_txt[];
extern unsigned char cat_10_mouth5_TA_tex_txt[];
extern unsigned char cat_10_mouth6_TA_tex_txt[];
extern unsigned char cat_10_tmem_txt[];
extern unsigned short cat_11_pal[];
extern unsigned char cat_11_eye1_TA_tex_txt[];
extern unsigned char cat_11_eye2_TA_tex_txt[];
extern unsigned char cat_11_eye3_TA_tex_txt[];
extern unsigned char cat_11_eye4_TA_tex_txt[];
extern unsigned char cat_11_eye5_TA_tex_txt[];
extern unsigned char cat_11_eye6_TA_tex_txt[];
extern unsigned char cat_11_eye7_TA_tex_txt[];
extern unsigned char cat_11_eye8_TA_tex_txt[];
extern unsigned char cat_11_mouth1_TA_tex_txt[];
extern unsigned char cat_11_mouth2_TA_tex_txt[];
extern unsigned char cat_11_mouth3_TA_tex_txt[];
extern unsigned char cat_11_mouth4_TA_tex_txt[];
extern unsigned char cat_11_mouth5_TA_tex_txt[];
extern unsigned char cat_11_mouth6_TA_tex_txt[];
extern unsigned char cat_11_tmem_txt[];
extern unsigned short cat_12_pal[];
extern unsigned char cat_12_eye1_TA_tex_txt[];
extern unsigned char cat_12_eye2_TA_tex_txt[];
extern unsigned char cat_12_eye3_TA_tex_txt[];
extern unsigned char cat_12_eye4_TA_tex_txt[];
extern unsigned char cat_12_eye5_TA_tex_txt[];
extern unsigned char cat_12_eye6_TA_tex_txt[];
extern unsigned char cat_12_eye7_TA_tex_txt[];
extern unsigned char cat_12_eye8_TA_tex_txt[];
extern unsigned char cat_12_mouth1_TA_tex_txt[];
extern unsigned char cat_12_mouth2_TA_tex_txt[];
extern unsigned char cat_12_mouth3_TA_tex_txt[];
extern unsigned char cat_12_mouth4_TA_tex_txt[];
extern unsigned char cat_12_mouth5_TA_tex_txt[];
extern unsigned char cat_12_mouth6_TA_tex_txt[];
extern unsigned char cat_12_tmem_txt[];
extern unsigned short cat_13_pal[];
extern unsigned char cat_13_eye1_TA_tex_txt[];
extern unsigned char cat_13_eye2_TA_tex_txt[];
extern unsigned char cat_13_eye3_TA_tex_txt[];
extern unsigned char cat_13_eye4_TA_tex_txt[];
extern unsigned char cat_13_eye5_TA_tex_txt[];
extern unsigned char cat_13_eye6_TA_tex_txt[];
extern unsigned char cat_13_eye7_TA_tex_txt[];
extern unsigned char cat_13_eye8_TA_tex_txt[];
extern unsigned char cat_13_mouth1_TA_tex_txt[];
extern unsigned char cat_13_mouth2_TA_tex_txt[];
extern unsigned char cat_13_mouth3_TA_tex_txt[];
extern unsigned char cat_13_mouth4_TA_tex_txt[];
extern unsigned char cat_13_mouth5_TA_tex_txt[];
extern unsigned char cat_13_mouth6_TA_tex_txt[];
extern unsigned char cat_13_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_ant_1;
extern unsigned short ant_1_pal[];
extern unsigned char ant_1_eye1_TA_tex_txt[];
extern unsigned char ant_1_eye2_TA_tex_txt[];
extern unsigned char ant_1_eye3_TA_tex_txt[];
extern unsigned char ant_1_eye4_TA_tex_txt[];
extern unsigned char ant_1_eye5_TA_tex_txt[];
extern unsigned char ant_1_eye6_TA_tex_txt[];
extern unsigned char ant_1_eye7_TA_tex_txt[];
extern unsigned char ant_1_eye8_TA_tex_txt[];
extern unsigned char ant_1_tmem_txt[];
extern unsigned short ant_2_pal[];
extern unsigned char ant_2_eye1_TA_tex_txt[];
extern unsigned char ant_2_eye2_TA_tex_txt[];
extern unsigned char ant_2_eye3_TA_tex_txt[];
extern unsigned char ant_2_eye4_TA_tex_txt[];
extern unsigned char ant_2_eye5_TA_tex_txt[];
extern unsigned char ant_2_eye6_TA_tex_txt[];
extern unsigned char ant_2_eye7_TA_tex_txt[];
extern unsigned char ant_2_eye8_TA_tex_txt[];
extern unsigned char ant_2_tmem_txt[];
extern unsigned short ant_3_pal[];
extern unsigned char ant_3_eye1_TA_tex_txt[];
extern unsigned char ant_3_eye2_TA_tex_txt[];
extern unsigned char ant_3_eye3_TA_tex_txt[];
extern unsigned char ant_3_eye4_TA_tex_txt[];
extern unsigned char ant_3_eye5_TA_tex_txt[];
extern unsigned char ant_3_eye6_TA_tex_txt[];
extern unsigned char ant_3_eye7_TA_tex_txt[];
extern unsigned char ant_3_eye8_TA_tex_txt[];
extern unsigned char ant_3_tmem_txt[];
extern unsigned short ant_4_pal[];
extern unsigned char ant_4_eye1_TA_tex_txt[];
extern unsigned char ant_4_eye2_TA_tex_txt[];
extern unsigned char ant_4_eye3_TA_tex_txt[];
extern unsigned char ant_4_eye4_TA_tex_txt[];
extern unsigned char ant_4_eye5_TA_tex_txt[];
extern unsigned char ant_4_eye6_TA_tex_txt[];
extern unsigned char ant_4_eye7_TA_tex_txt[];
extern unsigned char ant_4_eye8_TA_tex_txt[];
extern unsigned char ant_4_tmem_txt[];
extern unsigned short ant_5_pal[];
extern unsigned char ant_5_eye1_TA_tex_txt[];
extern unsigned char ant_5_eye2_TA_tex_txt[];
extern unsigned char ant_5_eye3_TA_tex_txt[];
extern unsigned char ant_5_eye4_TA_tex_txt[];
extern unsigned char ant_5_eye5_TA_tex_txt[];
extern unsigned char ant_5_eye6_TA_tex_txt[];
extern unsigned char ant_5_eye7_TA_tex_txt[];
extern unsigned char ant_5_eye8_TA_tex_txt[];
extern unsigned char ant_5_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_bea_1;
extern unsigned short bea_1_pal[];
extern unsigned char bea_1_eye1_TA_tex_txt[];
extern unsigned char bea_1_eye2_TA_tex_txt[];
extern unsigned char bea_1_eye3_TA_tex_txt[];
extern unsigned char bea_1_eye4_TA_tex_txt[];
extern unsigned char bea_1_eye5_TA_tex_txt[];
extern unsigned char bea_1_eye6_TA_tex_txt[];
extern unsigned char bea_1_eye7_TA_tex_txt[];
extern unsigned char bea_1_eye8_TA_tex_txt[];
extern unsigned char bea_1_mouth1_TA_tex_txt[];
extern unsigned char bea_1_mouth2_TA_tex_txt[];
extern unsigned char bea_1_mouth3_TA_tex_txt[];
extern unsigned char bea_1_mouth4_TA_tex_txt[];
extern unsigned char bea_1_mouth5_TA_tex_txt[];
extern unsigned char bea_1_mouth6_TA_tex_txt[];
extern unsigned char bea_1_tmem_txt[];
extern unsigned short bea_2_pal[];
extern unsigned char bea_2_eye1_TA_tex_txt[];
extern unsigned char bea_2_eye2_TA_tex_txt[];
extern unsigned char bea_2_eye3_TA_tex_txt[];
extern unsigned char bea_2_eye4_TA_tex_txt[];
extern unsigned char bea_2_eye5_TA_tex_txt[];
extern unsigned char bea_2_eye6_TA_tex_txt[];
extern unsigned char bea_2_eye7_TA_tex_txt[];
extern unsigned char bea_2_eye8_TA_tex_txt[];
extern unsigned char bea_2_mouth1_TA_tex_txt[];
extern unsigned char bea_2_mouth2_TA_tex_txt[];
extern unsigned char bea_2_mouth3_TA_tex_txt[];
extern unsigned char bea_2_mouth4_TA_tex_txt[];
extern unsigned char bea_2_mouth5_TA_tex_txt[];
extern unsigned char bea_2_mouth6_TA_tex_txt[];
extern unsigned char bea_2_tmem_txt[];
extern unsigned short bea_3_pal[];
extern unsigned char bea_3_eye1_TA_tex_txt[];
extern unsigned char bea_3_eye2_TA_tex_txt[];
extern unsigned char bea_3_eye3_TA_tex_txt[];
extern unsigned char bea_3_eye4_TA_tex_txt[];
extern unsigned char bea_3_eye5_TA_tex_txt[];
extern unsigned char bea_3_eye6_TA_tex_txt[];
extern unsigned char bea_3_eye7_TA_tex_txt[];
extern unsigned char bea_3_eye8_TA_tex_txt[];
extern unsigned char bea_3_mouth1_TA_tex_txt[];
extern unsigned char bea_3_mouth2_TA_tex_txt[];
extern unsigned char bea_3_mouth3_TA_tex_txt[];
extern unsigned char bea_3_mouth4_TA_tex_txt[];
extern unsigned char bea_3_mouth5_TA_tex_txt[];
extern unsigned char bea_3_mouth6_TA_tex_txt[];
extern unsigned char bea_3_tmem_txt[];
extern unsigned short bea_5_pal[];
extern unsigned char bea_5_eye1_TA_tex_txt[];
extern unsigned char bea_5_eye2_TA_tex_txt[];
extern unsigned char bea_5_eye3_TA_tex_txt[];
extern unsigned char bea_5_eye4_TA_tex_txt[];
extern unsigned char bea_5_eye5_TA_tex_txt[];
extern unsigned char bea_5_eye6_TA_tex_txt[];
extern unsigned char bea_5_eye7_TA_tex_txt[];
extern unsigned char bea_5_eye8_TA_tex_txt[];
extern unsigned char bea_5_mouth1_TA_tex_txt[];
extern unsigned char bea_5_mouth2_TA_tex_txt[];
extern unsigned char bea_5_mouth3_TA_tex_txt[];
extern unsigned char bea_5_mouth4_TA_tex_txt[];
extern unsigned char bea_5_mouth5_TA_tex_txt[];
extern unsigned char bea_5_mouth6_TA_tex_txt[];
extern unsigned char bea_5_tmem_txt[];
extern unsigned short bea_6_pal[];
extern unsigned char bea_6_eye1_TA_tex_txt[];
extern unsigned char bea_6_eye2_TA_tex_txt[];
extern unsigned char bea_6_eye3_TA_tex_txt[];
extern unsigned char bea_6_eye4_TA_tex_txt[];
extern unsigned char bea_6_eye5_TA_tex_txt[];
extern unsigned char bea_6_eye6_TA_tex_txt[];
extern unsigned char bea_6_eye7_TA_tex_txt[];
extern unsigned char bea_6_eye8_TA_tex_txt[];
extern unsigned char bea_6_mouth1_TA_tex_txt[];
extern unsigned char bea_6_mouth2_TA_tex_txt[];
extern unsigned char bea_6_mouth3_TA_tex_txt[];
extern unsigned char bea_6_mouth4_TA_tex_txt[];
extern unsigned char bea_6_mouth5_TA_tex_txt[];
extern unsigned char bea_6_mouth6_TA_tex_txt[];
extern unsigned char bea_6_tmem_txt[];
extern unsigned short bea_7_pal[];
extern unsigned char bea_7_eye1_TA_tex_txt[];
extern unsigned char bea_7_eye2_TA_tex_txt[];
extern unsigned char bea_7_eye3_TA_tex_txt[];
extern unsigned char bea_7_eye4_TA_tex_txt[];
extern unsigned char bea_7_eye5_TA_tex_txt[];
extern unsigned char bea_7_eye6_TA_tex_txt[];
extern unsigned char bea_7_eye7_TA_tex_txt[];
extern unsigned char bea_7_eye8_TA_tex_txt[];
extern unsigned char bea_7_mouth1_TA_tex_txt[];
extern unsigned char bea_7_mouth2_TA_tex_txt[];
extern unsigned char bea_7_mouth3_TA_tex_txt[];
extern unsigned char bea_7_mouth4_TA_tex_txt[];
extern unsigned char bea_7_mouth5_TA_tex_txt[];
extern unsigned char bea_7_mouth6_TA_tex_txt[];
extern unsigned char bea_7_tmem_txt[];
extern unsigned short bea_8_pal[];
extern unsigned char bea_8_eye1_TA_tex_txt[];
extern unsigned char bea_8_eye2_TA_tex_txt[];
extern unsigned char bea_8_eye3_TA_tex_txt[];
extern unsigned char bea_8_eye4_TA_tex_txt[];
extern unsigned char bea_8_eye5_TA_tex_txt[];
extern unsigned char bea_8_eye6_TA_tex_txt[];
extern unsigned char bea_8_eye7_TA_tex_txt[];
extern unsigned char bea_8_eye8_TA_tex_txt[];
extern unsigned char bea_8_mouth1_TA_tex_txt[];
extern unsigned char bea_8_mouth2_TA_tex_txt[];
extern unsigned char bea_8_mouth3_TA_tex_txt[];
extern unsigned char bea_8_mouth4_TA_tex_txt[];
extern unsigned char bea_8_mouth5_TA_tex_txt[];
extern unsigned char bea_8_mouth6_TA_tex_txt[];
extern unsigned char bea_8_tmem_txt[];
extern unsigned short bea_9_pal[];
extern unsigned char bea_9_eye1_TA_tex_txt[];
extern unsigned char bea_9_eye2_TA_tex_txt[];
extern unsigned char bea_9_eye3_TA_tex_txt[];
extern unsigned char bea_9_eye4_TA_tex_txt[];
extern unsigned char bea_9_eye5_TA_tex_txt[];
extern unsigned char bea_9_eye6_TA_tex_txt[];
extern unsigned char bea_9_eye7_TA_tex_txt[];
extern unsigned char bea_9_eye8_TA_tex_txt[];
extern unsigned char bea_9_mouth1_TA_tex_txt[];
extern unsigned char bea_9_mouth2_TA_tex_txt[];
extern unsigned char bea_9_mouth3_TA_tex_txt[];
extern unsigned char bea_9_mouth4_TA_tex_txt[];
extern unsigned char bea_9_mouth5_TA_tex_txt[];
extern unsigned char bea_9_mouth6_TA_tex_txt[];
extern unsigned char bea_9_tmem_txt[];
extern unsigned short bea_10_pal[];
extern unsigned char bea_10_eye1_TA_tex_txt[];
extern unsigned char bea_10_eye2_TA_tex_txt[];
extern unsigned char bea_10_eye3_TA_tex_txt[];
extern unsigned char bea_10_eye4_TA_tex_txt[];
extern unsigned char bea_10_eye5_TA_tex_txt[];
extern unsigned char bea_10_eye6_TA_tex_txt[];
extern unsigned char bea_10_eye7_TA_tex_txt[];
extern unsigned char bea_10_eye8_TA_tex_txt[];
extern unsigned char bea_10_mouth1_TA_tex_txt[];
extern unsigned char bea_10_mouth2_TA_tex_txt[];
extern unsigned char bea_10_mouth3_TA_tex_txt[];
extern unsigned char bea_10_mouth4_TA_tex_txt[];
extern unsigned char bea_10_mouth5_TA_tex_txt[];
extern unsigned char bea_10_mouth6_TA_tex_txt[];
extern unsigned char bea_10_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_brd_1;
extern unsigned short brd_1_pal[];
extern unsigned char brd_1_eye1_TA_tex_txt[];
extern unsigned char brd_1_eye2_TA_tex_txt[];
extern unsigned char brd_1_eye3_TA_tex_txt[];
extern unsigned char brd_1_eye4_TA_tex_txt[];
extern unsigned char brd_1_eye5_TA_tex_txt[];
extern unsigned char brd_1_eye6_TA_tex_txt[];
extern unsigned char brd_1_eye7_TA_tex_txt[];
extern unsigned char brd_1_eye8_TA_tex_txt[];
extern unsigned char brd_1_tmem_txt[];
extern unsigned short brd_2_pal[];
extern unsigned char brd_2_eye1_TA_tex_txt[];
extern unsigned char brd_2_eye2_TA_tex_txt[];
extern unsigned char brd_2_eye3_TA_tex_txt[];
extern unsigned char brd_2_eye4_TA_tex_txt[];
extern unsigned char brd_2_eye5_TA_tex_txt[];
extern unsigned char brd_2_eye6_TA_tex_txt[];
extern unsigned char brd_2_eye7_TA_tex_txt[];
extern unsigned char brd_2_eye8_TA_tex_txt[];
extern unsigned char brd_2_tmem_txt[];
extern unsigned short brd_3_pal[];
extern unsigned char brd_3_eye1_TA_tex_txt[];
extern unsigned char brd_3_eye2_TA_tex_txt[];
extern unsigned char brd_3_eye3_TA_tex_txt[];
extern unsigned char brd_3_eye4_TA_tex_txt[];
extern unsigned char brd_3_eye5_TA_tex_txt[];
extern unsigned char brd_3_eye6_TA_tex_txt[];
extern unsigned char brd_3_eye7_TA_tex_txt[];
extern unsigned char brd_3_eye8_TA_tex_txt[];
extern unsigned char brd_3_tmem_txt[];
extern unsigned short brd_4_pal[];
extern unsigned char brd_4_eye1_TA_tex_txt[];
extern unsigned char brd_4_eye2_TA_tex_txt[];
extern unsigned char brd_4_eye3_TA_tex_txt[];
extern unsigned char brd_4_eye4_TA_tex_txt[];
extern unsigned char brd_4_eye5_TA_tex_txt[];
extern unsigned char brd_4_eye6_TA_tex_txt[];
extern unsigned char brd_4_eye7_TA_tex_txt[];
extern unsigned char brd_4_eye8_TA_tex_txt[];
extern unsigned char brd_4_tmem_txt[];
extern unsigned short brd_5_pal[];
extern unsigned char brd_5_eye1_TA_tex_txt[];
extern unsigned char brd_5_eye2_TA_tex_txt[];
extern unsigned char brd_5_eye3_TA_tex_txt[];
extern unsigned char brd_5_eye4_TA_tex_txt[];
extern unsigned char brd_5_eye5_TA_tex_txt[];
extern unsigned char brd_5_eye6_TA_tex_txt[];
extern unsigned char brd_5_eye7_TA_tex_txt[];
extern unsigned char brd_5_eye8_TA_tex_txt[];
extern unsigned char brd_5_tmem_txt[];
extern unsigned short brd_6_pal[];
extern unsigned char brd_6_eye1_TA_tex_txt[];
extern unsigned char brd_6_eye2_TA_tex_txt[];
extern unsigned char brd_6_eye3_TA_tex_txt[];
extern unsigned char brd_6_eye4_TA_tex_txt[];
extern unsigned char brd_6_eye5_TA_tex_txt[];
extern unsigned char brd_6_eye6_TA_tex_txt[];
extern unsigned char brd_6_eye7_TA_tex_txt[];
extern unsigned char brd_6_eye8_TA_tex_txt[];
extern unsigned char brd_6_tmem_txt[];
extern unsigned short brd_7_pal[];
extern unsigned char brd_7_eye1_TA_tex_txt[];
extern unsigned char brd_7_eye2_TA_tex_txt[];
extern unsigned char brd_7_eye3_TA_tex_txt[];
extern unsigned char brd_7_eye4_TA_tex_txt[];
extern unsigned char brd_7_eye5_TA_tex_txt[];
extern unsigned char brd_7_eye6_TA_tex_txt[];
extern unsigned char brd_7_eye7_TA_tex_txt[];
extern unsigned char brd_7_eye8_TA_tex_txt[];
extern unsigned char brd_7_tmem_txt[];
extern unsigned short brd_8_pal[];
extern unsigned char brd_8_eye1_TA_tex_txt[];
extern unsigned char brd_8_eye2_TA_tex_txt[];
extern unsigned char brd_8_eye3_TA_tex_txt[];
extern unsigned char brd_8_eye4_TA_tex_txt[];
extern unsigned char brd_8_eye5_TA_tex_txt[];
extern unsigned char brd_8_eye6_TA_tex_txt[];
extern unsigned char brd_8_eye7_TA_tex_txt[];
extern unsigned char brd_8_eye8_TA_tex_txt[];
extern unsigned char brd_8_tmem_txt[];
extern unsigned short brd_9_pal[];
extern unsigned char brd_9_eye1_TA_tex_txt[];
extern unsigned char brd_9_eye2_TA_tex_txt[];
extern unsigned char brd_9_eye3_TA_tex_txt[];
extern unsigned char brd_9_eye4_TA_tex_txt[];
extern unsigned char brd_9_eye5_TA_tex_txt[];
extern unsigned char brd_9_eye6_TA_tex_txt[];
extern unsigned char brd_9_eye7_TA_tex_txt[];
extern unsigned char brd_9_eye8_TA_tex_txt[];
extern unsigned char brd_9_tmem_txt[];
extern unsigned short brd_10_pal[];
extern unsigned char brd_10_eye1_TA_tex_txt[];
extern unsigned char brd_10_eye2_TA_tex_txt[];
extern unsigned char brd_10_eye3_TA_tex_txt[];
extern unsigned char brd_10_eye4_TA_tex_txt[];
extern unsigned char brd_10_eye5_TA_tex_txt[];
extern unsigned char brd_10_eye6_TA_tex_txt[];
extern unsigned char brd_10_eye7_TA_tex_txt[];
extern unsigned char brd_10_eye8_TA_tex_txt[];
extern unsigned char brd_10_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_bul_1;
extern unsigned short bul_1_pal[];
extern unsigned char bul_1_eye1_TA_tex_txt[];
extern unsigned char bul_1_eye2_TA_tex_txt[];
extern unsigned char bul_1_eye3_TA_tex_txt[];
extern unsigned char bul_1_eye4_TA_tex_txt[];
extern unsigned char bul_1_eye5_TA_tex_txt[];
extern unsigned char bul_1_eye6_TA_tex_txt[];
extern unsigned char bul_1_eye7_TA_tex_txt[];
extern unsigned char bul_1_eye8_TA_tex_txt[];
extern unsigned char bul_1_mouth1_TA_tex_txt[];
extern unsigned char bul_1_mouth2_TA_tex_txt[];
extern unsigned char bul_1_mouth3_TA_tex_txt[];
extern unsigned char bul_1_mouth4_TA_tex_txt[];
extern unsigned char bul_1_mouth5_TA_tex_txt[];
extern unsigned char bul_1_mouth6_TA_tex_txt[];
extern unsigned char bul_1_tmem_txt[];
extern unsigned short bul_2_pal[];
extern unsigned char bul_2_eye1_TA_tex_txt[];
extern unsigned char bul_2_eye2_TA_tex_txt[];
extern unsigned char bul_2_eye3_TA_tex_txt[];
extern unsigned char bul_2_eye4_TA_tex_txt[];
extern unsigned char bul_2_eye5_TA_tex_txt[];
extern unsigned char bul_2_eye6_TA_tex_txt[];
extern unsigned char bul_2_eye7_TA_tex_txt[];
extern unsigned char bul_2_eye8_TA_tex_txt[];
extern unsigned char bul_2_mouth1_TA_tex_txt[];
extern unsigned char bul_2_mouth2_TA_tex_txt[];
extern unsigned char bul_2_mouth3_TA_tex_txt[];
extern unsigned char bul_2_mouth4_TA_tex_txt[];
extern unsigned char bul_2_mouth5_TA_tex_txt[];
extern unsigned char bul_2_mouth6_TA_tex_txt[];
extern unsigned char bul_2_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_chn_1;
extern unsigned short chn_1_pal[];
extern unsigned char chn_1_eye1_TA_tex_txt[];
extern unsigned char chn_1_eye2_TA_tex_txt[];
extern unsigned char chn_1_eye3_TA_tex_txt[];
extern unsigned char chn_1_eye4_TA_tex_txt[];
extern unsigned char chn_1_eye5_TA_tex_txt[];
extern unsigned char chn_1_eye6_TA_tex_txt[];
extern unsigned char chn_1_eye7_TA_tex_txt[];
extern unsigned char chn_1_eye8_TA_tex_txt[];
extern unsigned char chn_1_tmem_txt[];
extern unsigned short chn_2_pal[];
extern unsigned char chn_2_eye1_TA_tex_txt[];
extern unsigned char chn_2_eye2_TA_tex_txt[];
extern unsigned char chn_2_eye3_TA_tex_txt[];
extern unsigned char chn_2_eye4_TA_tex_txt[];
extern unsigned char chn_2_eye5_TA_tex_txt[];
extern unsigned char chn_2_eye6_TA_tex_txt[];
extern unsigned char chn_2_eye7_TA_tex_txt[];
extern unsigned char chn_2_eye8_TA_tex_txt[];
extern unsigned char chn_2_tmem_txt[];
extern unsigned short chn_3_pal[];
extern unsigned char chn_3_eye1_TA_tex_txt[];
extern unsigned char chn_3_eye2_TA_tex_txt[];
extern unsigned char chn_3_eye3_TA_tex_txt[];
extern unsigned char chn_3_eye4_TA_tex_txt[];
extern unsigned char chn_3_eye5_TA_tex_txt[];
extern unsigned char chn_3_eye6_TA_tex_txt[];
extern unsigned char chn_3_eye7_TA_tex_txt[];
extern unsigned char chn_3_eye8_TA_tex_txt[];
extern unsigned char chn_3_tmem_txt[];
extern unsigned short chn_4_pal[];
extern unsigned char chn_4_eye1_TA_tex_txt[];
extern unsigned char chn_4_eye2_TA_tex_txt[];
extern unsigned char chn_4_eye3_TA_tex_txt[];
extern unsigned char chn_4_eye4_TA_tex_txt[];
extern unsigned char chn_4_eye5_TA_tex_txt[];
extern unsigned char chn_4_eye6_TA_tex_txt[];
extern unsigned char chn_4_eye7_TA_tex_txt[];
extern unsigned char chn_4_eye8_TA_tex_txt[];
extern unsigned char chn_4_tmem_txt[];
extern unsigned short chn_5_pal[];
extern unsigned char chn_5_eye1_TA_tex_txt[];
extern unsigned char chn_5_eye2_TA_tex_txt[];
extern unsigned char chn_5_eye3_TA_tex_txt[];
extern unsigned char chn_5_eye4_TA_tex_txt[];
extern unsigned char chn_5_eye5_TA_tex_txt[];
extern unsigned char chn_5_eye6_TA_tex_txt[];
extern unsigned char chn_5_eye7_TA_tex_txt[];
extern unsigned char chn_5_eye8_TA_tex_txt[];
extern unsigned char chn_5_tmem_txt[];
extern unsigned short chn_6_pal[];
extern unsigned char chn_6_eye1_TA_tex_txt[];
extern unsigned char chn_6_eye2_TA_tex_txt[];
extern unsigned char chn_6_eye3_TA_tex_txt[];
extern unsigned char chn_6_eye4_TA_tex_txt[];
extern unsigned char chn_6_eye5_TA_tex_txt[];
extern unsigned char chn_6_eye6_TA_tex_txt[];
extern unsigned char chn_6_eye7_TA_tex_txt[];
extern unsigned char chn_6_eye8_TA_tex_txt[];
extern unsigned char chn_6_tmem_txt[];
extern unsigned short chn_7_pal[];
extern unsigned char chn_7_eye1_TA_tex_txt[];
extern unsigned char chn_7_eye2_TA_tex_txt[];
extern unsigned char chn_7_eye3_TA_tex_txt[];
extern unsigned char chn_7_eye4_TA_tex_txt[];
extern unsigned char chn_7_eye5_TA_tex_txt[];
extern unsigned char chn_7_eye6_TA_tex_txt[];
extern unsigned char chn_7_eye7_TA_tex_txt[];
extern unsigned char chn_7_eye8_TA_tex_txt[];
extern unsigned char chn_7_tmem_txt[];
extern unsigned short chn_8_pal[];
extern unsigned char chn_8_eye1_TA_tex_txt[];
extern unsigned char chn_8_eye2_TA_tex_txt[];
extern unsigned char chn_8_eye3_TA_tex_txt[];
extern unsigned char chn_8_eye4_TA_tex_txt[];
extern unsigned char chn_8_eye5_TA_tex_txt[];
extern unsigned char chn_8_eye6_TA_tex_txt[];
extern unsigned char chn_8_eye7_TA_tex_txt[];
extern unsigned char chn_8_eye8_TA_tex_txt[];
extern unsigned char chn_8_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_cbr_1;
extern unsigned short cbr_1_pal[];
extern unsigned char cbr_1_eye1_TA_tex_txt[];
extern unsigned char cbr_1_eye2_TA_tex_txt[];
extern unsigned char cbr_1_eye3_TA_tex_txt[];
extern unsigned char cbr_1_eye4_TA_tex_txt[];
extern unsigned char cbr_1_eye5_TA_tex_txt[];
extern unsigned char cbr_1_eye6_TA_tex_txt[];
extern unsigned char cbr_1_eye7_TA_tex_txt[];
extern unsigned char cbr_1_eye8_TA_tex_txt[];
extern unsigned char cbr_1_mouth1_TA_tex_txt[];
extern unsigned char cbr_1_mouth2_TA_tex_txt[];
extern unsigned char cbr_1_mouth3_TA_tex_txt[];
extern unsigned char cbr_1_mouth4_TA_tex_txt[];
extern unsigned char cbr_1_mouth5_TA_tex_txt[];
extern unsigned char cbr_1_mouth6_TA_tex_txt[];
extern unsigned char cbr_1_tmem_txt[];
extern unsigned short cbr_2_pal[];
extern unsigned char cbr_2_eye1_TA_tex_txt[];
extern unsigned char cbr_2_eye2_TA_tex_txt[];
extern unsigned char cbr_2_eye3_TA_tex_txt[];
extern unsigned char cbr_2_eye4_TA_tex_txt[];
extern unsigned char cbr_2_eye5_TA_tex_txt[];
extern unsigned char cbr_2_eye6_TA_tex_txt[];
extern unsigned char cbr_2_eye7_TA_tex_txt[];
extern unsigned char cbr_2_eye8_TA_tex_txt[];
extern unsigned char cbr_2_mouth1_TA_tex_txt[];
extern unsigned char cbr_2_mouth2_TA_tex_txt[];
extern unsigned char cbr_2_mouth3_TA_tex_txt[];
extern unsigned char cbr_2_mouth4_TA_tex_txt[];
extern unsigned char cbr_2_mouth5_TA_tex_txt[];
extern unsigned char cbr_2_mouth6_TA_tex_txt[];
extern unsigned char cbr_2_tmem_txt[];
extern unsigned short cbr_3_pal[];
extern unsigned char cbr_3_eye1_TA_tex_txt[];
extern unsigned char cbr_3_eye2_TA_tex_txt[];
extern unsigned char cbr_3_eye3_TA_tex_txt[];
extern unsigned char cbr_3_eye4_TA_tex_txt[];
extern unsigned char cbr_3_eye5_TA_tex_txt[];
extern unsigned char cbr_3_eye6_TA_tex_txt[];
extern unsigned char cbr_3_eye7_TA_tex_txt[];
extern unsigned char cbr_3_eye8_TA_tex_txt[];
extern unsigned char cbr_3_mouth1_TA_tex_txt[];
extern unsigned char cbr_3_mouth2_TA_tex_txt[];
extern unsigned char cbr_3_mouth3_TA_tex_txt[];
extern unsigned char cbr_3_mouth4_TA_tex_txt[];
extern unsigned char cbr_3_mouth5_TA_tex_txt[];
extern unsigned char cbr_3_mouth6_TA_tex_txt[];
extern unsigned char cbr_3_tmem_txt[];
extern unsigned short cbr_4_pal[];
extern unsigned char cbr_4_eye1_TA_tex_txt[];
extern unsigned char cbr_4_eye2_TA_tex_txt[];
extern unsigned char cbr_4_eye3_TA_tex_txt[];
extern unsigned char cbr_4_eye4_TA_tex_txt[];
extern unsigned char cbr_4_eye5_TA_tex_txt[];
extern unsigned char cbr_4_eye6_TA_tex_txt[];
extern unsigned char cbr_4_eye7_TA_tex_txt[];
extern unsigned char cbr_4_eye8_TA_tex_txt[];
extern unsigned char cbr_4_mouth1_TA_tex_txt[];
extern unsigned char cbr_4_mouth2_TA_tex_txt[];
extern unsigned char cbr_4_mouth3_TA_tex_txt[];
extern unsigned char cbr_4_mouth4_TA_tex_txt[];
extern unsigned char cbr_4_mouth5_TA_tex_txt[];
extern unsigned char cbr_4_mouth6_TA_tex_txt[];
extern unsigned char cbr_4_tmem_txt[];
extern unsigned short cbr_5_pal[];
extern unsigned char cbr_5_eye1_TA_tex_txt[];
extern unsigned char cbr_5_eye2_TA_tex_txt[];
extern unsigned char cbr_5_eye3_TA_tex_txt[];
extern unsigned char cbr_5_eye4_TA_tex_txt[];
extern unsigned char cbr_5_eye5_TA_tex_txt[];
extern unsigned char cbr_5_eye6_TA_tex_txt[];
extern unsigned char cbr_5_eye7_TA_tex_txt[];
extern unsigned char cbr_5_eye8_TA_tex_txt[];
extern unsigned char cbr_5_mouth1_TA_tex_txt[];
extern unsigned char cbr_5_mouth2_TA_tex_txt[];
extern unsigned char cbr_5_mouth3_TA_tex_txt[];
extern unsigned char cbr_5_mouth4_TA_tex_txt[];
extern unsigned char cbr_5_mouth5_TA_tex_txt[];
extern unsigned char cbr_5_mouth6_TA_tex_txt[];
extern unsigned char cbr_5_tmem_txt[];
extern unsigned short cbr_6_pal[];
extern unsigned char cbr_6_eye1_TA_tex_txt[];
extern unsigned char cbr_6_eye2_TA_tex_txt[];
extern unsigned char cbr_6_eye3_TA_tex_txt[];
extern unsigned char cbr_6_eye4_TA_tex_txt[];
extern unsigned char cbr_6_eye5_TA_tex_txt[];
extern unsigned char cbr_6_eye6_TA_tex_txt[];
extern unsigned char cbr_6_eye7_TA_tex_txt[];
extern unsigned char cbr_6_eye8_TA_tex_txt[];
extern unsigned char cbr_6_mouth1_TA_tex_txt[];
extern unsigned char cbr_6_mouth2_TA_tex_txt[];
extern unsigned char cbr_6_mouth3_TA_tex_txt[];
extern unsigned char cbr_6_mouth4_TA_tex_txt[];
extern unsigned char cbr_6_mouth5_TA_tex_txt[];
extern unsigned char cbr_6_mouth6_TA_tex_txt[];
extern unsigned char cbr_6_tmem_txt[];
extern unsigned short cbr_7_pal[];
extern unsigned char cbr_7_eye1_TA_tex_txt[];
extern unsigned char cbr_7_eye2_TA_tex_txt[];
extern unsigned char cbr_7_eye3_TA_tex_txt[];
extern unsigned char cbr_7_eye4_TA_tex_txt[];
extern unsigned char cbr_7_eye5_TA_tex_txt[];
extern unsigned char cbr_7_eye6_TA_tex_txt[];
extern unsigned char cbr_7_eye7_TA_tex_txt[];
extern unsigned char cbr_7_eye8_TA_tex_txt[];
extern unsigned char cbr_7_mouth1_TA_tex_txt[];
extern unsigned char cbr_7_mouth2_TA_tex_txt[];
extern unsigned char cbr_7_mouth3_TA_tex_txt[];
extern unsigned char cbr_7_mouth4_TA_tex_txt[];
extern unsigned char cbr_7_mouth5_TA_tex_txt[];
extern unsigned char cbr_7_mouth6_TA_tex_txt[];
extern unsigned char cbr_7_tmem_txt[];
extern unsigned short cbr_8_pal[];
extern unsigned char cbr_8_eye1_TA_tex_txt[];
extern unsigned char cbr_8_eye2_TA_tex_txt[];
extern unsigned char cbr_8_eye3_TA_tex_txt[];
extern unsigned char cbr_8_eye4_TA_tex_txt[];
extern unsigned char cbr_8_eye5_TA_tex_txt[];
extern unsigned char cbr_8_eye6_TA_tex_txt[];
extern unsigned char cbr_8_eye7_TA_tex_txt[];
extern unsigned char cbr_8_eye8_TA_tex_txt[];
extern unsigned char cbr_8_mouth1_TA_tex_txt[];
extern unsigned char cbr_8_mouth2_TA_tex_txt[];
extern unsigned char cbr_8_mouth3_TA_tex_txt[];
extern unsigned char cbr_8_mouth4_TA_tex_txt[];
extern unsigned char cbr_8_mouth5_TA_tex_txt[];
extern unsigned char cbr_8_mouth6_TA_tex_txt[];
extern unsigned char cbr_8_tmem_txt[];
extern unsigned short cbr_9_pal[];
extern unsigned char cbr_9_eye1_TA_tex_txt[];
extern unsigned char cbr_9_eye2_TA_tex_txt[];
extern unsigned char cbr_9_eye3_TA_tex_txt[];
extern unsigned char cbr_9_eye4_TA_tex_txt[];
extern unsigned char cbr_9_eye5_TA_tex_txt[];
extern unsigned char cbr_9_eye6_TA_tex_txt[];
extern unsigned char cbr_9_eye7_TA_tex_txt[];
extern unsigned char cbr_9_eye8_TA_tex_txt[];
extern unsigned char cbr_9_mouth1_TA_tex_txt[];
extern unsigned char cbr_9_mouth2_TA_tex_txt[];
extern unsigned char cbr_9_mouth3_TA_tex_txt[];
extern unsigned char cbr_9_mouth4_TA_tex_txt[];
extern unsigned char cbr_9_mouth5_TA_tex_txt[];
extern unsigned char cbr_9_mouth6_TA_tex_txt[];
extern unsigned char cbr_9_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_cow_1;
extern unsigned short cow_1_pal[];
extern unsigned char cow_1_eye1_TA_tex_txt[];
extern unsigned char cow_1_eye2_TA_tex_txt[];
extern unsigned char cow_1_eye3_TA_tex_txt[];
extern unsigned char cow_1_eye4_TA_tex_txt[];
extern unsigned char cow_1_eye5_TA_tex_txt[];
extern unsigned char cow_1_eye6_TA_tex_txt[];
extern unsigned char cow_1_eye7_TA_tex_txt[];
extern unsigned char cow_1_eye8_TA_tex_txt[];
extern unsigned char cow_1_mouth1_TA_tex_txt[];
extern unsigned char cow_1_mouth2_TA_tex_txt[];
extern unsigned char cow_1_mouth3_TA_tex_txt[];
extern unsigned char cow_1_mouth4_TA_tex_txt[];
extern unsigned char cow_1_mouth5_TA_tex_txt[];
extern unsigned char cow_1_mouth6_TA_tex_txt[];
extern unsigned char cow_1_tmem_txt[];
extern unsigned short cow_2_pal[];
extern unsigned char cow_2_eye1_TA_tex_txt[];
extern unsigned char cow_2_eye2_TA_tex_txt[];
extern unsigned char cow_2_eye3_TA_tex_txt[];
extern unsigned char cow_2_eye4_TA_tex_txt[];
extern unsigned char cow_2_eye5_TA_tex_txt[];
extern unsigned char cow_2_eye6_TA_tex_txt[];
extern unsigned char cow_2_eye7_TA_tex_txt[];
extern unsigned char cow_2_eye8_TA_tex_txt[];
extern unsigned char cow_2_mouth1_TA_tex_txt[];
extern unsigned char cow_2_mouth2_TA_tex_txt[];
extern unsigned char cow_2_mouth3_TA_tex_txt[];
extern unsigned char cow_2_mouth4_TA_tex_txt[];
extern unsigned char cow_2_mouth5_TA_tex_txt[];
extern unsigned char cow_2_mouth6_TA_tex_txt[];
extern unsigned char cow_2_tmem_txt[];
extern unsigned short cow_3_pal[];
extern unsigned char cow_3_eye1_TA_tex_txt[];
extern unsigned char cow_3_eye2_TA_tex_txt[];
extern unsigned char cow_3_eye3_TA_tex_txt[];
extern unsigned char cow_3_eye4_TA_tex_txt[];
extern unsigned char cow_3_eye5_TA_tex_txt[];
extern unsigned char cow_3_eye6_TA_tex_txt[];
extern unsigned char cow_3_eye7_TA_tex_txt[];
extern unsigned char cow_3_eye8_TA_tex_txt[];
extern unsigned char cow_3_mouth1_TA_tex_txt[];
extern unsigned char cow_3_mouth2_TA_tex_txt[];
extern unsigned char cow_3_mouth3_TA_tex_txt[];
extern unsigned char cow_3_mouth4_TA_tex_txt[];
extern unsigned char cow_3_mouth5_TA_tex_txt[];
extern unsigned char cow_3_mouth6_TA_tex_txt[];
extern unsigned char cow_3_tmem_txt[];
extern unsigned short cow_4_pal[];
extern unsigned char cow_4_eye1_TA_tex_txt[];
extern unsigned char cow_4_eye2_TA_tex_txt[];
extern unsigned char cow_4_eye3_TA_tex_txt[];
extern unsigned char cow_4_eye4_TA_tex_txt[];
extern unsigned char cow_4_eye5_TA_tex_txt[];
extern unsigned char cow_4_eye6_TA_tex_txt[];
extern unsigned char cow_4_eye7_TA_tex_txt[];
extern unsigned char cow_4_eye8_TA_tex_txt[];
extern unsigned char cow_4_mouth1_TA_tex_txt[];
extern unsigned char cow_4_mouth2_TA_tex_txt[];
extern unsigned char cow_4_mouth3_TA_tex_txt[];
extern unsigned char cow_4_mouth4_TA_tex_txt[];
extern unsigned char cow_4_mouth5_TA_tex_txt[];
extern unsigned char cow_4_mouth6_TA_tex_txt[];
extern unsigned char cow_4_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_crd_1;
extern unsigned short crd_1_pal[];
extern unsigned char crd_1_eye1_TA_tex_txt[];
extern unsigned char crd_1_eye2_TA_tex_txt[];
extern unsigned char crd_1_eye3_TA_tex_txt[];
extern unsigned char crd_1_eye4_TA_tex_txt[];
extern unsigned char crd_1_eye5_TA_tex_txt[];
extern unsigned char crd_1_eye6_TA_tex_txt[];
extern unsigned char crd_1_eye7_TA_tex_txt[];
extern unsigned char crd_1_eye8_TA_tex_txt[];
extern unsigned char crd_1_tmem_txt[];
extern unsigned short crd_2_pal[];
extern unsigned char crd_2_eye1_TA_tex_txt[];
extern unsigned char crd_2_eye2_TA_tex_txt[];
extern unsigned char crd_2_eye3_TA_tex_txt[];
extern unsigned char crd_2_eye4_TA_tex_txt[];
extern unsigned char crd_2_eye5_TA_tex_txt[];
extern unsigned char crd_2_eye6_TA_tex_txt[];
extern unsigned char crd_2_eye7_TA_tex_txt[];
extern unsigned char crd_2_eye8_TA_tex_txt[];
extern unsigned char crd_2_tmem_txt[];
extern unsigned short crd_3_pal[];
extern unsigned char crd_3_eye1_TA_tex_txt[];
extern unsigned char crd_3_eye2_TA_tex_txt[];
extern unsigned char crd_3_eye3_TA_tex_txt[];
extern unsigned char crd_3_eye4_TA_tex_txt[];
extern unsigned char crd_3_eye5_TA_tex_txt[];
extern unsigned char crd_3_eye6_TA_tex_txt[];
extern unsigned char crd_3_eye7_TA_tex_txt[];
extern unsigned char crd_3_eye8_TA_tex_txt[];
extern unsigned char crd_3_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_dog_1;
extern unsigned short dog_1_pal[];
extern unsigned char dog_1_eye1_TA_tex_txt[];
extern unsigned char dog_1_eye2_TA_tex_txt[];
extern unsigned char dog_1_eye3_TA_tex_txt[];
extern unsigned char dog_1_eye4_TA_tex_txt[];
extern unsigned char dog_1_eye5_TA_tex_txt[];
extern unsigned char dog_1_eye6_TA_tex_txt[];
extern unsigned char dog_1_eye7_TA_tex_txt[];
extern unsigned char dog_1_eye8_TA_tex_txt[];
extern unsigned char dog_1_mouth1_TA_tex_txt[];
extern unsigned char dog_1_mouth2_TA_tex_txt[];
extern unsigned char dog_1_mouth3_TA_tex_txt[];
extern unsigned char dog_1_mouth4_TA_tex_txt[];
extern unsigned char dog_1_mouth5_TA_tex_txt[];
extern unsigned char dog_1_mouth6_TA_tex_txt[];
extern unsigned char dog_1_tmem_txt[];
extern unsigned short dog_2_pal[];
extern unsigned char dog_2_eye1_TA_tex_txt[];
extern unsigned char dog_2_eye2_TA_tex_txt[];
extern unsigned char dog_2_eye3_TA_tex_txt[];
extern unsigned char dog_2_eye4_TA_tex_txt[];
extern unsigned char dog_2_eye5_TA_tex_txt[];
extern unsigned char dog_2_eye6_TA_tex_txt[];
extern unsigned char dog_2_eye7_TA_tex_txt[];
extern unsigned char dog_2_eye8_TA_tex_txt[];
extern unsigned char dog_2_mouth1_TA_tex_txt[];
extern unsigned char dog_2_mouth2_TA_tex_txt[];
extern unsigned char dog_2_mouth3_TA_tex_txt[];
extern unsigned char dog_2_mouth4_TA_tex_txt[];
extern unsigned char dog_2_mouth5_TA_tex_txt[];
extern unsigned char dog_2_mouth6_TA_tex_txt[];
extern unsigned char dog_2_tmem_txt[];
extern unsigned short dog_3_pal[];
extern unsigned char dog_3_eye1_TA_tex_txt[];
extern unsigned char dog_3_eye2_TA_tex_txt[];
extern unsigned char dog_3_eye3_TA_tex_txt[];
extern unsigned char dog_3_eye4_TA_tex_txt[];
extern unsigned char dog_3_eye5_TA_tex_txt[];
extern unsigned char dog_3_eye6_TA_tex_txt[];
extern unsigned char dog_3_eye7_TA_tex_txt[];
extern unsigned char dog_3_eye8_TA_tex_txt[];
extern unsigned char dog_3_mouth1_TA_tex_txt[];
extern unsigned char dog_3_mouth2_TA_tex_txt[];
extern unsigned char dog_3_mouth3_TA_tex_txt[];
extern unsigned char dog_3_mouth4_TA_tex_txt[];
extern unsigned char dog_3_mouth5_TA_tex_txt[];
extern unsigned char dog_3_mouth6_TA_tex_txt[];
extern unsigned char dog_3_tmem_txt[];
extern unsigned short dog_4_pal[];
extern unsigned char dog_4_eye1_TA_tex_txt[];
extern unsigned char dog_4_eye2_TA_tex_txt[];
extern unsigned char dog_4_eye3_TA_tex_txt[];
extern unsigned char dog_4_eye4_TA_tex_txt[];
extern unsigned char dog_4_eye5_TA_tex_txt[];
extern unsigned char dog_4_eye6_TA_tex_txt[];
extern unsigned char dog_4_eye7_TA_tex_txt[];
extern unsigned char dog_4_eye8_TA_tex_txt[];
extern unsigned char dog_4_mouth1_TA_tex_txt[];
extern unsigned char dog_4_mouth2_TA_tex_txt[];
extern unsigned char dog_4_mouth3_TA_tex_txt[];
extern unsigned char dog_4_mouth4_TA_tex_txt[];
extern unsigned char dog_4_mouth5_TA_tex_txt[];
extern unsigned char dog_4_mouth6_TA_tex_txt[];
extern unsigned char dog_4_tmem_txt[];
extern unsigned short dog_5_pal[];
extern unsigned char dog_5_eye1_TA_tex_txt[];
extern unsigned char dog_5_eye2_TA_tex_txt[];
extern unsigned char dog_5_eye3_TA_tex_txt[];
extern unsigned char dog_5_eye4_TA_tex_txt[];
extern unsigned char dog_5_eye5_TA_tex_txt[];
extern unsigned char dog_5_eye6_TA_tex_txt[];
extern unsigned char dog_5_eye7_TA_tex_txt[];
extern unsigned char dog_5_eye8_TA_tex_txt[];
extern unsigned char dog_5_mouth1_TA_tex_txt[];
extern unsigned char dog_5_mouth2_TA_tex_txt[];
extern unsigned char dog_5_mouth3_TA_tex_txt[];
extern unsigned char dog_5_mouth4_TA_tex_txt[];
extern unsigned char dog_5_mouth5_TA_tex_txt[];
extern unsigned char dog_5_mouth6_TA_tex_txt[];
extern unsigned char dog_5_tmem_txt[];
extern unsigned short dog_6_pal[];
extern unsigned char dog_6_eye1_TA_tex_txt[];
extern unsigned char dog_6_eye2_TA_tex_txt[];
extern unsigned char dog_6_eye3_TA_tex_txt[];
extern unsigned char dog_6_eye4_TA_tex_txt[];
extern unsigned char dog_6_eye5_TA_tex_txt[];
extern unsigned char dog_6_eye6_TA_tex_txt[];
extern unsigned char dog_6_eye7_TA_tex_txt[];
extern unsigned char dog_6_eye8_TA_tex_txt[];
extern unsigned char dog_6_mouth1_TA_tex_txt[];
extern unsigned char dog_6_mouth2_TA_tex_txt[];
extern unsigned char dog_6_mouth3_TA_tex_txt[];
extern unsigned char dog_6_mouth4_TA_tex_txt[];
extern unsigned char dog_6_mouth5_TA_tex_txt[];
extern unsigned char dog_6_mouth6_TA_tex_txt[];
extern unsigned char dog_6_tmem_txt[];
extern unsigned short dog_8_pal[];
extern unsigned char dog_8_eye1_TA_tex_txt[];
extern unsigned char dog_8_eye2_TA_tex_txt[];
extern unsigned char dog_8_eye3_TA_tex_txt[];
extern unsigned char dog_8_eye4_TA_tex_txt[];
extern unsigned char dog_8_eye5_TA_tex_txt[];
extern unsigned char dog_8_eye6_TA_tex_txt[];
extern unsigned char dog_8_eye7_TA_tex_txt[];
extern unsigned char dog_8_eye8_TA_tex_txt[];
extern unsigned char dog_8_mouth1_TA_tex_txt[];
extern unsigned char dog_8_mouth2_TA_tex_txt[];
extern unsigned char dog_8_mouth3_TA_tex_txt[];
extern unsigned char dog_8_mouth4_TA_tex_txt[];
extern unsigned char dog_8_mouth5_TA_tex_txt[];
extern unsigned char dog_8_mouth6_TA_tex_txt[];
extern unsigned char dog_8_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_duk_1;
extern unsigned short duk_1_pal[];
extern unsigned char duk_1_eye1_TA_tex_txt[];
extern unsigned char duk_1_eye2_TA_tex_txt[];
extern unsigned char duk_1_eye3_TA_tex_txt[];
extern unsigned char duk_1_eye4_TA_tex_txt[];
extern unsigned char duk_1_eye5_TA_tex_txt[];
extern unsigned char duk_1_eye6_TA_tex_txt[];
extern unsigned char duk_1_eye7_TA_tex_txt[];
extern unsigned char duk_1_eye8_TA_tex_txt[];
extern unsigned char duk_1_mouth1_TA_tex_txt[];
extern unsigned char duk_1_mouth2_TA_tex_txt[];
extern unsigned char duk_1_mouth3_TA_tex_txt[];
extern unsigned char duk_1_mouth4_TA_tex_txt[];
extern unsigned char duk_1_mouth5_TA_tex_txt[];
extern unsigned char duk_1_mouth6_TA_tex_txt[];
extern unsigned char duk_1_tmem_txt[];
extern unsigned short duk_2_pal[];
extern unsigned char duk_2_eye1_TA_tex_txt[];
extern unsigned char duk_2_eye2_TA_tex_txt[];
extern unsigned char duk_2_eye3_TA_tex_txt[];
extern unsigned char duk_2_eye4_TA_tex_txt[];
extern unsigned char duk_2_eye5_TA_tex_txt[];
extern unsigned char duk_2_eye6_TA_tex_txt[];
extern unsigned char duk_2_eye7_TA_tex_txt[];
extern unsigned char duk_2_eye8_TA_tex_txt[];
extern unsigned char duk_2_mouth1_TA_tex_txt[];
extern unsigned char duk_2_mouth2_TA_tex_txt[];
extern unsigned char duk_2_mouth3_TA_tex_txt[];
extern unsigned char duk_2_mouth4_TA_tex_txt[];
extern unsigned char duk_2_mouth5_TA_tex_txt[];
extern unsigned char duk_2_mouth6_TA_tex_txt[];
extern unsigned char duk_2_tmem_txt[];
extern unsigned short duk_3_pal[];
extern unsigned char duk_3_eye1_TA_tex_txt[];
extern unsigned char duk_3_eye2_TA_tex_txt[];
extern unsigned char duk_3_eye3_TA_tex_txt[];
extern unsigned char duk_3_eye4_TA_tex_txt[];
extern unsigned char duk_3_eye5_TA_tex_txt[];
extern unsigned char duk_3_eye6_TA_tex_txt[];
extern unsigned char duk_3_eye7_TA_tex_txt[];
extern unsigned char duk_3_eye8_TA_tex_txt[];
extern unsigned char duk_3_mouth1_TA_tex_txt[];
extern unsigned char duk_3_mouth2_TA_tex_txt[];
extern unsigned char duk_3_mouth3_TA_tex_txt[];
extern unsigned char duk_3_mouth4_TA_tex_txt[];
extern unsigned char duk_3_mouth5_TA_tex_txt[];
extern unsigned char duk_3_mouth6_TA_tex_txt[];
extern unsigned char duk_3_tmem_txt[];
extern unsigned short duk_4_pal[];
extern unsigned char duk_4_eye1_TA_tex_txt[];
extern unsigned char duk_4_eye2_TA_tex_txt[];
extern unsigned char duk_4_eye3_TA_tex_txt[];
extern unsigned char duk_4_eye4_TA_tex_txt[];
extern unsigned char duk_4_eye5_TA_tex_txt[];
extern unsigned char duk_4_eye6_TA_tex_txt[];
extern unsigned char duk_4_eye7_TA_tex_txt[];
extern unsigned char duk_4_eye8_TA_tex_txt[];
extern unsigned char duk_4_mouth1_TA_tex_txt[];
extern unsigned char duk_4_mouth2_TA_tex_txt[];
extern unsigned char duk_4_mouth3_TA_tex_txt[];
extern unsigned char duk_4_mouth4_TA_tex_txt[];
extern unsigned char duk_4_mouth5_TA_tex_txt[];
extern unsigned char duk_4_mouth6_TA_tex_txt[];
extern unsigned char duk_4_tmem_txt[];
extern unsigned short duk_5_pal[];
extern unsigned char duk_5_eye1_TA_tex_txt[];
extern unsigned char duk_5_eye2_TA_tex_txt[];
extern unsigned char duk_5_eye3_TA_tex_txt[];
extern unsigned char duk_5_eye4_TA_tex_txt[];
extern unsigned char duk_5_eye5_TA_tex_txt[];
extern unsigned char duk_5_eye6_TA_tex_txt[];
extern unsigned char duk_5_eye7_TA_tex_txt[];
extern unsigned char duk_5_eye8_TA_tex_txt[];
extern unsigned char duk_5_mouth1_TA_tex_txt[];
extern unsigned char duk_5_mouth2_TA_tex_txt[];
extern unsigned char duk_5_mouth3_TA_tex_txt[];
extern unsigned char duk_5_mouth4_TA_tex_txt[];
extern unsigned char duk_5_mouth5_TA_tex_txt[];
extern unsigned char duk_5_mouth6_TA_tex_txt[];
extern unsigned char duk_5_tmem_txt[];
extern unsigned short duk_6_pal[];
extern unsigned char duk_6_eye1_TA_tex_txt[];
extern unsigned char duk_6_eye2_TA_tex_txt[];
extern unsigned char duk_6_eye3_TA_tex_txt[];
extern unsigned char duk_6_eye4_TA_tex_txt[];
extern unsigned char duk_6_eye5_TA_tex_txt[];
extern unsigned char duk_6_eye6_TA_tex_txt[];
extern unsigned char duk_6_eye7_TA_tex_txt[];
extern unsigned char duk_6_eye8_TA_tex_txt[];
extern unsigned char duk_6_mouth1_TA_tex_txt[];
extern unsigned char duk_6_mouth2_TA_tex_txt[];
extern unsigned char duk_6_mouth3_TA_tex_txt[];
extern unsigned char duk_6_mouth4_TA_tex_txt[];
extern unsigned char duk_6_mouth5_TA_tex_txt[];
extern unsigned char duk_6_mouth6_TA_tex_txt[];
extern unsigned char duk_6_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_elp_1;
extern unsigned short elp_1_pal[];
extern unsigned char elp_1_eye1_TA_tex_txt[];
extern unsigned char elp_1_eye2_TA_tex_txt[];
extern unsigned char elp_1_eye3_TA_tex_txt[];
extern unsigned char elp_1_eye4_TA_tex_txt[];
extern unsigned char elp_1_eye5_TA_tex_txt[];
extern unsigned char elp_1_eye6_TA_tex_txt[];
extern unsigned char elp_1_eye7_TA_tex_txt[];
extern unsigned char elp_1_eye8_TA_tex_txt[];
extern unsigned char elp_1_mouth1_TA_tex_txt[];
extern unsigned char elp_1_mouth2_TA_tex_txt[];
extern unsigned char elp_1_mouth3_TA_tex_txt[];
extern unsigned char elp_1_mouth4_TA_tex_txt[];
extern unsigned char elp_1_mouth5_TA_tex_txt[];
extern unsigned char elp_1_mouth6_TA_tex_txt[];
extern unsigned char elp_1_tmem_txt[];
extern unsigned short elp_2_pal[];
extern unsigned char elp_2_eye1_TA_tex_txt[];
extern unsigned char elp_2_eye2_TA_tex_txt[];
extern unsigned char elp_2_eye3_TA_tex_txt[];
extern unsigned char elp_2_eye4_TA_tex_txt[];
extern unsigned char elp_2_eye5_TA_tex_txt[];
extern unsigned char elp_2_eye6_TA_tex_txt[];
extern unsigned char elp_2_eye7_TA_tex_txt[];
extern unsigned char elp_2_eye8_TA_tex_txt[];
extern unsigned char elp_2_mouth1_TA_tex_txt[];
extern unsigned char elp_2_mouth2_TA_tex_txt[];
extern unsigned char elp_2_mouth3_TA_tex_txt[];
extern unsigned char elp_2_mouth4_TA_tex_txt[];
extern unsigned char elp_2_mouth5_TA_tex_txt[];
extern unsigned char elp_2_mouth6_TA_tex_txt[];
extern unsigned char elp_2_tmem_txt[];
extern unsigned short elp_3_pal[];
extern unsigned char elp_3_eye1_TA_tex_txt[];
extern unsigned char elp_3_eye2_TA_tex_txt[];
extern unsigned char elp_3_eye3_TA_tex_txt[];
extern unsigned char elp_3_eye4_TA_tex_txt[];
extern unsigned char elp_3_eye5_TA_tex_txt[];
extern unsigned char elp_3_eye6_TA_tex_txt[];
extern unsigned char elp_3_eye7_TA_tex_txt[];
extern unsigned char elp_3_eye8_TA_tex_txt[];
extern unsigned char elp_3_mouth1_TA_tex_txt[];
extern unsigned char elp_3_mouth2_TA_tex_txt[];
extern unsigned char elp_3_mouth3_TA_tex_txt[];
extern unsigned char elp_3_mouth4_TA_tex_txt[];
extern unsigned char elp_3_mouth5_TA_tex_txt[];
extern unsigned char elp_3_mouth6_TA_tex_txt[];
extern unsigned char elp_3_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_flg_1;
extern unsigned short flg_1_pal[];
extern unsigned char flg_1_eye1_TA_tex_txt[];
extern unsigned char flg_1_eye2_TA_tex_txt[];
extern unsigned char flg_1_eye3_TA_tex_txt[];
extern unsigned char flg_1_eye4_TA_tex_txt[];
extern unsigned char flg_1_eye5_TA_tex_txt[];
extern unsigned char flg_1_eye6_TA_tex_txt[];
extern unsigned char flg_1_eye7_TA_tex_txt[];
extern unsigned char flg_1_eye8_TA_tex_txt[];
extern unsigned char flg_1_mouth1_TA_tex_txt[];
extern unsigned char flg_1_mouth2_TA_tex_txt[];
extern unsigned char flg_1_mouth3_TA_tex_txt[];
extern unsigned char flg_1_mouth4_TA_tex_txt[];
extern unsigned char flg_1_mouth5_TA_tex_txt[];
extern unsigned char flg_1_mouth6_TA_tex_txt[];
extern unsigned char flg_1_tmem_txt[];
extern unsigned short flg_2_pal[];
extern unsigned char flg_2_eye1_TA_tex_txt[];
extern unsigned char flg_2_eye2_TA_tex_txt[];
extern unsigned char flg_2_eye3_TA_tex_txt[];
extern unsigned char flg_2_eye4_TA_tex_txt[];
extern unsigned char flg_2_eye5_TA_tex_txt[];
extern unsigned char flg_2_eye6_TA_tex_txt[];
extern unsigned char flg_2_eye7_TA_tex_txt[];
extern unsigned char flg_2_eye8_TA_tex_txt[];
extern unsigned char flg_2_mouth1_TA_tex_txt[];
extern unsigned char flg_2_mouth2_TA_tex_txt[];
extern unsigned char flg_2_mouth3_TA_tex_txt[];
extern unsigned char flg_2_mouth4_TA_tex_txt[];
extern unsigned char flg_2_mouth5_TA_tex_txt[];
extern unsigned char flg_2_mouth6_TA_tex_txt[];
extern unsigned char flg_2_tmem_txt[];
extern unsigned short flg_3_pal[];
extern unsigned char flg_3_eye1_TA_tex_txt[];
extern unsigned char flg_3_eye2_TA_tex_txt[];
extern unsigned char flg_3_eye3_TA_tex_txt[];
extern unsigned char flg_3_eye4_TA_tex_txt[];
extern unsigned char flg_3_eye5_TA_tex_txt[];
extern unsigned char flg_3_eye6_TA_tex_txt[];
extern unsigned char flg_3_eye7_TA_tex_txt[];
extern unsigned char flg_3_eye8_TA_tex_txt[];
extern unsigned char flg_3_mouth1_TA_tex_txt[];
extern unsigned char flg_3_mouth2_TA_tex_txt[];
extern unsigned char flg_3_mouth3_TA_tex_txt[];
extern unsigned char flg_3_mouth4_TA_tex_txt[];
extern unsigned char flg_3_mouth5_TA_tex_txt[];
extern unsigned char flg_3_mouth6_TA_tex_txt[];
extern unsigned char flg_3_tmem_txt[];
extern unsigned short flg_4_pal[];
extern unsigned char flg_4_eye1_TA_tex_txt[];
extern unsigned char flg_4_eye2_TA_tex_txt[];
extern unsigned char flg_4_eye3_TA_tex_txt[];
extern unsigned char flg_4_eye4_TA_tex_txt[];
extern unsigned char flg_4_eye5_TA_tex_txt[];
extern unsigned char flg_4_eye6_TA_tex_txt[];
extern unsigned char flg_4_eye7_TA_tex_txt[];
extern unsigned char flg_4_eye8_TA_tex_txt[];
extern unsigned char flg_4_mouth1_TA_tex_txt[];
extern unsigned char flg_4_mouth2_TA_tex_txt[];
extern unsigned char flg_4_mouth3_TA_tex_txt[];
extern unsigned char flg_4_mouth4_TA_tex_txt[];
extern unsigned char flg_4_mouth5_TA_tex_txt[];
extern unsigned char flg_4_mouth6_TA_tex_txt[];
extern unsigned char flg_4_tmem_txt[];
extern unsigned short flg_5_pal[];
extern unsigned char flg_5_eye1_TA_tex_txt[];
extern unsigned char flg_5_eye2_TA_tex_txt[];
extern unsigned char flg_5_eye3_TA_tex_txt[];
extern unsigned char flg_5_eye4_TA_tex_txt[];
extern unsigned char flg_5_eye5_TA_tex_txt[];
extern unsigned char flg_5_eye6_TA_tex_txt[];
extern unsigned char flg_5_eye7_TA_tex_txt[];
extern unsigned char flg_5_eye8_TA_tex_txt[];
extern unsigned char flg_5_mouth1_TA_tex_txt[];
extern unsigned char flg_5_mouth2_TA_tex_txt[];
extern unsigned char flg_5_mouth3_TA_tex_txt[];
extern unsigned char flg_5_mouth4_TA_tex_txt[];
extern unsigned char flg_5_mouth5_TA_tex_txt[];
extern unsigned char flg_5_mouth6_TA_tex_txt[];
extern unsigned char flg_5_tmem_txt[];
extern unsigned short flg_6_pal[];
extern unsigned char flg_6_eye1_TA_tex_txt[];
extern unsigned char flg_6_eye2_TA_tex_txt[];
extern unsigned char flg_6_eye3_TA_tex_txt[];
extern unsigned char flg_6_eye4_TA_tex_txt[];
extern unsigned char flg_6_eye5_TA_tex_txt[];
extern unsigned char flg_6_eye6_TA_tex_txt[];
extern unsigned char flg_6_eye7_TA_tex_txt[];
extern unsigned char flg_6_eye8_TA_tex_txt[];
extern unsigned char flg_6_mouth1_TA_tex_txt[];
extern unsigned char flg_6_mouth2_TA_tex_txt[];
extern unsigned char flg_6_mouth3_TA_tex_txt[];
extern unsigned char flg_6_mouth4_TA_tex_txt[];
extern unsigned char flg_6_mouth5_TA_tex_txt[];
extern unsigned char flg_6_mouth6_TA_tex_txt[];
extern unsigned char flg_6_tmem_txt[];
extern unsigned short flg_7_pal[];
extern unsigned char flg_7_eye1_TA_tex_txt[];
extern unsigned char flg_7_eye2_TA_tex_txt[];
extern unsigned char flg_7_eye3_TA_tex_txt[];
extern unsigned char flg_7_eye4_TA_tex_txt[];
extern unsigned char flg_7_eye5_TA_tex_txt[];
extern unsigned char flg_7_eye6_TA_tex_txt[];
extern unsigned char flg_7_eye7_TA_tex_txt[];
extern unsigned char flg_7_eye8_TA_tex_txt[];
extern unsigned char flg_7_mouth1_TA_tex_txt[];
extern unsigned char flg_7_mouth2_TA_tex_txt[];
extern unsigned char flg_7_mouth3_TA_tex_txt[];
extern unsigned char flg_7_mouth4_TA_tex_txt[];
extern unsigned char flg_7_mouth5_TA_tex_txt[];
extern unsigned char flg_7_mouth6_TA_tex_txt[];
extern unsigned char flg_7_tmem_txt[];
extern unsigned short flg_8_pal[];
extern unsigned char flg_8_eye1_TA_tex_txt[];
extern unsigned char flg_8_eye2_TA_tex_txt[];
extern unsigned char flg_8_eye3_TA_tex_txt[];
extern unsigned char flg_8_eye4_TA_tex_txt[];
extern unsigned char flg_8_eye5_TA_tex_txt[];
extern unsigned char flg_8_eye6_TA_tex_txt[];
extern unsigned char flg_8_eye7_TA_tex_txt[];
extern unsigned char flg_8_eye8_TA_tex_txt[];
extern unsigned char flg_8_mouth1_TA_tex_txt[];
extern unsigned char flg_8_mouth2_TA_tex_txt[];
extern unsigned char flg_8_mouth3_TA_tex_txt[];
extern unsigned char flg_8_mouth4_TA_tex_txt[];
extern unsigned char flg_8_mouth5_TA_tex_txt[];
extern unsigned char flg_8_mouth6_TA_tex_txt[];
extern unsigned char flg_8_tmem_txt[];
extern unsigned short flg_9_pal[];
extern unsigned char flg_9_eye1_TA_tex_txt[];
extern unsigned char flg_9_eye2_TA_tex_txt[];
extern unsigned char flg_9_eye3_TA_tex_txt[];
extern unsigned char flg_9_eye4_TA_tex_txt[];
extern unsigned char flg_9_eye5_TA_tex_txt[];
extern unsigned char flg_9_eye6_TA_tex_txt[];
extern unsigned char flg_9_eye7_TA_tex_txt[];
extern unsigned char flg_9_eye8_TA_tex_txt[];
extern unsigned char flg_9_mouth1_TA_tex_txt[];
extern unsigned char flg_9_mouth2_TA_tex_txt[];
extern unsigned char flg_9_mouth3_TA_tex_txt[];
extern unsigned char flg_9_mouth4_TA_tex_txt[];
extern unsigned char flg_9_mouth5_TA_tex_txt[];
extern unsigned char flg_9_mouth6_TA_tex_txt[];
extern unsigned char flg_9_tmem_txt[];
extern unsigned short flg_10_pal[];
extern unsigned char flg_10_eye1_TA_tex_txt[];
extern unsigned char flg_10_eye2_TA_tex_txt[];
extern unsigned char flg_10_eye3_TA_tex_txt[];
extern unsigned char flg_10_eye4_TA_tex_txt[];
extern unsigned char flg_10_eye5_TA_tex_txt[];
extern unsigned char flg_10_eye6_TA_tex_txt[];
extern unsigned char flg_10_eye7_TA_tex_txt[];
extern unsigned char flg_10_eye8_TA_tex_txt[];
extern unsigned char flg_10_mouth1_TA_tex_txt[];
extern unsigned char flg_10_mouth2_TA_tex_txt[];
extern unsigned char flg_10_mouth3_TA_tex_txt[];
extern unsigned char flg_10_mouth4_TA_tex_txt[];
extern unsigned char flg_10_mouth5_TA_tex_txt[];
extern unsigned char flg_10_mouth6_TA_tex_txt[];
extern unsigned char flg_10_tmem_txt[];
extern unsigned short flg_11_pal[];
extern unsigned char flg_11_eye1_TA_tex_txt[];
extern unsigned char flg_11_eye2_TA_tex_txt[];
extern unsigned char flg_11_eye3_TA_tex_txt[];
extern unsigned char flg_11_eye4_TA_tex_txt[];
extern unsigned char flg_11_eye5_TA_tex_txt[];
extern unsigned char flg_11_eye6_TA_tex_txt[];
extern unsigned char flg_11_eye7_TA_tex_txt[];
extern unsigned char flg_11_eye8_TA_tex_txt[];
extern unsigned char flg_11_mouth1_TA_tex_txt[];
extern unsigned char flg_11_mouth2_TA_tex_txt[];
extern unsigned char flg_11_mouth3_TA_tex_txt[];
extern unsigned char flg_11_mouth4_TA_tex_txt[];
extern unsigned char flg_11_mouth5_TA_tex_txt[];
extern unsigned char flg_11_mouth6_TA_tex_txt[];
extern unsigned char flg_11_tmem_txt[];
extern unsigned short flg_12_pal[];
extern unsigned char flg_12_eye1_TA_tex_txt[];
extern unsigned char flg_12_eye2_TA_tex_txt[];
extern unsigned char flg_12_eye3_TA_tex_txt[];
extern unsigned char flg_12_eye4_TA_tex_txt[];
extern unsigned char flg_12_eye5_TA_tex_txt[];
extern unsigned char flg_12_eye6_TA_tex_txt[];
extern unsigned char flg_12_eye7_TA_tex_txt[];
extern unsigned char flg_12_eye8_TA_tex_txt[];
extern unsigned char flg_12_mouth1_TA_tex_txt[];
extern unsigned char flg_12_mouth2_TA_tex_txt[];
extern unsigned char flg_12_mouth3_TA_tex_txt[];
extern unsigned char flg_12_mouth4_TA_tex_txt[];
extern unsigned char flg_12_mouth5_TA_tex_txt[];
extern unsigned char flg_12_mouth6_TA_tex_txt[];
extern unsigned char flg_12_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_goa_1;
extern unsigned short goa_1_pal[];
extern unsigned char goa_1_eye1_TA_tex_txt[];
extern unsigned char goa_1_eye2_TA_tex_txt[];
extern unsigned char goa_1_eye3_TA_tex_txt[];
extern unsigned char goa_1_eye4_TA_tex_txt[];
extern unsigned char goa_1_eye5_TA_tex_txt[];
extern unsigned char goa_1_eye6_TA_tex_txt[];
extern unsigned char goa_1_eye7_TA_tex_txt[];
extern unsigned char goa_1_eye8_TA_tex_txt[];
extern unsigned char goa_1_mouth1_TA_tex_txt[];
extern unsigned char goa_1_mouth2_TA_tex_txt[];
extern unsigned char goa_1_mouth3_TA_tex_txt[];
extern unsigned char goa_1_mouth4_TA_tex_txt[];
extern unsigned char goa_1_mouth5_TA_tex_txt[];
extern unsigned char goa_1_mouth6_TA_tex_txt[];
extern unsigned char goa_1_tmem_txt[];
extern unsigned short goa_2_pal[];
extern unsigned char goa_2_eye1_TA_tex_txt[];
extern unsigned char goa_2_eye2_TA_tex_txt[];
extern unsigned char goa_2_eye3_TA_tex_txt[];
extern unsigned char goa_2_eye4_TA_tex_txt[];
extern unsigned char goa_2_eye5_TA_tex_txt[];
extern unsigned char goa_2_eye6_TA_tex_txt[];
extern unsigned char goa_2_eye7_TA_tex_txt[];
extern unsigned char goa_2_eye8_TA_tex_txt[];
extern unsigned char goa_2_mouth1_TA_tex_txt[];
extern unsigned char goa_2_mouth2_TA_tex_txt[];
extern unsigned char goa_2_mouth3_TA_tex_txt[];
extern unsigned char goa_2_mouth4_TA_tex_txt[];
extern unsigned char goa_2_mouth5_TA_tex_txt[];
extern unsigned char goa_2_mouth6_TA_tex_txt[];
extern unsigned char goa_2_tmem_txt[];
extern unsigned short goa_3_pal[];
extern unsigned char goa_3_eye1_TA_tex_txt[];
extern unsigned char goa_3_eye2_TA_tex_txt[];
extern unsigned char goa_3_eye3_TA_tex_txt[];
extern unsigned char goa_3_eye4_TA_tex_txt[];
extern unsigned char goa_3_eye5_TA_tex_txt[];
extern unsigned char goa_3_eye6_TA_tex_txt[];
extern unsigned char goa_3_eye7_TA_tex_txt[];
extern unsigned char goa_3_eye8_TA_tex_txt[];
extern unsigned char goa_3_mouth1_TA_tex_txt[];
extern unsigned char goa_3_mouth2_TA_tex_txt[];
extern unsigned char goa_3_mouth3_TA_tex_txt[];
extern unsigned char goa_3_mouth4_TA_tex_txt[];
extern unsigned char goa_3_mouth5_TA_tex_txt[];
extern unsigned char goa_3_mouth6_TA_tex_txt[];
extern unsigned char goa_3_tmem_txt[];
extern unsigned short goa_4_pal[];
extern unsigned char goa_4_eye1_TA_tex_txt[];
extern unsigned char goa_4_eye2_TA_tex_txt[];
extern unsigned char goa_4_eye3_TA_tex_txt[];
extern unsigned char goa_4_eye4_TA_tex_txt[];
extern unsigned char goa_4_eye5_TA_tex_txt[];
extern unsigned char goa_4_eye6_TA_tex_txt[];
extern unsigned char goa_4_eye7_TA_tex_txt[];
extern unsigned char goa_4_eye8_TA_tex_txt[];
extern unsigned char goa_4_mouth1_TA_tex_txt[];
extern unsigned char goa_4_mouth2_TA_tex_txt[];
extern unsigned char goa_4_mouth3_TA_tex_txt[];
extern unsigned char goa_4_mouth4_TA_tex_txt[];
extern unsigned char goa_4_mouth5_TA_tex_txt[];
extern unsigned char goa_4_mouth6_TA_tex_txt[];
extern unsigned char goa_4_tmem_txt[];
extern unsigned short goa_5_pal[];
extern unsigned char goa_5_eye1_TA_tex_txt[];
extern unsigned char goa_5_eye2_TA_tex_txt[];
extern unsigned char goa_5_eye3_TA_tex_txt[];
extern unsigned char goa_5_eye4_TA_tex_txt[];
extern unsigned char goa_5_eye5_TA_tex_txt[];
extern unsigned char goa_5_eye6_TA_tex_txt[];
extern unsigned char goa_5_eye7_TA_tex_txt[];
extern unsigned char goa_5_eye8_TA_tex_txt[];
extern unsigned char goa_5_mouth1_TA_tex_txt[];
extern unsigned char goa_5_mouth2_TA_tex_txt[];
extern unsigned char goa_5_mouth3_TA_tex_txt[];
extern unsigned char goa_5_mouth4_TA_tex_txt[];
extern unsigned char goa_5_mouth5_TA_tex_txt[];
extern unsigned char goa_5_mouth6_TA_tex_txt[];
extern unsigned char goa_5_tmem_txt[];
extern unsigned short goa_6_pal[];
extern unsigned char goa_6_eye1_TA_tex_txt[];
extern unsigned char goa_6_eye2_TA_tex_txt[];
extern unsigned char goa_6_eye3_TA_tex_txt[];
extern unsigned char goa_6_eye4_TA_tex_txt[];
extern unsigned char goa_6_eye5_TA_tex_txt[];
extern unsigned char goa_6_eye6_TA_tex_txt[];
extern unsigned char goa_6_eye7_TA_tex_txt[];
extern unsigned char goa_6_eye8_TA_tex_txt[];
extern unsigned char goa_6_mouth1_TA_tex_txt[];
extern unsigned char goa_6_mouth2_TA_tex_txt[];
extern unsigned char goa_6_mouth3_TA_tex_txt[];
extern unsigned char goa_6_mouth4_TA_tex_txt[];
extern unsigned char goa_6_mouth5_TA_tex_txt[];
extern unsigned char goa_6_mouth6_TA_tex_txt[];
extern unsigned char goa_6_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_gor_1;
extern unsigned short gor_1_pal[];
extern unsigned char gor_1_eye1_TA_tex_txt[];
extern unsigned char gor_1_eye2_TA_tex_txt[];
extern unsigned char gor_1_eye3_TA_tex_txt[];
extern unsigned char gor_1_eye4_TA_tex_txt[];
extern unsigned char gor_1_eye5_TA_tex_txt[];
extern unsigned char gor_1_eye6_TA_tex_txt[];
extern unsigned char gor_1_eye7_TA_tex_txt[];
extern unsigned char gor_1_eye8_TA_tex_txt[];
extern unsigned char gor_1_mouth1_TA_tex_txt[];
extern unsigned char gor_1_mouth2_TA_tex_txt[];
extern unsigned char gor_1_mouth3_TA_tex_txt[];
extern unsigned char gor_1_mouth4_TA_tex_txt[];
extern unsigned char gor_1_mouth5_TA_tex_txt[];
extern unsigned char gor_1_mouth6_TA_tex_txt[];
extern unsigned char gor_1_tmem_txt[];
extern unsigned short gor_2_pal[];
extern unsigned char gor_2_eye1_TA_tex_txt[];
extern unsigned char gor_2_eye2_TA_tex_txt[];
extern unsigned char gor_2_eye3_TA_tex_txt[];
extern unsigned char gor_2_eye4_TA_tex_txt[];
extern unsigned char gor_2_eye5_TA_tex_txt[];
extern unsigned char gor_2_eye6_TA_tex_txt[];
extern unsigned char gor_2_eye7_TA_tex_txt[];
extern unsigned char gor_2_eye8_TA_tex_txt[];
extern unsigned char gor_2_mouth1_TA_tex_txt[];
extern unsigned char gor_2_mouth2_TA_tex_txt[];
extern unsigned char gor_2_mouth3_TA_tex_txt[];
extern unsigned char gor_2_mouth4_TA_tex_txt[];
extern unsigned char gor_2_mouth5_TA_tex_txt[];
extern unsigned char gor_2_mouth6_TA_tex_txt[];
extern unsigned char gor_2_tmem_txt[];
extern unsigned short gor_3_pal[];
extern unsigned char gor_3_eye1_TA_tex_txt[];
extern unsigned char gor_3_eye2_TA_tex_txt[];
extern unsigned char gor_3_eye3_TA_tex_txt[];
extern unsigned char gor_3_eye4_TA_tex_txt[];
extern unsigned char gor_3_eye5_TA_tex_txt[];
extern unsigned char gor_3_eye6_TA_tex_txt[];
extern unsigned char gor_3_eye7_TA_tex_txt[];
extern unsigned char gor_3_eye8_TA_tex_txt[];
extern unsigned char gor_3_mouth1_TA_tex_txt[];
extern unsigned char gor_3_mouth2_TA_tex_txt[];
extern unsigned char gor_3_mouth3_TA_tex_txt[];
extern unsigned char gor_3_mouth4_TA_tex_txt[];
extern unsigned char gor_3_mouth5_TA_tex_txt[];
extern unsigned char gor_3_mouth6_TA_tex_txt[];
extern unsigned char gor_3_tmem_txt[];
extern unsigned short gor_4_pal[];
extern unsigned char gor_4_eye1_TA_tex_txt[];
extern unsigned char gor_4_eye2_TA_tex_txt[];
extern unsigned char gor_4_eye3_TA_tex_txt[];
extern unsigned char gor_4_eye4_TA_tex_txt[];
extern unsigned char gor_4_eye5_TA_tex_txt[];
extern unsigned char gor_4_eye6_TA_tex_txt[];
extern unsigned char gor_4_eye7_TA_tex_txt[];
extern unsigned char gor_4_eye8_TA_tex_txt[];
extern unsigned char gor_4_mouth1_TA_tex_txt[];
extern unsigned char gor_4_mouth2_TA_tex_txt[];
extern unsigned char gor_4_mouth3_TA_tex_txt[];
extern unsigned char gor_4_mouth4_TA_tex_txt[];
extern unsigned char gor_4_mouth5_TA_tex_txt[];
extern unsigned char gor_4_mouth6_TA_tex_txt[];
extern unsigned char gor_4_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_hip_1;
extern unsigned short hip_1_pal[];
extern unsigned char hip_1_eye1_TA_tex_txt[];
extern unsigned char hip_1_eye2_TA_tex_txt[];
extern unsigned char hip_1_eye3_TA_tex_txt[];
extern unsigned char hip_1_eye4_TA_tex_txt[];
extern unsigned char hip_1_eye5_TA_tex_txt[];
extern unsigned char hip_1_eye6_TA_tex_txt[];
extern unsigned char hip_1_eye7_TA_tex_txt[];
extern unsigned char hip_1_eye8_TA_tex_txt[];
extern unsigned char hip_1_tmem_txt[];
extern unsigned short hip_2_pal[];
extern unsigned char hip_2_eye1_TA_tex_txt[];
extern unsigned char hip_2_eye2_TA_tex_txt[];
extern unsigned char hip_2_eye3_TA_tex_txt[];
extern unsigned char hip_2_eye4_TA_tex_txt[];
extern unsigned char hip_2_eye5_TA_tex_txt[];
extern unsigned char hip_2_eye6_TA_tex_txt[];
extern unsigned char hip_2_eye7_TA_tex_txt[];
extern unsigned char hip_2_eye8_TA_tex_txt[];
extern unsigned char hip_2_tmem_txt[];
extern unsigned short hip_3_pal[];
extern unsigned char hip_3_eye1_TA_tex_txt[];
extern unsigned char hip_3_eye2_TA_tex_txt[];
extern unsigned char hip_3_eye3_TA_tex_txt[];
extern unsigned char hip_3_eye4_TA_tex_txt[];
extern unsigned char hip_3_eye5_TA_tex_txt[];
extern unsigned char hip_3_eye6_TA_tex_txt[];
extern unsigned char hip_3_eye7_TA_tex_txt[];
extern unsigned char hip_3_eye8_TA_tex_txt[];
extern unsigned char hip_3_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_hrs_1;
extern unsigned short hrs_1_pal[];
extern unsigned char hrs_1_eye1_TA_tex_txt[];
extern unsigned char hrs_1_eye2_TA_tex_txt[];
extern unsigned char hrs_1_eye3_TA_tex_txt[];
extern unsigned char hrs_1_eye4_TA_tex_txt[];
extern unsigned char hrs_1_eye5_TA_tex_txt[];
extern unsigned char hrs_1_eye6_TA_tex_txt[];
extern unsigned char hrs_1_eye7_TA_tex_txt[];
extern unsigned char hrs_1_eye8_TA_tex_txt[];
extern unsigned char hrs_1_tmem_txt[];
extern unsigned short hrs_2_pal[];
extern unsigned char hrs_2_eye1_TA_tex_txt[];
extern unsigned char hrs_2_eye2_TA_tex_txt[];
extern unsigned char hrs_2_eye3_TA_tex_txt[];
extern unsigned char hrs_2_eye4_TA_tex_txt[];
extern unsigned char hrs_2_eye5_TA_tex_txt[];
extern unsigned char hrs_2_eye6_TA_tex_txt[];
extern unsigned char hrs_2_eye7_TA_tex_txt[];
extern unsigned char hrs_2_eye8_TA_tex_txt[];
extern unsigned char hrs_2_tmem_txt[];
extern unsigned short hrs_3_pal[];
extern unsigned char hrs_3_eye1_TA_tex_txt[];
extern unsigned char hrs_3_eye2_TA_tex_txt[];
extern unsigned char hrs_3_eye3_TA_tex_txt[];
extern unsigned char hrs_3_eye4_TA_tex_txt[];
extern unsigned char hrs_3_eye5_TA_tex_txt[];
extern unsigned char hrs_3_eye6_TA_tex_txt[];
extern unsigned char hrs_3_eye7_TA_tex_txt[];
extern unsigned char hrs_3_eye8_TA_tex_txt[];
extern unsigned char hrs_3_tmem_txt[];
extern unsigned short hrs_4_pal[];
extern unsigned char hrs_4_eye1_TA_tex_txt[];
extern unsigned char hrs_4_eye2_TA_tex_txt[];
extern unsigned char hrs_4_eye3_TA_tex_txt[];
extern unsigned char hrs_4_eye4_TA_tex_txt[];
extern unsigned char hrs_4_eye5_TA_tex_txt[];
extern unsigned char hrs_4_eye6_TA_tex_txt[];
extern unsigned char hrs_4_eye7_TA_tex_txt[];
extern unsigned char hrs_4_eye8_TA_tex_txt[];
extern unsigned char hrs_4_tmem_txt[];
extern unsigned short hrs_5_pal[];
extern unsigned char hrs_5_eye1_TA_tex_txt[];
extern unsigned char hrs_5_eye2_TA_tex_txt[];
extern unsigned char hrs_5_eye3_TA_tex_txt[];
extern unsigned char hrs_5_eye4_TA_tex_txt[];
extern unsigned char hrs_5_eye5_TA_tex_txt[];
extern unsigned char hrs_5_eye6_TA_tex_txt[];
extern unsigned char hrs_5_eye7_TA_tex_txt[];
extern unsigned char hrs_5_eye8_TA_tex_txt[];
extern unsigned char hrs_5_tmem_txt[];
extern unsigned short hrs_6_pal[];
extern unsigned char hrs_6_eye1_TA_tex_txt[];
extern unsigned char hrs_6_eye2_TA_tex_txt[];
extern unsigned char hrs_6_eye3_TA_tex_txt[];
extern unsigned char hrs_6_eye4_TA_tex_txt[];
extern unsigned char hrs_6_eye5_TA_tex_txt[];
extern unsigned char hrs_6_eye6_TA_tex_txt[];
extern unsigned char hrs_6_eye7_TA_tex_txt[];
extern unsigned char hrs_6_eye8_TA_tex_txt[];
extern unsigned char hrs_6_tmem_txt[];
extern unsigned short hrs_7_pal[];
extern unsigned char hrs_7_eye1_TA_tex_txt[];
extern unsigned char hrs_7_eye2_TA_tex_txt[];
extern unsigned char hrs_7_eye3_TA_tex_txt[];
extern unsigned char hrs_7_eye4_TA_tex_txt[];
extern unsigned char hrs_7_eye5_TA_tex_txt[];
extern unsigned char hrs_7_eye6_TA_tex_txt[];
extern unsigned char hrs_7_eye7_TA_tex_txt[];
extern unsigned char hrs_7_eye8_TA_tex_txt[];
extern unsigned char hrs_7_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_kgr_1;
extern unsigned short kgr_1_pal[];
extern unsigned char kgr_1_eye1_TA_tex_txt[];
extern unsigned char kgr_1_eye2_TA_tex_txt[];
extern unsigned char kgr_1_eye3_TA_tex_txt[];
extern unsigned char kgr_1_eye4_TA_tex_txt[];
extern unsigned char kgr_1_eye5_TA_tex_txt[];
extern unsigned char kgr_1_eye6_TA_tex_txt[];
extern unsigned char kgr_1_eye7_TA_tex_txt[];
extern unsigned char kgr_1_eye8_TA_tex_txt[];
extern unsigned char kgr_1_tmem_txt[];
extern unsigned short kgr_2_pal[];
extern unsigned char kgr_2_eye1_TA_tex_txt[];
extern unsigned char kgr_2_eye2_TA_tex_txt[];
extern unsigned char kgr_2_eye3_TA_tex_txt[];
extern unsigned char kgr_2_eye4_TA_tex_txt[];
extern unsigned char kgr_2_eye5_TA_tex_txt[];
extern unsigned char kgr_2_eye6_TA_tex_txt[];
extern unsigned char kgr_2_eye7_TA_tex_txt[];
extern unsigned char kgr_2_eye8_TA_tex_txt[];
extern unsigned char kgr_2_tmem_txt[];
extern unsigned short kgr_3_pal[];
extern unsigned char kgr_3_eye1_TA_tex_txt[];
extern unsigned char kgr_3_eye2_TA_tex_txt[];
extern unsigned char kgr_3_eye3_TA_tex_txt[];
extern unsigned char kgr_3_eye4_TA_tex_txt[];
extern unsigned char kgr_3_eye5_TA_tex_txt[];
extern unsigned char kgr_3_eye6_TA_tex_txt[];
extern unsigned char kgr_3_eye7_TA_tex_txt[];
extern unsigned char kgr_3_eye8_TA_tex_txt[];
extern unsigned char kgr_3_tmem_txt[];
extern unsigned short kgr_4_pal[];
extern unsigned char kgr_4_eye1_TA_tex_txt[];
extern unsigned char kgr_4_eye2_TA_tex_txt[];
extern unsigned char kgr_4_eye3_TA_tex_txt[];
extern unsigned char kgr_4_eye4_TA_tex_txt[];
extern unsigned char kgr_4_eye5_TA_tex_txt[];
extern unsigned char kgr_4_eye6_TA_tex_txt[];
extern unsigned char kgr_4_eye7_TA_tex_txt[];
extern unsigned char kgr_4_eye8_TA_tex_txt[];
extern unsigned char kgr_4_tmem_txt[];
extern unsigned short kgr_5_pal[];
extern unsigned char kgr_5_eye1_TA_tex_txt[];
extern unsigned char kgr_5_eye2_TA_tex_txt[];
extern unsigned char kgr_5_eye3_TA_tex_txt[];
extern unsigned char kgr_5_eye4_TA_tex_txt[];
extern unsigned char kgr_5_eye5_TA_tex_txt[];
extern unsigned char kgr_5_eye6_TA_tex_txt[];
extern unsigned char kgr_5_eye7_TA_tex_txt[];
extern unsigned char kgr_5_eye8_TA_tex_txt[];
extern unsigned char kgr_5_tmem_txt[];
extern unsigned short kgr_6_pal[];
extern unsigned char kgr_6_eye1_TA_tex_txt[];
extern unsigned char kgr_6_eye2_TA_tex_txt[];
extern unsigned char kgr_6_eye3_TA_tex_txt[];
extern unsigned char kgr_6_eye4_TA_tex_txt[];
extern unsigned char kgr_6_eye5_TA_tex_txt[];
extern unsigned char kgr_6_eye6_TA_tex_txt[];
extern unsigned char kgr_6_eye7_TA_tex_txt[];
extern unsigned char kgr_6_eye8_TA_tex_txt[];
extern unsigned char kgr_6_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_kal_1;
extern unsigned short kal_1_pal[];
extern unsigned char kal_1_eye1_TA_tex_txt[];
extern unsigned char kal_1_eye2_TA_tex_txt[];
extern unsigned char kal_1_eye3_TA_tex_txt[];
extern unsigned char kal_1_eye4_TA_tex_txt[];
extern unsigned char kal_1_eye5_TA_tex_txt[];
extern unsigned char kal_1_eye6_TA_tex_txt[];
extern unsigned char kal_1_eye7_TA_tex_txt[];
extern unsigned char kal_1_eye8_TA_tex_txt[];
extern unsigned char kal_1_mouth1_TA_tex_txt[];
extern unsigned char kal_1_mouth2_TA_tex_txt[];
extern unsigned char kal_1_mouth3_TA_tex_txt[];
extern unsigned char kal_1_mouth4_TA_tex_txt[];
extern unsigned char kal_1_mouth5_TA_tex_txt[];
extern unsigned char kal_1_mouth6_TA_tex_txt[];
extern unsigned char kal_1_tmem_txt[];
extern unsigned short kal_2_pal[];
extern unsigned char kal_2_eye1_TA_tex_txt[];
extern unsigned char kal_2_eye2_TA_tex_txt[];
extern unsigned char kal_2_eye3_TA_tex_txt[];
extern unsigned char kal_2_eye4_TA_tex_txt[];
extern unsigned char kal_2_eye5_TA_tex_txt[];
extern unsigned char kal_2_eye6_TA_tex_txt[];
extern unsigned char kal_2_eye7_TA_tex_txt[];
extern unsigned char kal_2_eye8_TA_tex_txt[];
extern unsigned char kal_2_mouth1_TA_tex_txt[];
extern unsigned char kal_2_mouth2_TA_tex_txt[];
extern unsigned char kal_2_mouth3_TA_tex_txt[];
extern unsigned char kal_2_mouth4_TA_tex_txt[];
extern unsigned char kal_2_mouth5_TA_tex_txt[];
extern unsigned char kal_2_mouth6_TA_tex_txt[];
extern unsigned char kal_2_tmem_txt[];
extern unsigned short kal_3_pal[];
extern unsigned char kal_3_eye1_TA_tex_txt[];
extern unsigned char kal_3_eye2_TA_tex_txt[];
extern unsigned char kal_3_eye3_TA_tex_txt[];
extern unsigned char kal_3_eye4_TA_tex_txt[];
extern unsigned char kal_3_eye5_TA_tex_txt[];
extern unsigned char kal_3_eye6_TA_tex_txt[];
extern unsigned char kal_3_eye7_TA_tex_txt[];
extern unsigned char kal_3_eye8_TA_tex_txt[];
extern unsigned char kal_3_mouth1_TA_tex_txt[];
extern unsigned char kal_3_mouth2_TA_tex_txt[];
extern unsigned char kal_3_mouth3_TA_tex_txt[];
extern unsigned char kal_3_mouth4_TA_tex_txt[];
extern unsigned char kal_3_mouth5_TA_tex_txt[];
extern unsigned char kal_3_mouth6_TA_tex_txt[];
extern unsigned char kal_3_tmem_txt[];
extern unsigned short kal_4_pal[];
extern unsigned char kal_4_eye1_TA_tex_txt[];
extern unsigned char kal_4_eye2_TA_tex_txt[];
extern unsigned char kal_4_eye3_TA_tex_txt[];
extern unsigned char kal_4_eye4_TA_tex_txt[];
extern unsigned char kal_4_eye5_TA_tex_txt[];
extern unsigned char kal_4_eye6_TA_tex_txt[];
extern unsigned char kal_4_eye7_TA_tex_txt[];
extern unsigned char kal_4_eye8_TA_tex_txt[];
extern unsigned char kal_4_mouth1_TA_tex_txt[];
extern unsigned char kal_4_mouth2_TA_tex_txt[];
extern unsigned char kal_4_mouth3_TA_tex_txt[];
extern unsigned char kal_4_mouth4_TA_tex_txt[];
extern unsigned char kal_4_mouth5_TA_tex_txt[];
extern unsigned char kal_4_mouth6_TA_tex_txt[];
extern unsigned char kal_4_tmem_txt[];
extern unsigned short kal_5_pal[];
extern unsigned char kal_5_eye1_TA_tex_txt[];
extern unsigned char kal_5_eye2_TA_tex_txt[];
extern unsigned char kal_5_eye3_TA_tex_txt[];
extern unsigned char kal_5_eye4_TA_tex_txt[];
extern unsigned char kal_5_eye5_TA_tex_txt[];
extern unsigned char kal_5_eye6_TA_tex_txt[];
extern unsigned char kal_5_eye7_TA_tex_txt[];
extern unsigned char kal_5_eye8_TA_tex_txt[];
extern unsigned char kal_5_mouth1_TA_tex_txt[];
extern unsigned char kal_5_mouth2_TA_tex_txt[];
extern unsigned char kal_5_mouth3_TA_tex_txt[];
extern unsigned char kal_5_mouth4_TA_tex_txt[];
extern unsigned char kal_5_mouth5_TA_tex_txt[];
extern unsigned char kal_5_mouth6_TA_tex_txt[];
extern unsigned char kal_5_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_lon_1;
extern unsigned short lon_1_pal[];
extern unsigned char lon_1_eye1_TA_tex_txt[];
extern unsigned char lon_1_eye2_TA_tex_txt[];
extern unsigned char lon_1_eye3_TA_tex_txt[];
extern unsigned char lon_1_eye4_TA_tex_txt[];
extern unsigned char lon_1_eye5_TA_tex_txt[];
extern unsigned char lon_1_eye6_TA_tex_txt[];
extern unsigned char lon_1_eye7_TA_tex_txt[];
extern unsigned char lon_1_eye8_TA_tex_txt[];
extern unsigned char lon_1_mouth1_TA_tex_txt[];
extern unsigned char lon_1_mouth2_TA_tex_txt[];
extern unsigned char lon_1_mouth3_TA_tex_txt[];
extern unsigned char lon_1_mouth4_TA_tex_txt[];
extern unsigned char lon_1_mouth5_TA_tex_txt[];
extern unsigned char lon_1_mouth6_TA_tex_txt[];
extern unsigned char lon_1_tmem_txt[];
extern unsigned short lon_2_pal[];
extern unsigned char lon_2_eye1_TA_tex_txt[];
extern unsigned char lon_2_eye2_TA_tex_txt[];
extern unsigned char lon_2_eye3_TA_tex_txt[];
extern unsigned char lon_2_eye4_TA_tex_txt[];
extern unsigned char lon_2_eye5_TA_tex_txt[];
extern unsigned char lon_2_eye6_TA_tex_txt[];
extern unsigned char lon_2_eye7_TA_tex_txt[];
extern unsigned char lon_2_eye8_TA_tex_txt[];
extern unsigned char lon_2_mouth1_TA_tex_txt[];
extern unsigned char lon_2_mouth2_TA_tex_txt[];
extern unsigned char lon_2_mouth3_TA_tex_txt[];
extern unsigned char lon_2_mouth4_TA_tex_txt[];
extern unsigned char lon_2_mouth5_TA_tex_txt[];
extern unsigned char lon_2_mouth6_TA_tex_txt[];
extern unsigned char lon_2_tmem_txt[];
extern unsigned short lon_3_pal[];
extern unsigned char lon_3_eye1_TA_tex_txt[];
extern unsigned char lon_3_eye2_TA_tex_txt[];
extern unsigned char lon_3_eye3_TA_tex_txt[];
extern unsigned char lon_3_eye4_TA_tex_txt[];
extern unsigned char lon_3_eye5_TA_tex_txt[];
extern unsigned char lon_3_eye6_TA_tex_txt[];
extern unsigned char lon_3_eye7_TA_tex_txt[];
extern unsigned char lon_3_eye8_TA_tex_txt[];
extern unsigned char lon_3_mouth1_TA_tex_txt[];
extern unsigned char lon_3_mouth2_TA_tex_txt[];
extern unsigned char lon_3_mouth3_TA_tex_txt[];
extern unsigned char lon_3_mouth4_TA_tex_txt[];
extern unsigned char lon_3_mouth5_TA_tex_txt[];
extern unsigned char lon_3_mouth6_TA_tex_txt[];
extern unsigned char lon_3_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_mus_1;
extern unsigned short mus_1_pal[];
extern unsigned char mus_1_eye1_TA_tex_txt[];
extern unsigned char mus_1_eye2_TA_tex_txt[];
extern unsigned char mus_1_eye3_TA_tex_txt[];
extern unsigned char mus_1_eye4_TA_tex_txt[];
extern unsigned char mus_1_eye5_TA_tex_txt[];
extern unsigned char mus_1_eye6_TA_tex_txt[];
extern unsigned char mus_1_eye7_TA_tex_txt[];
extern unsigned char mus_1_eye8_TA_tex_txt[];
extern unsigned char mus_1_mouth1_TA_tex_txt[];
extern unsigned char mus_1_mouth2_TA_tex_txt[];
extern unsigned char mus_1_mouth3_TA_tex_txt[];
extern unsigned char mus_1_mouth4_TA_tex_txt[];
extern unsigned char mus_1_mouth5_TA_tex_txt[];
extern unsigned char mus_1_mouth6_TA_tex_txt[];
extern unsigned char mus_1_tmem_txt[];
extern unsigned short mus_2_pal[];
extern unsigned char mus_2_eye1_TA_tex_txt[];
extern unsigned char mus_2_eye2_TA_tex_txt[];
extern unsigned char mus_2_eye3_TA_tex_txt[];
extern unsigned char mus_2_eye4_TA_tex_txt[];
extern unsigned char mus_2_eye5_TA_tex_txt[];
extern unsigned char mus_2_eye6_TA_tex_txt[];
extern unsigned char mus_2_eye7_TA_tex_txt[];
extern unsigned char mus_2_eye8_TA_tex_txt[];
extern unsigned char mus_2_mouth1_TA_tex_txt[];
extern unsigned char mus_2_mouth2_TA_tex_txt[];
extern unsigned char mus_2_mouth3_TA_tex_txt[];
extern unsigned char mus_2_mouth4_TA_tex_txt[];
extern unsigned char mus_2_mouth5_TA_tex_txt[];
extern unsigned char mus_2_mouth6_TA_tex_txt[];
extern unsigned char mus_2_tmem_txt[];
extern unsigned short mus_3_pal[];
extern unsigned char mus_3_eye1_TA_tex_txt[];
extern unsigned char mus_3_eye2_TA_tex_txt[];
extern unsigned char mus_3_eye3_TA_tex_txt[];
extern unsigned char mus_3_eye4_TA_tex_txt[];
extern unsigned char mus_3_eye5_TA_tex_txt[];
extern unsigned char mus_3_eye6_TA_tex_txt[];
extern unsigned char mus_3_eye7_TA_tex_txt[];
extern unsigned char mus_3_eye8_TA_tex_txt[];
extern unsigned char mus_3_mouth1_TA_tex_txt[];
extern unsigned char mus_3_mouth2_TA_tex_txt[];
extern unsigned char mus_3_mouth3_TA_tex_txt[];
extern unsigned char mus_3_mouth4_TA_tex_txt[];
extern unsigned char mus_3_mouth5_TA_tex_txt[];
extern unsigned char mus_3_mouth6_TA_tex_txt[];
extern unsigned char mus_3_tmem_txt[];
extern unsigned short mus_4_pal[];
extern unsigned char mus_4_eye1_TA_tex_txt[];
extern unsigned char mus_4_eye2_TA_tex_txt[];
extern unsigned char mus_4_eye3_TA_tex_txt[];
extern unsigned char mus_4_eye4_TA_tex_txt[];
extern unsigned char mus_4_eye5_TA_tex_txt[];
extern unsigned char mus_4_eye6_TA_tex_txt[];
extern unsigned char mus_4_eye7_TA_tex_txt[];
extern unsigned char mus_4_eye8_TA_tex_txt[];
extern unsigned char mus_4_mouth1_TA_tex_txt[];
extern unsigned char mus_4_mouth2_TA_tex_txt[];
extern unsigned char mus_4_mouth3_TA_tex_txt[];
extern unsigned char mus_4_mouth4_TA_tex_txt[];
extern unsigned char mus_4_mouth5_TA_tex_txt[];
extern unsigned char mus_4_mouth6_TA_tex_txt[];
extern unsigned char mus_4_tmem_txt[];
extern unsigned short mus_5_pal[];
extern unsigned char mus_5_eye1_TA_tex_txt[];
extern unsigned char mus_5_eye2_TA_tex_txt[];
extern unsigned char mus_5_eye3_TA_tex_txt[];
extern unsigned char mus_5_eye4_TA_tex_txt[];
extern unsigned char mus_5_eye5_TA_tex_txt[];
extern unsigned char mus_5_eye6_TA_tex_txt[];
extern unsigned char mus_5_eye7_TA_tex_txt[];
extern unsigned char mus_5_eye8_TA_tex_txt[];
extern unsigned char mus_5_mouth1_TA_tex_txt[];
extern unsigned char mus_5_mouth2_TA_tex_txt[];
extern unsigned char mus_5_mouth3_TA_tex_txt[];
extern unsigned char mus_5_mouth4_TA_tex_txt[];
extern unsigned char mus_5_mouth5_TA_tex_txt[];
extern unsigned char mus_5_mouth6_TA_tex_txt[];
extern unsigned char mus_5_tmem_txt[];
extern unsigned short mus_6_pal[];
extern unsigned char mus_6_eye1_TA_tex_txt[];
extern unsigned char mus_6_eye2_TA_tex_txt[];
extern unsigned char mus_6_eye3_TA_tex_txt[];
extern unsigned char mus_6_eye4_TA_tex_txt[];
extern unsigned char mus_6_eye5_TA_tex_txt[];
extern unsigned char mus_6_eye6_TA_tex_txt[];
extern unsigned char mus_6_eye7_TA_tex_txt[];
extern unsigned char mus_6_eye8_TA_tex_txt[];
extern unsigned char mus_6_mouth1_TA_tex_txt[];
extern unsigned char mus_6_mouth2_TA_tex_txt[];
extern unsigned char mus_6_mouth3_TA_tex_txt[];
extern unsigned char mus_6_mouth4_TA_tex_txt[];
extern unsigned char mus_6_mouth5_TA_tex_txt[];
extern unsigned char mus_6_mouth6_TA_tex_txt[];
extern unsigned char mus_6_tmem_txt[];
extern unsigned short mus_7_pal[];
extern unsigned char mus_7_eye1_TA_tex_txt[];
extern unsigned char mus_7_eye2_TA_tex_txt[];
extern unsigned char mus_7_eye3_TA_tex_txt[];
extern unsigned char mus_7_eye4_TA_tex_txt[];
extern unsigned char mus_7_eye5_TA_tex_txt[];
extern unsigned char mus_7_eye6_TA_tex_txt[];
extern unsigned char mus_7_eye7_TA_tex_txt[];
extern unsigned char mus_7_eye8_TA_tex_txt[];
extern unsigned char mus_7_mouth1_TA_tex_txt[];
extern unsigned char mus_7_mouth2_TA_tex_txt[];
extern unsigned char mus_7_mouth3_TA_tex_txt[];
extern unsigned char mus_7_mouth4_TA_tex_txt[];
extern unsigned char mus_7_mouth5_TA_tex_txt[];
extern unsigned char mus_7_mouth6_TA_tex_txt[];
extern unsigned char mus_7_tmem_txt[];
extern unsigned short mus_8_pal[];
extern unsigned char mus_8_eye1_TA_tex_txt[];
extern unsigned char mus_8_eye2_TA_tex_txt[];
extern unsigned char mus_8_eye3_TA_tex_txt[];
extern unsigned char mus_8_eye4_TA_tex_txt[];
extern unsigned char mus_8_eye5_TA_tex_txt[];
extern unsigned char mus_8_eye6_TA_tex_txt[];
extern unsigned char mus_8_eye7_TA_tex_txt[];
extern unsigned char mus_8_eye8_TA_tex_txt[];
extern unsigned char mus_8_mouth1_TA_tex_txt[];
extern unsigned char mus_8_mouth2_TA_tex_txt[];
extern unsigned char mus_8_mouth3_TA_tex_txt[];
extern unsigned char mus_8_mouth4_TA_tex_txt[];
extern unsigned char mus_8_mouth5_TA_tex_txt[];
extern unsigned char mus_8_mouth6_TA_tex_txt[];
extern unsigned char mus_8_tmem_txt[];
extern unsigned short mus_9_pal[];
extern unsigned char mus_9_eye1_TA_tex_txt[];
extern unsigned char mus_9_eye2_TA_tex_txt[];
extern unsigned char mus_9_eye3_TA_tex_txt[];
extern unsigned char mus_9_eye4_TA_tex_txt[];
extern unsigned char mus_9_eye5_TA_tex_txt[];
extern unsigned char mus_9_eye6_TA_tex_txt[];
extern unsigned char mus_9_eye7_TA_tex_txt[];
extern unsigned char mus_9_eye8_TA_tex_txt[];
extern unsigned char mus_9_mouth1_TA_tex_txt[];
extern unsigned char mus_9_mouth2_TA_tex_txt[];
extern unsigned char mus_9_mouth3_TA_tex_txt[];
extern unsigned char mus_9_mouth4_TA_tex_txt[];
extern unsigned char mus_9_mouth5_TA_tex_txt[];
extern unsigned char mus_9_mouth6_TA_tex_txt[];
extern unsigned char mus_9_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_oct_1;
extern unsigned short oct_1_pal[];
extern unsigned char oct_1_eye1_TA_tex_txt[];
extern unsigned char oct_1_eye2_TA_tex_txt[];
extern unsigned char oct_1_eye3_TA_tex_txt[];
extern unsigned char oct_1_eye4_TA_tex_txt[];
extern unsigned char oct_1_eye5_TA_tex_txt[];
extern unsigned char oct_1_eye6_TA_tex_txt[];
extern unsigned char oct_1_eye7_TA_tex_txt[];
extern unsigned char oct_1_eye8_TA_tex_txt[];
extern unsigned char oct_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_ost_1;
extern unsigned short ost_1_pal[];
extern unsigned char ost_1_eye1_TA_tex_txt[];
extern unsigned char ost_1_eye2_TA_tex_txt[];
extern unsigned char ost_1_eye3_TA_tex_txt[];
extern unsigned char ost_1_eye4_TA_tex_txt[];
extern unsigned char ost_1_eye5_TA_tex_txt[];
extern unsigned char ost_1_eye6_TA_tex_txt[];
extern unsigned char ost_1_eye7_TA_tex_txt[];
extern unsigned char ost_1_eye8_TA_tex_txt[];
extern unsigned char ost_1_tmem_txt[];
extern unsigned short ost_2_pal[];
extern unsigned char ost_2_eye1_TA_tex_txt[];
extern unsigned char ost_2_eye2_TA_tex_txt[];
extern unsigned char ost_2_eye3_TA_tex_txt[];
extern unsigned char ost_2_eye4_TA_tex_txt[];
extern unsigned char ost_2_eye5_TA_tex_txt[];
extern unsigned char ost_2_eye6_TA_tex_txt[];
extern unsigned char ost_2_eye7_TA_tex_txt[];
extern unsigned char ost_2_eye8_TA_tex_txt[];
extern unsigned char ost_2_tmem_txt[];
extern unsigned short ost_3_pal[];
extern unsigned char ost_3_eye1_TA_tex_txt[];
extern unsigned char ost_3_eye2_TA_tex_txt[];
extern unsigned char ost_3_eye3_TA_tex_txt[];
extern unsigned char ost_3_eye4_TA_tex_txt[];
extern unsigned char ost_3_eye5_TA_tex_txt[];
extern unsigned char ost_3_eye6_TA_tex_txt[];
extern unsigned char ost_3_eye7_TA_tex_txt[];
extern unsigned char ost_3_eye8_TA_tex_txt[];
extern unsigned char ost_3_tmem_txt[];
extern unsigned short ost_4_pal[];
extern unsigned char ost_4_eye1_TA_tex_txt[];
extern unsigned char ost_4_eye2_TA_tex_txt[];
extern unsigned char ost_4_eye3_TA_tex_txt[];
extern unsigned char ost_4_eye4_TA_tex_txt[];
extern unsigned char ost_4_eye5_TA_tex_txt[];
extern unsigned char ost_4_eye6_TA_tex_txt[];
extern unsigned char ost_4_eye7_TA_tex_txt[];
extern unsigned char ost_4_eye8_TA_tex_txt[];
extern unsigned char ost_4_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_pbr_1;
extern unsigned short pbr_1_pal[];
extern unsigned char pbr_1_eye1_TA_tex_txt[];
extern unsigned char pbr_1_eye2_TA_tex_txt[];
extern unsigned char pbr_1_eye3_TA_tex_txt[];
extern unsigned char pbr_1_eye4_TA_tex_txt[];
extern unsigned char pbr_1_eye5_TA_tex_txt[];
extern unsigned char pbr_1_eye6_TA_tex_txt[];
extern unsigned char pbr_1_eye7_TA_tex_txt[];
extern unsigned char pbr_1_eye8_TA_tex_txt[];
extern unsigned char pbr_1_tmem_txt[];
extern unsigned short pbr_2_pal[];
extern unsigned char pbr_2_eye1_TA_tex_txt[];
extern unsigned char pbr_2_eye2_TA_tex_txt[];
extern unsigned char pbr_2_eye3_TA_tex_txt[];
extern unsigned char pbr_2_eye4_TA_tex_txt[];
extern unsigned char pbr_2_eye5_TA_tex_txt[];
extern unsigned char pbr_2_eye6_TA_tex_txt[];
extern unsigned char pbr_2_eye7_TA_tex_txt[];
extern unsigned char pbr_2_eye8_TA_tex_txt[];
extern unsigned char pbr_2_tmem_txt[];
extern unsigned short pbr_3_pal[];
extern unsigned char pbr_3_eye1_TA_tex_txt[];
extern unsigned char pbr_3_eye2_TA_tex_txt[];
extern unsigned char pbr_3_eye3_TA_tex_txt[];
extern unsigned char pbr_3_eye4_TA_tex_txt[];
extern unsigned char pbr_3_eye5_TA_tex_txt[];
extern unsigned char pbr_3_eye6_TA_tex_txt[];
extern unsigned char pbr_3_eye7_TA_tex_txt[];
extern unsigned char pbr_3_eye8_TA_tex_txt[];
extern unsigned char pbr_3_tmem_txt[];
extern unsigned short pbr_4_pal[];
extern unsigned char pbr_4_eye1_TA_tex_txt[];
extern unsigned char pbr_4_eye2_TA_tex_txt[];
extern unsigned char pbr_4_eye3_TA_tex_txt[];
extern unsigned char pbr_4_eye4_TA_tex_txt[];
extern unsigned char pbr_4_eye5_TA_tex_txt[];
extern unsigned char pbr_4_eye6_TA_tex_txt[];
extern unsigned char pbr_4_eye7_TA_tex_txt[];
extern unsigned char pbr_4_eye8_TA_tex_txt[];
extern unsigned char pbr_4_tmem_txt[];
extern unsigned short pbr_5_pal[];
extern unsigned char pbr_5_eye1_TA_tex_txt[];
extern unsigned char pbr_5_eye2_TA_tex_txt[];
extern unsigned char pbr_5_eye3_TA_tex_txt[];
extern unsigned char pbr_5_eye4_TA_tex_txt[];
extern unsigned char pbr_5_eye5_TA_tex_txt[];
extern unsigned char pbr_5_eye6_TA_tex_txt[];
extern unsigned char pbr_5_eye7_TA_tex_txt[];
extern unsigned char pbr_5_eye8_TA_tex_txt[];
extern unsigned char pbr_5_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_pgn_1;
extern unsigned short pgn_1_pal[];
extern unsigned char pgn_1_eye1_TA_tex_txt[];
extern unsigned char pgn_1_eye2_TA_tex_txt[];
extern unsigned char pgn_1_eye3_TA_tex_txt[];
extern unsigned char pgn_1_eye4_TA_tex_txt[];
extern unsigned char pgn_1_eye5_TA_tex_txt[];
extern unsigned char pgn_1_eye6_TA_tex_txt[];
extern unsigned char pgn_1_eye7_TA_tex_txt[];
extern unsigned char pgn_1_eye8_TA_tex_txt[];
extern unsigned char pgn_1_tmem_txt[];
extern unsigned short pgn_2_pal[];
extern unsigned char pgn_2_eye1_TA_tex_txt[];
extern unsigned char pgn_2_eye2_TA_tex_txt[];
extern unsigned char pgn_2_eye3_TA_tex_txt[];
extern unsigned char pgn_2_eye4_TA_tex_txt[];
extern unsigned char pgn_2_eye5_TA_tex_txt[];
extern unsigned char pgn_2_eye6_TA_tex_txt[];
extern unsigned char pgn_2_eye7_TA_tex_txt[];
extern unsigned char pgn_2_eye8_TA_tex_txt[];
extern unsigned char pgn_2_tmem_txt[];
extern unsigned short pgn_3_pal[];
extern unsigned char pgn_3_eye1_TA_tex_txt[];
extern unsigned char pgn_3_eye2_TA_tex_txt[];
extern unsigned char pgn_3_eye3_TA_tex_txt[];
extern unsigned char pgn_3_eye4_TA_tex_txt[];
extern unsigned char pgn_3_eye5_TA_tex_txt[];
extern unsigned char pgn_3_eye6_TA_tex_txt[];
extern unsigned char pgn_3_eye7_TA_tex_txt[];
extern unsigned char pgn_3_eye8_TA_tex_txt[];
extern unsigned char pgn_3_tmem_txt[];
extern unsigned short pgn_4_pal[];
extern unsigned char pgn_4_eye1_TA_tex_txt[];
extern unsigned char pgn_4_eye2_TA_tex_txt[];
extern unsigned char pgn_4_eye3_TA_tex_txt[];
extern unsigned char pgn_4_eye4_TA_tex_txt[];
extern unsigned char pgn_4_eye5_TA_tex_txt[];
extern unsigned char pgn_4_eye6_TA_tex_txt[];
extern unsigned char pgn_4_eye7_TA_tex_txt[];
extern unsigned char pgn_4_eye8_TA_tex_txt[];
extern unsigned char pgn_4_tmem_txt[];
extern unsigned short pgn_5_pal[];
extern unsigned char pgn_5_eye1_TA_tex_txt[];
extern unsigned char pgn_5_eye2_TA_tex_txt[];
extern unsigned char pgn_5_eye3_TA_tex_txt[];
extern unsigned char pgn_5_eye4_TA_tex_txt[];
extern unsigned char pgn_5_eye5_TA_tex_txt[];
extern unsigned char pgn_5_eye6_TA_tex_txt[];
extern unsigned char pgn_5_eye7_TA_tex_txt[];
extern unsigned char pgn_5_eye8_TA_tex_txt[];
extern unsigned char pgn_5_tmem_txt[];
extern unsigned short pgn_6_pal[];
extern unsigned char pgn_6_eye1_TA_tex_txt[];
extern unsigned char pgn_6_eye2_TA_tex_txt[];
extern unsigned char pgn_6_eye3_TA_tex_txt[];
extern unsigned char pgn_6_eye4_TA_tex_txt[];
extern unsigned char pgn_6_eye5_TA_tex_txt[];
extern unsigned char pgn_6_eye6_TA_tex_txt[];
extern unsigned char pgn_6_eye7_TA_tex_txt[];
extern unsigned char pgn_6_eye8_TA_tex_txt[];
extern unsigned char pgn_6_tmem_txt[];
extern unsigned short pgn_7_pal[];
extern unsigned char pgn_7_eye1_TA_tex_txt[];
extern unsigned char pgn_7_eye2_TA_tex_txt[];
extern unsigned char pgn_7_eye3_TA_tex_txt[];
extern unsigned char pgn_7_eye4_TA_tex_txt[];
extern unsigned char pgn_7_eye5_TA_tex_txt[];
extern unsigned char pgn_7_eye6_TA_tex_txt[];
extern unsigned char pgn_7_eye7_TA_tex_txt[];
extern unsigned char pgn_7_eye8_TA_tex_txt[];
extern unsigned char pgn_7_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_pig_1;
extern unsigned short pig_1_pal[];
extern unsigned char pig_1_eye1_TA_tex_txt[];
extern unsigned char pig_1_eye2_TA_tex_txt[];
extern unsigned char pig_1_eye3_TA_tex_txt[];
extern unsigned char pig_1_eye4_TA_tex_txt[];
extern unsigned char pig_1_eye5_TA_tex_txt[];
extern unsigned char pig_1_eye6_TA_tex_txt[];
extern unsigned char pig_1_eye7_TA_tex_txt[];
extern unsigned char pig_1_eye8_TA_tex_txt[];
extern unsigned char pig_1_mouth1_TA_tex_txt[];
extern unsigned char pig_1_mouth2_TA_tex_txt[];
extern unsigned char pig_1_mouth3_TA_tex_txt[];
extern unsigned char pig_1_mouth4_TA_tex_txt[];
extern unsigned char pig_1_mouth5_TA_tex_txt[];
extern unsigned char pig_1_mouth6_TA_tex_txt[];
extern unsigned char pig_1_tmem_txt[];
extern unsigned short pig_2_pal[];
extern unsigned char pig_2_eye1_TA_tex_txt[];
extern unsigned char pig_2_eye2_TA_tex_txt[];
extern unsigned char pig_2_eye3_TA_tex_txt[];
extern unsigned char pig_2_eye4_TA_tex_txt[];
extern unsigned char pig_2_eye5_TA_tex_txt[];
extern unsigned char pig_2_eye6_TA_tex_txt[];
extern unsigned char pig_2_eye7_TA_tex_txt[];
extern unsigned char pig_2_eye8_TA_tex_txt[];
extern unsigned char pig_2_mouth1_TA_tex_txt[];
extern unsigned char pig_2_mouth2_TA_tex_txt[];
extern unsigned char pig_2_mouth3_TA_tex_txt[];
extern unsigned char pig_2_mouth4_TA_tex_txt[];
extern unsigned char pig_2_mouth5_TA_tex_txt[];
extern unsigned char pig_2_mouth6_TA_tex_txt[];
extern unsigned char pig_2_tmem_txt[];
extern unsigned short pig_3_pal[];
extern unsigned char pig_3_eye1_TA_tex_txt[];
extern unsigned char pig_3_eye2_TA_tex_txt[];
extern unsigned char pig_3_eye3_TA_tex_txt[];
extern unsigned char pig_3_eye4_TA_tex_txt[];
extern unsigned char pig_3_eye5_TA_tex_txt[];
extern unsigned char pig_3_eye6_TA_tex_txt[];
extern unsigned char pig_3_eye7_TA_tex_txt[];
extern unsigned char pig_3_eye8_TA_tex_txt[];
extern unsigned char pig_3_mouth1_TA_tex_txt[];
extern unsigned char pig_3_mouth2_TA_tex_txt[];
extern unsigned char pig_3_mouth3_TA_tex_txt[];
extern unsigned char pig_3_mouth4_TA_tex_txt[];
extern unsigned char pig_3_mouth5_TA_tex_txt[];
extern unsigned char pig_3_mouth6_TA_tex_txt[];
extern unsigned char pig_3_tmem_txt[];
extern unsigned short pig_4_pal[];
extern unsigned char pig_4_eye1_TA_tex_txt[];
extern unsigned char pig_4_eye2_TA_tex_txt[];
extern unsigned char pig_4_eye3_TA_tex_txt[];
extern unsigned char pig_4_eye4_TA_tex_txt[];
extern unsigned char pig_4_eye5_TA_tex_txt[];
extern unsigned char pig_4_eye6_TA_tex_txt[];
extern unsigned char pig_4_eye7_TA_tex_txt[];
extern unsigned char pig_4_eye8_TA_tex_txt[];
extern unsigned char pig_4_mouth1_TA_tex_txt[];
extern unsigned char pig_4_mouth2_TA_tex_txt[];
extern unsigned char pig_4_mouth3_TA_tex_txt[];
extern unsigned char pig_4_mouth4_TA_tex_txt[];
extern unsigned char pig_4_mouth5_TA_tex_txt[];
extern unsigned char pig_4_mouth6_TA_tex_txt[];
extern unsigned char pig_4_tmem_txt[];
extern unsigned short pig_5_pal[];
extern unsigned char pig_5_eye1_TA_tex_txt[];
extern unsigned char pig_5_eye2_TA_tex_txt[];
extern unsigned char pig_5_eye3_TA_tex_txt[];
extern unsigned char pig_5_eye4_TA_tex_txt[];
extern unsigned char pig_5_eye5_TA_tex_txt[];
extern unsigned char pig_5_eye6_TA_tex_txt[];
extern unsigned char pig_5_eye7_TA_tex_txt[];
extern unsigned char pig_5_eye8_TA_tex_txt[];
extern unsigned char pig_5_mouth1_TA_tex_txt[];
extern unsigned char pig_5_mouth2_TA_tex_txt[];
extern unsigned char pig_5_mouth3_TA_tex_txt[];
extern unsigned char pig_5_mouth4_TA_tex_txt[];
extern unsigned char pig_5_mouth5_TA_tex_txt[];
extern unsigned char pig_5_mouth6_TA_tex_txt[];
extern unsigned char pig_5_tmem_txt[];
extern unsigned short pig_6_pal[];
extern unsigned char pig_6_eye1_TA_tex_txt[];
extern unsigned char pig_6_eye2_TA_tex_txt[];
extern unsigned char pig_6_eye3_TA_tex_txt[];
extern unsigned char pig_6_eye4_TA_tex_txt[];
extern unsigned char pig_6_eye5_TA_tex_txt[];
extern unsigned char pig_6_eye6_TA_tex_txt[];
extern unsigned char pig_6_eye7_TA_tex_txt[];
extern unsigned char pig_6_eye8_TA_tex_txt[];
extern unsigned char pig_6_mouth1_TA_tex_txt[];
extern unsigned char pig_6_mouth2_TA_tex_txt[];
extern unsigned char pig_6_mouth3_TA_tex_txt[];
extern unsigned char pig_6_mouth4_TA_tex_txt[];
extern unsigned char pig_6_mouth5_TA_tex_txt[];
extern unsigned char pig_6_mouth6_TA_tex_txt[];
extern unsigned char pig_6_tmem_txt[];
extern unsigned short pig_7_pal[];
extern unsigned char pig_7_eye1_TA_tex_txt[];
extern unsigned char pig_7_eye2_TA_tex_txt[];
extern unsigned char pig_7_eye3_TA_tex_txt[];
extern unsigned char pig_7_eye4_TA_tex_txt[];
extern unsigned char pig_7_eye5_TA_tex_txt[];
extern unsigned char pig_7_eye6_TA_tex_txt[];
extern unsigned char pig_7_eye7_TA_tex_txt[];
extern unsigned char pig_7_eye8_TA_tex_txt[];
extern unsigned char pig_7_mouth1_TA_tex_txt[];
extern unsigned char pig_7_mouth2_TA_tex_txt[];
extern unsigned char pig_7_mouth3_TA_tex_txt[];
extern unsigned char pig_7_mouth4_TA_tex_txt[];
extern unsigned char pig_7_mouth5_TA_tex_txt[];
extern unsigned char pig_7_mouth6_TA_tex_txt[];
extern unsigned char pig_7_tmem_txt[];
extern unsigned short pig_8_pal[];
extern unsigned char pig_8_eye1_TA_tex_txt[];
extern unsigned char pig_8_eye2_TA_tex_txt[];
extern unsigned char pig_8_eye3_TA_tex_txt[];
extern unsigned char pig_8_eye4_TA_tex_txt[];
extern unsigned char pig_8_eye5_TA_tex_txt[];
extern unsigned char pig_8_eye6_TA_tex_txt[];
extern unsigned char pig_8_eye7_TA_tex_txt[];
extern unsigned char pig_8_eye8_TA_tex_txt[];
extern unsigned char pig_8_mouth1_TA_tex_txt[];
extern unsigned char pig_8_mouth2_TA_tex_txt[];
extern unsigned char pig_8_mouth3_TA_tex_txt[];
extern unsigned char pig_8_mouth4_TA_tex_txt[];
extern unsigned char pig_8_mouth5_TA_tex_txt[];
extern unsigned char pig_8_mouth6_TA_tex_txt[];
extern unsigned char pig_8_tmem_txt[];
extern unsigned short pig_9_pal[];
extern unsigned char pig_9_eye1_TA_tex_txt[];
extern unsigned char pig_9_eye2_TA_tex_txt[];
extern unsigned char pig_9_eye3_TA_tex_txt[];
extern unsigned char pig_9_eye4_TA_tex_txt[];
extern unsigned char pig_9_eye5_TA_tex_txt[];
extern unsigned char pig_9_eye6_TA_tex_txt[];
extern unsigned char pig_9_eye7_TA_tex_txt[];
extern unsigned char pig_9_eye8_TA_tex_txt[];
extern unsigned char pig_9_mouth1_TA_tex_txt[];
extern unsigned char pig_9_mouth2_TA_tex_txt[];
extern unsigned char pig_9_mouth3_TA_tex_txt[];
extern unsigned char pig_9_mouth4_TA_tex_txt[];
extern unsigned char pig_9_mouth5_TA_tex_txt[];
extern unsigned char pig_9_mouth6_TA_tex_txt[];
extern unsigned char pig_9_tmem_txt[];
extern unsigned short pig_10_pal[];
extern unsigned char pig_10_eye1_TA_tex_txt[];
extern unsigned char pig_10_eye2_TA_tex_txt[];
extern unsigned char pig_10_eye3_TA_tex_txt[];
extern unsigned char pig_10_eye4_TA_tex_txt[];
extern unsigned char pig_10_eye5_TA_tex_txt[];
extern unsigned char pig_10_eye6_TA_tex_txt[];
extern unsigned char pig_10_eye7_TA_tex_txt[];
extern unsigned char pig_10_eye8_TA_tex_txt[];
extern unsigned char pig_10_mouth1_TA_tex_txt[];
extern unsigned char pig_10_mouth2_TA_tex_txt[];
extern unsigned char pig_10_mouth3_TA_tex_txt[];
extern unsigned char pig_10_mouth4_TA_tex_txt[];
extern unsigned char pig_10_mouth5_TA_tex_txt[];
extern unsigned char pig_10_mouth6_TA_tex_txt[];
extern unsigned char pig_10_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_rbt_1;
extern unsigned short rbt_1_pal[];
extern unsigned char rbt_1_eye1_TA_tex_txt[];
extern unsigned char rbt_1_eye2_TA_tex_txt[];
extern unsigned char rbt_1_eye3_TA_tex_txt[];
extern unsigned char rbt_1_eye4_TA_tex_txt[];
extern unsigned char rbt_1_eye5_TA_tex_txt[];
extern unsigned char rbt_1_eye6_TA_tex_txt[];
extern unsigned char rbt_1_eye7_TA_tex_txt[];
extern unsigned char rbt_1_eye8_TA_tex_txt[];
extern unsigned char rbt_1_mouth1_TA_tex_txt[];
extern unsigned char rbt_1_mouth2_TA_tex_txt[];
extern unsigned char rbt_1_mouth3_TA_tex_txt[];
extern unsigned char rbt_1_mouth4_TA_tex_txt[];
extern unsigned char rbt_1_mouth5_TA_tex_txt[];
extern unsigned char rbt_1_mouth6_TA_tex_txt[];
extern unsigned char rbt_1_tmem_txt[];
extern unsigned short rbt_2_pal[];
extern unsigned char rbt_2_eye1_TA_tex_txt[];
extern unsigned char rbt_2_eye2_TA_tex_txt[];
extern unsigned char rbt_2_eye3_TA_tex_txt[];
extern unsigned char rbt_2_eye4_TA_tex_txt[];
extern unsigned char rbt_2_eye5_TA_tex_txt[];
extern unsigned char rbt_2_eye6_TA_tex_txt[];
extern unsigned char rbt_2_eye7_TA_tex_txt[];
extern unsigned char rbt_2_eye8_TA_tex_txt[];
extern unsigned char rbt_2_mouth1_TA_tex_txt[];
extern unsigned char rbt_2_mouth2_TA_tex_txt[];
extern unsigned char rbt_2_mouth3_TA_tex_txt[];
extern unsigned char rbt_2_mouth4_TA_tex_txt[];
extern unsigned char rbt_2_mouth5_TA_tex_txt[];
extern unsigned char rbt_2_mouth6_TA_tex_txt[];
extern unsigned char rbt_2_tmem_txt[];
extern unsigned short rbt_3_pal[];
extern unsigned char rbt_3_eye1_TA_tex_txt[];
extern unsigned char rbt_3_eye2_TA_tex_txt[];
extern unsigned char rbt_3_eye3_TA_tex_txt[];
extern unsigned char rbt_3_eye4_TA_tex_txt[];
extern unsigned char rbt_3_eye5_TA_tex_txt[];
extern unsigned char rbt_3_eye6_TA_tex_txt[];
extern unsigned char rbt_3_eye7_TA_tex_txt[];
extern unsigned char rbt_3_eye8_TA_tex_txt[];
extern unsigned char rbt_3_mouth1_TA_tex_txt[];
extern unsigned char rbt_3_mouth2_TA_tex_txt[];
extern unsigned char rbt_3_mouth3_TA_tex_txt[];
extern unsigned char rbt_3_mouth4_TA_tex_txt[];
extern unsigned char rbt_3_mouth5_TA_tex_txt[];
extern unsigned char rbt_3_mouth6_TA_tex_txt[];
extern unsigned char rbt_3_tmem_txt[];
extern unsigned short rbt_4_pal[];
extern unsigned char rbt_4_eye1_TA_tex_txt[];
extern unsigned char rbt_4_eye2_TA_tex_txt[];
extern unsigned char rbt_4_eye3_TA_tex_txt[];
extern unsigned char rbt_4_eye4_TA_tex_txt[];
extern unsigned char rbt_4_eye5_TA_tex_txt[];
extern unsigned char rbt_4_eye6_TA_tex_txt[];
extern unsigned char rbt_4_eye7_TA_tex_txt[];
extern unsigned char rbt_4_eye8_TA_tex_txt[];
extern unsigned char rbt_4_mouth1_TA_tex_txt[];
extern unsigned char rbt_4_mouth2_TA_tex_txt[];
extern unsigned char rbt_4_mouth3_TA_tex_txt[];
extern unsigned char rbt_4_mouth4_TA_tex_txt[];
extern unsigned char rbt_4_mouth5_TA_tex_txt[];
extern unsigned char rbt_4_mouth6_TA_tex_txt[];
extern unsigned char rbt_4_tmem_txt[];
extern unsigned short rbt_5_pal[];
extern unsigned char rbt_5_eye1_TA_tex_txt[];
extern unsigned char rbt_5_eye2_TA_tex_txt[];
extern unsigned char rbt_5_eye3_TA_tex_txt[];
extern unsigned char rbt_5_eye4_TA_tex_txt[];
extern unsigned char rbt_5_eye5_TA_tex_txt[];
extern unsigned char rbt_5_eye6_TA_tex_txt[];
extern unsigned char rbt_5_eye7_TA_tex_txt[];
extern unsigned char rbt_5_eye8_TA_tex_txt[];
extern unsigned char rbt_5_mouth1_TA_tex_txt[];
extern unsigned char rbt_5_mouth2_TA_tex_txt[];
extern unsigned char rbt_5_mouth3_TA_tex_txt[];
extern unsigned char rbt_5_mouth4_TA_tex_txt[];
extern unsigned char rbt_5_mouth5_TA_tex_txt[];
extern unsigned char rbt_5_mouth6_TA_tex_txt[];
extern unsigned char rbt_5_tmem_txt[];
extern unsigned short rbt_6_pal[];
extern unsigned char rbt_6_eye1_TA_tex_txt[];
extern unsigned char rbt_6_eye2_TA_tex_txt[];
extern unsigned char rbt_6_eye3_TA_tex_txt[];
extern unsigned char rbt_6_eye4_TA_tex_txt[];
extern unsigned char rbt_6_eye5_TA_tex_txt[];
extern unsigned char rbt_6_eye6_TA_tex_txt[];
extern unsigned char rbt_6_eye7_TA_tex_txt[];
extern unsigned char rbt_6_eye8_TA_tex_txt[];
extern unsigned char rbt_6_mouth1_TA_tex_txt[];
extern unsigned char rbt_6_mouth2_TA_tex_txt[];
extern unsigned char rbt_6_mouth3_TA_tex_txt[];
extern unsigned char rbt_6_mouth4_TA_tex_txt[];
extern unsigned char rbt_6_mouth5_TA_tex_txt[];
extern unsigned char rbt_6_mouth6_TA_tex_txt[];
extern unsigned char rbt_6_tmem_txt[];
extern unsigned short rbt_7_pal[];
extern unsigned char rbt_7_eye1_TA_tex_txt[];
extern unsigned char rbt_7_eye2_TA_tex_txt[];
extern unsigned char rbt_7_eye3_TA_tex_txt[];
extern unsigned char rbt_7_eye4_TA_tex_txt[];
extern unsigned char rbt_7_eye5_TA_tex_txt[];
extern unsigned char rbt_7_eye6_TA_tex_txt[];
extern unsigned char rbt_7_eye7_TA_tex_txt[];
extern unsigned char rbt_7_eye8_TA_tex_txt[];
extern unsigned char rbt_7_mouth1_TA_tex_txt[];
extern unsigned char rbt_7_mouth2_TA_tex_txt[];
extern unsigned char rbt_7_mouth3_TA_tex_txt[];
extern unsigned char rbt_7_mouth4_TA_tex_txt[];
extern unsigned char rbt_7_mouth5_TA_tex_txt[];
extern unsigned char rbt_7_mouth6_TA_tex_txt[];
extern unsigned char rbt_7_tmem_txt[];
extern unsigned short rbt_8_pal[];
extern unsigned char rbt_8_eye1_TA_tex_txt[];
extern unsigned char rbt_8_eye2_TA_tex_txt[];
extern unsigned char rbt_8_eye3_TA_tex_txt[];
extern unsigned char rbt_8_eye4_TA_tex_txt[];
extern unsigned char rbt_8_eye5_TA_tex_txt[];
extern unsigned char rbt_8_eye6_TA_tex_txt[];
extern unsigned char rbt_8_eye7_TA_tex_txt[];
extern unsigned char rbt_8_eye8_TA_tex_txt[];
extern unsigned char rbt_8_mouth1_TA_tex_txt[];
extern unsigned char rbt_8_mouth2_TA_tex_txt[];
extern unsigned char rbt_8_mouth3_TA_tex_txt[];
extern unsigned char rbt_8_mouth4_TA_tex_txt[];
extern unsigned char rbt_8_mouth5_TA_tex_txt[];
extern unsigned char rbt_8_mouth6_TA_tex_txt[];
extern unsigned char rbt_8_tmem_txt[];
extern unsigned short rbt_9_pal[];
extern unsigned char rbt_9_eye1_TA_tex_txt[];
extern unsigned char rbt_9_eye2_TA_tex_txt[];
extern unsigned char rbt_9_eye3_TA_tex_txt[];
extern unsigned char rbt_9_eye4_TA_tex_txt[];
extern unsigned char rbt_9_eye5_TA_tex_txt[];
extern unsigned char rbt_9_eye6_TA_tex_txt[];
extern unsigned char rbt_9_eye7_TA_tex_txt[];
extern unsigned char rbt_9_eye8_TA_tex_txt[];
extern unsigned char rbt_9_mouth1_TA_tex_txt[];
extern unsigned char rbt_9_mouth2_TA_tex_txt[];
extern unsigned char rbt_9_mouth3_TA_tex_txt[];
extern unsigned char rbt_9_mouth4_TA_tex_txt[];
extern unsigned char rbt_9_mouth5_TA_tex_txt[];
extern unsigned char rbt_9_mouth6_TA_tex_txt[];
extern unsigned char rbt_9_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_rhn_1;
extern unsigned short rhn_1_pal[];
extern unsigned char rhn_1_eye1_TA_tex_txt[];
extern unsigned char rhn_1_eye2_TA_tex_txt[];
extern unsigned char rhn_1_eye3_TA_tex_txt[];
extern unsigned char rhn_1_eye4_TA_tex_txt[];
extern unsigned char rhn_1_eye5_TA_tex_txt[];
extern unsigned char rhn_1_eye6_TA_tex_txt[];
extern unsigned char rhn_1_eye7_TA_tex_txt[];
extern unsigned char rhn_1_eye8_TA_tex_txt[];
extern unsigned char rhn_1_mouth1_TA_tex_txt[];
extern unsigned char rhn_1_mouth2_TA_tex_txt[];
extern unsigned char rhn_1_mouth3_TA_tex_txt[];
extern unsigned char rhn_1_mouth4_TA_tex_txt[];
extern unsigned char rhn_1_mouth5_TA_tex_txt[];
extern unsigned char rhn_1_mouth6_TA_tex_txt[];
extern unsigned char rhn_1_tmem_txt[];
extern unsigned short rhn_2_pal[];
extern unsigned char rhn_2_eye1_TA_tex_txt[];
extern unsigned char rhn_2_eye2_TA_tex_txt[];
extern unsigned char rhn_2_eye3_TA_tex_txt[];
extern unsigned char rhn_2_eye4_TA_tex_txt[];
extern unsigned char rhn_2_eye5_TA_tex_txt[];
extern unsigned char rhn_2_eye6_TA_tex_txt[];
extern unsigned char rhn_2_eye7_TA_tex_txt[];
extern unsigned char rhn_2_eye8_TA_tex_txt[];
extern unsigned char rhn_2_mouth1_TA_tex_txt[];
extern unsigned char rhn_2_mouth2_TA_tex_txt[];
extern unsigned char rhn_2_mouth3_TA_tex_txt[];
extern unsigned char rhn_2_mouth4_TA_tex_txt[];
extern unsigned char rhn_2_mouth5_TA_tex_txt[];
extern unsigned char rhn_2_mouth6_TA_tex_txt[];
extern unsigned char rhn_2_tmem_txt[];
extern unsigned short rhn_3_pal[];
extern unsigned char rhn_3_eye1_TA_tex_txt[];
extern unsigned char rhn_3_eye2_TA_tex_txt[];
extern unsigned char rhn_3_eye3_TA_tex_txt[];
extern unsigned char rhn_3_eye4_TA_tex_txt[];
extern unsigned char rhn_3_eye5_TA_tex_txt[];
extern unsigned char rhn_3_eye6_TA_tex_txt[];
extern unsigned char rhn_3_eye7_TA_tex_txt[];
extern unsigned char rhn_3_eye8_TA_tex_txt[];
extern unsigned char rhn_3_mouth1_TA_tex_txt[];
extern unsigned char rhn_3_mouth2_TA_tex_txt[];
extern unsigned char rhn_3_mouth3_TA_tex_txt[];
extern unsigned char rhn_3_mouth4_TA_tex_txt[];
extern unsigned char rhn_3_mouth5_TA_tex_txt[];
extern unsigned char rhn_3_mouth6_TA_tex_txt[];
extern unsigned char rhn_3_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_shp_1;
extern unsigned short shp_1_pal[];
extern unsigned char shp_1_eye1_TA_tex_txt[];
extern unsigned char shp_1_eye2_TA_tex_txt[];
extern unsigned char shp_1_eye3_TA_tex_txt[];
extern unsigned char shp_1_eye4_TA_tex_txt[];
extern unsigned char shp_1_eye5_TA_tex_txt[];
extern unsigned char shp_1_eye6_TA_tex_txt[];
extern unsigned char shp_1_eye7_TA_tex_txt[];
extern unsigned char shp_1_eye8_TA_tex_txt[];
extern unsigned char shp_1_mouth1_TA_tex_txt[];
extern unsigned char shp_1_mouth2_TA_tex_txt[];
extern unsigned char shp_1_mouth3_TA_tex_txt[];
extern unsigned char shp_1_mouth4_TA_tex_txt[];
extern unsigned char shp_1_mouth5_TA_tex_txt[];
extern unsigned char shp_1_mouth6_TA_tex_txt[];
extern unsigned char shp_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_squ_1;
extern unsigned short squ_1_pal[];
extern unsigned char squ_1_eye1_TA_tex_txt[];
extern unsigned char squ_1_eye2_TA_tex_txt[];
extern unsigned char squ_1_eye3_TA_tex_txt[];
extern unsigned char squ_1_eye4_TA_tex_txt[];
extern unsigned char squ_1_eye5_TA_tex_txt[];
extern unsigned char squ_1_eye6_TA_tex_txt[];
extern unsigned char squ_1_eye7_TA_tex_txt[];
extern unsigned char squ_1_eye8_TA_tex_txt[];
extern unsigned char squ_1_mouth1_TA_tex_txt[];
extern unsigned char squ_1_mouth2_TA_tex_txt[];
extern unsigned char squ_1_mouth3_TA_tex_txt[];
extern unsigned char squ_1_mouth4_TA_tex_txt[];
extern unsigned char squ_1_mouth5_TA_tex_txt[];
extern unsigned char squ_1_mouth6_TA_tex_txt[];
extern unsigned char squ_1_tmem_txt[];
extern unsigned short squ_2_pal[];
extern unsigned char squ_2_eye1_TA_tex_txt[];
extern unsigned char squ_2_eye2_TA_tex_txt[];
extern unsigned char squ_2_eye3_TA_tex_txt[];
extern unsigned char squ_2_eye4_TA_tex_txt[];
extern unsigned char squ_2_eye5_TA_tex_txt[];
extern unsigned char squ_2_eye6_TA_tex_txt[];
extern unsigned char squ_2_eye7_TA_tex_txt[];
extern unsigned char squ_2_eye8_TA_tex_txt[];
extern unsigned char squ_2_mouth1_TA_tex_txt[];
extern unsigned char squ_2_mouth2_TA_tex_txt[];
extern unsigned char squ_2_mouth3_TA_tex_txt[];
extern unsigned char squ_2_mouth4_TA_tex_txt[];
extern unsigned char squ_2_mouth5_TA_tex_txt[];
extern unsigned char squ_2_mouth6_TA_tex_txt[];
extern unsigned char squ_2_tmem_txt[];
extern unsigned short squ_3_pal[];
extern unsigned char squ_3_eye1_TA_tex_txt[];
extern unsigned char squ_3_eye2_TA_tex_txt[];
extern unsigned char squ_3_eye3_TA_tex_txt[];
extern unsigned char squ_3_eye4_TA_tex_txt[];
extern unsigned char squ_3_eye5_TA_tex_txt[];
extern unsigned char squ_3_eye6_TA_tex_txt[];
extern unsigned char squ_3_eye7_TA_tex_txt[];
extern unsigned char squ_3_eye8_TA_tex_txt[];
extern unsigned char squ_3_mouth1_TA_tex_txt[];
extern unsigned char squ_3_mouth2_TA_tex_txt[];
extern unsigned char squ_3_mouth3_TA_tex_txt[];
extern unsigned char squ_3_mouth4_TA_tex_txt[];
extern unsigned char squ_3_mouth5_TA_tex_txt[];
extern unsigned char squ_3_mouth6_TA_tex_txt[];
extern unsigned char squ_3_tmem_txt[];
extern unsigned short squ_4_pal[];
extern unsigned char squ_4_eye1_TA_tex_txt[];
extern unsigned char squ_4_eye2_TA_tex_txt[];
extern unsigned char squ_4_eye3_TA_tex_txt[];
extern unsigned char squ_4_eye4_TA_tex_txt[];
extern unsigned char squ_4_eye5_TA_tex_txt[];
extern unsigned char squ_4_eye6_TA_tex_txt[];
extern unsigned char squ_4_eye7_TA_tex_txt[];
extern unsigned char squ_4_eye8_TA_tex_txt[];
extern unsigned char squ_4_mouth1_TA_tex_txt[];
extern unsigned char squ_4_mouth2_TA_tex_txt[];
extern unsigned char squ_4_mouth3_TA_tex_txt[];
extern unsigned char squ_4_mouth4_TA_tex_txt[];
extern unsigned char squ_4_mouth5_TA_tex_txt[];
extern unsigned char squ_4_mouth6_TA_tex_txt[];
extern unsigned char squ_4_tmem_txt[];
extern unsigned short squ_5_pal[];
extern unsigned char squ_5_eye1_TA_tex_txt[];
extern unsigned char squ_5_eye2_TA_tex_txt[];
extern unsigned char squ_5_eye3_TA_tex_txt[];
extern unsigned char squ_5_eye4_TA_tex_txt[];
extern unsigned char squ_5_eye5_TA_tex_txt[];
extern unsigned char squ_5_eye6_TA_tex_txt[];
extern unsigned char squ_5_eye7_TA_tex_txt[];
extern unsigned char squ_5_eye8_TA_tex_txt[];
extern unsigned char squ_5_mouth1_TA_tex_txt[];
extern unsigned char squ_5_mouth2_TA_tex_txt[];
extern unsigned char squ_5_mouth3_TA_tex_txt[];
extern unsigned char squ_5_mouth4_TA_tex_txt[];
extern unsigned char squ_5_mouth5_TA_tex_txt[];
extern unsigned char squ_5_mouth6_TA_tex_txt[];
extern unsigned char squ_5_tmem_txt[];
extern unsigned short squ_6_pal[];
extern unsigned char squ_6_eye1_TA_tex_txt[];
extern unsigned char squ_6_eye2_TA_tex_txt[];
extern unsigned char squ_6_eye3_TA_tex_txt[];
extern unsigned char squ_6_eye4_TA_tex_txt[];
extern unsigned char squ_6_eye5_TA_tex_txt[];
extern unsigned char squ_6_eye6_TA_tex_txt[];
extern unsigned char squ_6_eye7_TA_tex_txt[];
extern unsigned char squ_6_eye8_TA_tex_txt[];
extern unsigned char squ_6_mouth1_TA_tex_txt[];
extern unsigned char squ_6_mouth2_TA_tex_txt[];
extern unsigned char squ_6_mouth3_TA_tex_txt[];
extern unsigned char squ_6_mouth4_TA_tex_txt[];
extern unsigned char squ_6_mouth5_TA_tex_txt[];
extern unsigned char squ_6_mouth6_TA_tex_txt[];
extern unsigned char squ_6_tmem_txt[];
extern unsigned short squ_7_pal[];
extern unsigned char squ_7_eye1_TA_tex_txt[];
extern unsigned char squ_7_eye2_TA_tex_txt[];
extern unsigned char squ_7_eye3_TA_tex_txt[];
extern unsigned char squ_7_eye4_TA_tex_txt[];
extern unsigned char squ_7_eye5_TA_tex_txt[];
extern unsigned char squ_7_eye6_TA_tex_txt[];
extern unsigned char squ_7_eye7_TA_tex_txt[];
extern unsigned char squ_7_eye8_TA_tex_txt[];
extern unsigned char squ_7_mouth1_TA_tex_txt[];
extern unsigned char squ_7_mouth2_TA_tex_txt[];
extern unsigned char squ_7_mouth3_TA_tex_txt[];
extern unsigned char squ_7_mouth4_TA_tex_txt[];
extern unsigned char squ_7_mouth5_TA_tex_txt[];
extern unsigned char squ_7_mouth6_TA_tex_txt[];
extern unsigned char squ_7_tmem_txt[];
extern unsigned short squ_8_pal[];
extern unsigned char squ_8_eye1_TA_tex_txt[];
extern unsigned char squ_8_eye2_TA_tex_txt[];
extern unsigned char squ_8_eye3_TA_tex_txt[];
extern unsigned char squ_8_eye4_TA_tex_txt[];
extern unsigned char squ_8_eye5_TA_tex_txt[];
extern unsigned char squ_8_eye6_TA_tex_txt[];
extern unsigned char squ_8_eye7_TA_tex_txt[];
extern unsigned char squ_8_eye8_TA_tex_txt[];
extern unsigned char squ_8_mouth1_TA_tex_txt[];
extern unsigned char squ_8_mouth2_TA_tex_txt[];
extern unsigned char squ_8_mouth3_TA_tex_txt[];
extern unsigned char squ_8_mouth4_TA_tex_txt[];
extern unsigned char squ_8_mouth5_TA_tex_txt[];
extern unsigned char squ_8_mouth6_TA_tex_txt[];
extern unsigned char squ_8_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_tig_1;
extern unsigned short tig_1_pal[];
extern unsigned char tig_1_eye1_TA_tex_txt[];
extern unsigned char tig_1_eye2_TA_tex_txt[];
extern unsigned char tig_1_eye3_TA_tex_txt[];
extern unsigned char tig_1_eye4_TA_tex_txt[];
extern unsigned char tig_1_eye5_TA_tex_txt[];
extern unsigned char tig_1_eye6_TA_tex_txt[];
extern unsigned char tig_1_eye7_TA_tex_txt[];
extern unsigned char tig_1_eye8_TA_tex_txt[];
extern unsigned char tig_1_tmem_txt[];
extern unsigned short tig_2_pal[];
extern unsigned char tig_2_eye1_TA_tex_txt[];
extern unsigned char tig_2_eye2_TA_tex_txt[];
extern unsigned char tig_2_eye3_TA_tex_txt[];
extern unsigned char tig_2_eye4_TA_tex_txt[];
extern unsigned char tig_2_eye5_TA_tex_txt[];
extern unsigned char tig_2_eye6_TA_tex_txt[];
extern unsigned char tig_2_eye7_TA_tex_txt[];
extern unsigned char tig_2_eye8_TA_tex_txt[];
extern unsigned char tig_2_tmem_txt[];
extern unsigned short tig_3_pal[];
extern unsigned char tig_3_eye1_TA_tex_txt[];
extern unsigned char tig_3_eye2_TA_tex_txt[];
extern unsigned char tig_3_eye3_TA_tex_txt[];
extern unsigned char tig_3_eye4_TA_tex_txt[];
extern unsigned char tig_3_eye5_TA_tex_txt[];
extern unsigned char tig_3_eye6_TA_tex_txt[];
extern unsigned char tig_3_eye7_TA_tex_txt[];
extern unsigned char tig_3_eye8_TA_tex_txt[];
extern unsigned char tig_3_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_wol_1;
extern unsigned short wol_1_pal[];
extern unsigned char wol_1_eye1_TA_tex_txt[];
extern unsigned char wol_1_eye2_TA_tex_txt[];
extern unsigned char wol_1_eye3_TA_tex_txt[];
extern unsigned char wol_1_eye4_TA_tex_txt[];
extern unsigned char wol_1_eye5_TA_tex_txt[];
extern unsigned char wol_1_eye6_TA_tex_txt[];
extern unsigned char wol_1_eye7_TA_tex_txt[];
extern unsigned char wol_1_eye8_TA_tex_txt[];
extern unsigned char wol_1_tmem_txt[];
extern unsigned short wol_2_pal[];
extern unsigned char wol_2_eye1_TA_tex_txt[];
extern unsigned char wol_2_eye2_TA_tex_txt[];
extern unsigned char wol_2_eye3_TA_tex_txt[];
extern unsigned char wol_2_eye4_TA_tex_txt[];
extern unsigned char wol_2_eye5_TA_tex_txt[];
extern unsigned char wol_2_eye6_TA_tex_txt[];
extern unsigned char wol_2_eye7_TA_tex_txt[];
extern unsigned char wol_2_eye8_TA_tex_txt[];
extern unsigned char wol_2_tmem_txt[];
extern unsigned short wol_3_pal[];
extern unsigned char wol_3_eye1_TA_tex_txt[];
extern unsigned char wol_3_eye2_TA_tex_txt[];
extern unsigned char wol_3_eye3_TA_tex_txt[];
extern unsigned char wol_3_eye4_TA_tex_txt[];
extern unsigned char wol_3_eye5_TA_tex_txt[];
extern unsigned char wol_3_eye6_TA_tex_txt[];
extern unsigned char wol_3_eye7_TA_tex_txt[];
extern unsigned char wol_3_eye8_TA_tex_txt[];
extern unsigned char wol_3_tmem_txt[];
extern unsigned short duk_7_pal[];
extern unsigned char duk_7_eye1_TA_tex_txt[];
extern unsigned char duk_7_eye2_TA_tex_txt[];
extern unsigned char duk_7_eye3_TA_tex_txt[];
extern unsigned char duk_7_eye4_TA_tex_txt[];
extern unsigned char duk_7_eye5_TA_tex_txt[];
extern unsigned char duk_7_eye6_TA_tex_txt[];
extern unsigned char duk_7_eye7_TA_tex_txt[];
extern unsigned char duk_7_eye8_TA_tex_txt[];
extern unsigned char duk_7_mouth1_TA_tex_txt[];
extern unsigned char duk_7_mouth2_TA_tex_txt[];
extern unsigned char duk_7_mouth3_TA_tex_txt[];
extern unsigned char duk_7_mouth4_TA_tex_txt[];
extern unsigned char duk_7_mouth5_TA_tex_txt[];
extern unsigned char duk_7_mouth6_TA_tex_txt[];
extern unsigned char duk_7_tmem_txt[];
extern unsigned short duk_8_pal[];
extern unsigned char duk_8_eye1_TA_tex_txt[];
extern unsigned char duk_8_eye2_TA_tex_txt[];
extern unsigned char duk_8_eye3_TA_tex_txt[];
extern unsigned char duk_8_eye4_TA_tex_txt[];
extern unsigned char duk_8_eye5_TA_tex_txt[];
extern unsigned char duk_8_eye6_TA_tex_txt[];
extern unsigned char duk_8_eye7_TA_tex_txt[];
extern unsigned char duk_8_eye8_TA_tex_txt[];
extern unsigned char duk_8_mouth1_TA_tex_txt[];
extern unsigned char duk_8_mouth2_TA_tex_txt[];
extern unsigned char duk_8_mouth3_TA_tex_txt[];
extern unsigned char duk_8_mouth4_TA_tex_txt[];
extern unsigned char duk_8_mouth5_TA_tex_txt[];
extern unsigned char duk_8_mouth6_TA_tex_txt[];
extern unsigned char duk_8_tmem_txt[];
extern unsigned short wol_4_pal[];
extern unsigned char wol_4_eye1_TA_tex_txt[];
extern unsigned char wol_4_eye2_TA_tex_txt[];
extern unsigned char wol_4_eye3_TA_tex_txt[];
extern unsigned char wol_4_eye4_TA_tex_txt[];
extern unsigned char wol_4_eye5_TA_tex_txt[];
extern unsigned char wol_4_eye6_TA_tex_txt[];
extern unsigned char wol_4_eye7_TA_tex_txt[];
extern unsigned char wol_4_eye8_TA_tex_txt[];
extern unsigned char wol_4_tmem_txt[];
extern unsigned short rhn_4_pal[];
extern unsigned char rhn_4_eye1_TA_tex_txt[];
extern unsigned char rhn_4_eye2_TA_tex_txt[];
extern unsigned char rhn_4_eye3_TA_tex_txt[];
extern unsigned char rhn_4_eye4_TA_tex_txt[];
extern unsigned char rhn_4_eye5_TA_tex_txt[];
extern unsigned char rhn_4_eye6_TA_tex_txt[];
extern unsigned char rhn_4_eye7_TA_tex_txt[];
extern unsigned char rhn_4_eye8_TA_tex_txt[];
extern unsigned char rhn_4_mouth1_TA_tex_txt[];
extern unsigned char rhn_4_mouth2_TA_tex_txt[];
extern unsigned char rhn_4_mouth3_TA_tex_txt[];
extern unsigned char rhn_4_mouth4_TA_tex_txt[];
extern unsigned char rhn_4_mouth5_TA_tex_txt[];
extern unsigned char rhn_4_mouth6_TA_tex_txt[];
extern unsigned char rhn_4_tmem_txt[];
extern unsigned short bul_3_pal[];
extern unsigned char bul_3_eye1_TA_tex_txt[];
extern unsigned char bul_3_eye2_TA_tex_txt[];
extern unsigned char bul_3_eye3_TA_tex_txt[];
extern unsigned char bul_3_eye4_TA_tex_txt[];
extern unsigned char bul_3_eye5_TA_tex_txt[];
extern unsigned char bul_3_eye6_TA_tex_txt[];
extern unsigned char bul_3_eye7_TA_tex_txt[];
extern unsigned char bul_3_eye8_TA_tex_txt[];
extern unsigned char bul_3_mouth1_TA_tex_txt[];
extern unsigned char bul_3_mouth2_TA_tex_txt[];
extern unsigned char bul_3_mouth3_TA_tex_txt[];
extern unsigned char bul_3_mouth4_TA_tex_txt[];
extern unsigned char bul_3_mouth5_TA_tex_txt[];
extern unsigned char bul_3_mouth6_TA_tex_txt[];
extern unsigned char bul_3_tmem_txt[];
extern unsigned short bul_4_pal[];
extern unsigned char bul_4_eye1_TA_tex_txt[];
extern unsigned char bul_4_eye2_TA_tex_txt[];
extern unsigned char bul_4_eye3_TA_tex_txt[];
extern unsigned char bul_4_eye4_TA_tex_txt[];
extern unsigned char bul_4_eye5_TA_tex_txt[];
extern unsigned char bul_4_eye6_TA_tex_txt[];
extern unsigned char bul_4_eye7_TA_tex_txt[];
extern unsigned char bul_4_eye8_TA_tex_txt[];
extern unsigned char bul_4_mouth1_TA_tex_txt[];
extern unsigned char bul_4_mouth2_TA_tex_txt[];
extern unsigned char bul_4_mouth3_TA_tex_txt[];
extern unsigned char bul_4_mouth4_TA_tex_txt[];
extern unsigned char bul_4_mouth5_TA_tex_txt[];
extern unsigned char bul_4_mouth6_TA_tex_txt[];
extern unsigned char bul_4_tmem_txt[];
extern unsigned short hip_4_pal[];
extern unsigned char hip_4_eye1_TA_tex_txt[];
extern unsigned char hip_4_eye2_TA_tex_txt[];
extern unsigned char hip_4_eye3_TA_tex_txt[];
extern unsigned char hip_4_eye4_TA_tex_txt[];
extern unsigned char hip_4_eye5_TA_tex_txt[];
extern unsigned char hip_4_eye6_TA_tex_txt[];
extern unsigned char hip_4_eye7_TA_tex_txt[];
extern unsigned char hip_4_eye8_TA_tex_txt[];
extern unsigned char hip_4_tmem_txt[];
extern unsigned short elp_4_pal[];
extern unsigned char elp_4_eye1_TA_tex_txt[];
extern unsigned char elp_4_eye2_TA_tex_txt[];
extern unsigned char elp_4_eye3_TA_tex_txt[];
extern unsigned char elp_4_eye4_TA_tex_txt[];
extern unsigned char elp_4_eye5_TA_tex_txt[];
extern unsigned char elp_4_eye6_TA_tex_txt[];
extern unsigned char elp_4_eye7_TA_tex_txt[];
extern unsigned char elp_4_eye8_TA_tex_txt[];
extern unsigned char elp_4_mouth1_TA_tex_txt[];
extern unsigned char elp_4_mouth2_TA_tex_txt[];
extern unsigned char elp_4_mouth3_TA_tex_txt[];
extern unsigned char elp_4_mouth4_TA_tex_txt[];
extern unsigned char elp_4_mouth5_TA_tex_txt[];
extern unsigned char elp_4_mouth6_TA_tex_txt[];
extern unsigned char elp_4_tmem_txt[];
extern unsigned short dog_9_pal[];
extern unsigned char dog_9_eye1_TA_tex_txt[];
extern unsigned char dog_9_eye2_TA_tex_txt[];
extern unsigned char dog_9_eye3_TA_tex_txt[];
extern unsigned char dog_9_eye4_TA_tex_txt[];
extern unsigned char dog_9_eye5_TA_tex_txt[];
extern unsigned char dog_9_eye6_TA_tex_txt[];
extern unsigned char dog_9_eye7_TA_tex_txt[];
extern unsigned char dog_9_eye8_TA_tex_txt[];
extern unsigned char dog_9_mouth1_TA_tex_txt[];
extern unsigned char dog_9_mouth2_TA_tex_txt[];
extern unsigned char dog_9_mouth3_TA_tex_txt[];
extern unsigned char dog_9_mouth4_TA_tex_txt[];
extern unsigned char dog_9_mouth5_TA_tex_txt[];
extern unsigned char dog_9_mouth6_TA_tex_txt[];
extern unsigned char dog_9_tmem_txt[];
extern unsigned short dog_10_pal[];
extern unsigned char dog_10_eye1_TA_tex_txt[];
extern unsigned char dog_10_eye2_TA_tex_txt[];
extern unsigned char dog_10_eye3_TA_tex_txt[];
extern unsigned char dog_10_eye4_TA_tex_txt[];
extern unsigned char dog_10_eye5_TA_tex_txt[];
extern unsigned char dog_10_eye6_TA_tex_txt[];
extern unsigned char dog_10_eye7_TA_tex_txt[];
extern unsigned char dog_10_eye8_TA_tex_txt[];
extern unsigned char dog_10_mouth1_TA_tex_txt[];
extern unsigned char dog_10_mouth2_TA_tex_txt[];
extern unsigned char dog_10_mouth3_TA_tex_txt[];
extern unsigned char dog_10_mouth4_TA_tex_txt[];
extern unsigned char dog_10_mouth5_TA_tex_txt[];
extern unsigned char dog_10_mouth6_TA_tex_txt[];
extern unsigned char dog_10_tmem_txt[];
extern unsigned short hip_5_pal[];
extern unsigned char hip_5_eye1_TA_tex_txt[];
extern unsigned char hip_5_eye2_TA_tex_txt[];
extern unsigned char hip_5_eye3_TA_tex_txt[];
extern unsigned char hip_5_eye4_TA_tex_txt[];
extern unsigned char hip_5_eye5_TA_tex_txt[];
extern unsigned char hip_5_eye6_TA_tex_txt[];
extern unsigned char hip_5_eye7_TA_tex_txt[];
extern unsigned char hip_5_eye8_TA_tex_txt[];
extern unsigned char hip_5_tmem_txt[];
extern unsigned short hip_6_pal[];
extern unsigned char hip_6_eye1_TA_tex_txt[];
extern unsigned char hip_6_eye2_TA_tex_txt[];
extern unsigned char hip_6_eye3_TA_tex_txt[];
extern unsigned char hip_6_eye4_TA_tex_txt[];
extern unsigned char hip_6_eye5_TA_tex_txt[];
extern unsigned char hip_6_eye6_TA_tex_txt[];
extern unsigned char hip_6_eye7_TA_tex_txt[];
extern unsigned char hip_6_eye8_TA_tex_txt[];
extern unsigned char hip_6_tmem_txt[];
extern unsigned short hip_7_pal[];
extern unsigned char hip_7_eye1_TA_tex_txt[];
extern unsigned char hip_7_eye2_TA_tex_txt[];
extern unsigned char hip_7_eye3_TA_tex_txt[];
extern unsigned char hip_7_eye4_TA_tex_txt[];
extern unsigned char hip_7_eye5_TA_tex_txt[];
extern unsigned char hip_7_eye6_TA_tex_txt[];
extern unsigned char hip_7_eye7_TA_tex_txt[];
extern unsigned char hip_7_eye8_TA_tex_txt[];
extern unsigned char hip_7_tmem_txt[];
extern unsigned short squ_9_pal[];
extern unsigned char squ_9_eye1_TA_tex_txt[];
extern unsigned char squ_9_eye2_TA_tex_txt[];
extern unsigned char squ_9_eye3_TA_tex_txt[];
extern unsigned char squ_9_eye4_TA_tex_txt[];
extern unsigned char squ_9_eye5_TA_tex_txt[];
extern unsigned char squ_9_eye6_TA_tex_txt[];
extern unsigned char squ_9_eye7_TA_tex_txt[];
extern unsigned char squ_9_eye8_TA_tex_txt[];
extern unsigned char squ_9_mouth1_TA_tex_txt[];
extern unsigned char squ_9_mouth2_TA_tex_txt[];
extern unsigned char squ_9_mouth3_TA_tex_txt[];
extern unsigned char squ_9_mouth4_TA_tex_txt[];
extern unsigned char squ_9_mouth5_TA_tex_txt[];
extern unsigned char squ_9_mouth6_TA_tex_txt[];
extern unsigned char squ_9_tmem_txt[];
extern unsigned short squ_10_pal[];
extern unsigned char squ_10_eye1_TA_tex_txt[];
extern unsigned char squ_10_eye2_TA_tex_txt[];
extern unsigned char squ_10_eye3_TA_tex_txt[];
extern unsigned char squ_10_eye4_TA_tex_txt[];
extern unsigned char squ_10_eye5_TA_tex_txt[];
extern unsigned char squ_10_eye6_TA_tex_txt[];
extern unsigned char squ_10_eye7_TA_tex_txt[];
extern unsigned char squ_10_eye8_TA_tex_txt[];
extern unsigned char squ_10_mouth1_TA_tex_txt[];
extern unsigned char squ_10_mouth2_TA_tex_txt[];
extern unsigned char squ_10_mouth3_TA_tex_txt[];
extern unsigned char squ_10_mouth4_TA_tex_txt[];
extern unsigned char squ_10_mouth5_TA_tex_txt[];
extern unsigned char squ_10_mouth6_TA_tex_txt[];
extern unsigned char squ_10_tmem_txt[];
extern unsigned short elp_5_pal[];
extern unsigned char elp_5_eye1_TA_tex_txt[];
extern unsigned char elp_5_eye2_TA_tex_txt[];
extern unsigned char elp_5_eye3_TA_tex_txt[];
extern unsigned char elp_5_eye4_TA_tex_txt[];
extern unsigned char elp_5_eye5_TA_tex_txt[];
extern unsigned char elp_5_eye6_TA_tex_txt[];
extern unsigned char elp_5_eye7_TA_tex_txt[];
extern unsigned char elp_5_eye8_TA_tex_txt[];
extern unsigned char elp_5_mouth1_TA_tex_txt[];
extern unsigned char elp_5_mouth2_TA_tex_txt[];
extern unsigned char elp_5_mouth3_TA_tex_txt[];
extern unsigned char elp_5_mouth4_TA_tex_txt[];
extern unsigned char elp_5_mouth5_TA_tex_txt[];
extern unsigned char elp_5_mouth6_TA_tex_txt[];
extern unsigned char elp_5_tmem_txt[];
extern unsigned short elp_6_pal[];
extern unsigned char elp_6_eye1_TA_tex_txt[];
extern unsigned char elp_6_eye2_TA_tex_txt[];
extern unsigned char elp_6_eye3_TA_tex_txt[];
extern unsigned char elp_6_eye4_TA_tex_txt[];
extern unsigned char elp_6_eye5_TA_tex_txt[];
extern unsigned char elp_6_eye6_TA_tex_txt[];
extern unsigned char elp_6_eye7_TA_tex_txt[];
extern unsigned char elp_6_eye8_TA_tex_txt[];
extern unsigned char elp_6_mouth1_TA_tex_txt[];
extern unsigned char elp_6_mouth2_TA_tex_txt[];
extern unsigned char elp_6_mouth3_TA_tex_txt[];
extern unsigned char elp_6_mouth4_TA_tex_txt[];
extern unsigned char elp_6_mouth5_TA_tex_txt[];
extern unsigned char elp_6_mouth6_TA_tex_txt[];
extern unsigned char elp_6_tmem_txt[];
extern unsigned short crd_4_pal[];
extern unsigned char crd_4_eye1_TA_tex_txt[];
extern unsigned char crd_4_eye2_TA_tex_txt[];
extern unsigned char crd_4_eye3_TA_tex_txt[];
extern unsigned char crd_4_eye4_TA_tex_txt[];
extern unsigned char crd_4_eye5_TA_tex_txt[];
extern unsigned char crd_4_eye6_TA_tex_txt[];
extern unsigned char crd_4_eye7_TA_tex_txt[];
extern unsigned char crd_4_eye8_TA_tex_txt[];
extern unsigned char crd_4_tmem_txt[];
extern unsigned short rbt_10_pal[];
extern unsigned char rbt_10_eye1_TA_tex_txt[];
extern unsigned char rbt_10_eye2_TA_tex_txt[];
extern unsigned char rbt_10_eye3_TA_tex_txt[];
extern unsigned char rbt_10_eye4_TA_tex_txt[];
extern unsigned char rbt_10_eye5_TA_tex_txt[];
extern unsigned char rbt_10_eye6_TA_tex_txt[];
extern unsigned char rbt_10_eye7_TA_tex_txt[];
extern unsigned char rbt_10_eye8_TA_tex_txt[];
extern unsigned char rbt_10_mouth1_TA_tex_txt[];
extern unsigned char rbt_10_mouth2_TA_tex_txt[];
extern unsigned char rbt_10_mouth3_TA_tex_txt[];
extern unsigned char rbt_10_mouth4_TA_tex_txt[];
extern unsigned char rbt_10_mouth5_TA_tex_txt[];
extern unsigned char rbt_10_mouth6_TA_tex_txt[];
extern unsigned char rbt_10_tmem_txt[];
extern unsigned short shp_2_pal[];
extern unsigned char shp_2_eye1_TA_tex_txt[];
extern unsigned char shp_2_eye2_TA_tex_txt[];
extern unsigned char shp_2_eye3_TA_tex_txt[];
extern unsigned char shp_2_eye4_TA_tex_txt[];
extern unsigned char shp_2_eye5_TA_tex_txt[];
extern unsigned char shp_2_eye6_TA_tex_txt[];
extern unsigned char shp_2_eye7_TA_tex_txt[];
extern unsigned char shp_2_eye8_TA_tex_txt[];
extern unsigned char shp_2_mouth1_TA_tex_txt[];
extern unsigned char shp_2_mouth2_TA_tex_txt[];
extern unsigned char shp_2_mouth3_TA_tex_txt[];
extern unsigned char shp_2_mouth4_TA_tex_txt[];
extern unsigned char shp_2_mouth5_TA_tex_txt[];
extern unsigned char shp_2_mouth6_TA_tex_txt[];
extern unsigned char shp_2_tmem_txt[];
extern unsigned short shp_3_pal[];
extern unsigned char shp_3_eye1_TA_tex_txt[];
extern unsigned char shp_3_eye2_TA_tex_txt[];
extern unsigned char shp_3_eye3_TA_tex_txt[];
extern unsigned char shp_3_eye4_TA_tex_txt[];
extern unsigned char shp_3_eye5_TA_tex_txt[];
extern unsigned char shp_3_eye6_TA_tex_txt[];
extern unsigned char shp_3_eye7_TA_tex_txt[];
extern unsigned char shp_3_eye8_TA_tex_txt[];
extern unsigned char shp_3_mouth1_TA_tex_txt[];
extern unsigned char shp_3_mouth2_TA_tex_txt[];
extern unsigned char shp_3_mouth3_TA_tex_txt[];
extern unsigned char shp_3_mouth4_TA_tex_txt[];
extern unsigned char shp_3_mouth5_TA_tex_txt[];
extern unsigned char shp_3_mouth6_TA_tex_txt[];
extern unsigned char shp_3_tmem_txt[];
extern unsigned short wol_5_pal[];
extern unsigned char wol_5_eye1_TA_tex_txt[];
extern unsigned char wol_5_eye2_TA_tex_txt[];
extern unsigned char wol_5_eye3_TA_tex_txt[];
extern unsigned char wol_5_eye4_TA_tex_txt[];
extern unsigned char wol_5_eye5_TA_tex_txt[];
extern unsigned char wol_5_eye6_TA_tex_txt[];
extern unsigned char wol_5_eye7_TA_tex_txt[];
extern unsigned char wol_5_eye8_TA_tex_txt[];
extern unsigned char wol_5_tmem_txt[];
extern unsigned short duk_9_pal[];
extern unsigned char duk_9_eye1_TA_tex_txt[];
extern unsigned char duk_9_eye2_TA_tex_txt[];
extern unsigned char duk_9_eye3_TA_tex_txt[];
extern unsigned char duk_9_eye4_TA_tex_txt[];
extern unsigned char duk_9_eye5_TA_tex_txt[];
extern unsigned char duk_9_eye6_TA_tex_txt[];
extern unsigned char duk_9_eye7_TA_tex_txt[];
extern unsigned char duk_9_eye8_TA_tex_txt[];
extern unsigned char duk_9_mouth1_TA_tex_txt[];
extern unsigned char duk_9_mouth2_TA_tex_txt[];
extern unsigned char duk_9_mouth3_TA_tex_txt[];
extern unsigned char duk_9_mouth4_TA_tex_txt[];
extern unsigned char duk_9_mouth5_TA_tex_txt[];
extern unsigned char duk_9_mouth6_TA_tex_txt[];
extern unsigned char duk_9_tmem_txt[];
extern unsigned short duk_10_pal[];
extern unsigned char duk_10_eye1_TA_tex_txt[];
extern unsigned char duk_10_eye2_TA_tex_txt[];
extern unsigned char duk_10_eye3_TA_tex_txt[];
extern unsigned char duk_10_eye4_TA_tex_txt[];
extern unsigned char duk_10_eye5_TA_tex_txt[];
extern unsigned char duk_10_eye6_TA_tex_txt[];
extern unsigned char duk_10_eye7_TA_tex_txt[];
extern unsigned char duk_10_eye8_TA_tex_txt[];
extern unsigned char duk_10_mouth1_TA_tex_txt[];
extern unsigned char duk_10_mouth2_TA_tex_txt[];
extern unsigned char duk_10_mouth3_TA_tex_txt[];
extern unsigned char duk_10_mouth4_TA_tex_txt[];
extern unsigned char duk_10_mouth5_TA_tex_txt[];
extern unsigned char duk_10_mouth6_TA_tex_txt[];
extern unsigned char duk_10_tmem_txt[];
extern unsigned short shp_4_pal[];
extern unsigned char shp_4_eye1_TA_tex_txt[];
extern unsigned char shp_4_eye2_TA_tex_txt[];
extern unsigned char shp_4_eye3_TA_tex_txt[];
extern unsigned char shp_4_eye4_TA_tex_txt[];
extern unsigned char shp_4_eye5_TA_tex_txt[];
extern unsigned char shp_4_eye6_TA_tex_txt[];
extern unsigned char shp_4_eye7_TA_tex_txt[];
extern unsigned char shp_4_eye8_TA_tex_txt[];
extern unsigned char shp_4_mouth1_TA_tex_txt[];
extern unsigned char shp_4_mouth2_TA_tex_txt[];
extern unsigned char shp_4_mouth3_TA_tex_txt[];
extern unsigned char shp_4_mouth4_TA_tex_txt[];
extern unsigned char shp_4_mouth5_TA_tex_txt[];
extern unsigned char shp_4_mouth6_TA_tex_txt[];
extern unsigned char shp_4_tmem_txt[];
extern unsigned short shp_5_pal[];
extern unsigned char shp_5_eye1_TA_tex_txt[];
extern unsigned char shp_5_eye2_TA_tex_txt[];
extern unsigned char shp_5_eye3_TA_tex_txt[];
extern unsigned char shp_5_eye4_TA_tex_txt[];
extern unsigned char shp_5_eye5_TA_tex_txt[];
extern unsigned char shp_5_eye6_TA_tex_txt[];
extern unsigned char shp_5_eye7_TA_tex_txt[];
extern unsigned char shp_5_eye8_TA_tex_txt[];
extern unsigned char shp_5_mouth1_TA_tex_txt[];
extern unsigned char shp_5_mouth2_TA_tex_txt[];
extern unsigned char shp_5_mouth3_TA_tex_txt[];
extern unsigned char shp_5_mouth4_TA_tex_txt[];
extern unsigned char shp_5_mouth5_TA_tex_txt[];
extern unsigned char shp_5_mouth6_TA_tex_txt[];
extern unsigned char shp_5_tmem_txt[];
extern unsigned short shp_6_pal[];
extern unsigned char shp_6_eye1_TA_tex_txt[];
extern unsigned char shp_6_eye2_TA_tex_txt[];
extern unsigned char shp_6_eye3_TA_tex_txt[];
extern unsigned char shp_6_eye4_TA_tex_txt[];
extern unsigned char shp_6_eye5_TA_tex_txt[];
extern unsigned char shp_6_eye6_TA_tex_txt[];
extern unsigned char shp_6_eye7_TA_tex_txt[];
extern unsigned char shp_6_eye8_TA_tex_txt[];
extern unsigned char shp_6_mouth1_TA_tex_txt[];
extern unsigned char shp_6_mouth2_TA_tex_txt[];
extern unsigned char shp_6_mouth3_TA_tex_txt[];
extern unsigned char shp_6_mouth4_TA_tex_txt[];
extern unsigned char shp_6_mouth5_TA_tex_txt[];
extern unsigned char shp_6_mouth6_TA_tex_txt[];
extern unsigned char shp_6_tmem_txt[];
extern unsigned short dog_7_pal[];
extern unsigned char dog_7_eye1_TA_tex_txt[];
extern unsigned char dog_7_eye2_TA_tex_txt[];
extern unsigned char dog_7_eye3_TA_tex_txt[];
extern unsigned char dog_7_eye4_TA_tex_txt[];
extern unsigned char dog_7_eye5_TA_tex_txt[];
extern unsigned char dog_7_eye6_TA_tex_txt[];
extern unsigned char dog_7_eye7_TA_tex_txt[];
extern unsigned char dog_7_eye8_TA_tex_txt[];
extern unsigned char dog_7_mouth1_TA_tex_txt[];
extern unsigned char dog_7_mouth2_TA_tex_txt[];
extern unsigned char dog_7_mouth3_TA_tex_txt[];
extern unsigned char dog_7_mouth4_TA_tex_txt[];
extern unsigned char dog_7_mouth5_TA_tex_txt[];
extern unsigned char dog_7_mouth6_TA_tex_txt[];
extern unsigned char dog_7_tmem_txt[];
extern unsigned short duk_11_pal[];
extern unsigned char duk_11_eye1_TA_tex_txt[];
extern unsigned char duk_11_eye2_TA_tex_txt[];
extern unsigned char duk_11_eye3_TA_tex_txt[];
extern unsigned char duk_11_eye4_TA_tex_txt[];
extern unsigned char duk_11_eye5_TA_tex_txt[];
extern unsigned char duk_11_eye6_TA_tex_txt[];
extern unsigned char duk_11_eye7_TA_tex_txt[];
extern unsigned char duk_11_eye8_TA_tex_txt[];
extern unsigned char duk_11_mouth1_TA_tex_txt[];
extern unsigned char duk_11_mouth2_TA_tex_txt[];
extern unsigned char duk_11_mouth3_TA_tex_txt[];
extern unsigned char duk_11_mouth4_TA_tex_txt[];
extern unsigned char duk_11_mouth5_TA_tex_txt[];
extern unsigned char duk_11_mouth6_TA_tex_txt[];
extern unsigned char duk_11_tmem_txt[];
extern unsigned short rbt_11_pal[];
extern unsigned char rbt_11_eye1_TA_tex_txt[];
extern unsigned char rbt_11_eye2_TA_tex_txt[];
extern unsigned char rbt_11_eye3_TA_tex_txt[];
extern unsigned char rbt_11_eye4_TA_tex_txt[];
extern unsigned char rbt_11_eye5_TA_tex_txt[];
extern unsigned char rbt_11_eye6_TA_tex_txt[];
extern unsigned char rbt_11_eye7_TA_tex_txt[];
extern unsigned char rbt_11_eye8_TA_tex_txt[];
extern unsigned char rbt_11_mouth1_TA_tex_txt[];
extern unsigned char rbt_11_mouth2_TA_tex_txt[];
extern unsigned char rbt_11_mouth3_TA_tex_txt[];
extern unsigned char rbt_11_mouth4_TA_tex_txt[];
extern unsigned char rbt_11_mouth5_TA_tex_txt[];
extern unsigned char rbt_11_mouth6_TA_tex_txt[];
extern unsigned char rbt_11_tmem_txt[];
extern unsigned short squ_11_pal[];
extern unsigned char squ_11_eye1_TA_tex_txt[];
extern unsigned char squ_11_eye2_TA_tex_txt[];
extern unsigned char squ_11_eye3_TA_tex_txt[];
extern unsigned char squ_11_eye4_TA_tex_txt[];
extern unsigned char squ_11_eye5_TA_tex_txt[];
extern unsigned char squ_11_eye6_TA_tex_txt[];
extern unsigned char squ_11_eye7_TA_tex_txt[];
extern unsigned char squ_11_eye8_TA_tex_txt[];
extern unsigned char squ_11_mouth1_TA_tex_txt[];
extern unsigned char squ_11_mouth2_TA_tex_txt[];
extern unsigned char squ_11_mouth3_TA_tex_txt[];
extern unsigned char squ_11_mouth4_TA_tex_txt[];
extern unsigned char squ_11_mouth5_TA_tex_txt[];
extern unsigned char squ_11_mouth6_TA_tex_txt[];
extern unsigned char squ_11_tmem_txt[];
extern unsigned short flg_13_pal[];
extern unsigned char flg_13_eye1_TA_tex_txt[];
extern unsigned char flg_13_eye2_TA_tex_txt[];
extern unsigned char flg_13_eye3_TA_tex_txt[];
extern unsigned char flg_13_eye4_TA_tex_txt[];
extern unsigned char flg_13_eye5_TA_tex_txt[];
extern unsigned char flg_13_eye6_TA_tex_txt[];
extern unsigned char flg_13_eye7_TA_tex_txt[];
extern unsigned char flg_13_eye8_TA_tex_txt[];
extern unsigned char flg_13_mouth1_TA_tex_txt[];
extern unsigned char flg_13_mouth2_TA_tex_txt[];
extern unsigned char flg_13_mouth3_TA_tex_txt[];
extern unsigned char flg_13_mouth4_TA_tex_txt[];
extern unsigned char flg_13_mouth5_TA_tex_txt[];
extern unsigned char flg_13_mouth6_TA_tex_txt[];
extern unsigned char flg_13_tmem_txt[];
extern unsigned short lon_4_pal[];
extern unsigned char lon_4_eye1_TA_tex_txt[];
extern unsigned char lon_4_eye2_TA_tex_txt[];
extern unsigned char lon_4_eye3_TA_tex_txt[];
extern unsigned char lon_4_eye4_TA_tex_txt[];
extern unsigned char lon_4_eye5_TA_tex_txt[];
extern unsigned char lon_4_eye6_TA_tex_txt[];
extern unsigned char lon_4_eye7_TA_tex_txt[];
extern unsigned char lon_4_eye8_TA_tex_txt[];
extern unsigned char lon_4_mouth1_TA_tex_txt[];
extern unsigned char lon_4_mouth2_TA_tex_txt[];
extern unsigned char lon_4_mouth3_TA_tex_txt[];
extern unsigned char lon_4_mouth4_TA_tex_txt[];
extern unsigned char lon_4_mouth5_TA_tex_txt[];
extern unsigned char lon_4_mouth6_TA_tex_txt[];
extern unsigned char lon_4_tmem_txt[];
extern unsigned short pgn_8_pal[];
extern unsigned char pgn_8_eye1_TA_tex_txt[];
extern unsigned char pgn_8_eye2_TA_tex_txt[];
extern unsigned char pgn_8_eye3_TA_tex_txt[];
extern unsigned char pgn_8_eye4_TA_tex_txt[];
extern unsigned char pgn_8_eye5_TA_tex_txt[];
extern unsigned char pgn_8_eye6_TA_tex_txt[];
extern unsigned char pgn_8_eye7_TA_tex_txt[];
extern unsigned char pgn_8_eye8_TA_tex_txt[];
extern unsigned char pgn_8_tmem_txt[];
extern unsigned short elp_7_pal[];
extern unsigned char elp_7_eye1_TA_tex_txt[];
extern unsigned char elp_7_eye2_TA_tex_txt[];
extern unsigned char elp_7_eye3_TA_tex_txt[];
extern unsigned char elp_7_eye4_TA_tex_txt[];
extern unsigned char elp_7_eye5_TA_tex_txt[];
extern unsigned char elp_7_eye6_TA_tex_txt[];
extern unsigned char elp_7_eye7_TA_tex_txt[];
extern unsigned char elp_7_eye8_TA_tex_txt[];
extern unsigned char elp_7_mouth1_TA_tex_txt[];
extern unsigned char elp_7_mouth2_TA_tex_txt[];
extern unsigned char elp_7_mouth3_TA_tex_txt[];
extern unsigned char elp_7_mouth4_TA_tex_txt[];
extern unsigned char elp_7_mouth5_TA_tex_txt[];
extern unsigned char elp_7_mouth6_TA_tex_txt[];
extern unsigned char elp_7_tmem_txt[];
extern unsigned short brd_11_pal[];
extern unsigned char brd_11_eye1_TA_tex_txt[];
extern unsigned char brd_11_eye2_TA_tex_txt[];
extern unsigned char brd_11_eye3_TA_tex_txt[];
extern unsigned char brd_11_eye4_TA_tex_txt[];
extern unsigned char brd_11_eye5_TA_tex_txt[];
extern unsigned char brd_11_eye6_TA_tex_txt[];
extern unsigned char brd_11_eye7_TA_tex_txt[];
extern unsigned char brd_11_eye8_TA_tex_txt[];
extern unsigned char brd_11_tmem_txt[];
extern unsigned short wol_6_pal[];
extern unsigned char wol_6_eye1_TA_tex_txt[];
extern unsigned char wol_6_eye2_TA_tex_txt[];
extern unsigned char wol_6_eye3_TA_tex_txt[];
extern unsigned char wol_6_eye4_TA_tex_txt[];
extern unsigned char wol_6_eye5_TA_tex_txt[];
extern unsigned char wol_6_eye6_TA_tex_txt[];
extern unsigned char wol_6_eye7_TA_tex_txt[];
extern unsigned char wol_6_eye8_TA_tex_txt[];
extern unsigned char wol_6_tmem_txt[];
extern unsigned short mus_10_pal[];
extern unsigned char mus_10_eye1_TA_tex_txt[];
extern unsigned char mus_10_eye2_TA_tex_txt[];
extern unsigned char mus_10_eye3_TA_tex_txt[];
extern unsigned char mus_10_eye4_TA_tex_txt[];
extern unsigned char mus_10_eye5_TA_tex_txt[];
extern unsigned char mus_10_eye6_TA_tex_txt[];
extern unsigned char mus_10_eye7_TA_tex_txt[];
extern unsigned char mus_10_eye8_TA_tex_txt[];
extern unsigned char mus_10_mouth1_TA_tex_txt[];
extern unsigned char mus_10_mouth2_TA_tex_txt[];
extern unsigned char mus_10_mouth3_TA_tex_txt[];
extern unsigned char mus_10_mouth4_TA_tex_txt[];
extern unsigned char mus_10_mouth5_TA_tex_txt[];
extern unsigned char mus_10_mouth6_TA_tex_txt[];
extern unsigned char mus_10_tmem_txt[];
extern unsigned short hrs_8_pal[];
extern unsigned char hrs_8_eye1_TA_tex_txt[];
extern unsigned char hrs_8_eye2_TA_tex_txt[];
extern unsigned char hrs_8_eye3_TA_tex_txt[];
extern unsigned char hrs_8_eye4_TA_tex_txt[];
extern unsigned char hrs_8_eye5_TA_tex_txt[];
extern unsigned char hrs_8_eye6_TA_tex_txt[];
extern unsigned char hrs_8_eye7_TA_tex_txt[];
extern unsigned char hrs_8_eye8_TA_tex_txt[];
extern unsigned char hrs_8_tmem_txt[];
extern unsigned short chn_9_pal[];
extern unsigned char chn_9_eye1_TA_tex_txt[];
extern unsigned char chn_9_eye2_TA_tex_txt[];
extern unsigned char chn_9_eye3_TA_tex_txt[];
extern unsigned char chn_9_eye4_TA_tex_txt[];
extern unsigned char chn_9_eye5_TA_tex_txt[];
extern unsigned char chn_9_eye6_TA_tex_txt[];
extern unsigned char chn_9_eye7_TA_tex_txt[];
extern unsigned char chn_9_eye8_TA_tex_txt[];
extern unsigned char chn_9_tmem_txt[];
extern unsigned short kal_6_pal[];
extern unsigned char kal_6_eye1_TA_tex_txt[];
extern unsigned char kal_6_eye2_TA_tex_txt[];
extern unsigned char kal_6_eye3_TA_tex_txt[];
extern unsigned char kal_6_eye4_TA_tex_txt[];
extern unsigned char kal_6_eye5_TA_tex_txt[];
extern unsigned char kal_6_eye6_TA_tex_txt[];
extern unsigned char kal_6_eye7_TA_tex_txt[];
extern unsigned char kal_6_eye8_TA_tex_txt[];
extern unsigned char kal_6_mouth1_TA_tex_txt[];
extern unsigned char kal_6_mouth2_TA_tex_txt[];
extern unsigned char kal_6_mouth3_TA_tex_txt[];
extern unsigned char kal_6_mouth4_TA_tex_txt[];
extern unsigned char kal_6_mouth5_TA_tex_txt[];
extern unsigned char kal_6_mouth6_TA_tex_txt[];
extern unsigned char kal_6_tmem_txt[];
extern unsigned short gor_5_pal[];
extern unsigned char gor_5_eye1_TA_tex_txt[];
extern unsigned char gor_5_eye2_TA_tex_txt[];
extern unsigned char gor_5_eye3_TA_tex_txt[];
extern unsigned char gor_5_eye4_TA_tex_txt[];
extern unsigned char gor_5_eye5_TA_tex_txt[];
extern unsigned char gor_5_eye6_TA_tex_txt[];
extern unsigned char gor_5_eye7_TA_tex_txt[];
extern unsigned char gor_5_eye8_TA_tex_txt[];
extern unsigned char gor_5_mouth1_TA_tex_txt[];
extern unsigned char gor_5_mouth2_TA_tex_txt[];
extern unsigned char gor_5_mouth3_TA_tex_txt[];
extern unsigned char gor_5_mouth4_TA_tex_txt[];
extern unsigned char gor_5_mouth5_TA_tex_txt[];
extern unsigned char gor_5_mouth6_TA_tex_txt[];
extern unsigned char gor_5_tmem_txt[];
extern unsigned short tig_4_pal[];
extern unsigned char tig_4_eye1_TA_tex_txt[];
extern unsigned char tig_4_eye2_TA_tex_txt[];
extern unsigned char tig_4_eye3_TA_tex_txt[];
extern unsigned char tig_4_eye4_TA_tex_txt[];
extern unsigned char tig_4_eye5_TA_tex_txt[];
extern unsigned char tig_4_eye6_TA_tex_txt[];
extern unsigned char tig_4_eye7_TA_tex_txt[];
extern unsigned char tig_4_eye8_TA_tex_txt[];
extern unsigned char tig_4_tmem_txt[];
extern unsigned short cbr_10_pal[];
extern unsigned char cbr_10_eye1_TA_tex_txt[];
extern unsigned char cbr_10_eye2_TA_tex_txt[];
extern unsigned char cbr_10_eye3_TA_tex_txt[];
extern unsigned char cbr_10_eye4_TA_tex_txt[];
extern unsigned char cbr_10_eye5_TA_tex_txt[];
extern unsigned char cbr_10_eye6_TA_tex_txt[];
extern unsigned char cbr_10_eye7_TA_tex_txt[];
extern unsigned char cbr_10_eye8_TA_tex_txt[];
extern unsigned char cbr_10_mouth1_TA_tex_txt[];
extern unsigned char cbr_10_mouth2_TA_tex_txt[];
extern unsigned char cbr_10_mouth3_TA_tex_txt[];
extern unsigned char cbr_10_mouth4_TA_tex_txt[];
extern unsigned char cbr_10_mouth5_TA_tex_txt[];
extern unsigned char cbr_10_mouth6_TA_tex_txt[];
extern unsigned char cbr_10_tmem_txt[];
extern unsigned short cbr_11_pal[];
extern unsigned char cbr_11_eye1_TA_tex_txt[];
extern unsigned char cbr_11_eye2_TA_tex_txt[];
extern unsigned char cbr_11_eye3_TA_tex_txt[];
extern unsigned char cbr_11_eye4_TA_tex_txt[];
extern unsigned char cbr_11_eye5_TA_tex_txt[];
extern unsigned char cbr_11_eye6_TA_tex_txt[];
extern unsigned char cbr_11_eye7_TA_tex_txt[];
extern unsigned char cbr_11_eye8_TA_tex_txt[];
extern unsigned char cbr_11_mouth1_TA_tex_txt[];
extern unsigned char cbr_11_mouth2_TA_tex_txt[];
extern unsigned char cbr_11_mouth3_TA_tex_txt[];
extern unsigned char cbr_11_mouth4_TA_tex_txt[];
extern unsigned char cbr_11_mouth5_TA_tex_txt[];
extern unsigned char cbr_11_mouth6_TA_tex_txt[];
extern unsigned char cbr_11_tmem_txt[];
extern unsigned short pig_11_pal[];
extern unsigned char pig_11_eye1_TA_tex_txt[];
extern unsigned char pig_11_eye2_TA_tex_txt[];
extern unsigned char pig_11_eye3_TA_tex_txt[];
extern unsigned char pig_11_eye4_TA_tex_txt[];
extern unsigned char pig_11_eye5_TA_tex_txt[];
extern unsigned char pig_11_eye6_TA_tex_txt[];
extern unsigned char pig_11_eye7_TA_tex_txt[];
extern unsigned char pig_11_eye8_TA_tex_txt[];
extern unsigned char pig_11_mouth1_TA_tex_txt[];
extern unsigned char pig_11_mouth2_TA_tex_txt[];
extern unsigned char pig_11_mouth3_TA_tex_txt[];
extern unsigned char pig_11_mouth4_TA_tex_txt[];
extern unsigned char pig_11_mouth5_TA_tex_txt[];
extern unsigned char pig_11_mouth6_TA_tex_txt[];
extern unsigned char pig_11_tmem_txt[];
extern unsigned short cat_14_pal[];
extern unsigned char cat_14_eye1_TA_tex_txt[];
extern unsigned char cat_14_eye2_TA_tex_txt[];
extern unsigned char cat_14_eye3_TA_tex_txt[];
extern unsigned char cat_14_eye4_TA_tex_txt[];
extern unsigned char cat_14_eye5_TA_tex_txt[];
extern unsigned char cat_14_eye6_TA_tex_txt[];
extern unsigned char cat_14_eye7_TA_tex_txt[];
extern unsigned char cat_14_eye8_TA_tex_txt[];
extern unsigned char cat_14_mouth1_TA_tex_txt[];
extern unsigned char cat_14_mouth2_TA_tex_txt[];
extern unsigned char cat_14_mouth3_TA_tex_txt[];
extern unsigned char cat_14_mouth4_TA_tex_txt[];
extern unsigned char cat_14_mouth5_TA_tex_txt[];
extern unsigned char cat_14_mouth6_TA_tex_txt[];
extern unsigned char cat_14_tmem_txt[];
extern unsigned short cat_15_pal[];
extern unsigned char cat_15_eye1_TA_tex_txt[];
extern unsigned char cat_15_eye2_TA_tex_txt[];
extern unsigned char cat_15_eye3_TA_tex_txt[];
extern unsigned char cat_15_eye4_TA_tex_txt[];
extern unsigned char cat_15_eye5_TA_tex_txt[];
extern unsigned char cat_15_eye6_TA_tex_txt[];
extern unsigned char cat_15_eye7_TA_tex_txt[];
extern unsigned char cat_15_eye8_TA_tex_txt[];
extern unsigned char cat_15_mouth1_TA_tex_txt[];
extern unsigned char cat_15_mouth2_TA_tex_txt[];
extern unsigned char cat_15_mouth3_TA_tex_txt[];
extern unsigned char cat_15_mouth4_TA_tex_txt[];
extern unsigned char cat_15_mouth5_TA_tex_txt[];
extern unsigned char cat_15_mouth6_TA_tex_txt[];
extern unsigned char cat_15_tmem_txt[];
extern unsigned short chn_1_pal[];
extern unsigned char chn_1_eye1_TA_tex_txt[];
extern unsigned char chn_1_eye2_TA_tex_txt[];
extern unsigned char chn_1_eye3_TA_tex_txt[];
extern unsigned char chn_1_eye4_TA_tex_txt[];
extern unsigned char chn_1_eye5_TA_tex_txt[];
extern unsigned char chn_1_eye6_TA_tex_txt[];
extern unsigned char chn_1_eye7_TA_tex_txt[];
extern unsigned char chn_1_eye8_TA_tex_txt[];
extern unsigned char chn_1_tmem_txt[];
extern unsigned short chn_1_pal[];
extern unsigned char chn_1_eye1_TA_tex_txt[];
extern unsigned char chn_1_eye2_TA_tex_txt[];
extern unsigned char chn_1_eye3_TA_tex_txt[];
extern unsigned char chn_1_eye4_TA_tex_txt[];
extern unsigned char chn_1_eye5_TA_tex_txt[];
extern unsigned char chn_1_eye6_TA_tex_txt[];
extern unsigned char chn_1_eye7_TA_tex_txt[];
extern unsigned char chn_1_eye8_TA_tex_txt[];
extern unsigned char chn_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_wls_1;
extern unsigned short wls_1_pal[];
extern unsigned char wls_1_eye1_TA_tex_txt[];
extern unsigned char wls_1_eye2_TA_tex_txt[];
extern unsigned char wls_1_eye3_TA_tex_txt[];
extern unsigned char wls_1_eye4_TA_tex_txt[];
extern unsigned char wls_1_eye5_TA_tex_txt[];
extern unsigned char wls_1_eye6_TA_tex_txt[];
extern unsigned char wls_1_eye7_TA_tex_txt[];
extern unsigned char wls_1_eye8_TA_tex_txt[];
extern unsigned char wls_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_fox_1;
extern unsigned short fox_1_pal[];
extern unsigned char fox_1_eye1_TA_tex_txt[];
extern unsigned char fox_1_eye2_TA_tex_txt[];
extern unsigned char fox_1_eye3_TA_tex_txt[];
extern unsigned char fox_1_eye4_TA_tex_txt[];
extern unsigned char fox_1_eye5_TA_tex_txt[];
extern unsigned char fox_1_eye6_TA_tex_txt[];
extern unsigned char fox_1_eye7_TA_tex_txt[];
extern unsigned char fox_1_eye8_TA_tex_txt[];
extern unsigned char fox_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_grf_1;
extern unsigned short grf_1_pal[];
extern unsigned char grf_1_eye1_TA_tex_txt[];
extern unsigned char grf_1_eye2_TA_tex_txt[];
extern unsigned char grf_1_eye3_TA_tex_txt[];
extern unsigned char grf_1_eye4_TA_tex_txt[];
extern unsigned char grf_1_eye5_TA_tex_txt[];
extern unsigned char grf_1_eye6_TA_tex_txt[];
extern unsigned char grf_1_eye7_TA_tex_txt[];
extern unsigned char grf_1_eye8_TA_tex_txt[];
extern unsigned char grf_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_pga_1;
extern unsigned short pga_1_pal[];
extern unsigned char pga_1_eye1_TA_tex_txt[];
extern unsigned char pga_1_eye2_TA_tex_txt[];
extern unsigned char pga_1_eye3_TA_tex_txt[];
extern unsigned char pga_1_eye4_TA_tex_txt[];
extern unsigned char pga_1_eye5_TA_tex_txt[];
extern unsigned char pga_1_eye6_TA_tex_txt[];
extern unsigned char pga_1_eye7_TA_tex_txt[];
extern unsigned char pga_1_eye8_TA_tex_txt[];
extern unsigned char pga_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_xct_1;
extern unsigned short xct_1_pal[];
extern unsigned char xct_1_eye1_TA_tex_txt[];
extern unsigned char xct_1_eye2_TA_tex_txt[];
extern unsigned char xct_1_eye3_TA_tex_txt[];
extern unsigned char xct_1_eye4_TA_tex_txt[];
extern unsigned char xct_1_eye5_TA_tex_txt[];
extern unsigned char xct_1_eye6_TA_tex_txt[];
extern unsigned char xct_1_eye7_TA_tex_txt[];
extern unsigned char xct_1_eye8_TA_tex_txt[];
extern unsigned char xct_1_mouth1_TA_tex_txt[];
extern unsigned char xct_1_mouth2_TA_tex_txt[];
extern unsigned char xct_1_mouth3_TA_tex_txt[];
extern unsigned char xct_1_mouth4_TA_tex_txt[];
extern unsigned char xct_1_mouth5_TA_tex_txt[];
extern unsigned char xct_1_mouth6_TA_tex_txt[];
extern unsigned char xct_1_tmem_txt[];
extern unsigned short xct_1_pal[];
extern unsigned char xct_1_eye1_TA_tex_txt[];
extern unsigned char xct_1_eye2_TA_tex_txt[];
extern unsigned char xct_1_eye3_TA_tex_txt[];
extern unsigned char xct_1_eye4_TA_tex_txt[];
extern unsigned char xct_1_eye5_TA_tex_txt[];
extern unsigned char xct_1_eye6_TA_tex_txt[];
extern unsigned char xct_1_eye7_TA_tex_txt[];
extern unsigned char xct_1_eye8_TA_tex_txt[];
extern unsigned char xct_1_mouth1_TA_tex_txt[];
extern unsigned char xct_1_mouth2_TA_tex_txt[];
extern unsigned char xct_1_mouth3_TA_tex_txt[];
extern unsigned char xct_1_mouth4_TA_tex_txt[];
extern unsigned char xct_1_mouth5_TA_tex_txt[];
extern unsigned char xct_1_mouth6_TA_tex_txt[];
extern unsigned char xct_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_cml_1;
extern unsigned short cml_1_pal[];
extern unsigned char cml_1_eye1_TA_tex_txt[];
extern unsigned char cml_1_eye2_TA_tex_txt[];
extern unsigned char cml_1_eye3_TA_tex_txt[];
extern unsigned char cml_1_eye4_TA_tex_txt[];
extern unsigned char cml_1_eye5_TA_tex_txt[];
extern unsigned char cml_1_eye6_TA_tex_txt[];
extern unsigned char cml_1_eye7_TA_tex_txt[];
extern unsigned char cml_1_eye8_TA_tex_txt[];
extern unsigned char cml_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_boa_1;
extern unsigned short boa_1_pal[];
extern unsigned char boa_1_eye1_TA_tex_txt[];
extern unsigned char boa_1_eye2_TA_tex_txt[];
extern unsigned char boa_1_eye3_TA_tex_txt[];
extern unsigned char boa_1_eye4_TA_tex_txt[];
extern unsigned char boa_1_eye5_TA_tex_txt[];
extern unsigned char boa_1_eye6_TA_tex_txt[];
extern unsigned char boa_1_eye7_TA_tex_txt[];
extern unsigned char boa_1_eye8_TA_tex_txt[];
extern unsigned char boa_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_rcn_1;
extern unsigned short rcn_1_pal[];
extern unsigned char rcn_1_eye1_TA_tex_txt[];
extern unsigned char rcn_1_eye2_TA_tex_txt[];
extern unsigned char rcn_1_eye3_TA_tex_txt[];
extern unsigned char rcn_1_eye4_TA_tex_txt[];
extern unsigned char rcn_1_eye5_TA_tex_txt[];
extern unsigned char rcn_1_eye6_TA_tex_txt[];
extern unsigned char rcn_1_eye7_TA_tex_txt[];
extern unsigned char rcn_1_eye8_TA_tex_txt[];
extern unsigned char rcn_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_rcc_1;
extern unsigned short rcc_1_pal[];
extern unsigned char rcc_1_eye1_TA_tex_txt[];
extern unsigned char rcc_1_eye2_TA_tex_txt[];
extern unsigned char rcc_1_eye3_TA_tex_txt[];
extern unsigned char rcc_1_eye4_TA_tex_txt[];
extern unsigned char rcc_1_eye5_TA_tex_txt[];
extern unsigned char rcc_1_eye6_TA_tex_txt[];
extern unsigned char rcc_1_eye7_TA_tex_txt[];
extern unsigned char rcc_1_eye8_TA_tex_txt[];
extern unsigned char rcc_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_rcs_1;
extern unsigned short rcs_1_pal[];
extern unsigned char rcs_1_eye1_TA_tex_txt[];
extern unsigned char rcs_1_eye2_TA_tex_txt[];
extern unsigned char rcs_1_eye3_TA_tex_txt[];
extern unsigned char rcs_1_eye4_TA_tex_txt[];
extern unsigned char rcs_1_eye5_TA_tex_txt[];
extern unsigned char rcs_1_eye6_TA_tex_txt[];
extern unsigned char rcs_1_eye7_TA_tex_txt[];
extern unsigned char rcs_1_eye8_TA_tex_txt[];
extern unsigned char rcs_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_rcd_1;
extern unsigned short rcd_1_pal[];
extern unsigned char rcd_1_eye1_TA_tex_txt[];
extern unsigned char rcd_1_eye2_TA_tex_txt[];
extern unsigned char rcd_1_eye3_TA_tex_txt[];
extern unsigned char rcd_1_eye4_TA_tex_txt[];
extern unsigned char rcd_1_eye5_TA_tex_txt[];
extern unsigned char rcd_1_eye6_TA_tex_txt[];
extern unsigned char rcd_1_eye7_TA_tex_txt[];
extern unsigned char rcd_1_eye8_TA_tex_txt[];
extern unsigned char rcd_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_bpt_1;
extern unsigned short bpt_1_pal[];
extern unsigned char bpt_1_eye1_TA_tex_txt[];
extern unsigned char bpt_1_eye2_TA_tex_txt[];
extern unsigned char bpt_1_eye3_TA_tex_txt[];
extern unsigned char bpt_1_eye4_TA_tex_txt[];
extern unsigned char bpt_1_eye5_TA_tex_txt[];
extern unsigned char bpt_1_eye6_TA_tex_txt[];
extern unsigned char bpt_1_eye7_TA_tex_txt[];
extern unsigned char bpt_1_eye8_TA_tex_txt[];
extern unsigned char bpt_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_plc_1;
extern unsigned short plc_1_pal[];
extern unsigned char plc_1_eye1_TA_tex_txt[];
extern unsigned char plc_1_eye2_TA_tex_txt[];
extern unsigned char plc_1_eye3_TA_tex_txt[];
extern unsigned char plc_1_eye4_TA_tex_txt[];
extern unsigned char plc_1_eye5_TA_tex_txt[];
extern unsigned char plc_1_eye6_TA_tex_txt[];
extern unsigned char plc_1_eye7_TA_tex_txt[];
extern unsigned char plc_1_eye8_TA_tex_txt[];
extern unsigned char plc_1_mouth1_TA_tex_txt[];
extern unsigned char plc_1_mouth2_TA_tex_txt[];
extern unsigned char plc_1_mouth3_TA_tex_txt[];
extern unsigned char plc_1_mouth4_TA_tex_txt[];
extern unsigned char plc_1_mouth5_TA_tex_txt[];
extern unsigned char plc_1_mouth6_TA_tex_txt[];
extern unsigned char plc_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_mnk_1;
extern unsigned short mnk_1_pal[];
extern unsigned char mnk_1_eye1_TA_tex_txt[];
extern unsigned char mnk_1_eye2_TA_tex_txt[];
extern unsigned char mnk_1_eye3_TA_tex_txt[];
extern unsigned char mnk_1_eye4_TA_tex_txt[];
extern unsigned char mnk_1_eye5_TA_tex_txt[];
extern unsigned char mnk_1_eye6_TA_tex_txt[];
extern unsigned char mnk_1_eye7_TA_tex_txt[];
extern unsigned char mnk_1_eye8_TA_tex_txt[];
extern unsigned char mnk_1_mouth1_TA_tex_txt[];
extern unsigned char mnk_1_mouth2_TA_tex_txt[];
extern unsigned char mnk_1_mouth3_TA_tex_txt[];
extern unsigned char mnk_1_mouth4_TA_tex_txt[];
extern unsigned char mnk_1_mouth5_TA_tex_txt[];
extern unsigned char mnk_1_mouth6_TA_tex_txt[];
extern unsigned char mnk_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_snt_1;
extern unsigned short snt_1_pal[];
extern unsigned char snt_1_eye1_TA_tex_txt[];
extern unsigned char snt_1_eye2_TA_tex_txt[];
extern unsigned char snt_1_eye3_TA_tex_txt[];
extern unsigned char snt_1_eye4_TA_tex_txt[];
extern unsigned char snt_1_eye5_TA_tex_txt[];
extern unsigned char snt_1_eye6_TA_tex_txt[];
extern unsigned char snt_1_eye7_TA_tex_txt[];
extern unsigned char snt_1_eye8_TA_tex_txt[];
extern unsigned char snt_1_mouth1_TA_tex_txt[];
extern unsigned char snt_1_mouth2_TA_tex_txt[];
extern unsigned char snt_1_mouth3_TA_tex_txt[];
extern unsigned char snt_1_mouth4_TA_tex_txt[];
extern unsigned char snt_1_mouth5_TA_tex_txt[];
extern unsigned char snt_1_mouth6_TA_tex_txt[];
extern unsigned char snt_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_pla_1;
extern unsigned short pla_1_pal[];
extern unsigned char pla_1_eye1_TA_tex_txt[];
extern unsigned char pla_1_eye2_TA_tex_txt[];
extern unsigned char pla_1_eye3_TA_tex_txt[];
extern unsigned char pla_1_eye4_TA_tex_txt[];
extern unsigned char pla_1_eye5_TA_tex_txt[];
extern unsigned char pla_1_eye6_TA_tex_txt[];
extern unsigned char pla_1_eye7_TA_tex_txt[];
extern unsigned char pla_1_eye8_TA_tex_txt[];
extern unsigned char pla_1_mouth1_TA_tex_txt[];
extern unsigned char pla_1_mouth2_TA_tex_txt[];
extern unsigned char pla_1_mouth3_TA_tex_txt[];
extern unsigned char pla_1_mouth4_TA_tex_txt[];
extern unsigned char pla_1_mouth5_TA_tex_txt[];
extern unsigned char pla_1_mouth6_TA_tex_txt[];
extern unsigned char pla_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_plb_1;
extern unsigned short plb_1_pal[];
extern unsigned char plb_1_eye1_TA_tex_txt[];
extern unsigned char plb_1_eye2_TA_tex_txt[];
extern unsigned char plb_1_eye3_TA_tex_txt[];
extern unsigned char plb_1_eye4_TA_tex_txt[];
extern unsigned char plb_1_eye5_TA_tex_txt[];
extern unsigned char plb_1_eye6_TA_tex_txt[];
extern unsigned char plb_1_eye7_TA_tex_txt[];
extern unsigned char plb_1_eye8_TA_tex_txt[];
extern unsigned char plb_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_pgb_1;
extern unsigned short pgb_1_pal[];
extern unsigned char pgb_1_eye1_TA_tex_txt[];
extern unsigned char pgb_1_eye2_TA_tex_txt[];
extern unsigned char pgb_1_eye3_TA_tex_txt[];
extern unsigned char pgb_1_eye4_TA_tex_txt[];
extern unsigned char pgb_1_eye5_TA_tex_txt[];
extern unsigned char pgb_1_eye6_TA_tex_txt[];
extern unsigned char pgb_1_eye7_TA_tex_txt[];
extern unsigned char pgb_1_eye8_TA_tex_txt[];
extern unsigned char pgb_1_tmem_txt[];
extern unsigned short fox_1_pal[];
extern unsigned char fox_1_eye1_TA_tex_txt[];
extern unsigned char fox_1_eye2_TA_tex_txt[];
extern unsigned char fox_1_eye3_TA_tex_txt[];
extern unsigned char fox_1_eye4_TA_tex_txt[];
extern unsigned char fox_1_eye5_TA_tex_txt[];
extern unsigned char fox_1_eye6_TA_tex_txt[];
extern unsigned char fox_1_eye7_TA_tex_txt[];
extern unsigned char fox_1_eye8_TA_tex_txt[];
extern unsigned char fox_1_tmem_txt[];
extern unsigned short rcn_1_pal[];
extern unsigned char rcn_1_eye1_TA_tex_txt[];
extern unsigned char rcn_1_eye2_TA_tex_txt[];
extern unsigned char rcn_1_eye3_TA_tex_txt[];
extern unsigned char rcn_1_eye4_TA_tex_txt[];
extern unsigned char rcn_1_eye5_TA_tex_txt[];
extern unsigned char rcn_1_eye6_TA_tex_txt[];
extern unsigned char rcn_1_eye7_TA_tex_txt[];
extern unsigned char rcn_1_eye8_TA_tex_txt[];
extern unsigned char rcn_1_tmem_txt[];
extern unsigned short rcc_1_pal[];
extern unsigned char rcc_1_eye1_TA_tex_txt[];
extern unsigned char rcc_1_eye2_TA_tex_txt[];
extern unsigned char rcc_1_eye3_TA_tex_txt[];
extern unsigned char rcc_1_eye4_TA_tex_txt[];
extern unsigned char rcc_1_eye5_TA_tex_txt[];
extern unsigned char rcc_1_eye6_TA_tex_txt[];
extern unsigned char rcc_1_eye7_TA_tex_txt[];
extern unsigned char rcc_1_eye8_TA_tex_txt[];
extern unsigned char rcc_1_tmem_txt[];
extern unsigned short rcs_1_pal[];
extern unsigned char rcs_1_eye1_TA_tex_txt[];
extern unsigned char rcs_1_eye2_TA_tex_txt[];
extern unsigned char rcs_1_eye3_TA_tex_txt[];
extern unsigned char rcs_1_eye4_TA_tex_txt[];
extern unsigned char rcs_1_eye5_TA_tex_txt[];
extern unsigned char rcs_1_eye6_TA_tex_txt[];
extern unsigned char rcs_1_eye7_TA_tex_txt[];
extern unsigned char rcs_1_eye8_TA_tex_txt[];
extern unsigned char rcs_1_tmem_txt[];
extern unsigned short rcd_1_pal[];
extern unsigned char rcd_1_eye1_TA_tex_txt[];
extern unsigned char rcd_1_eye2_TA_tex_txt[];
extern unsigned char rcd_1_eye3_TA_tex_txt[];
extern unsigned char rcd_1_eye4_TA_tex_txt[];
extern unsigned char rcd_1_eye5_TA_tex_txt[];
extern unsigned char rcd_1_eye6_TA_tex_txt[];
extern unsigned char rcd_1_eye7_TA_tex_txt[];
extern unsigned char rcd_1_eye8_TA_tex_txt[];
extern unsigned char rcd_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_end_1;
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short rcn_1_pal[];
extern unsigned char rcn_1_eye1_TA_tex_txt[];
extern unsigned char rcn_1_eye2_TA_tex_txt[];
extern unsigned char rcn_1_eye3_TA_tex_txt[];
extern unsigned char rcn_1_eye4_TA_tex_txt[];
extern unsigned char rcn_1_eye5_TA_tex_txt[];
extern unsigned char rcn_1_eye6_TA_tex_txt[];
extern unsigned char rcn_1_eye7_TA_tex_txt[];
extern unsigned char rcn_1_eye8_TA_tex_txt[];
extern unsigned char rcn_1_tmem_txt[];
extern unsigned short rcc_1_pal[];
extern unsigned char rcc_1_eye1_TA_tex_txt[];
extern unsigned char rcc_1_eye2_TA_tex_txt[];
extern unsigned char rcc_1_eye3_TA_tex_txt[];
extern unsigned char rcc_1_eye4_TA_tex_txt[];
extern unsigned char rcc_1_eye5_TA_tex_txt[];
extern unsigned char rcc_1_eye6_TA_tex_txt[];
extern unsigned char rcc_1_eye7_TA_tex_txt[];
extern unsigned char rcc_1_eye8_TA_tex_txt[];
extern unsigned char rcc_1_tmem_txt[];
extern unsigned short rcs_1_pal[];
extern unsigned char rcs_1_eye1_TA_tex_txt[];
extern unsigned char rcs_1_eye2_TA_tex_txt[];
extern unsigned char rcs_1_eye3_TA_tex_txt[];
extern unsigned char rcs_1_eye4_TA_tex_txt[];
extern unsigned char rcs_1_eye5_TA_tex_txt[];
extern unsigned char rcs_1_eye6_TA_tex_txt[];
extern unsigned char rcs_1_eye7_TA_tex_txt[];
extern unsigned char rcs_1_eye8_TA_tex_txt[];
extern unsigned char rcs_1_tmem_txt[];
extern unsigned short rcd_1_pal[];
extern unsigned char rcd_1_eye1_TA_tex_txt[];
extern unsigned char rcd_1_eye2_TA_tex_txt[];
extern unsigned char rcd_1_eye3_TA_tex_txt[];
extern unsigned char rcd_1_eye4_TA_tex_txt[];
extern unsigned char rcd_1_eye5_TA_tex_txt[];
extern unsigned char rcd_1_eye6_TA_tex_txt[];
extern unsigned char rcd_1_eye7_TA_tex_txt[];
extern unsigned char rcd_1_eye8_TA_tex_txt[];
extern unsigned char rcd_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_bev_1;
extern unsigned short bev_1_pal[];
extern unsigned char bev_1_eye1_TA_tex_txt[];
extern unsigned char bev_1_eye2_TA_tex_txt[];
extern unsigned char bev_1_eye3_TA_tex_txt[];
extern unsigned char bev_1_eye4_TA_tex_txt[];
extern unsigned char bev_1_eye5_TA_tex_txt[];
extern unsigned char bev_1_eye6_TA_tex_txt[];
extern unsigned char bev_1_eye7_TA_tex_txt[];
extern unsigned char bev_1_eye8_TA_tex_txt[];
extern unsigned char bev_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_rcf_1;
extern unsigned short rcf_1_pal[];
extern unsigned char rcf_1_eye1_TA_tex_txt[];
extern unsigned char rcf_1_eye2_TA_tex_txt[];
extern unsigned char rcf_1_eye3_TA_tex_txt[];
extern unsigned char rcf_1_eye4_TA_tex_txt[];
extern unsigned char rcf_1_eye5_TA_tex_txt[];
extern unsigned char rcf_1_eye6_TA_tex_txt[];
extern unsigned char rcf_1_eye7_TA_tex_txt[];
extern unsigned char rcf_1_eye8_TA_tex_txt[];
extern unsigned char rcf_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_pkn_1;
extern unsigned short pkn_1_pal[];
extern unsigned char pkn_1_tmem_txt[];
extern unsigned short pkn_1_pal[];
extern unsigned char pkn_1_tmem_txt[];
extern unsigned short pkn_1_pal[];
extern unsigned char pkn_1_tmem_txt[];
extern unsigned short pkn_1_pal[];
extern unsigned char pkn_1_tmem_txt[];
extern unsigned short pkn_1_pal[];
extern unsigned char pkn_1_tmem_txt[];
extern unsigned short pkn_1_pal[];
extern unsigned char pkn_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_lrc_1;
extern unsigned short lrc_1_pal[];
extern unsigned char lrc_1_eye1_TA_tex_txt[];
extern unsigned char lrc_1_eye2_TA_tex_txt[];
extern unsigned char lrc_1_eye3_TA_tex_txt[];
extern unsigned char lrc_1_eye4_TA_tex_txt[];
extern unsigned char lrc_1_eye5_TA_tex_txt[];
extern unsigned char lrc_1_eye6_TA_tex_txt[];
extern unsigned char lrc_1_eye7_TA_tex_txt[];
extern unsigned char lrc_1_eye8_TA_tex_txt[];
extern unsigned char lrc_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_fob_1;
extern unsigned short fob_1_pal[];
extern unsigned char fob_1_eye1_TA_tex_txt[];
extern unsigned char fob_1_eye2_TA_tex_txt[];
extern unsigned char fob_1_eye3_TA_tex_txt[];
extern unsigned char fob_1_eye4_TA_tex_txt[];
extern unsigned char fob_1_eye5_TA_tex_txt[];
extern unsigned char fob_1_eye6_TA_tex_txt[];
extern unsigned char fob_1_eye7_TA_tex_txt[];
extern unsigned char fob_1_eye8_TA_tex_txt[];
extern unsigned char fob_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short lrc_1_pal[];
extern unsigned char lrc_1_eye1_TA_tex_txt[];
extern unsigned char lrc_1_eye2_TA_tex_txt[];
extern unsigned char lrc_1_eye3_TA_tex_txt[];
extern unsigned char lrc_1_eye4_TA_tex_txt[];
extern unsigned char lrc_1_eye5_TA_tex_txt[];
extern unsigned char lrc_1_eye6_TA_tex_txt[];
extern unsigned char lrc_1_eye7_TA_tex_txt[];
extern unsigned char lrc_1_eye8_TA_tex_txt[];
extern unsigned char lrc_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_kab_1;
extern unsigned short kab_1_pal[];
extern unsigned char kab_1_eye1_TA_tex_txt[];
extern unsigned char kab_1_eye2_TA_tex_txt[];
extern unsigned char kab_1_eye3_TA_tex_txt[];
extern unsigned char kab_1_eye4_TA_tex_txt[];
extern unsigned char kab_1_eye5_TA_tex_txt[];
extern unsigned char kab_1_eye6_TA_tex_txt[];
extern unsigned char kab_1_eye7_TA_tex_txt[];
extern unsigned char kab_1_eye8_TA_tex_txt[];
extern unsigned char kab_1_tmem_txt[];
extern unsigned short fob_1_pal[];
extern unsigned char fob_1_eye1_TA_tex_txt[];
extern unsigned char fob_1_eye2_TA_tex_txt[];
extern unsigned char fob_1_eye3_TA_tex_txt[];
extern unsigned char fob_1_eye4_TA_tex_txt[];
extern unsigned char fob_1_eye5_TA_tex_txt[];
extern unsigned char fob_1_eye6_TA_tex_txt[];
extern unsigned char fob_1_eye7_TA_tex_txt[];
extern unsigned char fob_1_eye8_TA_tex_txt[];
extern unsigned char fob_1_tmem_txt[];
extern unsigned short rcf_1_pal[];
extern unsigned char rcf_1_eye1_TA_tex_txt[];
extern unsigned char rcf_1_eye2_TA_tex_txt[];
extern unsigned char rcf_1_eye3_TA_tex_txt[];
extern unsigned char rcf_1_eye4_TA_tex_txt[];
extern unsigned char rcf_1_eye5_TA_tex_txt[];
extern unsigned char rcf_1_eye6_TA_tex_txt[];
extern unsigned char rcf_1_eye7_TA_tex_txt[];
extern unsigned char rcf_1_eye8_TA_tex_txt[];
extern unsigned char rcf_1_tmem_txt[];
extern unsigned short rcf_1_pal[];
extern unsigned char rcf_1_eye1_TA_tex_txt[];
extern unsigned char rcf_1_eye2_TA_tex_txt[];
extern unsigned char rcf_1_eye3_TA_tex_txt[];
extern unsigned char rcf_1_eye4_TA_tex_txt[];
extern unsigned char rcf_1_eye5_TA_tex_txt[];
extern unsigned char rcf_1_eye6_TA_tex_txt[];
extern unsigned char rcf_1_eye7_TA_tex_txt[];
extern unsigned char rcf_1_eye8_TA_tex_txt[];
extern unsigned char rcf_1_tmem_txt[];
extern unsigned short rcf_1_pal[];
extern unsigned char rcf_1_eye1_TA_tex_txt[];
extern unsigned char rcf_1_eye2_TA_tex_txt[];
extern unsigned char rcf_1_eye3_TA_tex_txt[];
extern unsigned char rcf_1_eye4_TA_tex_txt[];
extern unsigned char rcf_1_eye5_TA_tex_txt[];
extern unsigned char rcf_1_eye6_TA_tex_txt[];
extern unsigned char rcf_1_eye7_TA_tex_txt[];
extern unsigned char rcf_1_eye8_TA_tex_txt[];
extern unsigned char rcf_1_tmem_txt[];
extern unsigned short bpt_1_pal[];
extern unsigned char bpt_1_eye1_TA_tex_txt[];
extern unsigned char bpt_1_eye2_TA_tex_txt[];
extern unsigned char bpt_1_eye3_TA_tex_txt[];
extern unsigned char bpt_1_eye4_TA_tex_txt[];
extern unsigned char bpt_1_eye5_TA_tex_txt[];
extern unsigned char bpt_1_eye6_TA_tex_txt[];
extern unsigned char bpt_1_eye7_TA_tex_txt[];
extern unsigned char bpt_1_eye8_TA_tex_txt[];
extern unsigned char bpt_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_mol_1;
extern unsigned short mol_1_pal[];
extern unsigned char mol_1_eye1_TA_tex_txt[];
extern unsigned char mol_1_eye2_TA_tex_txt[];
extern unsigned char mol_1_eye3_TA_tex_txt[];
extern unsigned char mol_1_eye4_TA_tex_txt[];
extern unsigned char mol_1_eye5_TA_tex_txt[];
extern unsigned char mol_1_eye6_TA_tex_txt[];
extern unsigned char mol_1_eye7_TA_tex_txt[];
extern unsigned char mol_1_eye8_TA_tex_txt[];
extern unsigned char mol_1_mouth1_TA_tex_txt[];
extern unsigned char mol_1_mouth2_TA_tex_txt[];
extern unsigned char mol_1_mouth3_TA_tex_txt[];
extern unsigned char mol_1_mouth4_TA_tex_txt[];
extern unsigned char mol_1_mouth5_TA_tex_txt[];
extern unsigned char mol_1_mouth6_TA_tex_txt[];
extern unsigned char mol_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_plj_1;
extern unsigned short plj_1_pal[];
extern unsigned char plj_1_eye1_TA_tex_txt[];
extern unsigned char plj_1_eye2_TA_tex_txt[];
extern unsigned char plj_1_eye3_TA_tex_txt[];
extern unsigned char plj_1_eye4_TA_tex_txt[];
extern unsigned char plj_1_eye5_TA_tex_txt[];
extern unsigned char plj_1_eye6_TA_tex_txt[];
extern unsigned char plj_1_eye7_TA_tex_txt[];
extern unsigned char plj_1_eye8_TA_tex_txt[];
extern unsigned char plj_1_mouth1_TA_tex_txt[];
extern unsigned char plj_1_mouth2_TA_tex_txt[];
extern unsigned char plj_1_mouth3_TA_tex_txt[];
extern unsigned char plj_1_mouth4_TA_tex_txt[];
extern unsigned char plj_1_mouth5_TA_tex_txt[];
extern unsigned char plj_1_mouth6_TA_tex_txt[];
extern unsigned char plj_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_seg_1;
extern unsigned short seg_1_pal[];
extern unsigned char seg_1_eye1_TA_tex_txt[];
extern unsigned char seg_1_eye2_TA_tex_txt[];
extern unsigned char seg_1_eye3_TA_tex_txt[];
extern unsigned char seg_1_eye4_TA_tex_txt[];
extern unsigned char seg_1_eye5_TA_tex_txt[];
extern unsigned char seg_1_eye6_TA_tex_txt[];
extern unsigned char seg_1_eye7_TA_tex_txt[];
extern unsigned char seg_1_eye8_TA_tex_txt[];
extern unsigned char seg_1_tmem_txt[];
extern unsigned short mol_1_pal[];
extern unsigned char mol_1_eye1_TA_tex_txt[];
extern unsigned char mol_1_eye2_TA_tex_txt[];
extern unsigned char mol_1_eye3_TA_tex_txt[];
extern unsigned char mol_1_eye4_TA_tex_txt[];
extern unsigned char mol_1_eye5_TA_tex_txt[];
extern unsigned char mol_1_eye6_TA_tex_txt[];
extern unsigned char mol_1_eye7_TA_tex_txt[];
extern unsigned char mol_1_eye8_TA_tex_txt[];
extern unsigned char mol_1_mouth1_TA_tex_txt[];
extern unsigned char mol_1_mouth2_TA_tex_txt[];
extern unsigned char mol_1_mouth3_TA_tex_txt[];
extern unsigned char mol_1_mouth4_TA_tex_txt[];
extern unsigned char mol_1_mouth5_TA_tex_txt[];
extern unsigned char mol_1_mouth6_TA_tex_txt[];
extern unsigned char mol_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short mnk_1_pal[];
extern unsigned char mnk_1_eye1_TA_tex_txt[];
extern unsigned char mnk_1_eye2_TA_tex_txt[];
extern unsigned char mnk_1_eye3_TA_tex_txt[];
extern unsigned char mnk_1_eye4_TA_tex_txt[];
extern unsigned char mnk_1_eye5_TA_tex_txt[];
extern unsigned char mnk_1_eye6_TA_tex_txt[];
extern unsigned char mnk_1_eye7_TA_tex_txt[];
extern unsigned char mnk_1_eye8_TA_tex_txt[];
extern unsigned char mnk_1_mouth1_TA_tex_txt[];
extern unsigned char mnk_1_mouth2_TA_tex_txt[];
extern unsigned char mnk_1_mouth3_TA_tex_txt[];
extern unsigned char mnk_1_mouth4_TA_tex_txt[];
extern unsigned char mnk_1_mouth5_TA_tex_txt[];
extern unsigned char mnk_1_mouth6_TA_tex_txt[];
extern unsigned char mnk_1_tmem_txt[];
extern unsigned short mol_1_pal[];
extern unsigned char mol_1_eye1_TA_tex_txt[];
extern unsigned char mol_1_eye2_TA_tex_txt[];
extern unsigned char mol_1_eye3_TA_tex_txt[];
extern unsigned char mol_1_eye4_TA_tex_txt[];
extern unsigned char mol_1_eye5_TA_tex_txt[];
extern unsigned char mol_1_eye6_TA_tex_txt[];
extern unsigned char mol_1_eye7_TA_tex_txt[];
extern unsigned char mol_1_eye8_TA_tex_txt[];
extern unsigned char mol_1_mouth1_TA_tex_txt[];
extern unsigned char mol_1_mouth2_TA_tex_txt[];
extern unsigned char mol_1_mouth3_TA_tex_txt[];
extern unsigned char mol_1_mouth4_TA_tex_txt[];
extern unsigned char mol_1_mouth5_TA_tex_txt[];
extern unsigned char mol_1_mouth6_TA_tex_txt[];
extern unsigned char mol_1_tmem_txt[];
extern unsigned short mol_1_pal[];
extern unsigned char mol_1_eye1_TA_tex_txt[];
extern unsigned char mol_1_eye2_TA_tex_txt[];
extern unsigned char mol_1_eye3_TA_tex_txt[];
extern unsigned char mol_1_eye4_TA_tex_txt[];
extern unsigned char mol_1_eye5_TA_tex_txt[];
extern unsigned char mol_1_eye6_TA_tex_txt[];
extern unsigned char mol_1_eye7_TA_tex_txt[];
extern unsigned char mol_1_eye8_TA_tex_txt[];
extern unsigned char mol_1_mouth1_TA_tex_txt[];
extern unsigned char mol_1_mouth2_TA_tex_txt[];
extern unsigned char mol_1_mouth3_TA_tex_txt[];
extern unsigned char mol_1_mouth4_TA_tex_txt[];
extern unsigned char mol_1_mouth5_TA_tex_txt[];
extern unsigned char mol_1_mouth6_TA_tex_txt[];
extern unsigned char mol_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short mol_1_pal[];
extern unsigned char mol_1_eye1_TA_tex_txt[];
extern unsigned char mol_1_eye2_TA_tex_txt[];
extern unsigned char mol_1_eye3_TA_tex_txt[];
extern unsigned char mol_1_eye4_TA_tex_txt[];
extern unsigned char mol_1_eye5_TA_tex_txt[];
extern unsigned char mol_1_eye6_TA_tex_txt[];
extern unsigned char mol_1_eye7_TA_tex_txt[];
extern unsigned char mol_1_eye8_TA_tex_txt[];
extern unsigned char mol_1_mouth1_TA_tex_txt[];
extern unsigned char mol_1_mouth2_TA_tex_txt[];
extern unsigned char mol_1_mouth3_TA_tex_txt[];
extern unsigned char mol_1_mouth4_TA_tex_txt[];
extern unsigned char mol_1_mouth5_TA_tex_txt[];
extern unsigned char mol_1_mouth6_TA_tex_txt[];
extern unsigned char mol_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_xsq_1;
extern unsigned short xsq_1_pal[];
extern unsigned char xsq_1_eye1_TA_tex_txt[];
extern unsigned char xsq_1_eye2_TA_tex_txt[];
extern unsigned char xsq_1_eye3_TA_tex_txt[];
extern unsigned char xsq_1_eye4_TA_tex_txt[];
extern unsigned char xsq_1_eye5_TA_tex_txt[];
extern unsigned char xsq_1_eye6_TA_tex_txt[];
extern unsigned char xsq_1_eye7_TA_tex_txt[];
extern unsigned char xsq_1_eye8_TA_tex_txt[];
extern unsigned char xsq_1_mouth1_TA_tex_txt[];
extern unsigned char xsq_1_mouth2_TA_tex_txt[];
extern unsigned char xsq_1_mouth3_TA_tex_txt[];
extern unsigned char xsq_1_mouth4_TA_tex_txt[];
extern unsigned char xsq_1_mouth5_TA_tex_txt[];
extern unsigned char xsq_1_mouth6_TA_tex_txt[];
extern unsigned char xsq_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_owl_1;
extern unsigned short owl_1_pal[];
extern unsigned char owl_1_eye1_TA_tex_txt[];
extern unsigned char owl_1_eye2_TA_tex_txt[];
extern unsigned char owl_1_eye3_TA_tex_txt[];
extern unsigned char owl_1_eye4_TA_tex_txt[];
extern unsigned char owl_1_eye5_TA_tex_txt[];
extern unsigned char owl_1_eye6_TA_tex_txt[];
extern unsigned char owl_1_eye7_TA_tex_txt[];
extern unsigned char owl_1_eye8_TA_tex_txt[];
extern unsigned char owl_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_ttl_1;
extern unsigned short ttl_1_pal[];
extern unsigned char ttl_1_eye1_TA_tex_txt[];
extern unsigned char ttl_1_eye2_TA_tex_txt[];
extern unsigned char ttl_1_eye3_TA_tex_txt[];
extern unsigned char ttl_1_eye4_TA_tex_txt[];
extern unsigned char ttl_1_eye5_TA_tex_txt[];
extern unsigned char ttl_1_eye6_TA_tex_txt[];
extern unsigned char ttl_1_eye7_TA_tex_txt[];
extern unsigned char ttl_1_eye8_TA_tex_txt[];
extern unsigned char ttl_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_gst_1;
extern unsigned short gst_1_pal[];
extern unsigned char gst_1_eye1_TA_tex_txt[];
extern unsigned char gst_1_eye2_TA_tex_txt[];
extern unsigned char gst_1_eye3_TA_tex_txt[];
extern unsigned char gst_1_eye4_TA_tex_txt[];
extern unsigned char gst_1_eye5_TA_tex_txt[];
extern unsigned char gst_1_eye6_TA_tex_txt[];
extern unsigned char gst_1_eye7_TA_tex_txt[];
extern unsigned char gst_1_eye8_TA_tex_txt[];
extern unsigned char gst_1_mouth1_TA_tex_txt[];
extern unsigned char gst_1_mouth2_TA_tex_txt[];
extern unsigned char gst_1_mouth3_TA_tex_txt[];
extern unsigned char gst_1_mouth4_TA_tex_txt[];
extern unsigned char gst_1_mouth5_TA_tex_txt[];
extern unsigned char gst_1_mouth6_TA_tex_txt[];
extern unsigned char gst_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_hgh_1;
extern unsigned short hgh_1_pal[];
extern unsigned char hgh_1_eye1_TA_tex_txt[];
extern unsigned char hgh_1_eye2_TA_tex_txt[];
extern unsigned char hgh_1_eye3_TA_tex_txt[];
extern unsigned char hgh_1_eye4_TA_tex_txt[];
extern unsigned char hgh_1_eye5_TA_tex_txt[];
extern unsigned char hgh_1_eye6_TA_tex_txt[];
extern unsigned char hgh_1_eye7_TA_tex_txt[];
extern unsigned char hgh_1_eye8_TA_tex_txt[];
extern unsigned char hgh_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_hgs_1;
extern unsigned short hgs_1_pal[];
extern unsigned char hgs_1_eye1_TA_tex_txt[];
extern unsigned char hgs_1_eye2_TA_tex_txt[];
extern unsigned char hgs_1_eye3_TA_tex_txt[];
extern unsigned char hgs_1_eye4_TA_tex_txt[];
extern unsigned char hgs_1_eye5_TA_tex_txt[];
extern unsigned char hgs_1_eye6_TA_tex_txt[];
extern unsigned char hgs_1_eye7_TA_tex_txt[];
extern unsigned char hgs_1_eye8_TA_tex_txt[];
extern unsigned char hgs_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_wip_1;
extern unsigned short wip_1_pal[];
extern unsigned char wip_1_eye1_TA_tex_txt[];
extern unsigned char wip_1_eye2_TA_tex_txt[];
extern unsigned char wip_1_eye3_TA_tex_txt[];
extern unsigned char wip_1_eye4_TA_tex_txt[];
extern unsigned char wip_1_eye5_TA_tex_txt[];
extern unsigned char wip_1_eye6_TA_tex_txt[];
extern unsigned char wip_1_eye7_TA_tex_txt[];
extern unsigned char wip_1_eye8_TA_tex_txt[];
extern unsigned char wip_1_mouth1_TA_tex_txt[];
extern unsigned char wip_1_mouth2_TA_tex_txt[];
extern unsigned char wip_1_mouth3_TA_tex_txt[];
extern unsigned char wip_1_mouth4_TA_tex_txt[];
extern unsigned char wip_1_mouth5_TA_tex_txt[];
extern unsigned char wip_1_mouth6_TA_tex_txt[];
extern unsigned char wip_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short ttl_1_pal[];
extern unsigned char ttl_1_eye1_TA_tex_txt[];
extern unsigned char ttl_1_eye2_TA_tex_txt[];
extern unsigned char ttl_1_eye3_TA_tex_txt[];
extern unsigned char ttl_1_eye4_TA_tex_txt[];
extern unsigned char ttl_1_eye5_TA_tex_txt[];
extern unsigned char ttl_1_eye6_TA_tex_txt[];
extern unsigned char ttl_1_eye7_TA_tex_txt[];
extern unsigned char ttl_1_eye8_TA_tex_txt[];
extern unsigned char ttl_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_mka_1;
extern unsigned short mka_1_pal[];
extern unsigned char mka_1_tmem_txt[];
extern unsigned short mka_1_pal[];
extern unsigned char mka_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short ttl_1_pal[];
extern unsigned char ttl_1_eye1_TA_tex_txt[];
extern unsigned char ttl_1_eye2_TA_tex_txt[];
extern unsigned char ttl_1_eye3_TA_tex_txt[];
extern unsigned char ttl_1_eye4_TA_tex_txt[];
extern unsigned char ttl_1_eye5_TA_tex_txt[];
extern unsigned char ttl_1_eye6_TA_tex_txt[];
extern unsigned char ttl_1_eye7_TA_tex_txt[];
extern unsigned char ttl_1_eye8_TA_tex_txt[];
extern unsigned char ttl_1_tmem_txt[];
extern unsigned short pkn_1_pal[];
extern unsigned char pkn_1_tmem_txt[];
extern unsigned short mnk_1_pal[];
extern unsigned char mnk_1_eye1_TA_tex_txt[];
extern unsigned char mnk_1_eye2_TA_tex_txt[];
extern unsigned char mnk_1_eye3_TA_tex_txt[];
extern unsigned char mnk_1_eye4_TA_tex_txt[];
extern unsigned char mnk_1_eye5_TA_tex_txt[];
extern unsigned char mnk_1_eye6_TA_tex_txt[];
extern unsigned char mnk_1_eye7_TA_tex_txt[];
extern unsigned char mnk_1_eye8_TA_tex_txt[];
extern unsigned char mnk_1_mouth1_TA_tex_txt[];
extern unsigned char mnk_1_mouth2_TA_tex_txt[];
extern unsigned char mnk_1_mouth3_TA_tex_txt[];
extern unsigned char mnk_1_mouth4_TA_tex_txt[];
extern unsigned char mnk_1_mouth5_TA_tex_txt[];
extern unsigned char mnk_1_mouth6_TA_tex_txt[];
extern unsigned char mnk_1_tmem_txt[];
extern unsigned short seg_1_pal[];
extern unsigned char seg_1_eye1_TA_tex_txt[];
extern unsigned char seg_1_eye2_TA_tex_txt[];
extern unsigned char seg_1_eye3_TA_tex_txt[];
extern unsigned char seg_1_eye4_TA_tex_txt[];
extern unsigned char seg_1_eye5_TA_tex_txt[];
extern unsigned char seg_1_eye6_TA_tex_txt[];
extern unsigned char seg_1_eye7_TA_tex_txt[];
extern unsigned char seg_1_eye8_TA_tex_txt[];
extern unsigned char seg_1_tmem_txt[];
extern unsigned short mol_1_pal[];
extern unsigned char mol_1_eye1_TA_tex_txt[];
extern unsigned char mol_1_eye2_TA_tex_txt[];
extern unsigned char mol_1_eye3_TA_tex_txt[];
extern unsigned char mol_1_eye4_TA_tex_txt[];
extern unsigned char mol_1_eye5_TA_tex_txt[];
extern unsigned char mol_1_eye6_TA_tex_txt[];
extern unsigned char mol_1_eye7_TA_tex_txt[];
extern unsigned char mol_1_eye8_TA_tex_txt[];
extern unsigned char mol_1_mouth1_TA_tex_txt[];
extern unsigned char mol_1_mouth2_TA_tex_txt[];
extern unsigned char mol_1_mouth3_TA_tex_txt[];
extern unsigned char mol_1_mouth4_TA_tex_txt[];
extern unsigned char mol_1_mouth5_TA_tex_txt[];
extern unsigned char mol_1_mouth6_TA_tex_txt[];
extern unsigned char mol_1_tmem_txt[];
extern unsigned short mol_1_pal[];
extern unsigned char mol_1_eye1_TA_tex_txt[];
extern unsigned char mol_1_eye2_TA_tex_txt[];
extern unsigned char mol_1_eye3_TA_tex_txt[];
extern unsigned char mol_1_eye4_TA_tex_txt[];
extern unsigned char mol_1_eye5_TA_tex_txt[];
extern unsigned char mol_1_eye6_TA_tex_txt[];
extern unsigned char mol_1_eye7_TA_tex_txt[];
extern unsigned char mol_1_eye8_TA_tex_txt[];
extern unsigned char mol_1_mouth1_TA_tex_txt[];
extern unsigned char mol_1_mouth2_TA_tex_txt[];
extern unsigned char mol_1_mouth3_TA_tex_txt[];
extern unsigned char mol_1_mouth4_TA_tex_txt[];
extern unsigned char mol_1_mouth5_TA_tex_txt[];
extern unsigned char mol_1_mouth6_TA_tex_txt[];
extern unsigned char mol_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_mob_1;
extern unsigned short mob_1_pal[];
extern unsigned char mob_1_eye1_TA_tex_txt[];
extern unsigned char mob_1_eye2_TA_tex_txt[];
extern unsigned char mob_1_eye3_TA_tex_txt[];
extern unsigned char mob_1_eye4_TA_tex_txt[];
extern unsigned char mob_1_eye5_TA_tex_txt[];
extern unsigned char mob_1_eye6_TA_tex_txt[];
extern unsigned char mob_1_eye7_TA_tex_txt[];
extern unsigned char mob_1_eye8_TA_tex_txt[];
extern unsigned char mob_1_mouth1_TA_tex_txt[];
extern unsigned char mob_1_mouth2_TA_tex_txt[];
extern unsigned char mob_1_mouth3_TA_tex_txt[];
extern unsigned char mob_1_mouth4_TA_tex_txt[];
extern unsigned char mob_1_mouth5_TA_tex_txt[];
extern unsigned char mob_1_mouth6_TA_tex_txt[];
extern unsigned char mob_1_tmem_txt[];
extern unsigned short ttl_1_pal[];
extern unsigned char ttl_1_eye1_TA_tex_txt[];
extern unsigned char ttl_1_eye2_TA_tex_txt[];
extern unsigned char ttl_1_eye3_TA_tex_txt[];
extern unsigned char ttl_1_eye4_TA_tex_txt[];
extern unsigned char ttl_1_eye5_TA_tex_txt[];
extern unsigned char ttl_1_eye6_TA_tex_txt[];
extern unsigned char ttl_1_eye7_TA_tex_txt[];
extern unsigned char ttl_1_eye8_TA_tex_txt[];
extern unsigned char ttl_1_tmem_txt[];
extern unsigned short mol_1_pal[];
extern unsigned char mol_1_eye1_TA_tex_txt[];
extern unsigned char mol_1_eye2_TA_tex_txt[];
extern unsigned char mol_1_eye3_TA_tex_txt[];
extern unsigned char mol_1_eye4_TA_tex_txt[];
extern unsigned char mol_1_eye5_TA_tex_txt[];
extern unsigned char mol_1_eye6_TA_tex_txt[];
extern unsigned char mol_1_eye7_TA_tex_txt[];
extern unsigned char mol_1_eye8_TA_tex_txt[];
extern unsigned char mol_1_mouth1_TA_tex_txt[];
extern unsigned char mol_1_mouth2_TA_tex_txt[];
extern unsigned char mol_1_mouth3_TA_tex_txt[];
extern unsigned char mol_1_mouth4_TA_tex_txt[];
extern unsigned char mol_1_mouth5_TA_tex_txt[];
extern unsigned char mol_1_mouth6_TA_tex_txt[];
extern unsigned char mol_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_mos_1;
extern unsigned short mos_1_pal[];
extern unsigned char mos_1_eye1_TA_tex_txt[];
extern unsigned char mos_1_eye2_TA_tex_txt[];
extern unsigned char mos_1_eye3_TA_tex_txt[];
extern unsigned char mos_1_eye4_TA_tex_txt[];
extern unsigned char mos_1_eye5_TA_tex_txt[];
extern unsigned char mos_1_eye6_TA_tex_txt[];
extern unsigned char mos_1_eye7_TA_tex_txt[];
extern unsigned char mos_1_eye8_TA_tex_txt[];
extern unsigned char mos_1_mouth1_TA_tex_txt[];
extern unsigned char mos_1_mouth2_TA_tex_txt[];
extern unsigned char mos_1_mouth3_TA_tex_txt[];
extern unsigned char mos_1_mouth4_TA_tex_txt[];
extern unsigned char mos_1_mouth5_TA_tex_txt[];
extern unsigned char mos_1_mouth6_TA_tex_txt[];
extern unsigned char mos_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short ttl_1_pal[];
extern unsigned char ttl_1_eye1_TA_tex_txt[];
extern unsigned char ttl_1_eye2_TA_tex_txt[];
extern unsigned char ttl_1_eye3_TA_tex_txt[];
extern unsigned char ttl_1_eye4_TA_tex_txt[];
extern unsigned char ttl_1_eye5_TA_tex_txt[];
extern unsigned char ttl_1_eye6_TA_tex_txt[];
extern unsigned char ttl_1_eye7_TA_tex_txt[];
extern unsigned char ttl_1_eye8_TA_tex_txt[];
extern unsigned char ttl_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_tuk_1;
extern unsigned short tuk_1_pal[];
extern unsigned char tuk_1_eye1_TA_tex_txt[];
extern unsigned char tuk_1_eye2_TA_tex_txt[];
extern unsigned char tuk_1_eye3_TA_tex_txt[];
extern unsigned char tuk_1_eye4_TA_tex_txt[];
extern unsigned char tuk_1_eye5_TA_tex_txt[];
extern unsigned char tuk_1_eye6_TA_tex_txt[];
extern unsigned char tuk_1_eye7_TA_tex_txt[];
extern unsigned char tuk_1_eye8_TA_tex_txt[];
extern unsigned char tuk_1_tmem_txt[];
extern cKF_Skeleton_R_c cKF_bs_r_hem_1;
extern unsigned short hem_1_pal[];
extern unsigned char hem_1_tmem_txt[];
extern unsigned short end_1_pal[];
extern unsigned char end_1_eye1_TA_tex_txt[];
extern unsigned char end_1_eye2_TA_tex_txt[];
extern unsigned char end_1_eye3_TA_tex_txt[];
extern unsigned char end_1_eye4_TA_tex_txt[];
extern unsigned char end_1_eye5_TA_tex_txt[];
extern unsigned char end_1_eye6_TA_tex_txt[];
extern unsigned char end_1_eye7_TA_tex_txt[];
extern unsigned char end_1_eye8_TA_tex_txt[];
extern unsigned char end_1_mouth1_TA_tex_txt[];
extern unsigned char end_1_mouth2_TA_tex_txt[];
extern unsigned char end_1_mouth3_TA_tex_txt[];
extern unsigned char end_1_mouth4_TA_tex_txt[];
extern unsigned char end_1_mouth5_TA_tex_txt[];
extern unsigned char end_1_mouth6_TA_tex_txt[];
extern unsigned char end_1_tmem_txt[];

extern aNPC_draw_data_c npc_draw_data_tbl[] = {
    {
        ACTOR_OBJ_BANK_133,
        ACTOR_OBJ_BANK_134,
        &cKF_bs_r_cat_1,
        {
            cat_1_tmem_txt,
            cat_1_pal,
            {
                cat_1_eye1_TA_tex_txt,
                cat_1_eye2_TA_tex_txt,
                cat_1_eye3_TA_tex_txt,
                cat_1_eye4_TA_tex_txt,
                cat_1_eye5_TA_tex_txt,
                cat_1_eye6_TA_tex_txt,
                cat_1_eye7_TA_tex_txt,
                cat_1_eye8_TA_tex_txt,
            },
            {
                cat_1_mouth1_TA_tex_txt,
                cat_1_mouth2_TA_tex_txt,
                cat_1_mouth3_TA_tex_txt,
                cat_1_mouth4_TA_tex_txt,
                cat_1_mouth5_TA_tex_txt,
                cat_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            128,
        },
        0.008999999612569809,
        0,
        0,
        0,
        33,
        0,
        0,
        1,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_133,
        ACTOR_OBJ_BANK_135,
        &cKF_bs_r_cat_1,
        {
            cat_2_tmem_txt,
            cat_2_pal,
            {
                cat_2_eye1_TA_tex_txt,
                cat_2_eye2_TA_tex_txt,
                cat_2_eye3_TA_tex_txt,
                cat_2_eye4_TA_tex_txt,
                cat_2_eye5_TA_tex_txt,
                cat_2_eye6_TA_tex_txt,
                cat_2_eye7_TA_tex_txt,
                cat_2_eye8_TA_tex_txt,
            },
            {
                cat_2_mouth1_TA_tex_txt,
                cat_2_mouth2_TA_tex_txt,
                cat_2_mouth3_TA_tex_txt,
                cat_2_mouth4_TA_tex_txt,
                cat_2_mouth5_TA_tex_txt,
                cat_2_mouth6_TA_tex_txt,
            },
            0,
            32,
            128,
        },
        0.008999999612569809,
        0,
        1,
        10,
        33,
        0,
        0,
        2,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_133,
        ACTOR_OBJ_BANK_136,
        &cKF_bs_r_cat_1,
        {
            cat_3_tmem_txt,
            cat_3_pal,
            {
                cat_3_eye1_TA_tex_txt,
                cat_3_eye2_TA_tex_txt,
                cat_3_eye3_TA_tex_txt,
                cat_3_eye4_TA_tex_txt,
                cat_3_eye5_TA_tex_txt,
                cat_3_eye6_TA_tex_txt,
                cat_3_eye7_TA_tex_txt,
                cat_3_eye8_TA_tex_txt,
            },
            {
                cat_3_mouth1_TA_tex_txt,
                cat_3_mouth2_TA_tex_txt,
                cat_3_mouth3_TA_tex_txt,
                cat_3_mouth4_TA_tex_txt,
                cat_3_mouth5_TA_tex_txt,
                cat_3_mouth6_TA_tex_txt,
            },
            0,
            32,
            128,
        },
        0.008999999612569809,
        0,
        2,
        12,
        33,
        0,
        0,
        3,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_133,
        ACTOR_OBJ_BANK_137,
        &cKF_bs_r_cat_1,
        {
            cat_4_tmem_txt,
            cat_4_pal,
            {
                cat_4_eye1_TA_tex_txt,
                cat_4_eye2_TA_tex_txt,
                cat_4_eye3_TA_tex_txt,
                cat_4_eye4_TA_tex_txt,
                cat_4_eye5_TA_tex_txt,
                cat_4_eye6_TA_tex_txt,
                cat_4_eye7_TA_tex_txt,
                cat_4_eye8_TA_tex_txt,
            },
            {
                cat_4_mouth1_TA_tex_txt,
                cat_4_mouth2_TA_tex_txt,
                cat_4_mouth3_TA_tex_txt,
                cat_4_mouth4_TA_tex_txt,
                cat_4_mouth5_TA_tex_txt,
                cat_4_mouth6_TA_tex_txt,
            },
            0,
            32,
            128,
        },
        0.008999999612569809,
        0,
        3,
        6,
        33,
        0,
        0,
        4,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_133,
        ACTOR_OBJ_BANK_138,
        &cKF_bs_r_cat_1,
        {
            cat_5_tmem_txt,
            cat_5_pal,
            {
                cat_5_eye1_TA_tex_txt,
                cat_5_eye2_TA_tex_txt,
                cat_5_eye3_TA_tex_txt,
                cat_5_eye4_TA_tex_txt,
                cat_5_eye5_TA_tex_txt,
                cat_5_eye6_TA_tex_txt,
                cat_5_eye7_TA_tex_txt,
                cat_5_eye8_TA_tex_txt,
            },
            {
                cat_5_mouth1_TA_tex_txt,
                cat_5_mouth2_TA_tex_txt,
                cat_5_mouth3_TA_tex_txt,
                cat_5_mouth4_TA_tex_txt,
                cat_5_mouth5_TA_tex_txt,
                cat_5_mouth6_TA_tex_txt,
            },
            0,
            32,
            128,
        },
        0.008999999612569809,
        0,
        4,
        3,
        33,
        0,
        0,
        5,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_133,
        ACTOR_OBJ_BANK_139,
        &cKF_bs_r_cat_1,
        {
            cat_6_tmem_txt,
            cat_6_pal,
            {
                cat_6_eye1_TA_tex_txt,
                cat_6_eye2_TA_tex_txt,
                cat_6_eye3_TA_tex_txt,
                cat_6_eye4_TA_tex_txt,
                cat_6_eye5_TA_tex_txt,
                cat_6_eye6_TA_tex_txt,
                cat_6_eye7_TA_tex_txt,
                cat_6_eye8_TA_tex_txt,
            },
            {
                cat_6_mouth1_TA_tex_txt,
                cat_6_mouth2_TA_tex_txt,
                cat_6_mouth3_TA_tex_txt,
                cat_6_mouth4_TA_tex_txt,
                cat_6_mouth5_TA_tex_txt,
                cat_6_mouth6_TA_tex_txt,
            },
            0,
            32,
            128,
        },
        0.008999999612569809,
        0,
        5,
        26,
        33,
        0,
        0,
        6,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_133,
        ACTOR_OBJ_BANK_140,
        &cKF_bs_r_cat_1,
        {
            cat_7_tmem_txt,
            cat_7_pal,
            {
                cat_7_eye1_TA_tex_txt,
                cat_7_eye2_TA_tex_txt,
                cat_7_eye3_TA_tex_txt,
                cat_7_eye4_TA_tex_txt,
                cat_7_eye5_TA_tex_txt,
                cat_7_eye6_TA_tex_txt,
                cat_7_eye7_TA_tex_txt,
                cat_7_eye8_TA_tex_txt,
            },
            {
                cat_7_mouth1_TA_tex_txt,
                cat_7_mouth2_TA_tex_txt,
                cat_7_mouth3_TA_tex_txt,
                cat_7_mouth4_TA_tex_txt,
                cat_7_mouth5_TA_tex_txt,
                cat_7_mouth6_TA_tex_txt,
            },
            0,
            32,
            128,
        },
        0.008999999612569809,
        0,
        6,
        13,
        33,
        0,
        0,
        7,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_133,
        ACTOR_OBJ_BANK_141,
        &cKF_bs_r_cat_1,
        {
            cat_8_tmem_txt,
            cat_8_pal,
            {
                cat_8_eye1_TA_tex_txt,
                cat_8_eye2_TA_tex_txt,
                cat_8_eye3_TA_tex_txt,
                cat_8_eye4_TA_tex_txt,
                cat_8_eye5_TA_tex_txt,
                cat_8_eye6_TA_tex_txt,
                cat_8_eye7_TA_tex_txt,
                cat_8_eye8_TA_tex_txt,
            },
            {
                cat_8_mouth1_TA_tex_txt,
                cat_8_mouth2_TA_tex_txt,
                cat_8_mouth3_TA_tex_txt,
                cat_8_mouth4_TA_tex_txt,
                cat_8_mouth5_TA_tex_txt,
                cat_8_mouth6_TA_tex_txt,
            },
            0,
            32,
            128,
        },
        0.008999999612569809,
        0,
        7,
        6,
        33,
        0,
        0,
        8,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_133,
        ACTOR_OBJ_BANK_142,
        &cKF_bs_r_cat_1,
        {
            cat_9_tmem_txt,
            cat_9_pal,
            {
                cat_9_eye1_TA_tex_txt,
                cat_9_eye2_TA_tex_txt,
                cat_9_eye3_TA_tex_txt,
                cat_9_eye4_TA_tex_txt,
                cat_9_eye5_TA_tex_txt,
                cat_9_eye6_TA_tex_txt,
                cat_9_eye7_TA_tex_txt,
                cat_9_eye8_TA_tex_txt,
            },
            {
                cat_9_mouth1_TA_tex_txt,
                cat_9_mouth2_TA_tex_txt,
                cat_9_mouth3_TA_tex_txt,
                cat_9_mouth4_TA_tex_txt,
                cat_9_mouth5_TA_tex_txt,
                cat_9_mouth6_TA_tex_txt,
            },
            0,
            32,
            128,
        },
        0.008999999612569809,
        0,
        8,
        31,
        33,
        0,
        0,
        9,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_133,
        ACTOR_OBJ_BANK_143,
        &cKF_bs_r_cat_1,
        {
            cat_10_tmem_txt,
            cat_10_pal,
            {
                cat_10_eye1_TA_tex_txt,
                cat_10_eye2_TA_tex_txt,
                cat_10_eye3_TA_tex_txt,
                cat_10_eye4_TA_tex_txt,
                cat_10_eye5_TA_tex_txt,
                cat_10_eye6_TA_tex_txt,
                cat_10_eye7_TA_tex_txt,
                cat_10_eye8_TA_tex_txt,
            },
            {
                cat_10_mouth1_TA_tex_txt,
                cat_10_mouth2_TA_tex_txt,
                cat_10_mouth3_TA_tex_txt,
                cat_10_mouth4_TA_tex_txt,
                cat_10_mouth5_TA_tex_txt,
                cat_10_mouth6_TA_tex_txt,
            },
            0,
            32,
            128,
        },
        0.008999999612569809,
        0,
        9,
        22,
        33,
        0,
        0,
        10,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_133,
        ACTOR_OBJ_BANK_144,
        &cKF_bs_r_cat_1,
        {
            cat_11_tmem_txt,
            cat_11_pal,
            {
                cat_11_eye1_TA_tex_txt,
                cat_11_eye2_TA_tex_txt,
                cat_11_eye3_TA_tex_txt,
                cat_11_eye4_TA_tex_txt,
                cat_11_eye5_TA_tex_txt,
                cat_11_eye6_TA_tex_txt,
                cat_11_eye7_TA_tex_txt,
                cat_11_eye8_TA_tex_txt,
            },
            {
                cat_11_mouth1_TA_tex_txt,
                cat_11_mouth2_TA_tex_txt,
                cat_11_mouth3_TA_tex_txt,
                cat_11_mouth4_TA_tex_txt,
                cat_11_mouth5_TA_tex_txt,
                cat_11_mouth6_TA_tex_txt,
            },
            0,
            32,
            128,
        },
        0.008999999612569809,
        0,
        10,
        9,
        33,
        0,
        0,
        11,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_133,
        ACTOR_OBJ_BANK_145,
        &cKF_bs_r_cat_1,
        {
            cat_12_tmem_txt,
            cat_12_pal,
            {
                cat_12_eye1_TA_tex_txt,
                cat_12_eye2_TA_tex_txt,
                cat_12_eye3_TA_tex_txt,
                cat_12_eye4_TA_tex_txt,
                cat_12_eye5_TA_tex_txt,
                cat_12_eye6_TA_tex_txt,
                cat_12_eye7_TA_tex_txt,
                cat_12_eye8_TA_tex_txt,
            },
            {
                cat_12_mouth1_TA_tex_txt,
                cat_12_mouth2_TA_tex_txt,
                cat_12_mouth3_TA_tex_txt,
                cat_12_mouth4_TA_tex_txt,
                cat_12_mouth5_TA_tex_txt,
                cat_12_mouth6_TA_tex_txt,
            },
            0,
            32,
            128,
        },
        0.008999999612569809,
        0,
        11,
        31,
        33,
        0,
        0,
        12,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_133,
        ACTOR_OBJ_BANK_146,
        &cKF_bs_r_cat_1,
        {
            cat_13_tmem_txt,
            cat_13_pal,
            {
                cat_13_eye1_TA_tex_txt,
                cat_13_eye2_TA_tex_txt,
                cat_13_eye3_TA_tex_txt,
                cat_13_eye4_TA_tex_txt,
                cat_13_eye5_TA_tex_txt,
                cat_13_eye6_TA_tex_txt,
                cat_13_eye7_TA_tex_txt,
                cat_13_eye8_TA_tex_txt,
            },
            {
                cat_13_mouth1_TA_tex_txt,
                cat_13_mouth2_TA_tex_txt,
                cat_13_mouth3_TA_tex_txt,
                cat_13_mouth4_TA_tex_txt,
                cat_13_mouth5_TA_tex_txt,
                cat_13_mouth6_TA_tex_txt,
            },
            0,
            32,
            128,
        },
        0.008999999612569809,
        0,
        12,
        1,
        33,
        0,
        0,
        13,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_88,
        ACTOR_OBJ_BANK_89,
        &cKF_bs_r_ant_1,
        {
            ant_1_tmem_txt,
            ant_1_pal,
            {
                ant_1_eye1_TA_tex_txt,
                ant_1_eye2_TA_tex_txt,
                ant_1_eye3_TA_tex_txt,
                ant_1_eye4_TA_tex_txt,
                ant_1_eye5_TA_tex_txt,
                ant_1_eye6_TA_tex_txt,
                ant_1_eye7_TA_tex_txt,
                ant_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            32,
            0,
            152,
        },
        0.010700000450015068,
        1,
        0,
        27,
        41,
        0,
        0,
        159,
        25,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_88,
        ACTOR_OBJ_BANK_90,
        &cKF_bs_r_ant_1,
        {
            ant_2_tmem_txt,
            ant_2_pal,
            {
                ant_2_eye1_TA_tex_txt,
                ant_2_eye2_TA_tex_txt,
                ant_2_eye3_TA_tex_txt,
                ant_2_eye4_TA_tex_txt,
                ant_2_eye5_TA_tex_txt,
                ant_2_eye6_TA_tex_txt,
                ant_2_eye7_TA_tex_txt,
                ant_2_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            32,
            0,
            152,
        },
        0.010700000450015068,
        1,
        1,
        8,
        41,
        0,
        0,
        160,
        25,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_88,
        ACTOR_OBJ_BANK_91,
        &cKF_bs_r_ant_1,
        {
            ant_3_tmem_txt,
            ant_3_pal,
            {
                ant_3_eye1_TA_tex_txt,
                ant_3_eye2_TA_tex_txt,
                ant_3_eye3_TA_tex_txt,
                ant_3_eye4_TA_tex_txt,
                ant_3_eye5_TA_tex_txt,
                ant_3_eye6_TA_tex_txt,
                ant_3_eye7_TA_tex_txt,
                ant_3_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            32,
            0,
            152,
        },
        0.010700000450015068,
        1,
        2,
        17,
        41,
        0,
        0,
        161,
        25,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_88,
        ACTOR_OBJ_BANK_92,
        &cKF_bs_r_ant_1,
        {
            ant_4_tmem_txt,
            ant_4_pal,
            {
                ant_4_eye1_TA_tex_txt,
                ant_4_eye2_TA_tex_txt,
                ant_4_eye3_TA_tex_txt,
                ant_4_eye4_TA_tex_txt,
                ant_4_eye5_TA_tex_txt,
                ant_4_eye6_TA_tex_txt,
                ant_4_eye7_TA_tex_txt,
                ant_4_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            32,
            0,
            152,
        },
        0.010700000450015068,
        1,
        3,
        21,
        41,
        0,
        0,
        162,
        25,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_88,
        ACTOR_OBJ_BANK_93,
        &cKF_bs_r_ant_1,
        {
            ant_5_tmem_txt,
            ant_5_pal,
            {
                ant_5_eye1_TA_tex_txt,
                ant_5_eye2_TA_tex_txt,
                ant_5_eye3_TA_tex_txt,
                ant_5_eye4_TA_tex_txt,
                ant_5_eye5_TA_tex_txt,
                ant_5_eye6_TA_tex_txt,
                ant_5_eye7_TA_tex_txt,
                ant_5_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            32,
            0,
            152,
        },
        0.010700000450015068,
        1,
        4,
        26,
        41,
        0,
        0,
        163,
        25,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_96,
        ACTOR_OBJ_BANK_97,
        &cKF_bs_r_bea_1,
        {
            bea_1_tmem_txt,
            bea_1_pal,
            {
                bea_1_eye1_TA_tex_txt,
                bea_1_eye2_TA_tex_txt,
                bea_1_eye3_TA_tex_txt,
                bea_1_eye4_TA_tex_txt,
                bea_1_eye5_TA_tex_txt,
                bea_1_eye6_TA_tex_txt,
                bea_1_eye7_TA_tex_txt,
                bea_1_eye8_TA_tex_txt,
            },
            {
                bea_1_mouth1_TA_tex_txt,
                bea_1_mouth2_TA_tex_txt,
                bea_1_mouth3_TA_tex_txt,
                bea_1_mouth4_TA_tex_txt,
                bea_1_mouth5_TA_tex_txt,
                bea_1_mouth6_TA_tex_txt,
            },
            64,
            96,
            176,
        },
        0.008999999612569809,
        0,
        0,
        21,
        47,
        0,
        0,
        27,
        20,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_96,
        ACTOR_OBJ_BANK_98,
        &cKF_bs_r_bea_1,
        {
            bea_2_tmem_txt,
            bea_2_pal,
            {
                bea_2_eye1_TA_tex_txt,
                bea_2_eye2_TA_tex_txt,
                bea_2_eye3_TA_tex_txt,
                bea_2_eye4_TA_tex_txt,
                bea_2_eye5_TA_tex_txt,
                bea_2_eye6_TA_tex_txt,
                bea_2_eye7_TA_tex_txt,
                bea_2_eye8_TA_tex_txt,
            },
            {
                bea_2_mouth1_TA_tex_txt,
                bea_2_mouth2_TA_tex_txt,
                bea_2_mouth3_TA_tex_txt,
                bea_2_mouth4_TA_tex_txt,
                bea_2_mouth5_TA_tex_txt,
                bea_2_mouth6_TA_tex_txt,
            },
            64,
            96,
            176,
        },
        0.008999999612569809,
        0,
        1,
        25,
        47,
        0,
        0,
        28,
        20,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_96,
        ACTOR_OBJ_BANK_99,
        &cKF_bs_r_bea_1,
        {
            bea_3_tmem_txt,
            bea_3_pal,
            {
                bea_3_eye1_TA_tex_txt,
                bea_3_eye2_TA_tex_txt,
                bea_3_eye3_TA_tex_txt,
                bea_3_eye4_TA_tex_txt,
                bea_3_eye5_TA_tex_txt,
                bea_3_eye6_TA_tex_txt,
                bea_3_eye7_TA_tex_txt,
                bea_3_eye8_TA_tex_txt,
            },
            {
                bea_3_mouth1_TA_tex_txt,
                bea_3_mouth2_TA_tex_txt,
                bea_3_mouth3_TA_tex_txt,
                bea_3_mouth4_TA_tex_txt,
                bea_3_mouth5_TA_tex_txt,
                bea_3_mouth6_TA_tex_txt,
            },
            64,
            96,
            176,
        },
        0.008999999612569809,
        0,
        2,
        18,
        47,
        0,
        0,
        29,
        20,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_96,
        ACTOR_OBJ_BANK_101,
        &cKF_bs_r_bea_1,
        {
            bea_5_tmem_txt,
            bea_5_pal,
            {
                bea_5_eye1_TA_tex_txt,
                bea_5_eye2_TA_tex_txt,
                bea_5_eye3_TA_tex_txt,
                bea_5_eye4_TA_tex_txt,
                bea_5_eye5_TA_tex_txt,
                bea_5_eye6_TA_tex_txt,
                bea_5_eye7_TA_tex_txt,
                bea_5_eye8_TA_tex_txt,
            },
            {
                bea_5_mouth1_TA_tex_txt,
                bea_5_mouth2_TA_tex_txt,
                bea_5_mouth3_TA_tex_txt,
                bea_5_mouth4_TA_tex_txt,
                bea_5_mouth5_TA_tex_txt,
                bea_5_mouth6_TA_tex_txt,
            },
            64,
            96,
            176,
        },
        0.008999999612569809,
        0,
        4,
        3,
        47,
        0,
        0,
        31,
        20,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_96,
        ACTOR_OBJ_BANK_102,
        &cKF_bs_r_bea_1,
        {
            bea_6_tmem_txt,
            bea_6_pal,
            {
                bea_6_eye1_TA_tex_txt,
                bea_6_eye2_TA_tex_txt,
                bea_6_eye3_TA_tex_txt,
                bea_6_eye4_TA_tex_txt,
                bea_6_eye5_TA_tex_txt,
                bea_6_eye6_TA_tex_txt,
                bea_6_eye7_TA_tex_txt,
                bea_6_eye8_TA_tex_txt,
            },
            {
                bea_6_mouth1_TA_tex_txt,
                bea_6_mouth2_TA_tex_txt,
                bea_6_mouth3_TA_tex_txt,
                bea_6_mouth4_TA_tex_txt,
                bea_6_mouth5_TA_tex_txt,
                bea_6_mouth6_TA_tex_txt,
            },
            64,
            96,
            176,
        },
        0.008999999612569809,
        0,
        5,
        24,
        47,
        0,
        0,
        32,
        20,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_96,
        ACTOR_OBJ_BANK_103,
        &cKF_bs_r_bea_1,
        {
            bea_7_tmem_txt,
            bea_7_pal,
            {
                bea_7_eye1_TA_tex_txt,
                bea_7_eye2_TA_tex_txt,
                bea_7_eye3_TA_tex_txt,
                bea_7_eye4_TA_tex_txt,
                bea_7_eye5_TA_tex_txt,
                bea_7_eye6_TA_tex_txt,
                bea_7_eye7_TA_tex_txt,
                bea_7_eye8_TA_tex_txt,
            },
            {
                bea_7_mouth1_TA_tex_txt,
                bea_7_mouth2_TA_tex_txt,
                bea_7_mouth3_TA_tex_txt,
                bea_7_mouth4_TA_tex_txt,
                bea_7_mouth5_TA_tex_txt,
                bea_7_mouth6_TA_tex_txt,
            },
            64,
            96,
            176,
        },
        0.008999999612569809,
        0,
        6,
        27,
        47,
        0,
        0,
        33,
        20,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_96,
        ACTOR_OBJ_BANK_104,
        &cKF_bs_r_bea_1,
        {
            bea_8_tmem_txt,
            bea_8_pal,
            {
                bea_8_eye1_TA_tex_txt,
                bea_8_eye2_TA_tex_txt,
                bea_8_eye3_TA_tex_txt,
                bea_8_eye4_TA_tex_txt,
                bea_8_eye5_TA_tex_txt,
                bea_8_eye6_TA_tex_txt,
                bea_8_eye7_TA_tex_txt,
                bea_8_eye8_TA_tex_txt,
            },
            {
                bea_8_mouth1_TA_tex_txt,
                bea_8_mouth2_TA_tex_txt,
                bea_8_mouth3_TA_tex_txt,
                bea_8_mouth4_TA_tex_txt,
                bea_8_mouth5_TA_tex_txt,
                bea_8_mouth6_TA_tex_txt,
            },
            64,
            96,
            176,
        },
        0.008999999612569809,
        0,
        7,
        2,
        47,
        0,
        0,
        34,
        20,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_96,
        ACTOR_OBJ_BANK_105,
        &cKF_bs_r_bea_1,
        {
            bea_9_tmem_txt,
            bea_9_pal,
            {
                bea_9_eye1_TA_tex_txt,
                bea_9_eye2_TA_tex_txt,
                bea_9_eye3_TA_tex_txt,
                bea_9_eye4_TA_tex_txt,
                bea_9_eye5_TA_tex_txt,
                bea_9_eye6_TA_tex_txt,
                bea_9_eye7_TA_tex_txt,
                bea_9_eye8_TA_tex_txt,
            },
            {
                bea_9_mouth1_TA_tex_txt,
                bea_9_mouth2_TA_tex_txt,
                bea_9_mouth3_TA_tex_txt,
                bea_9_mouth4_TA_tex_txt,
                bea_9_mouth5_TA_tex_txt,
                bea_9_mouth6_TA_tex_txt,
            },
            64,
            96,
            176,
        },
        0.008999999612569809,
        0,
        8,
        26,
        47,
        0,
        0,
        35,
        20,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_96,
        ACTOR_OBJ_BANK_106,
        &cKF_bs_r_bea_1,
        {
            bea_10_tmem_txt,
            bea_10_pal,
            {
                bea_10_eye1_TA_tex_txt,
                bea_10_eye2_TA_tex_txt,
                bea_10_eye3_TA_tex_txt,
                bea_10_eye4_TA_tex_txt,
                bea_10_eye5_TA_tex_txt,
                bea_10_eye6_TA_tex_txt,
                bea_10_eye7_TA_tex_txt,
                bea_10_eye8_TA_tex_txt,
            },
            {
                bea_10_mouth1_TA_tex_txt,
                bea_10_mouth2_TA_tex_txt,
                bea_10_mouth3_TA_tex_txt,
                bea_10_mouth4_TA_tex_txt,
                bea_10_mouth5_TA_tex_txt,
                bea_10_mouth6_TA_tex_txt,
            },
            64,
            96,
            176,
        },
        0.008999999612569809,
        0,
        9,
        2,
        47,
        0,
        0,
        36,
        20,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_113,
        ACTOR_OBJ_BANK_114,
        &cKF_bs_r_brd_1,
        {
            brd_1_tmem_txt,
            brd_1_pal,
            {
                brd_1_eye1_TA_tex_txt,
                brd_1_eye2_TA_tex_txt,
                brd_1_eye3_TA_tex_txt,
                brd_1_eye4_TA_tex_txt,
                brd_1_eye5_TA_tex_txt,
                brd_1_eye6_TA_tex_txt,
                brd_1_eye7_TA_tex_txt,
                brd_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            8,
            0,
            144,
        },
        0.009499999694526196,
        1,
        0,
        18,
        35,
        0,
        0,
        124,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_113,
        ACTOR_OBJ_BANK_115,
        &cKF_bs_r_brd_1,
        {
            brd_2_tmem_txt,
            brd_2_pal,
            {
                brd_2_eye1_TA_tex_txt,
                brd_2_eye2_TA_tex_txt,
                brd_2_eye3_TA_tex_txt,
                brd_2_eye4_TA_tex_txt,
                brd_2_eye5_TA_tex_txt,
                brd_2_eye6_TA_tex_txt,
                brd_2_eye7_TA_tex_txt,
                brd_2_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            8,
            0,
            144,
        },
        0.009499999694526196,
        1,
        1,
        0,
        35,
        0,
        0,
        125,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_113,
        ACTOR_OBJ_BANK_116,
        &cKF_bs_r_brd_1,
        {
            brd_3_tmem_txt,
            brd_3_pal,
            {
                brd_3_eye1_TA_tex_txt,
                brd_3_eye2_TA_tex_txt,
                brd_3_eye3_TA_tex_txt,
                brd_3_eye4_TA_tex_txt,
                brd_3_eye5_TA_tex_txt,
                brd_3_eye6_TA_tex_txt,
                brd_3_eye7_TA_tex_txt,
                brd_3_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            8,
            0,
            144,
        },
        0.009499999694526196,
        1,
        2,
        3,
        35,
        0,
        0,
        126,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_113,
        ACTOR_OBJ_BANK_117,
        &cKF_bs_r_brd_1,
        {
            brd_4_tmem_txt,
            brd_4_pal,
            {
                brd_4_eye1_TA_tex_txt,
                brd_4_eye2_TA_tex_txt,
                brd_4_eye3_TA_tex_txt,
                brd_4_eye4_TA_tex_txt,
                brd_4_eye5_TA_tex_txt,
                brd_4_eye6_TA_tex_txt,
                brd_4_eye7_TA_tex_txt,
                brd_4_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            8,
            0,
            144,
        },
        0.009499999694526196,
        1,
        3,
        1,
        35,
        0,
        0,
        127,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_113,
        ACTOR_OBJ_BANK_118,
        &cKF_bs_r_brd_1,
        {
            brd_5_tmem_txt,
            brd_5_pal,
            {
                brd_5_eye1_TA_tex_txt,
                brd_5_eye2_TA_tex_txt,
                brd_5_eye3_TA_tex_txt,
                brd_5_eye4_TA_tex_txt,
                brd_5_eye5_TA_tex_txt,
                brd_5_eye6_TA_tex_txt,
                brd_5_eye7_TA_tex_txt,
                brd_5_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            8,
            0,
            144,
        },
        0.009499999694526196,
        1,
        4,
        21,
        35,
        0,
        0,
        128,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_113,
        ACTOR_OBJ_BANK_119,
        &cKF_bs_r_brd_1,
        {
            brd_6_tmem_txt,
            brd_6_pal,
            {
                brd_6_eye1_TA_tex_txt,
                brd_6_eye2_TA_tex_txt,
                brd_6_eye3_TA_tex_txt,
                brd_6_eye4_TA_tex_txt,
                brd_6_eye5_TA_tex_txt,
                brd_6_eye6_TA_tex_txt,
                brd_6_eye7_TA_tex_txt,
                brd_6_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            8,
            0,
            144,
        },
        0.009499999694526196,
        1,
        5,
        24,
        35,
        0,
        0,
        129,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_113,
        ACTOR_OBJ_BANK_120,
        &cKF_bs_r_brd_1,
        {
            brd_7_tmem_txt,
            brd_7_pal,
            {
                brd_7_eye1_TA_tex_txt,
                brd_7_eye2_TA_tex_txt,
                brd_7_eye3_TA_tex_txt,
                brd_7_eye4_TA_tex_txt,
                brd_7_eye5_TA_tex_txt,
                brd_7_eye6_TA_tex_txt,
                brd_7_eye7_TA_tex_txt,
                brd_7_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            8,
            0,
            144,
        },
        0.009499999694526196,
        1,
        6,
        30,
        35,
        0,
        0,
        130,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_113,
        ACTOR_OBJ_BANK_121,
        &cKF_bs_r_brd_1,
        {
            brd_8_tmem_txt,
            brd_8_pal,
            {
                brd_8_eye1_TA_tex_txt,
                brd_8_eye2_TA_tex_txt,
                brd_8_eye3_TA_tex_txt,
                brd_8_eye4_TA_tex_txt,
                brd_8_eye5_TA_tex_txt,
                brd_8_eye6_TA_tex_txt,
                brd_8_eye7_TA_tex_txt,
                brd_8_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            8,
            0,
            144,
        },
        0.009499999694526196,
        1,
        7,
        20,
        35,
        0,
        0,
        131,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_113,
        ACTOR_OBJ_BANK_122,
        &cKF_bs_r_brd_1,
        {
            brd_9_tmem_txt,
            brd_9_pal,
            {
                brd_9_eye1_TA_tex_txt,
                brd_9_eye2_TA_tex_txt,
                brd_9_eye3_TA_tex_txt,
                brd_9_eye4_TA_tex_txt,
                brd_9_eye5_TA_tex_txt,
                brd_9_eye6_TA_tex_txt,
                brd_9_eye7_TA_tex_txt,
                brd_9_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            8,
            0,
            144,
        },
        0.009499999694526196,
        1,
        8,
        23,
        35,
        0,
        0,
        132,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_113,
        ACTOR_OBJ_BANK_123,
        &cKF_bs_r_brd_1,
        {
            brd_10_tmem_txt,
            brd_10_pal,
            {
                brd_10_eye1_TA_tex_txt,
                brd_10_eye2_TA_tex_txt,
                brd_10_eye3_TA_tex_txt,
                brd_10_eye4_TA_tex_txt,
                brd_10_eye5_TA_tex_txt,
                brd_10_eye6_TA_tex_txt,
                brd_10_eye7_TA_tex_txt,
                brd_10_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            8,
            0,
            144,
        },
        0.009499999694526196,
        1,
        9,
        31,
        35,
        0,
        0,
        133,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_126,
        ACTOR_OBJ_BANK_127,
        &cKF_bs_r_bul_1,
        {
            bul_1_tmem_txt,
            bul_1_pal,
            {
                bul_1_eye1_TA_tex_txt,
                bul_1_eye2_TA_tex_txt,
                bul_1_eye3_TA_tex_txt,
                bul_1_eye4_TA_tex_txt,
                bul_1_eye5_TA_tex_txt,
                bul_1_eye6_TA_tex_txt,
                bul_1_eye7_TA_tex_txt,
                bul_1_eye8_TA_tex_txt,
            },
            {
                bul_1_mouth1_TA_tex_txt,
                bul_1_mouth2_TA_tex_txt,
                bul_1_mouth3_TA_tex_txt,
                bul_1_mouth4_TA_tex_txt,
                bul_1_mouth5_TA_tex_txt,
                bul_1_mouth6_TA_tex_txt,
            },
            128,
            32,
            176,
        },
        0.012500000186264515,
        0,
        0,
        13,
        45,
        0,
        0,
        116,
        25,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_126,
        ACTOR_OBJ_BANK_128,
        &cKF_bs_r_bul_1,
        {
            bul_2_tmem_txt,
            bul_2_pal,
            {
                bul_2_eye1_TA_tex_txt,
                bul_2_eye2_TA_tex_txt,
                bul_2_eye3_TA_tex_txt,
                bul_2_eye4_TA_tex_txt,
                bul_2_eye5_TA_tex_txt,
                bul_2_eye6_TA_tex_txt,
                bul_2_eye7_TA_tex_txt,
                bul_2_eye8_TA_tex_txt,
            },
            {
                bul_2_mouth1_TA_tex_txt,
                bul_2_mouth2_TA_tex_txt,
                bul_2_mouth3_TA_tex_txt,
                bul_2_mouth4_TA_tex_txt,
                bul_2_mouth5_TA_tex_txt,
                bul_2_mouth6_TA_tex_txt,
            },
            128,
            32,
            176,
        },
        0.012500000186264515,
        0,
        1,
        8,
        45,
        0,
        0,
        117,
        25,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_148,
        ACTOR_OBJ_BANK_149,
        &cKF_bs_r_chn_1,
        {
            chn_1_tmem_txt,
            chn_1_pal,
            {
                chn_1_eye1_TA_tex_txt,
                chn_1_eye2_TA_tex_txt,
                chn_1_eye3_TA_tex_txt,
                chn_1_eye4_TA_tex_txt,
                chn_1_eye5_TA_tex_txt,
                chn_1_eye6_TA_tex_txt,
                chn_1_eye7_TA_tex_txt,
                chn_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            16,
            0,
            152,
        },
        0.009999999776482582,
        1,
        0,
        21,
        35,
        0,
        0,
        108,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_148,
        ACTOR_OBJ_BANK_150,
        &cKF_bs_r_chn_1,
        {
            chn_2_tmem_txt,
            chn_2_pal,
            {
                chn_2_eye1_TA_tex_txt,
                chn_2_eye2_TA_tex_txt,
                chn_2_eye3_TA_tex_txt,
                chn_2_eye4_TA_tex_txt,
                chn_2_eye5_TA_tex_txt,
                chn_2_eye6_TA_tex_txt,
                chn_2_eye7_TA_tex_txt,
                chn_2_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            16,
            0,
            152,
        },
        0.009999999776482582,
        1,
        1,
        12,
        35,
        0,
        0,
        109,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_148,
        ACTOR_OBJ_BANK_151,
        &cKF_bs_r_chn_1,
        {
            chn_3_tmem_txt,
            chn_3_pal,
            {
                chn_3_eye1_TA_tex_txt,
                chn_3_eye2_TA_tex_txt,
                chn_3_eye3_TA_tex_txt,
                chn_3_eye4_TA_tex_txt,
                chn_3_eye5_TA_tex_txt,
                chn_3_eye6_TA_tex_txt,
                chn_3_eye7_TA_tex_txt,
                chn_3_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            16,
            0,
            152,
        },
        0.009999999776482582,
        1,
        2,
        14,
        35,
        0,
        0,
        110,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_148,
        ACTOR_OBJ_BANK_152,
        &cKF_bs_r_chn_1,
        {
            chn_4_tmem_txt,
            chn_4_pal,
            {
                chn_4_eye1_TA_tex_txt,
                chn_4_eye2_TA_tex_txt,
                chn_4_eye3_TA_tex_txt,
                chn_4_eye4_TA_tex_txt,
                chn_4_eye5_TA_tex_txt,
                chn_4_eye6_TA_tex_txt,
                chn_4_eye7_TA_tex_txt,
                chn_4_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            16,
            0,
            152,
        },
        0.009999999776482582,
        1,
        3,
        30,
        35,
        0,
        0,
        111,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_148,
        ACTOR_OBJ_BANK_153,
        &cKF_bs_r_chn_1,
        {
            chn_5_tmem_txt,
            chn_5_pal,
            {
                chn_5_eye1_TA_tex_txt,
                chn_5_eye2_TA_tex_txt,
                chn_5_eye3_TA_tex_txt,
                chn_5_eye4_TA_tex_txt,
                chn_5_eye5_TA_tex_txt,
                chn_5_eye6_TA_tex_txt,
                chn_5_eye7_TA_tex_txt,
                chn_5_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            16,
            0,
            152,
        },
        0.009999999776482582,
        1,
        4,
        22,
        35,
        0,
        0,
        112,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_148,
        ACTOR_OBJ_BANK_154,
        &cKF_bs_r_chn_1,
        {
            chn_6_tmem_txt,
            chn_6_pal,
            {
                chn_6_eye1_TA_tex_txt,
                chn_6_eye2_TA_tex_txt,
                chn_6_eye3_TA_tex_txt,
                chn_6_eye4_TA_tex_txt,
                chn_6_eye5_TA_tex_txt,
                chn_6_eye6_TA_tex_txt,
                chn_6_eye7_TA_tex_txt,
                chn_6_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            16,
            0,
            152,
        },
        0.009999999776482582,
        1,
        5,
        28,
        35,
        0,
        0,
        113,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_148,
        ACTOR_OBJ_BANK_155,
        &cKF_bs_r_chn_1,
        {
            chn_7_tmem_txt,
            chn_7_pal,
            {
                chn_7_eye1_TA_tex_txt,
                chn_7_eye2_TA_tex_txt,
                chn_7_eye3_TA_tex_txt,
                chn_7_eye4_TA_tex_txt,
                chn_7_eye5_TA_tex_txt,
                chn_7_eye6_TA_tex_txt,
                chn_7_eye7_TA_tex_txt,
                chn_7_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            16,
            0,
            152,
        },
        0.009999999776482582,
        1,
        6,
        18,
        35,
        0,
        0,
        114,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_148,
        ACTOR_OBJ_BANK_156,
        &cKF_bs_r_chn_1,
        {
            chn_8_tmem_txt,
            chn_8_pal,
            {
                chn_8_eye1_TA_tex_txt,
                chn_8_eye2_TA_tex_txt,
                chn_8_eye3_TA_tex_txt,
                chn_8_eye4_TA_tex_txt,
                chn_8_eye5_TA_tex_txt,
                chn_8_eye6_TA_tex_txt,
                chn_8_eye7_TA_tex_txt,
                chn_8_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            16,
            0,
            152,
        },
        0.009999999776482582,
        1,
        7,
        1,
        35,
        0,
        0,
        115,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_157,
        ACTOR_OBJ_BANK_158,
        &cKF_bs_r_cbr_1,
        {
            cbr_1_tmem_txt,
            cbr_1_pal,
            {
                cbr_1_eye1_TA_tex_txt,
                cbr_1_eye2_TA_tex_txt,
                cbr_1_eye3_TA_tex_txt,
                cbr_1_eye4_TA_tex_txt,
                cbr_1_eye5_TA_tex_txt,
                cbr_1_eye6_TA_tex_txt,
                cbr_1_eye7_TA_tex_txt,
                cbr_1_eye8_TA_tex_txt,
            },
            {
                cbr_1_mouth1_TA_tex_txt,
                cbr_1_mouth2_TA_tex_txt,
                cbr_1_mouth3_TA_tex_txt,
                cbr_1_mouth4_TA_tex_txt,
                cbr_1_mouth5_TA_tex_txt,
                cbr_1_mouth6_TA_tex_txt,
            },
            128,
            8,
            176,
        },
        0.006500000134110451,
        0,
        0,
        31,
        33,
        0,
        0,
        180,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_157,
        ACTOR_OBJ_BANK_159,
        &cKF_bs_r_cbr_1,
        {
            cbr_2_tmem_txt,
            cbr_2_pal,
            {
                cbr_2_eye1_TA_tex_txt,
                cbr_2_eye2_TA_tex_txt,
                cbr_2_eye3_TA_tex_txt,
                cbr_2_eye4_TA_tex_txt,
                cbr_2_eye5_TA_tex_txt,
                cbr_2_eye6_TA_tex_txt,
                cbr_2_eye7_TA_tex_txt,
                cbr_2_eye8_TA_tex_txt,
            },
            {
                cbr_2_mouth1_TA_tex_txt,
                cbr_2_mouth2_TA_tex_txt,
                cbr_2_mouth3_TA_tex_txt,
                cbr_2_mouth4_TA_tex_txt,
                cbr_2_mouth5_TA_tex_txt,
                cbr_2_mouth6_TA_tex_txt,
            },
            128,
            8,
            176,
        },
        0.006500000134110451,
        0,
        1,
        28,
        33,
        0,
        0,
        181,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_157,
        ACTOR_OBJ_BANK_160,
        &cKF_bs_r_cbr_1,
        {
            cbr_3_tmem_txt,
            cbr_3_pal,
            {
                cbr_3_eye1_TA_tex_txt,
                cbr_3_eye2_TA_tex_txt,
                cbr_3_eye3_TA_tex_txt,
                cbr_3_eye4_TA_tex_txt,
                cbr_3_eye5_TA_tex_txt,
                cbr_3_eye6_TA_tex_txt,
                cbr_3_eye7_TA_tex_txt,
                cbr_3_eye8_TA_tex_txt,
            },
            {
                cbr_3_mouth1_TA_tex_txt,
                cbr_3_mouth2_TA_tex_txt,
                cbr_3_mouth3_TA_tex_txt,
                cbr_3_mouth4_TA_tex_txt,
                cbr_3_mouth5_TA_tex_txt,
                cbr_3_mouth6_TA_tex_txt,
            },
            128,
            8,
            176,
        },
        0.006500000134110451,
        0,
        2,
        6,
        33,
        0,
        0,
        182,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_157,
        ACTOR_OBJ_BANK_161,
        &cKF_bs_r_cbr_1,
        {
            cbr_4_tmem_txt,
            cbr_4_pal,
            {
                cbr_4_eye1_TA_tex_txt,
                cbr_4_eye2_TA_tex_txt,
                cbr_4_eye3_TA_tex_txt,
                cbr_4_eye4_TA_tex_txt,
                cbr_4_eye5_TA_tex_txt,
                cbr_4_eye6_TA_tex_txt,
                cbr_4_eye7_TA_tex_txt,
                cbr_4_eye8_TA_tex_txt,
            },
            {
                cbr_4_mouth1_TA_tex_txt,
                cbr_4_mouth2_TA_tex_txt,
                cbr_4_mouth3_TA_tex_txt,
                cbr_4_mouth4_TA_tex_txt,
                cbr_4_mouth5_TA_tex_txt,
                cbr_4_mouth6_TA_tex_txt,
            },
            128,
            8,
            176,
        },
        0.006500000134110451,
        0,
        3,
        15,
        33,
        0,
        0,
        183,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_157,
        ACTOR_OBJ_BANK_162,
        &cKF_bs_r_cbr_1,
        {
            cbr_5_tmem_txt,
            cbr_5_pal,
            {
                cbr_5_eye1_TA_tex_txt,
                cbr_5_eye2_TA_tex_txt,
                cbr_5_eye3_TA_tex_txt,
                cbr_5_eye4_TA_tex_txt,
                cbr_5_eye5_TA_tex_txt,
                cbr_5_eye6_TA_tex_txt,
                cbr_5_eye7_TA_tex_txt,
                cbr_5_eye8_TA_tex_txt,
            },
            {
                cbr_5_mouth1_TA_tex_txt,
                cbr_5_mouth2_TA_tex_txt,
                cbr_5_mouth3_TA_tex_txt,
                cbr_5_mouth4_TA_tex_txt,
                cbr_5_mouth5_TA_tex_txt,
                cbr_5_mouth6_TA_tex_txt,
            },
            128,
            8,
            176,
        },
        0.006500000134110451,
        0,
        4,
        20,
        33,
        0,
        0,
        184,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_157,
        ACTOR_OBJ_BANK_163,
        &cKF_bs_r_cbr_1,
        {
            cbr_6_tmem_txt,
            cbr_6_pal,
            {
                cbr_6_eye1_TA_tex_txt,
                cbr_6_eye2_TA_tex_txt,
                cbr_6_eye3_TA_tex_txt,
                cbr_6_eye4_TA_tex_txt,
                cbr_6_eye5_TA_tex_txt,
                cbr_6_eye6_TA_tex_txt,
                cbr_6_eye7_TA_tex_txt,
                cbr_6_eye8_TA_tex_txt,
            },
            {
                cbr_6_mouth1_TA_tex_txt,
                cbr_6_mouth2_TA_tex_txt,
                cbr_6_mouth3_TA_tex_txt,
                cbr_6_mouth4_TA_tex_txt,
                cbr_6_mouth5_TA_tex_txt,
                cbr_6_mouth6_TA_tex_txt,
            },
            128,
            8,
            176,
        },
        0.006500000134110451,
        0,
        5,
        25,
        33,
        0,
        0,
        185,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_157,
        ACTOR_OBJ_BANK_164,
        &cKF_bs_r_cbr_1,
        {
            cbr_7_tmem_txt,
            cbr_7_pal,
            {
                cbr_7_eye1_TA_tex_txt,
                cbr_7_eye2_TA_tex_txt,
                cbr_7_eye3_TA_tex_txt,
                cbr_7_eye4_TA_tex_txt,
                cbr_7_eye5_TA_tex_txt,
                cbr_7_eye6_TA_tex_txt,
                cbr_7_eye7_TA_tex_txt,
                cbr_7_eye8_TA_tex_txt,
            },
            {
                cbr_7_mouth1_TA_tex_txt,
                cbr_7_mouth2_TA_tex_txt,
                cbr_7_mouth3_TA_tex_txt,
                cbr_7_mouth4_TA_tex_txt,
                cbr_7_mouth5_TA_tex_txt,
                cbr_7_mouth6_TA_tex_txt,
            },
            128,
            8,
            176,
        },
        0.006500000134110451,
        0,
        6,
        7,
        33,
        0,
        0,
        186,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_157,
        ACTOR_OBJ_BANK_165,
        &cKF_bs_r_cbr_1,
        {
            cbr_8_tmem_txt,
            cbr_8_pal,
            {
                cbr_8_eye1_TA_tex_txt,
                cbr_8_eye2_TA_tex_txt,
                cbr_8_eye3_TA_tex_txt,
                cbr_8_eye4_TA_tex_txt,
                cbr_8_eye5_TA_tex_txt,
                cbr_8_eye6_TA_tex_txt,
                cbr_8_eye7_TA_tex_txt,
                cbr_8_eye8_TA_tex_txt,
            },
            {
                cbr_8_mouth1_TA_tex_txt,
                cbr_8_mouth2_TA_tex_txt,
                cbr_8_mouth3_TA_tex_txt,
                cbr_8_mouth4_TA_tex_txt,
                cbr_8_mouth5_TA_tex_txt,
                cbr_8_mouth6_TA_tex_txt,
            },
            128,
            8,
            176,
        },
        0.006500000134110451,
        0,
        7,
        8,
        33,
        0,
        0,
        187,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_157,
        ACTOR_OBJ_BANK_166,
        &cKF_bs_r_cbr_1,
        {
            cbr_9_tmem_txt,
            cbr_9_pal,
            {
                cbr_9_eye1_TA_tex_txt,
                cbr_9_eye2_TA_tex_txt,
                cbr_9_eye3_TA_tex_txt,
                cbr_9_eye4_TA_tex_txt,
                cbr_9_eye5_TA_tex_txt,
                cbr_9_eye6_TA_tex_txt,
                cbr_9_eye7_TA_tex_txt,
                cbr_9_eye8_TA_tex_txt,
            },
            {
                cbr_9_mouth1_TA_tex_txt,
                cbr_9_mouth2_TA_tex_txt,
                cbr_9_mouth3_TA_tex_txt,
                cbr_9_mouth4_TA_tex_txt,
                cbr_9_mouth5_TA_tex_txt,
                cbr_9_mouth6_TA_tex_txt,
            },
            128,
            8,
            176,
        },
        0.006500000134110451,
        0,
        8,
        29,
        33,
        0,
        0,
        188,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_169,
        ACTOR_OBJ_BANK_170,
        &cKF_bs_r_cow_1,
        {
            cow_1_tmem_txt,
            cow_1_pal,
            {
                cow_1_eye1_TA_tex_txt,
                cow_1_eye2_TA_tex_txt,
                cow_1_eye3_TA_tex_txt,
                cow_1_eye4_TA_tex_txt,
                cow_1_eye5_TA_tex_txt,
                cow_1_eye6_TA_tex_txt,
                cow_1_eye7_TA_tex_txt,
                cow_1_eye8_TA_tex_txt,
            },
            {
                cow_1_mouth1_TA_tex_txt,
                cow_1_mouth2_TA_tex_txt,
                cow_1_mouth3_TA_tex_txt,
                cow_1_mouth4_TA_tex_txt,
                cow_1_mouth5_TA_tex_txt,
                cow_1_mouth6_TA_tex_txt,
            },
            56,
            104,
            176,
        },
        0.011300000362098217,
        0,
        0,
        0,
        42,
        0,
        0,
        120,
        25,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_169,
        ACTOR_OBJ_BANK_171,
        &cKF_bs_r_cow_1,
        {
            cow_2_tmem_txt,
            cow_2_pal,
            {
                cow_2_eye1_TA_tex_txt,
                cow_2_eye2_TA_tex_txt,
                cow_2_eye3_TA_tex_txt,
                cow_2_eye4_TA_tex_txt,
                cow_2_eye5_TA_tex_txt,
                cow_2_eye6_TA_tex_txt,
                cow_2_eye7_TA_tex_txt,
                cow_2_eye8_TA_tex_txt,
            },
            {
                cow_2_mouth1_TA_tex_txt,
                cow_2_mouth2_TA_tex_txt,
                cow_2_mouth3_TA_tex_txt,
                cow_2_mouth4_TA_tex_txt,
                cow_2_mouth5_TA_tex_txt,
                cow_2_mouth6_TA_tex_txt,
            },
            56,
            104,
            176,
        },
        0.011300000362098217,
        0,
        1,
        17,
        42,
        0,
        0,
        121,
        25,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_169,
        ACTOR_OBJ_BANK_172,
        &cKF_bs_r_cow_1,
        {
            cow_3_tmem_txt,
            cow_3_pal,
            {
                cow_3_eye1_TA_tex_txt,
                cow_3_eye2_TA_tex_txt,
                cow_3_eye3_TA_tex_txt,
                cow_3_eye4_TA_tex_txt,
                cow_3_eye5_TA_tex_txt,
                cow_3_eye6_TA_tex_txt,
                cow_3_eye7_TA_tex_txt,
                cow_3_eye8_TA_tex_txt,
            },
            {
                cow_3_mouth1_TA_tex_txt,
                cow_3_mouth2_TA_tex_txt,
                cow_3_mouth3_TA_tex_txt,
                cow_3_mouth4_TA_tex_txt,
                cow_3_mouth5_TA_tex_txt,
                cow_3_mouth6_TA_tex_txt,
            },
            56,
            104,
            176,
        },
        0.011300000362098217,
        0,
        2,
        8,
        42,
        0,
        0,
        122,
        25,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_169,
        ACTOR_OBJ_BANK_173,
        &cKF_bs_r_cow_1,
        {
            cow_4_tmem_txt,
            cow_4_pal,
            {
                cow_4_eye1_TA_tex_txt,
                cow_4_eye2_TA_tex_txt,
                cow_4_eye3_TA_tex_txt,
                cow_4_eye4_TA_tex_txt,
                cow_4_eye5_TA_tex_txt,
                cow_4_eye6_TA_tex_txt,
                cow_4_eye7_TA_tex_txt,
                cow_4_eye8_TA_tex_txt,
            },
            {
                cow_4_mouth1_TA_tex_txt,
                cow_4_mouth2_TA_tex_txt,
                cow_4_mouth3_TA_tex_txt,
                cow_4_mouth4_TA_tex_txt,
                cow_4_mouth5_TA_tex_txt,
                cow_4_mouth6_TA_tex_txt,
            },
            56,
            104,
            176,
        },
        0.011300000362098217,
        0,
        3,
        5,
        42,
        0,
        0,
        123,
        25,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_174,
        ACTOR_OBJ_BANK_175,
        &cKF_bs_r_crd_1,
        {
            crd_1_tmem_txt,
            crd_1_pal,
            {
                crd_1_eye1_TA_tex_txt,
                crd_1_eye2_TA_tex_txt,
                crd_1_eye3_TA_tex_txt,
                crd_1_eye4_TA_tex_txt,
                crd_1_eye5_TA_tex_txt,
                crd_1_eye6_TA_tex_txt,
                crd_1_eye7_TA_tex_txt,
                crd_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            96,
            0,
            168,
        },
        0.010499999858438969,
        1,
        0,
        4,
        48,
        0,
        0,
        146,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_174,
        ACTOR_OBJ_BANK_176,
        &cKF_bs_r_crd_1,
        {
            crd_2_tmem_txt,
            crd_2_pal,
            {
                crd_2_eye1_TA_tex_txt,
                crd_2_eye2_TA_tex_txt,
                crd_2_eye3_TA_tex_txt,
                crd_2_eye4_TA_tex_txt,
                crd_2_eye5_TA_tex_txt,
                crd_2_eye6_TA_tex_txt,
                crd_2_eye7_TA_tex_txt,
                crd_2_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            96,
            0,
            168,
        },
        0.010499999858438969,
        1,
        1,
        11,
        48,
        0,
        0,
        147,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_174,
        ACTOR_OBJ_BANK_177,
        &cKF_bs_r_crd_1,
        {
            crd_3_tmem_txt,
            crd_3_pal,
            {
                crd_3_eye1_TA_tex_txt,
                crd_3_eye2_TA_tex_txt,
                crd_3_eye3_TA_tex_txt,
                crd_3_eye4_TA_tex_txt,
                crd_3_eye5_TA_tex_txt,
                crd_3_eye6_TA_tex_txt,
                crd_3_eye7_TA_tex_txt,
                crd_3_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            96,
            0,
            168,
        },
        0.010499999858438969,
        1,
        2,
        2,
        48,
        0,
        0,
        148,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_182,
        ACTOR_OBJ_BANK_183,
        &cKF_bs_r_dog_1,
        {
            dog_1_tmem_txt,
            dog_1_pal,
            {
                dog_1_eye1_TA_tex_txt,
                dog_1_eye2_TA_tex_txt,
                dog_1_eye3_TA_tex_txt,
                dog_1_eye4_TA_tex_txt,
                dog_1_eye5_TA_tex_txt,
                dog_1_eye6_TA_tex_txt,
                dog_1_eye7_TA_tex_txt,
                dog_1_eye8_TA_tex_txt,
            },
            {
                dog_1_mouth1_TA_tex_txt,
                dog_1_mouth2_TA_tex_txt,
                dog_1_mouth3_TA_tex_txt,
                dog_1_mouth4_TA_tex_txt,
                dog_1_mouth5_TA_tex_txt,
                dog_1_mouth6_TA_tex_txt,
            },
            48,
            0,
            80,
        },
        0.009499999694526196,
        0,
        0,
        15,
        37,
        0,
        0,
        37,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_182,
        ACTOR_OBJ_BANK_184,
        &cKF_bs_r_dog_1,
        {
            dog_2_tmem_txt,
            dog_2_pal,
            {
                dog_2_eye1_TA_tex_txt,
                dog_2_eye2_TA_tex_txt,
                dog_2_eye3_TA_tex_txt,
                dog_2_eye4_TA_tex_txt,
                dog_2_eye5_TA_tex_txt,
                dog_2_eye6_TA_tex_txt,
                dog_2_eye7_TA_tex_txt,
                dog_2_eye8_TA_tex_txt,
            },
            {
                dog_2_mouth1_TA_tex_txt,
                dog_2_mouth2_TA_tex_txt,
                dog_2_mouth3_TA_tex_txt,
                dog_2_mouth4_TA_tex_txt,
                dog_2_mouth5_TA_tex_txt,
                dog_2_mouth6_TA_tex_txt,
            },
            48,
            0,
            80,
        },
        0.009499999694526196,
        0,
        1,
        22,
        37,
        0,
        0,
        38,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_182,
        ACTOR_OBJ_BANK_185,
        &cKF_bs_r_dog_1,
        {
            dog_3_tmem_txt,
            dog_3_pal,
            {
                dog_3_eye1_TA_tex_txt,
                dog_3_eye2_TA_tex_txt,
                dog_3_eye3_TA_tex_txt,
                dog_3_eye4_TA_tex_txt,
                dog_3_eye5_TA_tex_txt,
                dog_3_eye6_TA_tex_txt,
                dog_3_eye7_TA_tex_txt,
                dog_3_eye8_TA_tex_txt,
            },
            {
                dog_3_mouth1_TA_tex_txt,
                dog_3_mouth2_TA_tex_txt,
                dog_3_mouth3_TA_tex_txt,
                dog_3_mouth4_TA_tex_txt,
                dog_3_mouth5_TA_tex_txt,
                dog_3_mouth6_TA_tex_txt,
            },
            48,
            0,
            80,
        },
        0.009499999694526196,
        0,
        2,
        0,
        37,
        0,
        0,
        39,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_182,
        ACTOR_OBJ_BANK_186,
        &cKF_bs_r_dog_1,
        {
            dog_4_tmem_txt,
            dog_4_pal,
            {
                dog_4_eye1_TA_tex_txt,
                dog_4_eye2_TA_tex_txt,
                dog_4_eye3_TA_tex_txt,
                dog_4_eye4_TA_tex_txt,
                dog_4_eye5_TA_tex_txt,
                dog_4_eye6_TA_tex_txt,
                dog_4_eye7_TA_tex_txt,
                dog_4_eye8_TA_tex_txt,
            },
            {
                dog_4_mouth1_TA_tex_txt,
                dog_4_mouth2_TA_tex_txt,
                dog_4_mouth3_TA_tex_txt,
                dog_4_mouth4_TA_tex_txt,
                dog_4_mouth5_TA_tex_txt,
                dog_4_mouth6_TA_tex_txt,
            },
            48,
            0,
            80,
        },
        0.009499999694526196,
        0,
        3,
        16,
        37,
        0,
        0,
        40,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_182,
        ACTOR_OBJ_BANK_187,
        &cKF_bs_r_dog_1,
        {
            dog_5_tmem_txt,
            dog_5_pal,
            {
                dog_5_eye1_TA_tex_txt,
                dog_5_eye2_TA_tex_txt,
                dog_5_eye3_TA_tex_txt,
                dog_5_eye4_TA_tex_txt,
                dog_5_eye5_TA_tex_txt,
                dog_5_eye6_TA_tex_txt,
                dog_5_eye7_TA_tex_txt,
                dog_5_eye8_TA_tex_txt,
            },
            {
                dog_5_mouth1_TA_tex_txt,
                dog_5_mouth2_TA_tex_txt,
                dog_5_mouth3_TA_tex_txt,
                dog_5_mouth4_TA_tex_txt,
                dog_5_mouth5_TA_tex_txt,
                dog_5_mouth6_TA_tex_txt,
            },
            48,
            0,
            80,
        },
        0.009499999694526196,
        0,
        4,
        10,
        37,
        0,
        0,
        41,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_182,
        ACTOR_OBJ_BANK_188,
        &cKF_bs_r_dog_1,
        {
            dog_6_tmem_txt,
            dog_6_pal,
            {
                dog_6_eye1_TA_tex_txt,
                dog_6_eye2_TA_tex_txt,
                dog_6_eye3_TA_tex_txt,
                dog_6_eye4_TA_tex_txt,
                dog_6_eye5_TA_tex_txt,
                dog_6_eye6_TA_tex_txt,
                dog_6_eye7_TA_tex_txt,
                dog_6_eye8_TA_tex_txt,
            },
            {
                dog_6_mouth1_TA_tex_txt,
                dog_6_mouth2_TA_tex_txt,
                dog_6_mouth3_TA_tex_txt,
                dog_6_mouth4_TA_tex_txt,
                dog_6_mouth5_TA_tex_txt,
                dog_6_mouth6_TA_tex_txt,
            },
            48,
            0,
            80,
        },
        0.009499999694526196,
        0,
        5,
        27,
        37,
        0,
        0,
        42,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_182,
        ACTOR_OBJ_BANK_190,
        &cKF_bs_r_dog_1,
        {
            dog_8_tmem_txt,
            dog_8_pal,
            {
                dog_8_eye1_TA_tex_txt,
                dog_8_eye2_TA_tex_txt,
                dog_8_eye3_TA_tex_txt,
                dog_8_eye4_TA_tex_txt,
                dog_8_eye5_TA_tex_txt,
                dog_8_eye6_TA_tex_txt,
                dog_8_eye7_TA_tex_txt,
                dog_8_eye8_TA_tex_txt,
            },
            {
                dog_8_mouth1_TA_tex_txt,
                dog_8_mouth2_TA_tex_txt,
                dog_8_mouth3_TA_tex_txt,
                dog_8_mouth4_TA_tex_txt,
                dog_8_mouth5_TA_tex_txt,
                dog_8_mouth6_TA_tex_txt,
            },
            48,
            0,
            80,
        },
        0.009499999694526196,
        0,
        7,
        12,
        37,
        0,
        0,
        44,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_191,
        ACTOR_OBJ_BANK_192,
        &cKF_bs_r_duk_1,
        {
            duk_1_tmem_txt,
            duk_1_pal,
            {
                duk_1_eye1_TA_tex_txt,
                duk_1_eye2_TA_tex_txt,
                duk_1_eye3_TA_tex_txt,
                duk_1_eye4_TA_tex_txt,
                duk_1_eye5_TA_tex_txt,
                duk_1_eye6_TA_tex_txt,
                duk_1_eye7_TA_tex_txt,
                duk_1_eye8_TA_tex_txt,
            },
            {
                duk_1_mouth1_TA_tex_txt,
                duk_1_mouth2_TA_tex_txt,
                duk_1_mouth3_TA_tex_txt,
                duk_1_mouth4_TA_tex_txt,
                duk_1_mouth5_TA_tex_txt,
                duk_1_mouth6_TA_tex_txt,
            },
            112,
            72,
            160,
        },
        0.009999999776482582,
        1,
        0,
        11,
        31,
        0,
        0,
        67,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_191,
        ACTOR_OBJ_BANK_193,
        &cKF_bs_r_duk_1,
        {
            duk_2_tmem_txt,
            duk_2_pal,
            {
                duk_2_eye1_TA_tex_txt,
                duk_2_eye2_TA_tex_txt,
                duk_2_eye3_TA_tex_txt,
                duk_2_eye4_TA_tex_txt,
                duk_2_eye5_TA_tex_txt,
                duk_2_eye6_TA_tex_txt,
                duk_2_eye7_TA_tex_txt,
                duk_2_eye8_TA_tex_txt,
            },
            {
                duk_2_mouth1_TA_tex_txt,
                duk_2_mouth2_TA_tex_txt,
                duk_2_mouth3_TA_tex_txt,
                duk_2_mouth4_TA_tex_txt,
                duk_2_mouth5_TA_tex_txt,
                duk_2_mouth6_TA_tex_txt,
            },
            112,
            72,
            160,
        },
        0.009999999776482582,
        1,
        1,
        2,
        31,
        0,
        0,
        68,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_191,
        ACTOR_OBJ_BANK_194,
        &cKF_bs_r_duk_1,
        {
            duk_3_tmem_txt,
            duk_3_pal,
            {
                duk_3_eye1_TA_tex_txt,
                duk_3_eye2_TA_tex_txt,
                duk_3_eye3_TA_tex_txt,
                duk_3_eye4_TA_tex_txt,
                duk_3_eye5_TA_tex_txt,
                duk_3_eye6_TA_tex_txt,
                duk_3_eye7_TA_tex_txt,
                duk_3_eye8_TA_tex_txt,
            },
            {
                duk_3_mouth1_TA_tex_txt,
                duk_3_mouth2_TA_tex_txt,
                duk_3_mouth3_TA_tex_txt,
                duk_3_mouth4_TA_tex_txt,
                duk_3_mouth5_TA_tex_txt,
                duk_3_mouth6_TA_tex_txt,
            },
            112,
            72,
            160,
        },
        0.009999999776482582,
        1,
        2,
        19,
        31,
        0,
        0,
        69,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_191,
        ACTOR_OBJ_BANK_195,
        &cKF_bs_r_duk_1,
        {
            duk_4_tmem_txt,
            duk_4_pal,
            {
                duk_4_eye1_TA_tex_txt,
                duk_4_eye2_TA_tex_txt,
                duk_4_eye3_TA_tex_txt,
                duk_4_eye4_TA_tex_txt,
                duk_4_eye5_TA_tex_txt,
                duk_4_eye6_TA_tex_txt,
                duk_4_eye7_TA_tex_txt,
                duk_4_eye8_TA_tex_txt,
            },
            {
                duk_4_mouth1_TA_tex_txt,
                duk_4_mouth2_TA_tex_txt,
                duk_4_mouth3_TA_tex_txt,
                duk_4_mouth4_TA_tex_txt,
                duk_4_mouth5_TA_tex_txt,
                duk_4_mouth6_TA_tex_txt,
            },
            112,
            72,
            160,
        },
        0.009999999776482582,
        1,
        3,
        31,
        31,
        0,
        0,
        70,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_191,
        ACTOR_OBJ_BANK_196,
        &cKF_bs_r_duk_1,
        {
            duk_5_tmem_txt,
            duk_5_pal,
            {
                duk_5_eye1_TA_tex_txt,
                duk_5_eye2_TA_tex_txt,
                duk_5_eye3_TA_tex_txt,
                duk_5_eye4_TA_tex_txt,
                duk_5_eye5_TA_tex_txt,
                duk_5_eye6_TA_tex_txt,
                duk_5_eye7_TA_tex_txt,
                duk_5_eye8_TA_tex_txt,
            },
            {
                duk_5_mouth1_TA_tex_txt,
                duk_5_mouth2_TA_tex_txt,
                duk_5_mouth3_TA_tex_txt,
                duk_5_mouth4_TA_tex_txt,
                duk_5_mouth5_TA_tex_txt,
                duk_5_mouth6_TA_tex_txt,
            },
            112,
            72,
            160,
        },
        0.009999999776482582,
        1,
        4,
        3,
        31,
        0,
        0,
        71,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_191,
        ACTOR_OBJ_BANK_197,
        &cKF_bs_r_duk_1,
        {
            duk_6_tmem_txt,
            duk_6_pal,
            {
                duk_6_eye1_TA_tex_txt,
                duk_6_eye2_TA_tex_txt,
                duk_6_eye3_TA_tex_txt,
                duk_6_eye4_TA_tex_txt,
                duk_6_eye5_TA_tex_txt,
                duk_6_eye6_TA_tex_txt,
                duk_6_eye7_TA_tex_txt,
                duk_6_eye8_TA_tex_txt,
            },
            {
                duk_6_mouth1_TA_tex_txt,
                duk_6_mouth2_TA_tex_txt,
                duk_6_mouth3_TA_tex_txt,
                duk_6_mouth4_TA_tex_txt,
                duk_6_mouth5_TA_tex_txt,
                duk_6_mouth6_TA_tex_txt,
            },
            112,
            72,
            160,
        },
        0.009999999776482582,
        1,
        5,
        4,
        31,
        0,
        0,
        72,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_200,
        ACTOR_OBJ_BANK_201,
        &cKF_bs_r_elp_1,
        {
            elp_1_tmem_txt,
            elp_1_pal,
            {
                elp_1_eye1_TA_tex_txt,
                elp_1_eye2_TA_tex_txt,
                elp_1_eye3_TA_tex_txt,
                elp_1_eye4_TA_tex_txt,
                elp_1_eye5_TA_tex_txt,
                elp_1_eye6_TA_tex_txt,
                elp_1_eye7_TA_tex_txt,
                elp_1_eye8_TA_tex_txt,
            },
            {
                elp_1_mouth1_TA_tex_txt,
                elp_1_mouth2_TA_tex_txt,
                elp_1_mouth3_TA_tex_txt,
                elp_1_mouth4_TA_tex_txt,
                elp_1_mouth5_TA_tex_txt,
                elp_1_mouth6_TA_tex_txt,
            },
            48,
            176,
            80,
        },
        0.009999999776482582,
        1,
        0,
        4,
        40,
        0,
        0,
        15,
        25,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_200,
        ACTOR_OBJ_BANK_202,
        &cKF_bs_r_elp_1,
        {
            elp_2_tmem_txt,
            elp_2_pal,
            {
                elp_2_eye1_TA_tex_txt,
                elp_2_eye2_TA_tex_txt,
                elp_2_eye3_TA_tex_txt,
                elp_2_eye4_TA_tex_txt,
                elp_2_eye5_TA_tex_txt,
                elp_2_eye6_TA_tex_txt,
                elp_2_eye7_TA_tex_txt,
                elp_2_eye8_TA_tex_txt,
            },
            {
                elp_2_mouth1_TA_tex_txt,
                elp_2_mouth2_TA_tex_txt,
                elp_2_mouth3_TA_tex_txt,
                elp_2_mouth4_TA_tex_txt,
                elp_2_mouth5_TA_tex_txt,
                elp_2_mouth6_TA_tex_txt,
            },
            48,
            176,
            80,
        },
        0.009999999776482582,
        1,
        1,
        0,
        40,
        0,
        0,
        16,
        25,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_200,
        ACTOR_OBJ_BANK_203,
        &cKF_bs_r_elp_1,
        {
            elp_3_tmem_txt,
            elp_3_pal,
            {
                elp_3_eye1_TA_tex_txt,
                elp_3_eye2_TA_tex_txt,
                elp_3_eye3_TA_tex_txt,
                elp_3_eye4_TA_tex_txt,
                elp_3_eye5_TA_tex_txt,
                elp_3_eye6_TA_tex_txt,
                elp_3_eye7_TA_tex_txt,
                elp_3_eye8_TA_tex_txt,
            },
            {
                elp_3_mouth1_TA_tex_txt,
                elp_3_mouth2_TA_tex_txt,
                elp_3_mouth3_TA_tex_txt,
                elp_3_mouth4_TA_tex_txt,
                elp_3_mouth5_TA_tex_txt,
                elp_3_mouth6_TA_tex_txt,
            },
            48,
            176,
            80,
        },
        0.009999999776482582,
        1,
        2,
        28,
        40,
        0,
        0,
        17,
        25,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_205,
        ACTOR_OBJ_BANK_206,
        &cKF_bs_r_flg_1,
        {
            flg_1_tmem_txt,
            flg_1_pal,
            {
                flg_1_eye1_TA_tex_txt,
                flg_1_eye2_TA_tex_txt,
                flg_1_eye3_TA_tex_txt,
                flg_1_eye4_TA_tex_txt,
                flg_1_eye5_TA_tex_txt,
                flg_1_eye6_TA_tex_txt,
                flg_1_eye7_TA_tex_txt,
                flg_1_eye8_TA_tex_txt,
            },
            {
                flg_1_mouth1_TA_tex_txt,
                flg_1_mouth2_TA_tex_txt,
                flg_1_mouth3_TA_tex_txt,
                flg_1_mouth4_TA_tex_txt,
                flg_1_mouth5_TA_tex_txt,
                flg_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            176,
        },
        0.00800000037997961,
        0,
        0,
        20,
        38,
        0,
        0,
        134,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_205,
        ACTOR_OBJ_BANK_207,
        &cKF_bs_r_flg_1,
        {
            flg_2_tmem_txt,
            flg_2_pal,
            {
                flg_2_eye1_TA_tex_txt,
                flg_2_eye2_TA_tex_txt,
                flg_2_eye3_TA_tex_txt,
                flg_2_eye4_TA_tex_txt,
                flg_2_eye5_TA_tex_txt,
                flg_2_eye6_TA_tex_txt,
                flg_2_eye7_TA_tex_txt,
                flg_2_eye8_TA_tex_txt,
            },
            {
                flg_2_mouth1_TA_tex_txt,
                flg_2_mouth2_TA_tex_txt,
                flg_2_mouth3_TA_tex_txt,
                flg_2_mouth4_TA_tex_txt,
                flg_2_mouth5_TA_tex_txt,
                flg_2_mouth6_TA_tex_txt,
            },
            0,
            32,
            176,
        },
        0.00800000037997961,
        0,
        1,
        23,
        38,
        0,
        0,
        135,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_205,
        ACTOR_OBJ_BANK_208,
        &cKF_bs_r_flg_1,
        {
            flg_3_tmem_txt,
            flg_3_pal,
            {
                flg_3_eye1_TA_tex_txt,
                flg_3_eye2_TA_tex_txt,
                flg_3_eye3_TA_tex_txt,
                flg_3_eye4_TA_tex_txt,
                flg_3_eye5_TA_tex_txt,
                flg_3_eye6_TA_tex_txt,
                flg_3_eye7_TA_tex_txt,
                flg_3_eye8_TA_tex_txt,
            },
            {
                flg_3_mouth1_TA_tex_txt,
                flg_3_mouth2_TA_tex_txt,
                flg_3_mouth3_TA_tex_txt,
                flg_3_mouth4_TA_tex_txt,
                flg_3_mouth5_TA_tex_txt,
                flg_3_mouth6_TA_tex_txt,
            },
            0,
            32,
            176,
        },
        0.00800000037997961,
        0,
        2,
        19,
        38,
        0,
        0,
        136,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_205,
        ACTOR_OBJ_BANK_209,
        &cKF_bs_r_flg_1,
        {
            flg_4_tmem_txt,
            flg_4_pal,
            {
                flg_4_eye1_TA_tex_txt,
                flg_4_eye2_TA_tex_txt,
                flg_4_eye3_TA_tex_txt,
                flg_4_eye4_TA_tex_txt,
                flg_4_eye5_TA_tex_txt,
                flg_4_eye6_TA_tex_txt,
                flg_4_eye7_TA_tex_txt,
                flg_4_eye8_TA_tex_txt,
            },
            {
                flg_4_mouth1_TA_tex_txt,
                flg_4_mouth2_TA_tex_txt,
                flg_4_mouth3_TA_tex_txt,
                flg_4_mouth4_TA_tex_txt,
                flg_4_mouth5_TA_tex_txt,
                flg_4_mouth6_TA_tex_txt,
            },
            0,
            32,
            176,
        },
        0.00800000037997961,
        0,
        3,
        25,
        38,
        0,
        0,
        137,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_205,
        ACTOR_OBJ_BANK_210,
        &cKF_bs_r_flg_1,
        {
            flg_5_tmem_txt,
            flg_5_pal,
            {
                flg_5_eye1_TA_tex_txt,
                flg_5_eye2_TA_tex_txt,
                flg_5_eye3_TA_tex_txt,
                flg_5_eye4_TA_tex_txt,
                flg_5_eye5_TA_tex_txt,
                flg_5_eye6_TA_tex_txt,
                flg_5_eye7_TA_tex_txt,
                flg_5_eye8_TA_tex_txt,
            },
            {
                flg_5_mouth1_TA_tex_txt,
                flg_5_mouth2_TA_tex_txt,
                flg_5_mouth3_TA_tex_txt,
                flg_5_mouth4_TA_tex_txt,
                flg_5_mouth5_TA_tex_txt,
                flg_5_mouth6_TA_tex_txt,
            },
            0,
            32,
            176,
        },
        0.00800000037997961,
        0,
        4,
        2,
        38,
        0,
        0,
        138,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_205,
        ACTOR_OBJ_BANK_211,
        &cKF_bs_r_flg_1,
        {
            flg_6_tmem_txt,
            flg_6_pal,
            {
                flg_6_eye1_TA_tex_txt,
                flg_6_eye2_TA_tex_txt,
                flg_6_eye3_TA_tex_txt,
                flg_6_eye4_TA_tex_txt,
                flg_6_eye5_TA_tex_txt,
                flg_6_eye6_TA_tex_txt,
                flg_6_eye7_TA_tex_txt,
                flg_6_eye8_TA_tex_txt,
            },
            {
                flg_6_mouth1_TA_tex_txt,
                flg_6_mouth2_TA_tex_txt,
                flg_6_mouth3_TA_tex_txt,
                flg_6_mouth4_TA_tex_txt,
                flg_6_mouth5_TA_tex_txt,
                flg_6_mouth6_TA_tex_txt,
            },
            0,
            32,
            176,
        },
        0.00800000037997961,
        0,
        5,
        5,
        38,
        0,
        0,
        139,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_205,
        ACTOR_OBJ_BANK_212,
        &cKF_bs_r_flg_1,
        {
            flg_7_tmem_txt,
            flg_7_pal,
            {
                flg_7_eye1_TA_tex_txt,
                flg_7_eye2_TA_tex_txt,
                flg_7_eye3_TA_tex_txt,
                flg_7_eye4_TA_tex_txt,
                flg_7_eye5_TA_tex_txt,
                flg_7_eye6_TA_tex_txt,
                flg_7_eye7_TA_tex_txt,
                flg_7_eye8_TA_tex_txt,
            },
            {
                flg_7_mouth1_TA_tex_txt,
                flg_7_mouth2_TA_tex_txt,
                flg_7_mouth3_TA_tex_txt,
                flg_7_mouth4_TA_tex_txt,
                flg_7_mouth5_TA_tex_txt,
                flg_7_mouth6_TA_tex_txt,
            },
            0,
            32,
            176,
        },
        0.00800000037997961,
        0,
        6,
        13,
        38,
        0,
        0,
        140,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_205,
        ACTOR_OBJ_BANK_213,
        &cKF_bs_r_flg_1,
        {
            flg_8_tmem_txt,
            flg_8_pal,
            {
                flg_8_eye1_TA_tex_txt,
                flg_8_eye2_TA_tex_txt,
                flg_8_eye3_TA_tex_txt,
                flg_8_eye4_TA_tex_txt,
                flg_8_eye5_TA_tex_txt,
                flg_8_eye6_TA_tex_txt,
                flg_8_eye7_TA_tex_txt,
                flg_8_eye8_TA_tex_txt,
            },
            {
                flg_8_mouth1_TA_tex_txt,
                flg_8_mouth2_TA_tex_txt,
                flg_8_mouth3_TA_tex_txt,
                flg_8_mouth4_TA_tex_txt,
                flg_8_mouth5_TA_tex_txt,
                flg_8_mouth6_TA_tex_txt,
            },
            0,
            32,
            176,
        },
        0.00800000037997961,
        0,
        7,
        15,
        38,
        0,
        0,
        141,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_205,
        ACTOR_OBJ_BANK_214,
        &cKF_bs_r_flg_1,
        {
            flg_9_tmem_txt,
            flg_9_pal,
            {
                flg_9_eye1_TA_tex_txt,
                flg_9_eye2_TA_tex_txt,
                flg_9_eye3_TA_tex_txt,
                flg_9_eye4_TA_tex_txt,
                flg_9_eye5_TA_tex_txt,
                flg_9_eye6_TA_tex_txt,
                flg_9_eye7_TA_tex_txt,
                flg_9_eye8_TA_tex_txt,
            },
            {
                flg_9_mouth1_TA_tex_txt,
                flg_9_mouth2_TA_tex_txt,
                flg_9_mouth3_TA_tex_txt,
                flg_9_mouth4_TA_tex_txt,
                flg_9_mouth5_TA_tex_txt,
                flg_9_mouth6_TA_tex_txt,
            },
            0,
            32,
            176,
        },
        0.00800000037997961,
        0,
        8,
        16,
        38,
        0,
        0,
        142,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_205,
        ACTOR_OBJ_BANK_215,
        &cKF_bs_r_flg_1,
        {
            flg_10_tmem_txt,
            flg_10_pal,
            {
                flg_10_eye1_TA_tex_txt,
                flg_10_eye2_TA_tex_txt,
                flg_10_eye3_TA_tex_txt,
                flg_10_eye4_TA_tex_txt,
                flg_10_eye5_TA_tex_txt,
                flg_10_eye6_TA_tex_txt,
                flg_10_eye7_TA_tex_txt,
                flg_10_eye8_TA_tex_txt,
            },
            {
                flg_10_mouth1_TA_tex_txt,
                flg_10_mouth2_TA_tex_txt,
                flg_10_mouth3_TA_tex_txt,
                flg_10_mouth4_TA_tex_txt,
                flg_10_mouth5_TA_tex_txt,
                flg_10_mouth6_TA_tex_txt,
            },
            0,
            32,
            176,
        },
        0.00800000037997961,
        0,
        9,
        30,
        38,
        0,
        0,
        143,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_205,
        ACTOR_OBJ_BANK_216,
        &cKF_bs_r_flg_1,
        {
            flg_11_tmem_txt,
            flg_11_pal,
            {
                flg_11_eye1_TA_tex_txt,
                flg_11_eye2_TA_tex_txt,
                flg_11_eye3_TA_tex_txt,
                flg_11_eye4_TA_tex_txt,
                flg_11_eye5_TA_tex_txt,
                flg_11_eye6_TA_tex_txt,
                flg_11_eye7_TA_tex_txt,
                flg_11_eye8_TA_tex_txt,
            },
            {
                flg_11_mouth1_TA_tex_txt,
                flg_11_mouth2_TA_tex_txt,
                flg_11_mouth3_TA_tex_txt,
                flg_11_mouth4_TA_tex_txt,
                flg_11_mouth5_TA_tex_txt,
                flg_11_mouth6_TA_tex_txt,
            },
            0,
            32,
            176,
        },
        0.00800000037997961,
        0,
        10,
        19,
        38,
        0,
        0,
        144,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_205,
        ACTOR_OBJ_BANK_217,
        &cKF_bs_r_flg_1,
        {
            flg_12_tmem_txt,
            flg_12_pal,
            {
                flg_12_eye1_TA_tex_txt,
                flg_12_eye2_TA_tex_txt,
                flg_12_eye3_TA_tex_txt,
                flg_12_eye4_TA_tex_txt,
                flg_12_eye5_TA_tex_txt,
                flg_12_eye6_TA_tex_txt,
                flg_12_eye7_TA_tex_txt,
                flg_12_eye8_TA_tex_txt,
            },
            {
                flg_12_mouth1_TA_tex_txt,
                flg_12_mouth2_TA_tex_txt,
                flg_12_mouth3_TA_tex_txt,
                flg_12_mouth4_TA_tex_txt,
                flg_12_mouth5_TA_tex_txt,
                flg_12_mouth6_TA_tex_txt,
            },
            0,
            32,
            176,
        },
        0.00800000037997961,
        0,
        11,
        6,
        38,
        0,
        0,
        145,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_220,
        ACTOR_OBJ_BANK_221,
        &cKF_bs_r_goa_1,
        {
            goa_1_tmem_txt,
            goa_1_pal,
            {
                goa_1_eye1_TA_tex_txt,
                goa_1_eye2_TA_tex_txt,
                goa_1_eye3_TA_tex_txt,
                goa_1_eye4_TA_tex_txt,
                goa_1_eye5_TA_tex_txt,
                goa_1_eye6_TA_tex_txt,
                goa_1_eye7_TA_tex_txt,
                goa_1_eye8_TA_tex_txt,
            },
            {
                goa_1_mouth1_TA_tex_txt,
                goa_1_mouth2_TA_tex_txt,
                goa_1_mouth3_TA_tex_txt,
                goa_1_mouth4_TA_tex_txt,
                goa_1_mouth5_TA_tex_txt,
                goa_1_mouth6_TA_tex_txt,
            },
            136,
            88,
            192,
        },
        0.010499999858438969,
        0,
        0,
        12,
        35,
        0,
        0,
        150,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_220,
        ACTOR_OBJ_BANK_222,
        &cKF_bs_r_goa_1,
        {
            goa_2_tmem_txt,
            goa_2_pal,
            {
                goa_2_eye1_TA_tex_txt,
                goa_2_eye2_TA_tex_txt,
                goa_2_eye3_TA_tex_txt,
                goa_2_eye4_TA_tex_txt,
                goa_2_eye5_TA_tex_txt,
                goa_2_eye6_TA_tex_txt,
                goa_2_eye7_TA_tex_txt,
                goa_2_eye8_TA_tex_txt,
            },
            {
                goa_2_mouth1_TA_tex_txt,
                goa_2_mouth2_TA_tex_txt,
                goa_2_mouth3_TA_tex_txt,
                goa_2_mouth4_TA_tex_txt,
                goa_2_mouth5_TA_tex_txt,
                goa_2_mouth6_TA_tex_txt,
            },
            136,
            88,
            192,
        },
        0.010499999858438969,
        0,
        1,
        7,
        35,
        0,
        0,
        151,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_220,
        ACTOR_OBJ_BANK_223,
        &cKF_bs_r_goa_1,
        {
            goa_3_tmem_txt,
            goa_3_pal,
            {
                goa_3_eye1_TA_tex_txt,
                goa_3_eye2_TA_tex_txt,
                goa_3_eye3_TA_tex_txt,
                goa_3_eye4_TA_tex_txt,
                goa_3_eye5_TA_tex_txt,
                goa_3_eye6_TA_tex_txt,
                goa_3_eye7_TA_tex_txt,
                goa_3_eye8_TA_tex_txt,
            },
            {
                goa_3_mouth1_TA_tex_txt,
                goa_3_mouth2_TA_tex_txt,
                goa_3_mouth3_TA_tex_txt,
                goa_3_mouth4_TA_tex_txt,
                goa_3_mouth5_TA_tex_txt,
                goa_3_mouth6_TA_tex_txt,
            },
            136,
            88,
            192,
        },
        0.010499999858438969,
        0,
        2,
        23,
        35,
        0,
        0,
        152,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_220,
        ACTOR_OBJ_BANK_224,
        &cKF_bs_r_goa_1,
        {
            goa_4_tmem_txt,
            goa_4_pal,
            {
                goa_4_eye1_TA_tex_txt,
                goa_4_eye2_TA_tex_txt,
                goa_4_eye3_TA_tex_txt,
                goa_4_eye4_TA_tex_txt,
                goa_4_eye5_TA_tex_txt,
                goa_4_eye6_TA_tex_txt,
                goa_4_eye7_TA_tex_txt,
                goa_4_eye8_TA_tex_txt,
            },
            {
                goa_4_mouth1_TA_tex_txt,
                goa_4_mouth2_TA_tex_txt,
                goa_4_mouth3_TA_tex_txt,
                goa_4_mouth4_TA_tex_txt,
                goa_4_mouth5_TA_tex_txt,
                goa_4_mouth6_TA_tex_txt,
            },
            136,
            88,
            192,
        },
        0.010499999858438969,
        0,
        3,
        31,
        35,
        0,
        0,
        153,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_220,
        ACTOR_OBJ_BANK_225,
        &cKF_bs_r_goa_1,
        {
            goa_5_tmem_txt,
            goa_5_pal,
            {
                goa_5_eye1_TA_tex_txt,
                goa_5_eye2_TA_tex_txt,
                goa_5_eye3_TA_tex_txt,
                goa_5_eye4_TA_tex_txt,
                goa_5_eye5_TA_tex_txt,
                goa_5_eye6_TA_tex_txt,
                goa_5_eye7_TA_tex_txt,
                goa_5_eye8_TA_tex_txt,
            },
            {
                goa_5_mouth1_TA_tex_txt,
                goa_5_mouth2_TA_tex_txt,
                goa_5_mouth3_TA_tex_txt,
                goa_5_mouth4_TA_tex_txt,
                goa_5_mouth5_TA_tex_txt,
                goa_5_mouth6_TA_tex_txt,
            },
            136,
            88,
            192,
        },
        0.010499999858438969,
        0,
        4,
        21,
        35,
        0,
        0,
        154,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_220,
        ACTOR_OBJ_BANK_226,
        &cKF_bs_r_goa_1,
        {
            goa_6_tmem_txt,
            goa_6_pal,
            {
                goa_6_eye1_TA_tex_txt,
                goa_6_eye2_TA_tex_txt,
                goa_6_eye3_TA_tex_txt,
                goa_6_eye4_TA_tex_txt,
                goa_6_eye5_TA_tex_txt,
                goa_6_eye6_TA_tex_txt,
                goa_6_eye7_TA_tex_txt,
                goa_6_eye8_TA_tex_txt,
            },
            {
                goa_6_mouth1_TA_tex_txt,
                goa_6_mouth2_TA_tex_txt,
                goa_6_mouth3_TA_tex_txt,
                goa_6_mouth4_TA_tex_txt,
                goa_6_mouth5_TA_tex_txt,
                goa_6_mouth6_TA_tex_txt,
            },
            136,
            88,
            192,
        },
        0.010499999858438969,
        0,
        5,
        4,
        35,
        0,
        0,
        155,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_227,
        ACTOR_OBJ_BANK_228,
        &cKF_bs_r_gor_1,
        {
            gor_1_tmem_txt,
            gor_1_pal,
            {
                gor_1_eye1_TA_tex_txt,
                gor_1_eye2_TA_tex_txt,
                gor_1_eye3_TA_tex_txt,
                gor_1_eye4_TA_tex_txt,
                gor_1_eye5_TA_tex_txt,
                gor_1_eye6_TA_tex_txt,
                gor_1_eye7_TA_tex_txt,
                gor_1_eye8_TA_tex_txt,
            },
            {
                gor_1_mouth1_TA_tex_txt,
                gor_1_mouth2_TA_tex_txt,
                gor_1_mouth3_TA_tex_txt,
                gor_1_mouth4_TA_tex_txt,
                gor_1_mouth5_TA_tex_txt,
                gor_1_mouth6_TA_tex_txt,
            },
            80,
            112,
            152,
        },
        0.009999999776482582,
        1,
        0,
        15,
        42,
        0,
        0,
        193,
        20,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_227,
        ACTOR_OBJ_BANK_229,
        &cKF_bs_r_gor_1,
        {
            gor_2_tmem_txt,
            gor_2_pal,
            {
                gor_2_eye1_TA_tex_txt,
                gor_2_eye2_TA_tex_txt,
                gor_2_eye3_TA_tex_txt,
                gor_2_eye4_TA_tex_txt,
                gor_2_eye5_TA_tex_txt,
                gor_2_eye6_TA_tex_txt,
                gor_2_eye7_TA_tex_txt,
                gor_2_eye8_TA_tex_txt,
            },
            {
                gor_2_mouth1_TA_tex_txt,
                gor_2_mouth2_TA_tex_txt,
                gor_2_mouth3_TA_tex_txt,
                gor_2_mouth4_TA_tex_txt,
                gor_2_mouth5_TA_tex_txt,
                gor_2_mouth6_TA_tex_txt,
            },
            80,
            112,
            152,
        },
        0.009999999776482582,
        1,
        1,
        14,
        42,
        0,
        0,
        194,
        20,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_227,
        ACTOR_OBJ_BANK_230,
        &cKF_bs_r_gor_1,
        {
            gor_3_tmem_txt,
            gor_3_pal,
            {
                gor_3_eye1_TA_tex_txt,
                gor_3_eye2_TA_tex_txt,
                gor_3_eye3_TA_tex_txt,
                gor_3_eye4_TA_tex_txt,
                gor_3_eye5_TA_tex_txt,
                gor_3_eye6_TA_tex_txt,
                gor_3_eye7_TA_tex_txt,
                gor_3_eye8_TA_tex_txt,
            },
            {
                gor_3_mouth1_TA_tex_txt,
                gor_3_mouth2_TA_tex_txt,
                gor_3_mouth3_TA_tex_txt,
                gor_3_mouth4_TA_tex_txt,
                gor_3_mouth5_TA_tex_txt,
                gor_3_mouth6_TA_tex_txt,
            },
            80,
            112,
            152,
        },
        0.009999999776482582,
        1,
        2,
        5,
        42,
        0,
        0,
        195,
        20,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_227,
        ACTOR_OBJ_BANK_231,
        &cKF_bs_r_gor_1,
        {
            gor_4_tmem_txt,
            gor_4_pal,
            {
                gor_4_eye1_TA_tex_txt,
                gor_4_eye2_TA_tex_txt,
                gor_4_eye3_TA_tex_txt,
                gor_4_eye4_TA_tex_txt,
                gor_4_eye5_TA_tex_txt,
                gor_4_eye6_TA_tex_txt,
                gor_4_eye7_TA_tex_txt,
                gor_4_eye8_TA_tex_txt,
            },
            {
                gor_4_mouth1_TA_tex_txt,
                gor_4_mouth2_TA_tex_txt,
                gor_4_mouth3_TA_tex_txt,
                gor_4_mouth4_TA_tex_txt,
                gor_4_mouth5_TA_tex_txt,
                gor_4_mouth6_TA_tex_txt,
            },
            80,
            112,
            152,
        },
        0.009999999776482582,
        1,
        3,
        19,
        42,
        0,
        0,
        196,
        20,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_238,
        ACTOR_OBJ_BANK_239,
        &cKF_bs_r_hip_1,
        {
            hip_1_tmem_txt,
            hip_1_pal,
            {
                hip_1_eye1_TA_tex_txt,
                hip_1_eye2_TA_tex_txt,
                hip_1_eye3_TA_tex_txt,
                hip_1_eye4_TA_tex_txt,
                hip_1_eye5_TA_tex_txt,
                hip_1_eye6_TA_tex_txt,
                hip_1_eye7_TA_tex_txt,
                hip_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            136,
            0,
            32,
        },
        0.007300000172108412,
        1,
        0,
        11,
        43,
        0,
        0,
        77,
        25,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_238,
        ACTOR_OBJ_BANK_240,
        &cKF_bs_r_hip_1,
        {
            hip_2_tmem_txt,
            hip_2_pal,
            {
                hip_2_eye1_TA_tex_txt,
                hip_2_eye2_TA_tex_txt,
                hip_2_eye3_TA_tex_txt,
                hip_2_eye4_TA_tex_txt,
                hip_2_eye5_TA_tex_txt,
                hip_2_eye6_TA_tex_txt,
                hip_2_eye7_TA_tex_txt,
                hip_2_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            136,
            0,
            32,
        },
        0.007300000172108412,
        1,
        1,
        8,
        43,
        0,
        0,
        78,
        25,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_238,
        ACTOR_OBJ_BANK_241,
        &cKF_bs_r_hip_1,
        {
            hip_3_tmem_txt,
            hip_3_pal,
            {
                hip_3_eye1_TA_tex_txt,
                hip_3_eye2_TA_tex_txt,
                hip_3_eye3_TA_tex_txt,
                hip_3_eye4_TA_tex_txt,
                hip_3_eye5_TA_tex_txt,
                hip_3_eye6_TA_tex_txt,
                hip_3_eye7_TA_tex_txt,
                hip_3_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            136,
            0,
            32,
        },
        0.007300000172108412,
        1,
        2,
        7,
        43,
        0,
        0,
        79,
        25,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_243,
        ACTOR_OBJ_BANK_244,
        &cKF_bs_r_hrs_1,
        {
            hrs_1_tmem_txt,
            hrs_1_pal,
            {
                hrs_1_eye1_TA_tex_txt,
                hrs_1_eye2_TA_tex_txt,
                hrs_1_eye3_TA_tex_txt,
                hrs_1_eye4_TA_tex_txt,
                hrs_1_eye5_TA_tex_txt,
                hrs_1_eye6_TA_tex_txt,
                hrs_1_eye7_TA_tex_txt,
                hrs_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            40,
            0,
            184,
        },
        0.011500000022351742,
        1,
        0,
        0,
        43,
        0,
        0,
        169,
        23,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_243,
        ACTOR_OBJ_BANK_245,
        &cKF_bs_r_hrs_1,
        {
            hrs_2_tmem_txt,
            hrs_2_pal,
            {
                hrs_2_eye1_TA_tex_txt,
                hrs_2_eye2_TA_tex_txt,
                hrs_2_eye3_TA_tex_txt,
                hrs_2_eye4_TA_tex_txt,
                hrs_2_eye5_TA_tex_txt,
                hrs_2_eye6_TA_tex_txt,
                hrs_2_eye7_TA_tex_txt,
                hrs_2_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            40,
            0,
            184,
        },
        0.011500000022351742,
        1,
        1,
        7,
        43,
        0,
        0,
        170,
        23,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_243,
        ACTOR_OBJ_BANK_246,
        &cKF_bs_r_hrs_1,
        {
            hrs_3_tmem_txt,
            hrs_3_pal,
            {
                hrs_3_eye1_TA_tex_txt,
                hrs_3_eye2_TA_tex_txt,
                hrs_3_eye3_TA_tex_txt,
                hrs_3_eye4_TA_tex_txt,
                hrs_3_eye5_TA_tex_txt,
                hrs_3_eye6_TA_tex_txt,
                hrs_3_eye7_TA_tex_txt,
                hrs_3_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            40,
            0,
            184,
        },
        0.011500000022351742,
        1,
        2,
        29,
        43,
        0,
        0,
        171,
        23,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_243,
        ACTOR_OBJ_BANK_247,
        &cKF_bs_r_hrs_1,
        {
            hrs_4_tmem_txt,
            hrs_4_pal,
            {
                hrs_4_eye1_TA_tex_txt,
                hrs_4_eye2_TA_tex_txt,
                hrs_4_eye3_TA_tex_txt,
                hrs_4_eye4_TA_tex_txt,
                hrs_4_eye5_TA_tex_txt,
                hrs_4_eye6_TA_tex_txt,
                hrs_4_eye7_TA_tex_txt,
                hrs_4_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            40,
            0,
            184,
        },
        0.011500000022351742,
        1,
        3,
        17,
        43,
        0,
        0,
        172,
        23,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_243,
        ACTOR_OBJ_BANK_248,
        &cKF_bs_r_hrs_1,
        {
            hrs_5_tmem_txt,
            hrs_5_pal,
            {
                hrs_5_eye1_TA_tex_txt,
                hrs_5_eye2_TA_tex_txt,
                hrs_5_eye3_TA_tex_txt,
                hrs_5_eye4_TA_tex_txt,
                hrs_5_eye5_TA_tex_txt,
                hrs_5_eye6_TA_tex_txt,
                hrs_5_eye7_TA_tex_txt,
                hrs_5_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            40,
            0,
            184,
        },
        0.011500000022351742,
        1,
        4,
        29,
        43,
        0,
        0,
        173,
        23,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_243,
        ACTOR_OBJ_BANK_249,
        &cKF_bs_r_hrs_1,
        {
            hrs_6_tmem_txt,
            hrs_6_pal,
            {
                hrs_6_eye1_TA_tex_txt,
                hrs_6_eye2_TA_tex_txt,
                hrs_6_eye3_TA_tex_txt,
                hrs_6_eye4_TA_tex_txt,
                hrs_6_eye5_TA_tex_txt,
                hrs_6_eye6_TA_tex_txt,
                hrs_6_eye7_TA_tex_txt,
                hrs_6_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            40,
            0,
            184,
        },
        0.011500000022351742,
        1,
        5,
        2,
        43,
        0,
        0,
        174,
        23,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_243,
        ACTOR_OBJ_BANK_250,
        &cKF_bs_r_hrs_1,
        {
            hrs_7_tmem_txt,
            hrs_7_pal,
            {
                hrs_7_eye1_TA_tex_txt,
                hrs_7_eye2_TA_tex_txt,
                hrs_7_eye3_TA_tex_txt,
                hrs_7_eye4_TA_tex_txt,
                hrs_7_eye5_TA_tex_txt,
                hrs_7_eye6_TA_tex_txt,
                hrs_7_eye7_TA_tex_txt,
                hrs_7_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            40,
            0,
            184,
        },
        0.011500000022351742,
        1,
        6,
        23,
        43,
        0,
        0,
        175,
        23,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_253,
        ACTOR_OBJ_BANK_254,
        &cKF_bs_r_kgr_1,
        {
            kgr_1_tmem_txt,
            kgr_1_pal,
            {
                kgr_1_eye1_TA_tex_txt,
                kgr_1_eye2_TA_tex_txt,
                kgr_1_eye3_TA_tex_txt,
                kgr_1_eye4_TA_tex_txt,
                kgr_1_eye5_TA_tex_txt,
                kgr_1_eye6_TA_tex_txt,
                kgr_1_eye7_TA_tex_txt,
                kgr_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            88,
            0,
            128,
        },
        0.010499999858438969,
        1,
        0,
        7,
        41,
        0,
        0,
        201,
        23,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_253,
        ACTOR_OBJ_BANK_255,
        &cKF_bs_r_kgr_1,
        {
            kgr_2_tmem_txt,
            kgr_2_pal,
            {
                kgr_2_eye1_TA_tex_txt,
                kgr_2_eye2_TA_tex_txt,
                kgr_2_eye3_TA_tex_txt,
                kgr_2_eye4_TA_tex_txt,
                kgr_2_eye5_TA_tex_txt,
                kgr_2_eye6_TA_tex_txt,
                kgr_2_eye7_TA_tex_txt,
                kgr_2_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            88,
            0,
            128,
        },
        0.010499999858438969,
        1,
        1,
        10,
        41,
        0,
        0,
        202,
        23,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_253,
        ACTOR_OBJ_BANK_256,
        &cKF_bs_r_kgr_1,
        {
            kgr_3_tmem_txt,
            kgr_3_pal,
            {
                kgr_3_eye1_TA_tex_txt,
                kgr_3_eye2_TA_tex_txt,
                kgr_3_eye3_TA_tex_txt,
                kgr_3_eye4_TA_tex_txt,
                kgr_3_eye5_TA_tex_txt,
                kgr_3_eye6_TA_tex_txt,
                kgr_3_eye7_TA_tex_txt,
                kgr_3_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            88,
            0,
            128,
        },
        0.010499999858438969,
        1,
        2,
        22,
        41,
        0,
        0,
        203,
        23,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_253,
        ACTOR_OBJ_BANK_257,
        &cKF_bs_r_kgr_1,
        {
            kgr_4_tmem_txt,
            kgr_4_pal,
            {
                kgr_4_eye1_TA_tex_txt,
                kgr_4_eye2_TA_tex_txt,
                kgr_4_eye3_TA_tex_txt,
                kgr_4_eye4_TA_tex_txt,
                kgr_4_eye5_TA_tex_txt,
                kgr_4_eye6_TA_tex_txt,
                kgr_4_eye7_TA_tex_txt,
                kgr_4_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            88,
            0,
            128,
        },
        0.010499999858438969,
        1,
        3,
        3,
        41,
        0,
        0,
        204,
        23,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_253,
        ACTOR_OBJ_BANK_258,
        &cKF_bs_r_kgr_1,
        {
            kgr_5_tmem_txt,
            kgr_5_pal,
            {
                kgr_5_eye1_TA_tex_txt,
                kgr_5_eye2_TA_tex_txt,
                kgr_5_eye3_TA_tex_txt,
                kgr_5_eye4_TA_tex_txt,
                kgr_5_eye5_TA_tex_txt,
                kgr_5_eye6_TA_tex_txt,
                kgr_5_eye7_TA_tex_txt,
                kgr_5_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            88,
            0,
            128,
        },
        0.010499999858438969,
        1,
        4,
        27,
        41,
        0,
        0,
        205,
        23,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_253,
        ACTOR_OBJ_BANK_259,
        &cKF_bs_r_kgr_1,
        {
            kgr_6_tmem_txt,
            kgr_6_pal,
            {
                kgr_6_eye1_TA_tex_txt,
                kgr_6_eye2_TA_tex_txt,
                kgr_6_eye3_TA_tex_txt,
                kgr_6_eye4_TA_tex_txt,
                kgr_6_eye5_TA_tex_txt,
                kgr_6_eye6_TA_tex_txt,
                kgr_6_eye7_TA_tex_txt,
                kgr_6_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            88,
            0,
            128,
        },
        0.010499999858438969,
        1,
        5,
        31,
        41,
        0,
        0,
        206,
        23,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_262,
        ACTOR_OBJ_BANK_263,
        &cKF_bs_r_kal_1,
        {
            kal_1_tmem_txt,
            kal_1_pal,
            {
                kal_1_eye1_TA_tex_txt,
                kal_1_eye2_TA_tex_txt,
                kal_1_eye3_TA_tex_txt,
                kal_1_eye4_TA_tex_txt,
                kal_1_eye5_TA_tex_txt,
                kal_1_eye6_TA_tex_txt,
                kal_1_eye7_TA_tex_txt,
                kal_1_eye8_TA_tex_txt,
            },
            {
                kal_1_mouth1_TA_tex_txt,
                kal_1_mouth2_TA_tex_txt,
                kal_1_mouth3_TA_tex_txt,
                kal_1_mouth4_TA_tex_txt,
                kal_1_mouth5_TA_tex_txt,
                kal_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            192,
        },
        0.008500000461935997,
        0,
        0,
        22,
        34,
        0,
        0,
        164,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_262,
        ACTOR_OBJ_BANK_264,
        &cKF_bs_r_kal_1,
        {
            kal_2_tmem_txt,
            kal_2_pal,
            {
                kal_2_eye1_TA_tex_txt,
                kal_2_eye2_TA_tex_txt,
                kal_2_eye3_TA_tex_txt,
                kal_2_eye4_TA_tex_txt,
                kal_2_eye5_TA_tex_txt,
                kal_2_eye6_TA_tex_txt,
                kal_2_eye7_TA_tex_txt,
                kal_2_eye8_TA_tex_txt,
            },
            {
                kal_2_mouth1_TA_tex_txt,
                kal_2_mouth2_TA_tex_txt,
                kal_2_mouth3_TA_tex_txt,
                kal_2_mouth4_TA_tex_txt,
                kal_2_mouth5_TA_tex_txt,
                kal_2_mouth6_TA_tex_txt,
            },
            0,
            32,
            192,
        },
        0.008500000461935997,
        0,
        1,
        16,
        34,
        0,
        0,
        165,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_262,
        ACTOR_OBJ_BANK_265,
        &cKF_bs_r_kal_1,
        {
            kal_3_tmem_txt,
            kal_3_pal,
            {
                kal_3_eye1_TA_tex_txt,
                kal_3_eye2_TA_tex_txt,
                kal_3_eye3_TA_tex_txt,
                kal_3_eye4_TA_tex_txt,
                kal_3_eye5_TA_tex_txt,
                kal_3_eye6_TA_tex_txt,
                kal_3_eye7_TA_tex_txt,
                kal_3_eye8_TA_tex_txt,
            },
            {
                kal_3_mouth1_TA_tex_txt,
                kal_3_mouth2_TA_tex_txt,
                kal_3_mouth3_TA_tex_txt,
                kal_3_mouth4_TA_tex_txt,
                kal_3_mouth5_TA_tex_txt,
                kal_3_mouth6_TA_tex_txt,
            },
            0,
            32,
            192,
        },
        0.008500000461935997,
        0,
        2,
        19,
        34,
        0,
        0,
        166,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_262,
        ACTOR_OBJ_BANK_266,
        &cKF_bs_r_kal_1,
        {
            kal_4_tmem_txt,
            kal_4_pal,
            {
                kal_4_eye1_TA_tex_txt,
                kal_4_eye2_TA_tex_txt,
                kal_4_eye3_TA_tex_txt,
                kal_4_eye4_TA_tex_txt,
                kal_4_eye5_TA_tex_txt,
                kal_4_eye6_TA_tex_txt,
                kal_4_eye7_TA_tex_txt,
                kal_4_eye8_TA_tex_txt,
            },
            {
                kal_4_mouth1_TA_tex_txt,
                kal_4_mouth2_TA_tex_txt,
                kal_4_mouth3_TA_tex_txt,
                kal_4_mouth4_TA_tex_txt,
                kal_4_mouth5_TA_tex_txt,
                kal_4_mouth6_TA_tex_txt,
            },
            0,
            32,
            192,
        },
        0.008500000461935997,
        0,
        3,
        1,
        34,
        0,
        0,
        167,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_262,
        ACTOR_OBJ_BANK_267,
        &cKF_bs_r_kal_1,
        {
            kal_5_tmem_txt,
            kal_5_pal,
            {
                kal_5_eye1_TA_tex_txt,
                kal_5_eye2_TA_tex_txt,
                kal_5_eye3_TA_tex_txt,
                kal_5_eye4_TA_tex_txt,
                kal_5_eye5_TA_tex_txt,
                kal_5_eye6_TA_tex_txt,
                kal_5_eye7_TA_tex_txt,
                kal_5_eye8_TA_tex_txt,
            },
            {
                kal_5_mouth1_TA_tex_txt,
                kal_5_mouth2_TA_tex_txt,
                kal_5_mouth3_TA_tex_txt,
                kal_5_mouth4_TA_tex_txt,
                kal_5_mouth5_TA_tex_txt,
                kal_5_mouth6_TA_tex_txt,
            },
            0,
            32,
            192,
        },
        0.008500000461935997,
        0,
        4,
        6,
        34,
        0,
        0,
        168,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_268,
        ACTOR_OBJ_BANK_269,
        &cKF_bs_r_lon_1,
        {
            lon_1_tmem_txt,
            lon_1_pal,
            {
                lon_1_eye1_TA_tex_txt,
                lon_1_eye2_TA_tex_txt,
                lon_1_eye3_TA_tex_txt,
                lon_1_eye4_TA_tex_txt,
                lon_1_eye5_TA_tex_txt,
                lon_1_eye6_TA_tex_txt,
                lon_1_eye7_TA_tex_txt,
                lon_1_eye8_TA_tex_txt,
            },
            {
                lon_1_mouth1_TA_tex_txt,
                lon_1_mouth2_TA_tex_txt,
                lon_1_mouth3_TA_tex_txt,
                lon_1_mouth4_TA_tex_txt,
                lon_1_mouth5_TA_tex_txt,
                lon_1_mouth6_TA_tex_txt,
            },
            128,
            96,
            184,
        },
        0.01140000019222498,
        0,
        0,
        22,
        43,
        0,
        0,
        177,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_268,
        ACTOR_OBJ_BANK_270,
        &cKF_bs_r_lon_1,
        {
            lon_2_tmem_txt,
            lon_2_pal,
            {
                lon_2_eye1_TA_tex_txt,
                lon_2_eye2_TA_tex_txt,
                lon_2_eye3_TA_tex_txt,
                lon_2_eye4_TA_tex_txt,
                lon_2_eye5_TA_tex_txt,
                lon_2_eye6_TA_tex_txt,
                lon_2_eye7_TA_tex_txt,
                lon_2_eye8_TA_tex_txt,
            },
            {
                lon_2_mouth1_TA_tex_txt,
                lon_2_mouth2_TA_tex_txt,
                lon_2_mouth3_TA_tex_txt,
                lon_2_mouth4_TA_tex_txt,
                lon_2_mouth5_TA_tex_txt,
                lon_2_mouth6_TA_tex_txt,
            },
            128,
            96,
            184,
        },
        0.01140000019222498,
        0,
        1,
        24,
        43,
        0,
        0,
        178,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_268,
        ACTOR_OBJ_BANK_271,
        &cKF_bs_r_lon_1,
        {
            lon_3_tmem_txt,
            lon_3_pal,
            {
                lon_3_eye1_TA_tex_txt,
                lon_3_eye2_TA_tex_txt,
                lon_3_eye3_TA_tex_txt,
                lon_3_eye4_TA_tex_txt,
                lon_3_eye5_TA_tex_txt,
                lon_3_eye6_TA_tex_txt,
                lon_3_eye7_TA_tex_txt,
                lon_3_eye8_TA_tex_txt,
            },
            {
                lon_3_mouth1_TA_tex_txt,
                lon_3_mouth2_TA_tex_txt,
                lon_3_mouth3_TA_tex_txt,
                lon_3_mouth4_TA_tex_txt,
                lon_3_mouth5_TA_tex_txt,
                lon_3_mouth6_TA_tex_txt,
            },
            128,
            96,
            184,
        },
        0.01140000019222498,
        0,
        2,
        12,
        43,
        0,
        0,
        179,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_274,
        ACTOR_OBJ_BANK_275,
        &cKF_bs_r_mus_1,
        {
            mus_1_tmem_txt,
            mus_1_pal,
            {
                mus_1_eye1_TA_tex_txt,
                mus_1_eye2_TA_tex_txt,
                mus_1_eye3_TA_tex_txt,
                mus_1_eye4_TA_tex_txt,
                mus_1_eye5_TA_tex_txt,
                mus_1_eye6_TA_tex_txt,
                mus_1_eye7_TA_tex_txt,
                mus_1_eye8_TA_tex_txt,
            },
            {
                mus_1_mouth1_TA_tex_txt,
                mus_1_mouth2_TA_tex_txt,
                mus_1_mouth3_TA_tex_txt,
                mus_1_mouth4_TA_tex_txt,
                mus_1_mouth5_TA_tex_txt,
                mus_1_mouth6_TA_tex_txt,
            },
            96,
            128,
            184,
        },
        0.005499999970197678,
        0,
        0,
        3,
        30,
        0,
        0,
        89,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_274,
        ACTOR_OBJ_BANK_276,
        &cKF_bs_r_mus_1,
        {
            mus_2_tmem_txt,
            mus_2_pal,
            {
                mus_2_eye1_TA_tex_txt,
                mus_2_eye2_TA_tex_txt,
                mus_2_eye3_TA_tex_txt,
                mus_2_eye4_TA_tex_txt,
                mus_2_eye5_TA_tex_txt,
                mus_2_eye6_TA_tex_txt,
                mus_2_eye7_TA_tex_txt,
                mus_2_eye8_TA_tex_txt,
            },
            {
                mus_2_mouth1_TA_tex_txt,
                mus_2_mouth2_TA_tex_txt,
                mus_2_mouth3_TA_tex_txt,
                mus_2_mouth4_TA_tex_txt,
                mus_2_mouth5_TA_tex_txt,
                mus_2_mouth6_TA_tex_txt,
            },
            96,
            128,
            184,
        },
        0.005499999970197678,
        0,
        1,
        19,
        30,
        0,
        0,
        90,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_274,
        ACTOR_OBJ_BANK_277,
        &cKF_bs_r_mus_1,
        {
            mus_3_tmem_txt,
            mus_3_pal,
            {
                mus_3_eye1_TA_tex_txt,
                mus_3_eye2_TA_tex_txt,
                mus_3_eye3_TA_tex_txt,
                mus_3_eye4_TA_tex_txt,
                mus_3_eye5_TA_tex_txt,
                mus_3_eye6_TA_tex_txt,
                mus_3_eye7_TA_tex_txt,
                mus_3_eye8_TA_tex_txt,
            },
            {
                mus_3_mouth1_TA_tex_txt,
                mus_3_mouth2_TA_tex_txt,
                mus_3_mouth3_TA_tex_txt,
                mus_3_mouth4_TA_tex_txt,
                mus_3_mouth5_TA_tex_txt,
                mus_3_mouth6_TA_tex_txt,
            },
            96,
            128,
            184,
        },
        0.005499999970197678,
        0,
        2,
        23,
        30,
        0,
        0,
        91,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_274,
        ACTOR_OBJ_BANK_278,
        &cKF_bs_r_mus_1,
        {
            mus_4_tmem_txt,
            mus_4_pal,
            {
                mus_4_eye1_TA_tex_txt,
                mus_4_eye2_TA_tex_txt,
                mus_4_eye3_TA_tex_txt,
                mus_4_eye4_TA_tex_txt,
                mus_4_eye5_TA_tex_txt,
                mus_4_eye6_TA_tex_txt,
                mus_4_eye7_TA_tex_txt,
                mus_4_eye8_TA_tex_txt,
            },
            {
                mus_4_mouth1_TA_tex_txt,
                mus_4_mouth2_TA_tex_txt,
                mus_4_mouth3_TA_tex_txt,
                mus_4_mouth4_TA_tex_txt,
                mus_4_mouth5_TA_tex_txt,
                mus_4_mouth6_TA_tex_txt,
            },
            96,
            128,
            184,
        },
        0.005499999970197678,
        0,
        3,
        13,
        30,
        0,
        0,
        92,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_274,
        ACTOR_OBJ_BANK_279,
        &cKF_bs_r_mus_1,
        {
            mus_5_tmem_txt,
            mus_5_pal,
            {
                mus_5_eye1_TA_tex_txt,
                mus_5_eye2_TA_tex_txt,
                mus_5_eye3_TA_tex_txt,
                mus_5_eye4_TA_tex_txt,
                mus_5_eye5_TA_tex_txt,
                mus_5_eye6_TA_tex_txt,
                mus_5_eye7_TA_tex_txt,
                mus_5_eye8_TA_tex_txt,
            },
            {
                mus_5_mouth1_TA_tex_txt,
                mus_5_mouth2_TA_tex_txt,
                mus_5_mouth3_TA_tex_txt,
                mus_5_mouth4_TA_tex_txt,
                mus_5_mouth5_TA_tex_txt,
                mus_5_mouth6_TA_tex_txt,
            },
            96,
            128,
            184,
        },
        0.005499999970197678,
        0,
        4,
        5,
        30,
        0,
        0,
        93,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_274,
        ACTOR_OBJ_BANK_280,
        &cKF_bs_r_mus_1,
        {
            mus_6_tmem_txt,
            mus_6_pal,
            {
                mus_6_eye1_TA_tex_txt,
                mus_6_eye2_TA_tex_txt,
                mus_6_eye3_TA_tex_txt,
                mus_6_eye4_TA_tex_txt,
                mus_6_eye5_TA_tex_txt,
                mus_6_eye6_TA_tex_txt,
                mus_6_eye7_TA_tex_txt,
                mus_6_eye8_TA_tex_txt,
            },
            {
                mus_6_mouth1_TA_tex_txt,
                mus_6_mouth2_TA_tex_txt,
                mus_6_mouth3_TA_tex_txt,
                mus_6_mouth4_TA_tex_txt,
                mus_6_mouth5_TA_tex_txt,
                mus_6_mouth6_TA_tex_txt,
            },
            96,
            128,
            184,
        },
        0.005499999970197678,
        0,
        5,
        26,
        30,
        0,
        0,
        94,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_274,
        ACTOR_OBJ_BANK_281,
        &cKF_bs_r_mus_1,
        {
            mus_7_tmem_txt,
            mus_7_pal,
            {
                mus_7_eye1_TA_tex_txt,
                mus_7_eye2_TA_tex_txt,
                mus_7_eye3_TA_tex_txt,
                mus_7_eye4_TA_tex_txt,
                mus_7_eye5_TA_tex_txt,
                mus_7_eye6_TA_tex_txt,
                mus_7_eye7_TA_tex_txt,
                mus_7_eye8_TA_tex_txt,
            },
            {
                mus_7_mouth1_TA_tex_txt,
                mus_7_mouth2_TA_tex_txt,
                mus_7_mouth3_TA_tex_txt,
                mus_7_mouth4_TA_tex_txt,
                mus_7_mouth5_TA_tex_txt,
                mus_7_mouth6_TA_tex_txt,
            },
            96,
            128,
            184,
        },
        0.005499999970197678,
        0,
        6,
        2,
        30,
        0,
        0,
        95,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_274,
        ACTOR_OBJ_BANK_282,
        &cKF_bs_r_mus_1,
        {
            mus_8_tmem_txt,
            mus_8_pal,
            {
                mus_8_eye1_TA_tex_txt,
                mus_8_eye2_TA_tex_txt,
                mus_8_eye3_TA_tex_txt,
                mus_8_eye4_TA_tex_txt,
                mus_8_eye5_TA_tex_txt,
                mus_8_eye6_TA_tex_txt,
                mus_8_eye7_TA_tex_txt,
                mus_8_eye8_TA_tex_txt,
            },
            {
                mus_8_mouth1_TA_tex_txt,
                mus_8_mouth2_TA_tex_txt,
                mus_8_mouth3_TA_tex_txt,
                mus_8_mouth4_TA_tex_txt,
                mus_8_mouth5_TA_tex_txt,
                mus_8_mouth6_TA_tex_txt,
            },
            96,
            128,
            184,
        },
        0.005499999970197678,
        0,
        7,
        24,
        30,
        0,
        0,
        96,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_274,
        ACTOR_OBJ_BANK_283,
        &cKF_bs_r_mus_1,
        {
            mus_9_tmem_txt,
            mus_9_pal,
            {
                mus_9_eye1_TA_tex_txt,
                mus_9_eye2_TA_tex_txt,
                mus_9_eye3_TA_tex_txt,
                mus_9_eye4_TA_tex_txt,
                mus_9_eye5_TA_tex_txt,
                mus_9_eye6_TA_tex_txt,
                mus_9_eye7_TA_tex_txt,
                mus_9_eye8_TA_tex_txt,
            },
            {
                mus_9_mouth1_TA_tex_txt,
                mus_9_mouth2_TA_tex_txt,
                mus_9_mouth3_TA_tex_txt,
                mus_9_mouth4_TA_tex_txt,
                mus_9_mouth5_TA_tex_txt,
                mus_9_mouth6_TA_tex_txt,
            },
            96,
            128,
            184,
        },
        0.005499999970197678,
        0,
        8,
        5,
        30,
        0,
        0,
        97,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_284,
        ACTOR_OBJ_BANK_285,
        &cKF_bs_r_oct_1,
        {
            oct_1_tmem_txt,
            oct_1_pal,
            {
                oct_1_eye1_TA_tex_txt,
                oct_1_eye2_TA_tex_txt,
                oct_1_eye3_TA_tex_txt,
                oct_1_eye4_TA_tex_txt,
                oct_1_eye5_TA_tex_txt,
                oct_1_eye6_TA_tex_txt,
                oct_1_eye7_TA_tex_txt,
                oct_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            0,
            0,
            80,
        },
        0.00930000003427267,
        1,
        0,
        26,
        35,
        0,
        0,
        176,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_286,
        ACTOR_OBJ_BANK_287,
        &cKF_bs_r_ost_1,
        {
            ost_1_tmem_txt,
            ost_1_pal,
            {
                ost_1_eye1_TA_tex_txt,
                ost_1_eye2_TA_tex_txt,
                ost_1_eye3_TA_tex_txt,
                ost_1_eye4_TA_tex_txt,
                ost_1_eye5_TA_tex_txt,
                ost_1_eye6_TA_tex_txt,
                ost_1_eye7_TA_tex_txt,
                ost_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            56,
            0,
            160,
        },
        0.011500000022351742,
        1,
        0,
        0,
        44,
        0,
        0,
        197,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_286,
        ACTOR_OBJ_BANK_288,
        &cKF_bs_r_ost_1,
        {
            ost_2_tmem_txt,
            ost_2_pal,
            {
                ost_2_eye1_TA_tex_txt,
                ost_2_eye2_TA_tex_txt,
                ost_2_eye3_TA_tex_txt,
                ost_2_eye4_TA_tex_txt,
                ost_2_eye5_TA_tex_txt,
                ost_2_eye6_TA_tex_txt,
                ost_2_eye7_TA_tex_txt,
                ost_2_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            56,
            0,
            160,
        },
        0.011500000022351742,
        1,
        1,
        31,
        44,
        0,
        0,
        198,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_286,
        ACTOR_OBJ_BANK_289,
        &cKF_bs_r_ost_1,
        {
            ost_3_tmem_txt,
            ost_3_pal,
            {
                ost_3_eye1_TA_tex_txt,
                ost_3_eye2_TA_tex_txt,
                ost_3_eye3_TA_tex_txt,
                ost_3_eye4_TA_tex_txt,
                ost_3_eye5_TA_tex_txt,
                ost_3_eye6_TA_tex_txt,
                ost_3_eye7_TA_tex_txt,
                ost_3_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            56,
            0,
            160,
        },
        0.011500000022351742,
        1,
        2,
        11,
        44,
        0,
        0,
        199,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_286,
        ACTOR_OBJ_BANK_290,
        &cKF_bs_r_ost_1,
        {
            ost_4_tmem_txt,
            ost_4_pal,
            {
                ost_4_eye1_TA_tex_txt,
                ost_4_eye2_TA_tex_txt,
                ost_4_eye3_TA_tex_txt,
                ost_4_eye4_TA_tex_txt,
                ost_4_eye5_TA_tex_txt,
                ost_4_eye6_TA_tex_txt,
                ost_4_eye7_TA_tex_txt,
                ost_4_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            56,
            0,
            160,
        },
        0.011500000022351742,
        1,
        3,
        9,
        44,
        0,
        0,
        200,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_107,
        ACTOR_OBJ_BANK_108,
        &cKF_bs_r_pbr_1,
        {
            pbr_1_tmem_txt,
            pbr_1_pal,
            {
                pbr_1_eye1_TA_tex_txt,
                pbr_1_eye2_TA_tex_txt,
                pbr_1_eye3_TA_tex_txt,
                pbr_1_eye4_TA_tex_txt,
                pbr_1_eye5_TA_tex_txt,
                pbr_1_eye6_TA_tex_txt,
                pbr_1_eye7_TA_tex_txt,
                pbr_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            40,
            0,
            144,
        },
        0.013000000268220901,
        1,
        0,
        21,
        46,
        0,
        0,
        207,
        23,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_107,
        ACTOR_OBJ_BANK_109,
        &cKF_bs_r_pbr_1,
        {
            pbr_2_tmem_txt,
            pbr_2_pal,
            {
                pbr_2_eye1_TA_tex_txt,
                pbr_2_eye2_TA_tex_txt,
                pbr_2_eye3_TA_tex_txt,
                pbr_2_eye4_TA_tex_txt,
                pbr_2_eye5_TA_tex_txt,
                pbr_2_eye6_TA_tex_txt,
                pbr_2_eye7_TA_tex_txt,
                pbr_2_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            40,
            0,
            144,
        },
        0.013000000268220901,
        1,
        1,
        24,
        46,
        0,
        0,
        208,
        23,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_107,
        ACTOR_OBJ_BANK_110,
        &cKF_bs_r_pbr_1,
        {
            pbr_3_tmem_txt,
            pbr_3_pal,
            {
                pbr_3_eye1_TA_tex_txt,
                pbr_3_eye2_TA_tex_txt,
                pbr_3_eye3_TA_tex_txt,
                pbr_3_eye4_TA_tex_txt,
                pbr_3_eye5_TA_tex_txt,
                pbr_3_eye6_TA_tex_txt,
                pbr_3_eye7_TA_tex_txt,
                pbr_3_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            40,
            0,
            144,
        },
        0.013000000268220901,
        1,
        2,
        18,
        46,
        0,
        0,
        209,
        23,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_107,
        ACTOR_OBJ_BANK_111,
        &cKF_bs_r_pbr_1,
        {
            pbr_4_tmem_txt,
            pbr_4_pal,
            {
                pbr_4_eye1_TA_tex_txt,
                pbr_4_eye2_TA_tex_txt,
                pbr_4_eye3_TA_tex_txt,
                pbr_4_eye4_TA_tex_txt,
                pbr_4_eye5_TA_tex_txt,
                pbr_4_eye6_TA_tex_txt,
                pbr_4_eye7_TA_tex_txt,
                pbr_4_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            40,
            0,
            144,
        },
        0.013000000268220901,
        1,
        3,
        1,
        46,
        0,
        0,
        210,
        23,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_107,
        ACTOR_OBJ_BANK_112,
        &cKF_bs_r_pbr_1,
        {
            pbr_5_tmem_txt,
            pbr_5_pal,
            {
                pbr_5_eye1_TA_tex_txt,
                pbr_5_eye2_TA_tex_txt,
                pbr_5_eye3_TA_tex_txt,
                pbr_5_eye4_TA_tex_txt,
                pbr_5_eye5_TA_tex_txt,
                pbr_5_eye6_TA_tex_txt,
                pbr_5_eye7_TA_tex_txt,
                pbr_5_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            40,
            0,
            144,
        },
        0.013000000268220901,
        1,
        4,
        28,
        46,
        0,
        0,
        211,
        23,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_291,
        ACTOR_OBJ_BANK_292,
        &cKF_bs_r_pgn_1,
        {
            pgn_1_tmem_txt,
            pgn_1_pal,
            {
                pgn_1_eye1_TA_tex_txt,
                pgn_1_eye2_TA_tex_txt,
                pgn_1_eye3_TA_tex_txt,
                pgn_1_eye4_TA_tex_txt,
                pgn_1_eye5_TA_tex_txt,
                pgn_1_eye6_TA_tex_txt,
                pgn_1_eye7_TA_tex_txt,
                pgn_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            48,
            0,
            144,
        },
        0.007499999832361937,
        1,
        0,
        1,
        31,
        0,
        0,
        212,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_291,
        ACTOR_OBJ_BANK_293,
        &cKF_bs_r_pgn_1,
        {
            pgn_2_tmem_txt,
            pgn_2_pal,
            {
                pgn_2_eye1_TA_tex_txt,
                pgn_2_eye2_TA_tex_txt,
                pgn_2_eye3_TA_tex_txt,
                pgn_2_eye4_TA_tex_txt,
                pgn_2_eye5_TA_tex_txt,
                pgn_2_eye6_TA_tex_txt,
                pgn_2_eye7_TA_tex_txt,
                pgn_2_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            48,
            0,
            144,
        },
        0.007499999832361937,
        1,
        1,
        3,
        31,
        0,
        0,
        213,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_291,
        ACTOR_OBJ_BANK_294,
        &cKF_bs_r_pgn_1,
        {
            pgn_3_tmem_txt,
            pgn_3_pal,
            {
                pgn_3_eye1_TA_tex_txt,
                pgn_3_eye2_TA_tex_txt,
                pgn_3_eye3_TA_tex_txt,
                pgn_3_eye4_TA_tex_txt,
                pgn_3_eye5_TA_tex_txt,
                pgn_3_eye6_TA_tex_txt,
                pgn_3_eye7_TA_tex_txt,
                pgn_3_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            48,
            0,
            144,
        },
        0.007499999832361937,
        1,
        2,
        31,
        31,
        0,
        0,
        214,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_291,
        ACTOR_OBJ_BANK_295,
        &cKF_bs_r_pgn_1,
        {
            pgn_4_tmem_txt,
            pgn_4_pal,
            {
                pgn_4_eye1_TA_tex_txt,
                pgn_4_eye2_TA_tex_txt,
                pgn_4_eye3_TA_tex_txt,
                pgn_4_eye4_TA_tex_txt,
                pgn_4_eye5_TA_tex_txt,
                pgn_4_eye6_TA_tex_txt,
                pgn_4_eye7_TA_tex_txt,
                pgn_4_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            48,
            0,
            144,
        },
        0.007499999832361937,
        1,
        3,
        5,
        31,
        0,
        0,
        215,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_291,
        ACTOR_OBJ_BANK_296,
        &cKF_bs_r_pgn_1,
        {
            pgn_5_tmem_txt,
            pgn_5_pal,
            {
                pgn_5_eye1_TA_tex_txt,
                pgn_5_eye2_TA_tex_txt,
                pgn_5_eye3_TA_tex_txt,
                pgn_5_eye4_TA_tex_txt,
                pgn_5_eye5_TA_tex_txt,
                pgn_5_eye6_TA_tex_txt,
                pgn_5_eye7_TA_tex_txt,
                pgn_5_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            48,
            0,
            144,
        },
        0.007499999832361937,
        1,
        4,
        30,
        31,
        0,
        0,
        216,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_291,
        ACTOR_OBJ_BANK_297,
        &cKF_bs_r_pgn_1,
        {
            pgn_6_tmem_txt,
            pgn_6_pal,
            {
                pgn_6_eye1_TA_tex_txt,
                pgn_6_eye2_TA_tex_txt,
                pgn_6_eye3_TA_tex_txt,
                pgn_6_eye4_TA_tex_txt,
                pgn_6_eye5_TA_tex_txt,
                pgn_6_eye6_TA_tex_txt,
                pgn_6_eye7_TA_tex_txt,
                pgn_6_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            48,
            0,
            144,
        },
        0.007499999832361937,
        1,
        5,
        9,
        31,
        0,
        0,
        217,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_291,
        ACTOR_OBJ_BANK_298,
        &cKF_bs_r_pgn_1,
        {
            pgn_7_tmem_txt,
            pgn_7_pal,
            {
                pgn_7_eye1_TA_tex_txt,
                pgn_7_eye2_TA_tex_txt,
                pgn_7_eye3_TA_tex_txt,
                pgn_7_eye4_TA_tex_txt,
                pgn_7_eye5_TA_tex_txt,
                pgn_7_eye6_TA_tex_txt,
                pgn_7_eye7_TA_tex_txt,
                pgn_7_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            48,
            0,
            144,
        },
        0.007499999832361937,
        1,
        6,
        9,
        31,
        0,
        0,
        218,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_299,
        ACTOR_OBJ_BANK_300,
        &cKF_bs_r_pig_1,
        {
            pig_1_tmem_txt,
            pig_1_pal,
            {
                pig_1_eye1_TA_tex_txt,
                pig_1_eye2_TA_tex_txt,
                pig_1_eye3_TA_tex_txt,
                pig_1_eye4_TA_tex_txt,
                pig_1_eye5_TA_tex_txt,
                pig_1_eye6_TA_tex_txt,
                pig_1_eye7_TA_tex_txt,
                pig_1_eye8_TA_tex_txt,
            },
            {
                pig_1_mouth1_TA_tex_txt,
                pig_1_mouth2_TA_tex_txt,
                pig_1_mouth3_TA_tex_txt,
                pig_1_mouth4_TA_tex_txt,
                pig_1_mouth5_TA_tex_txt,
                pig_1_mouth6_TA_tex_txt,
            },
            64,
            112,
            160,
        },
        0.009999999776482582,
        0,
        0,
        0,
        36,
        0,
        0,
        98,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_299,
        ACTOR_OBJ_BANK_301,
        &cKF_bs_r_pig_1,
        {
            pig_2_tmem_txt,
            pig_2_pal,
            {
                pig_2_eye1_TA_tex_txt,
                pig_2_eye2_TA_tex_txt,
                pig_2_eye3_TA_tex_txt,
                pig_2_eye4_TA_tex_txt,
                pig_2_eye5_TA_tex_txt,
                pig_2_eye6_TA_tex_txt,
                pig_2_eye7_TA_tex_txt,
                pig_2_eye8_TA_tex_txt,
            },
            {
                pig_2_mouth1_TA_tex_txt,
                pig_2_mouth2_TA_tex_txt,
                pig_2_mouth3_TA_tex_txt,
                pig_2_mouth4_TA_tex_txt,
                pig_2_mouth5_TA_tex_txt,
                pig_2_mouth6_TA_tex_txt,
            },
            64,
            112,
            160,
        },
        0.009999999776482582,
        0,
        1,
        22,
        36,
        0,
        0,
        99,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_299,
        ACTOR_OBJ_BANK_302,
        &cKF_bs_r_pig_1,
        {
            pig_3_tmem_txt,
            pig_3_pal,
            {
                pig_3_eye1_TA_tex_txt,
                pig_3_eye2_TA_tex_txt,
                pig_3_eye3_TA_tex_txt,
                pig_3_eye4_TA_tex_txt,
                pig_3_eye5_TA_tex_txt,
                pig_3_eye6_TA_tex_txt,
                pig_3_eye7_TA_tex_txt,
                pig_3_eye8_TA_tex_txt,
            },
            {
                pig_3_mouth1_TA_tex_txt,
                pig_3_mouth2_TA_tex_txt,
                pig_3_mouth3_TA_tex_txt,
                pig_3_mouth4_TA_tex_txt,
                pig_3_mouth5_TA_tex_txt,
                pig_3_mouth6_TA_tex_txt,
            },
            64,
            112,
            160,
        },
        0.009999999776482582,
        0,
        2,
        18,
        36,
        0,
        0,
        100,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_299,
        ACTOR_OBJ_BANK_303,
        &cKF_bs_r_pig_1,
        {
            pig_4_tmem_txt,
            pig_4_pal,
            {
                pig_4_eye1_TA_tex_txt,
                pig_4_eye2_TA_tex_txt,
                pig_4_eye3_TA_tex_txt,
                pig_4_eye4_TA_tex_txt,
                pig_4_eye5_TA_tex_txt,
                pig_4_eye6_TA_tex_txt,
                pig_4_eye7_TA_tex_txt,
                pig_4_eye8_TA_tex_txt,
            },
            {
                pig_4_mouth1_TA_tex_txt,
                pig_4_mouth2_TA_tex_txt,
                pig_4_mouth3_TA_tex_txt,
                pig_4_mouth4_TA_tex_txt,
                pig_4_mouth5_TA_tex_txt,
                pig_4_mouth6_TA_tex_txt,
            },
            64,
            112,
            160,
        },
        0.009999999776482582,
        0,
        3,
        3,
        36,
        0,
        0,
        101,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_299,
        ACTOR_OBJ_BANK_304,
        &cKF_bs_r_pig_1,
        {
            pig_5_tmem_txt,
            pig_5_pal,
            {
                pig_5_eye1_TA_tex_txt,
                pig_5_eye2_TA_tex_txt,
                pig_5_eye3_TA_tex_txt,
                pig_5_eye4_TA_tex_txt,
                pig_5_eye5_TA_tex_txt,
                pig_5_eye6_TA_tex_txt,
                pig_5_eye7_TA_tex_txt,
                pig_5_eye8_TA_tex_txt,
            },
            {
                pig_5_mouth1_TA_tex_txt,
                pig_5_mouth2_TA_tex_txt,
                pig_5_mouth3_TA_tex_txt,
                pig_5_mouth4_TA_tex_txt,
                pig_5_mouth5_TA_tex_txt,
                pig_5_mouth6_TA_tex_txt,
            },
            64,
            112,
            160,
        },
        0.009999999776482582,
        0,
        4,
        13,
        36,
        0,
        0,
        102,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_299,
        ACTOR_OBJ_BANK_305,
        &cKF_bs_r_pig_1,
        {
            pig_6_tmem_txt,
            pig_6_pal,
            {
                pig_6_eye1_TA_tex_txt,
                pig_6_eye2_TA_tex_txt,
                pig_6_eye3_TA_tex_txt,
                pig_6_eye4_TA_tex_txt,
                pig_6_eye5_TA_tex_txt,
                pig_6_eye6_TA_tex_txt,
                pig_6_eye7_TA_tex_txt,
                pig_6_eye8_TA_tex_txt,
            },
            {
                pig_6_mouth1_TA_tex_txt,
                pig_6_mouth2_TA_tex_txt,
                pig_6_mouth3_TA_tex_txt,
                pig_6_mouth4_TA_tex_txt,
                pig_6_mouth5_TA_tex_txt,
                pig_6_mouth6_TA_tex_txt,
            },
            64,
            112,
            160,
        },
        0.009999999776482582,
        0,
        5,
        10,
        36,
        0,
        0,
        103,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_299,
        ACTOR_OBJ_BANK_306,
        &cKF_bs_r_pig_1,
        {
            pig_7_tmem_txt,
            pig_7_pal,
            {
                pig_7_eye1_TA_tex_txt,
                pig_7_eye2_TA_tex_txt,
                pig_7_eye3_TA_tex_txt,
                pig_7_eye4_TA_tex_txt,
                pig_7_eye5_TA_tex_txt,
                pig_7_eye6_TA_tex_txt,
                pig_7_eye7_TA_tex_txt,
                pig_7_eye8_TA_tex_txt,
            },
            {
                pig_7_mouth1_TA_tex_txt,
                pig_7_mouth2_TA_tex_txt,
                pig_7_mouth3_TA_tex_txt,
                pig_7_mouth4_TA_tex_txt,
                pig_7_mouth5_TA_tex_txt,
                pig_7_mouth6_TA_tex_txt,
            },
            64,
            112,
            160,
        },
        0.009999999776482582,
        0,
        6,
        14,
        36,
        0,
        0,
        104,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_299,
        ACTOR_OBJ_BANK_307,
        &cKF_bs_r_pig_1,
        {
            pig_8_tmem_txt,
            pig_8_pal,
            {
                pig_8_eye1_TA_tex_txt,
                pig_8_eye2_TA_tex_txt,
                pig_8_eye3_TA_tex_txt,
                pig_8_eye4_TA_tex_txt,
                pig_8_eye5_TA_tex_txt,
                pig_8_eye6_TA_tex_txt,
                pig_8_eye7_TA_tex_txt,
                pig_8_eye8_TA_tex_txt,
            },
            {
                pig_8_mouth1_TA_tex_txt,
                pig_8_mouth2_TA_tex_txt,
                pig_8_mouth3_TA_tex_txt,
                pig_8_mouth4_TA_tex_txt,
                pig_8_mouth5_TA_tex_txt,
                pig_8_mouth6_TA_tex_txt,
            },
            64,
            112,
            160,
        },
        0.009999999776482582,
        0,
        7,
        7,
        36,
        0,
        0,
        105,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_299,
        ACTOR_OBJ_BANK_308,
        &cKF_bs_r_pig_1,
        {
            pig_9_tmem_txt,
            pig_9_pal,
            {
                pig_9_eye1_TA_tex_txt,
                pig_9_eye2_TA_tex_txt,
                pig_9_eye3_TA_tex_txt,
                pig_9_eye4_TA_tex_txt,
                pig_9_eye5_TA_tex_txt,
                pig_9_eye6_TA_tex_txt,
                pig_9_eye7_TA_tex_txt,
                pig_9_eye8_TA_tex_txt,
            },
            {
                pig_9_mouth1_TA_tex_txt,
                pig_9_mouth2_TA_tex_txt,
                pig_9_mouth3_TA_tex_txt,
                pig_9_mouth4_TA_tex_txt,
                pig_9_mouth5_TA_tex_txt,
                pig_9_mouth6_TA_tex_txt,
            },
            64,
            112,
            160,
        },
        0.009999999776482582,
        0,
        8,
        14,
        36,
        0,
        0,
        106,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_299,
        ACTOR_OBJ_BANK_309,
        &cKF_bs_r_pig_1,
        {
            pig_10_tmem_txt,
            pig_10_pal,
            {
                pig_10_eye1_TA_tex_txt,
                pig_10_eye2_TA_tex_txt,
                pig_10_eye3_TA_tex_txt,
                pig_10_eye4_TA_tex_txt,
                pig_10_eye5_TA_tex_txt,
                pig_10_eye6_TA_tex_txt,
                pig_10_eye7_TA_tex_txt,
                pig_10_eye8_TA_tex_txt,
            },
            {
                pig_10_mouth1_TA_tex_txt,
                pig_10_mouth2_TA_tex_txt,
                pig_10_mouth3_TA_tex_txt,
                pig_10_mouth4_TA_tex_txt,
                pig_10_mouth5_TA_tex_txt,
                pig_10_mouth6_TA_tex_txt,
            },
            64,
            112,
            160,
        },
        0.009999999776482582,
        0,
        9,
        25,
        36,
        0,
        0,
        107,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_320,
        ACTOR_OBJ_BANK_321,
        &cKF_bs_r_rbt_1,
        {
            rbt_1_tmem_txt,
            rbt_1_pal,
            {
                rbt_1_eye1_TA_tex_txt,
                rbt_1_eye2_TA_tex_txt,
                rbt_1_eye3_TA_tex_txt,
                rbt_1_eye4_TA_tex_txt,
                rbt_1_eye5_TA_tex_txt,
                rbt_1_eye6_TA_tex_txt,
                rbt_1_eye7_TA_tex_txt,
                rbt_1_eye8_TA_tex_txt,
            },
            {
                rbt_1_mouth1_TA_tex_txt,
                rbt_1_mouth2_TA_tex_txt,
                rbt_1_mouth3_TA_tex_txt,
                rbt_1_mouth4_TA_tex_txt,
                rbt_1_mouth5_TA_tex_txt,
                rbt_1_mouth6_TA_tex_txt,
            },
            80,
            112,
            176,
        },
        0.009999999776482582,
        0,
        0,
        1,
        34,
        0,
        0,
        57,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_320,
        ACTOR_OBJ_BANK_322,
        &cKF_bs_r_rbt_1,
        {
            rbt_2_tmem_txt,
            rbt_2_pal,
            {
                rbt_2_eye1_TA_tex_txt,
                rbt_2_eye2_TA_tex_txt,
                rbt_2_eye3_TA_tex_txt,
                rbt_2_eye4_TA_tex_txt,
                rbt_2_eye5_TA_tex_txt,
                rbt_2_eye6_TA_tex_txt,
                rbt_2_eye7_TA_tex_txt,
                rbt_2_eye8_TA_tex_txt,
            },
            {
                rbt_2_mouth1_TA_tex_txt,
                rbt_2_mouth2_TA_tex_txt,
                rbt_2_mouth3_TA_tex_txt,
                rbt_2_mouth4_TA_tex_txt,
                rbt_2_mouth5_TA_tex_txt,
                rbt_2_mouth6_TA_tex_txt,
            },
            80,
            112,
            176,
        },
        0.009999999776482582,
        0,
        1,
        14,
        34,
        0,
        0,
        58,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_320,
        ACTOR_OBJ_BANK_323,
        &cKF_bs_r_rbt_1,
        {
            rbt_3_tmem_txt,
            rbt_3_pal,
            {
                rbt_3_eye1_TA_tex_txt,
                rbt_3_eye2_TA_tex_txt,
                rbt_3_eye3_TA_tex_txt,
                rbt_3_eye4_TA_tex_txt,
                rbt_3_eye5_TA_tex_txt,
                rbt_3_eye6_TA_tex_txt,
                rbt_3_eye7_TA_tex_txt,
                rbt_3_eye8_TA_tex_txt,
            },
            {
                rbt_3_mouth1_TA_tex_txt,
                rbt_3_mouth2_TA_tex_txt,
                rbt_3_mouth3_TA_tex_txt,
                rbt_3_mouth4_TA_tex_txt,
                rbt_3_mouth5_TA_tex_txt,
                rbt_3_mouth6_TA_tex_txt,
            },
            80,
            112,
            176,
        },
        0.009999999776482582,
        0,
        2,
        13,
        34,
        0,
        0,
        59,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_320,
        ACTOR_OBJ_BANK_324,
        &cKF_bs_r_rbt_1,
        {
            rbt_4_tmem_txt,
            rbt_4_pal,
            {
                rbt_4_eye1_TA_tex_txt,
                rbt_4_eye2_TA_tex_txt,
                rbt_4_eye3_TA_tex_txt,
                rbt_4_eye4_TA_tex_txt,
                rbt_4_eye5_TA_tex_txt,
                rbt_4_eye6_TA_tex_txt,
                rbt_4_eye7_TA_tex_txt,
                rbt_4_eye8_TA_tex_txt,
            },
            {
                rbt_4_mouth1_TA_tex_txt,
                rbt_4_mouth2_TA_tex_txt,
                rbt_4_mouth3_TA_tex_txt,
                rbt_4_mouth4_TA_tex_txt,
                rbt_4_mouth5_TA_tex_txt,
                rbt_4_mouth6_TA_tex_txt,
            },
            80,
            112,
            176,
        },
        0.009999999776482582,
        0,
        3,
        19,
        34,
        0,
        0,
        60,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_320,
        ACTOR_OBJ_BANK_325,
        &cKF_bs_r_rbt_1,
        {
            rbt_5_tmem_txt,
            rbt_5_pal,
            {
                rbt_5_eye1_TA_tex_txt,
                rbt_5_eye2_TA_tex_txt,
                rbt_5_eye3_TA_tex_txt,
                rbt_5_eye4_TA_tex_txt,
                rbt_5_eye5_TA_tex_txt,
                rbt_5_eye6_TA_tex_txt,
                rbt_5_eye7_TA_tex_txt,
                rbt_5_eye8_TA_tex_txt,
            },
            {
                rbt_5_mouth1_TA_tex_txt,
                rbt_5_mouth2_TA_tex_txt,
                rbt_5_mouth3_TA_tex_txt,
                rbt_5_mouth4_TA_tex_txt,
                rbt_5_mouth5_TA_tex_txt,
                rbt_5_mouth6_TA_tex_txt,
            },
            80,
            112,
            176,
        },
        0.009999999776482582,
        0,
        4,
        2,
        34,
        0,
        0,
        61,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_320,
        ACTOR_OBJ_BANK_326,
        &cKF_bs_r_rbt_1,
        {
            rbt_6_tmem_txt,
            rbt_6_pal,
            {
                rbt_6_eye1_TA_tex_txt,
                rbt_6_eye2_TA_tex_txt,
                rbt_6_eye3_TA_tex_txt,
                rbt_6_eye4_TA_tex_txt,
                rbt_6_eye5_TA_tex_txt,
                rbt_6_eye6_TA_tex_txt,
                rbt_6_eye7_TA_tex_txt,
                rbt_6_eye8_TA_tex_txt,
            },
            {
                rbt_6_mouth1_TA_tex_txt,
                rbt_6_mouth2_TA_tex_txt,
                rbt_6_mouth3_TA_tex_txt,
                rbt_6_mouth4_TA_tex_txt,
                rbt_6_mouth5_TA_tex_txt,
                rbt_6_mouth6_TA_tex_txt,
            },
            80,
            112,
            176,
        },
        0.009999999776482582,
        0,
        5,
        18,
        34,
        0,
        0,
        62,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_320,
        ACTOR_OBJ_BANK_327,
        &cKF_bs_r_rbt_1,
        {
            rbt_7_tmem_txt,
            rbt_7_pal,
            {
                rbt_7_eye1_TA_tex_txt,
                rbt_7_eye2_TA_tex_txt,
                rbt_7_eye3_TA_tex_txt,
                rbt_7_eye4_TA_tex_txt,
                rbt_7_eye5_TA_tex_txt,
                rbt_7_eye6_TA_tex_txt,
                rbt_7_eye7_TA_tex_txt,
                rbt_7_eye8_TA_tex_txt,
            },
            {
                rbt_7_mouth1_TA_tex_txt,
                rbt_7_mouth2_TA_tex_txt,
                rbt_7_mouth3_TA_tex_txt,
                rbt_7_mouth4_TA_tex_txt,
                rbt_7_mouth5_TA_tex_txt,
                rbt_7_mouth6_TA_tex_txt,
            },
            80,
            112,
            176,
        },
        0.009999999776482582,
        0,
        6,
        21,
        34,
        0,
        0,
        63,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_320,
        ACTOR_OBJ_BANK_328,
        &cKF_bs_r_rbt_1,
        {
            rbt_8_tmem_txt,
            rbt_8_pal,
            {
                rbt_8_eye1_TA_tex_txt,
                rbt_8_eye2_TA_tex_txt,
                rbt_8_eye3_TA_tex_txt,
                rbt_8_eye4_TA_tex_txt,
                rbt_8_eye5_TA_tex_txt,
                rbt_8_eye6_TA_tex_txt,
                rbt_8_eye7_TA_tex_txt,
                rbt_8_eye8_TA_tex_txt,
            },
            {
                rbt_8_mouth1_TA_tex_txt,
                rbt_8_mouth2_TA_tex_txt,
                rbt_8_mouth3_TA_tex_txt,
                rbt_8_mouth4_TA_tex_txt,
                rbt_8_mouth5_TA_tex_txt,
                rbt_8_mouth6_TA_tex_txt,
            },
            80,
            112,
            176,
        },
        0.009999999776482582,
        0,
        7,
        24,
        34,
        0,
        0,
        64,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_320,
        ACTOR_OBJ_BANK_329,
        &cKF_bs_r_rbt_1,
        {
            rbt_9_tmem_txt,
            rbt_9_pal,
            {
                rbt_9_eye1_TA_tex_txt,
                rbt_9_eye2_TA_tex_txt,
                rbt_9_eye3_TA_tex_txt,
                rbt_9_eye4_TA_tex_txt,
                rbt_9_eye5_TA_tex_txt,
                rbt_9_eye6_TA_tex_txt,
                rbt_9_eye7_TA_tex_txt,
                rbt_9_eye8_TA_tex_txt,
            },
            {
                rbt_9_mouth1_TA_tex_txt,
                rbt_9_mouth2_TA_tex_txt,
                rbt_9_mouth3_TA_tex_txt,
                rbt_9_mouth4_TA_tex_txt,
                rbt_9_mouth5_TA_tex_txt,
                rbt_9_mouth6_TA_tex_txt,
            },
            80,
            112,
            176,
        },
        0.009999999776482582,
        0,
        8,
        30,
        34,
        0,
        0,
        65,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_330,
        ACTOR_OBJ_BANK_331,
        &cKF_bs_r_rhn_1,
        {
            rhn_1_tmem_txt,
            rhn_1_pal,
            {
                rhn_1_eye1_TA_tex_txt,
                rhn_1_eye2_TA_tex_txt,
                rhn_1_eye3_TA_tex_txt,
                rhn_1_eye4_TA_tex_txt,
                rhn_1_eye5_TA_tex_txt,
                rhn_1_eye6_TA_tex_txt,
                rhn_1_eye7_TA_tex_txt,
                rhn_1_eye8_TA_tex_txt,
            },
            {
                rhn_1_mouth1_TA_tex_txt,
                rhn_1_mouth2_TA_tex_txt,
                rhn_1_mouth3_TA_tex_txt,
                rhn_1_mouth4_TA_tex_txt,
                rhn_1_mouth5_TA_tex_txt,
                rhn_1_mouth6_TA_tex_txt,
            },
            72,
            120,
            168,
        },
        0.010999999940395355,
        1,
        0,
        0,
        37,
        0,
        0,
        189,
        23,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_330,
        ACTOR_OBJ_BANK_332,
        &cKF_bs_r_rhn_1,
        {
            rhn_2_tmem_txt,
            rhn_2_pal,
            {
                rhn_2_eye1_TA_tex_txt,
                rhn_2_eye2_TA_tex_txt,
                rhn_2_eye3_TA_tex_txt,
                rhn_2_eye4_TA_tex_txt,
                rhn_2_eye5_TA_tex_txt,
                rhn_2_eye6_TA_tex_txt,
                rhn_2_eye7_TA_tex_txt,
                rhn_2_eye8_TA_tex_txt,
            },
            {
                rhn_2_mouth1_TA_tex_txt,
                rhn_2_mouth2_TA_tex_txt,
                rhn_2_mouth3_TA_tex_txt,
                rhn_2_mouth4_TA_tex_txt,
                rhn_2_mouth5_TA_tex_txt,
                rhn_2_mouth6_TA_tex_txt,
            },
            72,
            120,
            168,
        },
        0.010999999940395355,
        1,
        1,
        21,
        37,
        0,
        0,
        190,
        23,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_330,
        ACTOR_OBJ_BANK_333,
        &cKF_bs_r_rhn_1,
        {
            rhn_3_tmem_txt,
            rhn_3_pal,
            {
                rhn_3_eye1_TA_tex_txt,
                rhn_3_eye2_TA_tex_txt,
                rhn_3_eye3_TA_tex_txt,
                rhn_3_eye4_TA_tex_txt,
                rhn_3_eye5_TA_tex_txt,
                rhn_3_eye6_TA_tex_txt,
                rhn_3_eye7_TA_tex_txt,
                rhn_3_eye8_TA_tex_txt,
            },
            {
                rhn_3_mouth1_TA_tex_txt,
                rhn_3_mouth2_TA_tex_txt,
                rhn_3_mouth3_TA_tex_txt,
                rhn_3_mouth4_TA_tex_txt,
                rhn_3_mouth5_TA_tex_txt,
                rhn_3_mouth6_TA_tex_txt,
            },
            72,
            120,
            168,
        },
        0.010999999940395355,
        1,
        2,
        15,
        37,
        0,
        0,
        191,
        23,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_337,
        ACTOR_OBJ_BANK_338,
        &cKF_bs_r_shp_1,
        {
            shp_1_tmem_txt,
            shp_1_pal,
            {
                shp_1_eye1_TA_tex_txt,
                shp_1_eye2_TA_tex_txt,
                shp_1_eye3_TA_tex_txt,
                shp_1_eye4_TA_tex_txt,
                shp_1_eye5_TA_tex_txt,
                shp_1_eye6_TA_tex_txt,
                shp_1_eye7_TA_tex_txt,
                shp_1_eye8_TA_tex_txt,
            },
            {
                shp_1_mouth1_TA_tex_txt,
                shp_1_mouth2_TA_tex_txt,
                shp_1_mouth3_TA_tex_txt,
                shp_1_mouth4_TA_tex_txt,
                shp_1_mouth5_TA_tex_txt,
                shp_1_mouth6_TA_tex_txt,
            },
            96,
            128,
            192,
        },
        0.009999999776482582,
        0,
        0,
        10,
        40,
        0,
        0,
        21,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_343,
        ACTOR_OBJ_BANK_344,
        &cKF_bs_r_squ_1,
        {
            squ_1_tmem_txt,
            squ_1_pal,
            {
                squ_1_eye1_TA_tex_txt,
                squ_1_eye2_TA_tex_txt,
                squ_1_eye3_TA_tex_txt,
                squ_1_eye4_TA_tex_txt,
                squ_1_eye5_TA_tex_txt,
                squ_1_eye6_TA_tex_txt,
                squ_1_eye7_TA_tex_txt,
                squ_1_eye8_TA_tex_txt,
            },
            {
                squ_1_mouth1_TA_tex_txt,
                squ_1_mouth2_TA_tex_txt,
                squ_1_mouth3_TA_tex_txt,
                squ_1_mouth4_TA_tex_txt,
                squ_1_mouth5_TA_tex_txt,
                squ_1_mouth6_TA_tex_txt,
            },
            72,
            104,
            160,
        },
        0.006800000090152025,
        0,
        0,
        4,
        26,
        0,
        0,
        47,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_343,
        ACTOR_OBJ_BANK_345,
        &cKF_bs_r_squ_1,
        {
            squ_2_tmem_txt,
            squ_2_pal,
            {
                squ_2_eye1_TA_tex_txt,
                squ_2_eye2_TA_tex_txt,
                squ_2_eye3_TA_tex_txt,
                squ_2_eye4_TA_tex_txt,
                squ_2_eye5_TA_tex_txt,
                squ_2_eye6_TA_tex_txt,
                squ_2_eye7_TA_tex_txt,
                squ_2_eye8_TA_tex_txt,
            },
            {
                squ_2_mouth1_TA_tex_txt,
                squ_2_mouth2_TA_tex_txt,
                squ_2_mouth3_TA_tex_txt,
                squ_2_mouth4_TA_tex_txt,
                squ_2_mouth5_TA_tex_txt,
                squ_2_mouth6_TA_tex_txt,
            },
            72,
            104,
            160,
        },
        0.006800000090152025,
        0,
        1,
        5,
        26,
        0,
        0,
        48,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_343,
        ACTOR_OBJ_BANK_346,
        &cKF_bs_r_squ_1,
        {
            squ_3_tmem_txt,
            squ_3_pal,
            {
                squ_3_eye1_TA_tex_txt,
                squ_3_eye2_TA_tex_txt,
                squ_3_eye3_TA_tex_txt,
                squ_3_eye4_TA_tex_txt,
                squ_3_eye5_TA_tex_txt,
                squ_3_eye6_TA_tex_txt,
                squ_3_eye7_TA_tex_txt,
                squ_3_eye8_TA_tex_txt,
            },
            {
                squ_3_mouth1_TA_tex_txt,
                squ_3_mouth2_TA_tex_txt,
                squ_3_mouth3_TA_tex_txt,
                squ_3_mouth4_TA_tex_txt,
                squ_3_mouth5_TA_tex_txt,
                squ_3_mouth6_TA_tex_txt,
            },
            72,
            104,
            160,
        },
        0.006800000090152025,
        0,
        2,
        6,
        26,
        0,
        0,
        49,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_343,
        ACTOR_OBJ_BANK_347,
        &cKF_bs_r_squ_1,
        {
            squ_4_tmem_txt,
            squ_4_pal,
            {
                squ_4_eye1_TA_tex_txt,
                squ_4_eye2_TA_tex_txt,
                squ_4_eye3_TA_tex_txt,
                squ_4_eye4_TA_tex_txt,
                squ_4_eye5_TA_tex_txt,
                squ_4_eye6_TA_tex_txt,
                squ_4_eye7_TA_tex_txt,
                squ_4_eye8_TA_tex_txt,
            },
            {
                squ_4_mouth1_TA_tex_txt,
                squ_4_mouth2_TA_tex_txt,
                squ_4_mouth3_TA_tex_txt,
                squ_4_mouth4_TA_tex_txt,
                squ_4_mouth5_TA_tex_txt,
                squ_4_mouth6_TA_tex_txt,
            },
            72,
            104,
            160,
        },
        0.006800000090152025,
        0,
        3,
        17,
        26,
        0,
        0,
        50,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_343,
        ACTOR_OBJ_BANK_348,
        &cKF_bs_r_squ_1,
        {
            squ_5_tmem_txt,
            squ_5_pal,
            {
                squ_5_eye1_TA_tex_txt,
                squ_5_eye2_TA_tex_txt,
                squ_5_eye3_TA_tex_txt,
                squ_5_eye4_TA_tex_txt,
                squ_5_eye5_TA_tex_txt,
                squ_5_eye6_TA_tex_txt,
                squ_5_eye7_TA_tex_txt,
                squ_5_eye8_TA_tex_txt,
            },
            {
                squ_5_mouth1_TA_tex_txt,
                squ_5_mouth2_TA_tex_txt,
                squ_5_mouth3_TA_tex_txt,
                squ_5_mouth4_TA_tex_txt,
                squ_5_mouth5_TA_tex_txt,
                squ_5_mouth6_TA_tex_txt,
            },
            72,
            104,
            160,
        },
        0.006800000090152025,
        0,
        4,
        16,
        26,
        0,
        0,
        51,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_343,
        ACTOR_OBJ_BANK_349,
        &cKF_bs_r_squ_1,
        {
            squ_6_tmem_txt,
            squ_6_pal,
            {
                squ_6_eye1_TA_tex_txt,
                squ_6_eye2_TA_tex_txt,
                squ_6_eye3_TA_tex_txt,
                squ_6_eye4_TA_tex_txt,
                squ_6_eye5_TA_tex_txt,
                squ_6_eye6_TA_tex_txt,
                squ_6_eye7_TA_tex_txt,
                squ_6_eye8_TA_tex_txt,
            },
            {
                squ_6_mouth1_TA_tex_txt,
                squ_6_mouth2_TA_tex_txt,
                squ_6_mouth3_TA_tex_txt,
                squ_6_mouth4_TA_tex_txt,
                squ_6_mouth5_TA_tex_txt,
                squ_6_mouth6_TA_tex_txt,
            },
            72,
            104,
            160,
        },
        0.006800000090152025,
        0,
        5,
        18,
        26,
        0,
        0,
        52,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_343,
        ACTOR_OBJ_BANK_350,
        &cKF_bs_r_squ_1,
        {
            squ_7_tmem_txt,
            squ_7_pal,
            {
                squ_7_eye1_TA_tex_txt,
                squ_7_eye2_TA_tex_txt,
                squ_7_eye3_TA_tex_txt,
                squ_7_eye4_TA_tex_txt,
                squ_7_eye5_TA_tex_txt,
                squ_7_eye6_TA_tex_txt,
                squ_7_eye7_TA_tex_txt,
                squ_7_eye8_TA_tex_txt,
            },
            {
                squ_7_mouth1_TA_tex_txt,
                squ_7_mouth2_TA_tex_txt,
                squ_7_mouth3_TA_tex_txt,
                squ_7_mouth4_TA_tex_txt,
                squ_7_mouth5_TA_tex_txt,
                squ_7_mouth6_TA_tex_txt,
            },
            72,
            104,
            160,
        },
        0.006800000090152025,
        0,
        6,
        9,
        26,
        0,
        0,
        53,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_343,
        ACTOR_OBJ_BANK_351,
        &cKF_bs_r_squ_1,
        {
            squ_8_tmem_txt,
            squ_8_pal,
            {
                squ_8_eye1_TA_tex_txt,
                squ_8_eye2_TA_tex_txt,
                squ_8_eye3_TA_tex_txt,
                squ_8_eye4_TA_tex_txt,
                squ_8_eye5_TA_tex_txt,
                squ_8_eye6_TA_tex_txt,
                squ_8_eye7_TA_tex_txt,
                squ_8_eye8_TA_tex_txt,
            },
            {
                squ_8_mouth1_TA_tex_txt,
                squ_8_mouth2_TA_tex_txt,
                squ_8_mouth3_TA_tex_txt,
                squ_8_mouth4_TA_tex_txt,
                squ_8_mouth5_TA_tex_txt,
                squ_8_mouth6_TA_tex_txt,
            },
            72,
            104,
            160,
        },
        0.006800000090152025,
        0,
        7,
        11,
        26,
        0,
        0,
        54,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_356,
        ACTOR_OBJ_BANK_357,
        &cKF_bs_r_tig_1,
        {
            tig_1_tmem_txt,
            tig_1_pal,
            {
                tig_1_eye1_TA_tex_txt,
                tig_1_eye2_TA_tex_txt,
                tig_1_eye3_TA_tex_txt,
                tig_1_eye4_TA_tex_txt,
                tig_1_eye5_TA_tex_txt,
                tig_1_eye6_TA_tex_txt,
                tig_1_eye7_TA_tex_txt,
                tig_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            8,
            0,
            176,
        },
        0.011300000362098217,
        1,
        0,
        30,
        41,
        0,
        0,
        156,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_356,
        ACTOR_OBJ_BANK_358,
        &cKF_bs_r_tig_1,
        {
            tig_2_tmem_txt,
            tig_2_pal,
            {
                tig_2_eye1_TA_tex_txt,
                tig_2_eye2_TA_tex_txt,
                tig_2_eye3_TA_tex_txt,
                tig_2_eye4_TA_tex_txt,
                tig_2_eye5_TA_tex_txt,
                tig_2_eye6_TA_tex_txt,
                tig_2_eye7_TA_tex_txt,
                tig_2_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            8,
            0,
            176,
        },
        0.011300000362098217,
        1,
        1,
        11,
        41,
        0,
        0,
        157,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_356,
        ACTOR_OBJ_BANK_359,
        &cKF_bs_r_tig_1,
        {
            tig_3_tmem_txt,
            tig_3_pal,
            {
                tig_3_eye1_TA_tex_txt,
                tig_3_eye2_TA_tex_txt,
                tig_3_eye3_TA_tex_txt,
                tig_3_eye4_TA_tex_txt,
                tig_3_eye5_TA_tex_txt,
                tig_3_eye6_TA_tex_txt,
                tig_3_eye7_TA_tex_txt,
                tig_3_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            8,
            0,
            176,
        },
        0.011300000362098217,
        1,
        2,
        1,
        41,
        0,
        0,
        158,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_362,
        ACTOR_OBJ_BANK_363,
        &cKF_bs_r_wol_1,
        {
            wol_1_tmem_txt,
            wol_1_pal,
            {
                wol_1_eye1_TA_tex_txt,
                wol_1_eye2_TA_tex_txt,
                wol_1_eye3_TA_tex_txt,
                wol_1_eye4_TA_tex_txt,
                wol_1_eye5_TA_tex_txt,
                wol_1_eye6_TA_tex_txt,
                wol_1_eye7_TA_tex_txt,
                wol_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            80,
            0,
            160,
        },
        0.009999999776482582,
        1,
        0,
        21,
        37,
        0,
        0,
        84,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_362,
        ACTOR_OBJ_BANK_364,
        &cKF_bs_r_wol_1,
        {
            wol_2_tmem_txt,
            wol_2_pal,
            {
                wol_2_eye1_TA_tex_txt,
                wol_2_eye2_TA_tex_txt,
                wol_2_eye3_TA_tex_txt,
                wol_2_eye4_TA_tex_txt,
                wol_2_eye5_TA_tex_txt,
                wol_2_eye6_TA_tex_txt,
                wol_2_eye7_TA_tex_txt,
                wol_2_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            80,
            0,
            160,
        },
        0.009999999776482582,
        1,
        1,
        10,
        37,
        0,
        0,
        85,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_362,
        ACTOR_OBJ_BANK_365,
        &cKF_bs_r_wol_1,
        {
            wol_3_tmem_txt,
            wol_3_pal,
            {
                wol_3_eye1_TA_tex_txt,
                wol_3_eye2_TA_tex_txt,
                wol_3_eye3_TA_tex_txt,
                wol_3_eye4_TA_tex_txt,
                wol_3_eye5_TA_tex_txt,
                wol_3_eye6_TA_tex_txt,
                wol_3_eye7_TA_tex_txt,
                wol_3_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            80,
            0,
            160,
        },
        0.009999999776482582,
        1,
        2,
        17,
        37,
        0,
        0,
        86,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_191,
        ACTOR_OBJ_BANK_198,
        &cKF_bs_r_duk_1,
        {
            duk_7_tmem_txt,
            duk_7_pal,
            {
                duk_7_eye1_TA_tex_txt,
                duk_7_eye2_TA_tex_txt,
                duk_7_eye3_TA_tex_txt,
                duk_7_eye4_TA_tex_txt,
                duk_7_eye5_TA_tex_txt,
                duk_7_eye6_TA_tex_txt,
                duk_7_eye7_TA_tex_txt,
                duk_7_eye8_TA_tex_txt,
            },
            {
                duk_7_mouth1_TA_tex_txt,
                duk_7_mouth2_TA_tex_txt,
                duk_7_mouth3_TA_tex_txt,
                duk_7_mouth4_TA_tex_txt,
                duk_7_mouth5_TA_tex_txt,
                duk_7_mouth6_TA_tex_txt,
            },
            112,
            72,
            160,
        },
        0.009999999776482582,
        1,
        6,
        11,
        31,
        0,
        0,
        73,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_191,
        ACTOR_OBJ_BANK_199,
        &cKF_bs_r_duk_1,
        {
            duk_8_tmem_txt,
            duk_8_pal,
            {
                duk_8_eye1_TA_tex_txt,
                duk_8_eye2_TA_tex_txt,
                duk_8_eye3_TA_tex_txt,
                duk_8_eye4_TA_tex_txt,
                duk_8_eye5_TA_tex_txt,
                duk_8_eye6_TA_tex_txt,
                duk_8_eye7_TA_tex_txt,
                duk_8_eye8_TA_tex_txt,
            },
            {
                duk_8_mouth1_TA_tex_txt,
                duk_8_mouth2_TA_tex_txt,
                duk_8_mouth3_TA_tex_txt,
                duk_8_mouth4_TA_tex_txt,
                duk_8_mouth5_TA_tex_txt,
                duk_8_mouth6_TA_tex_txt,
            },
            112,
            72,
            160,
        },
        0.009999999776482582,
        1,
        7,
        15,
        31,
        0,
        0,
        74,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_362,
        ACTOR_OBJ_BANK_366,
        &cKF_bs_r_wol_1,
        {
            wol_4_tmem_txt,
            wol_4_pal,
            {
                wol_4_eye1_TA_tex_txt,
                wol_4_eye2_TA_tex_txt,
                wol_4_eye3_TA_tex_txt,
                wol_4_eye4_TA_tex_txt,
                wol_4_eye5_TA_tex_txt,
                wol_4_eye6_TA_tex_txt,
                wol_4_eye7_TA_tex_txt,
                wol_4_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            80,
            0,
            160,
        },
        0.009999999776482582,
        1,
        3,
        16,
        37,
        0,
        0,
        87,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_330,
        ACTOR_OBJ_BANK_334,
        &cKF_bs_r_rhn_1,
        {
            rhn_4_tmem_txt,
            rhn_4_pal,
            {
                rhn_4_eye1_TA_tex_txt,
                rhn_4_eye2_TA_tex_txt,
                rhn_4_eye3_TA_tex_txt,
                rhn_4_eye4_TA_tex_txt,
                rhn_4_eye5_TA_tex_txt,
                rhn_4_eye6_TA_tex_txt,
                rhn_4_eye7_TA_tex_txt,
                rhn_4_eye8_TA_tex_txt,
            },
            {
                rhn_4_mouth1_TA_tex_txt,
                rhn_4_mouth2_TA_tex_txt,
                rhn_4_mouth3_TA_tex_txt,
                rhn_4_mouth4_TA_tex_txt,
                rhn_4_mouth5_TA_tex_txt,
                rhn_4_mouth6_TA_tex_txt,
            },
            72,
            120,
            168,
        },
        0.010999999940395355,
        1,
        3,
        22,
        37,
        0,
        0,
        192,
        23,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_126,
        ACTOR_OBJ_BANK_129,
        &cKF_bs_r_bul_1,
        {
            bul_3_tmem_txt,
            bul_3_pal,
            {
                bul_3_eye1_TA_tex_txt,
                bul_3_eye2_TA_tex_txt,
                bul_3_eye3_TA_tex_txt,
                bul_3_eye4_TA_tex_txt,
                bul_3_eye5_TA_tex_txt,
                bul_3_eye6_TA_tex_txt,
                bul_3_eye7_TA_tex_txt,
                bul_3_eye8_TA_tex_txt,
            },
            {
                bul_3_mouth1_TA_tex_txt,
                bul_3_mouth2_TA_tex_txt,
                bul_3_mouth3_TA_tex_txt,
                bul_3_mouth4_TA_tex_txt,
                bul_3_mouth5_TA_tex_txt,
                bul_3_mouth6_TA_tex_txt,
            },
            128,
            32,
            176,
        },
        0.012500000186264515,
        0,
        2,
        24,
        45,
        0,
        0,
        118,
        25,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_126,
        ACTOR_OBJ_BANK_130,
        &cKF_bs_r_bul_1,
        {
            bul_4_tmem_txt,
            bul_4_pal,
            {
                bul_4_eye1_TA_tex_txt,
                bul_4_eye2_TA_tex_txt,
                bul_4_eye3_TA_tex_txt,
                bul_4_eye4_TA_tex_txt,
                bul_4_eye5_TA_tex_txt,
                bul_4_eye6_TA_tex_txt,
                bul_4_eye7_TA_tex_txt,
                bul_4_eye8_TA_tex_txt,
            },
            {
                bul_4_mouth1_TA_tex_txt,
                bul_4_mouth2_TA_tex_txt,
                bul_4_mouth3_TA_tex_txt,
                bul_4_mouth4_TA_tex_txt,
                bul_4_mouth5_TA_tex_txt,
                bul_4_mouth6_TA_tex_txt,
            },
            128,
            32,
            176,
        },
        0.012500000186264515,
        0,
        3,
        23,
        45,
        0,
        0,
        119,
        25,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_238,
        ACTOR_OBJ_BANK_242,
        &cKF_bs_r_hip_1,
        {
            hip_4_tmem_txt,
            hip_4_pal,
            {
                hip_4_eye1_TA_tex_txt,
                hip_4_eye2_TA_tex_txt,
                hip_4_eye3_TA_tex_txt,
                hip_4_eye4_TA_tex_txt,
                hip_4_eye5_TA_tex_txt,
                hip_4_eye6_TA_tex_txt,
                hip_4_eye7_TA_tex_txt,
                hip_4_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            136,
            0,
            32,
        },
        0.007300000172108412,
        1,
        3,
        4,
        43,
        0,
        0,
        80,
        25,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_200,
        ACTOR_OBJ_BANK_204,
        &cKF_bs_r_elp_1,
        {
            elp_4_tmem_txt,
            elp_4_pal,
            {
                elp_4_eye1_TA_tex_txt,
                elp_4_eye2_TA_tex_txt,
                elp_4_eye3_TA_tex_txt,
                elp_4_eye4_TA_tex_txt,
                elp_4_eye5_TA_tex_txt,
                elp_4_eye6_TA_tex_txt,
                elp_4_eye7_TA_tex_txt,
                elp_4_eye8_TA_tex_txt,
            },
            {
                elp_4_mouth1_TA_tex_txt,
                elp_4_mouth2_TA_tex_txt,
                elp_4_mouth3_TA_tex_txt,
                elp_4_mouth4_TA_tex_txt,
                elp_4_mouth5_TA_tex_txt,
                elp_4_mouth6_TA_tex_txt,
            },
            48,
            176,
            80,
        },
        0.009999999776482582,
        1,
        3,
        17,
        40,
        0,
        0,
        18,
        25,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_182,
        ACTOR_OBJ_BANK_372,
        &cKF_bs_r_dog_1,
        {
            dog_9_tmem_txt,
            dog_9_pal,
            {
                dog_9_eye1_TA_tex_txt,
                dog_9_eye2_TA_tex_txt,
                dog_9_eye3_TA_tex_txt,
                dog_9_eye4_TA_tex_txt,
                dog_9_eye5_TA_tex_txt,
                dog_9_eye6_TA_tex_txt,
                dog_9_eye7_TA_tex_txt,
                dog_9_eye8_TA_tex_txt,
            },
            {
                dog_9_mouth1_TA_tex_txt,
                dog_9_mouth2_TA_tex_txt,
                dog_9_mouth3_TA_tex_txt,
                dog_9_mouth4_TA_tex_txt,
                dog_9_mouth5_TA_tex_txt,
                dog_9_mouth6_TA_tex_txt,
            },
            48,
            0,
            80,
        },
        0.009499999694526196,
        0,
        8,
        19,
        37,
        0,
        0,
        45,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_182,
        ACTOR_OBJ_BANK_373,
        &cKF_bs_r_dog_1,
        {
            dog_10_tmem_txt,
            dog_10_pal,
            {
                dog_10_eye1_TA_tex_txt,
                dog_10_eye2_TA_tex_txt,
                dog_10_eye3_TA_tex_txt,
                dog_10_eye4_TA_tex_txt,
                dog_10_eye5_TA_tex_txt,
                dog_10_eye6_TA_tex_txt,
                dog_10_eye7_TA_tex_txt,
                dog_10_eye8_TA_tex_txt,
            },
            {
                dog_10_mouth1_TA_tex_txt,
                dog_10_mouth2_TA_tex_txt,
                dog_10_mouth3_TA_tex_txt,
                dog_10_mouth4_TA_tex_txt,
                dog_10_mouth5_TA_tex_txt,
                dog_10_mouth6_TA_tex_txt,
            },
            48,
            0,
            80,
        },
        0.009499999694526196,
        0,
        9,
        3,
        37,
        0,
        0,
        46,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_238,
        ACTOR_OBJ_BANK_374,
        &cKF_bs_r_hip_1,
        {
            hip_5_tmem_txt,
            hip_5_pal,
            {
                hip_5_eye1_TA_tex_txt,
                hip_5_eye2_TA_tex_txt,
                hip_5_eye3_TA_tex_txt,
                hip_5_eye4_TA_tex_txt,
                hip_5_eye5_TA_tex_txt,
                hip_5_eye6_TA_tex_txt,
                hip_5_eye7_TA_tex_txt,
                hip_5_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            136,
            0,
            32,
        },
        0.007300000172108412,
        1,
        4,
        6,
        43,
        0,
        0,
        81,
        25,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_238,
        ACTOR_OBJ_BANK_375,
        &cKF_bs_r_hip_1,
        {
            hip_6_tmem_txt,
            hip_6_pal,
            {
                hip_6_eye1_TA_tex_txt,
                hip_6_eye2_TA_tex_txt,
                hip_6_eye3_TA_tex_txt,
                hip_6_eye4_TA_tex_txt,
                hip_6_eye5_TA_tex_txt,
                hip_6_eye6_TA_tex_txt,
                hip_6_eye7_TA_tex_txt,
                hip_6_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            136,
            0,
            32,
        },
        0.007300000172108412,
        1,
        5,
        21,
        43,
        0,
        0,
        82,
        25,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_238,
        ACTOR_OBJ_BANK_376,
        &cKF_bs_r_hip_1,
        {
            hip_7_tmem_txt,
            hip_7_pal,
            {
                hip_7_eye1_TA_tex_txt,
                hip_7_eye2_TA_tex_txt,
                hip_7_eye3_TA_tex_txt,
                hip_7_eye4_TA_tex_txt,
                hip_7_eye5_TA_tex_txt,
                hip_7_eye6_TA_tex_txt,
                hip_7_eye7_TA_tex_txt,
                hip_7_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            136,
            0,
            32,
        },
        0.007300000172108412,
        1,
        6,
        3,
        43,
        0,
        0,
        83,
        25,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_343,
        ACTOR_OBJ_BANK_377,
        &cKF_bs_r_squ_1,
        {
            squ_9_tmem_txt,
            squ_9_pal,
            {
                squ_9_eye1_TA_tex_txt,
                squ_9_eye2_TA_tex_txt,
                squ_9_eye3_TA_tex_txt,
                squ_9_eye4_TA_tex_txt,
                squ_9_eye5_TA_tex_txt,
                squ_9_eye6_TA_tex_txt,
                squ_9_eye7_TA_tex_txt,
                squ_9_eye8_TA_tex_txt,
            },
            {
                squ_9_mouth1_TA_tex_txt,
                squ_9_mouth2_TA_tex_txt,
                squ_9_mouth3_TA_tex_txt,
                squ_9_mouth4_TA_tex_txt,
                squ_9_mouth5_TA_tex_txt,
                squ_9_mouth6_TA_tex_txt,
            },
            72,
            104,
            160,
        },
        0.006800000090152025,
        0,
        8,
        7,
        26,
        0,
        0,
        55,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_343,
        ACTOR_OBJ_BANK_378,
        &cKF_bs_r_squ_1,
        {
            squ_10_tmem_txt,
            squ_10_pal,
            {
                squ_10_eye1_TA_tex_txt,
                squ_10_eye2_TA_tex_txt,
                squ_10_eye3_TA_tex_txt,
                squ_10_eye4_TA_tex_txt,
                squ_10_eye5_TA_tex_txt,
                squ_10_eye6_TA_tex_txt,
                squ_10_eye7_TA_tex_txt,
                squ_10_eye8_TA_tex_txt,
            },
            {
                squ_10_mouth1_TA_tex_txt,
                squ_10_mouth2_TA_tex_txt,
                squ_10_mouth3_TA_tex_txt,
                squ_10_mouth4_TA_tex_txt,
                squ_10_mouth5_TA_tex_txt,
                squ_10_mouth6_TA_tex_txt,
            },
            72,
            104,
            160,
        },
        0.006800000090152025,
        0,
        9,
        2,
        26,
        0,
        0,
        56,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_200,
        ACTOR_OBJ_BANK_379,
        &cKF_bs_r_elp_1,
        {
            elp_5_tmem_txt,
            elp_5_pal,
            {
                elp_5_eye1_TA_tex_txt,
                elp_5_eye2_TA_tex_txt,
                elp_5_eye3_TA_tex_txt,
                elp_5_eye4_TA_tex_txt,
                elp_5_eye5_TA_tex_txt,
                elp_5_eye6_TA_tex_txt,
                elp_5_eye7_TA_tex_txt,
                elp_5_eye8_TA_tex_txt,
            },
            {
                elp_5_mouth1_TA_tex_txt,
                elp_5_mouth2_TA_tex_txt,
                elp_5_mouth3_TA_tex_txt,
                elp_5_mouth4_TA_tex_txt,
                elp_5_mouth5_TA_tex_txt,
                elp_5_mouth6_TA_tex_txt,
            },
            48,
            176,
            80,
        },
        0.009999999776482582,
        1,
        4,
        22,
        40,
        0,
        0,
        19,
        25,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_200,
        ACTOR_OBJ_BANK_380,
        &cKF_bs_r_elp_1,
        {
            elp_6_tmem_txt,
            elp_6_pal,
            {
                elp_6_eye1_TA_tex_txt,
                elp_6_eye2_TA_tex_txt,
                elp_6_eye3_TA_tex_txt,
                elp_6_eye4_TA_tex_txt,
                elp_6_eye5_TA_tex_txt,
                elp_6_eye6_TA_tex_txt,
                elp_6_eye7_TA_tex_txt,
                elp_6_eye8_TA_tex_txt,
            },
            {
                elp_6_mouth1_TA_tex_txt,
                elp_6_mouth2_TA_tex_txt,
                elp_6_mouth3_TA_tex_txt,
                elp_6_mouth4_TA_tex_txt,
                elp_6_mouth5_TA_tex_txt,
                elp_6_mouth6_TA_tex_txt,
            },
            48,
            176,
            80,
        },
        0.009999999776482582,
        1,
        5,
        11,
        40,
        0,
        0,
        20,
        25,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_174,
        ACTOR_OBJ_BANK_381,
        &cKF_bs_r_crd_1,
        {
            crd_4_tmem_txt,
            crd_4_pal,
            {
                crd_4_eye1_TA_tex_txt,
                crd_4_eye2_TA_tex_txt,
                crd_4_eye3_TA_tex_txt,
                crd_4_eye4_TA_tex_txt,
                crd_4_eye5_TA_tex_txt,
                crd_4_eye6_TA_tex_txt,
                crd_4_eye7_TA_tex_txt,
                crd_4_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            96,
            0,
            168,
        },
        0.010499999858438969,
        1,
        3,
        15,
        48,
        0,
        0,
        149,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_320,
        ACTOR_OBJ_BANK_385,
        &cKF_bs_r_rbt_1,
        {
            rbt_10_tmem_txt,
            rbt_10_pal,
            {
                rbt_10_eye1_TA_tex_txt,
                rbt_10_eye2_TA_tex_txt,
                rbt_10_eye3_TA_tex_txt,
                rbt_10_eye4_TA_tex_txt,
                rbt_10_eye5_TA_tex_txt,
                rbt_10_eye6_TA_tex_txt,
                rbt_10_eye7_TA_tex_txt,
                rbt_10_eye8_TA_tex_txt,
            },
            {
                rbt_10_mouth1_TA_tex_txt,
                rbt_10_mouth2_TA_tex_txt,
                rbt_10_mouth3_TA_tex_txt,
                rbt_10_mouth4_TA_tex_txt,
                rbt_10_mouth5_TA_tex_txt,
                rbt_10_mouth6_TA_tex_txt,
            },
            80,
            112,
            176,
        },
        0.009999999776482582,
        0,
        9,
        12,
        34,
        0,
        0,
        66,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_337,
        ACTOR_OBJ_BANK_382,
        &cKF_bs_r_shp_1,
        {
            shp_2_tmem_txt,
            shp_2_pal,
            {
                shp_2_eye1_TA_tex_txt,
                shp_2_eye2_TA_tex_txt,
                shp_2_eye3_TA_tex_txt,
                shp_2_eye4_TA_tex_txt,
                shp_2_eye5_TA_tex_txt,
                shp_2_eye6_TA_tex_txt,
                shp_2_eye7_TA_tex_txt,
                shp_2_eye8_TA_tex_txt,
            },
            {
                shp_2_mouth1_TA_tex_txt,
                shp_2_mouth2_TA_tex_txt,
                shp_2_mouth3_TA_tex_txt,
                shp_2_mouth4_TA_tex_txt,
                shp_2_mouth5_TA_tex_txt,
                shp_2_mouth6_TA_tex_txt,
            },
            96,
            128,
            192,
        },
        0.009999999776482582,
        0,
        1,
        8,
        40,
        0,
        0,
        22,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_337,
        ACTOR_OBJ_BANK_383,
        &cKF_bs_r_shp_1,
        {
            shp_3_tmem_txt,
            shp_3_pal,
            {
                shp_3_eye1_TA_tex_txt,
                shp_3_eye2_TA_tex_txt,
                shp_3_eye3_TA_tex_txt,
                shp_3_eye4_TA_tex_txt,
                shp_3_eye5_TA_tex_txt,
                shp_3_eye6_TA_tex_txt,
                shp_3_eye7_TA_tex_txt,
                shp_3_eye8_TA_tex_txt,
            },
            {
                shp_3_mouth1_TA_tex_txt,
                shp_3_mouth2_TA_tex_txt,
                shp_3_mouth3_TA_tex_txt,
                shp_3_mouth4_TA_tex_txt,
                shp_3_mouth5_TA_tex_txt,
                shp_3_mouth6_TA_tex_txt,
            },
            96,
            128,
            192,
        },
        0.009999999776482582,
        0,
        2,
        6,
        40,
        0,
        0,
        23,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_362,
        ACTOR_OBJ_BANK_384,
        &cKF_bs_r_wol_1,
        {
            wol_5_tmem_txt,
            wol_5_pal,
            {
                wol_5_eye1_TA_tex_txt,
                wol_5_eye2_TA_tex_txt,
                wol_5_eye3_TA_tex_txt,
                wol_5_eye4_TA_tex_txt,
                wol_5_eye5_TA_tex_txt,
                wol_5_eye6_TA_tex_txt,
                wol_5_eye7_TA_tex_txt,
                wol_5_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            80,
            0,
            160,
        },
        0.009999999776482582,
        1,
        4,
        29,
        37,
        0,
        0,
        88,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_191,
        ACTOR_OBJ_BANK_386,
        &cKF_bs_r_duk_1,
        {
            duk_9_tmem_txt,
            duk_9_pal,
            {
                duk_9_eye1_TA_tex_txt,
                duk_9_eye2_TA_tex_txt,
                duk_9_eye3_TA_tex_txt,
                duk_9_eye4_TA_tex_txt,
                duk_9_eye5_TA_tex_txt,
                duk_9_eye6_TA_tex_txt,
                duk_9_eye7_TA_tex_txt,
                duk_9_eye8_TA_tex_txt,
            },
            {
                duk_9_mouth1_TA_tex_txt,
                duk_9_mouth2_TA_tex_txt,
                duk_9_mouth3_TA_tex_txt,
                duk_9_mouth4_TA_tex_txt,
                duk_9_mouth5_TA_tex_txt,
                duk_9_mouth6_TA_tex_txt,
            },
            112,
            72,
            160,
        },
        0.009999999776482582,
        1,
        8,
        7,
        31,
        0,
        0,
        75,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_191,
        ACTOR_OBJ_BANK_387,
        &cKF_bs_r_duk_1,
        {
            duk_10_tmem_txt,
            duk_10_pal,
            {
                duk_10_eye1_TA_tex_txt,
                duk_10_eye2_TA_tex_txt,
                duk_10_eye3_TA_tex_txt,
                duk_10_eye4_TA_tex_txt,
                duk_10_eye5_TA_tex_txt,
                duk_10_eye6_TA_tex_txt,
                duk_10_eye7_TA_tex_txt,
                duk_10_eye8_TA_tex_txt,
            },
            {
                duk_10_mouth1_TA_tex_txt,
                duk_10_mouth2_TA_tex_txt,
                duk_10_mouth3_TA_tex_txt,
                duk_10_mouth4_TA_tex_txt,
                duk_10_mouth5_TA_tex_txt,
                duk_10_mouth6_TA_tex_txt,
            },
            112,
            72,
            160,
        },
        0.009999999776482582,
        1,
        9,
        8,
        31,
        0,
        0,
        76,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_337,
        ACTOR_OBJ_BANK_388,
        &cKF_bs_r_shp_1,
        {
            shp_4_tmem_txt,
            shp_4_pal,
            {
                shp_4_eye1_TA_tex_txt,
                shp_4_eye2_TA_tex_txt,
                shp_4_eye3_TA_tex_txt,
                shp_4_eye4_TA_tex_txt,
                shp_4_eye5_TA_tex_txt,
                shp_4_eye6_TA_tex_txt,
                shp_4_eye7_TA_tex_txt,
                shp_4_eye8_TA_tex_txt,
            },
            {
                shp_4_mouth1_TA_tex_txt,
                shp_4_mouth2_TA_tex_txt,
                shp_4_mouth3_TA_tex_txt,
                shp_4_mouth4_TA_tex_txt,
                shp_4_mouth5_TA_tex_txt,
                shp_4_mouth6_TA_tex_txt,
            },
            96,
            128,
            192,
        },
        0.009999999776482582,
        0,
        3,
        7,
        40,
        0,
        0,
        24,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_337,
        ACTOR_OBJ_BANK_389,
        &cKF_bs_r_shp_1,
        {
            shp_5_tmem_txt,
            shp_5_pal,
            {
                shp_5_eye1_TA_tex_txt,
                shp_5_eye2_TA_tex_txt,
                shp_5_eye3_TA_tex_txt,
                shp_5_eye4_TA_tex_txt,
                shp_5_eye5_TA_tex_txt,
                shp_5_eye6_TA_tex_txt,
                shp_5_eye7_TA_tex_txt,
                shp_5_eye8_TA_tex_txt,
            },
            {
                shp_5_mouth1_TA_tex_txt,
                shp_5_mouth2_TA_tex_txt,
                shp_5_mouth3_TA_tex_txt,
                shp_5_mouth4_TA_tex_txt,
                shp_5_mouth5_TA_tex_txt,
                shp_5_mouth6_TA_tex_txt,
            },
            96,
            128,
            192,
        },
        0.009999999776482582,
        0,
        4,
        17,
        40,
        0,
        0,
        25,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_337,
        ACTOR_OBJ_BANK_390,
        &cKF_bs_r_shp_1,
        {
            shp_6_tmem_txt,
            shp_6_pal,
            {
                shp_6_eye1_TA_tex_txt,
                shp_6_eye2_TA_tex_txt,
                shp_6_eye3_TA_tex_txt,
                shp_6_eye4_TA_tex_txt,
                shp_6_eye5_TA_tex_txt,
                shp_6_eye6_TA_tex_txt,
                shp_6_eye7_TA_tex_txt,
                shp_6_eye8_TA_tex_txt,
            },
            {
                shp_6_mouth1_TA_tex_txt,
                shp_6_mouth2_TA_tex_txt,
                shp_6_mouth3_TA_tex_txt,
                shp_6_mouth4_TA_tex_txt,
                shp_6_mouth5_TA_tex_txt,
                shp_6_mouth6_TA_tex_txt,
            },
            96,
            128,
            192,
        },
        0.009999999776482582,
        0,
        5,
        22,
        40,
        0,
        0,
        26,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_182,
        ACTOR_OBJ_BANK_189,
        &cKF_bs_r_dog_1,
        {
            dog_7_tmem_txt,
            dog_7_pal,
            {
                dog_7_eye1_TA_tex_txt,
                dog_7_eye2_TA_tex_txt,
                dog_7_eye3_TA_tex_txt,
                dog_7_eye4_TA_tex_txt,
                dog_7_eye5_TA_tex_txt,
                dog_7_eye6_TA_tex_txt,
                dog_7_eye7_TA_tex_txt,
                dog_7_eye8_TA_tex_txt,
            },
            {
                dog_7_mouth1_TA_tex_txt,
                dog_7_mouth2_TA_tex_txt,
                dog_7_mouth3_TA_tex_txt,
                dog_7_mouth4_TA_tex_txt,
                dog_7_mouth5_TA_tex_txt,
                dog_7_mouth6_TA_tex_txt,
            },
            48,
            0,
            80,
        },
        0.009499999694526196,
        0,
        6,
        20,
        37,
        0,
        0,
        43,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_191,
        ACTOR_OBJ_BANK_426,
        &cKF_bs_r_duk_1,
        {
            duk_11_tmem_txt,
            duk_11_pal,
            {
                duk_11_eye1_TA_tex_txt,
                duk_11_eye2_TA_tex_txt,
                duk_11_eye3_TA_tex_txt,
                duk_11_eye4_TA_tex_txt,
                duk_11_eye5_TA_tex_txt,
                duk_11_eye6_TA_tex_txt,
                duk_11_eye7_TA_tex_txt,
                duk_11_eye8_TA_tex_txt,
            },
            {
                duk_11_mouth1_TA_tex_txt,
                duk_11_mouth2_TA_tex_txt,
                duk_11_mouth3_TA_tex_txt,
                duk_11_mouth4_TA_tex_txt,
                duk_11_mouth5_TA_tex_txt,
                duk_11_mouth6_TA_tex_txt,
            },
            112,
            72,
            160,
        },
        0.009999999776482582,
        1,
        10,
        10,
        31,
        0,
        0,
        263,
        20,
        45,
        56,
        25,
    },
    {
        ACTOR_OBJ_BANK_320,
        ACTOR_OBJ_BANK_427,
        &cKF_bs_r_rbt_1,
        {
            rbt_11_tmem_txt,
            rbt_11_pal,
            {
                rbt_11_eye1_TA_tex_txt,
                rbt_11_eye2_TA_tex_txt,
                rbt_11_eye3_TA_tex_txt,
                rbt_11_eye4_TA_tex_txt,
                rbt_11_eye5_TA_tex_txt,
                rbt_11_eye6_TA_tex_txt,
                rbt_11_eye7_TA_tex_txt,
                rbt_11_eye8_TA_tex_txt,
            },
            {
                rbt_11_mouth1_TA_tex_txt,
                rbt_11_mouth2_TA_tex_txt,
                rbt_11_mouth3_TA_tex_txt,
                rbt_11_mouth4_TA_tex_txt,
                rbt_11_mouth5_TA_tex_txt,
                rbt_11_mouth6_TA_tex_txt,
            },
            80,
            112,
            176,
        },
        0.009999999776482582,
        0,
        10,
        0,
        34,
        0,
        0,
        272,
        20,
        40,
        61,
        25,
    },
    {
        ACTOR_OBJ_BANK_343,
        ACTOR_OBJ_BANK_421,
        &cKF_bs_r_squ_1,
        {
            squ_11_tmem_txt,
            squ_11_pal,
            {
                squ_11_eye1_TA_tex_txt,
                squ_11_eye2_TA_tex_txt,
                squ_11_eye3_TA_tex_txt,
                squ_11_eye4_TA_tex_txt,
                squ_11_eye5_TA_tex_txt,
                squ_11_eye6_TA_tex_txt,
                squ_11_eye7_TA_tex_txt,
                squ_11_eye8_TA_tex_txt,
            },
            {
                squ_11_mouth1_TA_tex_txt,
                squ_11_mouth2_TA_tex_txt,
                squ_11_mouth3_TA_tex_txt,
                squ_11_mouth4_TA_tex_txt,
                squ_11_mouth5_TA_tex_txt,
                squ_11_mouth6_TA_tex_txt,
            },
            72,
            104,
            160,
        },
        0.006800000090152025,
        0,
        10,
        15,
        26,
        0,
        0,
        275,
        20,
        35,
        58,
        25,
    },
    {
        ACTOR_OBJ_BANK_205,
        ACTOR_OBJ_BANK_428,
        &cKF_bs_r_flg_1,
        {
            flg_13_tmem_txt,
            flg_13_pal,
            {
                flg_13_eye1_TA_tex_txt,
                flg_13_eye2_TA_tex_txt,
                flg_13_eye3_TA_tex_txt,
                flg_13_eye4_TA_tex_txt,
                flg_13_eye5_TA_tex_txt,
                flg_13_eye6_TA_tex_txt,
                flg_13_eye7_TA_tex_txt,
                flg_13_eye8_TA_tex_txt,
            },
            {
                flg_13_mouth1_TA_tex_txt,
                flg_13_mouth2_TA_tex_txt,
                flg_13_mouth3_TA_tex_txt,
                flg_13_mouth4_TA_tex_txt,
                flg_13_mouth5_TA_tex_txt,
                flg_13_mouth6_TA_tex_txt,
            },
            0,
            32,
            176,
        },
        0.00800000037997961,
        0,
        12,
        28,
        38,
        0,
        0,
        265,
        20,
        35,
        63,
        13,
    },
    {
        ACTOR_OBJ_BANK_268,
        ACTOR_OBJ_BANK_429,
        &cKF_bs_r_lon_1,
        {
            lon_4_tmem_txt,
            lon_4_pal,
            {
                lon_4_eye1_TA_tex_txt,
                lon_4_eye2_TA_tex_txt,
                lon_4_eye3_TA_tex_txt,
                lon_4_eye4_TA_tex_txt,
                lon_4_eye5_TA_tex_txt,
                lon_4_eye6_TA_tex_txt,
                lon_4_eye7_TA_tex_txt,
                lon_4_eye8_TA_tex_txt,
            },
            {
                lon_4_mouth1_TA_tex_txt,
                lon_4_mouth2_TA_tex_txt,
                lon_4_mouth3_TA_tex_txt,
                lon_4_mouth4_TA_tex_txt,
                lon_4_mouth5_TA_tex_txt,
                lon_4_mouth6_TA_tex_txt,
            },
            128,
            96,
            184,
        },
        0.01140000019222498,
        0,
        3,
        26,
        43,
        0,
        0,
        269,
        20,
        50,
        64,
        13,
    },
    {
        ACTOR_OBJ_BANK_291,
        ACTOR_OBJ_BANK_430,
        &cKF_bs_r_pgn_1,
        {
            pgn_8_tmem_txt,
            pgn_8_pal,
            {
                pgn_8_eye1_TA_tex_txt,
                pgn_8_eye2_TA_tex_txt,
                pgn_8_eye3_TA_tex_txt,
                pgn_8_eye4_TA_tex_txt,
                pgn_8_eye5_TA_tex_txt,
                pgn_8_eye6_TA_tex_txt,
                pgn_8_eye7_TA_tex_txt,
                pgn_8_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            48,
            0,
            144,
        },
        0.007499999832361937,
        1,
        7,
        24,
        31,
        0,
        0,
        271,
        20,
        40,
        54,
        13,
    },
    {
        ACTOR_OBJ_BANK_200,
        ACTOR_OBJ_BANK_431,
        &cKF_bs_r_elp_1,
        {
            elp_7_tmem_txt,
            elp_7_pal,
            {
                elp_7_eye1_TA_tex_txt,
                elp_7_eye2_TA_tex_txt,
                elp_7_eye3_TA_tex_txt,
                elp_7_eye4_TA_tex_txt,
                elp_7_eye5_TA_tex_txt,
                elp_7_eye6_TA_tex_txt,
                elp_7_eye7_TA_tex_txt,
                elp_7_eye8_TA_tex_txt,
            },
            {
                elp_7_mouth1_TA_tex_txt,
                elp_7_mouth2_TA_tex_txt,
                elp_7_mouth3_TA_tex_txt,
                elp_7_mouth4_TA_tex_txt,
                elp_7_mouth5_TA_tex_txt,
                elp_7_mouth6_TA_tex_txt,
            },
            48,
            176,
            80,
        },
        0.009999999776482582,
        1,
        6,
        20,
        40,
        0,
        0,
        264,
        25,
        55,
        59,
        25,
    },
    {
        ACTOR_OBJ_BANK_113,
        ACTOR_OBJ_BANK_432,
        &cKF_bs_r_brd_1,
        {
            brd_11_tmem_txt,
            brd_11_pal,
            {
                brd_11_eye1_TA_tex_txt,
                brd_11_eye2_TA_tex_txt,
                brd_11_eye3_TA_tex_txt,
                brd_11_eye4_TA_tex_txt,
                brd_11_eye5_TA_tex_txt,
                brd_11_eye6_TA_tex_txt,
                brd_11_eye7_TA_tex_txt,
                brd_11_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            8,
            0,
            144,
        },
        0.009499999694526196,
        1,
        10,
        14,
        35,
        0,
        0,
        260,
        20,
        45,
        62,
        25,
    },
    {
        ACTOR_OBJ_BANK_362,
        ACTOR_OBJ_BANK_433,
        &cKF_bs_r_wol_1,
        {
            wol_6_tmem_txt,
            wol_6_pal,
            {
                wol_6_eye1_TA_tex_txt,
                wol_6_eye2_TA_tex_txt,
                wol_6_eye3_TA_tex_txt,
                wol_6_eye4_TA_tex_txt,
                wol_6_eye5_TA_tex_txt,
                wol_6_eye6_TA_tex_txt,
                wol_6_eye7_TA_tex_txt,
                wol_6_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            80,
            0,
            160,
        },
        0.009999999776482582,
        1,
        5,
        21,
        37,
        0,
        0,
        274,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_274,
        ACTOR_OBJ_BANK_434,
        &cKF_bs_r_mus_1,
        {
            mus_10_tmem_txt,
            mus_10_pal,
            {
                mus_10_eye1_TA_tex_txt,
                mus_10_eye2_TA_tex_txt,
                mus_10_eye3_TA_tex_txt,
                mus_10_eye4_TA_tex_txt,
                mus_10_eye5_TA_tex_txt,
                mus_10_eye6_TA_tex_txt,
                mus_10_eye7_TA_tex_txt,
                mus_10_eye8_TA_tex_txt,
            },
            {
                mus_10_mouth1_TA_tex_txt,
                mus_10_mouth2_TA_tex_txt,
                mus_10_mouth3_TA_tex_txt,
                mus_10_mouth4_TA_tex_txt,
                mus_10_mouth5_TA_tex_txt,
                mus_10_mouth6_TA_tex_txt,
            },
            96,
            128,
            184,
        },
        0.005499999970197678,
        0,
        9,
        27,
        30,
        0,
        0,
        270,
        20,
        40,
        66,
        25,
    },
    {
        ACTOR_OBJ_BANK_243,
        ACTOR_OBJ_BANK_435,
        &cKF_bs_r_hrs_1,
        {
            hrs_8_tmem_txt,
            hrs_8_pal,
            {
                hrs_8_eye1_TA_tex_txt,
                hrs_8_eye2_TA_tex_txt,
                hrs_8_eye3_TA_tex_txt,
                hrs_8_eye4_TA_tex_txt,
                hrs_8_eye5_TA_tex_txt,
                hrs_8_eye6_TA_tex_txt,
                hrs_8_eye7_TA_tex_txt,
                hrs_8_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            40,
            0,
            184,
        },
        0.011500000022351742,
        1,
        7,
        9,
        43,
        0,
        0,
        267,
        23,
        50,
        65,
        25,
    },
    {
        ACTOR_OBJ_BANK_148,
        ACTOR_OBJ_BANK_436,
        &cKF_bs_r_chn_1,
        {
            chn_9_tmem_txt,
            chn_9_pal,
            {
                chn_9_eye1_TA_tex_txt,
                chn_9_eye2_TA_tex_txt,
                chn_9_eye3_TA_tex_txt,
                chn_9_eye4_TA_tex_txt,
                chn_9_eye5_TA_tex_txt,
                chn_9_eye6_TA_tex_txt,
                chn_9_eye7_TA_tex_txt,
                chn_9_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            16,
            0,
            152,
        },
        0.009999999776482582,
        1,
        8,
        19,
        35,
        0,
        0,
        262,
        20,
        45,
        52,
        25,
    },
    {
        ACTOR_OBJ_BANK_262,
        ACTOR_OBJ_BANK_437,
        &cKF_bs_r_kal_1,
        {
            kal_6_tmem_txt,
            kal_6_pal,
            {
                kal_6_eye1_TA_tex_txt,
                kal_6_eye2_TA_tex_txt,
                kal_6_eye3_TA_tex_txt,
                kal_6_eye4_TA_tex_txt,
                kal_6_eye5_TA_tex_txt,
                kal_6_eye6_TA_tex_txt,
                kal_6_eye7_TA_tex_txt,
                kal_6_eye8_TA_tex_txt,
            },
            {
                kal_6_mouth1_TA_tex_txt,
                kal_6_mouth2_TA_tex_txt,
                kal_6_mouth3_TA_tex_txt,
                kal_6_mouth4_TA_tex_txt,
                kal_6_mouth5_TA_tex_txt,
                kal_6_mouth6_TA_tex_txt,
            },
            0,
            32,
            192,
        },
        0.008500000461935997,
        0,
        5,
        18,
        34,
        0,
        0,
        268,
        20,
        40,
        57,
        25,
    },
    {
        ACTOR_OBJ_BANK_227,
        ACTOR_OBJ_BANK_438,
        &cKF_bs_r_gor_1,
        {
            gor_5_tmem_txt,
            gor_5_pal,
            {
                gor_5_eye1_TA_tex_txt,
                gor_5_eye2_TA_tex_txt,
                gor_5_eye3_TA_tex_txt,
                gor_5_eye4_TA_tex_txt,
                gor_5_eye5_TA_tex_txt,
                gor_5_eye6_TA_tex_txt,
                gor_5_eye7_TA_tex_txt,
                gor_5_eye8_TA_tex_txt,
            },
            {
                gor_5_mouth1_TA_tex_txt,
                gor_5_mouth2_TA_tex_txt,
                gor_5_mouth3_TA_tex_txt,
                gor_5_mouth4_TA_tex_txt,
                gor_5_mouth5_TA_tex_txt,
                gor_5_mouth6_TA_tex_txt,
            },
            80,
            112,
            152,
        },
        0.009999999776482582,
        1,
        4,
        16,
        42,
        0,
        0,
        266,
        20,
        55,
        53,
        13,
    },
    {
        ACTOR_OBJ_BANK_356,
        ACTOR_OBJ_BANK_439,
        &cKF_bs_r_tig_1,
        {
            tig_4_tmem_txt,
            tig_4_pal,
            {
                tig_4_eye1_TA_tex_txt,
                tig_4_eye2_TA_tex_txt,
                tig_4_eye3_TA_tex_txt,
                tig_4_eye4_TA_tex_txt,
                tig_4_eye5_TA_tex_txt,
                tig_4_eye6_TA_tex_txt,
                tig_4_eye7_TA_tex_txt,
                tig_4_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            8,
            0,
            176,
        },
        0.011300000362098217,
        1,
        3,
        13,
        41,
        0,
        0,
        273,
        20,
        50,
        60,
        25,
    },
    {
        ACTOR_OBJ_BANK_157,
        ACTOR_OBJ_BANK_440,
        &cKF_bs_r_cbr_1,
        {
            cbr_10_tmem_txt,
            cbr_10_pal,
            {
                cbr_10_eye1_TA_tex_txt,
                cbr_10_eye2_TA_tex_txt,
                cbr_10_eye3_TA_tex_txt,
                cbr_10_eye4_TA_tex_txt,
                cbr_10_eye5_TA_tex_txt,
                cbr_10_eye6_TA_tex_txt,
                cbr_10_eye7_TA_tex_txt,
                cbr_10_eye8_TA_tex_txt,
            },
            {
                cbr_10_mouth1_TA_tex_txt,
                cbr_10_mouth2_TA_tex_txt,
                cbr_10_mouth3_TA_tex_txt,
                cbr_10_mouth4_TA_tex_txt,
                cbr_10_mouth5_TA_tex_txt,
                cbr_10_mouth6_TA_tex_txt,
            },
            128,
            8,
            176,
        },
        0.006500000134110451,
        0,
        9,
        5,
        33,
        0,
        0,
        261,
        20,
        45,
        55,
        25,
    },
    {
        ACTOR_OBJ_BANK_157,
        ACTOR_OBJ_BANK_441,
        &cKF_bs_r_cbr_1,
        {
            cbr_11_tmem_txt,
            cbr_11_pal,
            {
                cbr_11_eye1_TA_tex_txt,
                cbr_11_eye2_TA_tex_txt,
                cbr_11_eye3_TA_tex_txt,
                cbr_11_eye4_TA_tex_txt,
                cbr_11_eye5_TA_tex_txt,
                cbr_11_eye6_TA_tex_txt,
                cbr_11_eye7_TA_tex_txt,
                cbr_11_eye8_TA_tex_txt,
            },
            {
                cbr_11_mouth1_TA_tex_txt,
                cbr_11_mouth2_TA_tex_txt,
                cbr_11_mouth3_TA_tex_txt,
                cbr_11_mouth4_TA_tex_txt,
                cbr_11_mouth5_TA_tex_txt,
                cbr_11_mouth6_TA_tex_txt,
            },
            128,
            8,
            176,
        },
        0.006500000134110451,
        0,
        10,
        3,
        33,
        0,
        0,
        285,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_299,
        ACTOR_OBJ_BANK_442,
        &cKF_bs_r_pig_1,
        {
            pig_11_tmem_txt,
            pig_11_pal,
            {
                pig_11_eye1_TA_tex_txt,
                pig_11_eye2_TA_tex_txt,
                pig_11_eye3_TA_tex_txt,
                pig_11_eye4_TA_tex_txt,
                pig_11_eye5_TA_tex_txt,
                pig_11_eye6_TA_tex_txt,
                pig_11_eye7_TA_tex_txt,
                pig_11_eye8_TA_tex_txt,
            },
            {
                pig_11_mouth1_TA_tex_txt,
                pig_11_mouth2_TA_tex_txt,
                pig_11_mouth3_TA_tex_txt,
                pig_11_mouth4_TA_tex_txt,
                pig_11_mouth5_TA_tex_txt,
                pig_11_mouth6_TA_tex_txt,
            },
            64,
            112,
            160,
        },
        0.009999999776482582,
        0,
        10,
        31,
        36,
        0,
        0,
        276,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_133,
        ACTOR_OBJ_BANK_147,
        &cKF_bs_r_cat_1,
        {
            cat_14_tmem_txt,
            cat_14_pal,
            {
                cat_14_eye1_TA_tex_txt,
                cat_14_eye2_TA_tex_txt,
                cat_14_eye3_TA_tex_txt,
                cat_14_eye4_TA_tex_txt,
                cat_14_eye5_TA_tex_txt,
                cat_14_eye6_TA_tex_txt,
                cat_14_eye7_TA_tex_txt,
                cat_14_eye8_TA_tex_txt,
            },
            {
                cat_14_mouth1_TA_tex_txt,
                cat_14_mouth2_TA_tex_txt,
                cat_14_mouth3_TA_tex_txt,
                cat_14_mouth4_TA_tex_txt,
                cat_14_mouth5_TA_tex_txt,
                cat_14_mouth6_TA_tex_txt,
            },
            0,
            32,
            128,
        },
        0.008999999612569809,
        0,
        13,
        17,
        33,
        0,
        0,
        277,
        20,
        40,
        67,
        25,
    },
    {
        ACTOR_OBJ_BANK_133,
        ACTOR_OBJ_BANK_459,
        &cKF_bs_r_cat_1,
        {
            cat_15_tmem_txt,
            cat_15_pal,
            {
                cat_15_eye1_TA_tex_txt,
                cat_15_eye2_TA_tex_txt,
                cat_15_eye3_TA_tex_txt,
                cat_15_eye4_TA_tex_txt,
                cat_15_eye5_TA_tex_txt,
                cat_15_eye6_TA_tex_txt,
                cat_15_eye7_TA_tex_txt,
                cat_15_eye8_TA_tex_txt,
            },
            {
                cat_15_mouth1_TA_tex_txt,
                cat_15_mouth2_TA_tex_txt,
                cat_15_mouth3_TA_tex_txt,
                cat_15_mouth4_TA_tex_txt,
                cat_15_mouth5_TA_tex_txt,
                cat_15_mouth6_TA_tex_txt,
            },
            0,
            32,
            128,
        },
        0.008999999612569809,
        0,
        14,
        13,
        33,
        0,
        0,
        286,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_148,
        ACTOR_OBJ_BANK_153,
        &cKF_bs_r_chn_1,
        {
            chn_1_tmem_txt,
            chn_1_pal,
            {
                chn_1_eye1_TA_tex_txt,
                chn_1_eye2_TA_tex_txt,
                chn_1_eye3_TA_tex_txt,
                chn_1_eye4_TA_tex_txt,
                chn_1_eye5_TA_tex_txt,
                chn_1_eye6_TA_tex_txt,
                chn_1_eye7_TA_tex_txt,
                chn_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            0,
            0,
            0,
        },
        0.009999999776482582,
        1,
        4,
        1,
        35,
        0,
        0,
        1,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_148,
        ACTOR_OBJ_BANK_153,
        &cKF_bs_r_chn_1,
        {
            chn_1_tmem_txt,
            chn_1_pal,
            {
                chn_1_eye1_TA_tex_txt,
                chn_1_eye2_TA_tex_txt,
                chn_1_eye3_TA_tex_txt,
                chn_1_eye4_TA_tex_txt,
                chn_1_eye5_TA_tex_txt,
                chn_1_eye6_TA_tex_txt,
                chn_1_eye7_TA_tex_txt,
                chn_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            0,
            0,
            0,
        },
        0.008999999612569809,
        1,
        4,
        0,
        40,
        0,
        0,
        1,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_94,
        ACTOR_OBJ_BANK_95,
        &cKF_bs_r_wls_1,
        {
            wls_1_tmem_txt,
            wls_1_pal,
            {
                wls_1_eye1_TA_tex_txt,
                wls_1_eye2_TA_tex_txt,
                wls_1_eye3_TA_tex_txt,
                wls_1_eye4_TA_tex_txt,
                wls_1_eye5_TA_tex_txt,
                wls_1_eye6_TA_tex_txt,
                wls_1_eye7_TA_tex_txt,
                wls_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            20,
            0,
            0,
        },
        0.012500000186264515,
        1,
        0,
        0,
        51,
        0,
        0,
        224,
        23,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_124,
        ACTOR_OBJ_BANK_125,
        &cKF_bs_r_fox_1,
        {
            fox_1_tmem_txt,
            fox_1_pal,
            {
                fox_1_eye1_TA_tex_txt,
                fox_1_eye2_TA_tex_txt,
                fox_1_eye3_TA_tex_txt,
                fox_1_eye4_TA_tex_txt,
                fox_1_eye5_TA_tex_txt,
                fox_1_eye6_TA_tex_txt,
                fox_1_eye7_TA_tex_txt,
                fox_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            36,
            0,
            0,
        },
        0.009499999694526196,
        1,
        0,
        0,
        36,
        0,
        0,
        223,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_180,
        ACTOR_OBJ_BANK_181,
        &cKF_bs_r_grf_1,
        {
            grf_1_tmem_txt,
            grf_1_pal,
            {
                grf_1_eye1_TA_tex_txt,
                grf_1_eye2_TA_tex_txt,
                grf_1_eye3_TA_tex_txt,
                grf_1_eye4_TA_tex_txt,
                grf_1_eye5_TA_tex_txt,
                grf_1_eye6_TA_tex_txt,
                grf_1_eye7_TA_tex_txt,
                grf_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            68,
            0,
            0,
        },
        0.010999999940395355,
        1,
        0,
        0,
        35,
        0,
        0,
        226,
        20,
        65,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_314,
        ACTOR_OBJ_BANK_315,
        &cKF_bs_r_pga_1,
        {
            pga_1_tmem_txt,
            pga_1_pal,
            {
                pga_1_eye1_TA_tex_txt,
                pga_1_eye2_TA_tex_txt,
                pga_1_eye3_TA_tex_txt,
                pga_1_eye4_TA_tex_txt,
                pga_1_eye5_TA_tex_txt,
                pga_1_eye6_TA_tex_txt,
                pga_1_eye7_TA_tex_txt,
                pga_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            80,
            0,
            0,
        },
        0.00800000037997961,
        1,
        0,
        0,
        36,
        0,
        0,
        234,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_232,
        ACTOR_OBJ_BANK_233,
        &cKF_bs_r_xct_1,
        {
            xct_1_tmem_txt,
            xct_1_pal,
            {
                xct_1_eye1_TA_tex_txt,
                xct_1_eye2_TA_tex_txt,
                xct_1_eye3_TA_tex_txt,
                xct_1_eye4_TA_tex_txt,
                xct_1_eye5_TA_tex_txt,
                xct_1_eye6_TA_tex_txt,
                xct_1_eye7_TA_tex_txt,
                xct_1_eye8_TA_tex_txt,
            },
            {
                xct_1_mouth1_TA_tex_txt,
                xct_1_mouth2_TA_tex_txt,
                xct_1_mouth3_TA_tex_txt,
                xct_1_mouth4_TA_tex_txt,
                xct_1_mouth5_TA_tex_txt,
                xct_1_mouth6_TA_tex_txt,
            },
            32,
            96,
            0,
        },
        0.008999999612569809,
        0,
        0,
        0,
        31,
        0,
        0,
        0,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_232,
        ACTOR_OBJ_BANK_233,
        &cKF_bs_r_xct_1,
        {
            xct_1_tmem_txt,
            xct_1_pal,
            {
                xct_1_eye1_TA_tex_txt,
                xct_1_eye2_TA_tex_txt,
                xct_1_eye3_TA_tex_txt,
                xct_1_eye4_TA_tex_txt,
                xct_1_eye5_TA_tex_txt,
                xct_1_eye6_TA_tex_txt,
                xct_1_eye7_TA_tex_txt,
                xct_1_eye8_TA_tex_txt,
            },
            {
                xct_1_mouth1_TA_tex_txt,
                xct_1_mouth2_TA_tex_txt,
                xct_1_mouth3_TA_tex_txt,
                xct_1_mouth4_TA_tex_txt,
                xct_1_mouth5_TA_tex_txt,
                xct_1_mouth6_TA_tex_txt,
            },
            32,
            96,
            0,
        },
        0.008999999612569809,
        0,
        0,
        0,
        31,
        0,
        0,
        0,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_131,
        ACTOR_OBJ_BANK_132,
        &cKF_bs_r_cml_1,
        {
            cml_1_tmem_txt,
            cml_1_pal,
            {
                cml_1_eye1_TA_tex_txt,
                cml_1_eye2_TA_tex_txt,
                cml_1_eye3_TA_tex_txt,
                cml_1_eye4_TA_tex_txt,
                cml_1_eye5_TA_tex_txt,
                cml_1_eye6_TA_tex_txt,
                cml_1_eye7_TA_tex_txt,
                cml_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            48,
            0,
            0,
        },
        0.01600000075995922,
        1,
        0,
        0,
        53,
        0,
        0,
        225,
        23,
        60,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_251,
        ACTOR_OBJ_BANK_252,
        &cKF_bs_r_boa_1,
        {
            boa_1_tmem_txt,
            boa_1_pal,
            {
                boa_1_eye1_TA_tex_txt,
                boa_1_eye2_TA_tex_txt,
                boa_1_eye3_TA_tex_txt,
                boa_1_eye4_TA_tex_txt,
                boa_1_eye5_TA_tex_txt,
                boa_1_eye6_TA_tex_txt,
                boa_1_eye7_TA_tex_txt,
                boa_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            48,
            0,
            0,
        },
        0.010999999940395355,
        1,
        0,
        0,
        46,
        0,
        0,
        227,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_339,
        ACTOR_OBJ_BANK_340,
        &cKF_bs_r_rcn_1,
        {
            rcn_1_tmem_txt,
            rcn_1_pal,
            {
                rcn_1_eye1_TA_tex_txt,
                rcn_1_eye2_TA_tex_txt,
                rcn_1_eye3_TA_tex_txt,
                rcn_1_eye4_TA_tex_txt,
                rcn_1_eye5_TA_tex_txt,
                rcn_1_eye6_TA_tex_txt,
                rcn_1_eye7_TA_tex_txt,
                rcn_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            40,
            0,
            0,
        },
        0.010999999940395355,
        1,
        0,
        0,
        35,
        0,
        0,
        219,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_167,
        ACTOR_OBJ_BANK_168,
        &cKF_bs_r_rcc_1,
        {
            rcc_1_tmem_txt,
            rcc_1_pal,
            {
                rcc_1_eye1_TA_tex_txt,
                rcc_1_eye2_TA_tex_txt,
                rcc_1_eye3_TA_tex_txt,
                rcc_1_eye4_TA_tex_txt,
                rcc_1_eye5_TA_tex_txt,
                rcc_1_eye6_TA_tex_txt,
                rcc_1_eye7_TA_tex_txt,
                rcc_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            32,
            0,
            0,
        },
        0.010999999940395355,
        1,
        0,
        0,
        35,
        0,
        0,
        220,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_354,
        ACTOR_OBJ_BANK_355,
        &cKF_bs_r_rcs_1,
        {
            rcs_1_tmem_txt,
            rcs_1_pal,
            {
                rcs_1_eye1_TA_tex_txt,
                rcs_1_eye2_TA_tex_txt,
                rcs_1_eye3_TA_tex_txt,
                rcs_1_eye4_TA_tex_txt,
                rcs_1_eye5_TA_tex_txt,
                rcs_1_eye6_TA_tex_txt,
                rcs_1_eye7_TA_tex_txt,
                rcs_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            16,
            0,
            0,
        },
        0.010999999940395355,
        1,
        0,
        0,
        35,
        0,
        0,
        221,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_178,
        ACTOR_OBJ_BANK_179,
        &cKF_bs_r_rcd_1,
        {
            rcd_1_tmem_txt,
            rcd_1_pal,
            {
                rcd_1_eye1_TA_tex_txt,
                rcd_1_eye2_TA_tex_txt,
                rcd_1_eye3_TA_tex_txt,
                rcd_1_eye4_TA_tex_txt,
                rcd_1_eye5_TA_tex_txt,
                rcd_1_eye6_TA_tex_txt,
                rcd_1_eye7_TA_tex_txt,
                rcd_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            16,
            0,
            0,
        },
        0.010999999940395355,
        1,
        0,
        0,
        35,
        0,
        0,
        222,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_234,
        ACTOR_OBJ_BANK_235,
        &cKF_bs_r_bpt_1,
        {
            bpt_1_tmem_txt,
            bpt_1_pal,
            {
                bpt_1_eye1_TA_tex_txt,
                bpt_1_eye2_TA_tex_txt,
                bpt_1_eye3_TA_tex_txt,
                bpt_1_eye4_TA_tex_txt,
                bpt_1_eye5_TA_tex_txt,
                bpt_1_eye6_TA_tex_txt,
                bpt_1_eye7_TA_tex_txt,
                bpt_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            12,
            0,
            0,
        },
        0.009499999694526196,
        1,
        0,
        0,
        40,
        0,
        0,
        228,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_310,
        ACTOR_OBJ_BANK_311,
        &cKF_bs_r_plc_1,
        {
            plc_1_tmem_txt,
            plc_1_pal,
            {
                plc_1_eye1_TA_tex_txt,
                plc_1_eye2_TA_tex_txt,
                plc_1_eye3_TA_tex_txt,
                plc_1_eye4_TA_tex_txt,
                plc_1_eye5_TA_tex_txt,
                plc_1_eye6_TA_tex_txt,
                plc_1_eye7_TA_tex_txt,
                plc_1_eye8_TA_tex_txt,
            },
            {
                plc_1_mouth1_TA_tex_txt,
                plc_1_mouth2_TA_tex_txt,
                plc_1_mouth3_TA_tex_txt,
                plc_1_mouth4_TA_tex_txt,
                plc_1_mouth5_TA_tex_txt,
                plc_1_mouth6_TA_tex_txt,
            },
            104,
            72,
            0,
        },
        0.009999999776482582,
        0,
        0,
        0,
        46,
        0,
        0,
        229,
        25,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_352,
        ACTOR_OBJ_BANK_353,
        &cKF_bs_r_mnk_1,
        {
            mnk_1_tmem_txt,
            mnk_1_pal,
            {
                mnk_1_eye1_TA_tex_txt,
                mnk_1_eye2_TA_tex_txt,
                mnk_1_eye3_TA_tex_txt,
                mnk_1_eye4_TA_tex_txt,
                mnk_1_eye5_TA_tex_txt,
                mnk_1_eye6_TA_tex_txt,
                mnk_1_eye7_TA_tex_txt,
                mnk_1_eye8_TA_tex_txt,
            },
            {
                mnk_1_mouth1_TA_tex_txt,
                mnk_1_mouth2_TA_tex_txt,
                mnk_1_mouth3_TA_tex_txt,
                mnk_1_mouth4_TA_tex_txt,
                mnk_1_mouth5_TA_tex_txt,
                mnk_1_mouth6_TA_tex_txt,
            },
            40,
            0,
            0,
        },
        0.008999999612569809,
        0,
        0,
        0,
        35,
        0,
        0,
        230,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_335,
        ACTOR_OBJ_BANK_336,
        &cKF_bs_r_snt_1,
        {
            snt_1_tmem_txt,
            snt_1_pal,
            {
                snt_1_eye1_TA_tex_txt,
                snt_1_eye2_TA_tex_txt,
                snt_1_eye3_TA_tex_txt,
                snt_1_eye4_TA_tex_txt,
                snt_1_eye5_TA_tex_txt,
                snt_1_eye6_TA_tex_txt,
                snt_1_eye7_TA_tex_txt,
                snt_1_eye8_TA_tex_txt,
            },
            {
                snt_1_mouth1_TA_tex_txt,
                snt_1_mouth2_TA_tex_txt,
                snt_1_mouth3_TA_tex_txt,
                snt_1_mouth4_TA_tex_txt,
                snt_1_mouth5_TA_tex_txt,
                snt_1_mouth6_TA_tex_txt,
            },
            8,
            44,
            0,
        },
        0.009999999776482582,
        0,
        0,
        0,
        46,
        0,
        0,
        232,
        25,
        55,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_312,
        ACTOR_OBJ_BANK_313,
        &cKF_bs_r_pla_1,
        {
            pla_1_tmem_txt,
            pla_1_pal,
            {
                pla_1_eye1_TA_tex_txt,
                pla_1_eye2_TA_tex_txt,
                pla_1_eye3_TA_tex_txt,
                pla_1_eye4_TA_tex_txt,
                pla_1_eye5_TA_tex_txt,
                pla_1_eye6_TA_tex_txt,
                pla_1_eye7_TA_tex_txt,
                pla_1_eye8_TA_tex_txt,
            },
            {
                pla_1_mouth1_TA_tex_txt,
                pla_1_mouth2_TA_tex_txt,
                pla_1_mouth3_TA_tex_txt,
                pla_1_mouth4_TA_tex_txt,
                pla_1_mouth5_TA_tex_txt,
                pla_1_mouth6_TA_tex_txt,
            },
            104,
            44,
            0,
        },
        0.009499999694526196,
        0,
        0,
        0,
        43,
        0,
        0,
        239,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_318,
        ACTOR_OBJ_BANK_319,
        &cKF_bs_r_plb_1,
        {
            plb_1_tmem_txt,
            plb_1_pal,
            {
                plb_1_eye1_TA_tex_txt,
                plb_1_eye2_TA_tex_txt,
                plb_1_eye3_TA_tex_txt,
                plb_1_eye4_TA_tex_txt,
                plb_1_eye5_TA_tex_txt,
                plb_1_eye6_TA_tex_txt,
                plb_1_eye7_TA_tex_txt,
                plb_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            84,
            0,
            0,
        },
        0.00800000037997961,
        1,
        0,
        0,
        38,
        0,
        0,
        233,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_316,
        ACTOR_OBJ_BANK_317,
        &cKF_bs_r_pgb_1,
        {
            pgb_1_tmem_txt,
            pgb_1_pal,
            {
                pgb_1_eye1_TA_tex_txt,
                pgb_1_eye2_TA_tex_txt,
                pgb_1_eye3_TA_tex_txt,
                pgb_1_eye4_TA_tex_txt,
                pgb_1_eye5_TA_tex_txt,
                pgb_1_eye6_TA_tex_txt,
                pgb_1_eye7_TA_tex_txt,
                pgb_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            100,
            0,
            0,
        },
        0.00800000037997961,
        1,
        0,
        0,
        36,
        0,
        0,
        235,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_124,
        ACTOR_OBJ_BANK_125,
        &cKF_bs_r_fox_1,
        {
            fox_1_tmem_txt,
            fox_1_pal,
            {
                fox_1_eye1_TA_tex_txt,
                fox_1_eye2_TA_tex_txt,
                fox_1_eye3_TA_tex_txt,
                fox_1_eye4_TA_tex_txt,
                fox_1_eye5_TA_tex_txt,
                fox_1_eye6_TA_tex_txt,
                fox_1_eye7_TA_tex_txt,
                fox_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            36,
            0,
            0,
        },
        0.009499999694526196,
        1,
        0,
        0,
        36,
        0,
        0,
        223,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_339,
        ACTOR_OBJ_BANK_340,
        &cKF_bs_r_rcn_1,
        {
            rcn_1_tmem_txt,
            rcn_1_pal,
            {
                rcn_1_eye1_TA_tex_txt,
                rcn_1_eye2_TA_tex_txt,
                rcn_1_eye3_TA_tex_txt,
                rcn_1_eye4_TA_tex_txt,
                rcn_1_eye5_TA_tex_txt,
                rcn_1_eye6_TA_tex_txt,
                rcn_1_eye7_TA_tex_txt,
                rcn_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            40,
            0,
            0,
        },
        0.010999999940395355,
        1,
        0,
        0,
        35,
        0,
        0,
        219,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_167,
        ACTOR_OBJ_BANK_168,
        &cKF_bs_r_rcc_1,
        {
            rcc_1_tmem_txt,
            rcc_1_pal,
            {
                rcc_1_eye1_TA_tex_txt,
                rcc_1_eye2_TA_tex_txt,
                rcc_1_eye3_TA_tex_txt,
                rcc_1_eye4_TA_tex_txt,
                rcc_1_eye5_TA_tex_txt,
                rcc_1_eye6_TA_tex_txt,
                rcc_1_eye7_TA_tex_txt,
                rcc_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            32,
            0,
            0,
        },
        0.010999999940395355,
        1,
        0,
        0,
        35,
        0,
        0,
        220,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_354,
        ACTOR_OBJ_BANK_355,
        &cKF_bs_r_rcs_1,
        {
            rcs_1_tmem_txt,
            rcs_1_pal,
            {
                rcs_1_eye1_TA_tex_txt,
                rcs_1_eye2_TA_tex_txt,
                rcs_1_eye3_TA_tex_txt,
                rcs_1_eye4_TA_tex_txt,
                rcs_1_eye5_TA_tex_txt,
                rcs_1_eye6_TA_tex_txt,
                rcs_1_eye7_TA_tex_txt,
                rcs_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            16,
            0,
            0,
        },
        0.010999999940395355,
        1,
        0,
        0,
        35,
        0,
        0,
        221,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_178,
        ACTOR_OBJ_BANK_179,
        &cKF_bs_r_rcd_1,
        {
            rcd_1_tmem_txt,
            rcd_1_pal,
            {
                rcd_1_eye1_TA_tex_txt,
                rcd_1_eye2_TA_tex_txt,
                rcd_1_eye3_TA_tex_txt,
                rcd_1_eye4_TA_tex_txt,
                rcd_1_eye5_TA_tex_txt,
                rcd_1_eye6_TA_tex_txt,
                rcd_1_eye7_TA_tex_txt,
                rcd_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            16,
            0,
            0,
        },
        0.010999999940395355,
        1,
        0,
        0,
        35,
        0,
        0,
        222,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        36,
        0,
        0,
        0,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_339,
        ACTOR_OBJ_BANK_340,
        &cKF_bs_r_rcn_1,
        {
            rcn_1_tmem_txt,
            rcn_1_pal,
            {
                rcn_1_eye1_TA_tex_txt,
                rcn_1_eye2_TA_tex_txt,
                rcn_1_eye3_TA_tex_txt,
                rcn_1_eye4_TA_tex_txt,
                rcn_1_eye5_TA_tex_txt,
                rcn_1_eye6_TA_tex_txt,
                rcn_1_eye7_TA_tex_txt,
                rcn_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            40,
            0,
            0,
        },
        0.010999999940395355,
        1,
        0,
        0,
        35,
        0,
        0,
        219,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_167,
        ACTOR_OBJ_BANK_168,
        &cKF_bs_r_rcc_1,
        {
            rcc_1_tmem_txt,
            rcc_1_pal,
            {
                rcc_1_eye1_TA_tex_txt,
                rcc_1_eye2_TA_tex_txt,
                rcc_1_eye3_TA_tex_txt,
                rcc_1_eye4_TA_tex_txt,
                rcc_1_eye5_TA_tex_txt,
                rcc_1_eye6_TA_tex_txt,
                rcc_1_eye7_TA_tex_txt,
                rcc_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            32,
            0,
            0,
        },
        0.010999999940395355,
        1,
        0,
        0,
        35,
        0,
        0,
        220,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_354,
        ACTOR_OBJ_BANK_355,
        &cKF_bs_r_rcs_1,
        {
            rcs_1_tmem_txt,
            rcs_1_pal,
            {
                rcs_1_eye1_TA_tex_txt,
                rcs_1_eye2_TA_tex_txt,
                rcs_1_eye3_TA_tex_txt,
                rcs_1_eye4_TA_tex_txt,
                rcs_1_eye5_TA_tex_txt,
                rcs_1_eye6_TA_tex_txt,
                rcs_1_eye7_TA_tex_txt,
                rcs_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            16,
            0,
            0,
        },
        0.010999999940395355,
        1,
        0,
        0,
        35,
        0,
        0,
        221,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_178,
        ACTOR_OBJ_BANK_179,
        &cKF_bs_r_rcd_1,
        {
            rcd_1_tmem_txt,
            rcd_1_pal,
            {
                rcd_1_eye1_TA_tex_txt,
                rcd_1_eye2_TA_tex_txt,
                rcd_1_eye3_TA_tex_txt,
                rcd_1_eye4_TA_tex_txt,
                rcd_1_eye5_TA_tex_txt,
                rcd_1_eye6_TA_tex_txt,
                rcd_1_eye7_TA_tex_txt,
                rcd_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            16,
            0,
            0,
        },
        0.010999999940395355,
        1,
        0,
        0,
        35,
        0,
        0,
        222,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_86,
        ACTOR_OBJ_BANK_87,
        &cKF_bs_r_bev_1,
        {
            bev_1_tmem_txt,
            bev_1_pal,
            {
                bev_1_eye1_TA_tex_txt,
                bev_1_eye2_TA_tex_txt,
                bev_1_eye3_TA_tex_txt,
                bev_1_eye4_TA_tex_txt,
                bev_1_eye5_TA_tex_txt,
                bev_1_eye6_TA_tex_txt,
                bev_1_eye7_TA_tex_txt,
                bev_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            40,
            0,
            0,
        },
        0.008999999612569809,
        1,
        0,
        0,
        39,
        0,
        0,
        238,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_218,
        ACTOR_OBJ_BANK_219,
        &cKF_bs_r_rcf_1,
        {
            rcf_1_tmem_txt,
            rcf_1_pal,
            {
                rcf_1_eye1_TA_tex_txt,
                rcf_1_eye2_TA_tex_txt,
                rcf_1_eye3_TA_tex_txt,
                rcf_1_eye4_TA_tex_txt,
                rcf_1_eye5_TA_tex_txt,
                rcf_1_eye6_TA_tex_txt,
                rcf_1_eye7_TA_tex_txt,
                rcf_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            16,
            0,
            0,
        },
        0.010999999940395355,
        1,
        0,
        0,
        35,
        0,
        0,
        241,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        0,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_236,
        ACTOR_OBJ_BANK_237,
        &cKF_bs_r_pkn_1,
        {
            pkn_1_tmem_txt,
            pkn_1_pal,
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            0,
            0,
            0,
        },
        0.009999999776482582,
        1,
        0,
        0,
        40,
        0,
        0,
        231,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_236,
        ACTOR_OBJ_BANK_237,
        &cKF_bs_r_pkn_1,
        {
            pkn_1_tmem_txt,
            pkn_1_pal,
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            0,
            0,
            0,
        },
        0.009999999776482582,
        1,
        0,
        0,
        40,
        0,
        0,
        231,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_236,
        ACTOR_OBJ_BANK_237,
        &cKF_bs_r_pkn_1,
        {
            pkn_1_tmem_txt,
            pkn_1_pal,
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            0,
            0,
            0,
        },
        0.009999999776482582,
        1,
        0,
        0,
        40,
        0,
        0,
        231,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_236,
        ACTOR_OBJ_BANK_237,
        &cKF_bs_r_pkn_1,
        {
            pkn_1_tmem_txt,
            pkn_1_pal,
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            0,
            0,
            0,
        },
        0.009999999776482582,
        1,
        0,
        0,
        40,
        0,
        0,
        231,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_236,
        ACTOR_OBJ_BANK_237,
        &cKF_bs_r_pkn_1,
        {
            pkn_1_tmem_txt,
            pkn_1_pal,
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            0,
            0,
            0,
        },
        0.009999999776482582,
        1,
        0,
        0,
        40,
        0,
        0,
        231,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_236,
        ACTOR_OBJ_BANK_237,
        &cKF_bs_r_pkn_1,
        {
            pkn_1_tmem_txt,
            pkn_1_pal,
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            40,
            0,
            0,
        },
        0.009999999776482582,
        1,
        0,
        0,
        35,
        0,
        0,
        231,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_272,
        ACTOR_OBJ_BANK_273,
        &cKF_bs_r_lrc_1,
        {
            lrc_1_tmem_txt,
            lrc_1_pal,
            {
                lrc_1_eye1_TA_tex_txt,
                lrc_1_eye2_TA_tex_txt,
                lrc_1_eye3_TA_tex_txt,
                lrc_1_eye4_TA_tex_txt,
                lrc_1_eye5_TA_tex_txt,
                lrc_1_eye6_TA_tex_txt,
                lrc_1_eye7_TA_tex_txt,
                lrc_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            40,
            0,
            0,
        },
        0.00800000037997961,
        1,
        0,
        0,
        30,
        0,
        0,
        240,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_260,
        ACTOR_OBJ_BANK_261,
        &cKF_bs_r_fob_1,
        {
            fob_1_tmem_txt,
            fob_1_pal,
            {
                fob_1_eye1_TA_tex_txt,
                fob_1_eye2_TA_tex_txt,
                fob_1_eye3_TA_tex_txt,
                fob_1_eye4_TA_tex_txt,
                fob_1_eye5_TA_tex_txt,
                fob_1_eye6_TA_tex_txt,
                fob_1_eye7_TA_tex_txt,
                fob_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            24,
            0,
            0,
        },
        0.009499999694526196,
        1,
        0,
        0,
        36,
        0,
        0,
        242,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_272,
        ACTOR_OBJ_BANK_273,
        &cKF_bs_r_lrc_1,
        {
            lrc_1_tmem_txt,
            lrc_1_pal,
            {
                lrc_1_eye1_TA_tex_txt,
                lrc_1_eye2_TA_tex_txt,
                lrc_1_eye3_TA_tex_txt,
                lrc_1_eye4_TA_tex_txt,
                lrc_1_eye5_TA_tex_txt,
                lrc_1_eye6_TA_tex_txt,
                lrc_1_eye7_TA_tex_txt,
                lrc_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            40,
            0,
            0,
        },
        0.00800000037997961,
        1,
        0,
        0,
        30,
        0,
        0,
        0,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_341,
        ACTOR_OBJ_BANK_342,
        &cKF_bs_r_kab_1,
        {
            kab_1_tmem_txt,
            kab_1_pal,
            {
                kab_1_eye1_TA_tex_txt,
                kab_1_eye2_TA_tex_txt,
                kab_1_eye3_TA_tex_txt,
                kab_1_eye4_TA_tex_txt,
                kab_1_eye5_TA_tex_txt,
                kab_1_eye6_TA_tex_txt,
                kab_1_eye7_TA_tex_txt,
                kab_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            32,
            0,
            0,
        },
        0.009999999776482582,
        1,
        0,
        0,
        43,
        0,
        0,
        227,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_260,
        ACTOR_OBJ_BANK_261,
        &cKF_bs_r_fob_1,
        {
            fob_1_tmem_txt,
            fob_1_pal,
            {
                fob_1_eye1_TA_tex_txt,
                fob_1_eye2_TA_tex_txt,
                fob_1_eye3_TA_tex_txt,
                fob_1_eye4_TA_tex_txt,
                fob_1_eye5_TA_tex_txt,
                fob_1_eye6_TA_tex_txt,
                fob_1_eye7_TA_tex_txt,
                fob_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            24,
            0,
            0,
        },
        0.009499999694526196,
        1,
        0,
        0,
        36,
        0,
        0,
        242,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_218,
        ACTOR_OBJ_BANK_219,
        &cKF_bs_r_rcf_1,
        {
            rcf_1_tmem_txt,
            rcf_1_pal,
            {
                rcf_1_eye1_TA_tex_txt,
                rcf_1_eye2_TA_tex_txt,
                rcf_1_eye3_TA_tex_txt,
                rcf_1_eye4_TA_tex_txt,
                rcf_1_eye5_TA_tex_txt,
                rcf_1_eye6_TA_tex_txt,
                rcf_1_eye7_TA_tex_txt,
                rcf_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            16,
            0,
            0,
        },
        0.010999999940395355,
        1,
        0,
        0,
        35,
        0,
        0,
        241,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_218,
        ACTOR_OBJ_BANK_219,
        &cKF_bs_r_rcf_1,
        {
            rcf_1_tmem_txt,
            rcf_1_pal,
            {
                rcf_1_eye1_TA_tex_txt,
                rcf_1_eye2_TA_tex_txt,
                rcf_1_eye3_TA_tex_txt,
                rcf_1_eye4_TA_tex_txt,
                rcf_1_eye5_TA_tex_txt,
                rcf_1_eye6_TA_tex_txt,
                rcf_1_eye7_TA_tex_txt,
                rcf_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            16,
            0,
            0,
        },
        0.010999999940395355,
        1,
        0,
        0,
        35,
        0,
        0,
        241,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_218,
        ACTOR_OBJ_BANK_219,
        &cKF_bs_r_rcf_1,
        {
            rcf_1_tmem_txt,
            rcf_1_pal,
            {
                rcf_1_eye1_TA_tex_txt,
                rcf_1_eye2_TA_tex_txt,
                rcf_1_eye3_TA_tex_txt,
                rcf_1_eye4_TA_tex_txt,
                rcf_1_eye5_TA_tex_txt,
                rcf_1_eye6_TA_tex_txt,
                rcf_1_eye7_TA_tex_txt,
                rcf_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            16,
            0,
            0,
        },
        0.010999999940395355,
        1,
        0,
        0,
        35,
        0,
        0,
        241,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_234,
        ACTOR_OBJ_BANK_235,
        &cKF_bs_r_bpt_1,
        {
            bpt_1_tmem_txt,
            bpt_1_pal,
            {
                bpt_1_eye1_TA_tex_txt,
                bpt_1_eye2_TA_tex_txt,
                bpt_1_eye3_TA_tex_txt,
                bpt_1_eye4_TA_tex_txt,
                bpt_1_eye5_TA_tex_txt,
                bpt_1_eye6_TA_tex_txt,
                bpt_1_eye7_TA_tex_txt,
                bpt_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            12,
            0,
            0,
        },
        0.009499999694526196,
        1,
        0,
        0,
        40,
        0,
        0,
        243,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_49,
        ACTOR_OBJ_BANK_50,
        &cKF_bs_r_mol_1,
        {
            mol_1_tmem_txt,
            mol_1_pal,
            {
                mol_1_eye1_TA_tex_txt,
                mol_1_eye2_TA_tex_txt,
                mol_1_eye3_TA_tex_txt,
                mol_1_eye4_TA_tex_txt,
                mol_1_eye5_TA_tex_txt,
                mol_1_eye6_TA_tex_txt,
                mol_1_eye7_TA_tex_txt,
                mol_1_eye8_TA_tex_txt,
            },
            {
                mol_1_mouth1_TA_tex_txt,
                mol_1_mouth2_TA_tex_txt,
                mol_1_mouth3_TA_tex_txt,
                mol_1_mouth4_TA_tex_txt,
                mol_1_mouth5_TA_tex_txt,
                mol_1_mouth6_TA_tex_txt,
            },
            64,
            104,
            0,
        },
        0.008999999612569809,
        0,
        0,
        0,
        34,
        0,
        0,
        244,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_398,
        ACTOR_OBJ_BANK_399,
        &cKF_bs_r_plj_1,
        {
            plj_1_tmem_txt,
            plj_1_pal,
            {
                plj_1_eye1_TA_tex_txt,
                plj_1_eye2_TA_tex_txt,
                plj_1_eye3_TA_tex_txt,
                plj_1_eye4_TA_tex_txt,
                plj_1_eye5_TA_tex_txt,
                plj_1_eye6_TA_tex_txt,
                plj_1_eye7_TA_tex_txt,
                plj_1_eye8_TA_tex_txt,
            },
            {
                plj_1_mouth1_TA_tex_txt,
                plj_1_mouth2_TA_tex_txt,
                plj_1_mouth3_TA_tex_txt,
                plj_1_mouth4_TA_tex_txt,
                plj_1_mouth5_TA_tex_txt,
                plj_1_mouth6_TA_tex_txt,
            },
            84,
            52,
            0,
        },
        0.009999999776482582,
        0,
        0,
        0,
        46,
        0,
        0,
        246,
        25,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        36,
        0,
        0,
        237,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_396,
        ACTOR_OBJ_BANK_397,
        &cKF_bs_r_seg_1,
        {
            seg_1_tmem_txt,
            seg_1_pal,
            {
                seg_1_eye1_TA_tex_txt,
                seg_1_eye2_TA_tex_txt,
                seg_1_eye3_TA_tex_txt,
                seg_1_eye4_TA_tex_txt,
                seg_1_eye5_TA_tex_txt,
                seg_1_eye6_TA_tex_txt,
                seg_1_eye7_TA_tex_txt,
                seg_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            48,
            0,
            0,
        },
        0.00800000037997961,
        1,
        0,
        0,
        39,
        0,
        0,
        247,
        23,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_49,
        ACTOR_OBJ_BANK_50,
        &cKF_bs_r_mol_1,
        {
            mol_1_tmem_txt,
            mol_1_pal,
            {
                mol_1_eye1_TA_tex_txt,
                mol_1_eye2_TA_tex_txt,
                mol_1_eye3_TA_tex_txt,
                mol_1_eye4_TA_tex_txt,
                mol_1_eye5_TA_tex_txt,
                mol_1_eye6_TA_tex_txt,
                mol_1_eye7_TA_tex_txt,
                mol_1_eye8_TA_tex_txt,
            },
            {
                mol_1_mouth1_TA_tex_txt,
                mol_1_mouth2_TA_tex_txt,
                mol_1_mouth3_TA_tex_txt,
                mol_1_mouth4_TA_tex_txt,
                mol_1_mouth5_TA_tex_txt,
                mol_1_mouth6_TA_tex_txt,
            },
            64,
            104,
            0,
        },
        0.008999999612569809,
        0,
        0,
        0,
        34,
        0,
        0,
        245,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        36,
        0,
        0,
        0,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_352,
        ACTOR_OBJ_BANK_353,
        &cKF_bs_r_mnk_1,
        {
            mnk_1_tmem_txt,
            mnk_1_pal,
            {
                mnk_1_eye1_TA_tex_txt,
                mnk_1_eye2_TA_tex_txt,
                mnk_1_eye3_TA_tex_txt,
                mnk_1_eye4_TA_tex_txt,
                mnk_1_eye5_TA_tex_txt,
                mnk_1_eye6_TA_tex_txt,
                mnk_1_eye7_TA_tex_txt,
                mnk_1_eye8_TA_tex_txt,
            },
            {
                mnk_1_mouth1_TA_tex_txt,
                mnk_1_mouth2_TA_tex_txt,
                mnk_1_mouth3_TA_tex_txt,
                mnk_1_mouth4_TA_tex_txt,
                mnk_1_mouth5_TA_tex_txt,
                mnk_1_mouth6_TA_tex_txt,
            },
            40,
            0,
            0,
        },
        0.008999999612569809,
        0,
        0,
        0,
        35,
        0,
        0,
        230,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_49,
        ACTOR_OBJ_BANK_50,
        &cKF_bs_r_mol_1,
        {
            mol_1_tmem_txt,
            mol_1_pal,
            {
                mol_1_eye1_TA_tex_txt,
                mol_1_eye2_TA_tex_txt,
                mol_1_eye3_TA_tex_txt,
                mol_1_eye4_TA_tex_txt,
                mol_1_eye5_TA_tex_txt,
                mol_1_eye6_TA_tex_txt,
                mol_1_eye7_TA_tex_txt,
                mol_1_eye8_TA_tex_txt,
            },
            {
                mol_1_mouth1_TA_tex_txt,
                mol_1_mouth2_TA_tex_txt,
                mol_1_mouth3_TA_tex_txt,
                mol_1_mouth4_TA_tex_txt,
                mol_1_mouth5_TA_tex_txt,
                mol_1_mouth6_TA_tex_txt,
            },
            64,
            104,
            0,
        },
        0.008999999612569809,
        0,
        0,
        0,
        34,
        0,
        0,
        245,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_49,
        ACTOR_OBJ_BANK_50,
        &cKF_bs_r_mol_1,
        {
            mol_1_tmem_txt,
            mol_1_pal,
            {
                mol_1_eye1_TA_tex_txt,
                mol_1_eye2_TA_tex_txt,
                mol_1_eye3_TA_tex_txt,
                mol_1_eye4_TA_tex_txt,
                mol_1_eye5_TA_tex_txt,
                mol_1_eye6_TA_tex_txt,
                mol_1_eye7_TA_tex_txt,
                mol_1_eye8_TA_tex_txt,
            },
            {
                mol_1_mouth1_TA_tex_txt,
                mol_1_mouth2_TA_tex_txt,
                mol_1_mouth3_TA_tex_txt,
                mol_1_mouth4_TA_tex_txt,
                mol_1_mouth5_TA_tex_txt,
                mol_1_mouth6_TA_tex_txt,
            },
            64,
            104,
            0,
        },
        0.008999999612569809,
        0,
        0,
        0,
        34,
        0,
        0,
        245,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        0,
        20,
        40,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_49,
        ACTOR_OBJ_BANK_50,
        &cKF_bs_r_mol_1,
        {
            mol_1_tmem_txt,
            mol_1_pal,
            {
                mol_1_eye1_TA_tex_txt,
                mol_1_eye2_TA_tex_txt,
                mol_1_eye3_TA_tex_txt,
                mol_1_eye4_TA_tex_txt,
                mol_1_eye5_TA_tex_txt,
                mol_1_eye6_TA_tex_txt,
                mol_1_eye7_TA_tex_txt,
                mol_1_eye8_TA_tex_txt,
            },
            {
                mol_1_mouth1_TA_tex_txt,
                mol_1_mouth2_TA_tex_txt,
                mol_1_mouth3_TA_tex_txt,
                mol_1_mouth4_TA_tex_txt,
                mol_1_mouth5_TA_tex_txt,
                mol_1_mouth6_TA_tex_txt,
            },
            64,
            104,
            0,
        },
        0.008999999612569809,
        0,
        0,
        0,
        34,
        0,
        0,
        245,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_422,
        ACTOR_OBJ_BANK_423,
        &cKF_bs_r_xsq_1,
        {
            xsq_1_tmem_txt,
            xsq_1_pal,
            {
                xsq_1_eye1_TA_tex_txt,
                xsq_1_eye2_TA_tex_txt,
                xsq_1_eye3_TA_tex_txt,
                xsq_1_eye4_TA_tex_txt,
                xsq_1_eye5_TA_tex_txt,
                xsq_1_eye6_TA_tex_txt,
                xsq_1_eye7_TA_tex_txt,
                xsq_1_eye8_TA_tex_txt,
            },
            {
                xsq_1_mouth1_TA_tex_txt,
                xsq_1_mouth2_TA_tex_txt,
                xsq_1_mouth3_TA_tex_txt,
                xsq_1_mouth4_TA_tex_txt,
                xsq_1_mouth5_TA_tex_txt,
                xsq_1_mouth6_TA_tex_txt,
            },
            72,
            104,
            0,
        },
        0.006800000090152025,
        0,
        0,
        0,
        26,
        0,
        0,
        49,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_401,
        ACTOR_OBJ_BANK_402,
        &cKF_bs_r_owl_1,
        {
            owl_1_tmem_txt,
            owl_1_pal,
            {
                owl_1_eye1_TA_tex_txt,
                owl_1_eye2_TA_tex_txt,
                owl_1_eye3_TA_tex_txt,
                owl_1_eye4_TA_tex_txt,
                owl_1_eye5_TA_tex_txt,
                owl_1_eye6_TA_tex_txt,
                owl_1_eye7_TA_tex_txt,
                owl_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            40,
            0,
            0,
        },
        0.009499999694526196,
        1,
        0,
        0,
        40,
        0,
        0,
        280,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_403,
        ACTOR_OBJ_BANK_404,
        &cKF_bs_r_ttl_1,
        {
            ttl_1_tmem_txt,
            ttl_1_pal,
            {
                ttl_1_eye1_TA_tex_txt,
                ttl_1_eye2_TA_tex_txt,
                ttl_1_eye3_TA_tex_txt,
                ttl_1_eye4_TA_tex_txt,
                ttl_1_eye5_TA_tex_txt,
                ttl_1_eye6_TA_tex_txt,
                ttl_1_eye7_TA_tex_txt,
                ttl_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            88,
            0,
            0,
        },
        0.009999999776482582,
        1,
        0,
        0,
        40,
        0,
        0,
        281,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_10,
        ACTOR_OBJ_BANK_393,
        &cKF_bs_r_gst_1,
        {
            gst_1_tmem_txt,
            gst_1_pal,
            {
                gst_1_eye1_TA_tex_txt,
                gst_1_eye2_TA_tex_txt,
                gst_1_eye3_TA_tex_txt,
                gst_1_eye4_TA_tex_txt,
                gst_1_eye5_TA_tex_txt,
                gst_1_eye6_TA_tex_txt,
                gst_1_eye7_TA_tex_txt,
                gst_1_eye8_TA_tex_txt,
            },
            {
                gst_1_mouth1_TA_tex_txt,
                gst_1_mouth2_TA_tex_txt,
                gst_1_mouth3_TA_tex_txt,
                gst_1_mouth4_TA_tex_txt,
                gst_1_mouth5_TA_tex_txt,
                gst_1_mouth6_TA_tex_txt,
            },
            32,
            0,
            0,
        },
        0.009999999776482582,
        0,
        0,
        0,
        40,
        0,
        0,
        249,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_416,
        ACTOR_OBJ_BANK_417,
        &cKF_bs_r_hgh_1,
        {
            hgh_1_tmem_txt,
            hgh_1_pal,
            {
                hgh_1_eye1_TA_tex_txt,
                hgh_1_eye2_TA_tex_txt,
                hgh_1_eye3_TA_tex_txt,
                hgh_1_eye4_TA_tex_txt,
                hgh_1_eye5_TA_tex_txt,
                hgh_1_eye6_TA_tex_txt,
                hgh_1_eye7_TA_tex_txt,
                hgh_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            88,
            0,
            0,
        },
        0.009999999776482582,
        1,
        0,
        0,
        40,
        0,
        0,
        278,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_418,
        ACTOR_OBJ_BANK_419,
        &cKF_bs_r_hgs_1,
        {
            hgs_1_tmem_txt,
            hgs_1_pal,
            {
                hgs_1_eye1_TA_tex_txt,
                hgs_1_eye2_TA_tex_txt,
                hgs_1_eye3_TA_tex_txt,
                hgs_1_eye4_TA_tex_txt,
                hgs_1_eye5_TA_tex_txt,
                hgs_1_eye6_TA_tex_txt,
                hgs_1_eye7_TA_tex_txt,
                hgs_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            88,
            0,
            0,
        },
        0.009999999776482582,
        1,
        0,
        0,
        40,
        0,
        0,
        279,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_414,
        ACTOR_OBJ_BANK_415,
        &cKF_bs_r_wip_1,
        {
            wip_1_tmem_txt,
            wip_1_pal,
            {
                wip_1_eye1_TA_tex_txt,
                wip_1_eye2_TA_tex_txt,
                wip_1_eye3_TA_tex_txt,
                wip_1_eye4_TA_tex_txt,
                wip_1_eye5_TA_tex_txt,
                wip_1_eye6_TA_tex_txt,
                wip_1_eye7_TA_tex_txt,
                wip_1_eye8_TA_tex_txt,
            },
            {
                wip_1_mouth1_TA_tex_txt,
                wip_1_mouth2_TA_tex_txt,
                wip_1_mouth3_TA_tex_txt,
                wip_1_mouth4_TA_tex_txt,
                wip_1_mouth5_TA_tex_txt,
                wip_1_mouth6_TA_tex_txt,
            },
            88,
            0,
            0,
        },
        0.009999999776482582,
        0,
        0,
        0,
        40,
        0,
        0,
        282,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_403,
        ACTOR_OBJ_BANK_404,
        &cKF_bs_r_ttl_1,
        {
            ttl_1_tmem_txt,
            ttl_1_pal,
            {
                ttl_1_eye1_TA_tex_txt,
                ttl_1_eye2_TA_tex_txt,
                ttl_1_eye3_TA_tex_txt,
                ttl_1_eye4_TA_tex_txt,
                ttl_1_eye5_TA_tex_txt,
                ttl_1_eye6_TA_tex_txt,
                ttl_1_eye7_TA_tex_txt,
                ttl_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            88,
            0,
            0,
        },
        0.009999999776482582,
        1,
        0,
        0,
        40,
        0,
        0,
        281,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_424,
        ACTOR_OBJ_BANK_425,
        &cKF_bs_r_mka_1,
        {
            mka_1_tmem_txt,
            mka_1_pal,
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            88,
            0,
            0,
        },
        0.009999999776482582,
        0,
        0,
        0,
        40,
        0,
        0,
        284,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_424,
        ACTOR_OBJ_BANK_425,
        &cKF_bs_r_mka_1,
        {
            mka_1_tmem_txt,
            mka_1_pal,
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            88,
            0,
            0,
        },
        0.009999999776482582,
        0,
        0,
        0,
        40,
        0,
        0,
        284,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_403,
        ACTOR_OBJ_BANK_404,
        &cKF_bs_r_ttl_1,
        {
            ttl_1_tmem_txt,
            ttl_1_pal,
            {
                ttl_1_eye1_TA_tex_txt,
                ttl_1_eye2_TA_tex_txt,
                ttl_1_eye3_TA_tex_txt,
                ttl_1_eye4_TA_tex_txt,
                ttl_1_eye5_TA_tex_txt,
                ttl_1_eye6_TA_tex_txt,
                ttl_1_eye7_TA_tex_txt,
                ttl_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            88,
            0,
            0,
        },
        0.009999999776482582,
        1,
        0,
        0,
        40,
        0,
        0,
        281,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_236,
        ACTOR_OBJ_BANK_237,
        &cKF_bs_r_pkn_1,
        {
            pkn_1_tmem_txt,
            pkn_1_pal,
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            0,
            0,
            0,
        },
        0.009999999776482582,
        1,
        0,
        0,
        40,
        0,
        0,
        231,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_352,
        ACTOR_OBJ_BANK_353,
        &cKF_bs_r_mnk_1,
        {
            mnk_1_tmem_txt,
            mnk_1_pal,
            {
                mnk_1_eye1_TA_tex_txt,
                mnk_1_eye2_TA_tex_txt,
                mnk_1_eye3_TA_tex_txt,
                mnk_1_eye4_TA_tex_txt,
                mnk_1_eye5_TA_tex_txt,
                mnk_1_eye6_TA_tex_txt,
                mnk_1_eye7_TA_tex_txt,
                mnk_1_eye8_TA_tex_txt,
            },
            {
                mnk_1_mouth1_TA_tex_txt,
                mnk_1_mouth2_TA_tex_txt,
                mnk_1_mouth3_TA_tex_txt,
                mnk_1_mouth4_TA_tex_txt,
                mnk_1_mouth5_TA_tex_txt,
                mnk_1_mouth6_TA_tex_txt,
            },
            40,
            0,
            0,
        },
        0.008999999612569809,
        0,
        0,
        0,
        35,
        0,
        0,
        230,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_396,
        ACTOR_OBJ_BANK_397,
        &cKF_bs_r_seg_1,
        {
            seg_1_tmem_txt,
            seg_1_pal,
            {
                seg_1_eye1_TA_tex_txt,
                seg_1_eye2_TA_tex_txt,
                seg_1_eye3_TA_tex_txt,
                seg_1_eye4_TA_tex_txt,
                seg_1_eye5_TA_tex_txt,
                seg_1_eye6_TA_tex_txt,
                seg_1_eye7_TA_tex_txt,
                seg_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            48,
            0,
            0,
        },
        0.00800000037997961,
        1,
        0,
        0,
        39,
        0,
        0,
        247,
        23,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_49,
        ACTOR_OBJ_BANK_50,
        &cKF_bs_r_mol_1,
        {
            mol_1_tmem_txt,
            mol_1_pal,
            {
                mol_1_eye1_TA_tex_txt,
                mol_1_eye2_TA_tex_txt,
                mol_1_eye3_TA_tex_txt,
                mol_1_eye4_TA_tex_txt,
                mol_1_eye5_TA_tex_txt,
                mol_1_eye6_TA_tex_txt,
                mol_1_eye7_TA_tex_txt,
                mol_1_eye8_TA_tex_txt,
            },
            {
                mol_1_mouth1_TA_tex_txt,
                mol_1_mouth2_TA_tex_txt,
                mol_1_mouth3_TA_tex_txt,
                mol_1_mouth4_TA_tex_txt,
                mol_1_mouth5_TA_tex_txt,
                mol_1_mouth6_TA_tex_txt,
            },
            64,
            104,
            0,
        },
        0.008999999612569809,
        0,
        0,
        0,
        34,
        0,
        0,
        244,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_49,
        ACTOR_OBJ_BANK_50,
        &cKF_bs_r_mol_1,
        {
            mol_1_tmem_txt,
            mol_1_pal,
            {
                mol_1_eye1_TA_tex_txt,
                mol_1_eye2_TA_tex_txt,
                mol_1_eye3_TA_tex_txt,
                mol_1_eye4_TA_tex_txt,
                mol_1_eye5_TA_tex_txt,
                mol_1_eye6_TA_tex_txt,
                mol_1_eye7_TA_tex_txt,
                mol_1_eye8_TA_tex_txt,
            },
            {
                mol_1_mouth1_TA_tex_txt,
                mol_1_mouth2_TA_tex_txt,
                mol_1_mouth3_TA_tex_txt,
                mol_1_mouth4_TA_tex_txt,
                mol_1_mouth5_TA_tex_txt,
                mol_1_mouth6_TA_tex_txt,
            },
            64,
            104,
            0,
        },
        0.008999999612569809,
        0,
        0,
        0,
        34,
        0,
        0,
        244,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_460,
        ACTOR_OBJ_BANK_461,
        &cKF_bs_r_mob_1,
        {
            mob_1_tmem_txt,
            mob_1_pal,
            {
                mob_1_eye1_TA_tex_txt,
                mob_1_eye2_TA_tex_txt,
                mob_1_eye3_TA_tex_txt,
                mob_1_eye4_TA_tex_txt,
                mob_1_eye5_TA_tex_txt,
                mob_1_eye6_TA_tex_txt,
                mob_1_eye7_TA_tex_txt,
                mob_1_eye8_TA_tex_txt,
            },
            {
                mob_1_mouth1_TA_tex_txt,
                mob_1_mouth2_TA_tex_txt,
                mob_1_mouth3_TA_tex_txt,
                mob_1_mouth4_TA_tex_txt,
                mob_1_mouth5_TA_tex_txt,
                mob_1_mouth6_TA_tex_txt,
            },
            64,
            104,
            0,
        },
        0.009999999776482582,
        0,
        0,
        0,
        34,
        0,
        0,
        244,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_403,
        ACTOR_OBJ_BANK_404,
        &cKF_bs_r_ttl_1,
        {
            ttl_1_tmem_txt,
            ttl_1_pal,
            {
                ttl_1_eye1_TA_tex_txt,
                ttl_1_eye2_TA_tex_txt,
                ttl_1_eye3_TA_tex_txt,
                ttl_1_eye4_TA_tex_txt,
                ttl_1_eye5_TA_tex_txt,
                ttl_1_eye6_TA_tex_txt,
                ttl_1_eye7_TA_tex_txt,
                ttl_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            88,
            0,
            0,
        },
        0.009999999776482582,
        1,
        0,
        0,
        40,
        0,
        0,
        281,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_49,
        ACTOR_OBJ_BANK_50,
        &cKF_bs_r_mol_1,
        {
            mol_1_tmem_txt,
            mol_1_pal,
            {
                mol_1_eye1_TA_tex_txt,
                mol_1_eye2_TA_tex_txt,
                mol_1_eye3_TA_tex_txt,
                mol_1_eye4_TA_tex_txt,
                mol_1_eye5_TA_tex_txt,
                mol_1_eye6_TA_tex_txt,
                mol_1_eye7_TA_tex_txt,
                mol_1_eye8_TA_tex_txt,
            },
            {
                mol_1_mouth1_TA_tex_txt,
                mol_1_mouth2_TA_tex_txt,
                mol_1_mouth3_TA_tex_txt,
                mol_1_mouth4_TA_tex_txt,
                mol_1_mouth5_TA_tex_txt,
                mol_1_mouth6_TA_tex_txt,
            },
            64,
            104,
            0,
        },
        0.008999999612569809,
        0,
        0,
        0,
        34,
        0,
        0,
        244,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_462,
        ACTOR_OBJ_BANK_463,
        &cKF_bs_r_mos_1,
        {
            mos_1_tmem_txt,
            mos_1_pal,
            {
                mos_1_eye1_TA_tex_txt,
                mos_1_eye2_TA_tex_txt,
                mos_1_eye3_TA_tex_txt,
                mos_1_eye4_TA_tex_txt,
                mos_1_eye5_TA_tex_txt,
                mos_1_eye6_TA_tex_txt,
                mos_1_eye7_TA_tex_txt,
                mos_1_eye8_TA_tex_txt,
            },
            {
                mos_1_mouth1_TA_tex_txt,
                mos_1_mouth2_TA_tex_txt,
                mos_1_mouth3_TA_tex_txt,
                mos_1_mouth4_TA_tex_txt,
                mos_1_mouth5_TA_tex_txt,
                mos_1_mouth6_TA_tex_txt,
            },
            64,
            104,
            0,
        },
        0.009999999776482582,
        0,
        0,
        0,
        34,
        0,
        0,
        244,
        20,
        35,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_403,
        ACTOR_OBJ_BANK_404,
        &cKF_bs_r_ttl_1,
        {
            ttl_1_tmem_txt,
            ttl_1_pal,
            {
                ttl_1_eye1_TA_tex_txt,
                ttl_1_eye2_TA_tex_txt,
                ttl_1_eye3_TA_tex_txt,
                ttl_1_eye4_TA_tex_txt,
                ttl_1_eye5_TA_tex_txt,
                ttl_1_eye6_TA_tex_txt,
                ttl_1_eye7_TA_tex_txt,
                ttl_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            88,
            0,
            0,
        },
        0.009999999776482582,
        1,
        0,
        0,
        40,
        0,
        0,
        281,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_464,
        ACTOR_OBJ_BANK_465,
        &cKF_bs_r_tuk_1,
        {
            tuk_1_tmem_txt,
            tuk_1_pal,
            {
                tuk_1_eye1_TA_tex_txt,
                tuk_1_eye2_TA_tex_txt,
                tuk_1_eye3_TA_tex_txt,
                tuk_1_eye4_TA_tex_txt,
                tuk_1_eye5_TA_tex_txt,
                tuk_1_eye6_TA_tex_txt,
                tuk_1_eye7_TA_tex_txt,
                tuk_1_eye8_TA_tex_txt,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            84,
            0,
            0,
        },
        0.012000000104308128,
        1,
        0,
        0,
        38,
        0,
        0,
        233,
        20,
        45,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_466,
        ACTOR_OBJ_BANK_467,
        &cKF_bs_r_hem_1,
        {
            hem_1_tmem_txt,
            hem_1_pal,
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            {
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
                NULL,
            },
            88,
            0,
            0,
        },
        0.007000000216066837,
        0,
        0,
        0,
        40,
        0,
        0,
        284,
        20,
        50,
        -1,
        -1,
    },
    {
        ACTOR_OBJ_BANK_360,
        ACTOR_OBJ_BANK_361,
        &cKF_bs_r_end_1,
        {
            end_1_tmem_txt,
            end_1_pal,
            {
                end_1_eye1_TA_tex_txt,
                end_1_eye2_TA_tex_txt,
                end_1_eye3_TA_tex_txt,
                end_1_eye4_TA_tex_txt,
                end_1_eye5_TA_tex_txt,
                end_1_eye6_TA_tex_txt,
                end_1_eye7_TA_tex_txt,
                end_1_eye8_TA_tex_txt,
            },
            {
                end_1_mouth1_TA_tex_txt,
                end_1_mouth2_TA_tex_txt,
                end_1_mouth3_TA_tex_txt,
                end_1_mouth4_TA_tex_txt,
                end_1_mouth5_TA_tex_txt,
                end_1_mouth6_TA_tex_txt,
            },
            0,
            32,
            0,
        },
        0.010999999940395355,
        0,
        0,
        0,
        40,
        0,
        0,
        237,
        20,
        30,
        -1,
        -1,
    },
};
