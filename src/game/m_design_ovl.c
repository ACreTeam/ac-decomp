#include "m_design_ovl.h"

#include "m_debug.h"
#include "padmgr.h"

#include "libultra/libultra.h"
#include "audio.h"
#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_needlework_ovl.h"

#define mDE_POS_MIN 0
#define mDE_POS_MAX 31
#define mDE_DESIGN_TEXELS (mNW_ORIGINAL_DESIGN_WIDTH * mNW_ORIGINAL_DESIGN_HEIGHT)

#define mDE_POS2TEXEL(x, y) ((((x) & 7) + ((y) & 7) * 8 + ((((x) & 0x18) >> 3) + (((y) & 0x18) >> 3) * 4) * 0x40) >> 1)

u16 mDE_SinCosTBL[] = {
    0,    6,    12,   18,   25,   31,   37,   43,   49,   56,   62,   68,   74,   80,   86,   92,   97,   103,  109,
    115,  120,  126,  131,  136,  142,  147,  152,  157,  162,  167,  171,  176,  181,  185,  189,  193,  197,  201,
    205,  209,  212,  216,  219,  222,  225,  228,  231,  234,  236,  238,  241,  243,  244,  246,  248,  249,  251,
    252,  253,  254,  254,  255,  255,  255,  256,  255,  255,  255,  254,  254,  253,  252,  251,  249,  248,  246,
    244,  243,  241,  238,  236,  234,  231,  228,  225,  222,  219,  216,  212,  209,  205,  201,  197,  193,  189,
    185,  181,  176,  171,  167,  162,  157,  152,  147,  142,  136,  131,  126,  120,  115,  109,  103,  97,   92,
    86,   80,   74,   68,   62,   56,   49,   43,   37,   31,   25,   18,   12,   6,    0,    -6,   -12,  -18,  -25,
    -31,  -37,  -43,  -49,  -56,  -62,  -68,  -74,  -80,  -86,  -92,  -97,  -103, -109, -115, -120, -126, -131, -136,
    -142, -147, -152, -157, -162, -167, -171, -176, -181, -185, -189, -193, -197, -201, -205, -209, -212, -216, -219,
    -222, -225, -228, -231, -234, -236, -238, -241, -243, -244, -246, -248, -249, -251, -252, -253, -254, -254, -255,
    -255, -255, -256, -255, -255, -255, -254, -254, -253, -252, -251, -249, -248, -246, -244, -243, -241, -238, -236,
    -234, -231, -228, -225, -222, -219, -216, -212, -209, -205, -201, -197, -193, -189, -185, -181, -176, -171, -167,
    -162, -157, -152, -147, -142, -136, -131, -126, -120, -115, -109, -103, -97,  -92,  -86,  -80,  -74,  -68,  -62,
    -56,  -49,  -43,  -37,  -31,  -25,  -18,  -12,  -6,   0,    6,    12,   18,   25,   31,   37,   43,   49,   56,
    62,   68,   74,   80,   86,   92,   97,   103,  109,  115,  120,  126,  131,  136,  142,  147,  152,  157,  162,
    167,  171,  176,  181,  185,  189,  193,  197,  201,  205,  209,  212,  216,  219,  222,  225,  228,  231,  234,
    236,  238,  241,  243,  244,  246,  248,  249,  251,  252,  253,  254,  254,  255,  255,  255
};
u8 mDE_pen_2[] = { 1, 1, 1, 1 };
u8 mDE_pen_3[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
u8 mDE_heart[] = { 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x01,
                   0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                   0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                   0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01,
                   0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                   0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00,
                   0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                   0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00,
                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
u8 mDE_star[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
                  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01,
                  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                  0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,
                  0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
                  0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00 };
u8 mDE_circle[] = { 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,
                    0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
                    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                    0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
                    0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00 };
u8 mDE_square[] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                    0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };
u8 mDE_kao1[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
                  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00,
                  0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
                  0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01,
                  0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00,
                  0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
u8 mDE_kao2[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01,
                  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
u8 mDE_kao3[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
                  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                  0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x01,
                  0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                  0x00, 0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
u8 mDE_kao4[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
u8 mDE_kao5[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
                  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

// clang-format off
u8 mDE_paint_mizutama[0x100] = { 
    0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0, 
    0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0, 
    0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0, 
    0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0, 
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1, 
    1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1, 
    1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1, 
    1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1, 
    1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1, 
    1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1, 
    1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1, 
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1, 
    0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0, 
    0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0, 
    0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0, 
    0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 
};

u8 mDE_paint_mask_cat_mask[0x400] = {  
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1, 
    1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1, 
    1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1, 
    1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1, 
    1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1, 
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1, 
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1, 
    1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1, 
    1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1, 
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1, 
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1, 
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1, 
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1, 
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1, 
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1, 
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1, 
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1, 
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1, 
    1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1, 
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1, 
    1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1, 
    1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1, 
    1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1, 
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1, 
    1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1, 
    1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1, 
    1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1, 
    1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1, 
    1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1, 
    1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1, 
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 
};
// clang-format on

mDE_Ovl_c de_ovl_data;

#define MDE_SIN(x) (mDE_SinCosTBL[(x)])
#define MDE_COS(x) (mDE_SinCosTBL[(x) + 0x40])
#define MDE_90DEG (0x40)
enum {
    mDE_MOVE_DIR_UP,
    mDE_MOVE_DIR_DOWN,
    mDE_MOVE_DIR_LEFT,
    mDE_MOVE_DIR_RIGHT,

    mDE_MOVE_DIR_NUM
};

enum {
    mDE_MAIN_MODE_0,
    mDE_MAIN_MODE_1,
    mDE_MAIN_MODE_2,
    mDE_MAIN_MODE_3,
    mDE_MAIN_MODE_4,
};
void mDE_setup_action(mDE_Ovl_c* design_ovl, int param_2);

static void mDE_pallet_RGB5A3_to_RGB24(mDE_Ovl_c* design_ovl) {
    int i;

    for (i = 0; i < mNW_PALETTE_COUNT; i++) {
        u16 color = design_ovl->palette_p[i];

        if (color & 0x8000) {
            // fully opaque, a1r5g5b5
            design_ovl->rgb8_pal[i].r = (((color >> 10) & 0x1F) * 255) / 31;
            design_ovl->rgb8_pal[i].g = (((color >> 5) & 0x1F) * 255) / 31;
            design_ovl->rgb8_pal[i].b = (((color >> 0) & 0x1F) * 255) / 31;
        } else {
            // transparent color, a3r4g4b4
            design_ovl->rgb8_pal[i].r = ((color >> 8) & 0xF) * 17;
            design_ovl->rgb8_pal[i].g = ((color >> 4) & 0xF) * 17;
            design_ovl->rgb8_pal[i].b = ((color >> 0) & 0xF) * 17;
        }
    }
}

static u8 mDE_judge_stick(mDE_Ovl_c* design_ovl) {
    design_ovl->_6B8++;
    if (design_ovl->move_pR >= 0.1f && design_ovl->_6B5 == 0) {
        design_ovl->_6B5 = 1;
        design_ovl->_6B8 = 0;
        return TRUE;
    }

    if (design_ovl->move_pR > 0.9f && design_ovl->_6C0 >= design_ovl->_6C4 && design_ovl->_6B5 &&
        design_ovl->_6B8 > design_ovl->_6BC) {
        design_ovl->_6B8 = 0;
        return TRUE;
    }

    if (design_ovl->_6B8 > design_ovl->_6BC) {
        design_ovl->_6B8 = 0;
    }

    return FALSE;
}

static int mDE_judge_stick_full(mDE_Ovl_c* design_ovl) {
    if (design_ovl->move_pR >= 0.9f) {
        design_ovl->_6C0++;
        if (design_ovl->_6C0 > design_ovl->_6C4) {
            design_ovl->_6C0 = design_ovl->_6C4;
        }

        return TRUE;
    }

    return FALSE;
}

static int mDE_judge_stick_nuetral(mDE_Ovl_c* design_ovl) {
    if (design_ovl->move_pR < 0.1f) {
        design_ovl->_6C0 = 0;
        design_ovl->_6B4 = 0;
        design_ovl->_6B5 = 0;
        return TRUE;
    }

    design_ovl->_6B4 = 1;
    return FALSE;
}

static int mDE_cursor_move_check(mDE_Ovl_c* design_ovl, int move_dir) {
    int min = 0;

    if (design_ovl->main_mode_act == mDE_MAIN_MODE_0) {
        switch (design_ovl->_6A0) {
            case 1:
                min = 1;
                break;
            case 2:
                min = 2;
                break;
        }
    }

    switch (move_dir) {
        case mDE_MOVE_DIR_UP:
            if (gamePT->pads[PAD0].now.stick_y > 0 && design_ovl->cursor_y > min) {
                return TRUE;
            }
            break;
        case mDE_MOVE_DIR_DOWN:
            if (gamePT->pads[PAD0].now.stick_y < 0 && design_ovl->cursor_y < mDE_POS_MAX) {
                return TRUE;
            }
            break;
        case mDE_MOVE_DIR_LEFT:
            if (gamePT->pads[PAD0].now.stick_x < 0 && design_ovl->cursor_x > 0) {
                return TRUE;
            }
            break;
        case mDE_MOVE_DIR_RIGHT:
            if (gamePT->pads[PAD0].now.stick_x > 0 && design_ovl->cursor_x < (mDE_POS_MAX - min)) {
                return TRUE;
            }
            break;
    }

    return FALSE;
}

static void mDE_cursor_move(mDE_Ovl_c* design_ovl, int move_dir) {
    switch (move_dir) {
        case mDE_MOVE_DIR_UP:
            design_ovl->cursor_y--;
            design_ovl->_654 += 5;
            break;
        case mDE_MOVE_DIR_DOWN:
            design_ovl->cursor_y++;
            design_ovl->_654 -= 5;
            break;
        case mDE_MOVE_DIR_LEFT:
            design_ovl->cursor_x--;
            design_ovl->_650 -= 5;
            break;
        case mDE_MOVE_DIR_RIGHT:
            design_ovl->cursor_x++;
            design_ovl->_650 += 5;
            break;
    }
}

static void mDE_cursor_analog_move_hosei(f32* move_x, f32* move_y, f32 corrected_val, f32 min, f32 max) {
    if (*move_y > min && *move_y < max) {
        *move_y = corrected_val;
    }

    if (*move_y > -max && *move_y < -min) {
        *move_y = -corrected_val;
    }

    if (*move_x > min && *move_x < max) {
        *move_x = corrected_val;
    }

    if (*move_x > -max && *move_x < -min) {
        *move_x = -corrected_val;
    }
}

static void mDE_cursor_analog_move(mDE_Ovl_c* design_ovl) {
    int bounds = 0;
    f32 move_x;
    f32 move_y;
    int _660;
    int _664;
    int x;
    int y;

    if (design_ovl->main_mode_act == mDE_MAIN_MODE_0) {
        switch (design_ovl->_6A0) {
            case 1:
                bounds = 1;
                break;
            case 2:
                bounds = 2;
                break;
        }
    }

    _660 = (int)(design_ovl->_660 / 5.0f);
    _664 = -(int)(design_ovl->_664 / 5.0f);
    move_x = gamePT->pads[PAD0].now.stick_x / 72.0f;
    move_y = gamePT->pads[PAD0].now.stick_y / 72.0f;
    // _664 = -_664;

    if (!GETREG(NMREG, 16)) {
        mDE_cursor_analog_move_hosei(&move_x, &move_y, 0.5f, 0.44f, 0.56f);
        mDE_cursor_analog_move_hosei(&move_x, &move_y, 0.75f, 0.725f, 0.775f);
        mDE_cursor_analog_move_hosei(&move_x, &move_y, 0.25f, 0.225f, 0.275f);
        mDE_cursor_analog_move_hosei(&move_x, &move_y, 0.8f, 0.775f, 0.825f);
        mDE_cursor_analog_move_hosei(&move_x, &move_y, 0.2f, 0.175f, 0.225f);
    }

    if (gamePT->pads[PAD0].now.stick_y != 0) {
        move_x *= 10.0f;
    } else {
        move_x *= 5.0f;
    }

    if (gamePT->pads[PAD0].now.stick_x != 0) {
        move_y *= 10.0f;
    } else {
        move_y *= 5.0f;
    }

    if (_664 < bounds) {
        design_ovl->cursor_y = bounds;
        design_ovl->_654 = -design_ovl->cursor_y * 5;
    } else if (_664 > mDE_POS_MAX) {
        design_ovl->cursor_y = mDE_POS_MAX;
        design_ovl->_654 = -design_ovl->cursor_y * 5;
    }

    if (_660 < 0) {
        design_ovl->cursor_x = 0;
        design_ovl->_650 = design_ovl->cursor_x * 5;
    } else if (_660 > (mDE_POS_MAX - bounds)) {
        design_ovl->cursor_x = mDE_POS_MAX - bounds;
        design_ovl->_650 = design_ovl->cursor_x * 5;
    }

    y = gamePT->pads[PAD0].now.stick_y;
    if ((y > 0 && design_ovl->cursor_y > bounds) || (y < 0 && design_ovl->cursor_y < mDE_POS_MAX)) {
        if (GETREG(NMREG, 19)) {
            if (GETREG(NMREG, 18)) {
                design_ovl->_664 += gamePT->pads[PAD0].now.stick_y * (10.0f / 72.0f);
            } else if (GETREG(NMREG, 17)) {
                design_ovl->_664 += gamePT->pads[PAD0].now.stick_y * (5.0f / 72.0f);
            } else {
                design_ovl->_664 += gamePT->pads[PAD0].now.stick_y * ((1.0f + GETREG(NMREG, 20) * 0.1f) / 72.0f);
            }
        } else {
            design_ovl->_664 += move_y;
        }
    }

    x = gamePT->pads[PAD0].now.stick_x;
    if ((x < 0 && design_ovl->cursor_x > 0) || (x > 0 && design_ovl->cursor_x < (mDE_POS_MAX - bounds))) {
        if (GETREG(NMREG, 19)) {
            if (GETREG(NMREG, 18)) {
                design_ovl->_660 += gamePT->pads[PAD0].now.stick_x * (10.0f / 72.0f);
            } else if (GETREG(NMREG, 17)) {
                design_ovl->_660 += gamePT->pads[PAD0].now.stick_x * (5.0f / 72.0f);
            } else {
                design_ovl->_660 += gamePT->pads[PAD0].now.stick_x * ((1.0f + GETREG(NMREG, 20) * 0.1f) / 72.0f);
            }
        } else {
            design_ovl->_660 += move_x;
        }
    }
}

static int mDE_cursor_waku_genten_rotate(mDE_Ovl_c* design_ovl, int move_dir) {
    if (design_ovl->cursor_y == design_ovl->_67C && design_ovl->cursor_x == design_ovl->_678) {
        switch (move_dir) {
            case 4:
                if (design_ovl->_6D9 == 2) {
                    design_ovl->_6D8 = 1;
                    return TRUE;
                }
                break;
            case 5:
                if (design_ovl->_6D9 == 3) {
                    design_ovl->_6D8 = 0;
                    return TRUE;
                }
                break;
            case 6:
                if (design_ovl->_6D9 == 0) {
                    design_ovl->_6D8 = 3;
                    return TRUE;
                }
                break;
            case 7:
                if (design_ovl->_6D9 == 1) {
                    design_ovl->_6D8 = 2;
                    return TRUE;
                }
                break;
        }
    }

    return FALSE;
}

static int mDE_cursor_waku_rotate(mDE_Ovl_c* design_ovl, int move_dir) {
    switch (move_dir) {
        case mDE_MOVE_DIR_UP:
            if (design_ovl->cursor_y == design_ovl->_67C && (design_ovl->_6D8 == 0 || design_ovl->_6D8 == 2)) {
                switch (design_ovl->_6D9) {
                    case 0:
                        design_ovl->_6D8 = 1;
                        break;
                    case 2:
                        design_ovl->_6D8 = 3;
                        break;
                }

                return TRUE;
            }
            break;
        case mDE_MOVE_DIR_DOWN:
            if (design_ovl->cursor_y == design_ovl->_67C && (design_ovl->_6D8 == 1 || design_ovl->_6D8 == 3)) {
                switch (design_ovl->_6D9) {
                    case 1:
                        design_ovl->_6D8 = 0;
                        break;
                    case 3:
                        design_ovl->_6D8 = 2;
                        break;
                }

                return TRUE;
            }
            break;
        case mDE_MOVE_DIR_LEFT:
            if (design_ovl->cursor_x == design_ovl->_678 && (design_ovl->_6D8 == 1 || design_ovl->_6D8 == 0)) {
                switch (design_ovl->_6D9) {
                    case 1:
                        design_ovl->_6D8 = 3;
                        break;
                    case 0:
                        design_ovl->_6D8 = 2;
                        break;
                }

                return TRUE;
            }
            break;
        case mDE_MOVE_DIR_RIGHT:
            if (design_ovl->cursor_x == design_ovl->_678 && (design_ovl->_6D8 == 3 || design_ovl->_6D8 == 2)) {
                switch (design_ovl->_6D9) {
                    case 3:
                        design_ovl->_6D8 = 1;
                        break;
                    case 2:
                        design_ovl->_6D8 = 0;
                        break;
                }

                return TRUE;
            }
            break;
    }

    return FALSE;
}

static int mDE_get_pal_on_cursor(mDE_Ovl_c* design_ovl, int x, int y) {
    int idx;

    if (x < mDE_POS_MIN || x > mDE_POS_MAX || y < mDE_POS_MIN || y > mDE_POS_MAX) {
        return 0;
    }

    idx = mDE_POS2TEXEL(x, y);
    if (x & 1) {
        return (design_ovl->work_texture.data[idx] >> 0) & 0x0F;
    } else {
        return (design_ovl->work_texture.data[idx] >> 4) & 0x0F;
    }
}

static void mDE_set_pal_on_cursor(mDE_Ovl_c* design_ovl, int x, int y, int pal) {
    int idx;

    if (x < mDE_POS_MIN || x > mDE_POS_MAX || y < mDE_POS_MIN || y > mDE_POS_MAX) {
        return;
    }

    idx = mDE_POS2TEXEL(x, y);
    if (x & 1) {
        design_ovl->work_texture.data[idx] &= 0xF0;
        design_ovl->work_texture.data[idx] |= (pal << 0);
    } else {
        design_ovl->work_texture.data[idx] &= 0x0F;
        design_ovl->work_texture.data[idx] |= (pal << 4);
    }
}

typedef struct design_bounds_s {
    int x0;
    int x1;
    int y0;
    int y1;
} mDE_bounds_c;

static void mDE_farbado(mDE_Ovl_c* r20 /*design_pal*/, int r24 /*x*/, int y, int r21 /*pal*/) {
#define mDE_DESIGN_TEXELS_2 (16 * 16)
    mDE_bounds_c pos_tbl[mDE_DESIGN_TEXELS_2];
    int r29 = 0;
    int r28 = 1;
    int r17;
    int r31;
    int r19;
    int r25;

    pos_tbl[0].x0 = r24;
    pos_tbl[0].x1 = r24;
    pos_tbl[0].y0 = y;
    pos_tbl[0].y1 = y;
    r31 = mDE_get_pal_on_cursor(r20, r24, y);

    do {
        mDE_bounds_c* bounds = &pos_tbl[r29];
        int r27 = bounds->x0;
        int r26 = bounds->x1;
        int r30 = bounds->y0;
        int r24 = bounds->y1;
        int r23 = r27 - 1;
        int r22 = r26 + 1;

        if (++r29 == mDE_DESIGN_TEXELS_2) {
            r29 = 0;
        }

        if (r21 != mDE_get_pal_on_cursor(r20, r27, r30)) {
            while (r26 < mDE_POS_MAX + 1) {
                r26++;
                if (r31 != mDE_get_pal_on_cursor(r20, r26, r30)) {
                    r26--;
                    break;
                }
            }

            while (r27 > 0) {
                r27--;
                if (r31 != mDE_get_pal_on_cursor(r20, r27, r30)) {
                    r27++;
                    break;
                }
            }

            for (r17 = r27; r17 <= r26; r17++) {
                mDE_set_pal_on_cursor(r20, r17, r30, r21);
            }
            // issue here
            r25 = r30 - 1;
            if (r25 >= mDE_POS_MIN) {
                if (r25 == r24) {
                    r17 = r27;
                    r19 = r25 + 1;
                    while (r17 <= r23) {
                        for (; r17 < r23; r17++) {
                            if (r31 == mDE_get_pal_on_cursor(r20, r17, r25)) {
                                break;
                            }
                        }
                        if (r31 != mDE_get_pal_on_cursor(r20, r17, r25)) {
                            break;
                        }

                        pos_tbl[r28].x0 = r17;

                        for (; r17 <= r23; r17++) {
                            if (r31 != mDE_get_pal_on_cursor(r20, r17, r25)) {
                                break;
                            }
                        }
                        pos_tbl[r28].x1 = r17 - 1;
                        pos_tbl[r28].y0 = r25;
                        pos_tbl[r28].y1 = r19;
                        r28++;
                        if (r28 == mDE_DESIGN_TEXELS_2) {
                            r28 = 0;
                        }
                    }

                    r17 = r22;
                    r19 = r25 + 1;

                    while (r17 <= r26) {
                        for (; r17 < r26; r17++) {
                            if (r31 == mDE_get_pal_on_cursor(r20, r17, r25)) {
                                break;
                            }
                        }

                        if (r31 != mDE_get_pal_on_cursor(r20, r17, r25)) {
                            break;
                        }

                        pos_tbl[r28].x0 = r17;

                        for (; r17 <= r26; r17++) {
                            if (r31 != mDE_get_pal_on_cursor(r20, r17, r25)) {
                                break;
                            }
                        }
                        pos_tbl[r28].x1 = r17 - 1;
                        pos_tbl[r28].y0 = r25;
                        pos_tbl[r28].y1 = r19;
                        r28++;
                        if (r28 == mDE_DESIGN_TEXELS_2) {
                            r28 = 0;
                        }
                    }
                } else {
                    r17 = r27;
                    r19 = r25 + 1;

                    while (r17 <= r26) {
                        for (; r17 < r26; r17++) {
                            if (r31 == mDE_get_pal_on_cursor(r20, r17, r25)) {
                                break;
                            }
                        }

                        if (r31 != mDE_get_pal_on_cursor(r20, r17, r25)) {
                            break;
                        }

                        pos_tbl[r28].x0 = r17;

                        for (; r17 <= r26; r17++) {
                            if (r31 != mDE_get_pal_on_cursor(r20, r17, r25)) {
                                break;
                            }
                        }
                        pos_tbl[r28].x1 = r17 - 1;
                        pos_tbl[r28].y0 = r25;
                        pos_tbl[r28].y1 = r19;
                        r28++;
                        if (r28 == mDE_DESIGN_TEXELS_2) {
                            r28 = 0;
                        }
                    }
                }
            }
            r25 = r30 + 1;
            if (r25 <= (mDE_POS_MAX + 1)) {
                if (r25 == r24) {
                    r19 = r27;
                    r24 = r25 - 1;

                    while (r19 <= r23) {
                        for (; r19 < r23; r19++) {
                            if (r31 == mDE_get_pal_on_cursor(r20, r19, r25)) {
                                break;
                            }
                        }

                        if (r31 != mDE_get_pal_on_cursor(r20, r19, r25)) {
                            break;
                        }

                        pos_tbl[r28].x0 = r19;

                        for (; r19 <= r26; r19++) {
                            if (r31 != mDE_get_pal_on_cursor(r20, r19, r25)) {
                                break;
                            }
                        }
                        pos_tbl[r28].x1 = r19 - 1;
                        pos_tbl[r28].y0 = r25;
                        pos_tbl[r28].y1 = r24;
                        r28++;
                        if (r28 == mDE_DESIGN_TEXELS_2) {
                            r28 = 0;
                        }
                    }

                    r19 = r22;
                    r22 = r25 - 1;

                    while (r19 <= r26) {
                        for (; r19 < r26; r19++) {
                            if (r31 == mDE_get_pal_on_cursor(r20, r19, r25)) {
                                break;
                            }
                        }

                        if (r31 != mDE_get_pal_on_cursor(r20, r19, r25)) {
                            break;
                        }

                        pos_tbl[r28].x0 = r19;

                        for (; r19 <= r26; r19++) {
                            if (r31 != mDE_get_pal_on_cursor(r20, r19, r25)) {
                                break;
                            }
                        }
                        pos_tbl[r28].x1 = r19 - 1;
                        pos_tbl[r28].y0 = r25;
                        pos_tbl[r28].y1 = r22;
                        r28++;
                        if (r28 == mDE_DESIGN_TEXELS_2) {
                            r28 = 0;
                        }
                    }
                } else {
                    r19 = r27;
                    r22 = r25 - 1;

                    while (r19 <= r26) {
                        for (; r19 < r26; r19++) {
                            if (r31 == mDE_get_pal_on_cursor(r20, r19, r25)) {
                                break;
                            }
                        }

                        if (r31 != mDE_get_pal_on_cursor(r20, r19, r25)) {
                            break;
                        }

                        pos_tbl[r28].x0 = r19;

                        for (; r19 <= r26; r19++) {
                            if (r31 != mDE_get_pal_on_cursor(r20, r19, r25)) {
                                break;
                            }
                        }
                        pos_tbl[r28].x1 = r19 - 1;
                        pos_tbl[r28].y0 = r25;
                        pos_tbl[r28].y1 = r22;
                        r28++;
                        if (r28 == mDE_DESIGN_TEXELS_2) {
                            r28 = 0;
                        }
                    }
                }
            }
        }

    } while (r29 != r28);
}

void mDE_set_texture_template(mDE_Ovl_c* design_ovl, u8* param_2, int offsetX, int offsetY, int param_5, int param_6,
                              int param_7, int param_8) {
    int i;
    for (i = 0; i < param_5 * param_6; i++) {
        int y = offsetY + (i / param_5) - param_8;
        int x = offsetX + (i % param_6) - param_7;
        if (param_2[i]) {
            mDE_set_pal_on_cursor(design_ovl, x, y, design_ovl->_6A4);
        }
    }
}

void mDE_mask_cat_mask(mDE_Ovl_c* design_ovl) {
    int i;
    for (i = 0; i < ARRAY_COUNT(mDE_paint_mask_cat_mask); i++) {
        int y = i / 32;
        int x = i % 32;
        if (mDE_paint_mask_cat_mask[i]) {
            mDE_set_pal_on_cursor(design_ovl, x, y, 0);
        }
    }
}

void mDE_paint(mDE_Ovl_c* design_ovl, int pal) {
    int i;
    int j;
    switch (design_ovl->_6A1) {
        case 0: {
            mDE_farbado(design_ovl, design_ovl->cursor_x, design_ovl->cursor_y, design_ovl->_6A4);
        } break;
        case 1: {
            for (i = 0; i < 0x20; i++) {
                for (j = 0; j < 0x20; j++) {
                    if ((i / 4) % 2 == 0) {
                        mDE_set_pal_on_cursor(design_ovl, i, j, pal);
                    }
                }
            }
        } break;
        case 2: {
            for (i = 0; i < 0x20; i++) {
                for (j = 0; j < 0x20; j++) {
                    if ((j / 4) % 2 == 0) {
                        mDE_set_pal_on_cursor(design_ovl, i, j, pal);
                    }
                }
            }
        } break;
        case 3: {
            for (i = 0; i < 0x20; i++) {
                for (j = 0; j < 0x20; j++) {
                    if ((i / 4) % 2 == 0 || (j / 4) % 2 == 0) {
                        mDE_set_pal_on_cursor(design_ovl, i, j, pal);
                    }
                }
            }
        } break;
        case 4: {
            mDE_set_texture_template(design_ovl, mDE_paint_mizutama, 0x00, 0x00, 0x10, 0x10, 0x00, 0x00);
            mDE_set_texture_template(design_ovl, mDE_paint_mizutama, 0x10, 0x00, 0x10, 0x10, 0x00, 0x00);
            mDE_set_texture_template(design_ovl, mDE_paint_mizutama, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00);
            mDE_set_texture_template(design_ovl, mDE_paint_mizutama, 0x00, 0x10, 0x10, 0x10, 0x00, 0x00);
        } break;
        default: {
            for (i = 0; i < 0x20; i++) {
                for (j = 0; j < 0x20; j++) {
                    mDE_set_pal_on_cursor(design_ovl, i, j, pal);
                }
            }
        } break;
    }
}

void mDE_print_texture() {
    return;
}

void mDE_save_maskcat_texture(mDE_Ovl_c* design_ovl) {
    int i, j;
    for (i = 0; i < 0x20; i++) {
        for (j = 0; j < 0x20; j++) {
            if (mDE_get_pal_on_cursor(design_ovl, i, j) == 0) {
                mDE_set_pal_on_cursor(design_ovl, i, j, 0xf);
            }
        }
    }
}

void mDE_set_undo_texture(mDE_Ovl_c* design_ovl) {
    bcopy(&design_ovl->work_texture, &design_ovl->undo_texture, sizeof(design_ovl->work_texture));
}

void mDE_undo(mDE_Ovl_c* design_ovl) {
    design_ovl->_6DA = !design_ovl->_6DA;
    if (design_ovl->_6DA) {
        sAdo_SysTrgStart(0x45b);
    } else {
        sAdo_SysTrgStart(0x45c);
    }
    bcopy(&design_ovl->work_texture, &design_ovl->texture, sizeof(design_ovl->work_texture));
    bcopy(&design_ovl->undo_texture, &design_ovl->work_texture, sizeof(design_ovl->undo_texture));
    bcopy(&design_ovl->texture, &design_ovl->undo_texture, sizeof(design_ovl->texture));
}

void mDE_main_pen_move(mDE_Ovl_c* design_ovl) {
    design_ovl->_699 = 0;
    design_ovl->_698 = 1;
    if (chkTrigger(BUTTON_A)) {
        design_ovl->_6CC = 1;
        mDE_set_undo_texture(design_ovl);
        switch (design_ovl->_6A0) {
            case 1: {
                sAdo_SysTrgStart(0x451);
            } break;
            case 2: {
                sAdo_SysTrgStart(0x452);
            } break;
            default: {
                sAdo_SysTrgStart(0x450);
            } break;
        }
    } else if (chkButton(BUTTON_A) && design_ovl->_6CC) {
        mDE_get_pal_on_cursor(design_ovl, design_ovl->cursor_x, design_ovl->cursor_y);
        switch (design_ovl->_6A0) {
            case 1: {
                mDE_set_texture_template(design_ovl, mDE_pen_2, design_ovl->cursor_x, design_ovl->cursor_y, 2, 2, 0, 1);
            } break;
            case 2: {
                mDE_set_texture_template(design_ovl, mDE_pen_3, design_ovl->cursor_x, design_ovl->cursor_y, 3, 3, 0, 2);
            } break;
            default: {
                mDE_set_pal_on_cursor(design_ovl, design_ovl->cursor_x, design_ovl->cursor_y, design_ovl->_6A4);
            } break;
        }
    }
    switch (design_ovl->_6A0) {
        case 1: {
            if (design_ovl->cursor_y == mDE_POS_MIN) {
                mDE_cursor_move(design_ovl, 1);
            }
            if (design_ovl->cursor_x == mDE_POS_MAX) {
                mDE_cursor_move(design_ovl, 2);
            }
            design_ovl->_680 = design_ovl->_650;
            switch (design_ovl->cursor_x) {
                case mDE_POS_MAX: {
                    design_ovl->_688 = 1;
                } break;
                default: {
                    design_ovl->_688 = 2;
                } break;
            }
            switch (design_ovl->cursor_y) {
                case mDE_POS_MIN: {
                    design_ovl->_68C = 1;
                    design_ovl->_684 = design_ovl->_654;
                } break;
                default: {
                    design_ovl->_68C = 2;
                    design_ovl->_684 = design_ovl->_654 + 5;
                } break;
            }
        } break;
        case 2: {
            if (design_ovl->cursor_y == mDE_POS_MIN) {
                mDE_cursor_move(design_ovl, 1);
                mDE_cursor_move(design_ovl, 1);
            } else if (design_ovl->cursor_y == mDE_POS_MIN + 1) {
                mDE_cursor_move(design_ovl, 1);
            }
            if (design_ovl->cursor_x == mDE_POS_MAX) {
                mDE_cursor_move(design_ovl, 2);
                mDE_cursor_move(design_ovl, 2);
            } else if (design_ovl->cursor_x == mDE_POS_MAX - 1) {
                mDE_cursor_move(design_ovl, 2);
            }
            design_ovl->_680 = design_ovl->_650;
            switch (design_ovl->cursor_x) {
                case mDE_POS_MAX: {
                    design_ovl->_688 = 1;
                } break;
                case mDE_POS_MAX - 1: {
                    design_ovl->_688 = 2;
                } break;
                default: {
                    design_ovl->_688 = 3;
                } break;
            }
            switch (design_ovl->cursor_y) {
                case mDE_POS_MIN: {
                    design_ovl->_68C = 1;
                    design_ovl->_684 = design_ovl->_654;
                } break;
                case mDE_POS_MIN + 1: {
                    design_ovl->_68C = 2;
                    design_ovl->_684 = design_ovl->_654 + 5;
                } break;
                default: {
                    design_ovl->_68C = 3;
                    design_ovl->_684 = design_ovl->_654 + 10;
                } break;
            }
        } break;
        default: {
            design_ovl->_680 = design_ovl->_650;
            design_ovl->_684 = design_ovl->_654;
            design_ovl->_688 = 1;
            design_ovl->_68C = 1;
        } break;
    }
}

void mDE_main_nuri_move(mDE_Ovl_c* design_ovl) {
    design_ovl->_699 = 1;
    if (chkTrigger(BUTTON_A)) {
        sAdo_SysTrgStart(0x455);
        mDE_set_undo_texture(design_ovl);
        mDE_paint(design_ovl, design_ovl->_6A4);
    }
}

void mDE_waku_set_start(mDE_Ovl_c* design_ovl) {
    if (design_ovl->_678 > design_ovl->cursor_x) {
        design_ovl->_680 = design_ovl->_650;
    } else {
        design_ovl->_680 = design_ovl->_658;
    }
    if (design_ovl->_67C > design_ovl->cursor_y) {
        design_ovl->_684 = design_ovl->_654;
    } else {
        design_ovl->_684 = design_ovl->_65C;
    }
}

void mDE_waku_set_main_start_end(mDE_Ovl_c* design_ovl, int* x_start, int* y_start, int* x_end, int* y_end) {
    if (design_ovl->_678 > design_ovl->cursor_x) {
        *x_start = design_ovl->cursor_x;
        *x_end = design_ovl->_678;
    } else {
        *x_start = design_ovl->_678;
        *x_end = design_ovl->cursor_x;
    }

    if (design_ovl->_67C > design_ovl->cursor_y) {
        *y_start = design_ovl->cursor_y;
        *y_end = design_ovl->_67C;
    } else {
        *y_start = design_ovl->_67C;
        *y_end = design_ovl->cursor_y;
    }
}

void mDE_waku_line(mDE_Ovl_c* design_ovl, int _param_2, int _param_3, int param_4, int param_5) {
    int iVar4;
    int param_2;
    int param_3;
    int x;
    int y;
    int iVar2;
    int iVar1;
    int i;
    if (param_4 > _param_2) {
        x = param_4 - _param_2;
        iVar2 = 1;
    } else {
        iVar2 = -1;
        x = _param_2 - param_4;
    }

    if (param_5 > _param_3) {
        y = param_5 - _param_3;
        iVar1 = 1;
    } else {
        iVar1 = -1;
        y = _param_3 - param_5;
    }
    param_2 = _param_2;
    param_3 = _param_3;
    if (x >= y) {
        iVar4 = -x;
        for (i = 0; i <= x; i++) {
            mDE_set_pal_on_cursor(design_ovl, param_2, param_3, design_ovl->_6A4);
            iVar4 += y * 2;
            param_2 += iVar2;
            if (iVar4 >= 0) {
                param_3 += iVar1;
                iVar4 += -(x * 2);
            }
        }
    } else {
        iVar4 = -y;
        for (i = 0; i <= y; i++) {
            mDE_set_pal_on_cursor(design_ovl, param_2, param_3, design_ovl->_6A4);
            iVar4 += x * 2;
            param_3 += iVar1;
            if (iVar4 >= 0) {
                param_2 += iVar2;
                iVar4 += -(y * 2);
            }
        }
    }
}

void mDE_waku_circle_write(mDE_Ovl_c* design_ovl, u8 fill) {
    // stack variables
    int x_start;
    int y_start;
    int x_end;
    int y_end;

    // registers
    int v1;
    int v2;
    int x_width;
    int y_width;
    int mid_x;
    int mid_y;
    int half_x_width;
    int half_y_width;
    s16 i;

    if (GETREG(NMREG, 2)) {
        v1 = GETREG(NMREG, 2);
    } else {
        v1 = 45;
    }
    mDE_waku_set_main_start_end(design_ovl, &x_start, &y_start, &x_end, &y_end);
    x_width = ABS(x_end - x_start);
    y_width = ABS(y_end - y_start);
    half_x_width = x_width >> 1;
    half_y_width = y_width >> 1;
    mid_x = x_start + half_x_width;
    mid_y = y_start + half_y_width;
    v2 = ((half_x_width + half_y_width) >> 1) - ((half_x_width + half_y_width) >> 3) -
         (ABS(half_x_width - half_y_width) >> 1) - 1;

    if (GETREG(NMREG, 3)) {
        v2 -= GETREG(NMREG, 3);
    } else {
        v2 -= 4;
    }

    for (i = 0; i < MDE_90DEG; i += MDE_90DEG / (s16)((half_x_width + half_y_width - v2) | 1)) {
        int cos_v = (v1 + half_x_width * MDE_COS(i)) >> 8;
        int sin_v = (v1 + half_y_width * MDE_SIN(i)) >> 8;
        if (fill) {
            int j;
            for (j = mid_x - cos_v; j <= mid_x + cos_v + (x_width & 1); j++) {
                mDE_set_pal_on_cursor(design_ovl, j, mid_y - sin_v, design_ovl->_6A4);
                mDE_set_pal_on_cursor(design_ovl, j, mid_y + sin_v + (y_width & 1), design_ovl->_6A4);
            }
        } else {
            mDE_set_pal_on_cursor(design_ovl, mid_x + cos_v + (x_width & 1), mid_y + sin_v + (y_width & 1),
                                  design_ovl->_6A4);
            mDE_set_pal_on_cursor(design_ovl, mid_x + cos_v + (x_width & 1), mid_y - sin_v, design_ovl->_6A4);
            mDE_set_pal_on_cursor(design_ovl, mid_x - cos_v, mid_y + sin_v + (y_width & 1), design_ovl->_6A4);
            mDE_set_pal_on_cursor(design_ovl, mid_x - cos_v, mid_y - sin_v, design_ovl->_6A4);
        }
    }
}

void mDE_waku_square_write(mDE_Ovl_c* design_ovl, u8 fill) {
    int x_start;
    int y_start;
    int x_end;
    int y_end;
    int j;
    int i;
    mDE_waku_set_main_start_end(design_ovl, &x_start, &y_start, &x_end, &y_end);
    if (x_start > x_end || y_start > y_end) {
        return;
    }
    if (fill) {
        for (j = y_start; j <= y_end; j++) {
            for (i = x_start; i <= x_end; i++) {
                mDE_set_pal_on_cursor(design_ovl, i, j, design_ovl->_6A4);
            }
        }
    } else {
        for (i = x_start; i <= x_end; i++) {
            mDE_set_pal_on_cursor(design_ovl, i, y_start, design_ovl->_6A4);
            mDE_set_pal_on_cursor(design_ovl, i, y_end, design_ovl->_6A4);
        }
        for (j = y_start; j <= y_end; j++) {
            mDE_set_pal_on_cursor(design_ovl, x_start, j, design_ovl->_6A4);
            mDE_set_pal_on_cursor(design_ovl, x_end, j, design_ovl->_6A4);
        }
    }
}

void mDE_main_waku_move(mDE_Ovl_c* design_ovl) {
    if (design_ovl->_6A2 == 4) {
        design_ovl->_699 = 9;
    } else {
        design_ovl->_699 = 2;
    }
    if (design_ovl->_69A) {
        mDE_waku_set_start(design_ovl);
        design_ovl->_688 = ABS(design_ovl->_678 - design_ovl->cursor_x) + 1;
        design_ovl->_68C = ABS(design_ovl->_67C - design_ovl->cursor_y) + 1;
    }
    if (chkTrigger(BUTTON_A)) {
        if (design_ovl->_69A == 0) {
            design_ovl->_658 = design_ovl->_650;
            design_ovl->_65C = design_ovl->_654;
            design_ovl->_678 = design_ovl->cursor_x;
            design_ovl->_67C = design_ovl->cursor_y;
            sAdo_SysTrgStart(0x454);
            design_ovl->_698 = 1;
            design_ovl->_680 = 0;
            design_ovl->_684 = 0;
            design_ovl->_688 = 0;
            design_ovl->_68C = 0;
        } else {
            mDE_set_undo_texture(design_ovl);
            design_ovl->_6D8 = 0;
            design_ovl->_6D9 = 0;
            switch (design_ovl->_6A2) {
                case 0: {
                    mDE_waku_square_write(design_ovl, 0);
                    sAdo_SysTrgStart(0x455);
                } break;
                case 2: {
                    mDE_waku_square_write(design_ovl, 1);
                    sAdo_SysTrgStart(0x455);
                } break;
                case 1: {
                    mDE_waku_circle_write(design_ovl, 0);
                    sAdo_SysTrgStart(0x455);
                } break;
                case 3: {
                    mDE_waku_circle_write(design_ovl, 1);
                    sAdo_SysTrgStart(0x455);
                } break;
                case 4: {
                    mDE_waku_line(design_ovl, design_ovl->cursor_x, design_ovl->cursor_y, design_ovl->_678,
                                  design_ovl->_67C);
                    sAdo_SysTrgStart(0x455);
                } break;
            }
            design_ovl->_698 = 0;
            design_ovl->_680 = 0;
            design_ovl->_684 = 0;
            design_ovl->_688 = 0;
            design_ovl->_68C = 0;
        }
        design_ovl->_69A = !design_ovl->_69A;
    }

    if (chkTrigger(BUTTON_B) && design_ovl->_69A == TRUE) {
        design_ovl->_69A = 0;
        design_ovl->_698 = 0;
        design_ovl->_680 = 0;
        design_ovl->_684 = 0;
        design_ovl->_688 = 0;
        design_ovl->_68C = 0;
        sAdo_SysTrgStart(0x460);
    }
}

void mDE_main_mark_move(mDE_Ovl_c* design_ovl) {
    if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
        switch (design_ovl->_6A3) {
            case 0: {
                design_ovl->_699 = 0xa;
            } break;
            case 1: {
                design_ovl->_699 = 0xb;
            } break;
            case 2: {
                design_ovl->_699 = 0xc;
            } break;
            case 3: {
                design_ovl->_699 = 0xd;
            } break;
            case 4: {
                design_ovl->_699 = 0xe;
            } break;
        }
    } else {
        switch (design_ovl->_6A3) {
            case 0: {
                design_ovl->_699 = 3;
            } break;
            case 1: {
                design_ovl->_699 = 4;
            } break;
            case 2: {
                design_ovl->_699 = 5;
            } break;
            case 3: {
                design_ovl->_699 = 6;
            } break;
        }
    }
    if (chkTrigger(BUTTON_A)) {
        mDE_set_undo_texture(design_ovl);
        sAdo_SysTrgStart(0x455);
        if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
            switch (design_ovl->_6A3) {
                case 0: {
                    mDE_set_texture_template(design_ovl, mDE_kao1, design_ovl->cursor_x, design_ovl->cursor_y, 0xc, 0xc,
                                             5, 6);
                } break;
                case 1: {
                    mDE_set_texture_template(design_ovl, mDE_kao2, design_ovl->cursor_x, design_ovl->cursor_y, 0xc, 0xc,
                                             5, 6);
                } break;
                case 2: {
                    mDE_set_texture_template(design_ovl, mDE_kao3, design_ovl->cursor_x, design_ovl->cursor_y, 0xc, 0xc,
                                             5, 6);
                } break;
                case 3: {
                    mDE_set_texture_template(design_ovl, mDE_kao4, design_ovl->cursor_x, design_ovl->cursor_y, 0xc, 0xc,
                                             5, 6);
                } break;
                case 4: {
                    mDE_set_texture_template(design_ovl, mDE_kao5, design_ovl->cursor_x, design_ovl->cursor_y, 0xc, 0xc,
                                             5, 6);
                } break;
            }
        } else {
            switch (design_ovl->_6A3) {
                case 0: {
                    mDE_set_texture_template(design_ovl, mDE_heart, design_ovl->cursor_x, design_ovl->cursor_y, 0xc,
                                             0xc, 5, 6);
                } break;
                case 1: {
                    mDE_set_texture_template(design_ovl, mDE_star, design_ovl->cursor_x, design_ovl->cursor_y, 0xc, 0xc,
                                             5, 6);
                } break;
                case 2: {
                    mDE_set_texture_template(design_ovl, mDE_circle, design_ovl->cursor_x, design_ovl->cursor_y, 0xc,
                                             0xc, 5, 6);
                } break;
                case 3: {
                    mDE_set_texture_template(design_ovl, mDE_square, design_ovl->cursor_x, design_ovl->cursor_y, 0xc,
                                             0xc, 5, 6);
                } break;
            }
        }
    }
}

void mDE_main_undo_move(mDE_Ovl_c* design_ovl) {
    design_ovl->_699 = 7;
    if (chkTrigger(BUTTON_A)) {
        mDE_undo(design_ovl);
    }
}

BOOL mDE_mode_tool_check(mDE_Ovl_c* design_ovl, int param_2, int param_3, int param_4, int param_5) {
    u8 x_values[5];
    u8 y_values[5];
    BOOL moved = FALSE;
    x_values[0] = design_ovl->_6A0;
    y_values[0] = 3;
    x_values[1] = design_ovl->_6A1;
    y_values[1] = 6;
    x_values[2] = design_ovl->_6A2;
    y_values[2] = 5;
    if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
        x_values[3] = design_ovl->_6A3;
        y_values[3] = 5;
    } else {
        x_values[3] = design_ovl->_6A3;
        y_values[3] = 4;
    }
    x_values[4] = 0;
    y_values[4] = 1;
    if (design_ovl->_6A7 == 3) {
        if (gamePT->pads[PAD0].now.stick_x < 0 && design_ovl->_69E > param_2) {
            moved = TRUE;
            design_ovl->_69E--;
        }
        if (gamePT->pads[PAD0].now.stick_x > 0 && design_ovl->_69E < param_3 - 1) {
            moved = TRUE;
            design_ovl->_69E++;
        }
        if (gamePT->pads[PAD0].now.stick_y > 0) {
            if (design_ovl->_69F) {
                if (design_ovl->_69E < param_4) {
                    moved = TRUE;
                    design_ovl->_69F--;
                }
            } else if (design_ovl->_69E == 0) {
                moved = TRUE;
                design_ovl->_69F = 4;
            }
        }
        if (gamePT->pads[PAD0].now.stick_y < 0) {
            if (design_ovl->_69F < 4) {
                if (design_ovl->_69E < param_5) {
                    moved = TRUE;
                    design_ovl->_69F++;
                }
            } else {
                moved = TRUE;
                design_ovl->_69E = 0;
                design_ovl->_69F = 0;
            }
        }
    } else if (design_ovl->_6A7 == 0) {
        if (chkTrigger(BUTTON_DLEFT)) {
            if (design_ovl->_69E > param_2) {
                moved = TRUE;
                design_ovl->_69E--;
            } else {
                moved = TRUE;
                design_ovl->_69E = y_values[design_ovl->_69F] - 1;
            }
        }
        if (chkTrigger(BUTTON_DRIGHT)) {
            if (design_ovl->_69E < param_3 - 1) {
                moved = TRUE;
                design_ovl->_69E++;
            } else {
                moved = TRUE;
                design_ovl->_69E = 0;
            }
        }
        if (chkTrigger(BUTTON_DUP)) {
            if (design_ovl->_69F) {
                moved = TRUE;
                design_ovl->_69F--;
                design_ovl->_69E = x_values[design_ovl->_69F];
            } else {
                design_ovl->_69E = 0;
                moved = TRUE;
                design_ovl->_69F = 4;
            }
        }
        if (chkTrigger(BUTTON_DDOWN)) {
            if (design_ovl->_69F < 4) {
                moved = TRUE;
                design_ovl->_69F++;
                design_ovl->_69E = x_values[design_ovl->_69F];
            } else {
                moved = TRUE;
                design_ovl->_69E = 0;
                design_ovl->_69F = 0;
            }
        }
    }
    return moved;
}

void mDE_main_mode_setup_action(mDE_Ovl_c* design_ovl, int param_2) {
    static mDE_OVL_PROC process[] = { mDE_main_pen_move, mDE_main_nuri_move, mDE_main_waku_move, mDE_main_mark_move,
                                      mDE_main_undo_move };
    if (param_2 != 2) {
        design_ovl->_69A = 0;
        design_ovl->_698 = 0;
        design_ovl->_680 = 0;
        design_ovl->_684 = 0;
        design_ovl->_688 = 0;
        design_ovl->_68C = 0;
    }
    design_ovl->_6DA = 0;
    design_ovl->main_mode_act = param_2;
    design_ovl->main_mode_proc = process[param_2];
}

void mde_main_move_sound(mDE_Ovl_c* design_ovl) {
    if (chkButton(BUTTON_A) && design_ovl->main_mode_act == mDE_MAIN_MODE_0) {
        switch (design_ovl->_6A0) {
            case 1: {
                sAdo_SysTrgStart(0x451);
            } break;
            case 2: {
                sAdo_SysTrgStart(0x452);
            } break;
            default: {
                sAdo_SysTrgStart(0x450);
            } break;
        }
    } else {
        sAdo_SysTrgStart(0x453);
    }
}

void mDE_mode_main_shortcut_tool(mDE_Ovl_c* design_ovl, int param_2) {
    int prevAction = param_2 - 1;
    int nextAction = param_2 + 1;
    switch (param_2) {
        case 0: {
            prevAction = 4;
        } break;
        case 4: {
            nextAction = 0;
        } break;
    }

    if (chkTrigger(BUTTON_DLEFT) || chkTrigger(BUTTON_DRIGHT)) {
        mDE_main_mode_setup_action(design_ovl, param_2);
    } else if (chkTrigger(BUTTON_DUP)) {
        mDE_main_mode_setup_action(design_ovl, prevAction);
    } else if (chkTrigger(BUTTON_DDOWN)) {
        mDE_main_mode_setup_action(design_ovl, nextAction);
    }
}

void mDE_cursor_waku(mDE_Ovl_c* design_ovl, int param_2) {
    if (mDE_cursor_waku_rotate(design_ovl, param_2) == FALSE) {
        mDE_cursor_move(design_ovl, param_2);
    }
    mde_main_move_sound(design_ovl);
}

void mDE_cursor_waku_naname(mDE_Ovl_c* design_ovl, int param_2, int param_3, int param_4) {
    if (mDE_cursor_waku_genten_rotate(design_ovl, param_2)) {
        mDE_cursor_move(design_ovl, param_3);
        mDE_cursor_move(design_ovl, param_4);
    } else if (mDE_cursor_waku_rotate(design_ovl, param_3) == FALSE &&
               mDE_cursor_waku_rotate(design_ovl, param_4) == FALSE) {
        mDE_cursor_move(design_ovl, param_3);
        mDE_cursor_move(design_ovl, param_4);
    }
    mde_main_move_sound(design_ovl);
}

void mDE_mode_stick_control_waku(mDE_Ovl_c* design_ovl) {
    if (mDE_cursor_move_check(design_ovl, 3) && mDE_cursor_move_check(design_ovl, 0)) {
        mDE_cursor_waku_naname(design_ovl, 4, 3, 0);
    } else if (mDE_cursor_move_check(design_ovl, 3) && mDE_cursor_move_check(design_ovl, 1)) {
        mDE_cursor_waku_naname(design_ovl, 5, 3, 1);
    } else if (mDE_cursor_move_check(design_ovl, 2) && mDE_cursor_move_check(design_ovl, 0)) {
        mDE_cursor_waku_naname(design_ovl, 6, 2, 0);
    } else if (mDE_cursor_move_check(design_ovl, 2) && mDE_cursor_move_check(design_ovl, 1)) {
        mDE_cursor_waku_naname(design_ovl, 7, 2, 1);
    } else if (mDE_cursor_move_check(design_ovl, 3)) {
        mDE_cursor_waku(design_ovl, 3);
    } else if (mDE_cursor_move_check(design_ovl, 2)) {
        mDE_cursor_waku(design_ovl, 2);
    } else if (mDE_cursor_move_check(design_ovl, 0)) {
        mDE_cursor_waku(design_ovl, 0);
    } else if (mDE_cursor_move_check(design_ovl, 1)) {
        mDE_cursor_waku(design_ovl, 1);
    }
}

void mDE_mode_stick_control(mDE_Ovl_c* design_ovl) {
    if (mDE_cursor_move_check(design_ovl, 3) && mDE_cursor_move_check(design_ovl, 0)) {
        mde_main_move_sound(design_ovl);
        mDE_cursor_move(design_ovl, 3);
        mDE_cursor_move(design_ovl, 0);
    } else if (mDE_cursor_move_check(design_ovl, 3) && mDE_cursor_move_check(design_ovl, 1)) {
        mde_main_move_sound(design_ovl);
        mDE_cursor_move(design_ovl, 3);
        mDE_cursor_move(design_ovl, 1);
    } else if (mDE_cursor_move_check(design_ovl, 2) && mDE_cursor_move_check(design_ovl, 0)) {
        mde_main_move_sound(design_ovl);
        mDE_cursor_move(design_ovl, 2);
        mDE_cursor_move(design_ovl, 0);
    } else if (mDE_cursor_move_check(design_ovl, 2) && mDE_cursor_move_check(design_ovl, 1)) {
        mde_main_move_sound(design_ovl);
        mDE_cursor_move(design_ovl, 2);
        mDE_cursor_move(design_ovl, 1);
    } else if (mDE_cursor_move_check(design_ovl, 3)) {
        mde_main_move_sound(design_ovl);
        mDE_cursor_move(design_ovl, 3);
    } else if (mDE_cursor_move_check(design_ovl, 2)) {
        mde_main_move_sound(design_ovl);
        mDE_cursor_move(design_ovl, 2);
    } else if (mDE_cursor_move_check(design_ovl, 0)) {
        mde_main_move_sound(design_ovl);
        mDE_cursor_move(design_ovl, 0);
    } else if (mDE_cursor_move_check(design_ovl, 1)) {
        mde_main_move_sound(design_ovl);
        mDE_cursor_move(design_ovl, 1);
    }
}

void mDE_mode_stick_control_analog(mDE_Ovl_c* design_ovl) {
    int oldCursorX = design_ovl->cursor_x;
    if (oldCursorX != (int)(design_ovl->_660 / 5.f) || design_ovl->cursor_y != -(int)(design_ovl->_664 / 5.f)) {
        int oldCursorY = design_ovl->cursor_y;
        design_ovl->cursor_x = (int)(design_ovl->_660) / 5;
        design_ovl->cursor_y = -(int)(design_ovl->_664) / 5;
        design_ovl->_650 = design_ovl->cursor_x * 5;
        design_ovl->_654 = -design_ovl->cursor_y * 5;
        switch (design_ovl->_6A0) {
            case 1: {
                sAdo_SysTrgStart(0x451);
            } break;
            case 2: {
                sAdo_SysTrgStart(0x452);
            } break;
            default: {
                sAdo_SysTrgStart(0x450);
            } break;
        }
        mDE_waku_line(design_ovl, oldCursorX, oldCursorY, design_ovl->cursor_x, design_ovl->cursor_y);
    }
    mDE_cursor_analog_move(design_ovl);
}

void mDE_mode_main_move(mDE_Ovl_c* design_ovl) {
    design_ovl->move_pR = gamePT->mcon.move_pR;
    design_ovl->_6C4 = 1;
    if (design_ovl->main_mode_act == mDE_MAIN_MODE_0 && chkButton(BUTTON_A)) {
        design_ovl->_6C4 = 3;
        if (GETREG(NMREG, 0x13)) {
            if (GETREG(NMREG, 0x12)) {
                design_ovl->_6BC = 5;
            } else if (GETREG(NMREG, 0x11)) {
                design_ovl->_6BC = 4;
            } else {
                design_ovl->_6BC = GETREG(NMREG, 0x15);
            }
        } else if (gamePT->pads[PAD0].now.stick_x || gamePT->pads[PAD0].now.stick_y) {
            design_ovl->_6BC = 5;
        } else {
            design_ovl->_6BC = 4;
        }
        if (gamePT->pads[PAD0].now.stick_y == 0 && gamePT->pads[PAD0].now.stick_x == 0) {
            design_ovl->_660 = design_ovl->_650 + 2.5f;
            design_ovl->_664 = design_ovl->_654 - 2.5f;
            design_ovl->_6DC = 0;
        }
    } else {
        if (design_ovl->move_pR > 0.9f) {
            design_ovl->_6BC = 3;
            design_ovl->_660 = design_ovl->_650 + 2.5f;
            design_ovl->_664 = design_ovl->_654 - 2.5f;
        } else {
            design_ovl->_6BC = 4;
            design_ovl->_660 = design_ovl->_650 + 2.5f;
            design_ovl->_664 = design_ovl->_654 - 2.5f;
        }
    }
    mDE_judge_stick_nuetral(design_ovl);
    mDE_judge_stick_full(design_ovl);
    if (mDE_judge_stick(design_ovl)) {
        if (design_ovl->_69A && design_ovl->_699 != 9) {
            mDE_mode_stick_control(design_ovl);
            design_ovl->_6D9 = design_ovl->_6D8;
        } else if (design_ovl->main_mode_act == mDE_MAIN_MODE_0 && chkButton(BUTTON_A)) {
            if (design_ovl->_6DC) {
                mDE_mode_stick_control_analog(design_ovl);
            } else {
                design_ovl->_6DC = 1;
                mDE_mode_stick_control(design_ovl);
                design_ovl->_660 = design_ovl->_650 + 2.5f;
                design_ovl->_664 = design_ovl->_654 - 2.5f;
            }
        } else {
            mDE_mode_stick_control(design_ovl);
        }
    }

    if (chkTrigger(BUTTON_B) && design_ovl->_69A == 0) {
        design_ovl->_6CD = 1;
        design_ovl->_6A4 = mDE_get_pal_on_cursor(design_ovl, design_ovl->cursor_x, design_ovl->cursor_y);
    } else if (chkButton(BUTTON_B) && design_ovl->_69A == 0 && design_ovl->_6CD) {
        design_ovl->_6DB = 1;
        design_ovl->_6A4 = mDE_get_pal_on_cursor(design_ovl, design_ovl->cursor_x, design_ovl->cursor_y);
    } else if (design_ovl->_6DB) {
        design_ovl->_6DB = 0;
        sAdo_SysTrgStart(0x45d);
    }
    design_ovl->_6D4 = 4;
    if (chkTrigger(BUTTON_CDOWN)) {
        design_ovl->_6CE = 1;
        design_ovl->_6A4++;
        design_ovl->_6D0 = 0;
        sAdo_SysTrgStart(0x459);
    } else if (chkButton(BUTTON_CDOWN) && design_ovl->_6CE) {
        if (design_ovl->_6D0 > design_ovl->_6D4) {
            design_ovl->_6A4++;
            design_ovl->_6D0 = 0;
            sAdo_SysTrgStart(0x459);
        } else {
            design_ovl->_6D0++;
        }
    } else {
        design_ovl->_6CE = 0;
    }

    if (chkTrigger(BUTTON_CUP)) {
        design_ovl->_6CF = 1;
        design_ovl->_6A4--;
        design_ovl->_6D0 = 0;
        sAdo_SysTrgStart(0x459);
    } else if (chkButton(BUTTON_CUP) && design_ovl->_6CF) {
        if (design_ovl->_6D0 > design_ovl->_6D4) {
            design_ovl->_6A4--;
            design_ovl->_6D0 = 0;
            sAdo_SysTrgStart(0x459);
        } else {
            design_ovl->_6D0++;
        }
    } else {
        design_ovl->_6CF = 0;
    }

    design_ovl->_6A5 = design_ovl->_6A4;

    if (design_ovl->_6A4 >= 0x10) {
        design_ovl->_6A4 = 1;
    }

    if (design_ovl->_6A4 < 1) {
        design_ovl->_6A4 = 0xf;
    }

    if (design_ovl->_69F == 0) {
        if (mDE_mode_tool_check(design_ovl, 0, 3, 0, 6)) {
            sAdo_SysTrgStart(0x32);
        }
        if (chkTrigger(BUTTON_DLEFT) || chkTrigger(BUTTON_DRIGHT)) {
            design_ovl->_6A0 = design_ovl->_69E;
        }
        mDE_mode_main_shortcut_tool(design_ovl, 0);
    } else if (design_ovl->_69F == 1) {
        if (mDE_mode_tool_check(design_ovl, 0, 6, 3, 5)) {
            sAdo_SysTrgStart(0x32);
        }
        if (chkTrigger(BUTTON_DLEFT) || chkTrigger(BUTTON_DRIGHT)) {
            design_ovl->_6A1 = design_ovl->_69E;
        }
        mDE_mode_main_shortcut_tool(design_ovl, 1);
    } else if (design_ovl->_69F == 2) {
        if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
            if (mDE_mode_tool_check(design_ovl, 0, 5, 6, 5)) {
                sAdo_SysTrgStart(0x32);
            }
        } else {
            if (mDE_mode_tool_check(design_ovl, 0, 5, 6, 4)) {
                sAdo_SysTrgStart(0x32);
            }
        }
        if (chkTrigger(BUTTON_DLEFT) || chkTrigger(BUTTON_DRIGHT)) {
            design_ovl->_6A2 = design_ovl->_69E;
        }
        mDE_mode_main_shortcut_tool(design_ovl, 2);
    } else if (design_ovl->_69F == 3) {
        if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
            if (mDE_mode_tool_check(design_ovl, 0, 5, 5, 1)) {
                sAdo_SysTrgStart(0x32);
            }
        } else {
            if (mDE_mode_tool_check(design_ovl, 0, 4, 5, 1)) {
                sAdo_SysTrgStart(0x32);
            }
        }
        if (chkTrigger(BUTTON_DLEFT) || chkTrigger(BUTTON_DRIGHT)) {
            design_ovl->_6A3 = design_ovl->_69E;
        }
        mDE_mode_main_shortcut_tool(design_ovl, 3);
    } else if (design_ovl->_69F == 4) {
        if (mDE_mode_tool_check(design_ovl, 0, 1, 5, 1) &&
            (chkTrigger(BUTTON_DLEFT) == 0 && chkTrigger(BUTTON_DRIGHT) == 0)) {
            sAdo_SysTrgStart(0x32);
        }
        mDE_mode_main_shortcut_tool(design_ovl, 4);
    }
    if (chkTrigger(BUTTON_X)) {
        design_ovl->_69D = !design_ovl->_69D;
        if (design_ovl->_69D == FALSE) {
            sAdo_SysTrgStart(0x457);
        } else {
            sAdo_SysTrgStart(0x456);
        }
    }
    if (chkTrigger(BUTTON_Y)) {
        mDE_undo(design_ovl);
    }
    if (chkButton(BUTTON_Z)) {
        mDE_print_texture(design_ovl);
    }
    design_ovl->main_mode_proc(design_ovl);
    if (chkButton(BUTTON_B) && design_ovl->_69A == 0 && design_ovl->_6CD) {
        design_ovl->_699 = 8;
    }
}

void mDE_mode_pallet_move(mDE_Ovl_c* design_ovl) {
    int old6A5 = design_ovl->_6A5;
    design_ovl->move_pR = gamePT->mcon.move_pR;
    if (GETREG(NMREG, 0x10)) {
        design_ovl->_6C4 = GETREG(NMREG, 0x10);
    } else {
        design_ovl->_6C4 = 0x18;
    }
    if (GETREG(NMREG, 0x11)) {
        design_ovl->_6BC = GETREG(NMREG, 0x11);
    } else {
        design_ovl->_6BC = 4;
    }
    mDE_judge_stick_nuetral(design_ovl);
    mDE_judge_stick_full(design_ovl);
    if (mDE_judge_stick(design_ovl)) {
        if (gamePT->pads[PAD0].now.stick_y < 0) {
            sAdo_SysTrgStart(0x459);
            old6A5++;
        }
        if (gamePT->pads[PAD0].now.stick_y > 0) {
            sAdo_SysTrgStart(0x459);
            old6A5--;
        }
    }
    design_ovl->_6A5 = old6A5;
    if (old6A5 >= 0x10) {
        design_ovl->_6A5 = 0;
    }
    if (old6A5 < 0) {
        design_ovl->_6A5 = 0xf;
    }
    if (design_ovl->_6A5 == 0 && chkTrigger(BUTTON_A)) {
        sAdo_SysTrgStart(0x458);
        design_ovl->palette_no++;
        if (design_ovl->palette_no >= 0x10) {
            design_ovl->palette_no = 0;
        }
        design_ovl->palette_p = mNW_PaletteIdx2Palette(design_ovl->palette_no);
        mDE_pallet_RGB5A3_to_RGB24(design_ovl);
    }
    if (design_ovl->_6A5 == 0 && chkTrigger(BUTTON_B)) {
        sAdo_SysTrgStart(0x458);
        if (design_ovl->palette_no == 0) {
            design_ovl->palette_no = 0xf;
        } else {
            design_ovl->palette_no--;
        }
        design_ovl->palette_p = mNW_PaletteIdx2Palette(design_ovl->palette_no);
        mDE_pallet_RGB5A3_to_RGB24(design_ovl);
    }
    if (design_ovl->_6A5 && chkTrigger(BUTTON_A)) {
        sAdo_SysTrgStart(0x45a);
        design_ovl->_6A4 = design_ovl->_6A5;
        mDE_setup_action(design_ovl, 0);
    }
}

void mDE_mode_grid_move(mDE_Ovl_c* design_ovl) {
    if (chkTrigger(BUTTON_A)) {
        design_ovl->_69D = !design_ovl->_69D;
        if (design_ovl->_69D == FALSE) {
            sAdo_SysTrgStart(0x457);
        } else {
            sAdo_SysTrgStart(0x456);
        }
    }
}

void mDE_mode_tool_move(mDE_Ovl_c* design_ovl) {
    design_ovl->move_pR = gamePT->mcon.move_pR;
    if (GETREG(NMREG, 0x12)) {
        design_ovl->_6C4 = GETREG(NMREG, 0x12);
    } else {
        design_ovl->_6C4 = 0x18;
    }
    if (GETREG(NMREG, 0x13)) {
        design_ovl->_6BC = GETREG(NMREG, 0x13);
    } else {
        design_ovl->_6BC = 8;
    }
    mDE_judge_stick_nuetral(design_ovl);
    mDE_judge_stick_full(design_ovl);
    if (mDE_judge_stick(design_ovl)) {
        if (design_ovl->_69F == 0) {
            if (mDE_mode_tool_check(design_ovl, 0, 3, 0, 6)) {
                sAdo_SysTrgStart(0x32);
            }
        } else if (design_ovl->_69F == 1) {
            if (mDE_mode_tool_check(design_ovl, 0, 6, 3, 5)) {
                sAdo_SysTrgStart(0x32);
            }
        } else if (design_ovl->_69F == 2) {
            if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
                if (mDE_mode_tool_check(design_ovl, 0, 5, 6, 5)) {
                    sAdo_SysTrgStart(0x32);
                }
            } else {
                if (mDE_mode_tool_check(design_ovl, 0, 5, 6, 4)) {
                    sAdo_SysTrgStart(0x32);
                }
            }
        } else if (design_ovl->_69F == 3) {
            if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
                if (mDE_mode_tool_check(design_ovl, 0, 5, 5, 1)) {
                    sAdo_SysTrgStart(0x32);
                }
            } else {
                if (mDE_mode_tool_check(design_ovl, 0, 4, 5, 1)) {
                    sAdo_SysTrgStart(0x32);
                }
            }
        } else if (design_ovl->_69F == 4) {
            if (mDE_mode_tool_check(design_ovl, 0, 1, 5, 1)) {
                sAdo_SysTrgStart(0x32);
            }
        }
    }

    if (chkTrigger(BUTTON_A)) {
        sAdo_SysTrgStart(0x33);
        switch (design_ovl->_69F) {
            case 0: {
                design_ovl->_6A0 = design_ovl->_69E;
                mDE_main_mode_setup_action(design_ovl, 0);
                mDE_setup_action(design_ovl, 0);
            } break;
            case 1: {
                design_ovl->_6A1 = design_ovl->_69E;
                mDE_main_mode_setup_action(design_ovl, 1);
                mDE_setup_action(design_ovl, 0);
            } break;
            case 2: {
                design_ovl->_6A2 = design_ovl->_69E;
                mDE_main_mode_setup_action(design_ovl, 2);
                mDE_setup_action(design_ovl, 0);
            } break;
            case 3: {
                design_ovl->_6A3 = design_ovl->_69E;
                mDE_main_mode_setup_action(design_ovl, 3);
                mDE_setup_action(design_ovl, 0);
            } break;
            case 4: {
                mDE_main_mode_setup_action(design_ovl, 4);
                mDE_setup_action(design_ovl, 0);
            } break;
        }
    }
}

