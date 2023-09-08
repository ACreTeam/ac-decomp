#include "m_random_field.h"

#include "m_random_field_ovl.h"
#include "m_collision_bg.h"
#include "m_field_info.h"
#include "m_common_data.h"
#include "m_scene_table.h"

extern void mRF_MakeRandomField(mFM_combination_c* combi_table, mFM_combo_info_c* combo_info, int combo_count, GAME* game) {
  mRF_MakeRandomField_ovl(combi_table, combo_info, combo_count, game);
}

static u32 mRF_block_info[mRF_BLOCK_TYPE_MAX] = {
  mRF_BLOCKKIND_BORDER,
  mRF_BLOCKKIND_BORDER | mRF_BLOCKKIND_RIVER0,
  mRF_BLOCKKIND_BORDER,
  mRF_BLOCKKIND_BORDER,
  mRF_BLOCKKIND_BORDER,
  mRF_BLOCKKIND_BORDER,
  mRF_BLOCKKIND_BORDER,
  mRF_BLOCKKIND_BORDER,
  mRF_BLOCKKIND_BORDER,
  mRF_BLOCKKIND_RAILROAD | mRF_BLOCKKIND_TUNNEL,
  mRF_BLOCKKIND_RAILROAD | mRF_BLOCKKIND_TUNNEL,
  mRF_BLOCKKIND_STATION | mRF_BLOCKKIND_RAILROAD,
  mRF_BLOCKKIND_RAILROAD | mRF_BLOCKKIND_DUMP,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RAILROAD | mRF_BLOCKKIND_18 | mRF_BLOCKKIND_RIVER0,
  mRF_BLOCKKIND_PLAYER,
  mRF_BLOCKKIND_CLIFF,
  mRF_BLOCKKIND_CLIFF,
  mRF_BLOCKKIND_CLIFF,
  mRF_BLOCKKIND_CLIFF,
  mRF_BLOCKKIND_CLIFF,
  mRF_BLOCKKIND_CLIFF,
  mRF_BLOCKKIND_CLIFF,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_WATERFALL | mRF_BLOCKKIND_RIVER0,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_WATERFALL | mRF_BLOCKKIND_RIVER0,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_18 | mRF_BLOCKKIND_RIVER0,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_18 | mRF_BLOCKKIND_RIVER0,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_WATERFALL | mRF_BLOCKKIND_RIVER0,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_18 | mRF_BLOCKKIND_RIVER0,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_18 | mRF_BLOCKKIND_RIVER0,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_18 | mRF_BLOCKKIND_RIVER1,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_WATERFALL | mRF_BLOCKKIND_RIVER1,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_WATERFALL | mRF_BLOCKKIND_RIVER1,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_18 | mRF_BLOCKKIND_RIVER1,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_18 | mRF_BLOCKKIND_RIVER1,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RIVER2,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RIVER2,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_RIVER2,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_WATERFALL | mRF_BLOCKKIND_RIVER2,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_WATERFALL | mRF_BLOCKKIND_RIVER2,
  mRF_BLOCKKIND_NONE,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_18 | mRF_BLOCKKIND_RIVER0,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_18 | mRF_BLOCKKIND_RIVER1,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_18 | mRF_BLOCKKIND_RIVER2,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_18 | mRF_BLOCKKIND_RIVER3,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_18 | mRF_BLOCKKIND_RIVER4,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_18 | mRF_BLOCKKIND_RIVER5,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_18 | mRF_BLOCKKIND_RIVER6,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER0,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER1,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER2,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER3,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER4,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER5,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER6,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_SLOPE,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_SLOPE,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_SLOPE,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_SLOPE,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_SLOPE,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_SLOPE,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_SLOPE,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_BORDER,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_BORDER,
  mRF_BLOCKKIND_MARINE,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_MARINE | mRF_BLOCKKIND_18 | mRF_BLOCKKIND_RIVER0,
  mRF_BLOCKKIND_SHOP | mRF_BLOCKKIND_RAILROAD,
  mRF_BLOCKKIND_SHRINE,
  mRF_BLOCKKIND_POSTOFFICE | mRF_BLOCKKIND_RAILROAD,
  mRF_BLOCKKIND_POLICE,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_POOL | mRF_BLOCKKIND_RIVER0,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_POOL | mRF_BLOCKKIND_RIVER1,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_POOL | mRF_BLOCKKIND_RIVER2,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_POOL | mRF_BLOCKKIND_RIVER3,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_POOL | mRF_BLOCKKIND_RIVER4,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_POOL | mRF_BLOCKKIND_RIVER5,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_POOL | mRF_BLOCKKIND_RIVER6,
  mRF_BLOCKKIND_BORDER,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BORDER | mRF_BLOCKKIND_RIVER0,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_BORDER,
  mRF_BLOCKKIND_RAILROAD | mRF_BLOCKKIND_BORDER,
  mRF_BLOCKKIND_MARINE | mRF_BLOCKKIND_BORDER,
  mRF_BLOCKKIND_MARINE | mRF_BLOCKKIND_BORDER,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_MARINE | mRF_BLOCKKIND_RIVER0,
  mRF_BLOCKKIND_NONE,
  mRF_BLOCKKIND_MUSEUM,
  mRF_BLOCKKIND_MARINE | mRF_BLOCKKIND_TAILORS,
  mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RAILROAD | mRF_BLOCKKIND_RIVER0,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER1,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER0,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER0,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER1,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER1,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER0,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER0,
  mRF_BLOCKKIND_MARINE | mRF_BLOCKKIND_OCEAN | mRF_BLOCKKIND_OFFING,
  mRF_BLOCKKIND_MARINE | mRF_BLOCKKIND_OCEAN | mRF_BLOCKKIND_OFFING,
  mRF_BLOCKKIND_MARINE | mRF_BLOCKKIND_OCEAN | mRF_BLOCKKIND_OFFING,
  mRF_BLOCKKIND_MARINE | mRF_BLOCKKIND_OCEAN | mRF_BLOCKKIND_OFFING,
  mRF_BLOCKKIND_MARINE | mRF_BLOCKKIND_OCEAN | mRF_BLOCKKIND_ISLAND | mRF_BLOCKKIND_ISLAND_LEFT,
  mRF_BLOCKKIND_MARINE | mRF_BLOCKKIND_OCEAN | mRF_BLOCKKIND_ISLAND,
  mRF_BLOCKKIND_MARINE | mRF_BLOCKKIND_DOCK,
  mRF_BLOCKKIND_MARINE | mRF_BLOCKKIND_OCEAN | mRF_BLOCKKIND_OFFING,
  mRF_BLOCKKIND_MARINE | mRF_BLOCKKIND_OCEAN | mRF_BLOCKKIND_OFFING,
  mRF_BLOCKKIND_MARINE | mRF_BLOCKKIND_OCEAN | mRF_BLOCKKIND_OFFING,
  mRF_BLOCKKIND_MARINE | mRF_BLOCKKIND_OCEAN | mRF_BLOCKKIND_OFFING,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER1,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER1,
  mRF_BLOCKKIND_CLIFF | mRF_BLOCKKIND_RIVER | mRF_BLOCKKIND_BRIDGE | mRF_BLOCKKIND_RIVER1
};

