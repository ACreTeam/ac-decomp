#include "ac_set_ovl_gyoei.h"

#include "m_field_info.h"
#include "m_collision_bg.h"
#include "m_random_field_h.h"
#include "libc64/qrand.h"
#include "libultra/libultra.h"
#include "m_field_assessment.h"
#include "m_field_make.h"
#include "m_common_data.h"
#include "m_play.h"
#include "m_event.h"
#include "m_kankyo.h"
#include "m_time.h"

/* sizeof(aSOG_term_info_c) == 4 */
typedef struct term_info_s {
  /* 0x00 */ s16 type; /* fish type (aGYO_TYPE_*) */
  /* 0x02 */ u8 spawn_area; /* spawn area (aSOG_SPAWN_AREA_*) */
  /* 0x03 */ u8 weight; /* weight value */
} aSOG_term_info_c;

/* sizeof (aSOG_term_list_c) == 8 */
typedef struct term_list_s {
  /* 0x00 */ u8 count; /* number of term info items */
  /* 0x04 */ aSOG_term_info_c* term_info; /* pointer to term info items */
} aSOG_term_list_c;

#define FISH_SPAWN(fish, area, weight) { aGYO_TYPE_##fish, aSOG_SPAWN_AREA_##area, weight }

static aSOG_term_info_c r_m1_t0[14] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 5),
  FISH_SPAWN(BROOK_TROUT, POOL, 5),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(SMALL_BASS, RIVER, 3),
  FISH_SPAWN(BASS, RIVER, 2),
  FISH_SPAWN(LARGE_BASS, RIVER, 1),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(DACE, RIVER, 10),
  FISH_SPAWN(BITTERLING, RIVER, 20),
  FISH_SPAWN(POND_SMELT, RIVER, 40),
  FISH_SPAWN(STRINGFISH, RIVER, 1),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
};

static aSOG_term_info_c s_m1_t0[2] = {
  FISH_SPAWN(SEA_BASS, SEA, 20),
  FISH_SPAWN(RED_SNAPPER, SEA, 3),
};

static aSOG_term_info_c r_m1_t1[14] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 7),
  FISH_SPAWN(BROOK_TROUT, POOL, 5),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(SMALL_BASS, RIVER, 3),
  FISH_SPAWN(BASS, RIVER, 3),
  FISH_SPAWN(LARGE_BASS, RIVER, 2),
  FISH_SPAWN(BLUEGILL, RIVER, 2),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(PALE_CHUB, RIVER, 5),
  FISH_SPAWN(BITTERLING, RIVER, 20),
  FISH_SPAWN(POND_SMELT, RIVER, 40),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(POPEYED_GOLDFISH, RIVER, 1),
};

static aSOG_term_info_c r_m1_t2[14] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 5),
  FISH_SPAWN(BROOK_TROUT, POOL, 5),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(SMALL_BASS, RIVER, 3),
  FISH_SPAWN(BASS, RIVER, 2),
  FISH_SPAWN(LARGE_BASS, RIVER, 1),
  FISH_SPAWN(BARBEL_STEED, RIVER, 15),
  FISH_SPAWN(DACE, RIVER, 15),
  FISH_SPAWN(BITTERLING, RIVER, 15),
  FISH_SPAWN(POND_SMELT, RIVER, 30),
  FISH_SPAWN(STRINGFISH, RIVER, 1),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
};

static aSOG_term_list_c r_begining_january[aSOG_TIME_NUM] = {
  { 14, r_m1_t2 },
  { 14, r_m1_t0 },
  { 14, r_m1_t1 },
  { 14, r_m1_t0 }
};

static aSOG_term_list_c s_begining_january[aSOG_TIME_NUM] = {
  { 2, s_m1_t0 },
  { 2, s_m1_t0 },
  { 2, s_m1_t0 },
  { 2, s_m1_t0 }
};

static aSOG_term_info_c r_m2_t0[14] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 5),
  FISH_SPAWN(BROOK_TROUT, POOL, 5),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(SMALL_BASS, RIVER, 3),
  FISH_SPAWN(BASS, RIVER, 2),
  FISH_SPAWN(LARGE_BASS, RIVER, 1),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(DACE, RIVER, 10),
  FISH_SPAWN(BITTERLING, RIVER, 20),
  FISH_SPAWN(POND_SMELT, RIVER, 40),
  FISH_SPAWN(STRINGFISH, RIVER, 1),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
};

static aSOG_term_info_c s_m2_t0[2] = {
  FISH_SPAWN(SEA_BASS, SEA, 20),
  FISH_SPAWN(RED_SNAPPER, SEA, 3),
};

static aSOG_term_info_c r_m2_t1[14] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 7),
  FISH_SPAWN(BROOK_TROUT, POOL, 5),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(SMALL_BASS, RIVER, 3),
  FISH_SPAWN(BASS, RIVER, 3),
  FISH_SPAWN(LARGE_BASS, RIVER, 2),
  FISH_SPAWN(BLUEGILL, RIVER, 2),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(PALE_CHUB, RIVER, 5),
  FISH_SPAWN(BITTERLING, RIVER, 20),
  FISH_SPAWN(POND_SMELT, RIVER, 40),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(POPEYED_GOLDFISH, RIVER, 1),
};

static aSOG_term_info_c r_m2_t2[14] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 5),
  FISH_SPAWN(BROOK_TROUT, POOL, 5),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(SMALL_BASS, RIVER, 3),
  FISH_SPAWN(BASS, RIVER, 2),
  FISH_SPAWN(LARGE_BASS, RIVER, 1),
  FISH_SPAWN(BARBEL_STEED, RIVER, 15),
  FISH_SPAWN(DACE, RIVER, 15),
  FISH_SPAWN(BITTERLING, RIVER, 15),
  FISH_SPAWN(POND_SMELT, RIVER, 30),
  FISH_SPAWN(STRINGFISH, RIVER, 1),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
};

static aSOG_term_list_c r_begining_february[aSOG_TIME_NUM] = {
  { 14, r_m2_t2 },
  { 14, r_m2_t0 },
  { 14, r_m2_t1 },
  { 14, r_m2_t0 }
};

static aSOG_term_list_c s_begining_february[aSOG_TIME_NUM] = {
  { 2, s_m2_t0 },
  { 2, s_m2_t0 },
  { 2, s_m2_t0 },
  { 2, s_m2_t0 }
};

static aSOG_term_info_c r_m3_t0[15] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 11),
  FISH_SPAWN(BROOK_TROUT, POOL, 10),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(SMALL_BASS, RIVER, 3),
  FISH_SPAWN(BASS, RIVER, 2),
  FISH_SPAWN(LARGE_BASS, RIVER, 1),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(DACE, RIVER, 5),
  FISH_SPAWN(LOACH, RIVER, 25),
  FISH_SPAWN(CHERRY_SALMON, RIVER, 10),
  FISH_SPAWN(LARGE_CHAR, WATERFALL, 10),
  FISH_SPAWN(RAINBOW_TROUT, RIVER, 10),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
};

static aSOG_term_info_c s_m3_t0[3] = {
  FISH_SPAWN(SEA_BASS, SEA, 20),
  FISH_SPAWN(RED_SNAPPER, SEA, 10),
  FISH_SPAWN(BARRED_KNIFEJAW, SEA, 5),
};

static aSOG_term_info_c r_m3_t1[13] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 22),
  FISH_SPAWN(BROOK_TROUT, POOL, 15),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(SMALL_BASS, RIVER, 3),
  FISH_SPAWN(BASS, RIVER, 3),
  FISH_SPAWN(LARGE_BASS, RIVER, 2),
  FISH_SPAWN(BLUEGILL, RIVER, 2),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(PALE_CHUB, RIVER, 5),
  FISH_SPAWN(LOACH, RIVER, 35),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(POPEYED_GOLDFISH, RIVER, 1),
};

static aSOG_term_info_c r_m3_t2[12] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 21),
  FISH_SPAWN(BROOK_TROUT, POOL, 10),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(SMALL_BASS, RIVER, 3),
  FISH_SPAWN(BASS, RIVER, 2),
  FISH_SPAWN(LARGE_BASS, RIVER, 1),
  FISH_SPAWN(BARBEL_STEED, RIVER, 15),
  FISH_SPAWN(DACE, RIVER, 15),
  FISH_SPAWN(LOACH, RIVER, 25),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
};

static aSOG_term_list_c r_begining_march[aSOG_TIME_NUM] = {
  { 12, r_m3_t2 },
  { 15, r_m3_t0 },
  { 13, r_m3_t1 },
  { 15, r_m3_t0 }
};

static aSOG_term_list_c s_begining_march[aSOG_TIME_NUM] = {
  { 3, s_m3_t0 },
  { 3, s_m3_t0 },
  { 3, s_m3_t0 },
  { 3, s_m3_t0 }
};

static aSOG_term_info_c r_m4_t0[16] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 10),
  FISH_SPAWN(BROOK_TROUT, POOL, 10),
  FISH_SPAWN(CARP, RIVER, 14),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(SMALL_BASS, RIVER, 5),
  FISH_SPAWN(BASS, RIVER, 3),
  FISH_SPAWN(LARGE_BASS, RIVER, 2),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(DACE, RIVER, 5),
  FISH_SPAWN(LOACH, RIVER, 10),
  FISH_SPAWN(CHERRY_SALMON, RIVER, 10),
  FISH_SPAWN(LARGE_CHAR, WATERFALL, 10),
  FISH_SPAWN(RAINBOW_TROUT, RIVER, 10),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(KILLIFISH, RIVER, 1),
};

static aSOG_term_info_c s_m4_t0[3] = {
  FISH_SPAWN(SEA_BASS, SEA, 20),
  FISH_SPAWN(RED_SNAPPER, SEA, 15),
  FISH_SPAWN(BARRED_KNIFEJAW, SEA, 7),
};

static aSOG_term_info_c p_m4_t0[2] = {
  FISH_SPAWN(KILLIFISH, POND, 3),
  FISH_SPAWN(CRAWFISH, POND, 20),
};

static aSOG_term_info_c r_m4_t1[15] = {
 FISH_SPAWN(CRUCIAN_CARP, RIVER, 24),
  FISH_SPAWN(BROOK_TROUT, POOL, 15),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(SMALL_BASS, RIVER, 5),
  FISH_SPAWN(BASS, RIVER, 3),
  FISH_SPAWN(LARGE_BASS, RIVER, 2),
  FISH_SPAWN(BLUEGILL, RIVER, 2),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(PALE_CHUB, RIVER, 10),
  FISH_SPAWN(LOACH, RIVER, 24),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(GUPPY, RIVER, 1),
  FISH_SPAWN(POPEYED_GOLDFISH, RIVER, 1),
  FISH_SPAWN(KILLIFISH, RIVER, 1),
};

