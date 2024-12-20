#include "ac_museum_fish.h"
#include "m_demo.h"
#include "m_name_table.h"
#include "m_item_name.h"
#include "m_msg.h"
#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_player_lib.h"
#include "m_debug_mode.h"
#include "libforest/gbi_extensions.h"
#include "m_rcp.h"
#include "ac_gyoei.h"

// found useful macros
#define MY_MAX(a, b) (((a) >= (b)) ? (a) : (b))
#define MY_CLAMP(v, l, h) MIN(MY_MAX((l), (v)), (h))
#define ARRAY_LEN(a) (sizeof(a) / sizeof(*a))

#define CALC_EASE(x) (1 - sqrtf(1 - (x)))
#define CALC_EASE2(x) CALC_EASE(CALC_EASE(x))
#define SHORT2DEG_ANGLE2(x) ((x) * (360.0f / 65536.0f))
#define RANDOMF_RANGE(min, max) ((f32)(min) + (f32)RANDOM_F((f32)(max) - (f32)(min)))
#define RANDOM2F_RANGE(min, max) ((f32)(min) + (f32)RANDOM2_F((f32)(max) - (f32)(min)))
#define RANDOM_RANGE(min, max) ((int)(min) + (int)RANDOM((int)(max) - (int)(min)))
#define RANDOM2_RANGE(min, max) ((int)(min) + (int)RANDOM2((int)(max) - (int)(min)))

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

static xyz_t suisou_pos[5] = { 
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

    actor->_5A0.y = mfish_init_data[fishNum]._0C + RANDOM2_F(10);
    if (r6 == 1) {
        actor->_5A0.x += RANDOM2_F(90);
        actor->_5A0.z += RANDOM2_F(90);
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
        actor->prvKusa[i]._54C = kusa_model[i];
        cKF_SkeletonInfo_R_ct(&actor->prvKusa[i]._00, kusa_model[i], kusa_anime[i], &actor->prvKusa[i]._4F0,
                              &actor->prvKusa[i]._514);
        cKF_SkeletonInfo_R_init_standard_repeat_speedsetandmorph(&actor->prvKusa[i]._00, kusa_anime[i], NULL,
                                                                 kusa_group_tbl[i] == 2 ? 1.5f : 0.5f, 0.0f);
        actor->prvKusa[i]._00.frame_control.current_frame = kusa_start_frame[i];
        actor->prvKusa[i]._538.x = qrand();
        actor->prvKusa[i]._538.z = qrand();
        // actor->_101f0[i * 2 + 2] = qrand();
    }

    if (mMmd_FishInfo(0x21)) {
        actor->prvFish[0x21]._590 = &actor->_14788;
    } else {
        mfish_hasu_ct(&actor->_14788, gamex);
    }

    prv = actor->prvFish;
    for (i = 0; i < 40; i++, prv++) {
        prv->_62E &= ~1;
        if (mMmd_FishInfo(i)) {
            prv->_38._54C = mfish_model_tbl[i];
            prv->_38._550[0] = mfish_anime_init_tbl[i];
            prv->_62E |= 1;
            Museum_Fish_Prv_data_init(prv, gamex, i, 1);
        }
    }

    for (i = 0; i < 20; i++) {
        actor->_14d50[i] = RANDOMF_RANGE(80, 120);
        actor->_14d78[i] = RANDOMF_RANGE(2, 5);
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

void Museum_Fish_Talk_process(ACTOR* actorx, GAME* game) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;

    if (mDemo_Check(8, actorx) != 0) {
        GAME_PLAY* _gamePT;
        PLAYER_ACTOR* playerActor = get_player_actor_withoutCheck((GAME_PLAY*)game);
        s_xyz rotation = playerActor->actor_class.shape_info.rotation;
        add_calc_short_angle2(&rotation.y, DEG2SHORT_ANGLE(-180), 0.3f, DEG2SHORT_ANGLE(22.5f), 0);

        _gamePT = (GAME_PLAY*)gamePT;
        get_player_actor_withoutCheck(_gamePT)->Set_force_position_angle_proc(&_gamePT->game, NULL, &rotation, 32);
        if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p()) != 0) {
            int choseNum = mChoice_Get_ChoseNum(mChoice_Get_base_window_p());
            if (choseNum != -1) {
                if (choseNum == 0) {
                    mMsg_Window_c* windowC;
                    int msgNum = Museum_Fish_GetMsgNo(actorx);
                    actor->fishDisplayMsgIter += 1;
                    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), msgNum);
                    mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
                } else {
                    mMsg_Set_CancelNormalContinue(mMsg_Get_base_window_p());
                    mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
                }
            }
        }
    } else {
        if (chkTrigger(BUTTON_A) != 0 && mDemo_Get_talk_actor() == 0) {
            int i;
            for (i = 0; i < 5; i++) {
                if (Museum_Fish_Check_Talk_Distance(game, i)) {
                    Museum_Fish_Set_MsgFishInfo(actorx, i);
                    mDemo_Request(8, actorx, &Museum_Fish_set_talk_info);
                }
            }
        }
    }
    // line 16C

    return;
}