void mDE_setup_action(mDE_Ovl_c* design_ovl, int param_2) {
    static mDE_OVL_PROC process[] = { mDE_mode_main_move, mDE_mode_pallet_move, mDE_mode_grid_move,
                                      mDE_mode_tool_move };
    if (param_2 >= 4) {
        param_2 = 0;
    }
    if (param_2 < 0) {
        param_2 = 3;
    }
    design_ovl->_6CC = 0;
    design_ovl->_6CD = 0;
    design_ovl->_698 = 0;
    design_ovl->_680 = 0;
    design_ovl->_684 = 0;
    design_ovl->_688 = 0;
    design_ovl->_68C = 0;
    design_ovl->_6A7 = param_2;
    design_ovl->act_proc = process[param_2];
}

void mDE_move_Move(Submenu* submenu, mSM_MenuInfo_c* info) {
    submenu->overlay->move_Move_proc(submenu, info);
}

void mDE_move_tool_decide(mDE_Ovl_c* design_ovl) {
    switch (design_ovl->_69F) {
        case 0: {
            design_ovl->_6A0 = design_ovl->_69E;
            mDE_main_mode_setup_action(design_ovl, 0);
        } break;
        case 1: {
            design_ovl->_6A1 = design_ovl->_69E;
            mDE_main_mode_setup_action(design_ovl, 1);
        } break;
        case 2: {
            design_ovl->_6A2 = design_ovl->_69E;
            mDE_main_mode_setup_action(design_ovl, 2);
        } break;
        case 3: {
            design_ovl->_6A3 = design_ovl->_69E;
            mDE_main_mode_setup_action(design_ovl, 3);
        } break;
        case 4: {
            mDE_main_mode_setup_action(design_ovl, 4);
        } break;
    }
}