static aSOG_term_info_c r_m4_t2[13] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 20),
  FISH_SPAWN(BROOK_TROUT, POOL, 10),
  FISH_SPAWN(CARP, RIVER, 14),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(SMALL_BASS, RIVER, 5),
  FISH_SPAWN(BASS, RIVER, 3),
  FISH_SPAWN(LARGE_BASS, RIVER, 2),
  FISH_SPAWN(BARBEL_STEED, RIVER, 15),
  FISH_SPAWN(DACE, RIVER, 15),
  FISH_SPAWN(LOACH, RIVER, 10),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(KILLIFISH, RIVER, 1),
};

static aSOG_term_list_c r_begining_april[aSOG_TIME_NUM] = {
  { 13, r_m4_t2 },
  { 16, r_m4_t0 },
  { 15, r_m4_t1 },
  { 16, r_m4_t0 }
};

static aSOG_term_list_c s_begining_april[aSOG_TIME_NUM] = {
  { 3, s_m4_t0 },
  { 3, s_m4_t0 },
  { 3, s_m4_t0 },
  { 3, s_m4_t0 }
};

static aSOG_term_list_c p_begining_april[aSOG_TIME_NUM] = {
  { 2, p_m4_t0 },
  { 2, p_m4_t0 },
  { 2, p_m4_t0 },
  { 2, p_m4_t0 }
};

static aSOG_term_info_c r_m5_t0[18] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 11),
  FISH_SPAWN(BROOK_TROUT, POOL, 10),
  FISH_SPAWN(CARP, RIVER, 14),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(CATFISH, RIVER, 2),
  FISH_SPAWN(SMALL_BASS, RIVER, 5),
  FISH_SPAWN(BASS, RIVER, 15),
  FISH_SPAWN(LARGE_BASS, RIVER, 5),
  FISH_SPAWN(BARBEL_STEED, RIVER, 3),
  FISH_SPAWN(DACE, RIVER, 5),
  FISH_SPAWN(LOACH, RIVER, 3),
  FISH_SPAWN(CHERRY_SALMON, RIVER, 5),
  FISH_SPAWN(LARGE_CHAR, WATERFALL, 10),
  FISH_SPAWN(RAINBOW_TROUT, RIVER, 5),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(ANGELFISH, RIVER, 1),
  FISH_SPAWN(KILLIFISH, RIVER, 1),
};

static aSOG_term_info_c s_m5_t0[3] = {
  FISH_SPAWN(SEA_BASS, SEA, 20),
  FISH_SPAWN(RED_SNAPPER, SEA, 15),
  FISH_SPAWN(BARRED_KNIFEJAW, SEA, 7),
};

static aSOG_term_info_c p_m5_t0[3] = {
  FISH_SPAWN(KILLIFISH, POND, 3),
  FISH_SPAWN(CRAWFISH, POND, 20),
  FISH_SPAWN(FROG, POND, 15),
};

static aSOG_term_info_c r_m5_t1[15] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 18),
  FISH_SPAWN(BROOK_TROUT, POOL, 15),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(SMALL_BASS, RIVER, 20),
  FISH_SPAWN(BASS, RIVER, 5),
  FISH_SPAWN(LARGE_BASS, RIVER, 2),
  FISH_SPAWN(BLUEGILL, RIVER, 10),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(PALE_CHUB, RIVER, 10),
  FISH_SPAWN(LOACH, RIVER, 5),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(GUPPY, RIVER, 1),
  FISH_SPAWN(POPEYED_GOLDFISH, RIVER, 1),
  FISH_SPAWN(KILLIFISH, RIVER, 1),
};

static aSOG_term_info_c r_m5_t2[15] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 16),
  FISH_SPAWN(BROOK_TROUT, POOL, 10),
  FISH_SPAWN(CARP, RIVER, 14),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(CATFISH, RIVER, 5),
  FISH_SPAWN(SMALL_BASS, RIVER, 5),
  FISH_SPAWN(BASS, RIVER, 15),
  FISH_SPAWN(LARGE_BASS, RIVER, 5),
  FISH_SPAWN(BARBEL_STEED, RIVER, 10),
  FISH_SPAWN(DACE, RIVER, 10),
  FISH_SPAWN(LOACH, RIVER, 3),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(ANGELFISH, RIVER, 1),
  FISH_SPAWN(KILLIFISH, RIVER, 1),
};

static aSOG_term_list_c r_begining_may[aSOG_TIME_NUM] = {
  { 15, r_m5_t2 },
  { 18, r_m5_t0 },
  { 15, r_m5_t1 },
  { 18, r_m5_t0 }
};

static aSOG_term_list_c s_begining_may[aSOG_TIME_NUM] = {
  { 3, s_m5_t0 },
  { 3, s_m5_t0 },
  { 3, s_m5_t0 },
  { 3, s_m5_t0 }
};

static aSOG_term_list_c p_begining_may[aSOG_TIME_NUM] = {
  { 3, p_m5_t0 },
  { 3, p_m5_t0 },
  { 3, p_m5_t0 },
  { 3, p_m5_t0 }
};

static aSOG_term_info_c r_m6_t0[20] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 7),
  FISH_SPAWN(BROOK_TROUT, POOL, 5),
  FISH_SPAWN(CARP, RIVER, 14),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(CATFISH, RIVER, 5),
  FISH_SPAWN(SMALL_BASS, RIVER, 5),
  FISH_SPAWN(BASS, RIVER, 15),
  FISH_SPAWN(LARGE_BASS, RIVER, 5),
  FISH_SPAWN(GIANT_CATFISH, POOL, 5),
  FISH_SPAWN(BARBEL_STEED, RIVER, 3),
  FISH_SPAWN(DACE, RIVER, 3),
  FISH_SPAWN(CHERRY_SALMON, RIVER, 5),
  FISH_SPAWN(LARGE_CHAR, WATERFALL, 10),
  FISH_SPAWN(RAINBOW_TROUT, RIVER, 5),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(AROWANA, RIVER, 1),
  FISH_SPAWN(EEL, RIVER, 5),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(ANGELFISH, RIVER, 1),
  FISH_SPAWN(KILLIFISH, RIVER, 1),
};

static aSOG_term_info_c s_m6_t0[] = {
  FISH_SPAWN(SEA_BASS, SEA, 20),
  FISH_SPAWN(RED_SNAPPER, SEA, 15),
  FISH_SPAWN(BARRED_KNIFEJAW, SEA, 5),
};

static aSOG_term_info_c p_m6_t0[] = {
  FISH_SPAWN(KILLIFISH, POND, 3),
  FISH_SPAWN(CRAWFISH, POND, 20),
  FISH_SPAWN(FROG, POND, 15),
};

static aSOG_term_info_c r_m6_t1[16] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 17),
  FISH_SPAWN(BROOK_TROUT, POOL, 15),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(SMALL_BASS, RIVER, 20),
  FISH_SPAWN(BASS, RIVER, 5),
  FISH_SPAWN(LARGE_BASS, RIVER, 2),
  FISH_SPAWN(BLUEGILL, RIVER, 10),
  FISH_SPAWN(GIANT_SNAKEHEAD, POOL, 5),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(PALE_CHUB, RIVER, 10),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(PIRANHA, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(GUPPY, RIVER, 1),
  FISH_SPAWN(POPEYED_GOLDFISH, RIVER, 1),
  FISH_SPAWN(KILLIFISH, RIVER, 1),
};

static aSOG_term_info_c r_m6_t2[17] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 5),
  FISH_SPAWN(BROOK_TROUT, POOL, 5),
  FISH_SPAWN(CARP, RIVER, 5),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(CATFISH, RIVER, 29),
  FISH_SPAWN(SMALL_BASS, RIVER, 5),
  FISH_SPAWN(BASS, RIVER, 10),
  FISH_SPAWN(LARGE_BASS, RIVER, 5),
  FISH_SPAWN(GIANT_CATFISH, POOL, 10),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(DACE, RIVER, 3),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(PIRANHA, RIVER, 1),
  FISH_SPAWN(EEL, RIVER, 10),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(ANGELFISH, RIVER, 1),
  FISH_SPAWN(KILLIFISH, RIVER, 1),
};

static aSOG_term_list_c r_begining_june[aSOG_TIME_NUM] = {
  { 17, r_m6_t2 },
  { 20, r_m6_t0 },
  { 16, r_m6_t1 },
  { 20, r_m6_t0 }
};

static aSOG_term_list_c s_begining_june[aSOG_TIME_NUM] = {
  { 3, s_m6_t0 },
  { 3, s_m6_t0 },
  { 3, s_m6_t0 },
  { 3, s_m6_t0 }
};

static aSOG_term_list_c p_begining_june[aSOG_TIME_NUM] = {
  { 3, p_m6_t0 },
  { 3, p_m6_t0 },
  { 3, p_m6_t0 },
  { 3, p_m6_t0 }
};

static aSOG_term_info_c r_m7_t0[19] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 7),
  FISH_SPAWN(BROOK_TROUT, POOL, 5),
  FISH_SPAWN(CARP, RIVER, 5),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(CATFISH, RIVER, 5),
  FISH_SPAWN(SMALL_BASS, RIVER, 5),
  FISH_SPAWN(BASS, RIVER, 15),
  FISH_SPAWN(LARGE_BASS, RIVER, 5),
  FISH_SPAWN(GIANT_CATFISH, POOL, 10),
  FISH_SPAWN(BARBEL_STEED, RIVER, 3),
  FISH_SPAWN(DACE, RIVER, 3),
  FISH_SPAWN(SWEETFISH, RIVER, 23),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(AROWANA, RIVER, 1),
  FISH_SPAWN(EEL, RIVER, 5),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(ANGELFISH, RIVER, 1),
  FISH_SPAWN(KILLIFISH, RIVER, 1),
  FISH_SPAWN(ARAPAIMA, RIVER, 1),
};

static aSOG_term_info_c s_m7_t0[3] = {
  FISH_SPAWN(SEA_BASS, SEA, 20),
  FISH_SPAWN(RED_SNAPPER, SEA, 10),
  FISH_SPAWN(BARRED_KNIFEJAW, SEA, 3),
};

static aSOG_term_info_c p_m7_t0[3] = {
  FISH_SPAWN(KILLIFISH, POND, 3),
  FISH_SPAWN(CRAWFISH, POND, 20),
  FISH_SPAWN(FROG, POND, 15),
};

static aSOG_term_info_c r_m7_t1[17] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 8),
  FISH_SPAWN(BROOK_TROUT, POOL, 5),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(SMALL_BASS, RIVER, 15),
  FISH_SPAWN(BASS, RIVER, 5),
  FISH_SPAWN(LARGE_BASS, RIVER, 2),
  FISH_SPAWN(BLUEGILL, RIVER, 10),
  FISH_SPAWN(GIANT_SNAKEHEAD, POOL, 10),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(PALE_CHUB, RIVER, 5),
  FISH_SPAWN(SWEETFISH, RIVER, 24),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(PIRANHA, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(GUPPY, RIVER, 1),
  FISH_SPAWN(POPEYED_GOLDFISH, RIVER, 1),
  FISH_SPAWN(KILLIFISH, RIVER, 1),
};

