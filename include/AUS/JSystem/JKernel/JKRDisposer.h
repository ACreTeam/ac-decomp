#ifndef JKRDISPOSER_H
#define JKRDISPOSER_H

#include "types.h"
#include "JSystem/JSupport/JSUList.h"

#ifdef __cplusplus
extern "C" {

class JKRHeap;

class JKRDisposer {
  public:
    JKRDisposer();
    virtual ~JKRDisposer();

  public:
    JKRHeap* mRootHeap;                 // _4
    JSULink<JKRDisposer> mPointerLinks; // _8
};
}
#endif

#endif
