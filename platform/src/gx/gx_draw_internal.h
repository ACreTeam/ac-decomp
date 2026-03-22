#pragma once
/* Internal draw-call interface shared between gx_geometry.cpp, gx_vert.cpp,
 * gx_texture.mm and metal_renderer.mm.  NOT part of the public GX API.
 * All functions use C linkage so they are callable from .cpp and .mm alike. */
#include <dolphin/gx.h>
#include <stdint.h>

/* Flat per-vertex layout sent to Metal — always float, normalised on input */
struct PlatVertex {
    float x, y, z;     /* model-space position */
    float r, g, b, a;  /* vertex colour [0..1]  */
    float u, v;         /* texcoord 0            */
};

#ifdef __cplusplus
extern "C" {
#endif

/* --- Vertex accumulation (gx_vert.cpp → metal_renderer.mm) --------- */
/* Call at each GXPosition*: commits the previous vertex, starts a new one */
void plat_gx_start_vertex(void);
/* Returns a writable pointer to the vertex currently being built */
PlatVertex* plat_gx_cur_vtx(void);

/* --- Draw context (gx_geometry.cpp → metal_renderer.mm) ------------ */
void plat_gx_begin_draw(GXPrimitive prim);   /* called from GXBegin */
void plat_gx_end_draw(GXPrimitive rawPrim);  /* called from GXEnd; rawPrim for quad/fan conv */

/* --- Texture slots (gx_texture.mm → metal_renderer.mm) ------------- */
/* slot = GXTexMapID (0-7).  tex_ptr = id<MTLTexture> cast via __bridge void* */
void  plat_metal_set_texture(int slot, void* tex_ptr);
/* Texture decode cache, keyed by GC texture data pointer */
void* plat_metal_get_cached_tex(uintptr_t key);  /* NULL = not cached */
void  plat_metal_store_cached_tex(uintptr_t key, void* tex_ptr);
/* Accessors for Metal objects needed by gx_texture.mm */
void* plat_metal_device_ptr(void);     /* id<MTLDevice>  */
void* plat_metal_white_tex_ptr(void);  /* 1×1 white fallback id<MTLTexture> */

#ifdef __cplusplus
} /* extern "C" */
#endif