static aSOG_term_info_c r_m7_t2[19] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 7),
  FISH_SPAWN(BROOK_TROUT, POOL, 5),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(CATFISH, RIVER, 23),
  FISH_SPAWN(SMALL_BASS, RIVER, 5),
  FISH_SPAWN(BASS, RIVER, 5),
  FISH_SPAWN(LARGE_BASS, RIVER, 5),
  FISH_SPAWN(GIANT_CATFISH, POOL, 10),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(DACE, RIVER, 3),
  FISH_SPAWN(SWEETFISH, RIVER, 5),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(PIRANHA, RIVER, 1),
  FISH_SPAWN(EEL, RIVER, 15),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(ANGELFISH, RIVER, 1),
  FISH_SPAWN(KILLIFISH, RIVER, 1),
  FISH_SPAWN(ARAPAIMA, RIVER, 1),
};

static aSOG_term_list_c r_begining_july[aSOG_TIME_NUM] = {
  { 19, r_m7_t2 },
  { 19, r_m7_t0 },
  { 17, r_m7_t1 },
  { 19, r_m7_t0 }
};

static aSOG_term_list_c s_begining_july[aSOG_TIME_NUM] = {
  { 3, s_m7_t0 },
  { 3, s_m7_t0 },
  { 3, s_m7_t0 },
  { 3, s_m7_t0 }
};

static aSOG_term_list_c p_begining_july[aSOG_TIME_NUM] = {
  { 3, p_m7_t0 },
  { 3, p_m7_t0 },
  { 3, p_m7_t0 },
  { 3, p_m7_t0 }
};

static aSOG_term_info_c r_m8_t0[19] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 7),
  FISH_SPAWN(BROOK_TROUT, POOL, 5),
  FISH_SPAWN(CARP, RIVER, 5),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(CATFISH, RIVER, 5),
  FISH_SPAWN(SMALL_BASS, RIVER, 5),
  FISH_SPAWN(BASS, RIVER, 15),
  FISH_SPAWN(LARGE_BASS, RIVER, 5),
  FISH_SPAWN(GIANT_CATFISH, POOL, 10),
  FISH_SPAWN(BARBEL_STEED, RIVER, 3),
  FISH_SPAWN(DACE, RIVER, 3),
  FISH_SPAWN(SWEETFISH, RIVER, 23),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(AROWANA, RIVER, 1),
  FISH_SPAWN(EEL, RIVER, 5),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(ANGELFISH, RIVER, 1),
  FISH_SPAWN(KILLIFISH, RIVER, 1),
  FISH_SPAWN(ARAPAIMA, RIVER, 1),
};

static aSOG_term_info_c s_m8_t0[3] = {
  FISH_SPAWN(SEA_BASS, SEA, 20),
  FISH_SPAWN(RED_SNAPPER, SEA, 10),
  FISH_SPAWN(BARRED_KNIFEJAW, SEA, 3),
};

static aSOG_term_info_c s_m8_t0_2[3] = {
  FISH_SPAWN(JELLYFISH, SEA, 77),
  FISH_SPAWN(RED_SNAPPER, SEA, 10),
  FISH_SPAWN(BARRED_KNIFEJAW, SEA, 3),
};

static aSOG_term_info_c p_m8_t0[3] = {
  FISH_SPAWN(KILLIFISH, POND, 3),
  FISH_SPAWN(CRAWFISH, POND, 20),
  FISH_SPAWN(FROG, POND, 15),
};

static aSOG_term_info_c r_m8_t1[17] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 8),
  FISH_SPAWN(BROOK_TROUT, POOL, 5),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(SMALL_BASS, RIVER, 15),
  FISH_SPAWN(BASS, RIVER, 5),
  FISH_SPAWN(LARGE_BASS, RIVER, 2),
  FISH_SPAWN(BLUEGILL, RIVER, 10),
  FISH_SPAWN(GIANT_SNAKEHEAD, POOL, 10),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(PALE_CHUB, RIVER, 5),
  FISH_SPAWN(SWEETFISH, RIVER, 24),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(PIRANHA, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(GUPPY, RIVER, 1),
  FISH_SPAWN(POPEYED_GOLDFISH, RIVER, 1),
  FISH_SPAWN(KILLIFISH, RIVER, 1),
};

static aSOG_term_info_c s_m8_t1_2[3] = {
  FISH_SPAWN(JELLYFISH, SEA, 87),
  FISH_SPAWN(RED_SNAPPER, SEA, 10),
  FISH_SPAWN(BARRED_KNIFEJAW, SEA, 3),
};

static aSOG_term_info_c r_m8_t2[19] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 7),
  FISH_SPAWN(BROOK_TROUT, POOL, 5),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(CATFISH, RIVER, 23),
  FISH_SPAWN(SMALL_BASS, RIVER, 5),
  FISH_SPAWN(BASS, RIVER, 5),
  FISH_SPAWN(LARGE_BASS, RIVER, 5),
  FISH_SPAWN(GIANT_CATFISH, POOL, 10),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(DACE, RIVER, 3),
  FISH_SPAWN(SWEETFISH, RIVER, 5),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(PIRANHA, RIVER, 1),
  FISH_SPAWN(EEL, RIVER, 15),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(ANGELFISH, RIVER, 1),
  FISH_SPAWN(KILLIFISH, RIVER, 1),
  FISH_SPAWN(ARAPAIMA, RIVER, 1),
};

static aSOG_term_list_c r_begining_august[aSOG_TIME_NUM] = {
  { 19, r_m8_t2 },
  { 19, r_m8_t0 },
  { 17, r_m8_t1 },
  { 19, r_m8_t0 }
};

static aSOG_term_list_c s_begining_august[aSOG_TIME_NUM] = {
  { 3, s_m8_t0 },
  { 3, s_m8_t0 },
  { 3, s_m8_t0 },
  { 3, s_m8_t0 }
};

static aSOG_term_list_c s_latter_august[aSOG_TIME_NUM] = {
  { 3, s_m8_t0_2 },
  { 3, s_m8_t0_2 },
  { 3, s_m8_t1_2 },
  { 3, s_m8_t0_2 }
};

static aSOG_term_list_c p_begining_august[aSOG_TIME_NUM] = {
  { 3, p_m8_t0 },
  { 3, p_m8_t0 },
  { 3, p_m8_t0 },
  { 3, p_m8_t0 }
};

static aSOG_term_info_c r_m9_t0[20] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 8),
  FISH_SPAWN(BROOK_TROUT, POOL, 5),
  FISH_SPAWN(CARP, RIVER, 5),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(CATFISH, RIVER, 5),
  FISH_SPAWN(SMALL_BASS, RIVER, 5),
  FISH_SPAWN(BASS, RIVER, 15),
  FISH_SPAWN(LARGE_BASS, RIVER, 5),
  FISH_SPAWN(BARBEL_STEED, RIVER, 3),
  FISH_SPAWN(DACE, RIVER, 3),
  FISH_SPAWN(SWEETFISH, RIVER, 5),
  FISH_SPAWN(CHERRY_SALMON, RIVER, 10),
  FISH_SPAWN(LARGE_CHAR, WATERFALL, 10),
  FISH_SPAWN(RAINBOW_TROUT, RIVER, 10),
  FISH_SPAWN(GOLDFISH, RIVER, 2),
  FISH_SPAWN(AROWANA, RIVER, 1),
  FISH_SPAWN(EEL, RIVER, 2),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(ANGELFISH, RIVER, 1),
  FISH_SPAWN(ARAPAIMA, RIVER, 1),
};

static aSOG_term_info_c r_m9_t0_2[18] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 4),
  FISH_SPAWN(BROOK_TROUT, POOL, 5),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(CATFISH, RIVER, 3),
  FISH_SPAWN(SMALL_BASS, RIVER, 3),
  FISH_SPAWN(BASS, RIVER, 3),
  FISH_SPAWN(LARGE_BASS, RIVER, 2),
  FISH_SPAWN(BARBEL_STEED, RIVER, 3),
  FISH_SPAWN(DACE, RIVER, 3),
  FISH_SPAWN(CHERRY_SALMON, RIVER, 5),
  FISH_SPAWN(LARGE_CHAR, WATERFALL, 5),
  FISH_SPAWN(RAINBOW_TROUT, RIVER, 5),
  FISH_SPAWN(SALMON, RIVER, 49),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(ANGELFISH, RIVER, 1),
  FISH_SPAWN(ARAPAIMA, RIVER, 1),
};

static aSOG_term_info_c s_m9_t0[] = {
  FISH_SPAWN(SALMON2, RIVER_MOUTH, 75), // river mouth salmon variant
  FISH_SPAWN(RED_SNAPPER, SEA, 10),
  FISH_SPAWN(BARRED_KNIFEJAW, SEA, 5),
};

static aSOG_term_info_c s_m9_t0_2[] = {
  FISH_SPAWN(SEA_BASS, SEA, 20),
  FISH_SPAWN(RED_SNAPPER, SEA, 10),
  FISH_SPAWN(BARRED_KNIFEJAW, SEA, 7),
};

static aSOG_term_info_c p_m9_t0[] = {
  FISH_SPAWN(CRAWFISH, POND, 20),
};

static aSOG_term_info_c r_m9_t1[15] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 16),
  FISH_SPAWN(BROOK_TROUT, POOL, 15),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(SMALL_BASS, RIVER, 20),
  FISH_SPAWN(BASS, RIVER, 5),
  FISH_SPAWN(LARGE_BASS, RIVER, 2),
  FISH_SPAWN(BLUEGILL, RIVER, 10),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(PALE_CHUB, RIVER, 10),
  FISH_SPAWN(SWEETFISH, RIVER, 5),
  FISH_SPAWN(GOLDFISH, RIVER, 2),
  FISH_SPAWN(PIRANHA, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(GUPPY, RIVER, 1),
  FISH_SPAWN(POPEYED_GOLDFISH, RIVER, 2),
};

static aSOG_term_info_c r_m9_t1_2[14] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 6),
  FISH_SPAWN(BROOK_TROUT, POOL, 10),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(SMALL_BASS, RIVER, 5),
  FISH_SPAWN(BASS, RIVER, 3),
  FISH_SPAWN(LARGE_BASS, RIVER, 2),
  FISH_SPAWN(BLUEGILL, RIVER, 5),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(PALE_CHUB, RIVER, 5),
  FISH_SPAWN(SALMON, RIVER, 50),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(GUPPY, RIVER, 1),
  FISH_SPAWN(POPEYED_GOLDFISH, RIVER, 1),
};

static aSOG_term_info_c s_m9_t1[3] = {
  FISH_SPAWN(SALMON2, RIVER_MOUTH, 85), // river mouth salmon variant
  FISH_SPAWN(RED_SNAPPER, SEA, 10),
  FISH_SPAWN(BARRED_KNIFEJAW, SEA, 5),
};

