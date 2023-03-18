#ifndef GFXALLOC_H
#define GFXALLOC_H

#include "types.h"
#include "PR/mbi.h"

#ifdef __cplusplus
extern "C" {
#endif

extern Gfx* gfxopen(Gfx* gfxp);
extern Gfx* gfxclose(Gfx* gfxp, Gfx* gfxp_new);
extern Gfx* gfxalloc(Gfx** gfxpp, size_t size);

#ifdef __cplusplus
};
#endif

#endif
