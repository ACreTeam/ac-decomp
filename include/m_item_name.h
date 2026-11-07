#ifndef M_ITEM_NAME_H
#define M_ITEM_NAME_H

#include "types.h"
#include "m_actor_type.h"

#if VERSION >= VER_GAFP01_00
#include "m_gender.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define mIN_ITEM_NAME_LEN 16

extern u8 itemName_paper[];
extern u8 itemName_money[];
extern u8 itemName_tool[];
extern u8 itemName_fish[];
extern u8 itemName_cloth[];
extern u8 itemName_etc[];
extern u8 itemName_carpet[];
extern u8 itemName_wall[];
extern u8 itemName_fruit[];
extern u8 itemName_plant[];
extern u8 itemName_minidisk[];
extern u8 itemName_dummy[];
extern u8 itemName_ticket[];
extern u8 itemName_insect[];
extern u8 itemName_hukubukuro[];
extern u8 itemName_kabu[];

extern u8 ftrName_table[];
extern u8 ftrName2_table[];

enum item_article {
#if VERSION >= VER_GAFP01_00
  mIN_ARTICLE_UNSPECIFIED = -1,
#endif
  mIN_ARTICLE_NONE,
  mIN_ARTICLE_A,
  mIN_ARTICLE_AN,
  mIN_ARTICLE_THE,
  mIN_ARTICLE_SOME,

  mIN_ARTICLE_NUM
};

extern void mIN_copy_name_str(u8* str, mActor_name_t item_no);
extern int mIN_get_item_article(mActor_name_t item_no);
#if VERSION >= VER_GAFP01_00
extern int mIN_get_item_article_def(mActor_name_t item_no);
extern int mIN_get_item_article_indef(mActor_name_t item_no);
extern int mIN_get_item_gender(mActor_name_t item_no);
#endif

#ifdef __cplusplus
}
#endif

#endif