static aSOG_term_info_c r_m9_t2[17] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 16),
  FISH_SPAWN(BROOK_TROUT, POOL, 5),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(CATFISH, RIVER, 24),
  FISH_SPAWN(SMALL_BASS, RIVER, 5),
  FISH_SPAWN(BASS, RIVER, 15),
  FISH_SPAWN(LARGE_BASS, RIVER, 5),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(DACE, RIVER, 3),
  FISH_SPAWN(SWEETFISH, RIVER, 5),
  FISH_SPAWN(GOLDFISH, RIVER, 2),
  FISH_SPAWN(PIRANHA, RIVER, 1),
  FISH_SPAWN(EEL, RIVER, 5),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(ANGELFISH, RIVER, 1),
  FISH_SPAWN(ARAPAIMA, RIVER, 1),
};

static aSOG_term_info_c r_m9_t2_2[15] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 5),
  FISH_SPAWN(BROOK_TROUT, POOL, 5),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(CATFISH, RIVER, 15),
  FISH_SPAWN(SMALL_BASS, RIVER, 3),
  FISH_SPAWN(BASS, RIVER, 3),
  FISH_SPAWN(LARGE_BASS, RIVER, 2),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(DACE, RIVER, 3),
  FISH_SPAWN(SALMON, RIVER, 49),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(ANGELFISH, RIVER, 1),
  FISH_SPAWN(ARAPAIMA, RIVER, 1),
};

static aSOG_term_list_c r_begining_september[aSOG_TIME_NUM] = {
  { 17, r_m9_t2 },
  { 20, r_m9_t0 },
  { 15, r_m9_t1 },
  { 20, r_m9_t0 }
};

static aSOG_term_list_c r_latter_september[aSOG_TIME_NUM] = {
  { 15, r_m9_t2_2 },
  { 18, r_m9_t0_2 },
  { 14, r_m9_t1_2 },
  { 18, r_m9_t0_2 }
};

static aSOG_term_list_c s_begining_september[aSOG_TIME_NUM] = {
  { 3, s_m9_t0 },
  { 3, s_m9_t0 },
  { 3, s_m9_t1 },
  { 3, s_m9_t0 }
};

static aSOG_term_list_c s_latter_september[aSOG_TIME_NUM] = {
  { 3, s_m9_t0_2 },
  { 3, s_m9_t0_2 },
  { 3, s_m9_t0_2 },
  { 3, s_m9_t0_2 }
};

static aSOG_term_list_c p_begining_september[aSOG_TIME_NUM] = {
  { 1, p_m9_t0 },
  { 1, p_m9_t0 },
  { 1, p_m9_t0 },
  { 1, p_m9_t0 }
};

static aSOG_term_info_c r_m10_t0[16] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 6),
  FISH_SPAWN(BROOK_TROUT, POOL, 10),
  FISH_SPAWN(CARP, RIVER, 15),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(CATFISH, RIVER, 2),
  FISH_SPAWN(SMALL_BASS, RIVER, 5),
  FISH_SPAWN(BASS, RIVER, 15),
  FISH_SPAWN(LARGE_BASS, RIVER, 5),
  FISH_SPAWN(BARBEL_STEED, RIVER, 3),
  FISH_SPAWN(DACE, RIVER, 3),
  FISH_SPAWN(CHERRY_SALMON, RIVER, 10),
  FISH_SPAWN(LARGE_CHAR, WATERFALL, 10),
  FISH_SPAWN(RAINBOW_TROUT, RIVER, 10),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(ANGELFISH, RIVER, 1),
};

static aSOG_term_info_c s_m10_t0[3] = {
  FISH_SPAWN(SEA_BASS, SEA, 20),
  FISH_SPAWN(RED_SNAPPER, SEA, 10),
  FISH_SPAWN(BARRED_KNIFEJAW, SEA, 7),
};

static aSOG_term_info_c r_m10_t1[13] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 24),
  FISH_SPAWN(BROOK_TROUT, POOL, 15),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(SMALL_BASS, RIVER, 20),
  FISH_SPAWN(BASS, RIVER, 5),
  FISH_SPAWN(LARGE_BASS, RIVER, 2),
  FISH_SPAWN(BLUEGILL, RIVER, 10),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(PALE_CHUB, RIVER, 10),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(GUPPY, RIVER, 1),
  FISH_SPAWN(POPEYED_GOLDFISH, RIVER, 1),
};

static aSOG_term_info_c r_m10_t2[13] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 19),
  FISH_SPAWN(BROOK_TROUT, POOL, 10),
  FISH_SPAWN(CARP, RIVER, 15),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(CATFISH, RIVER, 5),
  FISH_SPAWN(SMALL_BASS, RIVER, 5),
  FISH_SPAWN(BASS, RIVER, 15),
  FISH_SPAWN(LARGE_BASS, RIVER, 5),
  FISH_SPAWN(BARBEL_STEED, RIVER, 10),
  FISH_SPAWN(DACE, RIVER, 10),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(ANGELFISH, RIVER, 1),
};

static aSOG_term_list_c r_begining_october[aSOG_TIME_NUM] = {
  { 13, r_m10_t2 },
  { 16, r_m10_t0 },
  { 13, r_m10_t1 },
  { 16, r_m10_t0 }
};

static aSOG_term_list_c s_begining_october[aSOG_TIME_NUM] = {
  { 3, s_m10_t0 },
  { 3, s_m10_t0 },
  { 3, s_m10_t0 },
  { 3, s_m10_t0 }
};

static aSOG_term_info_c r_m11_t0[14] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 15),
  FISH_SPAWN(BROOK_TROUT, POOL, 10),
  FISH_SPAWN(CARP, RIVER, 15),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(SMALL_BASS, RIVER, 5),
  FISH_SPAWN(BASS, RIVER, 15),
  FISH_SPAWN(LARGE_BASS, RIVER, 5),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(DACE, RIVER, 5),
  FISH_SPAWN(CHERRY_SALMON, RIVER, 5),
  FISH_SPAWN(LARGE_CHAR, WATERFALL, 10),
  FISH_SPAWN(RAINBOW_TROUT, RIVER, 5),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
};

static aSOG_term_info_c s_m11_t0[3] = {
  FISH_SPAWN(SEA_BASS, SEA, 20),
  FISH_SPAWN(RED_SNAPPER, SEA, 5),
  FISH_SPAWN(BARRED_KNIFEJAW, SEA, 5),
};

static aSOG_term_info_c r_m11_t1[13] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 24),
  FISH_SPAWN(BROOK_TROUT, POOL, 15),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(SMALL_BASS, RIVER, 20),
  FISH_SPAWN(BASS, RIVER, 5),
  FISH_SPAWN(LARGE_BASS, RIVER, 2),
  FISH_SPAWN(BLUEGILL, RIVER, 10),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(PALE_CHUB, RIVER, 10),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(GUPPY, RIVER, 1),
  FISH_SPAWN(POPEYED_GOLDFISH, RIVER, 1),
};

static aSOG_term_info_c r_m11_t2[11] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 15),
  FISH_SPAWN(BROOK_TROUT, POOL, 10),
  FISH_SPAWN(CARP, RIVER, 15),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(SMALL_BASS, RIVER, 5),
  FISH_SPAWN(BASS, RIVER, 15),
  FISH_SPAWN(LARGE_BASS, RIVER, 5),
  FISH_SPAWN(BARBEL_STEED, RIVER, 15),
  FISH_SPAWN(DACE, RIVER, 15),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
};

static aSOG_term_list_c r_begining_november[aSOG_TIME_NUM] = {
  { 11, r_m11_t2 },
  { 14, r_m11_t0 },
  { 13, r_m11_t1 },
  { 14, r_m11_t0 }
};

static aSOG_term_list_c s_begining_november[aSOG_TIME_NUM] = {
  { 3, s_m11_t0 },
  { 3, s_m11_t0 },
  { 3, s_m11_t0 },
  { 3, s_m11_t0 }
};

static aSOG_term_info_c r_m12_t0[14] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 5),
  FISH_SPAWN(BROOK_TROUT, POOL, 5),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(SMALL_BASS, RIVER, 3),
  FISH_SPAWN(BASS, RIVER, 2),
  FISH_SPAWN(LARGE_BASS, RIVER, 1),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(DACE, RIVER, 10),
  FISH_SPAWN(BITTERLING, RIVER, 20),
  FISH_SPAWN(POND_SMELT, RIVER, 40),
  FISH_SPAWN(STRINGFISH, RIVER, 1),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
};

static aSOG_term_info_c s_m12_t0[2] = {
  FISH_SPAWN(SEA_BASS, SEA, 20),
  FISH_SPAWN(RED_SNAPPER, SEA, 3),
};

static aSOG_term_info_c r_m12_t1[14] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 7),
  FISH_SPAWN(BROOK_TROUT, POOL, 5),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(SMALL_BASS, RIVER, 3),
  FISH_SPAWN(BASS, RIVER, 3),
  FISH_SPAWN(LARGE_BASS, RIVER, 2),
  FISH_SPAWN(BLUEGILL, RIVER, 2),
  FISH_SPAWN(BARBEL_STEED, RIVER, 5),
  FISH_SPAWN(PALE_CHUB, RIVER, 5),
  FISH_SPAWN(BITTERLING, RIVER, 20),
  FISH_SPAWN(POND_SMELT, RIVER, 40),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
  FISH_SPAWN(POPEYED_GOLDFISH, RIVER, 1),
};

static aSOG_term_info_c r_m12_t2[14] = {
  FISH_SPAWN(CRUCIAN_CARP, RIVER, 5),
  FISH_SPAWN(BROOK_TROUT, POOL, 5),
  FISH_SPAWN(CARP, RIVER, 3),
  FISH_SPAWN(KOI, RIVER, 1),
  FISH_SPAWN(SMALL_BASS, RIVER, 3),
  FISH_SPAWN(BASS, RIVER, 2),
  FISH_SPAWN(LARGE_BASS, RIVER, 1),
  FISH_SPAWN(BARBEL_STEED, RIVER, 15),
  FISH_SPAWN(DACE, RIVER, 15),
  FISH_SPAWN(BITTERLING, RIVER, 15),
  FISH_SPAWN(POND_SMELT, RIVER, 30),
  FISH_SPAWN(STRINGFISH, RIVER, 1),
  FISH_SPAWN(GOLDFISH, RIVER, 1),
  FISH_SPAWN(FRESHWATER_GOBY, RIVER, 3),
};

static aSOG_term_list_c r_begining_december[aSOG_TIME_NUM] = {
  { 14, r_m12_t2 },
  { 14, r_m12_t0 },
  { 14, r_m12_t1 },
  { 14, r_m12_t0 }
};