void mDE_move_Play(Submenu* submenu, mSM_MenuInfo_c* info) {
    mDE_Ovl_c* design_ovl = submenu->overlay->design_ovl;
    if (submenu->current_menu_type == mSM_OVL_DESIGN) {
        if (submenu->overlay->menu_control.trigger & BUTTON_START) {
            design_ovl->_698 = 0;
            design_ovl->_680 = 0;
            design_ovl->_684 = 0;
            design_ovl->_688 = 0;
            design_ovl->_68C = 0;
            design_ovl->_6CC = 0;
            design_ovl->_6CD = 0;
            mSM_open_submenu(submenu, 0xf, 4, 0);
            info->proc_status = mSM_OVL_PROC_WAIT;
            sAdo_SysTrgStart(2);
        } else if (chkTrigger(BUTTON_R)) {
            if (design_ovl->_6A5) {
                design_ovl->_6A4 = design_ovl->_6A5;
            }
            sAdo_SysTrgStart(0x37);
            mDE_move_tool_decide(design_ovl);
            mDE_setup_action(design_ovl, design_ovl->_6A7 + 1);
        } else if (chkTrigger(BUTTON_L)) {
            if (design_ovl->_6A5) {
                design_ovl->_6A4 = design_ovl->_6A5;
            }
            sAdo_SysTrgStart(0x37);
            mDE_move_tool_decide(design_ovl);
            mDE_setup_action(design_ovl, design_ovl->_6A7 - 1);
        } else {
            design_ovl->act_proc(design_ovl);
            if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
                mDE_mask_cat_mask(design_ovl);
            }
            bcopy(&design_ovl->work_texture, &design_ovl->texture, sizeof(design_ovl->work_texture));
            osWritebackDCache(&design_ovl->texture, sizeof(design_ovl->work_texture));
        }
    }
}

