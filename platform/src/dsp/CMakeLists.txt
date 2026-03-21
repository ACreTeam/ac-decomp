add_library(platform_dsp OBJECT
    dsp_shim.cpp
    ai_shim.cpp
)
target_include_directories(platform_dsp PRIVATE
    ${PLATFORM_INCLUDES}
)
