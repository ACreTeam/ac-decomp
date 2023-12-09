#include "THA_GA.h"
#include "types.h"

/* TODO: fabricate unused methods */

extern void THA_GA_ct(THA_GA* this, Gfx* p, size_t n) {
  THA_ct(&this->tha, (char*)p, n);
}

extern int THA_GA_isCrash(THA_GA* this) {
  return THA_isCrash(&this->tha);
}

extern int THA_GA_getFreeBytes(THA_GA* this) {
  return THA_getFreeBytes(&this->tha);
}