void mDE_move_Wait(Submenu* submenu, mSM_MenuInfo_c* info) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mDE_Ovl_c* design_ovl = overlay->design_ovl;
    if (overlay->menu_info[mSM_OVL_EDITENDCHK].proc_status == mSM_OVL_PROC_MOVE &&
        overlay->menu_info[mSM_OVL_EDITENDCHK].next_proc_status == mSM_OVL_PROC_END) {
        switch (overlay->menu_info[mSM_OVL_EDITENDCHK].data1) {
            case 0: {
                overlay->move_chg_base_proc(info, 6);
                if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
                    mDE_save_maskcat_texture(design_ovl);
                    if (GETREG(NMREG, 0x5f)) {
                        mDE_print_texture(design_ovl);
                    }
                    Save_Get(mask_cat.palette_no) = design_ovl->palette_no;
                    bcopy(&design_ovl->work_texture, Save_GetPointer(mask_cat.design.design),
                          sizeof(design_ovl->work_texture));
                    osWritebackDCache(Save_GetPointer(mask_cat.design.design),
                                      sizeof(Save_Get(mask_cat.design.design)));
                } else {
                    mNW_original_design_c* my_design = &Now_Private->my_org[design_ovl->image_no & 7];
                    my_design->palette = design_ovl->palette_no;
                    mNW_OverWriteOriginalTexture(my_design, design_ovl->texture.data);
                }
                submenu->item_p->slot_no = 1;
            } break;
            case 1: {
                info->proc_status = mSM_OVL_PROC_PLAY;
            } break;
            default: {
                overlay->move_chg_base_proc(info, 6);
            } break;
        }
    }
}