extern u32 mRF_Type2BlockInfo(u8 type) {
  if (type < mRF_BLOCK_TYPE_MAX) {
    return mRF_block_info[type];
  }

  return mRF_BLOCKKIND_NONE;
}

static int mRF_GateType2GateCount(int gate_type) {
  static u8 gate_count_table[mRF_GATE_TYPE_NUM] = {
    0, 1, 1, 2, 2, 3
  };

  if (gate_type < mRF_GATE_TYPE_NUM) {
    return gate_count_table[gate_type];
  }

  return 0;
}

extern int mRF_SearchPond(int* ut_x, int* ut_z, int block_x, int block_z) {
  mFI_sound_source_info_c* s_source_info = mFI_GetSoundSourcePBlockNum(block_x, block_z);

  if (s_source_info != NULL) {
    int i;

    for (i = 0; i < mFI_NUM_SOUND_SOURCES; i++, s_source_info++) {
      if (s_source_info->kind == mFI_SOUND_SOURCE_POND) {
        if (mFI_Wpos2UtNum(ut_x, ut_z, s_source_info->wpos)) {
          return TRUE;
        }
      }
    }
  }

  return FALSE;
}

static int mRF_Attr2BeastRoadAttr(int attr) {
  switch (attr) {
    case mCoBG_ATTRIBUTE_GRASS0:
    case mCoBG_ATTRIBUTE_GRASS1:
      return mCoBG_ATTRIBUTE_GRASS2;
    
    case mCoBG_ATTRIBUTE_SOIL0:
    case mCoBG_ATTRIBUTE_SOIL1:
      return mCoBG_ATTRIBUTE_SOIL2;

    default:
      return attr;
  }
}