static aSOG_term_list_c s_begining_december[aSOG_TIME_NUM] = {
  { 2, s_m12_t0 },
  { 2, s_m12_t0 },
  { 2, s_m12_t0 },
  { 2, s_m12_t0 }
};

static aSOG_term_info_c f_bs_t0[3] = {
  FISH_SPAWN(SMALL_BASS, RIVER, 10),
  FISH_SPAWN(BASS, RIVER, 70),
  FISH_SPAWN(LARGE_BASS, RIVER, 20),
};

static aSOG_term_info_c f_bs_t1[3] = {
  FISH_SPAWN(SMALL_BASS, RIVER, 50),
  FISH_SPAWN(BASS, RIVER, 40),
  FISH_SPAWN(LARGE_BASS, RIVER, 10),
};

static aSOG_term_info_c f_bs_t2[3] = {
  FISH_SPAWN(SMALL_BASS, RIVER, 20),
  FISH_SPAWN(BASS, RIVER, 70),
  FISH_SPAWN(LARGE_BASS, RIVER, 10),
};

static aSOG_term_info_c f_il_t0[3] = {
  FISH_SPAWN(SEA_BASS, SEA, 20),
  FISH_SPAWN(RED_SNAPPER, SEA, 10),
  FISH_SPAWN(BARRED_KNIFEJAW, SEA, 3),
};

static aSOG_term_info_c f_il_t1[3] = {
  FISH_SPAWN(SEA_BASS, SEA, 20),
  FISH_SPAWN(RED_SNAPPER, SEA, 10),
  FISH_SPAWN(BARRED_KNIFEJAW, SEA, 3),
};

static aSOG_term_info_c f_il_t2[3] = {
  FISH_SPAWN(SEA_BASS, SEA, 20),
  FISH_SPAWN(RED_SNAPPER, SEA, 10),
  FISH_SPAWN(BARRED_KNIFEJAW, SEA, 3),
};

/* river fish by month */
static aSOG_term_list_c* r_month[lbRTC_MONTHS_MAX][aSOG_TERM_NUM] = {
  { r_begining_january, r_begining_january },
  { r_begining_february, r_begining_february },
  { r_begining_march, r_begining_march },
  { r_begining_april, r_begining_april },
  { r_begining_may, r_begining_may },
  { r_begining_june, r_begining_june },
  { r_begining_july, r_begining_july },
  { r_begining_august, r_begining_august },
  { r_begining_september, r_latter_september },
  { r_begining_october, r_begining_october },
  { r_begining_november, r_begining_november },
  { r_begining_december, r_begining_december },
};

/* ocean fish by month */
static aSOG_term_list_c* s_month[lbRTC_MONTHS_MAX][aSOG_TERM_NUM] = {
  { s_begining_january, s_begining_january },
  { s_begining_february, s_begining_february },
  { s_begining_march, s_begining_march },
  { s_begining_april, s_begining_april },
  { s_begining_may, s_begining_may },
  { s_begining_june, s_begining_june },
  { s_begining_july, s_begining_july },
  { s_begining_august, s_latter_august },
  { s_begining_september, s_latter_september },
  { s_begining_october, s_begining_october },
  { s_begining_november, s_begining_november },
  { s_begining_december, s_begining_december },
};

/* pond fish by month */
static aSOG_term_list_c* p_month[lbRTC_MONTHS_MAX][aSOG_TERM_NUM] = {
  { NULL, NULL },
  { NULL, NULL },
  { NULL, NULL },
  { p_begining_april, p_begining_april },
  { p_begining_may, p_begining_may },
  { p_begining_june, p_begining_june },
  { p_begining_july, p_begining_july },
  { p_begining_august, p_begining_august },
  { p_begining_september, NULL },
  { NULL, NULL },
  { NULL, NULL },
  { NULL, NULL },
};

static aSOG_term_list_c f_event[aSOG_TIME_NUM] = {
  { 3, f_bs_t2 },
  { 3, f_bs_t0 },
  { 3, f_bs_t1 },
  { 3, f_bs_t0 }
};

static aSOG_term_list_c f_island[aSOG_TIME_NUM] = {
  { 3, f_il_t2 },
  { 3, f_il_t0 },
  { 3, f_il_t1 },
  { 3, f_il_t0 }
};

/* sizeof(aSOG_set_data_c) == 8 */
typedef struct {
  /* 0x00 */ u8 type;
  /* 0x01 */ u8 ut_x;
  /* 0x02 */ u8 ut_z;
  /* 0x03 */ u8 should_spawn;
  /* 0x04 */ int extra_data;
} aSOG_set_data_c;

/* hack to get function-local .bss variables ordered properly */
#ifndef NONMATCHING
static aSOG_set_data_c set_data;
static aSOG_gyoei_spawn_info_weight_f_c copy_range[aSetMgr_GYOEI_NUM];
static u16 fg_idx_table[UT_TOTAL_NUM - 1];
#endif

/**
 * @brief Re-initializes a set data structure.
 * 
 * @param set_data aSOG_set_data_c object to re-initialize
 **/
static void aSOG_gyoei_clear_set_data(aSOG_set_data_c* set_data) {
  set_data->type = 0;
  set_data->ut_x = 0xFF;
  set_data->ut_z = 0xFF;
  set_data->should_spawn = FALSE;
  set_data->extra_data = -1;
}

/**
 * @brief Searches for the first world position of a unit with a 'water' attribute
 * from the supplied wpos.
 * 
 * The area checked is equivalent to one unit, so up to 4 units may be checked.
 * 
 * @param wpos The world position which is both the source and destination
 **/
static void aSOG_get_water_attribute_position(xyz_t* wpos) {
  int utpos_x, utpos_z;

  for (utpos_x = 0; utpos_x < mFI_UT_WORLDSIZE_X; utpos_x++) {
    for (utpos_z = 0; utpos_z < mFI_UT_WORLDSIZE_Z; utpos_z++) {
      int attribute;
      xyz_t unit_pos;
      unit_pos.x = wpos->x + (f32)utpos_x;
      unit_pos.z = wpos->z + (f32)utpos_z;

      attribute = mCoBG_Wpos2BgAttribute_Original(unit_pos);
      if (mCoBG_CheckWaterAttribute(attribute)) {
        wpos->x = unit_pos.x;
        wpos->z = unit_pos.z;
        return;
      }
    }
  }

  /* default to the middle of the unit */
  wpos->x += (mFI_UT_WORLDSIZE_X_F / 2.0f);
  wpos->z += (mFI_UT_WORLDSIZE_Z_F / 2.0f);
}

/**
 * @brief Moves an input world position to the approximate location of the 'waterfall' position.
 * 
 * The input world position will be pointing to a unit which has the waterfall attribute.
 * 
 * @param wpos The input world position
 * @return 
 **/
static void aSOG_get_fall_attribute_position(xyz_t* wpos) {
  int attribute;
  xyz_t unit_pos;
  unit_pos.x = wpos->x + (mFI_UT_WORLDSIZE_X_F / 2.0f); // move over half a unit
  unit_pos.z = wpos->z + (mFI_UT_WORLDSIZE_Z_F / 2.0f) + (mFI_UT_WORLDSIZE_Z_F / 2.0f); // move up one entire unit

  attribute = mCoBG_Wpos2Attribute(unit_pos, NULL);
  if (mCoBG_CheckWaterAttribute(attribute)) {
    wpos->x = unit_pos.x;
    wpos->z = unit_pos.z;
  }
  else {
    wpos->x += (mFI_UT_WORLDSIZE_X_F / 2.0f);
    wpos->z += (mFI_UT_WORLDSIZE_Z_F / 2.0f);
  }
}

/**
 * @brief Checks if an acre has the correct typing for a given spawn type.
 * 
 * @param spawn_area The spawn area type to check
 * @param block_type The typing of the acre being checked
 * @return TRUE when spawn is valid for the acre, FALSE otherwise
 **/