void mDE_move_End(Submenu* submenu, mSM_MenuInfo_c* info) {
    submenu->overlay->move_End_proc(submenu, info);
}

void mDE_design_ovl_move(Submenu* submenu) {
    static mSM_MOVE_PROC ovl_move_proc[] = { &mDE_move_Move, &mDE_move_Play, &mDE_move_Wait, (mSM_MOVE_PROC)&none_proc1,
                                             &mDE_move_End };
    mSM_MenuInfo_c* overlay = &submenu->overlay->menu_info[mSM_OVL_DESIGN];
    overlay->pre_move_func(submenu);
    ovl_move_proc[overlay->proc_status](submenu, overlay);
}

extern Gfx des_sen_waku_model[], des_win_before[], des_win_before_model[], des_win_before_model_2[],
    des_win_waku_model[], des_win_waku2_model[], des_win_color_model[], des_win_toubai_model[], des_win_main_model[],
    des_win_color_before_model[], des_win_grid_model[], des_win_grid2_model[], des_cursor_waku2T_model[],
    des_tool_pen_all_model[], des_tool_nuri_all_model[], des_tool_waku_all_model[], des_tool_kao_all_model[],
    des_tool_mark_all_model[], des_tool_pen1T_model[], des_tool_nuriT_model[], des_tool_waku1T_model[],
    des_tool_mark1T_model[], des_tool_undoT_model[], des_tool_pen1_tex_rgb_ia8[], des_tool_pen2_tex_rgb_ia8[],
    des_tool_pen3_tex_rgb_ia8[], des_tool_nuri1_tex_rgb_ia8[], des_tool_nuri2_tex_rgb_ia8[],
    des_tool_nuri3_tex_rgb_ia8[], des_tool_nuri4_tex_rgb_ia8[], des_tool_nuri5_tex_rgb_ia8[],
    des_tool_nuri6_tex_rgb_ia8[], des_tool_waku1_tex_rgb_ia8[], des_tool_waku2_tex_rgb_ia8[],
    des_tool_waku3_tex_rgb_ia8[], des_tool_waku4_tex_rgb_ia8[], des_tool_waku5_tex_rgb_ia8[],
    des_tool_mark1_tex_rgb_ia8[], des_tool_mark2_tex_rgb_ia8[], des_tool_mark3_tex_rgb_ia8[],
    des_tool_mark4_tex_rgb_ia8[], des_tool_kao1_tex[], des_tool_kao2_tex[], des_tool_kao3_tex[], des_tool_kao4_tex[],
    des_tool_kao5_tex[], des_win_suuji0_tex_rgb_i4[], des_win_suuji1_tex_rgb_i4[], des_win_suuji2_tex_rgb_i4[],
    des_win_suuji3_tex_rgb_i4[], des_win_suuji4_tex_rgb_i4[], des_win_suuji5_tex_rgb_i4[], des_win_suuji6_tex_rgb_i4[],
    des_win_suuji7_tex_rgb_i4[], des_win_suuji8_tex_rgb_i4[], des_win_suuji9_tex_rgb_i4[], des_cursor_penT_model[],
    des_cursor_nuriT_model[], des_cursor_waku1T_model[], des_cursor_mark1_model[], des_cursor_mark2_model[],
    des_cursor_mark3_model[], des_cursor_mark4_model[], des_cursor_undo_model[], des_cursor_spT_model[],
    des_cursor_wakuT_model[], des_cursor_kao1T_model[], des_cursor_kao2T_model[], des_cursor_kao3T_model[],
    des_cursor_kao4_model[], des_cursor_kao5_model[], des_win_area1_model[], des_win_area2_model[],
    des_win_area4_model[], des_win_area3_model[], des_win_shikiri_model[], des_win_suuji_before[],
    des_win_suuji3_model[], des_win_suuji4_model[], des_win_suuji2_model[], des_win_suuji1_model[],
    des_win_marking_model[], des_win_marking2T_model[];