#define GATE_UT(z, x) ((((z) & 0xF) << 4) | ((x) & 0xF))
#define GATE(z0, x0, z1, x1) { GATE_UT(z0, x0), GATE_UT(z1, x1) }

static mRF_gate_c gate1_type0_up[1] = { GATE(0, 7, 1, 7) };
static mRF_gate_c gate1_type0_lt[1] = { GATE(7, 0, 7, 1) };
static mRF_gate_c gate1_type0_dn[1] = { GATE(15, 7, 14, 7) };
static mRF_gate_c gate1_type0_rt[1] = { GATE(7, 15, 7, 14) };

static mRF_gate_c gate1_type1_up[1] = { GATE(0, 7, 1, 7) };
static mRF_gate_c gate1_type1_lt[1] = { GATE(9, 0, 9, 1) };
static mRF_gate_c gate1_type1_dn[1] = { GATE(15, 7, 14, 7) };
static mRF_gate_c gate1_type1_rt[1] = { GATE(9, 15, 9, 14) };

static mRF_gate_c gate2_type0_up[2] = { GATE(0, 5, 1, 5), GATE(0, 12, 1, 12) };
static mRF_gate_c gate2_type0_lt[2] = { GATE(5, 0, 5, 1), GATE(12, 0, 12, 1) };
static mRF_gate_c gate2_type0_dn[2] = { GATE(15, 5, 14, 5), GATE(15, 12, 14, 12) };
static mRF_gate_c gate2_type0_rt[2] = { GATE(5, 15, 5, 14), GATE(12, 15, 12, 14) };

static mRF_gate_c gate2_type1_up[2] = { GATE(0, 2, 1, 2), GATE(0, 11, 1, 11) };
static mRF_gate_c gate2_type1_lt[2] = { GATE(2, 0, 2, 1), GATE(11, 0, 11, 1) };
static mRF_gate_c gate2_type1_dn[2] = { GATE(15, 2, 14, 2), GATE(15, 11, 14, 11) };
static mRF_gate_c gate2_type1_rt[2] = { GATE(2, 15, 2, 14), GATE(11, 15, 11, 14) };

static mRF_gate_c gate3_type0_up[3] = { GATE(0, 2, 1, 2), GATE(0, 8, 1, 8), GATE(0, 12, 1, 12) };
static mRF_gate_c gate3_type0_lt[3] = { GATE(2, 0, 2, 1), GATE(8, 0, 8, 1), GATE(12, 0, 12, 1) };
static mRF_gate_c gate3_type0_dn[3] = { GATE(15, 2, 14, 2), GATE(15, 8, 14, 8), GATE(15, 12, 14, 12) };
static mRF_gate_c gate3_type0_rt[3] = { GATE(2, 15, 2, 14), GATE(8, 15, 8, 14), GATE(12, 15, 12, 14) };

static mRF_gate_c* mRF_gate_correct_info[mRF_GATE_TYPE_NUM][mRF_DIRECT_NUM] = {
  { NULL, NULL, NULL, NULL },
  { gate1_type0_up, gate1_type0_lt, gate1_type0_dn, gate1_type0_rt },
  { gate1_type1_up, gate1_type1_lt, gate1_type1_dn, gate1_type1_rt },
  { gate2_type0_up, gate2_type0_lt, gate2_type0_dn, gate2_type0_rt },
  { gate2_type1_up, gate2_type1_lt, gate2_type1_dn, gate2_type1_rt },
  { gate3_type0_up, gate3_type0_lt, gate3_type0_dn, gate3_type0_rt },
};

