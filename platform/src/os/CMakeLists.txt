add_library(platform_os OBJECT
    os_shim.cpp
    thread_shim.cpp
    message_shim.cpp
    arena_shim.cpp
    alarm_shim.cpp
    rtc_shim.cpp
)
target_include_directories(platform_os PRIVATE
    ${PLATFORM_INCLUDES}
)
target_compile_options(platform_os PRIVATE -fobjc-arc)
