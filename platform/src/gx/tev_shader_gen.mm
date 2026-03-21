/* TEV shader generator: hashes GX TEV state and produces / caches MSL pipelines.
 * Stage 1: empty.  Stage 9: implement dynamic MSL generation. */
#import <Metal/Metal.h>
#include "platform/platform.h"

extern "C" {

/* TODO Stage 9: given a snapshot of GX TEV state, return a cached
 * MTLRenderPipelineState* for use in the draw call. */
void* plat_tev_get_pipeline(void* tev_state_snapshot) {
    (void)tev_state_snapshot;
    return nullptr;
}

} /* extern "C" */
