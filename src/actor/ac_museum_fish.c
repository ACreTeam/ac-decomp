#include "ac_museum_fish.h"
#include "m_kankyo.h"
#include "m_play.h"
#include "m_demo.h"
#include "m_name_table.h"
#include "m_item_name.h"
#include "m_msg.h"
#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_player_lib.h"
#include "m_debug_mode.h"
#include "libforest/gbi_extensions.h"

// found useful macros
#define MY_MAX(a, b) (((a) >= (b)) ? (a) : (b))
#define MY_CLAMP(v, l, h) MIN(MY_MAX((l), (v)), (h))
#define ARRAY_LEN(a) (sizeof(a) / sizeof(*a))

// delete this stuff later
typedef Mtx;
typedef Gfx;

// extern data
// clang-format off
extern cKF_Skeleton_R_c
    cKF_bs_r_act_mus_funa_a1,
    cKF_bs_r_act_mus_hera_a1,
    cKF_bs_r_act_mus_koi_a1,
    cKF_bs_r_act_mus_nisiki_a1,
    cKF_bs_r_act_mus_namazu_a1,
    cKF_bs_r_act_mus_bass_a1,
    cKF_bs_r_act_mus_bassm_a1,
    cKF_bs_r_act_mus_bassl_a1,
    cKF_bs_r_act_mus_gill_a1,
    cKF_bs_r_act_mus_onamazu_a1,
    cKF_bs_r_act_mus_raigyo_a1,
    cKF_bs_r_act_mus_nigoi_a1,
    cKF_bs_r_act_mus_ugui_a1,
    cKF_bs_r_act_mus_oikawa_a1,
    cKF_bs_r_act_mus_tanago_a1,
    cKF_bs_r_act_mus_dojyo_a1,
    cKF_bs_r_act_mus_wakasa_a1,
    cKF_bs_r_act_mus_ayu_a1,
    cKF_bs_r_act_mus_yamame_a1,
    cKF_bs_r_act_mus_iwana_a1,
    cKF_bs_r_act_mus_niji_a1,
    cKF_bs_r_act_mus_ito_a1,
    cKF_bs_r_act_mus_sake_a1,
    cKF_bs_r_act_mus_kingyo_a1,
    cKF_bs_r_act_mus_pirania_a1,
    cKF_bs_r_act_mus_aroana_a1,
    cKF_bs_r_act_mus_unagi_a1,
    cKF_bs_r_act_mus_donko_a1,
    cKF_bs_r_act_mus_angel_a1,
    cKF_bs_r_act_mus_gupi_a1,
    cKF_bs_r_act_mus_demekin_a1,
    cKF_bs_r_act_mus_kaseki_a1,
    cKF_bs_r_act_mus_zari,
    cKF_bs_r_act_mus_kaeru_a1,
    cKF_bs_r_act_mus_medaka_a1,
    cKF_bs_r_act_mus_suzuki_a1,
    cKF_bs_r_act_mus_tai_a1,
    cKF_bs_r_act_mus_isidai_a1,
    cKF_bs_r_act_mus_pira_a1;

extern cKF_Animation_R_c
    cKF_ba_r_act_mus_funa_a1,
    cKF_ba_r_act_mus_hera_a1,
    cKF_ba_r_act_mus_koi_a1,
    cKF_ba_r_act_mus_nisiki_a1,
    cKF_ba_r_act_mus_namazu_a1,
    cKF_ba_r_act_mus_bass_a1,
    cKF_ba_r_act_mus_bassm_a1,
    cKF_ba_r_act_mus_bassl_a1,
    cKF_ba_r_act_mus_gill_a1,
    cKF_ba_r_act_mus_onamazu_a1,
    cKF_ba_r_act_mus_raigyo_a1,
    cKF_ba_r_act_mus_nigoi_a1,
    cKF_ba_r_act_mus_ugui_a1,
    cKF_ba_r_act_mus_oikawa_a1,
    cKF_ba_r_act_mus_tanago_a1,
    cKF_ba_r_act_mus_dojyo_a1,
    cKF_ba_r_act_mus_wakasa_a1,
    cKF_ba_r_act_mus_ayu_a1,
    cKF_ba_r_act_mus_yamame_a1,
    cKF_ba_r_act_mus_iwana_a1,
    cKF_ba_r_act_mus_niji_a1,
    cKF_ba_r_act_mus_ito_a1,
    cKF_ba_r_act_mus_sake_a1,
    cKF_ba_r_act_mus_kingyo_a1,
    cKF_ba_r_act_mus_pirania_a1,
    cKF_ba_r_act_mus_aroana_a1,
    cKF_ba_r_act_mus_unagi_a1,
    cKF_ba_r_act_mus_donko_a1,
    cKF_ba_r_act_mus_angel_a1,
    cKF_ba_r_act_mus_gupi_a1,
    cKF_ba_r_act_mus_demekin_a1,
    cKF_ba_r_act_mus_kaseki_a1,
    cKF_ba_r_act_mus_zari,
    cKF_ba_r_act_mus_kaeru_a1,
    cKF_ba_r_act_mus_medaka_a1,
    cKF_ba_r_act_mus_suzuki_a1,
    cKF_ba_r_act_mus_tai_a1,
    cKF_ba_r_act_mus_isidai_a1,
    cKF_ba_r_act_mus_pira_a1;
    
extern cKF_Skeleton_R_c
    cKF_bs_r_obj_museum5_kusa1,
    cKF_bs_r_obj_museum5_kusa2,
    cKF_bs_r_obj_museum5_kusa3;

extern cKF_Animation_R_c
    cKF_ba_r_obj_museum5_kusa1,
    cKF_ba_r_obj_museum5_kusa2,
    cKF_ba_r_obj_museum5_kusa3;

// data

MUSEUM_FISH_ACTOR* MF_Control_Actor;

/*  Init stuff  */
ACTOR_PROFILE Museum_Fish_Profile = {
    mAc_PROFILE_MUSEUM_FISH,
    ACTOR_PART_BG,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_407,
    sizeof(MUSEUM_FISH_ACTOR),
    Museum_Fish_Actor_ct,
    Museum_Fish_Actor_dt,
    Museum_Fish_Actor_move,
    Museum_Fish_Actor_draw,
    NULL
};

xyz_t suisou_pos[5] = { 
    { 220.0f, 40.0f, 220.0f }, 
    { 420.0f, 40.0f, 220.0f }, 
    { 220.0f, 40.0f, 460.0f }, 
    { 420.0f, 40.0f, 460.0f }, 
    { 320.0f, 40.0f,  20.0f } 
};

int kusa_group_tbl[14] = { 0, 2, 1, 3, 3, 4, 4, 4, 4, 4, 0, 2, 1, 3 };

xyz_t kusa_pos[14] = {
    { 179.0f, 40.0f, 170.0f },
    { 253.0f, 40.0f, 495.0f },
    { 376.0f, 40.0f, 260.0f },
    { 397.0f, 40.0f, 412.0f },
    { 467.0f, 40.0f, 432.0f },
    { 141.0f, 40.0f, -18.0f },
    { 206.0f, 40.0f, -25.0f },
    { 346.0f, 40.0f, -38.0f },
    { 473.0f, 40.0f, -29.0f },
    { 495.0f, 40.0f, -21.0f },
    { 210.0f, 40.0f, 215.0f },
    { 266.0f, 40.0f, 507.0f },
    { 393.0f, 40.0f, 270.0f },
    { 415.0f, 40.0f, 415.0f }
};

xyz_t hasu_pos = { 420, 0, 220 };

xyz_t suisou_awa_pos[20] = {
    { 150.0f, 60.0f, -12.0f },
    { 192.0f, 60.0f, -20.0f },
    { 216.0f, 60.0f,  -4.0f }, 
    { 300.0f, 60.0f, -42.0f },
    { 332.0f, 60.0f, -28.0f },
    { 356.0f, 60.0f, -46.0f },
    { 416.0f, 60.0f, -28.0f },
    { 456.0f, 60.0f,  20.0f }, 
    { 190.0f, 60.0f, 173.0f },
    { 196.0f, 60.0f, 186.0f },
    { 232.0f, 60.0f, 178.0f },
    { 372.0f, 60.0f, 254.0f },
    { 388.0f, 60.0f, 270.0f },
    { 434.0f, 60.0f, 173.0f },
    { 180.0f, 60.0f, 408.0f },
    { 256.0f, 60.0f, 512.0f },
    { 270.0f, 60.0f, 500.0f },
    { 406.0f, 60.0f, 414.0f },
    { 458.0f, 60.0f, 424.0f },
    { 447.0f, 60.0f, 442.0f }
};

s16 suisou_awa_group[20] = { 
    4, 4, 4, 4, 4, 
    4, 4, 4, 0, 0, 
    0, 1, 1, 1, 2, 
    2, 2, 3, 3, 3 
};