static int aSOG_gyoei_place_check(u8 spawn_area, u32 block_type) {
  int res = TRUE;
  switch (spawn_area) {
    case aSOG_SPAWN_AREA_WATERFALL:
      if ((block_type & mRF_BLOCKKIND_WATERFALL) != mRF_BLOCKKIND_WATERFALL) {
        res = FALSE;
      }
      break;
    
    case aSOG_SPAWN_AREA_POOL:
      if ((block_type & mRF_BLOCKKIND_POOL) != mRF_BLOCKKIND_POOL) {
        res = FALSE;
      }
      break;

    case aSOG_SPAWN_AREA_RIVER_MOUTH:
// Aus version clarifies that 'river mouth' spawns can only spawn in the river & sea block.
#if VERSION >= VER_GAFU01_00
      if ((block_type & (mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_MARINE)) != (mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_MARINE)) {
#else
      if ((block_type & mRF_BLOCKKIND_RIVER) != mRF_BLOCKKIND_RIVER) {
#endif
        res = FALSE;
      }
      break;
  }

  return res;
}

/**
 * @brief Decides the index into the spawn table of the fish which will be spawned (actual logic).
 * 
 * The spawn table can hold multiple of the same fish spawns and work correctly,
 * however that never occurs in the official release.
 * 
 * @param spawn_info Pointer to the possible spawns
 * @param set_table Pointer to list of indicies already tried for spawning
 * @param block_type Current acre type flags
 * @param info_count Number of spawns in spawn_info
 * @param env_rate Town environment rating spawn % modifier rate
 * @return Spawn is invalid: aGYO_TYPE_INVALID/aGYO_TYPE_NUM, otherwise index into the spawn_info table to try spawning
 **/
static int aSOG_gyoei_get_idx_sub(aSOG_gyoei_spawn_info_weight_f_c* spawn_info, int* set_table, u32 block_type, int info_count, f32 env_rate) {
  f32 total_spawn_weight = 0.0f;
  f32 selected_weight;
  f32 now_weight;
  int selected_idx = aGYO_TYPE_INVALID;
  aSOG_gyoei_spawn_info_weight_f_c* spawn_info_p = spawn_info;
  int* set_table_p = set_table;
  int i;

  /* determine total weight of all fish */
  for (i = 0; i < info_count; i++) {
    if (*set_table_p == 0) {
      total_spawn_weight += spawn_info_p->spawn_weight;
    }
    spawn_info_p++;
    set_table_p++;
  }

  /* pick a random point in the total weight */
  selected_weight = total_spawn_weight * fqrand();

  /* go through fish info list until we've hit the desired fish */
  now_weight = total_spawn_weight;
  spawn_info_p = spawn_info;
  set_table_p = set_table;
  for (i = 0; i < info_count; i++) {
    if (*set_table_p == 0) {
      now_weight -= spawn_info_p->spawn_weight * env_rate; // subtract weight modified by environment rating factor
      if (now_weight < 0.0f) {
        break;
      }

      if (selected_weight >= now_weight) {
        *set_table_p = TRUE;
        if (!aSOG_gyoei_place_check(spawn_info_p->spawn_area, block_type)) {
          selected_idx = aGYO_TYPE_NUM;
        }
        else {
          selected_idx = i;
        }

        break;
      }
    }

    spawn_info_p++;
    set_table_p++;
  }

  return selected_idx;
}

/**
 * @brief Decides the index into the spawn table of the fish which will be spawned (setup logic).
 * 
 * @param spawn_info Pointer to the possible spawns
 * @param info_count Number of spawns in spawn_info
 * @param block_type Current acre type flags
 * @return Spawn is invalid: aGYO_TYPE_INVALID/aGYO_TYPE_NUM, otherwise index into the spawn_info table to try spawning
 **/
static int aSOG_gyoei_get_idx(aSOG_gyoei_spawn_info_weight_f_c* spawn_info, int info_count, u32 block_type) {
  static f32 env_rate_table[mFAs_FIELDRANK_NUM] = {
    0.500f, /* Field Rank 0 */
    0.750f, /* Field Rank 1 */
    0.875f, /* Field Rank 2 */
    1.000f, /* Field Rank 3 */
    1.000f, /* Field Rank 4 */
    1.000f, /* Field Rank 5 */
    1.000f  /* Field Rank 6 */
  };

  int set_table[aGYO_TYPE_NUM];
  f32 env_rate;
  int field_rank;
  int i;
  int idx = aGYO_TYPE_INVALID;
  
  bzero(set_table, aGYO_TYPE_NUM * sizeof(int));
  field_rank = mFAs_GetFieldRank();

  if (field_rank < mFAs_FIELDRANK_ZERO || field_rank > mFAs_FIELDRANK_SIX) {
    if (field_rank < mFAs_FIELDRANK_ZERO) {
      field_rank = mFAs_FIELDRANK_ZERO;
    }

    if (field_rank > mFAs_FIELDRANK_SIX) {
      field_rank = mFAs_FIELDRANK_SIX;
    }
  }

  env_rate = env_rate_table[field_rank];
  /* keep trying to roll a fish until a valid one is found for the current acre or all have been exhausted */
  for (i = 0; i < info_count; i++) {
    idx = aSOG_gyoei_get_idx_sub(spawn_info, set_table, block_type, info_count, env_rate);
    if (idx == aGYO_TYPE_INVALID || idx != aGYO_TYPE_NUM) {
      break;
    }
  }

  return idx;
}

/**
 * @brief Sets up the structure containing the actual fish spawn data.
 * 
 * @param set_data Pointer to fish spawn data structure
 * @param block_xz Pointer to acre position in format: block_xz[0] = X-Acre, block_xz[1] = Z-Acre
 * @param type The index of the fish to spawn
 * @return TRUE when the data was successfully setup, FALSE otherwise
 **/
static int aSOG_gyoei_set_gyoei_data(aSOG_set_data_c* set_data, int* block_xz, int type) {
  #ifdef NONMATCHING
  static u16 fg_idx_table[UT_TOTAL_NUM - 1];
  #endif
  u16* fg_p;
  int selected_unit;
  int ut_z;
  s16 valid_fg_num = 0;
  int ut_x;
  mCoBG_Collision_u* collision_data;
  u32 attribute;
  xyz_t wpos;

  if (type != aGYO_TYPE_INVALID) {
    fg_p = fg_idx_table;
    for (ut_z = 0; ut_z < UT_TOTAL_NUM - 1; ut_z++) {
      *fg_p++ = 0xffff;
    }
    
    set_data->type = type;
    collision_data = mFI_GetBkNum2ColTop(block_xz[0], block_xz[1]);
    fg_p = fg_idx_table;
    if (collision_data != NULL) {
      for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
        for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
          if (ut_z >= 2 && ut_z < UT_Z_NUM - 2 && ut_x >= 2 && ut_x < UT_X_NUM - 2) {
            attribute = collision_data->data.unit_attribute;
            switch (set_data->type) {
              case aGYO_TYPE_LARGE_CHAR:
              {
                if (attribute == mCoBG_ATTRIBUTE_WATERFALL) {
                  valid_fg_num++;
                  *fg_p++ = ut_x + ut_z * UT_X_NUM;
                }
                break;
              }

              /* ocean fish */
              case aGYO_TYPE_COELACANTH:
              case aGYO_TYPE_JELLYFISH:
              case aGYO_TYPE_SEA_BASS:
              case aGYO_TYPE_RED_SNAPPER:
              case aGYO_TYPE_BARRED_KNIFEJAW:
              {
                if (attribute == mCoBG_ATTRIBUTE_SEA && attribute != mCoBG_ATTRIBUTE_WAVE) {
                    f32 bg_y;
                    f32 water_height;
                    f32 diff;

                    mFI_BkandUtNum2CenterWpos(&wpos, block_xz[0], block_xz[1], ut_x, ut_z);
                    bg_y = mCoBG_GetBgY_AngleS_FromWpos(NULL, wpos, 0.0f);
                    water_height = mCoBG_GetWaterHeight_File(wpos, __FILE__, 1957);
                    diff = water_height - bg_y;

                    /* TODO 20.0f should be a definition somewhere */
                    if (mCoBG_CheckSandUt_ForFish(&wpos) == FALSE && diff >= 20.0f) {
                      valid_fg_num++;
                      *fg_p++ = ut_x + ut_z * UT_X_NUM;
                    }
                }
                break;
              }

              case aGYO_TYPE_SALMON:
              case aGYO_TYPE_SALMON2:
              {
                if (mCoBG_CheckWaterAttribute(attribute)) {
                  if (attribute == mCoBG_ATTRIBUTE_SEA && attribute != mCoBG_ATTRIBUTE_WAVE) {
                    /* Salmon is in a 'sea' attribute unit */
                    f32 bg_y;
                    f32 water_height;
                    f32 diff;

                    mFI_BkandUtNum2CenterWpos(&wpos, block_xz[0], block_xz[1], ut_x, ut_z);
                    bg_y = mCoBG_GetBgY_AngleS_FromWpos(NULL, wpos, 0.0f);
                    water_height = mCoBG_GetWaterHeight_File(wpos, __FILE__, 1983);
                    diff = water_height - bg_y;

                    /* TODO 20.0f should be a definition somewhere */
                    if (mCoBG_CheckSandUt_ForFish(&wpos) == FALSE && diff >= 20.0f) {
                      valid_fg_num++;
                      *fg_p++ = ut_x + ut_z * UT_X_NUM;
                    }
                  }
                  else {
                    /* Salmon is in the river/in a 'wave' attribute unit */
                    valid_fg_num++;
                    *fg_p++ = ut_x + ut_z * UT_X_NUM;
                  }
                }
                break;
              }

              case aGYO_TYPE_WHALE:
              {
                if (ut_z >= 5 && ut_z < UT_Z_NUM - 5 && ut_x >= 5 && ut_x < UT_X_NUM - 5 && mCoBG_CheckWaterAttribute(attribute)) {
                  valid_fg_num++;
                  *fg_p++ = ut_x + ut_z * UT_X_NUM;
                }
                break;
              }

              default:
              {
                if (mCoBG_CheckWaterAttribute(attribute)) {
                  valid_fg_num++;
                  *fg_p++ = ut_x + ut_z * UT_X_NUM;
                }
                break;
              }
            }
          }

          collision_data++;
        }
      }
    }

    if (valid_fg_num == 0) {
      return FALSE; // no space to spawn a valid fish here
    }
    
    /* select random position from valid fg units */
    selected_unit = fg_idx_table[(int)(fqrand() * (f32)valid_fg_num)];
    set_data->ut_x = selected_unit % UT_X_NUM;
    set_data->ut_z = selected_unit / UT_X_NUM;
    set_data->should_spawn = TRUE;
    set_data->extra_data = 0;
  }

  return TRUE;
}

/**
 * @brief Decides which fish should spawn and sets the spawn data for it.
 * 
 * @param set_data Pointer to fish spawn data structure
 * @param block_xz Pointer to acre position in format: block_xz[0] = X-Acre, block_xz[1] = Z-Acre
 * @param spawn_info Pointer to all possible current fish spawns
 * @param info_count Number of possible current fish spawns contained in spawn_info
 * @param block_type Current acre type flags
 * @return TRUE when fish was successfully selected, FALSE otherwise
 **/
static int aSOG_gyoei_decide_gyoei(aSOG_set_data_c* set_data, int* block_xz, aSOG_gyoei_spawn_info_weight_f_c* spawn_info, int info_count, u32 block_type) {
  int res = FALSE;
  int idx = aSOG_gyoei_get_idx(spawn_info, info_count, block_type); // decide fish
  if (idx != aGYO_TYPE_INVALID) {
    aSOG_gyoei_spawn_info_weight_f_c* selected_info = spawn_info + idx;
    int spawn_area = selected_info->spawn_area;
    if (spawn_area < aSOG_SPAWN_AREA_NUM) {
      res = aSOG_gyoei_set_gyoei_data(set_data, block_xz, selected_info->type); // set fish data
    }
  }

  return res;
}

/**
 * @brief Attempts to actually make the fish actor
 * 
 * @param set_data Pointer to fish spawn data
 * @param block_xz Pointer to acre position in format: block_xz[0] = X-Acre, block_xz[1] = Z-Acre
 * @param GAME* Pointer to the GAME structure
 * @return TRUE when fish was successfully spawned, FALSE otherwise
 **/
static int aSOG_gyoei_make(aSOG_set_data_c* set_data, int* block_xz, GAME* game) {
  int res = FALSE;

  if (set_data->should_spawn == TRUE && Common_Get(clip.gyo_clip)->make_gyoei_proc != NULL) {
    aGYO_Init_c init_data;
    xyz_t wpos;
    mFI_BkandUtNum2Wpos(&wpos, block_xz[0], block_xz[1], set_data->ut_x, set_data->ut_z);
    init_data.fish_type = set_data->type;

    switch (init_data.fish_type) {
      case aGYO_TYPE_LARGE_CHAR:
      {
        aSOG_get_fall_attribute_position(&wpos);
        break;
      }

      default:
      {
        aSOG_get_water_attribute_position(&wpos);
        break;
      }
    }

    init_data.position = wpos;
    init_data.extra_data = set_data->extra_data;
    init_data.game = game;

    /* send fish off to fish actor to spawn actual actor */
    res = (*Common_Get(clip.gyo_clip)->make_gyoei_proc)(&init_data);
    set_data->should_spawn = FALSE;
  }

  return res;
}

/**
 * @brief Checks that a unit attribute which is 'water' exists in the acre the player is moving into.
 * 
 * @param set_manager SET_MANAGER actor
 * @return TRUE when water exists in the acre, FALSE otherwise
 **/