static u8 mRF_gate_info2[mRF_BLOCK_TYPE_MAX][mRF_DIRECT_NUM] = {
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE1_TYPE1, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE1_TYPE1  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE1_TYPE1, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE1_TYPE1  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE1_TYPE1, // west
    mRF_GATE2_TYPE1, // south
    mRF_GATE1_TYPE1  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE2_TYPE0, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE2_TYPE0  // east
  },
  {
    mRF_GATE2_TYPE0, // north
    mRF_GATE2_TYPE0, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE2_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE2_TYPE0, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE2_TYPE0, // south
    mRF_GATE2_TYPE0  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE2_TYPE0, // west
    mRF_GATE2_TYPE0, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE2_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE2_TYPE0, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE2_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE2_TYPE0  // east
  },
  {
    mRF_GATE2_TYPE1, // north
    mRF_GATE2_TYPE0, // west
    mRF_GATE2_TYPE1, // south
    mRF_GATE2_TYPE0  // east
  },
  {
    mRF_GATE3_TYPE0, // north
    mRF_GATE2_TYPE0, // west
    mRF_GATE2_TYPE1, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE3_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE3_TYPE0, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE2_TYPE1, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE3_TYPE0, // south
    mRF_GATE2_TYPE0  // east
  },
  {
    mRF_GATE2_TYPE1, // north
    mRF_GATE2_TYPE0, // west
    mRF_GATE3_TYPE0, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE3_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE3_TYPE0, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE3_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE2_TYPE1, // south
    mRF_GATE2_TYPE0  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE3_TYPE0, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE3_TYPE0  // east
  },
  {
    mRF_GATE2_TYPE0, // north
    mRF_GATE3_TYPE0, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE2_TYPE1  // east
  },
  {
    mRF_GATE2_TYPE0, // north
    mRF_GATE2_TYPE1, // west
    mRF_GATE2_TYPE0, // south
    mRF_GATE2_TYPE1  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE2_TYPE1, // west
    mRF_GATE2_TYPE0, // south
    mRF_GATE3_TYPE0  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE3_TYPE0, // west
    mRF_GATE2_TYPE0, // south
    mRF_GATE2_TYPE1  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE3_TYPE0, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE3_TYPE0  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE2_TYPE1, // west
    mRF_GATE2_TYPE0, // south
    mRF_GATE3_TYPE0  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE3_TYPE0, // west
    mRF_GATE2_TYPE0, // south
    mRF_GATE2_TYPE1  // east
  },
  {
    mRF_GATE2_TYPE0, // north
    mRF_GATE2_TYPE1, // west
    mRF_GATE2_TYPE0, // south
    mRF_GATE2_TYPE1  // east
  },
  {
    mRF_GATE2_TYPE0, // north
    mRF_GATE2_TYPE1, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE3_TYPE0  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE2_TYPE1, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE2_TYPE1, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE2_TYPE1, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE2_TYPE1  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE2_TYPE1, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE2_TYPE1  // east
  },
  {
    mRF_GATE2_TYPE1, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE2_TYPE1  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE2_TYPE1, // west
    mRF_GATE2_TYPE1, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE2_TYPE1, // north
    mRF_GATE2_TYPE1, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE2_TYPE1, // south
    mRF_GATE2_TYPE1  // east
  },
  {
    mRF_GATE2_TYPE1, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE2_TYPE1, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE2_TYPE1, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE2_TYPE1  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE2_TYPE1, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE2_TYPE1  // east
  },
  {
    mRF_GATE2_TYPE1, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE2_TYPE1  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE2_TYPE1, // west
    mRF_GATE2_TYPE1, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE2_TYPE1, // north
    mRF_GATE2_TYPE1, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE2_TYPE1, // south
    mRF_GATE2_TYPE1  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE2_TYPE0, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE2_TYPE0  // east
  },
  {
    mRF_GATE2_TYPE0, // north
    mRF_GATE2_TYPE0, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE2_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE2_TYPE0, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE2_TYPE0, // south
    mRF_GATE2_TYPE0  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE2_TYPE0, // west
    mRF_GATE2_TYPE0, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE2_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE2_TYPE0, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE2_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE2_TYPE0  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE_NONE, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE2_TYPE1, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE_NONE, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE1_TYPE1, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE1_TYPE1  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE1_TYPE1, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE1_TYPE1  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE2_TYPE1, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE2_TYPE1, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE2_TYPE1, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE2_TYPE1  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE2_TYPE1, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE2_TYPE1  // east
  },
  {
    mRF_GATE2_TYPE1, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE2_TYPE1  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE2_TYPE1, // west
    mRF_GATE2_TYPE1, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE2_TYPE1, // north
    mRF_GATE2_TYPE1, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE2_TYPE1, // south
    mRF_GATE2_TYPE1  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE2_TYPE1, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE_NONE, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE_NONE, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE1_TYPE1, // west
    mRF_GATE2_TYPE1, // south
    mRF_GATE1_TYPE1  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE3_TYPE0, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE3_TYPE0  // east
  },
  {
    mRF_GATE3_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE3_TYPE0, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE2_TYPE1, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE3_TYPE0, // south
    mRF_GATE2_TYPE0  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE2_TYPE1, // west
    mRF_GATE2_TYPE0, // south
    mRF_GATE3_TYPE0  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE3_TYPE0, // west
    mRF_GATE2_TYPE0, // south
    mRF_GATE2_TYPE1  // east
  },
  {
    mRF_GATE3_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE3_TYPE0, // south
    mRF_GATE1_TYPE0  // east
  },
  {
    mRF_GATE3_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE2_TYPE1, // south
    mRF_GATE2_TYPE0  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE1_TYPE0, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE_NONE, // north
    mRF_GATE_NONE, // west
    mRF_GATE_NONE, // south
    mRF_GATE_NONE  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE3_TYPE0, // west
    mRF_GATE1_TYPE0, // south
    mRF_GATE3_TYPE0  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE2_TYPE1, // west
    mRF_GATE2_TYPE0, // south
    mRF_GATE3_TYPE0  // east
  },
  {
    mRF_GATE1_TYPE0, // north
    mRF_GATE3_TYPE0, // west
    mRF_GATE2_TYPE0, // south
    mRF_GATE2_TYPE1  // east
  }
};

