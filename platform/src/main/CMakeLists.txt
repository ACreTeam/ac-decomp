add_library(platform_main OBJECT
    main_apple.mm
)
target_include_directories(platform_main PRIVATE
    ${PLATFORM_INCLUDES}
)
target_compile_options(platform_main PRIVATE -fobjc-arc)
