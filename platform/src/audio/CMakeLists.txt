add_library(platform_audio OBJECT
    audio_mixer.cpp
    audio_stub_thread.c
)
target_include_directories(platform_audio PRIVATE
    ${PLATFORM_INCLUDES}
)