static int mRF_BlockTypeDirect2GateType(u8 block_type, int direct) {
  return mRF_gate_info2[block_type][direct];
}


extern mRF_gate_c* mRF_BlockTypeDirect2GateData(int* gate_count, u8 block_type, int direct) {
  int type = mRF_BlockTypeDirect2GateType(block_type, direct);
  int count = mRF_GateType2GateCount(type);

  *gate_count = count;
  return mRF_gate_correct_info[type][direct];
}

static int mRF_BlockInf2CheckBeastRoad(u8 block_type, mCoBG_Collision_u* collision_data) {
  int i;
  int j;
  xyz_t wpos = { 0.0f, 0.0f, 0.0f };
  int changed_attribute_count = 0;
  int col_ut;
  mCoBG_Collision_u* col;
  u32 attrib;

  for (i = 0; i < mRF_DIRECT_NUM; i++) {
    int gate_count;
    mRF_gate_c* gate_p = mRF_BlockTypeDirect2GateData(&gate_count, block_type, i);

    if (gate_p != NULL) {
      for (j = 0; j < gate_count; j++) {
        /* process first unit */
        {
          col_ut = gate_p[j].ut0;
          col = collision_data + (u8)col_ut;
          attrib = col->data.unit_attribute;
          
          mFI_UtNum2CenterWpos(&wpos, col_ut & 0xF, (col_ut >> 4) & 0xF);

          /* only bother updating the unit attribute if the unit can grow collideable plants in it */
          if (mCoBG_Attribute2CheckPlant(attrib, &wpos) > 0) {
            u32 new_attrib = mRF_Attr2BeastRoadAttr(attrib);
            changed_attribute_count++;

            col->data.unit_attribute = new_attrib;
          }
        }

        /* process second unit */
        {
          col_ut = gate_p[j].ut1;
          col = collision_data + (u8)col_ut;
          attrib = col->data.unit_attribute;
          
          mFI_UtNum2CenterWpos(&wpos, col_ut & 0xF, (col_ut >> 4) & 0xF);

          /* only bother updating the unit attribute if the unit can grow collideable plants in it */
          if (mCoBG_Attribute2CheckPlant(attrib, &wpos) > 0) {
            u32 new_attrib = mRF_Attr2BeastRoadAttr(attrib);
            changed_attribute_count++;

            col->data.unit_attribute = new_attrib;
          }
        }
      }
    }
  }

  return !changed_attribute_count;
}