static int aSOG_gyoei_check_water_unit_in_block(SET_MANAGER* set_manager) {
  mCoBG_Collision_u* collision_data = mFI_GetBkNum2ColTop(set_manager->player_pos.next_bx, set_manager->player_pos.next_bz);
  if (collision_data != NULL) {
    int x, z;

    for (z = 0; z < mFI_UT_WORLDSIZE_Z; z++) {
      for (x = 0; x < mFI_UT_WORLDSIZE_X; x++) {
        if (mCoBG_CheckWaterAttribute_OutOfSea(collision_data->data.unit_attribute) == TRUE) {
          return TRUE;
        }

        collision_data++;
      }
    }
  }

  return FALSE;
}

/**
 * @brief Checks if a fish already exists in the acre the player is moving into.
 * 
 * @param set_manager SET_MANAGER actor
 * @param play Pointer to GAME_PLAY structure
 * @return TRUE when a fish already exists in the acre, FALSE otherwise
 **/
static int aSOG_gyo_chk_live_gyoei(SET_MANAGER* set_manager, GAME_PLAY* play) {
  int res = FALSE;
  aGYO_Clip_c* gyoei_clip = Common_Get(clip.gyo_clip);
  if (gyoei_clip->chk_live_gyoei_proc != NULL) {
    res = (*gyoei_clip->chk_live_gyoei_proc)(set_manager->player_pos.next_bx, set_manager->player_pos.next_bz, (GAME*)play);
  }

  return res;
}

/**
 * @brief Checks if a fish exists in the acre the player is moving into and if that acre has a valid spawn location for fish.
 * 
 * @param set_manager SET_MANAGER actor
 * @param play Pointer to GAME_PLAY structure
 * @param block_type Acre type flags
 * @return FALSE when the acre is valid (not an invalid acre), TRUE otherwise
 **/
static int aSOG_gyoei_block_check(SET_MANAGER* set_manager, GAME_PLAY* play, u32 block_type) {
  int res = FALSE;
  if (aSOG_gyo_chk_live_gyoei(set_manager, play) == FALSE) {
    if ((block_type & mRF_BLOCKKIND_MARINE) != mRF_BLOCKKIND_MARINE && (block_type & mRF_BLOCKKIND_RIVER) != mRF_BLOCKKIND_RIVER && aSOG_gyoei_check_water_unit_in_block(set_manager) == FALSE) {
      res = TRUE;
    }
  }
  else {
    res = TRUE;
  }

  return res;
}

/**
 * @brief Initializes fish spawn data & attempts to spawn the fish.
 * 
 * @param set_data Pointer to fish spawn data
 * @param set_manager SET_MANAGER actor
 * @param game Pointer to GAME structure
 * @param block_type Acre type flags
 * @return TRUE when the fish was successfully spawned, FALSE otherwise
 **/
static int aSOG_gyoei_set_with_list(aSOG_set_data_c* set_data, SET_MANAGER* set_manager, GAME* game, u32 block_type) {
  #ifdef NONMATCHING
  static aSOG_gyoei_spawn_info_weight_f_c copy_range[aSetMgr_GYOEI_NUM];
  #endif
  int res = FALSE;

  if (set_manager->keep.gyoei_keep.possible_gyoei_num > 0) {
    aSOG_gyoei_keep_c* keep = &set_manager->keep.gyoei_keep;
    int i;

    for (i = 0; i < aSetMgr_GYOEI_NUM; i++) {
      bcopy(keep->spawn_weights + i, copy_range + i, sizeof(aSOG_gyoei_spawn_info_weight_f_c));
    }

    if (aSOG_gyoei_decide_gyoei(set_data, &set_manager->player_pos.next_bx, copy_range, keep->possible_gyoei_num, block_type) == TRUE) {
      res = aSOG_gyoei_make(set_data, &set_manager->player_pos.next_bx, game);
    }
  }

  return res;
}

/**
 * @brief Gets the current 'time no' (see aSOG_TIME_NO_*).
 * 
 * There are four quarters of the day which represent a unique "time_no".
 * Only times 0-2 are utilized, where 0 is repeated.
 * 
 * @return The current time number
 **/
static int aSOG_gyoei_get_time_no() {
  int hour = Common_Get(time.rtc_time.hour);
  int time_no = aSOG_TIME_0;
    
  if (hour <= aSOG_TIME_NO_0_END) {
    time_no = aSOG_TIME_0;
  }
  else if (hour <= aSOG_TIME_NO_1_END) {
    time_no = aSOG_TIME_1;
  }
  else if (hour <= aSOG_TIME_NO_2_END) {
    time_no = aSOG_TIME_2;
  }
  else if (hour <= aSOG_TIME_NO_3_END) {
    time_no = aSOG_TIME_3;
  }

  return time_no;
}

/**
 * @brief Updates the saved fishing term transitory info to save data.
 * 
 * The term transitory period allows fish from the next term to begin
 * spawning during the end of the current term. It lasts 5 days,
 * and can start in the period [next_term - 5, next_term].
 * The change rate is (end_of_transition - current_day) * (1/6).
 * 
 * @param term The new term to save
 **/
static void aSOG_gyoei_renew_term_info(int term) {
  Save_Set(gyoei_term, term);
  Save_Set(gyoei_term_transition_offset, (int)(fqrand() * (f32)(aSOG_TERM_TRANSITION_MAX_DAYS + 1))); /* 0-5 days */
}

/**
 * @brief Gets information about the current term, next term, and the term transition period.
 * 
 * @param term0 Current term
 * @param term1 Next term
 * @param term_rate Percentage rate to spawn current term's fish (1.0f when transition is not active, 1.0f-x otherwise)
 **/
static void aSOG_gyoei_chk_term_info(int* term0, int* term1, f32* term_rate) {
  static f32 rate[aSOG_TERM_TRANSITION_MAX_DAYS] = {
    5.0f/6.0f, /* 1 day from end of transition */
    4.0f/6.0f, /* 2 days from end of transition */
    3.0f/6.0f, /* 3 days from end of transition */
    2.0f/6.0f, /* 4 days from end of transition */
    1.0f/6.0f  /* 5 days from end of transition */
  };

  const lbRTC_time_c* rtc_time;
  int now_term;
  u32 next_term;
  int saved_term;

  saved_term = Save_Get(gyoei_term);
  now_term = (Common_Get(time.rtc_time.month) - 1) * 2;

  if (Common_Get(time.rtc_time.day) > 15) {
    now_term++; /* second half of the month */
  }

  next_term = now_term == 23 ? 0 : now_term + 1;

  /* if 0 or 1 terms have passed (current or next term), or saved term is first term of year, or current term is last term of year */
  if (ABS(saved_term - now_term) > 1 && saved_term != 0 && now_term != 23) {
    /* term_delta >= 2 && saved_term != 0 && now_term != 23 */
    aSOG_gyoei_renew_term_info(next_term);
    *term0 = now_term;
    *term1 = now_term;
    *term_rate = 1.0f; /* entirely 'now term' */
  }
  else {
    lbRTC_time_c next_term_time;
    lbRTC_time_c end_next_term_time;
    rtc_time = Common_GetPointer(time.rtc_time);

    lbRTC_TimeCopy(&next_term_time, rtc_time);
    next_term_time.month = (saved_term >> 1) + lbRTC_JANUARY;
    next_term_time.hour = 0;
    next_term_time.min = 0;
    next_term_time.sec = 0;

    if ((saved_term & 1) == 0) {
      if (saved_term != now_term && now_term == 23) {
        next_term_time.year++; /* roll into the next year */
      }

      next_term_time.day = 1;
    }
    else {
      next_term_time.day = 15;
    }

    lbRTC_Sub_DD(&next_term_time, Save_Get(gyoei_term_transition_offset));
    lbRTC_TimeCopy(&end_next_term_time, &next_term_time);
    lbRTC_Add_DD(&end_next_term_time, aSOG_TERM_TRANSITION_MAX_DAYS);

    if (lbRTC_IsOverRTC(&end_next_term_time) == lbRTC_OVER) {
      aSOG_gyoei_renew_term_info(next_term);
      *term0 = now_term;
      *term1 = now_term;
      *term_rate = 1.0f; /* entirely 'now term' */
    }
    else {
      if (lbRTC_IsOverRTC(&next_term_time) == lbRTC_OVER) {
        int days_after_term_start = lbRTC_GetIntervalDays(&next_term_time, rtc_time);
        *term0 = now_term;
        *term1 = saved_term;
        *term_rate = rate[days_after_term_start];
      }
      else {
        *term0 = now_term;
        *term1 = now_term;
        *term_rate = 1.0f; /* entirely 'now term' */
      }
    }
  }
}

/**
 * @brief Checks if a fishing tourney is currently active and, if so, rolls
 * whether or not the current fishing spawn info should be swapped out
 * if the acre is valid.
 * 
 * The acre must have one of the following features to be considered:
 *   - Lake (POOL)
 *   - Bridge
 *   - Waterfall
 * 
 * The stock chance is 75% if the acre has an above feature.
 * 
 * @param block_kind Acre type flags
 * @return TRUE when fish spawns should be changed to fishing tourney spawns, FALSE otherwise
 **/
static int aSOG_gyoei_check_fishing_event(u32 block_kind) {
  static u32 chk_kind[3] = {
    mRF_BLOCKKIND_POOL, mRF_BLOCKKIND_BRIDGE, mRF_BLOCKKIND_WATERFALL
  };

  int res = FALSE;

  if (mEv_check_status(mEv_EVENT_FISHING_TOURNEY_1, mEv_STATUS_ACTIVE) || mEv_check_status(mEv_EVENT_FISHING_TOURNEY_2, mEv_STATUS_ACTIVE)) {
    int i;

    for (i = 0; i < 3; i++) {
      if (chk_kind[i] == (chk_kind[i] & block_kind)) {
        /* 75% chance of it being a fishing tourney fish list */
        if (fqrand() < 0.75f) {
          res = TRUE;
        }
        break;
      }
    }
  }

  return res;
}

/**
 * @brief Initializes the fish spawn data from list data while applying term rate scaling.
 * 
 * The fish spawns' weights are modified by the term rate scale. This is used for the
 * term transitory period. It will always be (current_term_rate + next_term_rate) = 1.0f.
 * 
 * @param keep Pointer to SET_MANAGER's aSOG_gyoei_keep_c data
 * @param term_list Pointer to the current term's fish spawn data
 * @param term_rate Fish spawn weight adjustment value based on term spawn ratio
 **/
static void aSOG_gyoei_copy_range_data(aSOG_gyoei_keep_c* keep, aSOG_term_list_c* term_list, f32 term_rate) {
  aSOG_term_info_c* term_data = term_list->term_info;
  aSOG_gyoei_spawn_info_weight_f_c* spawn_weight = keep->spawn_weights + keep->possible_gyoei_num;
  int count = term_list->count;

  keep->possible_gyoei_num = keep->possible_gyoei_num + count;

  for (count; count != 0; count--) {
    spawn_weight->type = term_data->type;
    spawn_weight->spawn_area = term_data->spawn_area;
    spawn_weight->spawn_weight = ((f32)term_data->weight) * term_rate;

    term_data++;
    spawn_weight++;
  }
}