void mDE_set_frame_tool_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu) {

    static Gfx* tool_pen_table[] = { des_tool_pen1_tex_rgb_ia8, des_tool_pen2_tex_rgb_ia8, des_tool_pen3_tex_rgb_ia8 };
    static Gfx* tool_nuri_table[] = { des_tool_nuri1_tex_rgb_ia8, des_tool_nuri2_tex_rgb_ia8,
                                      des_tool_nuri3_tex_rgb_ia8, des_tool_nuri4_tex_rgb_ia8,
                                      des_tool_nuri5_tex_rgb_ia8, des_tool_nuri6_tex_rgb_ia8 };
    static Gfx* tool_waku_table[] = { des_tool_waku1_tex_rgb_ia8, des_tool_waku2_tex_rgb_ia8,
                                      des_tool_waku3_tex_rgb_ia8, des_tool_waku4_tex_rgb_ia8,
                                      des_tool_waku5_tex_rgb_ia8 };
    static Gfx* tool_mark_table[] = { des_tool_mark1_tex_rgb_ia8, des_tool_mark2_tex_rgb_ia8,
                                      des_tool_mark3_tex_rgb_ia8, des_tool_mark4_tex_rgb_ia8 };
    static Gfx* tool_kao_table[] = { des_tool_kao1_tex, des_tool_kao2_tex, des_tool_kao3_tex, des_tool_kao4_tex,
                                     des_tool_kao5_tex };
    GRAPH* graph = game->graph;
    mDE_Ovl_c* design_ovl = submenu->overlay->design_ovl;
    Matrix_scale(16.f, 16.f, 1.f, FALSE);
    Matrix_translate(menu->position[0], menu->position[1], 140.f, TRUE);
    OPEN_POLY_OPA_DISP(graph);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, des_win_before);
    if (design_ovl->_6A7 == 3) {
        gSPSegment(POLY_OPA_DISP++, ANIME_1_TXT_SEG, tool_pen_table[0]);
        gSPSegment(POLY_OPA_DISP++, ANIME_2_TXT_SEG, tool_nuri_table[0]);
        gSPSegment(POLY_OPA_DISP++, ANIME_3_TXT_SEG, tool_waku_table[0]);
        if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
            gSPSegment(POLY_OPA_DISP++, ANIME_4_TXT_SEG, tool_kao_table[0]);
        } else {
            gSPSegment(POLY_OPA_DISP++, ANIME_4_TXT_SEG, tool_mark_table[0]);
        }
        gSPDisplayList(POLY_OPA_DISP++, des_tool_pen_all_model);
        gSPDisplayList(POLY_OPA_DISP++, des_tool_nuri_all_model);
        gSPDisplayList(POLY_OPA_DISP++, des_tool_waku_all_model);
        if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
            gSPDisplayList(POLY_OPA_DISP++, des_tool_kao_all_model);
        } else {
            gSPDisplayList(POLY_OPA_DISP++, des_tool_mark_all_model);
        }
    } else {
        gSPSegment(POLY_OPA_DISP++, ANIME_1_TXT_SEG, tool_pen_table[design_ovl->_6A0]);
        gSPSegment(POLY_OPA_DISP++, ANIME_2_TXT_SEG, tool_nuri_table[design_ovl->_6A1]);
        gSPSegment(POLY_OPA_DISP++, ANIME_3_TXT_SEG, tool_waku_table[design_ovl->_6A2]);
        if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
            gSPSegment(POLY_OPA_DISP++, ANIME_4_TXT_SEG, tool_kao_table[design_ovl->_6A3]);
        } else {
            gSPSegment(POLY_OPA_DISP++, ANIME_4_TXT_SEG, tool_mark_table[design_ovl->_6A3]);
        }
        gSPDisplayList(POLY_OPA_DISP++, des_tool_pen1T_model);
        gSPDisplayList(POLY_OPA_DISP++, des_tool_nuriT_model);
        gSPDisplayList(POLY_OPA_DISP++, des_tool_waku1T_model);
        gSPDisplayList(POLY_OPA_DISP++, des_tool_mark1T_model);
    }
    gSPDisplayList(POLY_OPA_DISP++, des_tool_undoT_model);

    CLOSE_POLY_OPA_DISP(graph);
}