void Museum_Fish_Actor_move(ACTOR* actorx, GAME* game) {
    int i;
    int j;
    MUSEUM_FISH_PRIVATE_DATA* prv;
    s16 old_14db4;
    f32 v;
    GAME_PLAY* play = (GAME_PLAY*)game;
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;

    mfish_point_light_mv(actor, &play->game);
    old_14db4 = actor->_14db4;
    mfish_get_player_area(actor, &play->game);

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
                prv->_626 = RANDOM_F(60);
            }
        }
    }

    for (j = 0; j < 14; j++) {
        cKF_SkeletonInfo_R_play(&actor->prvKusa[j]._00);
        if (kusa_group_tbl[j] == 2) {
            add_calc2(&actor->prvKusa[j]._540.x, -2.25f, 1.75f, 1.75f);
            add_calc_short_angle2(&actor->prvKusa[j]._538.y, DEG2SHORT_ANGLE(3.5f), CALC_EASE2(0.1f), 22, 4);
        } else {
            actor->prvKusa[j]._540.x *= 0.9f;
            add_calc_short_angle2(&actor->prvKusa[j]._538.y, DEG2SHORT_ANGLE(0), CALC_EASE2(0.1f), 22, 4);
        }
        actor->prvKusa[j]._540.z *= 0.98f;

        actor->prvKusa[j]._538.x += actor->prvKusa[j]._538.y;
        actor->prvKusa[j]._538.z += actor->prvKusa[j]._538.y >> 1;

        add_calc_short_angle2(&actor->prvKusa[j]._538.y, DEG2SHORT_ANGLE(0), CALC_EASE2(0.1f), 22, 4);
    }

    Museum_Fish_Kusa_Check(actor, &play->game);
    Museum_Fish_Object_Check(actor, &play->game);

    for (i = 0; i < 20; i++) {
        actor->_14d50[i]--;
        if (actor->_14d50[i] < 0) {
            common_data.clip.effect_clip->effect_make_proc(0x6e, suisou_awa_pos[i], 2, 0, &play->game, -1,
                                                           suisou_awa_group[i], 0);
            if (actor->_14d78[i] > 0) {
                actor->_14d78[i]--;
                actor->_14d50[i] = RANDOMF_RANGE(2, 10);
            } else {
                actor->_14d50[i] = RANDOMF_RANGE(160, 240);
                actor->_14d78[i] = RANDOMF_RANGE(2, 5);
            }
        }
    }

    Museum_Fish_Talk_process(actorx, game);

    {
        // needs a new variable
        MUSEUM_FISH_PRIVATE_DATA* prv = actor->prvFish;
        for (i = 0; i < 40; i++, prv++) {
            if (prv->_62E & 1) {
                mfish_mv[i](prv, game);
            }
        }
    }

    if ((actor->prvFish[0x21]._62E & 1) == 0) {
        mfish_hasu_mv((MUSEUM_FISH_PRIVATE_DATA*)&actor->_14788, game);
    }

    for (i = 0; i < 5; i++) {
        if (i == 2) {
            actor->_14daa[i] += (s16)DEG2SHORT_ANGLE2((float)GETREG(TAKREG, 31) * 0.1f + 0.5f + RANDOM_F(1));
        } else {
            actor->_14daa[i] += 8;
        }
    }
}

extern Gfx obj_suisou1_model[];
extern Gfx obj_suisou1_modelT[];

extern Gfx obj_museum5_model[];
extern Gfx obj_museum5_modelT[];