extern void mRF_CheckBeastRoad() {
  if (Save_Get(scene_no) == SCENE_FG) {
    int max_bx = mFI_GetBlockXMax() - 1;
    int max_bz = mFI_GetBlockZMax() - 1;
    
    int block_x;
    int block_z;

    for (block_z = 1; block_z < max_bz; block_z++) {
      for (block_x = 1; block_x < max_bx; block_x++) {
        mCoBG_Collision_u* collision_data = mFI_GetBkNum2ColTop(block_x, block_z);
        u8 type = mFI_BkNum2BlockType(block_x, block_z);

        mRF_BlockInf2CheckBeastRoad(type, collision_data);
      }
    }
  }
}

static u8 l_river_next_direct[mRF_RIVER_NUM] = {
  mRF_DIRECT_SOUTH,
  mRF_DIRECT_EAST,
  mRF_DIRECT_WEST,
  mRF_DIRECT_EAST,
  mRF_DIRECT_SOUTH,
  mRF_DIRECT_WEST,
  mRF_DIRECT_SOUTH
};

extern int mRF_RiverIdx2NextDirect(int river_idx) {
  if (river_idx >= mRF_RIVER0 && river_idx < mRF_RIVER_NUM) {
    return l_river_next_direct[river_idx];
  }

  return mRF_DIRECT_SOUTH;
}

extern int mRF_BlockType2RiverNextDirect(u8 type) {
  u32 block_kind = mRF_Type2BlockInfo(type);
  u32 river_kinds[mRF_RIVER_NUM] = {
    mRF_BLOCKKIND_RIVER0,
    mRF_BLOCKKIND_RIVER1,
    mRF_BLOCKKIND_RIVER2,
    mRF_BLOCKKIND_RIVER3,
    mRF_BLOCKKIND_RIVER4,
    mRF_BLOCKKIND_RIVER5,
    mRF_BLOCKKIND_RIVER6
  };

  int i;

  for (i = 0; i < mRF_RIVER_NUM; i++) {
    if ((block_kind & river_kinds[i]) != 0) {
      return mRF_RiverIdx2NextDirect(i);
    }
  }

  return mRF_DIRECT_ERROR;
}

static int mRF_FindBgNameTypeCombiNum(mActor_name_t bg_id, u8 type) {
  mFM_combo_info_c* combo_info = data_combi_table;
  int combi_num = data_combi_table_number;
  int i;

  for (i = 0; i < combi_num; i++) {
    if (combo_info->bg_id == bg_id && combo_info->type == type) {
      return i;
    }
    combo_info++;
  }

  return 0;
}

extern void mRF_IslandBgData_To_VillageData() {
  int left_bg_idx = Save_Get(island.bg_data[0]) & 3;
  int right_bg_idx = Save_Get(island.bg_data[1]) & 3;
  int island_left_bx;
  int island_left_bz;
  /* TODO: enums for these */    
  mActor_name_t left_t = left_bg_idx + 0x74;
  mActor_name_t right_t = right_bg_idx + 0x70;

  if (mFI_BlockKind2BkNum(&island_left_bx, &island_left_bz, mRF_BLOCKKIND_ISLAND_LEFT)) {
    mActor_name_t left_bg_name = mRF_FindBgNameTypeCombiNum(left_t, 0x62);
    mActor_name_t right_bg_name = mRF_FindBgNameTypeCombiNum(right_t, 0x63);
    
    Save_Set(combi_table[island_left_bz][island_left_bx].combination_type, left_bg_name);
    Save_Set(combi_table[island_left_bz][island_left_bx + 1].combination_type, right_bg_name);
  }
}

extern int mRF_CheckFieldStep3() {
  return Save_Get(combi_table[0][0]).height == mRF_FIELD_STEP3;
}