void mDE_set_frame_suuji_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu) {

    static Gfx* suuji_table[] = { des_win_suuji0_tex_rgb_i4, des_win_suuji1_tex_rgb_i4, des_win_suuji2_tex_rgb_i4,
                                  des_win_suuji3_tex_rgb_i4, des_win_suuji4_tex_rgb_i4, des_win_suuji5_tex_rgb_i4,
                                  des_win_suuji6_tex_rgb_i4, des_win_suuji7_tex_rgb_i4, des_win_suuji8_tex_rgb_i4,
                                  des_win_suuji9_tex_rgb_i4 };

    mDE_Ovl_c* design_ovl = submenu->overlay->design_ovl;
    GRAPH* graph = game->graph;
    int pal = design_ovl->palette_no + 1;
    Matrix_scale(16.f, 16.f, 1.f, FALSE);
    Matrix_translate(menu->position[0], menu->position[1], 140.f, TRUE);
    OPEN_POLY_OPA_DISP(graph);
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (design_ovl->_6A7 == 1) {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, 215, 30, 30, 255);
    } else {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 255, 245, 215, 180);
    }
    gSPDisplayList(POLY_OPA_DISP++, des_win_shikiri_model);
    gSPDisplayList(POLY_OPA_DISP++, des_win_suuji_before);
    gSPDisplayList(POLY_OPA_DISP++, des_win_suuji3_model);
    gSPDisplayList(POLY_OPA_DISP++, des_win_suuji4_model);
    if (pal >= ARRAY_COUNT(suuji_table)) {
        gSPSegment(POLY_OPA_DISP++, ANIME_1_TXT_SEG, suuji_table[1]);
        gSPDisplayList(POLY_OPA_DISP++, des_win_suuji1_model);
        gSPSegment(POLY_OPA_DISP++, ANIME_2_TXT_SEG, suuji_table[pal % ARRAY_COUNT(suuji_table)]);
        gSPDisplayList(POLY_OPA_DISP++, des_win_suuji2_model);
    } else {
        Matrix_push();
        Matrix_translate(-2.f, 0.f, 0.f, TRUE);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(POLY_OPA_DISP++, ANIME_2_TXT_SEG, suuji_table[pal]);
        gSPDisplayList(POLY_OPA_DISP++, des_win_suuji2_model);
        Matrix_pull();
    }

    CLOSE_POLY_OPA_DISP(graph);
}

void mDE_set_frame_mark_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu) {
    GRAPH* graph = game->graph;
    mDE_Ovl_c* design_ovl = submenu->overlay->design_ovl;
    Matrix_scale(16.f, 16.f, 1.f, FALSE);
    Matrix_translate(menu->position[0], menu->position[1], 140.f, TRUE);

    OPEN_POLY_OPA_DISP(graph);
    gSPDisplayList(POLY_OPA_DISP++, des_win_before);
    Matrix_push();
    if (design_ovl->_6A7 == 3) {
        Matrix_translate(-112.f + design_ovl->_69E * 0x18, 16.f - design_ovl->_69F * 0x18, 0.f, TRUE);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 185, 50, 50, 255);
    } else {
        Matrix_translate(-112.f, 16.f - design_ovl->_69F * 0x18, 0.f, TRUE);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 215, 195, 195, 255);
    }
    gSPDisplayList(POLY_OPA_DISP++, des_win_marking_model);
    Matrix_pull();
    Matrix_push();
    Matrix_translate(110.f, 0x3f - design_ovl->_6A4 * 10, 0.f, TRUE);
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (design_ovl->_6A7 != 1) {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 0xcd, 0xb9, 0xb9, 255);
        gDPSetEnvColor(POLY_OPA_DISP++, 105, 85, 115, 255);
    } else {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 235, 235, 235, 255);
        gDPSetEnvColor(POLY_OPA_DISP++, 105, 85, 115, 255);
    }
    gSPDisplayList(POLY_OPA_DISP++, des_win_marking2T_model);
    Matrix_pull();
    if (design_ovl->_6A7 == 1) {
        Matrix_push();
        if (design_ovl->_6A5 == 0) {
            Matrix_translate(110.f, 71.f, 0.f, TRUE);
            gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 185, 50, 50, 255);
            gSPDisplayList(POLY_OPA_DISP++, des_win_marking_model);
        } else {
            Matrix_translate(110.f, 0x3f - design_ovl->_6A5 * 10, 0.f, TRUE);
            gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 255, 80, 80, 255);
            gDPSetEnvColor(POLY_OPA_DISP++, 30, 30, 30, 255);
            gSPDisplayList(POLY_OPA_DISP++, des_win_marking2T_model);
        }
        Matrix_pull();
    }
    CLOSE_POLY_OPA_DISP(graph);
}

void mDE_waku_right_top(f32 param_1, f32* param_2, f32* param_3, s16* param_4) {
    *param_3 = param_1;
    *param_4 = DEG2SHORT_ANGLE2(90);
}

void mDE_waku_right_bottom(f32 param_1, f32* param_2, f32* param_3, s16* param_4) {
    // nothing;
}

void mDE_waku_left_top(f32 param_1, f32* param_2, f32* param_3, s16* param_4) {
    *param_3 = param_1;
    *param_2 = -1.f * param_1;
    *param_4 = DEG2SHORT_ANGLE2(180);
}

void mDE_waku_left_bottom(f32 param_1, f32* param_2, f32* param_3, s16* param_4) {
    *param_2 = -1.f * param_1;
    *param_4 = DEG2SHORT_ANGLE2(270);
}

void mDE_set_cursor_waku_rotate(mDE_Ovl_c* design_ovl, u32 param_2, f32* param_3, f32* param_4, s16* param_5) {
    f32 v = 1.f;
    if (param_2) {
        v = -1.f;
    }
    switch (design_ovl->_6D8) {
        case 0: {
            mDE_waku_right_bottom(v, param_3, param_4, param_5);
        } break;
        case 1: {
            mDE_waku_right_top(v, param_3, param_4, param_5);
        } break;
        case 2: {
            mDE_waku_left_bottom(v, param_3, param_4, param_5);
        } break;
        case 3: {
            mDE_waku_left_bottom(v, param_3, param_4, param_5);
        } break;
    }
}