void Museum_Fish_Suisou_draw(ACTOR* actorx, GAME* game, int r5) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;
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

            gSPDisplayList(NEXT_POLY_OPA_DISP, obj_suisou1_model);
            gSPDisplayList(NEXT_POLY_XLU_DISP, obj_suisou1_modelT);

            CLOSE_DISP(graph);

            if ((actor->prvFish[0x21]._62E & 1) == 0) {
                mfish_hasu_dw((MUSEUM_FISH_PRIVATE_DATA*)&actor->_14788, game);
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

BOOL kusa_before_disp(GAME* game, cKF_SkeletonInfo_R_c* keyframe, int joint_num, Gfx** mjoint_m, u8* joint_f, void* arg,
                      s_xyz* joint1, xyz_t* trans) {
    MUSEUM_FISH_KUSA_DATA* actor = (MUSEUM_FISH_KUSA_DATA*)arg;
    if (joint_num > 0) {
        f32 v = (actor->_54C == &cKF_bs_r_obj_museum5_kusa3) ? 35.0f : 20.f;

        joint1->y += (s16)(sin_s(actor->_538.x + (joint_num * DEG2SHORT_ANGLE(90))) * 1274.0f);
        joint1->x += (s16)(sin_s(actor->_538.z + (joint_num * DEG2SHORT_ANGLE(90))) * 4369.0f);

        trans->y -= actor->_540.x * (v * joint_num);
        trans->z += actor->_540.z * (v * joint_num);
    }
    return TRUE;
}

void Museum_Fish_Kusa_Draw(ACTOR* actorx, GAME* game, int r5) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    if (mfish_cull_check(game, &kusa_pos[r5], 0.0f, 0.0f, 120.0f)) {
        Mtx* mtx;
        if (play->game.frame_counter % 2 != 0) {
            mtx = &actor->prvKusa[r5]._70;
        } else {
            mtx = &actor->prvKusa[r5]._2b0;
        }
        OPEN_DISP(game->graph);
        Matrix_translate(kusa_pos[r5].x, 0, kusa_pos[r5].z, 0);
        Matrix_scale(0.01f, 0.01f, 0.01f, 1);
        gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        CLOSE_DISP(game->graph);
        cKF_Si3_draw_R_SV(game, &actor->prvKusa[r5]._00, mtx, kusa_before_disp, NULL, &actor->prvKusa[r5]);
    }
}

extern EVW_ANIME_DATA obj_suisou1_evw_anime, obj_museum5_evw_anime;
extern Gfx act_mus_fish_set_mode;
void Museum_Fish_Actor_draw(ACTOR* actorx, GAME* game) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    int i;

    _texture_z_light_fog_prim(game->graph);
    _texture_z_light_fog_prim_xlu(game->graph);

    if (!GETREG(TAKREG, 90)) {
        for (i = 0; i < 14; i++) {
            Museum_Fish_Kusa_Draw(actorx, game, i);
        }
    }

    if (!GETREG(TAKREG, 92)) {
        MUSEUM_FISH_PRIVATE_DATA* prv;
        GRAPH* graph;
        graph = play->game.graph;
        OPEN_DISP(graph);
        gSPDisplayList(NEXT_POLY_OPA_DISP, &act_mus_fish_set_mode);
        CLOSE_DISP(graph);

        prv = actor->prvFish;
        for (i = 0; i < 40; i++, prv++) {
            if (prv->_62E & 1 && prv->_59C != 0x23 && prv->_59C != 0x21 &&
                mfish_cull_check(game, &prv->_5B8, prv->init_data._08 + 50.0f, prv->init_data._08 + 10.0f,
                                 prv->init_data._08 + 10.0f)) {
                mfish_dw[i](prv, game);
            }
        }

        if (actor->prvFish[0x23]._62E & 1 &&
            mfish_cull_check(game, &actor->prvFish[0x23]._5A0, actor->prvFish[0x23].init_data._08 + 10.0f,
                             actor->prvFish[0x23].init_data._04, actor->prvFish[0x23].init_data._04)) {
            mfish_dw[0x23](&actor->prvFish[0x23], game);
        }

        if (!GETREG(TAKREG, 82)) {
            mfish_normal_light_set(actorx, game);
        }

        if (actor->prvFish[0x21]._62E & 1) {
            mfish_dw[0x21](&actor->prvFish[0x21], game);
        }

        if (GETREG(TAKREG, 82) == 1) {
            mfish_normal_light_set(actorx, game);
        }
    }

    if (!GETREG(TAKREG, 91)) {
        if (!GETREG(TAKREG, 88)) {
            Evw_Anime_Set(play, &obj_museum5_evw_anime);
            Museum_Fish_Suisou_draw(actorx, game, 0x5);
        }

        for (i = 0; i < 4; i++) {
            Evw_Anime_Set(play, &obj_suisou1_evw_anime);
            Museum_Fish_Suisou_draw(actorx, game, i);
        }
    }
}

BOOL mfish_cull_check(GAME* game, xyz_t* worldPos, f32 x, f32 y, f32 _y) {
    xyz_t screenPos;
    Game_play_Projection_Trans((GAME_PLAY*)game, worldPos, &screenPos);
    if ((-x < screenPos.x) && (screenPos.x < x + 320) && (-y < screenPos.y) && (screenPos.y < _y + 240)) {
        return TRUE;
    }
    return FALSE;
}