/**
 * @brief Adds coelacanth spawn info into the current fish spawn table.
 * 
 * It must be raining and not between the hours of 9am-3:59pm.
 * 
 * Additionally, the coelacanth's spawn data is only added to
 * the current term's info. This means that it will become rarer
 * as the term transition nears the next term.
 * 
 * @param keep Pointer to SET_MANAGER's aSOG_gyoei_keep_c data
 * @param time_no Current time number
 * @param is_next_term TRUE when the data is for the next term, FALSE otherwise
 **/
static void aSOG_add_kaseki_range_data(aSOG_gyoei_keep_c* keep, int time_no, int is_next_term) {
  static aSOG_gyoei_spawn_info_weight_f_c kaseki_data = FISH_SPAWN(COELACANTH, SEA, 2.0f);

  /* Only the current term, while raining, and not during 9am-3:59pm */
  if (is_next_term == FALSE && mEnv_NowWeather() == mEnv_WEATHER_RAIN && time_no != aSOG_TIME_2) {
    keep->spawn_weights[keep->possible_gyoei_num] = kaseki_data;
    keep->possible_gyoei_num++;
  }
}

typedef void(*aSOG_gyoei_make_range_proc)(aSOG_gyoei_keep_c* keep, int time_no, int term, int next_term, f32 term_rate);

/**
 * @brief Creates fish spawn data for river acres.
 * 
 * @param keep Pointer to SET_MANAGER's aSOG_gyoei_keep_c data
 * @param time_no Current time number
 * @param term The term index
 * @param next_term TRUE when this is for the next term, FALSE when it is for the current term
 * @param term_rate Term rate spawn weight modifier
 **/
static void aSOG_gyoei_make_river_range_data(aSOG_gyoei_keep_c* keep, int time_no, int term, int next_term, f32 term_rate) {
  aSOG_term_list_c* list = r_month[term >> 1][term & 1] + time_no;
  if (list != NULL) {
    aSOG_gyoei_copy_range_data(keep, list, term_rate);
  }
}

/**
 * @brief Creates fish spawn data for valid fishing event acres.
 * 
 * @param keep Pointer to SET_MANAGER's aSOG_gyoei_keep_c data
 * @param time_no Current time number
 * @param term The term index
 * @param next_term TRUE when this is for the next term, FALSE when it is for the current term
 * @param term_rate Term rate spawn weight modifier
 **/
static void aSOG_gyoei_make_fishing_event_range_data(aSOG_gyoei_keep_c* keep, int time_no, int term, int next_term, f32 term_rate) {
  aSOG_term_list_c* list = f_event + time_no;
  if (list != NULL) {
    aSOG_gyoei_copy_range_data(keep, list, 1.0f);
  }
}

/**
 * @brief Creates fish spawn data for beachfront ocean acres.
 * 
 * @param keep Pointer to SET_MANAGER's aSOG_gyoei_keep_c data
 * @param time_no Current time number
 * @param term The term index
 * @param next_term TRUE when this is for the next term, FALSE when it is for the current term
 * @param term_rate Term rate spawn weight modifier
 **/
static void aSOG_gyoei_make_sea_range_data(aSOG_gyoei_keep_c* keep, int time_no, int term, int next_term, f32 term_rate) {
  aSOG_term_list_c* list = s_month[term >> 1][term & 1] + time_no;
  if (list != NULL) {
    aSOG_gyoei_copy_range_data(keep, list, term_rate);
    aSOG_add_kaseki_range_data(keep, time_no, next_term);
  }
}

/**
 * @brief Updates fish spawn rates by 10x. Used to artificially decrease
 * the whale's spawn rate.
 * 
 * @param keep Pointer to SET_MANAGER's aSOG_gyoei_keep_c data
 **/
static void aSOG_gyoei_make_offing_range_data_sub(aSOG_gyoei_keep_c* keep) {
  int gyoei_num = keep->possible_gyoei_num;
  aSOG_gyoei_spawn_info_weight_f_c* weight_info = keep->spawn_weights;

  for (gyoei_num; gyoei_num != 0; gyoei_num--) {
    weight_info->spawn_weight *= 10.0f;
    weight_info++;
  }
}

/**
 * @brief Creates fish spawn data for ocean between the town and the island.
 * 
 * @param keep Pointer to SET_MANAGER's aSOG_gyoei_keep_c data
 * @param time_no Current time number
 * @param term The term index
 * @param next_term TRUE when this is for the next term, FALSE when it is for the current term
 * @param term_rate Term rate spawn weight modifier
 **/
static void aSOG_gyoei_make_offing_range_data(aSOG_gyoei_keep_c* keep, int time_no, int term, int next_term, f32 term_rate) {
  static aSOG_gyoei_spawn_info_weight_f_c whale_data = FISH_SPAWN(WHALE, OFFING, 1.0f);

  aSOG_gyoei_make_sea_range_data(keep, time_no, term, next_term, term_rate); /* initialize to ocean fish list */
  aSOG_gyoei_make_offing_range_data_sub(keep); /* multiply all weights 10x */

  /* check and add whale data */
  if (next_term == FALSE) {
    keep->spawn_weights[keep->possible_gyoei_num] = whale_data;
    keep->possible_gyoei_num++;
  }
}

/**
 * @brief Creates fish spawn data for ponds.
 * 
 * NOTE: pool here refers to ponds, not the river 'lake'/pool
 * 
 * @param keep Pointer to SET_MANAGER's aSOG_gyoei_keep_c data
 * @param time_no Current time number
 * @param term The term index
 * @param next_term TRUE when this is for the next term, FALSE when it is for the current term
 * @param term_rate Term rate spawn weight modifier
 **/
static void aSOG_gyoei_make_pool_range_data(aSOG_gyoei_keep_c* keep, int time_no, int term, int next_term, f32 term_rate) {
  aSOG_term_list_c* list = p_month[term >> 1][term & 1]; /* missing + time_no */
  if (list != NULL) {
    aSOG_gyoei_copy_range_data(keep, list + time_no, term_rate);
  }
}

/**
 * @brief Creates fish spawn data for the island.
 * 
 * @param keep Pointer to SET_MANAGER's aSOG_gyoei_keep_c data
 * @param time_no Current time number
 * @param term The term index
 * @param next_term TRUE when this is for the next term, FALSE when it is for the current term
 * @param term_rate Term rate spawn weight modifier
 **/
static void aSOG_gyoei_make_island_range_data(aSOG_gyoei_keep_c* keep, int time_no, int term, int next_term, f32 term_rate) {
  aSOG_term_list_c* list = f_island + time_no;
  if (list != NULL) {
    aSOG_gyoei_copy_range_data(keep, list, 1.0f);
    aSOG_add_kaseki_range_data(keep, time_no, next_term);
  }
}

/**
 * @brief Creates fish spawn data for an acre.
 * 
 * @param set_manager SET_MANAGER actor
 * @param block_type Acre type flags
 **/
static void aSOG_gyoei_make_range_data(SET_MANAGER* set_manager, u32 block_type) {
  static aSOG_gyoei_make_range_proc make_range_data_proc[aSOG_RANGE_PROC_NUM] = {
    &aSOG_gyoei_make_river_range_data,
    &aSOG_gyoei_make_sea_range_data,
    &aSOG_gyoei_make_offing_range_data,
    &aSOG_gyoei_make_pool_range_data,
    &aSOG_gyoei_make_fishing_event_range_data,
    &aSOG_gyoei_make_island_range_data
  };

  int term0, term1;
  int time_no;
  int range_proc;
  f32 term0_rate;
  aSOG_gyoei_keep_c* gyoei_keep = &set_manager->keep.gyoei_keep;
  
  /* get the current term (term0), the next term (term1), and the ratio of current-to-next term (term0_rate + term1_rate = 1.0f) */
  aSOG_gyoei_chk_term_info(&term0, &term1, &term0_rate);
  
  /* clear old gyoei data */
  bzero(gyoei_keep->spawn_weights, aSetMgr_GYOEI_NUM * sizeof(aSOG_gyoei_spawn_info_weight_f_c));
  gyoei_keep->possible_gyoei_num = 0;

  if ((block_type & mRF_BLOCKKIND_MARINE) == mRF_BLOCKKIND_MARINE) {
    if ((block_type & mRF_BLOCKKIND_OFFING) == mRF_BLOCKKIND_OFFING) {
      range_proc = aSOG_RANGE_PROC_OFFING;
      term0_rate = 1.0f;
    }
    else if ((block_type & mRF_BLOCKKIND_ISLAND) == mRF_BLOCKKIND_ISLAND) {
      range_proc = aSOG_RANGE_PROC_ISLAND;
      term0_rate = 1.0f;
    }
    else {
      range_proc = aSOG_RANGE_PROC_SEA;
    }
  }
  else if ((block_type & mRF_BLOCKKIND_RIVER) == mRF_BLOCKKIND_RIVER) {
    if (aSOG_gyoei_check_fishing_event(block_type) == TRUE) {
      range_proc = aSOG_RANGE_PROC_FISHING_EVENT;
      term0_rate = 1.0f;
    }
    else {
      range_proc = aSOG_RANGE_PROC_RIVER;
    }
  }
  else {
    /* default to pond (pool) range proc since pools can be in any acre */
    range_proc = aSOG_RANGE_PROC_POOL;
  }

  time_no = aSOG_gyoei_get_time_no();
  
  /* populate the current term's fishing data */
  (*make_range_data_proc[range_proc])(gyoei_keep, time_no, term0, FALSE, term0_rate);

  /* if the term0 rate isn't 100% (1.0f), populate the next term with the inverse rate used for term0 (1.0f-x) */
  if (term0_rate != 1.0f) {
    (*make_range_data_proc[range_proc])(gyoei_keep, time_no, term1, TRUE, 1.0f - term0_rate);
  }
}

/**
 * @brief Attempts to spawn a fish.
 * 
 * @param set_manager SET_MANAGER actor
 * @param play Pointer to GAME_PLAY structure 
 * @return TRUE when a fish was successfully spawned, FALSE otherwise
 **/
extern int aSOG_gyoei_set(SET_MANAGER* set_manager, GAME_PLAY* play) {
  #ifdef NONMATCHING
  static aSOG_set_data_c set_data;
  #endif

  u32 block_kind;
  int res;

  res = FALSE;
  block_kind = mFI_BkNum2BlockKind(set_manager->player_pos.next_bx, set_manager->player_pos.next_bz);

  /* check if there's any condition preventing a fish from spawning in the next acre, and spawn one if not */
  if (aSOG_gyoei_block_check(set_manager, play, block_kind) == FALSE) {
    aSOG_gyoei_clear_set_data(&set_data);
    aSOG_gyoei_make_range_data(set_manager, block_kind);
    res = aSOG_gyoei_set_with_list(&set_data, set_manager, (GAME*)play, block_kind);
  }

  return res;
}
