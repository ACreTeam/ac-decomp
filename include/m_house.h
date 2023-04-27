#ifndef M_HOUSE_H
#define M_HOUSE_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * House arrangement byte breakdown
 * 
 * PX = player x
 * HX = house x
 * 
 * xx xx xx xx
 * P3 P2 P1 P0
 * 
 * Example:
 * 01 11 10 00
 * P3 P2 P1 P0
 * H1 H3 H2 H0
 **/

enum {
  mHS_HOUSE0, /* Top-left house */
  mHS_HOUSE1, /* Top-right house */
  mHS_HOUSE2, /* Bottom-left house */
  mHS_HOUSE3, /* Bottom-right house */

  mHS_HOUSE_NUM
};

extern void mHS_house_init();
extern int mHS_get_arrange_idx(int player_no);
extern int mHS_get_pl_no(int house_no);
extern int mHS_get_pl_no_detail(int home_no);
extern int mHS_set_use(int player_no, int house_no);

#ifdef __cplusplus
}
#endif

#endif
