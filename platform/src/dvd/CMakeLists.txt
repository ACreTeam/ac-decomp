add_library(platform_dvd OBJECT
    dvd_shim.cpp
    gcm_fs.cpp
)
target_include_directories(platform_dvd PRIVATE
    ${PLATFORM_INCLUDES}
)
