/* GX geometry: vertex descriptor / format state + GXBegin/GXEnd. */
#include "gx_state.h"
#include "gx_draw_internal.h"
#include <dolphin/gx.h>
#include <string.h>

extern "C" {

void GXSetVtxDesc(GXAttr attr, GXAttrType type) {
    for (int i = 0; i < GX_VA_MAX_ATTR; i++) {
        if (gx_state().vtxDesc[i].attr == attr || gx_state().vtxDesc[i].attr == GX_VA_NULL) {
            gx_state().vtxDesc[i].attr = attr;
            gx_state().vtxDesc[i].type = type;
            return;
        }
    }
}

void GXSetVtxDescv(const GXVtxDescList* list) {
    memset(gx_state().vtxDesc, 0, sizeof(gx_state().vtxDesc));
    for (int i = 0; list[i].attr != GX_VA_NULL; i++) {
        gx_state().vtxDesc[i].attr = list[i].attr;
        gx_state().vtxDesc[i].type = list[i].type;
    }
}

void GXClearVtxDesc(void) {
    memset(gx_state().vtxDesc, 0, sizeof(gx_state().vtxDesc));
}

void GXSetVtxAttrFmt(GXVtxFmt vtxfmt, GXAttr attr, GXCompCnt cnt,
                     GXCompType type, u8 frac) {
    if ((int)vtxfmt < 8) {
        for (int i = 0; i < GX_VA_MAX_ATTR; i++) {
            if (gx_state().vtxFmt[vtxfmt][i].attr == attr ||
                gx_state().vtxFmt[vtxfmt][i].attr == GX_VA_NULL) {
                gx_state().vtxFmt[vtxfmt][i].attr     = attr;
                gx_state().vtxFmt[vtxfmt][i].compCnt  = cnt;
                gx_state().vtxFmt[vtxfmt][i].compType = type;
                gx_state().vtxFmt[vtxfmt][i].frac     = frac;
                return;
            }
        }
    }
}

void GXSetVtxAttrFmtv(GXVtxFmt vtxfmt, const GXVtxAttrFmtList* list) {
    if ((int)vtxfmt >= 8) return;
    memset(gx_state().vtxFmt[vtxfmt], 0, sizeof(gx_state().vtxFmt[0]));
    for (int i = 0; list[i].attr != GX_VA_NULL; i++) {
        gx_state().vtxFmt[vtxfmt][i].attr     = list[i].attr;
        gx_state().vtxFmt[vtxfmt][i].compCnt  = list[i].cnt;
        gx_state().vtxFmt[vtxfmt][i].compType = list[i].type;
        gx_state().vtxFmt[vtxfmt][i].frac     = list[i].frac;
    }
}

void GXSetArray(GXAttr attr, const void* data, u32 size, u8 stride) {
    (void)attr; (void)data; (void)size; (void)stride;
    /* Indexed array pointers — not yet used in direct-mode fast path */
}

void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts) {
    gx_state().primType  = type;
    gx_state().primFmt   = vtxfmt;
    gx_state().primCount = nverts;
    plat_gx_begin_draw(type);
}

void GXEnd(void) {
    plat_gx_end_draw(gx_state().primType);
}

void GXSetLineWidth(u8 width, GXTexOffset off)  { (void)width; (void)off; }
void GXSetPointSize(u8 size, GXTexOffset off)   { (void)size; (void)off; }
void GXEnableTexOffsets(GXTexCoordID c, GXBool lb, GXBool pt) {
    (void)c; (void)lb; (void)pt;
}

} /* extern "C" */
