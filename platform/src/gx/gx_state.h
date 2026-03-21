#pragma once
/* GX state machine: captures all GX API calls so the Metal renderer can
 * translate them to draw commands.  Stage 1: struct definition only. */
#include "platform/platform.h"
#include <dolphin/gx.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
#include <vector>

/* Vertex attribute format record */
struct GXVtxAttr {
    GXAttr     attr;
    GXAttrType type;
    GXCompCnt  compCnt;
    GXCompType compType;
    uint8_t    frac;
};

/* Current GX render state */
struct GXState {
    /* Vertex format */
    GXVtxAttr  vtxDesc[GX_VA_MAX_ATTR];
    GXVtxAttr  vtxFmt[8][GX_VA_MAX_ATTR];

    /* Current primitive batch */
    GXPrimitive primType;
    GXVtxFmt    primFmt;
    uint16_t    primCount;

    /* Transforms */
    float projMtx[4][4];
    GXProjectionType projType;
    float posMtx[10][3][4];   /* 10 pos matrix slots */
    uint32_t curMtxIdx;
    float viewport[6];        /* left, top, wd, ht, nearZ, farZ */

    /* TEV */
    uint8_t numTevStages;
    uint8_t numTexGens;
    uint8_t numChans;

    /* Pixel */
    GXBool      zCompare;
    GXCompare   zFunc;
    GXBool      zUpdate;
    GXBlendMode blendMode;
    GXBlendFactor blendSrc, blendDst;
    GXBool     colorUpdate, alphaUpdate;

    /* Cull / scissor */
    GXCullMode cullMode;
    uint32_t scissorL, scissorT, scissorW, scissorH;

    /* Clear color */
    GXColor clearColor;
    uint32_t clearZ;

    /* Texture cache handle (opaque pointer, managed by gx_texture.cpp) */
    void* texCache;

    GXState() { reset(); }
    void reset();
};

/* Global GX state singleton */
GXState& gx_state(void);

#endif /* __cplusplus */
