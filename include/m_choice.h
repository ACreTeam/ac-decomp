#ifndef M_CHOICE_H
#define M_CHOICE_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct choice_s mChoice_c; // TODO

enum choice {
  mChoice_CHOICE0,
  mChoice_CHOICE1,
  mChoice_CHOICE2,
  mChoice_CHOICE3,

  mChoice_CHOICE_NUM
};

extern mChoice_c* mChoice_Get_base_window_p();
extern int mChoice_Get_ChoseNum(mChoice_c* choice);

#ifdef __cplusplus
}
#endif

#endif
