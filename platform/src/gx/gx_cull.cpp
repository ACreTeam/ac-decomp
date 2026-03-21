/* GX cull and scissor state. */
#include "gx_state.h"
#include <dolphin/gx.h>

extern "C" {

void GXSetCullMode(GXCullMode mode) { gx_state().cullMode = mode; }

void GXSetScissor(u32 left, u32 top, u32 wd, u32 ht) {
    gx_state().scissorL = left;
    gx_state().scissorT = top;
    gx_state().scissorW = wd;
    gx_state().scissorH = ht;
}

void GXSetScissorBoxOffset(s32 xoffset, s32 yoffset) {
    (void)xoffset; (void)yoffset;
}

void GXSetClipMode(GXClipMode mode) { (void)mode; }

} /* extern "C" */
