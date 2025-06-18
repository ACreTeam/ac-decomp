#ifndef JSUIOSBASE_H
#define JSUIOSBASE_H

#include "types.h"
#include "JSystem/JSupport/JSUStreamEnum.h"

#ifdef __cplusplus
class JSUIosBase {
  public:
    inline JSUIosBase() : mState(GOOD) {
    }

    virtual ~JSUIosBase() {
    }

    bool isGood() {
        return !this->mState;
    }
    void clrState(EIoState ioState) {
        this->mState &= ~ioState;
    }
    void setState(EIoState ioState) {
        this->mState |= ioState;
    }

    u8 mState;
};
#endif

#endif