cKF_Skeleton_R_c* mfish_model_tbl[40] = {
/* CRUCIAN_CARP     */ &cKF_bs_r_act_mus_funa_a1,
/* BROOK_TROUT      */ &cKF_bs_r_act_mus_hera_a1,
/* CARP             */ &cKF_bs_r_act_mus_koi_a1,
/* KOI              */ &cKF_bs_r_act_mus_nisiki_a1,
/* CATFISH          */ &cKF_bs_r_act_mus_namazu_a1,
/* SMALL_BASS       */ &cKF_bs_r_act_mus_bass_a1,
/* BASS             */ &cKF_bs_r_act_mus_bassm_a1,
/* LARGE_BASS       */ &cKF_bs_r_act_mus_bassl_a1,
/* BLUEGILL         */ &cKF_bs_r_act_mus_gill_a1,
/* GIANT_CATFISH    */ &cKF_bs_r_act_mus_onamazu_a1,
/* GIANT_SNAKEHEAD  */ &cKF_bs_r_act_mus_raigyo_a1,
/* BARBEL_STEED     */ &cKF_bs_r_act_mus_nigoi_a1,
/* DACE             */ &cKF_bs_r_act_mus_ugui_a1,
/* PALE_CHUB        */ &cKF_bs_r_act_mus_oikawa_a1,
/* BITTERLING       */ &cKF_bs_r_act_mus_tanago_a1,
/* LOACH            */ &cKF_bs_r_act_mus_dojyo_a1,
/* POND_SMELT       */ &cKF_bs_r_act_mus_wakasa_a1,
/* SWEETFISH        */ &cKF_bs_r_act_mus_ayu_a1,
/* CHERRY_SALMON    */ &cKF_bs_r_act_mus_yamame_a1,
/* LARGE_CHAR       */ &cKF_bs_r_act_mus_iwana_a1,
/* RAINBOW_TROUT    */ &cKF_bs_r_act_mus_niji_a1,
/* STRINGFISH       */ &cKF_bs_r_act_mus_ito_a1,
/* SALMON           */ &cKF_bs_r_act_mus_sake_a1,
/* GOLDFISH         */ &cKF_bs_r_act_mus_kingyo_a1,
/* PIRANHA          */ &cKF_bs_r_act_mus_pirania_a1,
/* AROWANA          */ &cKF_bs_r_act_mus_aroana_a1,
/* EEL              */ &cKF_bs_r_act_mus_unagi_a1,
/* FRESHWATER_GOBY  */ &cKF_bs_r_act_mus_donko_a1,
/* ANGELFISH        */ &cKF_bs_r_act_mus_angel_a1,
/* GUPPY            */ &cKF_bs_r_act_mus_gupi_a1,
/* POPEYED_GOLDFISH */ &cKF_bs_r_act_mus_demekin_a1,
/* COELACANTH       */ &cKF_bs_r_act_mus_kaseki_a1,
/* CRAWFISH         */ &cKF_bs_r_act_mus_zari,
/* FROG             */ &cKF_bs_r_act_mus_kaeru_a1,
/* KILLIFISH        */ &cKF_bs_r_act_mus_medaka_a1,
/* JELLYFISH        */ NULL,
/* SEA_BASS         */ &cKF_bs_r_act_mus_suzuki_a1,
/* RED_SNAPPER      */ &cKF_bs_r_act_mus_tai_a1,
/* BARRED_KNIFEJAW  */ &cKF_bs_r_act_mus_isidai_a1,
/* ARAPAIMA         */ &cKF_bs_r_act_mus_pira_a1
};

cKF_Animation_R_c* mfish_anime_init_tbl[40] = {
/* CRUCIAN_CARP     */ &cKF_ba_r_act_mus_funa_a1,
/* BROOK_TROUT      */ &cKF_ba_r_act_mus_hera_a1,
/* CARP             */ &cKF_ba_r_act_mus_koi_a1,
/* KOI              */ &cKF_ba_r_act_mus_nisiki_a1,
/* CATFISH          */ &cKF_ba_r_act_mus_namazu_a1,
/* SMALL_BASS       */ &cKF_ba_r_act_mus_bass_a1,
/* BASS             */ &cKF_ba_r_act_mus_bassm_a1,
/* LARGE_BASS       */ &cKF_ba_r_act_mus_bassl_a1,
/* BLUEGILL         */ &cKF_ba_r_act_mus_gill_a1,
/* GIANT_CATFISH    */ &cKF_ba_r_act_mus_onamazu_a1,
/* GIANT_SNAKEHEAD  */ &cKF_ba_r_act_mus_raigyo_a1,
/* BARBEL_STEED     */ &cKF_ba_r_act_mus_nigoi_a1,
/* DACE             */ &cKF_ba_r_act_mus_ugui_a1,
/* PALE_CHUB        */ &cKF_ba_r_act_mus_oikawa_a1,
/* BITTERLING       */ &cKF_ba_r_act_mus_tanago_a1,
/* LOACH            */ &cKF_ba_r_act_mus_dojyo_a1,
/* POND_SMELT       */ &cKF_ba_r_act_mus_wakasa_a1,
/* SWEETFISH        */ &cKF_ba_r_act_mus_ayu_a1,
/* CHERRY_SALMON    */ &cKF_ba_r_act_mus_yamame_a1,
/* LARGE_CHAR       */ &cKF_ba_r_act_mus_iwana_a1,
/* RAINBOW_TROUT    */ &cKF_ba_r_act_mus_niji_a1,
/* STRINGFISH       */ &cKF_ba_r_act_mus_ito_a1,
/* SALMON           */ &cKF_ba_r_act_mus_sake_a1,
/* GOLDFISH         */ &cKF_ba_r_act_mus_kingyo_a1,
/* PIRANHA          */ &cKF_ba_r_act_mus_pirania_a1,
/* AROWANA          */ &cKF_ba_r_act_mus_aroana_a1,
/* EEL              */ &cKF_ba_r_act_mus_unagi_a1,
/* FRESHWATER_GOBY  */ &cKF_ba_r_act_mus_donko_a1,
/* ANGELFISH        */ &cKF_ba_r_act_mus_angel_a1,
/* GUPPY            */ &cKF_ba_r_act_mus_gupi_a1,
/* POPEYED_GOLDFISH */ &cKF_ba_r_act_mus_demekin_a1,
/* COELACANTH       */ &cKF_ba_r_act_mus_kaseki_a1,
/* CRAWFISH         */ &cKF_ba_r_act_mus_zari,
/* FROG             */ &cKF_ba_r_act_mus_kaeru_a1,
/* KILLIFISH        */ &cKF_ba_r_act_mus_medaka_a1,
/* JELLYFISH        */ NULL,
/* SEA_BASS         */ &cKF_ba_r_act_mus_suzuki_a1,
/* RED_SNAPPER      */ &cKF_ba_r_act_mus_tai_a1,
/* BARRED_KNIFEJAW  */ &cKF_ba_r_act_mus_isidai_a1,
/* ARAPAIMA         */ &cKF_ba_r_act_mus_pira_a1
};