void mDE_set_frame_cursor_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu) {
    static Gfx* cursor_table[] = { des_cursor_penT_model,  des_cursor_nuriT_model, des_cursor_waku1T_model,
                                   des_cursor_mark1_model, des_cursor_mark2_model, des_cursor_mark3_model,
                                   des_cursor_mark4_model, des_cursor_undo_model,  des_cursor_spT_model,
                                   des_cursor_wakuT_model, des_cursor_kao1T_model, des_cursor_kao2T_model,
                                   des_cursor_kao3T_model, des_cursor_kao4_model,  des_cursor_kao5_model };
    GRAPH* graph = game->graph;
    mDE_Ovl_c* design_ovl = submenu->overlay->design_ovl;
    if (design_ovl->_6A7 == 0) {
        if (design_ovl->_698 != 0) {
            if (design_ovl->_699 != 9) {
                int a, b;
                design_ovl->_680 -= 0x52;
                design_ovl->_684 += 0x4f;
                design_ovl->_690 = design_ovl->_680 + design_ovl->_688 * 5;
                design_ovl->_694 = design_ovl->_684 + design_ovl->_68C * 5;
                a = ABS(design_ovl->_680 - design_ovl->_690);
                b = ABS(design_ovl->_684 - design_ovl->_694);
                design_ovl->_684 -= b;
                design_ovl->_694 -= b;

                Matrix_push();
                Matrix_scale(16.f, 16.f, 1.f, FALSE);
                Matrix_translate(design_ovl->_680, design_ovl->_684, 0.f, TRUE);
                Matrix_scale(a, 2.f, 1.f, TRUE);
                OPEN_POLY_OPA_DISP(graph);
                gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                if (GETREG(NMREG, 2)) {
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, design_ovl->rgb8_pal[design_ovl->_6A4].r,
                                    design_ovl->rgb8_pal[design_ovl->_6A4].g, design_ovl->rgb8_pal[design_ovl->_6A4].b,
                                    255);
                } else {
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, 90, 90, 90, 0xff);
                }
                gSPDisplayList(POLY_OPA_DISP++, des_sen_waku_model);
                CLOSE_POLY_OPA_DISP(graph);
                Matrix_pull();

                Matrix_push();
                Matrix_scale(16.f, 16.f, 1.f, FALSE);
                Matrix_translate(design_ovl->_680, design_ovl->_694, 0.f, TRUE);
                if (a) {
                    a += 2.f;
                }
                Matrix_scale(a, 2.f, 1.f, TRUE);
                OPEN_POLY_OPA_DISP(graph);
                gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                if (GETREG(NMREG, 2)) {
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, design_ovl->rgb8_pal[design_ovl->_6A4].r,
                                    design_ovl->rgb8_pal[design_ovl->_6A4].g, design_ovl->rgb8_pal[design_ovl->_6A4].b,
                                    255);
                } else {
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, 90, 90, 90, 0xff);
                }
                gSPDisplayList(POLY_OPA_DISP++, des_sen_waku_model);
                CLOSE_POLY_OPA_DISP(graph);
                Matrix_pull();

                Matrix_push();
                Matrix_scale(16.f, 16.f, 1.f, FALSE);
                Matrix_translate(design_ovl->_680, design_ovl->_684, 0.f, TRUE);
                Matrix_scale(2.f, b, 1.f, TRUE);
                OPEN_POLY_OPA_DISP(graph);
                gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                if (GETREG(NMREG, 2)) {
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, design_ovl->rgb8_pal[design_ovl->_6A4].r,
                                    design_ovl->rgb8_pal[design_ovl->_6A4].g, design_ovl->rgb8_pal[design_ovl->_6A4].b,
                                    255);
                } else {
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, 90, 90, 90, 0xff);
                }
                gSPDisplayList(POLY_OPA_DISP++, des_sen_waku_model);
                CLOSE_POLY_OPA_DISP(graph);
                Matrix_pull();

                Matrix_push();
                Matrix_scale(16.f, 16.f, 1.f, FALSE);
                Matrix_translate(design_ovl->_690, design_ovl->_684, 0.f, TRUE);
                Matrix_scale(2.f, b, 1.f, TRUE);
                OPEN_POLY_OPA_DISP(graph);
                gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                if (GETREG(NMREG, 2)) {
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, design_ovl->rgb8_pal[design_ovl->_6A4].r,
                                    design_ovl->rgb8_pal[design_ovl->_6A4].g, design_ovl->rgb8_pal[design_ovl->_6A4].b,
                                    255);
                } else {
                    gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, 90, 90, 90, 0xff);
                }
                gSPDisplayList(POLY_OPA_DISP++, des_sen_waku_model);
                CLOSE_POLY_OPA_DISP(graph);
                Matrix_pull();
            }
        }
        Matrix_scale(16.f, 16.f, 1.f, FALSE);
        Matrix_translate(menu->position[0], menu->position[1], 140.f, TRUE);
        OPEN_POLY_OPA_DISP(graph);
        gSPDisplayList(POLY_OPA_DISP++, des_win_before);
        if (design_ovl->_69A && design_ovl->_699 != 9) {
            float f1, f2;
            s16 s1;
            s1 = 0;
            f1 = 0.f;
            f2 = 0.f;
            mDE_set_cursor_waku_rotate(design_ovl, 1, &f1, &f2, &s1);
            Matrix_push();
            Matrix_translate(design_ovl->_658 - 3.f - 75.f - f1, design_ovl->_65C + 2.f - (-75.f) - f2, 0.f, TRUE);
            Matrix_RotateZ(s1, TRUE);
            gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, des_cursor_waku1T_model);
            Matrix_pull();
        } else if (design_ovl->_69A && design_ovl->_699 == 9) {
            Matrix_push();
            Matrix_translate(design_ovl->_658 - 3.f - 75.f, (design_ovl->_65C + 10.f) - (-75.f), 0.f, TRUE);
            gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, des_cursor_wakuT_model);
            Matrix_pull();
        }
        if (design_ovl->_699 == 1) {
            Matrix_translate(design_ovl->_650 + 1.f - 75.f, design_ovl->_654 + 11.f - (-75.f), 0.f, TRUE);
        } else if (design_ovl->_699 == 2) {
            if (design_ovl->_69A) {
                float f1, f2;
                s16 s1;
                s1 = 0;
                f1 = 0.f;
                f2 = 0.f;
                mDE_set_cursor_waku_rotate(design_ovl, 0, &f1, &f2, &s1);
                Matrix_translate(design_ovl->_650 - 4.f - 75.f - f1, design_ovl->_654 + 3.f - (-75.f) - f2, 0.f, TRUE);
                Matrix_RotateZ(s1, TRUE);
            } else {
                Matrix_translate(design_ovl->_650 - 3.f - 75.f, design_ovl->_654 + 2.f - (-75.f), 0.f, TRUE);
            }
        } else if (design_ovl->_699 == 3) {
            Matrix_translate(design_ovl->_650 - 1.f - 75.f, design_ovl->_654 + 8.f - (-75.f), 0.f, TRUE);
        } else if (design_ovl->_699 == 4) {
            Matrix_translate(design_ovl->_650 - 1.f - 75.f, design_ovl->_654 + 8.f - (-75.f), 0.f, TRUE);
        } else if (design_ovl->_699 == 5) {
            Matrix_translate(design_ovl->_650 - 1.f - 75.f, design_ovl->_654 + 8.f - (-75.f), 0.f, TRUE);
        } else if (design_ovl->_699 == 6) {
            Matrix_translate(design_ovl->_650 - 1.f - 75.f, design_ovl->_654 + 8.f - (-75.f), 0.f, TRUE);
        } else if (design_ovl->_699 == 7) {
            Matrix_translate(design_ovl->_650 - 1.f - 75.f, design_ovl->_654 + 8.f - (-75.f), 0.f, TRUE);
        } else if (design_ovl->_699 == 9) {
            Matrix_translate(design_ovl->_650 - 3.f - 75.f, design_ovl->_654 + 10.f - (-75.f), 0.f, TRUE);
        } else if (design_ovl->_699 == 10) {
            Matrix_translate(design_ovl->_650 - 75.f, design_ovl->_654 + 5.f - (-75.f), 0.f, TRUE);
        } else if (design_ovl->_699 == 11) {
            Matrix_translate(design_ovl->_650 - 75.f, design_ovl->_654 + 5.f - (-75.f), 0.f, TRUE);
        } else if (design_ovl->_699 == 12) {
            Matrix_translate(design_ovl->_650 + 2.f - 75.f, design_ovl->_654 + 7.f - (-75.f), 0.f, TRUE);
        } else if (design_ovl->_699 == 13) {
            Matrix_translate(design_ovl->_650 - 1.f - 75.f, design_ovl->_654 + 5.f - (-75.f), 0.f, TRUE);
        } else if (design_ovl->_699 == 14) {
            Matrix_translate(design_ovl->_650 - 1.f - 75.f, design_ovl->_654 + 5.f - (-75.f), 0.f, TRUE);
        } else {
            Matrix_translate(design_ovl->_650 + 8.f - 75.f, design_ovl->_654 + 13.f - (-75.f), 0.f, TRUE);
        }
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        if (design_ovl->_69A && design_ovl->_699 == 2) {
            gSPDisplayList(POLY_OPA_DISP++, des_cursor_waku2T_model);
        } else {
            gSPDisplayList(POLY_OPA_DISP++, cursor_table[design_ovl->_699]);
        }
        CLOSE_POLY_OPA_DISP(graph);
    }
}

void mDE_set_frame_main_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu) {
    int i;
    static Gfx* area_table[] = { des_win_area1_model, des_win_area2_model, des_win_area4_model, des_win_area3_model };

    GRAPH* graph = game->graph;
    mDE_Ovl_c* design_ovl = submenu->overlay->design_ovl;
    Matrix_scale(16.f, 16.f, 1.f, FALSE);
    Matrix_translate(menu->position[0], menu->position[1], 140.f, TRUE);
    OPEN_POLY_OPA_DISP(graph);
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, des_win_before_model);
    for (i = 0; i < ARRAY_COUNT(area_table); i++) {
        if (i == design_ovl->_6A7) {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 0x28, 0xeb, 0xa0, 0xb4);
        } else {
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 0x5a, 0x46, 0x28, 0xb4);
        }
        gSPDisplayList(POLY_OPA_DISP++, area_table[i]);
    }
    gSPDisplayList(POLY_OPA_DISP++, des_win_before_model_2);
    gSPDisplayList(POLY_OPA_DISP++, des_win_waku_model);
    gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_POINT);
    gDPLoadTLUT_Dolphin(POLY_OPA_DISP++, 15, 16, 1, design_ovl->palette_p);
    gDPLoadTextureBlock_4b_Dolphin(POLY_OPA_DISP++, design_ovl->texture.data, G_IM_FMT_CI, 32, 32, 15, GX_MIRROR,
                                   GX_MIRROR, 0, 0);
    gSPDisplayList(POLY_OPA_DISP++, des_win_toubai_model);
    gSPDisplayList(POLY_OPA_DISP++, des_win_main_model);
    gDPSetTextureFilter(POLY_OPA_DISP++, G_TF_BILERP);
    gSPDisplayList(POLY_OPA_DISP++, des_win_color_before_model);
    Matrix_push();
    for (i = 0; i < ARRAY_COUNT(design_ovl->rgb8_pal) - 1; i++) {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 128, design_ovl->rgb8_pal[i + 1].r, design_ovl->rgb8_pal[i + 1].g,
                        design_ovl->rgb8_pal[i + 1].b, 255);
        gSPDisplayList(POLY_OPA_DISP++, des_win_color_model);
        Matrix_translate(0.f, -10.f, 0.f, TRUE);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }
    Matrix_pull();
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, des_win_waku2_model);
    if (design_ovl->_69D) {
        gSPDisplayList(POLY_OPA_DISP++, des_win_grid_model);
        gSPDisplayList(POLY_OPA_DISP++, des_win_grid2_model);
    }
    CLOSE_POLY_OPA_DISP(graph);
}

void mDE_set_frame_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu) {
    mDE_set_frame_main_dl(submenu, game, menu);
    mDE_set_frame_tool_dl(submenu, game, menu);
    mDE_set_frame_suuji_dl(submenu, game, menu);
    mDE_set_frame_mark_dl(submenu, game, menu);
    mDE_set_frame_cursor_dl(submenu, game, menu);
}
void mDE_design_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu = &submenu->overlay->menu_info[mSM_OVL_DESIGN];
    menu->pre_draw_func(submenu, game);
    mDE_set_frame_dl(submenu, game, menu);
}

void mDE_design_ovl_set_proc(Submenu* submenu) {
    Submenu_Overlay_c* ovl = submenu->overlay;

    ovl->menu_control.menu_move_func = mDE_design_ovl_move;
    ovl->menu_control.menu_draw_func = mDE_design_ovl_draw;
}

void mDE_design_ovl_init(Submenu* submenu) {
    Submenu_Overlay_c* ovl = submenu->overlay;
    mDE_Ovl_c* design_ovl = submenu->overlay->design_ovl;
    ovl->menu_control.animation_flag = 0;
    ovl->menu_info[mSM_OVL_DESIGN].proc_status = 0;
    ovl->menu_info[mSM_OVL_DESIGN].next_proc_status = 1;
    ovl->menu_info[mSM_OVL_DESIGN].move_drt = 5;
    if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
        MaskCat_c* cat = Save_GetPointer(mask_cat);
        design_ovl->palette_no = 15;
        mDE_maskcat_init(cat);
        bcopy(&cat->design.design, &design_ovl->texture, sizeof(design_ovl->texture));
    } else {
        mNW_original_design_c* p;
        design_ovl->image_no = mNW_get_image_no(submenu, submenu->param0);
        p = &Now_Private->my_org[design_ovl->image_no & 7];
        design_ovl->palette_no = p->palette;
        mNW_CopyOriginalTexture(&design_ovl->texture, p);
    }
    osWritebackDCache(&design_ovl->texture, sizeof(design_ovl->texture));
    design_ovl->palette_p = mNW_PaletteIdx2Palette(design_ovl->palette_no);
    mDE_pallet_RGB5A3_to_RGB24(design_ovl);
    design_ovl->_69D = 1;
    design_ovl->_6A7 = 0;
    design_ovl->_6A4 = 1;
    design_ovl->_6A5 = 1;
    design_ovl->_6CC = 0;
    design_ovl->_6CD = 0;
    design_ovl->_6B4 = 0;
    design_ovl->_6B8 = 0;
    design_ovl->_6C0 = 0;
    design_ovl->_6D8 = 0;
    design_ovl->_6D9 = 0;
    design_ovl->_6DA = 0;
    mDE_setup_action(design_ovl, 0);
    mDE_main_mode_setup_action(design_ovl, 0);
    design_ovl->_650 = 75;
    design_ovl->_654 = -75;
    design_ovl->_660 = 77.5f;
    design_ovl->_664 = -77.5f;
    design_ovl->cursor_x = 15;
    design_ovl->cursor_y = 15;
    bcopy(&design_ovl->texture, &design_ovl->work_texture, sizeof(design_ovl->work_texture));
    osWritebackDCache(&design_ovl->work_texture, sizeof(design_ovl->work_texture));
    if (Save_Get(scene_no) == SCENE_START_DEMO3 || GETREG(NMREG, 0x5f)) {
        mDE_mask_cat_mask(design_ovl);
        osWritebackDCache(&design_ovl->work_texture, sizeof(design_ovl->work_texture));
        bcopy(&design_ovl->work_texture, &design_ovl->texture, sizeof(design_ovl->texture));
        osWritebackDCache(&design_ovl->texture, sizeof(design_ovl->texture));
    }
    bcopy(&design_ovl->texture, &design_ovl->undo_texture, sizeof(design_ovl->undo_texture));
    osWritebackDCache(&design_ovl->undo_texture, sizeof(design_ovl->undo_texture));
}

void mDE_maskcat_init(MaskCat_c* mask_cat) {
    int i;
    mask_cat->palette_no = 15;
    for (i = 0; i < ARRAY_COUNT(mask_cat->design.design.data); i++) {
        mask_cat->design.design.data[i] = 0xff;
    }
}

void mDE_design_ovl_construct(Submenu* submenu) {
    mDE_Ovl_c** ovl = &submenu->overlay->design_ovl;
    if (*ovl == NULL) {
        mem_clear((u8*)&de_ovl_data, sizeof(de_ovl_data), 0);
        *ovl = &de_ovl_data;
    }
    mDE_design_ovl_init(submenu);
    mDE_design_ovl_set_proc(submenu);
}

void mDE_design_ovl_destruct(Submenu* submenu) {
    submenu->overlay->design_ovl = NULL;
}
