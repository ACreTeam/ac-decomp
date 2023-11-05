#ifndef M_RANDOM_FIELD_H
#define M_RANDOM_FIELD_H

#include "types.h"
#include "m_random_field_h.h"
#include "m_field_make.h"
#include "game_h.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mRF_DIRECT_ERROR 100

enum {
  mRF_GATE_NONE,
  mRF_GATE1_TYPE0,
  mRF_GATE1_TYPE1,
  mRF_GATE2_TYPE0,
  mRF_GATE2_TYPE1,
  mRF_GATE3_TYPE0,

  mRF_GATE_TYPE_NUM
};

enum {
  mRF_DIRECT_NORTH,
  mRF_DIRECT_WEST,
  mRF_DIRECT_SOUTH,
  mRF_DIRECT_EAST,

  mRF_DIRECT_NUM
};

enum {
  mRF_RIVER0,
  mRF_RIVER1,
  mRF_RIVER2,
  mRF_RIVER3,
  mRF_RIVER4,
  mRF_RIVER5,
  mRF_RIVER6,

  mRF_RIVER_NUM
};

enum {
  mRF_FIELD_STEP1,  /* first level */
  mRF_FIELD_STEP2,  /* second level*/
  mRF_FIELD_STEP3,  /* third level */
  mRF_FIELD_STEP4,  /* fourth level */

  mRF_FIELD_STEP_NUM
};

typedef struct gate_s {
  int ut0;
  int ut1;
} mRF_gate_c;

extern void mRF_MakeRandomField(mFM_combination_c* combi_table, mFM_combo_info_c* combo_info, int combo_count, GAME* game);
extern u32 mRF_Type2BlockInfo(u8 type);
extern int mRF_SearchPond(int* ut_x, int* ut_z, int block_x, int block_z);
extern mRF_gate_c* mRF_BlockTypeDirect2GateData(int* gate_count, u8 block_type, int direct);
extern void mRF_CheckBeastRoad();
extern int mRF_RiverIdx2NextDirect(int river_idx);
extern int mRF_BlockType2RiverNextDirect(u8 type);
extern void mRF_IslandBgData_To_VillageData();
extern int mRF_CheckFieldStep3();

extern mFM_combo_info_c data_combi_table[];
extern int data_combi_table_number;

#ifdef __cplusplus
}
#endif

#endif