MUSEUM_FISH_INIT_DATA mfish_init_data[40] = {
/* CRUCIAN_CARP     */ { 0.0100f, 3.8f,  7.5f,  74.0f,  0.400f, 0.450f, 0.98995f,    0.2f, 0.40f,  -3.5f,  -6.0f, 120,  120, DEG2SHORT_ANGLE(70) },
/* BROOK_TROUT      */ { 0.0100f, 4.6f,  7.0f,  78.0f,  0.400f, 0.600f, 0.98995f,    0.2f, 0.40f,  -3.5f,  -6.0f, 100,  160, DEG2SHORT_ANGLE(70) },
/* CARP             */ { 0.0100f, 6.0f, 10.6f,  80.0f,  0.350f, 0.300f, 0.98995f,    0.2f, 0.60f,  -5.0f,  -9.0f, 100,  150, DEG2SHORT_ANGLE(90) },
/* KOI              */ { 0.0100f, 6.0f, 10.7f,  85.0f,  0.350f, 0.300f, 0.98995f,    0.2f, 0.60f,  -5.0f,  -9.0f, 100,  120, DEG2SHORT_ANGLE(90) },
/* CATFISH          */ { 0.0110f, 6.0f, 13.6f,  63.0f,  0.050f, 0.075f, 0.995f,      0.4f, 0.85f,  -2.5f, -10.0f, 600,  900, DEG2SHORT_ANGLE(60) },
/* SMALL_BASS       */ { 0.0110f, 3.0f,  8.0f,  85.0f,  0.700f, 0.500f, 0.97468f,    0.2f, 0.30f,  -4.0f,  -6.0f, 100,  100, DEG2SHORT_ANGLE(70) },
/* BASS             */ { 0.0110f, 4.7f,  9.8f,  92.0f,  0.700f, 0.500f, 0.97468f,    0.2f, 0.60f,  -5.0f,  -8.0f, 150,  110, DEG2SHORT_ANGLE(70) },
/* LARGE_BASS       */ { 0.0110f, 5.5f, 12.0f,  90.0f,  0.600f, 0.500f, 0.97468f,    0.2f, 0.80f,  -5.5f, -10.0f, 160,  120, DEG2SHORT_ANGLE(70) },
/* BLUEGILL         */ { 0.0100f, 4.3f,  6.1f,  95.0f,  0.700f, 0.500f, 0.97468f,    0.2f, 0.30f,  -3.5f,  -5.0f,  80,   80, DEG2SHORT_ANGLE(70) },
/* GIANT_CATFISH    */ { 0.0120f, 7.6f, 19.4f,  65.0f,  0.075f, 0.150f, 0.995f,      0.4f, 0.95f,  -6.0f, -18.0f, 720, 1000, DEG2SHORT_ANGLE(60) },
/* GIANT_SNAKEHEAD  */ { 0.0120f, 9.6f, 20.8f,  65.0f,  0.050f, 0.100f, 0.98488998f, 0.4f, 0.95f, -13.0f, -19.0f, 240,  480, DEG2SHORT_ANGLE(90) },
/* BARBEL_STEED     */ { 0.0100f, 4.8f, 10.5f, 102.0f,  0.350f, 0.300f, 0.98995f,    0.2f, 0.70f,  -3.5f,  -9.0f, 150,  120, DEG2SHORT_ANGLE(70) },
/* DACE             */ { 0.0100f, 3.0f, 10.6f,  75.0f,  0.750f, 1.500f, 0.94867998f, 0.2f, 0.60f,  -4.5f,  -8.0f, 480,  150, DEG2SHORT_ANGLE(45) },
/* PALE_CHUB        */ { 0.0100f, 2.5f,  7.0f,  90.0f,  0.050f, 0.475f, 0.94867998f, 0.4f, 0.30f,  -3.5f,  -6.0f, 240,  200, DEG2SHORT_ANGLE(50) },
/* BITTERLING       */ { 0.0100f, 3.5f,  6.0f,  76.0f,  0.350f, 0.400f, 0.98995f,    0.4f, 0.40f,  -3.0f,  -6.0f, 100,  120, DEG2SHORT_ANGLE(45) },
/* LOACH            */ { 0.0100f, 4.0f,  6.4f,  65.0f,  0.100f, 0.150f, 0.89442998f, 0.4f, 0.20f,  -2.0f,  -6.0f, 240,  240, DEG2SHORT_ANGLE(50) },
/* POND_SMELT       */ { 0.0100f, 2.0f,  6.0f,  96.0f,  0.100f, 0.450f, 0.92194998f, 0.2f, 0.10f,  -3.5f,  -6.0f, 300,  120, DEG2SHORT_ANGLE(50) },
/* SWEETFISH        */ { 0.0100f, 3.0f,  9.8f,  75.0f,  1.000f, 1.500f, 0.94867998f, 0.2f, 0.50f,  -3.5f,  -7.5f, 480,  120, DEG2SHORT_ANGLE(45) },
/* CHERRY_SALMON    */ { 0.0100f, 3.5f,  9.3f,  85.0f,  0.750f, 1.000f, 0.94867998f, 0.2f, 0.50f,  -3.0f,  -8.0f, 540,  120, DEG2SHORT_ANGLE(45) },
/* LARGE_CHAR       */ { 0.0100f, 2.5f, 10.6f,  80.0f,  0.750f, 1.000f, 0.94867998f, 0.2f, 0.70f,  -3.0f,  -9.0f, 600,  140, DEG2SHORT_ANGLE(70) },
/* RAINBOW_TROUT    */ { 0.0100f, 2.5f,  8.8f,  80.0f,  0.500f, 1.000f, 0.94867998f, 0.2f, 0.50f,  -4.0f,  -7.0f, 660,  160, DEG2SHORT_ANGLE(45) },
/* STRINGFISH       */ { 0.0120f, 6.1f, 19.8f,  75.0f,  0.050f, 0.100f, 0.98488998f, 0.4f, 0.95f, -14.0f, -19.0f, 360,  720, DEG2SHORT_ANGLE(90) },
/* SALMON           */ { 0.0140f, 6.2f, 15.0f,  80.0f,  0.300f, 1.000f, 0.995f,      0.1f, 0.70f,  -6.0f, -10.0f, 120,  220, DEG2SHORT_ANGLE(40) },
/* GOLDFISH         */ { 0.0080f, 2.2f,  4.9f,  90.0f,  0.000f, 0.250f, 0.89442998f, 0.2f, 0.10f,  -1.5f,  -3.0f, 120,  240, DEG2SHORT_ANGLE(50) },
/* PIRANHA          */ { 0.0120f, 4.2f,  7.0f,  75.0f,  0.750f, 1.000f, 0.94867998f, 0.2f, 0.40f,  -3.5f,  -6.0f, 240,  240, DEG2SHORT_ANGLE(90) },
/* AROWANA          */ { 0.0130f, 5.0f, 13.4f,  70.0f,  0.500f, 0.750f, 0.98995f,    0.2f, 0.60f,  -4.5f, -12.0f, 240,  300, DEG2SHORT_ANGLE(60) },
/* EEL              */ { 0.0095f, 3.4f, 15.0f,  55.0f,  0.200f, 0.250f, 0.98995f,    0.6f, 0.70f, -13.5f,  -4.0f,  60, 1120, DEG2SHORT_ANGLE(70) },
/* FRESHWATER_GOBY  */ { 0.0120f, 3.3f,  8.0f,  75.0f,  0.300f, 0.600f, 0.97468f,    0.2f, 0.20f,  -2.0f,  -7.0f, 240,  240, DEG2SHORT_ANGLE(70) },
/* ANGELFISH        */ { 0.0100f, 5.1f,  6.0f,  85.0f,  0.200f, 0.200f, 0.94867998f, 0.5f, 0.20f,  -3.0f,  -4.0f, 120,  360, DEG2SHORT_ANGLE(50) },
/* GUPPY            */ { 0.0080f, 2.7f,  4.9f,  96.0f,  0.200f, 0.400f, 0.89442998f, 0.5f, 0.10f,  -3.0f,  -3.0f, 120,  360, DEG2SHORT_ANGLE(30) },
/* POPEYED_GOLDFISH */ { 0.0080f, 2.5f,  4.9f, 102.0f,  0.000f, 0.250f, 0.89442998f, 0.2f, 0.10f,  -2.0f,  -3.0f, 120,  240, DEG2SHORT_ANGLE(50) },
/* COELACANTH       */ { 0.0160f, 7.1f, 22.8f,  65.0f,  0.100f, 0.300f, 0.98995f,    0.4f, 0.85f,  -2.5f, -20.5f, 300,  420, DEG2SHORT_ANGLE(20) },
/* CRAWFISH         */ { 0.0165f, 5.8f, 10.4f,  70.0f, -0.050f, 0.150f, 0.94867998f, 0.2f, 0.40f,   5.0f, -14.0f, 120,  180, DEG2SHORT_ANGLE(70) },
/* FROG             */ { 0.0100f, 1.0f,  1.0f,  70.0f,  0.500f, 0.500f, 0.94867998f, 0.2f, 0.40f,  -1.0f,  -9.0f, 120,  180, DEG2SHORT_ANGLE(70) },
/* KILLIFISH        */ { 0.0080f, 1.5f,  3.9f, 102.0f,  0.150f, 0.400f, 0.89442998f, 0.1f, 0.40f,  -1.0f,  -3.0f, 120,  360, DEG2SHORT_ANGLE(30) },
/* JELLYFISH        */ { 0.0100f, 4.0f,  5.5f,  70.0f,  0.200f, 0.150f, 0.94867998f, 0.1f, 0.40f,  -1.0f,  -3.0f,  60,  120, DEG2SHORT_ANGLE(70) },
/* SEA_BASS         */ { 0.0100f, 4.0f,  9.5f,  80.0f,  0.300f, 0.800f, 0.995f,      0.1f, 0.75f,  -3.5f,  -5.0f, 160,  200, DEG2SHORT_ANGLE(25) },
/* RED_SNAPPER      */ { 0.0100f, 6.0f, 11.4f,  90.0f,  0.250f, 0.350f, 0.995f,      0.2f, 0.45f,  -6.0f,  -6.5f, 120,  240, DEG2SHORT_ANGLE(30) },
/* BARRED_KNIFEJAW  */ { 0.0100f, 5.0f, 10.9f,  95.0f,  0.250f, 0.450f, 0.995f,      0.2f, 0.40f,  -5.0f,  -6.0f, 120,  240, DEG2SHORT_ANGLE(30) },
/* ARAPAIMA         */ { 0.0120f, 9.3f, 31.5f,  75.0f,  0.050f, 0.100f, 0.97468f,    0.2f, 0.90f, -14.0f, -31.0f, 240,  480, DEG2SHORT_ANGLE(90) }
};

s16 mfish_group_tbl[40] = {
/* CRUCIAN_CARP     */ 0, 
/* BROOK_TROUT      */ 0, 
/* CARP             */ 0, 
/* KOI              */ 0, 
/* CATFISH          */ 1, 
/* SMALL_BASS       */ 1, 
/* BASS             */ 1, 
/* LARGE_BASS       */ 1, 
/* BLUEGILL         */ 1, 
/* GIANT_CATFISH    */ 1, 
/* GIANT_SNAKEHEAD  */ 3, 
/* BARBEL_STEED     */ 0, 
/* DACE             */ 2, 
/* PALE_CHUB        */ 2, 
/* BITTERLING       */ 0, 
/* LOACH            */ 1, 
/* POND_SMELT       */ 2, 
/* SWEETFISH        */ 2, 
/* CHERRY_SALMON    */ 2, 
/* LARGE_CHAR       */ 2,
/* RAINBOW_TROUT    */ 2, 
/* STRINGFISH       */ 2, 
/* SALMON           */ 4, 
/* GOLDFISH         */ 0, 
/* PIRANHA          */ 3, 
/* AROWANA          */ 3, 
/* EEL              */ 0, 
/* FRESHWATER_GOBY  */ 1, 
/* ANGELFISH        */ 3, 
/* GUPPY            */ 3, 
/* POPEYED_GOLDFISH */ 0, 
/* COELACANTH       */ 4, 
/* CRAWFISH         */ 2, 
/* FROG             */ 1, 
/* KILLIFISH        */ 0, 
/* JELLYFISH        */ 4, 
/* SEA_BASS         */ 4, 
/* RED_SNAPPER      */ 4, 
/* BARRED_KNIFEJAW  */ 4, 
/* ARAPAIMA         */ 3
};

PRIV_FISH_CONSTRUCTOR mfish_ct[40] = {
/* CRUCIAN_CARP     */ mfish_afish_ct,
/* BROOK_TROUT      */ mfish_afish_ct,
/* CARP             */ mfish_koi_ct,
/* KOI              */ mfish_koi_ct,
/* CATFISH          */ mfish_namazu_ct,
/* SMALL_BASS       */ mfish_bass_ct,
/* BASS             */ mfish_bass_ct,
/* LARGE_BASS       */ mfish_bass_ct,
/* BLUEGILL         */ mfish_bass_ct,
/* GIANT_CATFISH    */ mfish_namazu_ct,
/* GIANT_SNAKEHEAD  */ mfish_big_fish_ct,
/* BARBEL_STEED     */ mfish_koi_ct,
/* DACE             */ mfish_ani_base_ct,
/* PALE_CHUB        */ mfish_small_fish_ct,
/* BITTERLING       */ mfish_afish_ct,
/* LOACH            */ mfish_dojou_ct,
/* POND_SMELT       */ mfish_small_fish_ct,
/* SWEETFISH        */ mfish_ani_base_ct,
/* CHERRY_SALMON    */ mfish_ani_base_ct,
/* LARGE_CHAR       */ mfish_ani_base_ct,
/* RAINBOW_TROUT    */ mfish_ani_base_ct,
/* STRINGFISH       */ mfish_ito_ct,
/* SALMON           */ mfish_seafish_ct,
/* GOLDFISH         */ mfish_kingyo_ct,
/* PIRANHA          */ mfish_ani_base_ct,
/* AROWANA          */ mfish_aroana_ct,
/* EEL              */ mfish_unagi_ct,
/* FRESHWATER_GOBY  */ mfish_donko_ct,
/* ANGELFISH        */ mfish_small_fish_ct,
/* GUPPY            */ mfish_gupi_ct,
/* POPEYED_GOLDFISH */ mfish_kingyo_ct,
/* COELACANTH       */ mfish_kaseki_ct,
/* CRAWFISH         */ mfish_zarigani_ct,
/* FROG             */ mfish_kaeru_ct,
/* KILLIFISH        */ mfish_medaka_ct,
/* JELLYFISH        */ mfish_kurage_ct,
/* SEA_BASS         */ mfish_seafish_ct,
/* RED_SNAPPER      */ mfish_tai_ct,
/* BARRED_KNIFEJAW  */ mfish_tai_ct,
/* ARAPAIMA         */ mfish_big_fish_ct
};

