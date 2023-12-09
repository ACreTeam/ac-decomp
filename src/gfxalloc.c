#include "gfxalloc.h"
#include "types.h"

extern Gfx* gfxopen(Gfx* gfxpp) {
  return gfxpp + 1;
}

extern Gfx* gfxclose(Gfx* gfxp, Gfx* gfxp_new) {
  if (gfxp + 1 != gfxp_new) {
    gSPBranchList(gfxp, gfxp_new);
    return gfxp_new;
  }

  gSPNoOp(gfxp);
  return gfxp;
}

extern Gfx* gfxalloc(Gfx** gfxpp, size_t size) {
  u8* ptr;
  Gfx* dst;

  size = ALIGN_NEXT(size, 8);
  ptr = (u8*)(*gfxpp + 1);
  dst = (Gfx*)(ptr + size);
  gSPBranchList(*gfxpp, dst);

  *gfxpp = dst;
  return (Gfx*)ptr;
}
