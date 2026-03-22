add_library(platform_gx OBJECT
    gx_init.cpp
    gx_fifo.cpp
    gx_geometry.cpp
    gx_vert.cpp
    gx_transform.cpp
    gx_tev.cpp
    gx_texture.mm
    gx_lighting.cpp
    gx_pixel.cpp
    gx_framebuf.cpp
    gx_displist.cpp
    gx_cull.cpp
    gx_get.cpp
    texture_decode.cpp
    metal_renderer.mm
    tev_shader_gen.mm
)
target_include_directories(platform_gx PRIVATE
    ${PLATFORM_INCLUDES}
)
target_compile_options(platform_gx PRIVATE -fobjc-arc)