PRIV_FISH_MOVE mfish_mv[40] = {
/* CRUCIAN_CARP     */ mfish_afish_mv,
/* BROOK_TROUT      */ mfish_afish_mv,
/* CARP             */ mfish_koi_mv,
/* KOI              */ mfish_koi_mv,
/* CATFISH          */ mfish_namazu_mv,
/* SMALL_BASS       */ mfish_bass_mv,
/* BASS             */ mfish_bass_mv,
/* LARGE_BASS       */ mfish_bass_mv,
/* BLUEGILL         */ mfish_bass_mv,
/* GIANT_CATFISH    */ mfish_namazu_mv,
/* GIANT_SNAKEHEAD  */ mfish_big_fish_mv,
/* BARBEL_STEED     */ mfish_koi_mv,
/* DACE             */ mfish_ani_base_mv,
/* PALE_CHUB        */ mfish_small_fish_mv,
/* BITTERLING       */ mfish_afish_mv,
/* LOACH            */ mfish_dojou_mv,
/* POND_SMELT       */ mfish_small_fish_mv,
/* SWEETFISH        */ mfish_ani_base_mv,
/* CHERRY_SALMON    */ mfish_ani_base_mv,
/* LARGE_CHAR       */ mfish_ani_base_mv,
/* RAINBOW_TROUT    */ mfish_ani_base_mv,
/* STRINGFISH       */ mfish_ito_mv,
/* SALMON           */ mfish_seafish_mv,
/* GOLDFISH         */ mfish_kingyo_mv,
/* PIRANHA          */ mfish_ani_base_mv,
/* AROWANA          */ mfish_aroana_mv,
/* EEL              */ mfish_unagi_mv,
/* FRESHWATER_GOBY  */ mfish_donko_mv,
/* ANGELFISH        */ mfish_small_fish_mv,
/* GUPPY            */ mfish_gupi_mv,
/* POPEYED_GOLDFISH */ mfish_kingyo_mv,
/* COELACANTH       */ mfish_kaseki_mv,
/* CRAWFISH         */ mfish_zarigani_mv,
/* FROG             */ mfish_kaeru_mv,
/* KILLIFISH        */ mfish_medaka_mv,
/* JELLYFISH        */ mfish_kurage_mv,
/* SEA_BASS         */ mfish_seafish_mv,
/* RED_SNAPPER      */ mfish_tai_mv,
/* BARRED_KNIFEJAW  */ mfish_tai_mv,
/* ARAPAIMA         */ mfish_big_fish_mv
};


PRIV_FISH_DRAW mfish_dw[40] = {
/* CRUCIAN_CARP     */ mfish_afish_dw,
/* BROOK_TROUT      */ mfish_afish_dw,
/* CARP             */ mfish_koi_dw,
/* KOI              */ mfish_koi_dw,
/* CATFISH          */ mfish_namazu_dw,
/* SMALL_BASS       */ mfish_bass_dw,
/* BASS             */ mfish_bass_dw,
/* LARGE_BASS       */ mfish_bass_dw,
/* BLUEGILL         */ mfish_bass_dw,
/* GIANT_CATFISH    */ mfish_namazu_dw,
/* GIANT_SNAKEHEAD  */ mfish_big_fish_dw,
/* BARBEL_STEED     */ mfish_koi_dw,
/* DACE             */ mfish_ani_base_dw,
/* PALE_CHUB        */ mfish_small_fish_dw,
/* BITTERLING       */ mfish_afish_dw,
/* LOACH            */ mfish_dojou_dw,
/* POND_SMELT       */ mfish_small_fish_dw,
/* SWEETFISH        */ mfish_ani_base_dw,
/* CHERRY_SALMON    */ mfish_ani_base_dw,
/* LARGE_CHAR       */ mfish_ani_base_dw,
/* RAINBOW_TROUT    */ mfish_ani_base_dw,
/* STRINGFISH       */ mfish_ito_dw,
/* SALMON           */ mfish_seafish_dw,
/* GOLDFISH         */ mfish_kingyo_dw,
/* PIRANHA          */ mfish_ani_base_dw,
/* AROWANA          */ mfish_aroana_dw,
/* EEL              */ mfish_unagi_dw,
/* FRESHWATER_GOBY  */ mfish_donko_dw,
/* ANGELFISH        */ mfish_small_fish_dw,
/* GUPPY            */ mfish_gupi_dw,
/* POPEYED_GOLDFISH */ mfish_kingyo_dw,
/* COELACANTH       */ mfish_kaseki_dw,
/* CRAWFISH         */ mfish_zarigani_dw,
/* FROG             */ mfish_kaeru_dw,
/* KILLIFISH        */ mfish_medaka_dw,
/* JELLYFISH        */ mfish_kurage_dw,
/* SEA_BASS         */ mfish_seafish_dw,
/* RED_SNAPPER      */ mfish_tai_dw,
/* BARRED_KNIFEJAW  */ mfish_tai_dw,
/* ARAPAIMA         */ mfish_big_fish_dw
};

xyz_t unagi_rail_pos[25] = {
    { 228.0f, 57.0f, 192.0f },
    { 231.0f, 57.0f, 203.0f },
    { 237.0f, 57.0f, 215.0f },
    { 245.0f, 58.0f, 225.0f },
    { 252.0f, 59.0f, 233.0f },
    { 254.0f, 60.0f, 245.0f },
    { 248.0f, 60.0f, 255.0f },
    { 238.0f, 60.0f, 256.0f },
    { 231.0f, 60.0f, 247.0f },
    { 222.0f, 60.0f, 240.0f },
    { 212.0f, 60.0f, 243.0f },
    { 203.0f, 60.0f, 249.0f },
    { 196.0f, 60.0f, 248.0f },
    { 191.0f, 60.0f, 241.0f },
    { 191.0f, 60.0f, 234.0f },
    { 187.0f, 60.0f, 223.0f },
    { 183.0f, 60.0f, 212.0f },
    { 181.0f, 60.0f, 203.0f },
    { 182.0f, 57.0f, 191.0f },
    { 187.0f, 56.0f, 183.0f },
    { 193.0f, 56.0f, 176.0f },
    { 201.0f, 56.0f, 172.0f },
    { 209.0f, 56.0f, 173.0f },
    { 216.0f, 56.0f, 176.0f },
    { 221.0f, 56.0f, 182.0f }
};

xyz_t unagi_rail_pos2[20] = {
    { 228.0f, 57.0f, 192.0f },
    { 236.0f, 57.0f, 201.0f },
    { 244.0f, 57.0f, 204.0f },
    { 250.0f, 58.0f, 213.0f },
    { 254.0f, 59.0f, 225.0f },
    { 250.0f, 60.0f, 238.0f },
    { 243.0f, 60.0f, 242.0f },
    { 235.0f, 60.0f, 238.0f },
    { 226.0f, 60.0f, 233.0f },
    { 215.0f, 60.0f, 229.0f },
    { 205.0f, 60.0f, 228.0f },
    { 198.0f, 60.0f, 229.0f },
    { 191.0f, 60.0f, 227.0f },
    { 186.0f, 60.0f, 222.0f },
    { 181.0f, 60.0f, 216.0f },
    { 181.0f, 60.0f, 207.0f },
    { 184.0f, 60.0f, 196.0f },
    { 191.0f, 60.0f, 186.0f },
    { 201.0f, 57.0f, 177.0f },
    { 213.0f, 56.0f, 178.0f }
};

xyz_t unagi_rail_pos3[25] = {
    { 228.0f, 57.0f, 192.0f },
    { 231.0f, 57.0f, 203.0f },
    { 229.0f, 57.0f, 213.0f },
    { 222.0f, 58.0f, 225.0f },
    { 212.0f, 59.0f, 226.0f },
    { 204.0f, 60.0f, 227.0f },
    { 197.0f, 60.0f, 230.0f },
    { 193.0f, 60.0f, 236.0f },
    { 195.0f, 60.0f, 246.0f },
    { 201.0f, 60.0f, 253.0f },
    { 212.0f, 60.0f, 256.0f },
    { 222.0f, 60.0f, 255.0f },
    { 237.0f, 60.0f, 254.0f },
    { 243.0f, 60.0f, 246.0f },
    { 240.0f, 60.0f, 232.0f },
    { 232.0f, 60.0f, 227.0f },
    { 223.0f, 60.0f, 225.0f },
    { 209.0f, 60.0f, 225.0f },
    { 198.0f, 60.0f, 220.0f },
    { 190.0f, 60.0f, 209.0f },
    { 187.0f, 60.0f, 196.0f },
    { 191.0f, 60.0f, 184.0f },
    { 197.0f, 60.0f, 178.0f },
    { 207.0f, 59.0f, 173.0f },
    { 221.0f, 57.0f, 180.0f }
};

xyz_t unagi_normal_to_reverse_rail_pos[12] = {
    { 228.0f, 57.0f, 192.0f },
    { 236.0f, 57.0f, 201.0f },
    { 244.0f, 57.0f, 204.0f },
    { 250.0f, 58.0f, 213.0f },
    { 254.0f, 59.0f, 225.0f },
    { 250.0f, 60.0f, 238.0f },
    { 243.0f, 60.0f, 242.0f },
    { 235.0f, 60.0f, 236.0f },
    { 226.0f, 60.0f, 228.0f },
    { 225.0f, 60.0f, 219.0f },
    { 228.0f, 58.0f, 208.0f },
    { 228.0f, 57.0f, 192.0f }
};

xyz_t unagi_reverse_to_normal_rail_pos[19] = {
    { 228.0f, 57.0f, 192.0f },
    { 218.0f, 56.0f, 178.0f },
    { 204.0f, 57.0f, 176.0f },
    { 191.0f, 58.0f, 186.0f },
    { 184.0f, 59.0f, 196.0f },
    { 189.0f, 60.0f, 208.0f },
    { 198.0f, 60.0f, 215.0f },
    { 205.0f, 60.0f, 224.0f },
    { 204.0f, 60.0f, 235.0f },
    { 196.0f, 60.0f, 242.0f },
    { 188.0f, 60.0f, 241.0f },
    { 183.0f, 60.0f, 233.0f },
    { 180.0f, 60.0f, 219.0f },
    { 181.0f, 60.0f, 207.0f },
    { 184.0f, 60.0f, 196.0f },
    { 191.0f, 59.0f, 186.0f },
    { 204.0f, 57.0f, 176.0f },
    { 218.0f, 56.0f, 178.0f },
    { 228.0f, 57.0f, 192.0f }
};

xyz_t *unagi_rail_tbl[3] = {
    unagi_rail_pos,
    unagi_rail_pos2,
    unagi_rail_pos3
};

