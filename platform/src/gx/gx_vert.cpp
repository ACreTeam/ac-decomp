/* GX vertex submission functions.
 * Stage 1: all no-ops.  Stage 7: accumulate into vertex buffer. */
#include "platform/platform.h"
#include <dolphin/gx/GXVert.h>

extern "C" {

void GXPosition3f32(f32 x, f32 y, f32 z)      { (void)x; (void)y; (void)z; }
void GXPosition3u16(u16 x, u16 y, u16 z)      { (void)x; (void)y; (void)z; }
void GXPosition3s16(s16 x, s16 y, s16 z)      { (void)x; (void)y; (void)z; }
void GXPosition3u8 (u8 x, u8 y, u8 z)         { (void)x; (void)y; (void)z; }
void GXPosition3s8 (s8 x, s8 y, s8 z)         { (void)x; (void)y; (void)z; }
void GXPosition2f32(f32 x, f32 y)             { (void)x; (void)y; }
void GXPosition2u16(u16 x, u16 y)             { (void)x; (void)y; }
void GXPosition2s16(s16 x, s16 y)             { (void)x; (void)y; }
void GXPosition2u8 (u8 x, u8 y)               { (void)x; (void)y; }
void GXPosition2s8 (s8 x, s8 y)               { (void)x; (void)y; }
void GXPosition1x16(u16 index)                 { (void)index; }
void GXPosition1x8 (u8 index)                  { (void)index; }

void GXNormal3f32(f32 x, f32 y, f32 z)        { (void)x; (void)y; (void)z; }
void GXNormal3s16(s16 x, s16 y, s16 z)        { (void)x; (void)y; (void)z; }
void GXNormal3s8 (s8 x, s8 y, s8 z)           { (void)x; (void)y; (void)z; }
void GXNormal1x16(u16 index)                   { (void)index; }
void GXNormal1x8 (u8 index)                    { (void)index; }

void GXColor4u8(u8 r, u8 g, u8 b, u8 a)       { (void)r; (void)g; (void)b; (void)a; }
void GXColor3u8(u8 r, u8 g, u8 b)             { (void)r; (void)g; (void)b; }
void GXColor1u32(u32 clr)                      { (void)clr; }
void GXColor1u16(u16 clr)                      { (void)clr; }
void GXColor1x16(u16 index)                    { (void)index; }
void GXColor1x8 (u8 index)                     { (void)index; }

void GXTexCoord2f32(f32 s, f32 t)             { (void)s; (void)t; }
void GXTexCoord2u16(u16 s, u16 t)             { (void)s; (void)t; }
void GXTexCoord2s16(s16 s, s16 t)             { (void)s; (void)t; }
void GXTexCoord2u8 (u8 s, u8 t)               { (void)s; (void)t; }
void GXTexCoord2s8 (s8 s, s8 t)               { (void)s; (void)t; }
void GXTexCoord1f32(f32 s, f32 t)             { (void)s; (void)t; }
void GXTexCoord1u16(u16 s, u16 t)             { (void)s; (void)t; }
void GXTexCoord1s16(s16 s, s16 t)             { (void)s; (void)t; }
void GXTexCoord1u8 (u8 s, u8 t)               { (void)s; (void)t; }
void GXTexCoord1s8 (s8 s, s8 t)               { (void)s; (void)t; }
void GXTexCoord1x16(u16 index)                 { (void)index; }
void GXTexCoord1x8 (u8 index)                  { (void)index; }

} /* extern "C" */
