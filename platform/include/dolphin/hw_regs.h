/* Shadow override of include/dolphin/hw_regs.h for arm64.
 * On GC the register macros cast to fixed MMIO addresses (0xCC00xxxx).
 * On arm64 those are unmapped; redirect to platform-owned dummy arrays. */
#ifndef _DOLPHIN_HW_REGS_H_
#define _DOLPHIN_HW_REGS_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dummy backing storage — defined in platform/src/os/os_shim.cpp */
extern volatile uint16_t plat_VIRegs[64];
extern volatile uint32_t plat_PIRegs[16];
extern volatile uint16_t plat_MEMRegs[64];
extern volatile uint16_t plat_DSPRegs[32];
extern volatile uint32_t plat_DIRegs[16];
extern volatile uint32_t plat_SIRegs[0x100];
extern volatile uint32_t plat_EXIRegs[0x40];
extern volatile uint32_t plat_AIRegs[8];

#define __VIRegs   plat_VIRegs
#define __PIRegs   plat_PIRegs
#define __MEMRegs  plat_MEMRegs
#define __DSPRegs  plat_DSPRegs
#define __DIRegs   plat_DIRegs
#define __SIRegs   plat_SIRegs
#define __EXIRegs  plat_EXIRegs
#define __AIRegs   plat_AIRegs

#ifdef __cplusplus
}
#endif

/* Offsets for __VIRegs[i] — unchanged from original */
#define VI_VERT_TIMING         (0)
#define VI_DISP_CONFIG         (1)
#define VI_HORIZ_TIMING_0L     (2)
#define VI_HORIZ_TIMING_0U     (3)
#define VI_HORIZ_TIMING_1L     (4)
#define VI_HORIZ_TIMING_1U     (5)
#define VI_VERT_TIMING_ODD     (6)
#define VI_VERT_TIMING_ODD_U   (7)
#define VI_VERT_TIMING_EVEN    (8)
#define VI_VERT_TIMING_EVEN_U  (9)
#define VI_BBI_ODD    (10)
#define VI_BBI_ODD_U  (11)
#define VI_BBI_EVEN   (12)
#define VI_BBI_EVEN_U (13)
#define VI_TOP_FIELD_BASE_LEFT    (14)
#define VI_TOP_FIELD_BASE_LEFT_U  (15)
#define VI_TOP_FIELD_BASE_RIGHT   (16)
#define VI_TOP_FIELD_BASE_RIGHT_U (17)
#define VI_BTTM_FIELD_BASE_LEFT   (18)
#define VI_BTTM_FIELD_BASE_LEFT_U (19)
#define VI_BTTM_FIELD_BASE_RIGHT  (20)
#define VI_BTTM_FIELD_BASE_RIGHT_U (21)
#define VI_VERT_COUNT  (22)
#define VI_HORIZ_COUNT (23)
#define VI_DISP_INT_0  (24)
#define VI_DISP_INT_0U (25)
#define VI_DISP_INT_1  (26)
#define VI_DISP_INT_1U (27)
#define VI_DISP_INT_2  (28)
#define VI_DISP_INT_2U (29)
#define VI_DISP_INT_3  (30)
#define VI_DISP_INT_3U (31)
#define VI_HSW  (36)
#define VI_HSR  (37)
#define VI_FCT_0  (38)
#define VI_FCT_0U (39)
#define VI_FCT_1  (40)
#define VI_FCT_1U (41)
#define VI_FCT_2  (42)
#define VI_FCT_2U (43)
#define VI_FCT_3  (44)
#define VI_FCT_3U (45)
#define VI_FCT_4  (46)
#define VI_FCT_4U (47)
#define VI_FCT_5  (48)
#define VI_FCT_5U (49)
#define VI_FCT_6  (50)
#define VI_FCT_6U (51)
#define VI_CLOCK_SEL (54)
#define VI_DTV_STAT  (55)
#define VI_WIDTH     (56)

/* Offsets for __DSPRegs[i] */
#define DSP_MAILBOX_IN_HI   (0)
#define DSP_MAILBOX_IN_LO   (1)
#define DSP_MAILBOX_OUT_HI  (2)
#define DSP_MAILBOX_OUT_LO  (3)
#define DSP_CONTROL_STATUS  (5)
#define DSP_ARAM_SIZE        (9)
#define DSP_ARAM_MODE       (11)
#define DSP_ARAM_REFRESH    (13)
#define DSP_ARAM_DMA_MM_HI   (16)
#define DSP_ARAM_DMA_MM_LO   (17)
#define DSP_ARAM_DMA_ARAM_HI (18)
#define DSP_ARAM_DMA_ARAM_LO (19)
#define DSP_ARAM_DMA_SIZE_HI (20)
#define DSP_ARAM_DMA_SIZE_LO (21)
#define DSP_DMA_START_HI    (24)
#define DSP_DMA_START_LO    (25)
#define DSP_DMA_CONTROL_LEN (27)
#define DSP_DMA_BYTES_LEFT  (29)
#define DSP_DMA_START_FLAG  (0x8000)

#endif /* _DOLPHIN_HW_REGS_H_ */