int unagi_rail_num_tbl[3] = {
    ARRAY_LEN(unagi_rail_pos),
    ARRAY_LEN(unagi_rail_pos2),
    ARRAY_LEN(unagi_rail_pos3),
};

cKF_Skeleton_R_c* kusa_model[14] = {
    &cKF_bs_r_obj_museum5_kusa1,
    &cKF_bs_r_obj_museum5_kusa1,
    &cKF_bs_r_obj_museum5_kusa1,
    &cKF_bs_r_obj_museum5_kusa1,
    &cKF_bs_r_obj_museum5_kusa1,
    &cKF_bs_r_obj_museum5_kusa2,
    &cKF_bs_r_obj_museum5_kusa2,
    &cKF_bs_r_obj_museum5_kusa2,
    &cKF_bs_r_obj_museum5_kusa2,
    &cKF_bs_r_obj_museum5_kusa2,
    &cKF_bs_r_obj_museum5_kusa3,
    &cKF_bs_r_obj_museum5_kusa3,
    &cKF_bs_r_obj_museum5_kusa3,
    &cKF_bs_r_obj_museum5_kusa3
};
cKF_Animation_R_c* kusa_anime[14]= {
    &cKF_ba_r_obj_museum5_kusa1,
    &cKF_ba_r_obj_museum5_kusa1,
    &cKF_ba_r_obj_museum5_kusa1,
    &cKF_ba_r_obj_museum5_kusa1,
    &cKF_ba_r_obj_museum5_kusa1,
    &cKF_ba_r_obj_museum5_kusa2,
    &cKF_ba_r_obj_museum5_kusa2,
    &cKF_ba_r_obj_museum5_kusa2,
    &cKF_ba_r_obj_museum5_kusa2,
    &cKF_ba_r_obj_museum5_kusa2,
    &cKF_ba_r_obj_museum5_kusa3,
    &cKF_ba_r_obj_museum5_kusa3,
    &cKF_ba_r_obj_museum5_kusa3,
    &cKF_ba_r_obj_museum5_kusa3
};

float kusa_start_frame[14] = {
    25.0f, 0.0f, 25.0f, 0.0f, 50.0f, 0.0f, 20.0f, 60.0f, 80.0f, 0.0f, 0.0f, 25.0f, 0.0f, 75.0f
};

// clang-format on

void Museum_Fish_Prv_data_init(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game, int fishNum, int r6) {
    actor->_59C = fishNum;
    actor->init_data = mfish_init_data[fishNum];
    actor->_630 = mfish_group_tbl[fishNum];

    if (actor->_630 >= 0) {
        actor->_5A0 = suisou_pos[actor->_630];
    } else {
        actor->_5A0 = ZeroVec;
    }

    actor->_5A0.y = mfish_init_data[fishNum]._0C + fqrand2() * 10.0f;
    if (r6 == 1) {
        actor->_5A0.x += fqrand2() * 90.0f;
        actor->_5A0.z += fqrand2() * 90.0f;
    }
    actor->_34 = &mfish_normal_process;
    mfish_ct[fishNum](actor, game);
}

void Museum_Fish_Actor_ct(ACTOR* actorx, GAME* gamex) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;
    int i;
    MUSEUM_FISH_PRIVATE_DATA* prv;
    MF_Control_Actor = actor;
    actor->_14db6 = 0x1e;

    mfish_point_light_ct(actorx, gamex);

    for (i = 0; i < 14; i++) {
        // 0x0060 : kusa_group_tbl
        // 0x1300 : kusa_model
        // 0x1338 : kusa_anime
        // 0x1370 : kusa_start_frame
        actor->prvFish2[i]._54C = kusa_model[i];
        cKF_SkeletonInfo_R_ct(&actor->prvFish2[i]._00, kusa_model[i], kusa_anime[i], &actor->prvFish2[i]._4F0,
                              &actor->prvFish2[i]._514);
        cKF_SkeletonInfo_R_init_standard_repeat_speedsetandmorph(&actor->prvFish2[i]._00, kusa_anime[i], NULL,
                                                                 kusa_group_tbl[i] == 2 ? 1.5f : 0.5f, 0.0f);
        actor->prvFish2[i]._00.frame_control.current_frame = kusa_start_frame[i];
        actor->_101f0 = qrand();
        actor->_101f4 = qrand();
    }

    if (mMmd_FishInfo(0x21)) {
        actor->prvFish[0x21]._590 = &actor->_14788;
    } else {
        mfish_hasu_ct(&actor->prvFish[0x21], gamex);
    }

    prv = actor->prvFish;
    for (i = 0; i < 40; i++, prv++) {
        prv->_62E &= ~1;
        if (mMmd_FishInfo(i)) {
            prv->_584 = mfish_model_tbl[i];
            prv->_588 = mfish_anime_init_tbl[i];
            prv->_62E |= 1;
            Museum_Fish_Prv_data_init(prv, gamex, i, 1);
        }
    }

    for (i = 0; i < 20; i++) {
        actor->_14d50[i] = 40.0f + 80.0f * fqrand();
        actor->_14d78[i] = 2.0f + 3.0f * fqrand();
    }
}

void Museum_Fish_Actor_dt(ACTOR* actor, GAME* game) {
    mfish_point_light_dt(actor, game);
}

int Museum_Fish_GetMsgNo(ACTOR* actorx) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;

    static u8 item_name[mIN_ITEM_NAME_LEN];
    int itemArticle;
    mMsg_Window_c* msg;

    int fishInfo = actor->fishDisplayMsgInfo[actor->fishDisplayMsgIter].fishInfo;
    mActor_name_t fishName = mNT_FishIdx2FishItemNo(actor->fishDisplayMsgInfo[actor->fishDisplayMsgIter].fishName);
    mIN_copy_name_str(item_name, fishName);
    mMsg_Set_item_str_art(mMsg_Get_base_window_p(), 0, item_name, 0x10, mIN_get_item_article(fishName));

    if (fishInfo >= 1 && fishInfo <= 4) {
        mMsg_Set_free_str(mMsg_Get_base_window_p(), 0,
                          common_data.save.save.private_data[fishInfo - 1].player_ID.player_name, 8);
    }

    if (actor->fishDisplayMsgIter < actor->numFishDisplayed - 1) {
        if (fishInfo >= 1 && fishInfo <= 4) {
            return 0x2fa2;
        } else {
            return 0x2fa3;
        }
    }

    if (fishInfo >= 1 && fishInfo <= 4) {
        return 0x2f9f;
    } else {
        return 0x2fa0;
    }
}

BOOL Museum_Fish_Check_Talk_Distance(GAME* gamex, int index) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    s16 subAngle;
    xyz_t pos;
    PLAYER_ACTOR* actor;

    // fish tank locations?
    static xyz_t kanban_pos[5] = { { 260.0f, 40.0f, 300.0f },
                                   { 460.0f, 40.0f, 300.0f },
                                   { 260.0f, 40.0f, 540.0f },
                                   { 460.0f, 40.0f, 540.0f },
                                   { 500.0f, 40.0f, 60.0f } };

    actor = get_player_actor_withoutCheck(game);
    subAngle = DEG2SHORT_ANGLE(-180) + actor->actor_class.world.angle.y;
    xyz_t_sub(&actor->actor_class.world.position, &kanban_pos[index], &pos);

    if (ABS(pos.x) < 20.0f && ABS(pos.z) < 20.0f && ABS(subAngle) < 0x3000) {
        return TRUE;
    }
    return FALSE;
}

void Museum_Fish_Set_MsgFishInfo(ACTOR* actorx, int param2) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;
    int i;
    // defines how many fish are in each grouping of fish names
    static int group_max_num[5] = { 10, 9, 9, 6, 6 };
    static int group_A_fish_name[10] = { 0, 1, 2, 3, 11, 14, 26, 23, 30, 34 };
    static int group_B_fish_name[9] = { 4, 9, 15, 8, 5, 6, 7, 27, 33 };
    static int group_C_fish_name[9] = { 12, 13, 16, 17, 18, 20, 19, 21, 32 };
    static int group_D_fish_name[6] = { 10, 29, 28, 24, 25, 39 };
    static int group_E_fish_name[6] = { 22, 31, 35, 36, 37, 38 };

    static int* group_fish_name[5] = { group_A_fish_name, group_B_fish_name, group_C_fish_name, group_D_fish_name,
                                       group_E_fish_name };

    actor->numFishDisplayed = 0;
    actor->fishDisplayMsgIter = 0;
    for (i = 0; i < group_max_num[param2]; i++) {
        s16 fishName = group_fish_name[param2][i];
        s16 fishInfo = mMmd_FishInfo(fishName); // is this fish on display?
        if (fishInfo != 0) {
            actor->fishDisplayMsgInfo[actor->numFishDisplayed].fishName = fishName; // add info to list
            actor->fishDisplayMsgInfo[actor->numFishDisplayed].fishInfo = fishInfo;
            actor->numFishDisplayed++; // incrememnt counter of fish on display
        }
    }

    return;
}

void Museum_Fish_set_talk_info(ACTOR* actorx) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;

    static rgba_t window_color = { 255, 255, 0xcd, 255 };
    int r3;
    if (actor->numFishDisplayed > 0) { // maybe related to if there are fish in the tank
        r3 = Museum_Fish_GetMsgNo(actorx);
        actor->fishDisplayMsgIter++; // maybe iterating through the fish donation record, given which fish are donated?
    } else {
        r3 = 0x2fa1;
    }

    mDemo_Set_msg_num(r3);
    mDemo_Set_talk_window_color(&window_color);
    mDemo_Set_talk_display_name(0);
    mDemo_Set_ListenAble();
    mDemo_Set_camera(CAMERA2_PROCESS_NORMAL);
    mDemo_Set_use_zoom_sound(TRUE);
}

void Museum_Fish_Talk_process() {
    // NOT BAD
    return;
}

