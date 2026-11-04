#ifndef J3DTYPES_H
#define J3DTYPES_H

#include "types.h"

#ifdef __cplusplus
enum JBlockType {
    JBT_ColorAmbientOn = 'CLAB',
    JBT_ColorNull = 'CLNL',
    JBT_ColorLightOff = 'CLOF',
    JBT_ColorLightOn = 'CLON',
    JBT_IndFull = 'IBLF',
    JBT_IndNull = 'IBLN',
    JBT_PETexEdge = 'PEED',
    JBT_PEFogOff = 'PEFG',
    JBT_PEFull = 'PEFL',
    JBT_PENull = 'PENL',
    JBT_PEOpa = 'PEOP',
    JBT_PEXlu = 'PEXL',
    JBT_TexGen4 = 'TGB4',
    JBT_TexGenBasic = 'TGBC',
    JBT_TexGenNull = 'TGNL',
    JBT_TexGenPatched = 'TGPT',
    JBT_Tev16 = 'TV16',
    JBT_Tev1 = 'TVB1',
    JBT_Tev2 = 'TVB2',
    JBT_Tev4 = 'TVB4',
    JBT_Tev8 = 'TVB8',
    JBT_TevNull = 'TVNL',
    JBT_TevPatched = 'TVPT'
};
#endif

#endif
