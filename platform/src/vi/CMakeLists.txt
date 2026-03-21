add_library(platform_vi OBJECT
    vi_shim.cpp
    vi_window.mm
)
target_include_directories(platform_vi PRIVATE
    ${PLATFORM_INCLUDES}
)
target_compile_options(platform_vi PRIVATE -fobjc-arc)