void Museum_Fish_Actor_move(ACTOR* actorx, GAME* game) {
    s16 old_14db4;
    int i;
    f32 v;
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    MUSEUM_FISH_PRIVATE_DATA* prv;

    mfish_point_light_mv(actorx, game);
    old_14db4 = actor->_14db4;
    mfish_get_player_area(actor, game);

    if (actor->_14db4 != old_14db4) {
        PLAYER_ACTOR* player;
        xyz_t p;
        prv = actor->prvFish;
        player = get_player_actor_withoutCheck(play);
        p = player->actor_class.world.position;

        if (actor->_14db4 == 3) {
            actor->prvFish[0x17]._626 = 0;
            actor->prvFish[0x1e]._626 = 0;
            actor->prvFish[0x18]._626 = 0;
        } else if (actor->_14db4 == 0) {
            actor->prvFish[2]._626 = 20;
            actor->prvFish[3]._626 = 20;
        }

        for (i = 0; i < 40; i++, prv++) {
            f32 v = search_position_distanceXZ(&p, &prv->_5A0);
            if (actor->_14db4 == prv->_630 && v < 60.0f) {
                prv->_626 = fqrand() * 60.0f;
            }
        }
    }

    for (i = 0; i < 0xe; i++) {
        cKF_SkeletonInfo_R_play(&actor->prvFish2[i]._00);
        if (kusa_group_tbl[i] == 2) {
            add_calc2(&actor->prvFish2[i]._540, -2.25f, 1.75f, 1.75f);
            add_calc_short_angle2(&actor->prvFish2[i]._53A, DEG2SHORT_ANGLE(3.5f),
                                  1.0f - sqrtf(1.0f - (1.0f - sqrtf(0.9f))), 20, 4);
        } else {
            actor->prvFish2[i]._540 *= 0.9f;
            add_calc_short_angle2(&actor->prvFish2[i]._53A, DEG2SHORT_ANGLE(3.5f),
                                  1.0f - sqrtf(1.0f - (1.0f - sqrtf(0.9f))), 20, 4);
        }
        actor->prvFish2[i]._548 *= 0.98f;

        actor->prvFish2[i]._538 += actor->prvFish2[i]._53A;
        actor->prvFish2[i]._53C += actor->prvFish2[i]._53A >> 1;

        add_calc_short_angle2(&actor->prvFish2[i]._53A, DEG2SHORT_ANGLE(0), 1.0f - sqrtf(1.0f - (1.0f - sqrtf(0.9f))),
                              20, 4);
    }

    Museum_Fish_Kusa_Check(actor, game);
    Museum_Fish_Object_Check(actor, game);

    for (i = 0; i < 20; i++) {
        actor->_14d50[i]--;
        if (actor->_14d50[i] < 0) {
            common_data.clip.effect_clip->effect_make_proc(0x6e, suisou_awa_pos[i], 2, 0, game, -1, suisou_awa_group[i],
                                                           0);
            if (actor->_14d78[i] > 0) {
                actor->_14d78[i]--;

                actor->_14d50[i] = fqrand() * 8 + 2;
            } else {
                actor->_14d50[i] = fqrand() * 160 + 80;
                actor->_14d78[i] = fqrand() * 3 + 2;
            }
        }
    }

    Museum_Fish_Talk_process(actor, game);
    prv = actor->prvFish;
    for (i = 0; i < 40; i++, prv++) {
        if (prv->_62E & 1) {
            mfish_mv[i](prv, game);
        }
    }

    if ((actor->prvFish[0x21]._62E & 1) == 0) {
        mfish_hasu_mv(&actor->prvFish[0x21], game);
    }

    for (i = 0; i < 5; i++) {
        if (i == 2) {
            actor->_14d78[i] += (s16)DEG2SHORT_ANGLE2((float)GETREG(TAKREG, 20) * 0.1f + 0.5f + fqrand());
        } else {
            actor->_14d78[i] += 8;
        }
    }
}

extern Gfx obj_suisou1_model[];
extern Gfx obj_suisou1_modelT[];

extern Gfx obj_museum5_model[];
extern Gfx obj_museum5_modelT[];

void Museum_Fish_Suisou_draw(MUSEUM_FISH_ACTOR* actor, GAME* game, int r5) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    GRAPH* graph = play->game.graph;
    if (r5 < 4) {
        xyz_t* p = &suisou_pos[r5];
        if (mfish_cull_check(game, &suisou_pos[r5], 350.0f, 20.0f, 650.0f)) {
            Matrix_translate(suisou_pos[r5].x, 0, suisou_pos[r5].z, 0);
            Matrix_scale(0.1f, 0.1f, 0.1f, 1);

            OPEN_DISP(graph);
            gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(play->game.graph),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(play->game.graph),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

            Setpos_HiliteReflect_xlu_init(&suisou_pos[r5], play);

            gSPDisplayList(NEXT_POLY_XLU_DISP, obj_suisou1_model);
            gSPDisplayList(NEXT_POLY_XLU_DISP, obj_suisou1_modelT);

            CLOSE_DISP(graph);

            if ((actor->prvFish[0x21]._62E & 1) == 0) {
                mfish_hasu_dw(&actor->prvFish[0x21], game);
            }
        }
    } else if (mfish_cull_check(game, &suisou_pos[4], 215.0f, 25.0f, 0.0f)) {
        Matrix_scale(0.0625f, 0.0625f, 0.0625f, 0);
        OPEN_DISP(graph);

        gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(play->game.graph),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(play->game.graph),
                  G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        Setpos_HiliteReflect_xlu_init(&suisou_pos[r5], play);

        gDPSetTextureAdjustMode(NEXT_POLY_OPA_DISP, G_TA_DOLPHIN);
        gDPSetTextureAdjustMode(NEXT_POLY_XLU_DISP, G_TA_DOLPHIN);
        gSPDisplayList(NEXT_POLY_OPA_DISP, obj_museum5_model);
        gSPDisplayList(NEXT_POLY_XLU_DISP, obj_museum5_modelT);
        gDPSetTextureAdjustMode(NEXT_POLY_OPA_DISP, G_TA_N64);
        gDPSetTextureAdjustMode(NEXT_POLY_XLU_DISP, G_TA_N64);
        CLOSE_DISP(graph);
    }
}

void kusa_before_disp() {
    return;
}

void Museum_Fish_Kusa_Draw(ACTOR* actor, GAME* game) {
    return;
}

void Museum_Fish_Actor_draw(ACTOR* actor, GAME* game) {
    return;
}

BOOL mfish_cull_check(GAME* game, xyz_t* worldPos, f32 x, f32 y, f32 _y) {
    xyz_t screenPos;
    Game_play_Projection_Trans((GAME_PLAY*)game, worldPos, &screenPos);
    if ((-x < screenPos.x) && (screenPos.x < x + 320) && (-y < screenPos.y) && (screenPos.y < _y + 240)) {
        return TRUE;
    }
    return FALSE;
}

void mfish_point_ligh_pos_get() {
    return;
}

void mfish_point_light_ct(ACTOR* actorx, GAME* gamex) {
    MUSEUM_FISH_ACTOR* actor;
    GAME_PLAY* game;
    game = (GAME_PLAY*)gamex;
    actor = (MUSEUM_FISH_ACTOR*)actorx;
    mfish_point_ligh_pos_get(actor, game, 0);
    mfish_point_ligh_pos_get(actor, game, 1);
    actor->_14db8 = mEnv_ReservePointLight(game, &actor->_14d08, 0, 0x96, 0xff, (u8)actor->_14dbc);
    actor->_14dba = mEnv_ReservePointLight(game, &actor->_14d14, 0, 0x96, 0xff, (u8)actor->_14dbe);
    actor->_14dc0 = 0;
}

void mfish_point_light_dt(ACTOR* actorx, GAME* game) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;

    if (actor->_14db8 != -1) {
        mEnv_CancelReservedPointLight(actor->_14db8, (GAME_PLAY*)game);
    }

    if (actor->_14dba != -1) {
        mEnv_CancelReservedPointLight(actor->_14dba, (GAME_PLAY*)game);
    }
}

void mfish_point_light_mv(ACTOR* actor, GAME* game) {
    return;
}

void mfish_normal_light_set(ACTOR* actor, GAME* _game) {
    LightsN* lights;
    GAME_PLAY* game = (GAME_PLAY*)_game;

    xyz_t lightPos;
    lightPos.x = 320;
    lightPos.y = 0;
    lightPos.z = 240;

    lights = Global_light_read(&game->global_light, game->game.graph);
    LightsN_list_check(lights, game->global_light.list, &lightPos);
    LightsN_disp(lights, game->game.graph);
}

f32 Rnd_EX_f(f32 v) {
    f32 rand1 = 2 * fqrand2();
    f32 rand2 = fqrand();
    if (rand2 > (rand1 * rand1)) {
        if (rand1 > 0) {
            rand1 = sqrtf(rand2);
        } else {
            rand1 = -sqrtf(rand2);
        }
    }
    rand1 = (1.0f + rand1) * 0.5f;
    return v * rand1;
}

f32 Rnd_EX_fx(f32 v1) {
    f32 rand1 = 2 * fqrand2();
    f32 rand2 = fqrand();
    if (rand2 > (rand1 * rand1)) {
        if (rand1 > 0) {
            rand1 = sqrtf(rand2);
        } else {
            rand1 = -sqrtf(rand2);
        }
    }
    rand1 = rand1 / 2;
    return v1 * rand1;
}

void mfish_base_FishMove() {
    return;
}

int mfish_PosWallCheck(MUSEUM_FISH_PRIVATE_DATA* priv, xyz_t* pos) {
    u32 flag = 0;
    xyz_t p = suisou_pos[priv->_630];
    f32 a, b, c, d;

    if (priv->_630 < 4) {
        a = priv->init_data._28 + 45;
        b = priv->init_data._28 + 45;
        c = priv->init_data._28 + 45;
        d = priv->init_data._28 + 45;
    } else {
        a = priv->init_data._28 + 180;
        b = priv->init_data._28 + 180;
        c = priv->init_data._28 + 5;
        d = priv->init_data._28 + 45;
    }

    if (pos->x > p.x + a) {
        flag |= 4;
    } else if (pos->x < p.x - b) {
        flag |= 2;
    }

    if (pos->z > p.z + c) {
        flag |= 8;
    } else if (pos->z < p.z - d) {
        flag |= 0x10;
    }

    return flag;
}

void mfish_WallCheck() {
    return;
}

s16 mfish_get_hide_camera_angle(MUSEUM_FISH_PRIVATE_DATA* priv) {
    s16 v = priv->_60C.z;
    if (v > 0 || (priv->_630 == 2 && fqrand() < 0.8f)) {
        if (v > DEG2SHORT_ANGLE(90)) {
            v = DEG2SHORT_ANGLE(90) + DEG2SHORT_ANGLE(45 * fqrand());
        } else {
            v = DEG2SHORT_ANGLE(90) - DEG2SHORT_ANGLE(45 * fqrand());
        }
    } else {
        if (v > DEG2SHORT_ANGLE(-90)) {
            v = DEG2SHORT_ANGLE(-90) + DEG2SHORT_ANGLE(45 * fqrand());
        } else {
            v = DEG2SHORT_ANGLE(-90) - DEG2SHORT_ANGLE(45 * fqrand());
        }
    }
    return v;
}

