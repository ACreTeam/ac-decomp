add_library(platform_main OBJECT
    main_apple.mm
    ctors_shim.c
    bootdata_shim.c
)
target_include_directories(platform_main PRIVATE
    ${PLATFORM_INCLUDES}
)
target_compile_options(platform_main PRIVATE -fobjc-arc)
