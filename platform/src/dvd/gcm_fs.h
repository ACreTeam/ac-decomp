#pragma once
#include <stdint.h>
#include <stdbool.h>

/* Open the disc image; must be called before any DVD* calls. */
bool gcm_fs_open(const char* iso_path);
bool gcm_fs_lookup(const char* path, uint32_t* out_offset, uint32_t* out_length);
bool gcm_fs_read(uint32_t disc_offset, void* buf, uint32_t length);
int  gcm_fs_get_fd(void);
bool gcm_fs_is_open(void);