void mfish_dummy_process_init() {
    mfish_get_hide_camera_angle(0);
}

void mfish_dummy_process() {
    return;
}

void mfish_normal_process_init() {
    return;
}

void mfish_normal_process() {
    return;
}

void mfish_turn_process_init() {
    return;
}

void mfish_turn_process() {
    return;
}

void mfish_peck_process_init() {
    return;
}

void mfish_peck_process() {
    return;
}

void mfish_ground_peck_process_init() {
    return;
}

void mfish_ground_peck_process() {
    return;
}

void mfish_base_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_base_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_onefish_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    YET_SKELETON* huh = &actor->_38;
    // looks like it loads from 0x38, which i labeled as the skeleton,
    // but then it adds like 0x514 to it, so this must be huge

    // cKF_SkeletonInfo_R_ct(&huh->_00, huh->_00); //TODO
    return;
}

void mfish_onefish_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    cKF_SkeletonInfo_R_play(&actor->_38._00);
    return;
}

int mfish_before_disp(GAME* r3, cKF_SkeletonInfo_R_c* r4, int r5, Gfx** r6, u8* r7, void* arg, s_xyz* r9, xyz_t* r10) {

    MUSEUM_FISH_PRIVATE_DATA* actor = (MUSEUM_FISH_PRIVATE_DATA*)arg;
    if (r5 == 2) {
        int v, t;
        if (actor->_630 != 4) {
            v = 2;
        } else if (actor->init_data._20 > 0.7f) {
            v = 1;
        } else if (actor->init_data._20 > 0.5f) {
            v = 2;
        } else {
            v = 3;
        }
        t = r9->y - (actor->_61C * v);
        r9->y = MY_CLAMP(t, DEG2SHORT_ANGLE(-60), DEG2SHORT_ANGLE(60));
        t = r9->x - (actor->_61C >> 1);
        r9->x = MY_CLAMP(t, DEG2SHORT_ANGLE(-25), DEG2SHORT_ANGLE(25));
    }
    return 1;
}

void mfish_onefish_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    YET_SKELETON* skele;
    Mtx* mtx;
    GAME_PLAY* play;
    GRAPH* graph;

    play = (GAME_PLAY*)gamex;
    skele = &actor->_38;

    if (play->game.frame_counter % 2 != 0) {
        mtx = &skele->_70;
    } else {
        mtx = &skele->_2b0;
    }

    graph = play->game.graph;

    Matrix_translate(actor->_5A0.x, actor->_5A0.y + actor->_5B0, actor->_5A0.z, 0);
    Matrix_RotateY(actor->_60C.z, 1);

    Matrix_translate(0, 0.25f * actor->init_data._04, 0.5f * actor->init_data._24, 1);
    Matrix_RotateX(actor->_60C.x, 1);
    Matrix_RotateZ(MY_CLAMP(-(actor->_61C >> 1), DEG2SHORT_ANGLE(-20), DEG2SHORT_ANGLE(20)), 1);
    Matrix_translate(0, 0.25f * -actor->init_data._04, 0.5f * -actor->init_data._24, 1);
    Matrix_scale(actor->init_data._00, actor->init_data._00, actor->init_data._00, 1);

    OPEN_DISP(graph);
    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(play->game.graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    CLOSE_DISP(graph);

    cKF_Si3_draw_R_SV(&play->game, &skele->_00, mtx, &mfish_before_disp, 0, actor);
}

void mfish_ani_base_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_ani_base_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_ani_base_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void Museum_Fish_BigFishObjCheck() {
    return;
}

void Museum_Fish_ObjBGCheck() {
    return;
}

void Museum_Fish_DonkoBGCheck() {
    return;
}

void Museum_Fish_objchk_pos_set() {
    return;
}

void Museum_Fish_BGCheck() {
    return;
}

void Museum_Fish_Kusa_Check() {
    static int kusa_group_tbl[] = { 0, 2, 1, 3, 3, 4, 4, 4, 4, 4, 0, 2, 1, 3 };
}

void Museum_Fish_Object_Check() {
    return;
}

void mfish_body_wind_anime_play() {
    return;
}

void mfish_get_player_angle() {
    return;
}

void mfish_peck_check() {
    return;
}

void mfish_peck_wall_check() {
    return;
}

void mfish_ground_peck_before_check() {
    return;
}

void mfish_get_player_area() {
    return;
}

void mfish_get_flow_vec(xyz_t* pos, MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game) {
    return;
}

void mfish_get_escape_angle() {
    return;
}

void mfish_move_smooth() {
    return;
}

void mfish_hamon_make() {
    return;
}

void mfish_afish_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_afish_dummy_process_init() {
    return;
}

void mfish_afish_dummy_process() {
    return;
}

void mfish_afish_normal_process_init() {
    return;
}

void mfish_afish_normal_process() {
    return;
}

void mfish_afish_turn_process_init() {
    return;
}

void mfish_afish_turn_process() {
    return;
}

void mfish_afish_base_FishMove() {
    return;
}

void mfish_afish_base_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_afish_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_afish_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_aroana_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_aroana_dummy_process_init() {
    return;
}

void mfish_aroana_dummy_process() {
    return;
}

void mfish_aroana_normal_process_init() {
    return;
}

void mfish_aroana_normal_process() {
    return;
}

void mfish_aroana_turn_process_init() {
    return;
}

void mfish_aroana_turn_process() {
    return;
}

void mfish_aroana_long_move_process_init() {
    return;
}

void mfish_aroana_long_move_process() {
    return;
}

void mfish_aroana_base_FishMove() {
    return;
}

void mfish_aroana_base_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_aroana_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_aroana_before_disp() {
    return;
}

void mfish_aroana_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_koi_tail_anim_set() {
    return;
}

void mfish_koi_move_smooth() {
    return;
}

void mfish_koi_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_koi_dummy_process_init() {
    return;
}

void mfish_koi_dummy_process() {
    return;
}

void mfish_koi_normal_process_init() {
    return;
}

void mfish_koi_normal_process() {
    return;
}

void mfish_koi_turn_process_init() {
    return;
}

void mfish_koi_turn_process() {
    return;
}

void mfish_koi_peck_process_init() {
    return;
}

void mfish_koi_peck_process() {
    return;
}

void mfish_koi_long_move_process_init() {
    return;
}

void mfish_koi_long_move_process() {
    return;
}

void mfish_koi_base_FishMove() {
    return;
}

void mfish_koi_base_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_koi_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_koi_before_disp() {
    return;
}

void mfish_koi_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_kaseki_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_kaseki_normal_init() {
    return;
}

void mfish_kaseki_normal() {
    return;
}

void mfish_kaseki_move_wall_smooth() {
    return;
}

void mfish_kaseki_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_kaseki_before_disp() {
    return;
}

void mfish_kaseki_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_bass_tail_anim_set(MUSEUM_FISH_PRIVATE_DATA* actor, s32 r4) {
    if (r4 == 0) {
        actor->_640 = 0xf;
        actor->_5B4 = 4;
    } else if (r4 == 1 && actor->_640 == 0) {
        actor->_640 = 0x14;
        actor->_5B4 = 3;
    }
}

void mfish_bass_base_FishMove(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    f32 t;
    xyz_t pos;
    add_calc2(&actor->_5E8, actor->_5AC, 1 - actor->init_data._18, 0.01f + 0.001f * GETREG(TAKREG, 20));
    actor->_5D0 = actor->_5E8 * sin_s(actor->_60C.z);
    actor->_5D8 = actor->_5E8 * cos_s(actor->_60C.z);

    add_calc(&actor->_5D4, MAX(ABS(actor->_5E8 * sin_s(actor->_60C.x)), 0.1f), 0.1f, 0.1f, 0.005f);
    t = add_calc(&actor->_5A0.y, actor->_5F4 + actor->init_data._0C, 0.1f, actor->_5D4, 0);
    if (fabsf(t) < 0.08f) {
        add_calc_short_angle2(&actor->_612.x, 0, 1.0f - sqrtf(0.97), DEG2SHORT_ANGLE(1.0f + (0.5f * actor->_5B0)) >> 1,
                              9);
    }
    mfish_move_smooth(actor, game);
    mfish_get_flow_vec(&pos, actor, game);
    actor->_5A0.y += actor->_5D0 + actor->_5DC.x;
    actor->_5A0.z += actor->_5D0 + actor->_5DC.x;
    actor->_5A0.y = actor->_5A0.y + actor->_5DC.y;
    actor->_5A0.y = MAX(60, MIN(110, actor->_5A0.y));
}

void mfish_bass_dummy_process_init(MUSEUM_FISH_PRIVATE_DATA* actor) {
    actor->_634 = mfish_get_hide_camera_angle(actor);

    if ((actor->_62E & 0x1E) != 0) {
        // works with temp instead of cast
        if ((s16)(actor->_612.z - actor->_62C) > 0) {
            actor->_634 = actor->_62C + DEG2SHORT_ANGLE(90);
        } else {
            actor->_634 = actor->_62C - DEG2SHORT_ANGLE(90);
        }
    } else {
        add_calc_short_angle2(&actor->_634, actor->_612.z, 1.0f - sqrtf(0.5), DEG2SHORT_ANGLE(22.5), 0x5b);
    }

    actor->_5EC = 0.0f;
    actor->_34 = &mfish_bass_dummy_process;

    return;
}

void mfish_bass_dummy_process(MUSEUM_FISH_PRIVATE_DATA* actor) {
    // no clue what's going on here
    add_calc_short_angle2(&actor->_612.z, actor->_634, 1.0f - sqrtf(1.0f - (1.0f - sqrtf(1.0f))), 0x1c7, 0x2d);
    actor->_622 =
        add_calc_short_angle2(&actor->_60C.z, actor->_612.z, 1.0f - sqrtf(1.0f - (1.0f - sqrtf(0.75))), 0xe3, 0x2d);
    add_calc_short_angle2(&actor->_61C, actor->_622, 1.0f - sqrtf(1.0f - (1.0f - sqrtf(0.75))), 0xe3, 0x2d);
}