void mfish_point_ligh_pos_get(ACTOR* actorx, GAME* game, int r5) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    f32 a, b, c, d;
    xyz_t _30;
    xyz_t _24;
    xyz_t _18;
    xyz_t _0c;

    int r;
    f32 v;
    PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);

    _30 = player->actor_class.world.position;

    if (_30.z < 100.0f) {
        r = 4;
    } else if (_30.z > 100.0f && _30.z < 340.0f) {
        if (r5 == 0) {
            r = 0;
        } else {
            r = 1;
        }
    } else if (_30.z > 340.0f && _30.z < 580.0f) {
        if (r5 == 0) {
            r = 2;
        } else {
            r = 3;
        }
    } else {
        return;
    }

    if (r < 4) {
        a = 60.0f;
        b = 60.0f;
        c = 60.0f;
        d = 60.0f;
        _0c = suisou_pos[r];
        _18 = _30;
    } else {
        a = 200.0f;
        c = 35.0f;
        d = 20.0f;
        b = 200.0f;
        _0c = suisou_pos[r];
        _18 = _30;
        if (r5 == 0) {
            _18.x -= d;
        } else {
            _18.x += d;
        }
    }

    if (_18.x > _0c.x + a) {
        _18.x = _0c.x + a;
    } else if (_18.x < _0c.x - b) {
        _18.x = _0c.x - b;
    }

    if (_18.z > _0c.z + c) {
        _18.z = _0c.z + c;
    } else if (_18.z < _0c.z - d) {
        _18.z = _0c.z - d;
    }

    actor->_14d08[r5] = _18;

    xyz_t_sub(&_18, &_30, &_24);

    v = sqrtf(_24.x * _24.x + _24.z * _24.z);

    actor->_14dbc[r5] = (u8)(((60.0f - CLAMP(v, 0.0f, 60.0f)) / 60.0f) * 55.0f);
}

void mfish_point_light_ct(ACTOR* actorx, GAME* game) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    mfish_point_ligh_pos_get(&actor->actor, game, 0);
    mfish_point_ligh_pos_get(&actor->actor, game, 1);
    actor->_14db8 = mEnv_ReservePointLight(play, &actor->_14d08[0], 0, 0x96, 0xff, (u8)actor->_14dbc[0]);
    actor->_14dba = mEnv_ReservePointLight(play, &actor->_14d08[1], 0, 0x96, 0xff, (u8)actor->_14dbc[1]);
    actor->_14dc0 = 0;
}

void mfish_point_light_dt(ACTOR* actorx, GAME* game) {
    MUSEUM_FISH_ACTOR* actor = (MUSEUM_FISH_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (actor->_14db8 != -1) {
        mEnv_CancelReservedPointLight(actor->_14db8, (GAME_PLAY*)game);
    }

    if (actor->_14dba != -1) {
        mEnv_CancelReservedPointLight(actor->_14dba, (GAME_PLAY*)game);
    }
}

void mfish_point_light_mv(MUSEUM_FISH_ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    mfish_point_ligh_pos_get(&actor->actor, game, 0);
    mfish_point_ligh_pos_get(&actor->actor, game, 1);

    mEnv_OperateReservedPointLight(actor->_14db8, &actor->_14d08[0], 0, 0x96, 0xff, (u8)actor->_14dbc[0]);
    mEnv_OperateReservedPointLight(actor->_14dba, &actor->_14d08[1], 0, 0x96, 0xff, (u8)actor->_14dbc[1]);
    actor->actor.world.position = actor->_14d08[0];
    actor->actor.world.position.x = sin_s(actor->_14dc0) * 200.0f;
    actor->actor.world.position.y = sin_s(actor->_14dc0 * 2) * 10.0f;
    actor->actor.world.position.z = cos_s(actor->_14dc0) * 200.0f;
    actor->_14dc0 += 0x111;
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

#include "../src/actor/ac_museum_fish_base.c_inc"
#include "../src/actor/ac_museum_fish_afish.c_inc"
#include "../src/actor/ac_museum_fish_aroana.c_inc"
#include "../src/actor/ac_museum_fish_koi.c_inc"
#include "../src/actor/ac_museum_fish_kaseki.c_inc"
#include "../src/actor/ac_museum_fish_bass.c_inc"
#include "../src/actor/ac_museum_fish_seafish.c_inc"
#include "../src/actor/ac_museum_fish_tai.c_inc"
#include "../src/actor/ac_museum_fish_small_fish.c_inc"
#include "../src/actor/ac_museum_fish_gupi.c_inc"
#include "../src/actor/ac_museum_fish_medaka.c_inc"
#include "../src/actor/ac_museum_fish_kingyo.c_inc"
#include "../src/actor/ac_museum_fish_dojou.c_inc"
#include "../src/actor/ac_museum_fish_donko.c_inc"
#include "../src/actor/ac_museum_fish_big_fish.c_inc"
#include "../src/actor/ac_museum_fish_ito.c_inc"
#include "../src/actor/ac_museum_fish_unagi.c_inc"
#include "../src/actor/ac_museum_fish_namazu.c_inc"
#include "../src/actor/ac_museum_fish_zarigani.c_inc"
#include "../src/actor/ac_museum_fish_kurage.c_inc"
#include "../src/actor/ac_museum_fish_hasu.c_inc"
