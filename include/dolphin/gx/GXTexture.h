#ifndef _DOLPHIN_GXTEXTURE
#define _DOLPHIN_GXTEXTURE

#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXStruct.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef GXTexRegion* (*GXTexRegionCallback)(const GXTexObj* obj, GXTexMapID id);

void GXInitTexObj(GXTexObj* obj, const void* data, u16 width, u16 height, u32 format,
                  GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXBool mipmap);
void GXInitTexObjCI(GXTexObj* obj, const void* data, u16 width, u16 height, GXCITexFmt format,
                    GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXBool mipmap, u32 tlut);
void GXInitTexObjData(GXTexObj* obj, const void* data);
void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt, f32 min_lod,
                     f32 max_lod, f32 lod_bias, GXBool bias_clamp, GXBool do_edge_lod,
                     GXAnisotropy max_aniso);
void GXLoadTexObj(GXTexObj* obj, GXTexMapID id);
u32 GXGetTexBufferSize(u16 width, u16 height, u32 format, GXBool mipmap, u8 max_lod);
void GXInvalidateTexAll();
void GXInitTexObjWrapMode(GXTexObj* obj, GXTexWrapMode s, GXTexWrapMode t);
void GXInitTlutObj(GXTlutObj* obj, const void* data, GXTlutFmt format, u16 entries);
void GXLoadTlut(const GXTlutObj* obj, u32 idx);
void GXSetTexCoordScaleManually(GXTexCoordID coord, GXBool enable, u16 ss, u16 ts);
void GXInitTexCacheRegion(GXTexRegion* region, GXBool is_32b_mipmap, u32 tmem_even,
                          GXTexCacheSize size_even, u32 tmem_odd, GXTexCacheSize size_odd);
GXTexRegionCallback GXSetTexRegionCallback(GXTexRegionCallback callback);
void GXInvalidateTexRegion(const GXTexRegion* region);

#ifdef __cplusplus
}
#endif

#endif // _DOLPHIN_GXTEXTURE
