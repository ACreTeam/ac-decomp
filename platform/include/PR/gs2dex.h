/* Shadow PR/gs2dex.h - S2DEX2 sprite/background API stubs for arm64 port. */
#ifndef _PR_GS2DEX_H_
#define _PR_GS2DEX_H_

#include <PR/mbi.h>

#ifdef __cplusplus
extern "C" {
#endif

/* S2DEX2 ucode entry points (stubbed - emu64 handles S2DEX) */

/* S2DEX2 block BG structure (copy or non-scaled) */
typedef struct {
    uint16_t  imageX;       /* source X (Q10.2) */
    uint16_t  imageW;       /* source width (Q10.2 + 1) */
    int16_t   frameX;       /* frame X (S10.2) */
    uint16_t  frameW;       /* frame width (Q10.2) */
    uint16_t  imageY;       /* source Y (Q10.2) */
    uint16_t  imageH;       /* source height (Q10.2 + 1) */
    int16_t   frameY;       /* frame Y (S10.2) */
    uint16_t  frameH;       /* frame height (Q10.2) */
    void*     imagePtr;     /* DRAM pointer to image */
    uint16_t  imageLoad;    /* load type (G_BGLT_*) */
    uint8_t   imageFmt;     /* G_IM_FMT_* */
    uint8_t   imageSiz;     /* G_IM_SIZ_* */
    uint8_t   imagePal;     /* palette number */
    uint8_t   imageFlip;    /* flip flags */
    uint16_t  tmemW;        /* TMEM width for scale mode */
    uint16_t  tmemH;        /* TMEM height for scale mode */
    uint16_t  imageStride;  /* stride in texels */
    uint16_t  imageTileH;   /* tile height */
} uObjBg_t;

/* S2DEX2 scale BG structure (1-cycle/2-cycle scale mode) */
typedef struct {
    uint16_t  imageX;
    uint16_t  imageW;
    int16_t   frameX;
    uint16_t  frameW;
    uint16_t  imageY;
    uint16_t  imageH;
    int16_t   frameY;
    uint16_t  frameH;
    void*     imagePtr;
    uint16_t  imageLoad;
    uint8_t   imageFmt;
    uint8_t   imageSiz;
    uint8_t   imagePal;
    uint8_t   imageFlip;
    uint16_t  scaleW;       /* horizontal scale (Q10.5) */
    uint16_t  scaleH;       /* vertical scale (Q10.5) */
    int32_t   imageYorig;   /* original Y for scrolling */
    uint8_t   padding[4];
} uObjScaleBg_t;

typedef union {
    uObjBg_t      b;    /* block BG */
    uObjScaleBg_t s;    /* scale BG */
    long long int force_structure_alignment[4];
} uObjBg;

/* Sprite object */
typedef struct {
    float    objX, objY;
    float    scaleW, scaleH;
    uint16_t imageW, imageH;
    uint32_t imageBase;
    uint8_t  imageFmt, imageSiz, imagePal, imageFlip;
} uObjSprite;

/* ObjRenderMode flags */
#define G_OBJRM_NOTXCLAMP   0x01
#define G_OBJRM_BILERP0     0x02
#define G_OBJRM_BILERP1     0x04
#define G_OBJRM_SHRINKSTEP  0x08
#define G_OBJRM_NOINTERSECT 0x10
#define G_OBJRM_ANTIALIAS   0x00  /* No equivalent — stub to 0 */
#define G_OBJRM_BILERP      (G_OBJRM_BILERP0 | G_OBJRM_BILERP1)

/* S2DEX2 background rendering macros (emu64 handles the actual drawing) */
#define gSPBgRect1Cyc(pkt, bg) do { (void)(pkt); (void)(bg); } while(0)
#define gSPBgRectCopy(pkt, bg) do { (void)(pkt); (void)(bg); } while(0)

#ifdef __cplusplus
}
#endif

#endif /* _PR_GS2DEX_H_ */