void mfish_bass_normal_process_init(MUSEUM_FISH_PRIVATE_DATA* fishActor) {
    f32 ra;
    f32 t;
    f32 temp;

    ra = fqrand() * fishActor->init_data._14 + fishActor->init_data._10;
    t = (ra) / MAX(fishActor->init_data._14 + fishActor->init_data._10, 1);

    if (fqrand() > 0.25f && !(fishActor->_62E & 0x200)) {
        fishActor->_62E |= 0x200;
    } else {
        fishActor->_62E &= ~0x200;
    }

    if (ra > fishActor->_5E8) {
        f32 v2;
        fishActor->_5F0 = ra;
        fishActor->_5AC = 0.15f + Rnd_EX_fx(0.1f);
        mfish_bass_tail_anim_set(fishActor, 0);
    }

    fishActor->_5F4 = t * Rnd_EX_fx(10);
    temp = (fishActor->_5F4 + fishActor->init_data._0C - fishActor->_5A0.y);
    fishActor->_612.x = DEG2SHORT_ANGLE2(temp * -(2 * fishActor->_5B0 + 10));

    fishActor->_612.x = CLAMP(fishActor->_612.x, DEG2SHORT_ANGLE(-50), DEG2SHORT_ANGLE(50));
    fishActor->_5D4 = 0;

    if (fqrand() > fishActor->init_data._1C) {
        int diff;

        fishActor->_612.z += (s16)Rnd_EX_fx(fishActor->init_data._30 * 2.0f);
        diff = fishActor->_612.z - fishActor->_60C.z;
        if (ABS((s16)diff) < DEG2SHORT_ANGLE(20)) {
            if ((s16)diff > 0) {
                fishActor->_612.z += DEG2SHORT_ANGLE(20);
            } else {
                fishActor->_612.z += DEG2SHORT_ANGLE(-20);
            }
        }

        if ((fishActor->_62E & 0x200) == 0) {
            fishActor->_632 = DEG2SHORT_ANGLE(t * 15 + 20);
        } else {
            fishActor->_632 = DEG2SHORT_ANGLE(t * 30 + 20);
        }
    } else {
        if ((s16)(fishActor->_612.z - fishActor->_60C.z) > 0) {
            fishActor->_612.z += DEG2SHORT_ANGLE(15);
        } else {
            fishActor->_612.z += DEG2SHORT_ANGLE(-15);
        }

        if ((fishActor->_62E & 0x200) == 0) {
            fishActor->_632 = DEG2SHORT_ANGLE(t * 15 + 20);
        } else {
            fishActor->_632 = DEG2SHORT_ANGLE((GETREG(TAKREG, 42) + 40.0f) * t + 30);
        }
    }
    if ((s16)(fishActor->_612.z - fishActor->_60C.z) > 0) {
        fishActor->_636 = DEG2SHORT_ANGLE(0);
    } else {
        fishActor->_636 = DEG2SHORT_ANGLE(-180);
    }

    fishActor->_62E &= ~0xC0;
    fishActor->_5EC = 0;
    fishActor->_34 = mfish_bass_normal_process;
}

void mfish_bass_normal_process(MUSEUM_FISH_PRIVATE_DATA* actorx) {
    return;
}

void mfish_bass_turn_process_init() {
    return;
}

void mfish_bass_turn_process() {
    return;
}

void mfish_bass_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;

    mfish_onefish_ct(actor, gamex);
    mfish_base_ct(actor, gamex);

    actor->_34 = mfish_bass_normal_process;

    if (actor->_59C == 7) {
        actor->_5B0 = 0;
    } else if (actor->_59C == 6) {
        actor->_5B0 = 0.5f;
    } else {
        actor->_5B0 = 1;
    }

    actor->_624 = 0xb;

    return;
}

void mfish_bass_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_bass_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    YET_SKELETON* skele;
    Mtx* mtx;
    GRAPH* graph;
    GAME_PLAY* play;

    play = (GAME_PLAY*)gamex;

    skele = &actor->_38;

    if (play->game.frame_counter % 2 != 0) {
        mtx = &skele->_70;
    } else {
        mtx = &skele->_2b0;
    }

    graph = play->game.graph;

    Matrix_translate(actor->_5A0.x, actor->_5A0.y, actor->_5A0.z, 0);
    Matrix_RotateY(actor->_60C.z, 1);

    Matrix_translate(0, 0.25f * actor->init_data._04, 0.5f * actor->init_data._24, 1);
    Matrix_RotateX(actor->_60C.x, 1);
    Matrix_RotateZ(MY_CLAMP(-(actor->_61C >> 1), DEG2SHORT_ANGLE(-20), DEG2SHORT_ANGLE(20)), 1);
    Matrix_translate(0, 0.25f * -actor->init_data._04, 0.5f * -actor->init_data._24, 1);
    Matrix_scale(actor->init_data._00, actor->init_data._00, actor->init_data._00, 1);

    OPEN_DISP(graph);
    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(play->game.graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    CLOSE_DISP(graph);

    cKF_Si3_draw_R_SV(&play->game, &skele->_00, mtx, &mfish_before_disp, 0, actor);
    return;
}

void mfish_seafish_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_seafish_normal_init() {
    return;
}

void mfish_seafish_normal() {
    return;
}

void mfish_seafish_turn_init() {
    return;
}

void mfish_seafish_turn() {
    return;
}

void mfish_seafish_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_seafish_before_disp() {
    return;
}

void mfish_seafish_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_tai_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_tai_normal_init() {
    return;
}

void mfish_tai_normal() {
    return;
}

void mfish_tai_turn_init() {
    return;
}

void mfish_tai_turn() {
    return;
}

void mfish_tai_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_tai_before_disp() {
    return;
}

void mfish_tai_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_small_fish_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_sfish_normal_init() {
    return;
}

void mfish_sfish_normal() {
    return;
}

void mfish_sfish_turn_init() {
    return;
}

void mfish_sfish_turn() {
    return;
}

void mfish_small_fish_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_sfish_before_disp() {
    return;
}

void mfish_small_fish_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_gupi_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_gupi_normal_init() {
    return;
}

void mfish_gupi_normal() {
    return;
}

void mfish_gupi_turn_init() {
    return;
}

void mfish_gupi_turn() {
    return;
}

void mfish_gupi_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_gupi_before_disp() {
    return;
}

void mfish_gupi_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_medaka_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_medaka_normal_init() {
    return;
}

void mfish_medaka_normal() {
    return;
}

void mfish_medaka_turn_init() {
    return;
}

void mfish_medaka_turn() {
    return;
}

void mfish_medaka_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_medaka_before_disp() {
    return;
}

void mfish_medaka_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_kingyo_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_kingyo_normal_init() {
    return;
}

void mfish_kingyo_normal() {
    return;
}

void mfish_kingyo_turn_init() {
    return;
}

void mfish_kingyo_turn() {
    return;
}

void mfish_kingyo_peck_init() {
    return;
}

void mfish_kingyo_peck() {
    return;
}

void mfish_kingyo_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_kingyo_before_disp() {
    return;
}

void mfish_kingyo_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_dojou_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_dojou_normal_init() {
    return;
}

void mfish_dojou_normal() {
    return;
}

void mfish_dojou_turn_init() {
    return;
}

void mfish_dojou_turn() {
    return;
}

void mfish_dojou_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_dojou_before_disp() {
    return;
}

void mfish_dojou_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_donko_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_donko_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_donko_before_disp() {
    return;
}

void mfish_donko_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_big_fish_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_big_fish_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_bfish_before_disp() {
    return;
}

void mfish_big_fish_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_ito_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_ito_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_ito_before_disp() {
    return;
}

void mfish_ito_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_unagi_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_unagi_get_next_rail_type() {
    return;
}

void mfish_unagi_aim_wind_angle_calc() {
    return;
}

void mfish_unagi_rail_move_init() {
    return;
}

void mfish_unagi_rail_move() {
    return;
}

void mfish_unagi_normal_to_reverse_init() {
    return;
}

void mfish_unagi_normal_to_reverse() {
    return;
}

void mfish_unagi_rail_move_reverse_init() {
    return;
}

void mfish_unagi_rail_move_reverse() {
    return;
}

void mfish_unagi_reverse_to_normal_init() {
    return;
}

void mfish_unagi_reverse_to_normal() {
    return;
}

void mfish_unagi_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_unagi_before_disp() {
    return;
}

void mfish_unagi_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_namazu_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_namazu_body_wind_anime_play() {
    return;
}

void mfish_namazu_normal_process_init() {
    return;
}

void mfish_namazu_normal_process() {
    return;
}

void mfish_namazu_dummy_process_init() {
    return;
}

void mfish_namazu_dummy_process() {
    return;
}

void mfish_namazu_turn_process_init() {
    return;
}

void mfish_namazu_turn_process() {
    return;
}

void mfish_namazu_ground_sweep_process_init() {
    return;
}

void mfish_namazu_ground_sweep_process() {
    return;
}

void mfish_namazu_base_FishMove() {
    return;
}

void mfish_namazu_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_namazu_before_disp() {
    return;
}

void mfish_namazu_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_zarigani_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_zarigani_normal_process_init() {
    return;
}

void mfish_zarigani_normal_process() {
    return;
}

void mfish_zarigani_wait_process_init() {
    return;
}

void mfish_zarigani_wait_process() {
    return;
}

void mfish_zarigani_stand_process_init() {
    return;
}

void mfish_zarigani_stand_process() {
    return;
}

void mfish_zarigani_jump_process_init() {
    return;
}

void mfish_zarigani_jump_process() {
    return;
}

void mfish_zarigani_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_zarigani_before_disp() {
    return;
}

void mfish_zarigani_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_kurage_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_kurage_normal_init() {
    return;
}

void mfish_kurage_normal() {
    return;
}

void mfish_kurage_turn_init() {
    return;
}

void mfish_kurage_turn() {
    return;
}

void mfish_kurage_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_kurage_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_hasu_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_hasu_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_hasu_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_kaeru_ct(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {
    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void mfish_kaeru_mv(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}

void hasu_before_disp() {
    return;
}

void hasu_after_disp() {
    return;
}

void mfish_kaeru_dw(MUSEUM_FISH_PRIVATE_DATA* actor, GAME* gamex) {

    GAME_PLAY* game = (GAME_PLAY*)gamex;
    return;
}
