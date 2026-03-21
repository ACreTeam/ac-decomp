/* GX TEV state capture. Stage 1: store to GXState. Stage 9: emit MSL. */
#include "gx_state.h"
#include <dolphin/gx.h>

extern "C" {

void GXSetTevOp(GXTevStageID id, GXTevMode mode) { (void)id; (void)mode; }
void GXSetTevColorIn(GXTevStageID id, GXTevColorArg a, GXTevColorArg b,
                     GXTevColorArg c, GXTevColorArg d) {
    (void)id; (void)a; (void)b; (void)c; (void)d;
}
void GXSetTevAlphaIn(GXTevStageID id, GXTevAlphaArg a, GXTevAlphaArg b,
                     GXTevAlphaArg c, GXTevAlphaArg d) {
    (void)id; (void)a; (void)b; (void)c; (void)d;
}
void GXSetTevColorOp(GXTevStageID id, GXTevOp op, GXTevBias bias,
                     GXTevScale scale, GXBool clamp, GXTevRegID out) {
    (void)id; (void)op; (void)bias; (void)scale; (void)clamp; (void)out;
}
void GXSetTevAlphaOp(GXTevStageID id, GXTevOp op, GXTevBias bias,
                     GXTevScale scale, GXBool clamp, GXTevRegID out) {
    (void)id; (void)op; (void)bias; (void)scale; (void)clamp; (void)out;
}
void GXSetTevOrder(GXTevStageID id, GXTexCoordID tc, GXTexMapID tm,
                   GXChannelID ch) {
    (void)id; (void)tc; (void)tm; (void)ch;
}
void GXSetTevColor(GXTevRegID id, GXColor c)       { (void)id; (void)c; }
void GXSetTevColorS10(GXTevRegID id, GXColorS10 c) { (void)id; (void)c; }
void GXSetTevKColor(GXTevKColorID id, GXColor c)   { (void)id; (void)c; }
void GXSetTevKColorSel(GXTevStageID id, GXTevKColorSel sel) { (void)id; (void)sel; }
void GXSetTevKAlphaSel(GXTevStageID id, GXTevKAlphaSel sel) { (void)id; (void)sel; }
void GXSetTevSwapMode(GXTevStageID id, GXTevSwapSel ras, GXTevSwapSel tex) {
    (void)id; (void)ras; (void)tex;
}
void GXSetTevSwapModeTable(GXTevSwapSel id, GXTevColorChan r, GXTevColorChan g,
                            GXTevColorChan b, GXTevColorChan a) {
    (void)id; (void)r; (void)g; (void)b; (void)a;
}
void GXSetTevIndirect(GXTevStageID ts, GXIndTexStageID is, GXIndTexFormat fmt,
                      GXIndTexBiasSel bs, GXIndTexMtxID mi, GXIndTexWrap ws,
                      GXIndTexWrap wt, GXBool addprev, GXBool utclod,
                      GXIndTexAlphaSel as) {
    (void)ts; (void)is; (void)fmt; (void)bs; (void)mi; (void)ws; (void)wt;
    (void)addprev; (void)utclod; (void)as;
}
void GXSetTevDirect(GXTevStageID ts) { (void)ts; }
void GXSetIndTexOrder(GXIndTexStageID is, GXTexCoordID tc, GXTexMapID tm) {
    (void)is; (void)tc; (void)tm;
}
void GXSetIndTexCoordScale(GXIndTexStageID is, GXIndTexScale sx, GXIndTexScale sy) {
    (void)is; (void)sx; (void)sy;
}
void GXSetIndTexMtx(GXIndTexMtxID id, const void* mtx, s8 scaleExp) {
    (void)id; (void)mtx; (void)scaleExp;
}
void GXSetNumIndStages(u8 n) { (void)n; }

void GXSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op,
                       GXCompare comp1, u8 ref1) {
    (void)comp0; (void)ref0; (void)op; (void)comp1; (void)ref1;
}

} /* extern "C" */
