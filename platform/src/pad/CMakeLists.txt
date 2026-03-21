add_library(platform_pad OBJECT
    pad_shim.cpp
)
target_include_directories(platform_pad PRIVATE
    ${PLATFORM_INCLUDES}
)
