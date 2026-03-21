add_library(platform_card OBJECT
    card_shim.cpp
)
target_include_directories(platform_card PRIVATE
    ${PLATFORM_INCLUDES}
)
