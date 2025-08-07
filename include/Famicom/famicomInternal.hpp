#ifndef FAMICOMINTERNAL_H
#define FAMICOMINTERNAL_H

#include "types.h"
#include "Famicom/famicomPriv.h"
#include "Famicom/ks_nes.h"

#define MURA_GAME_NAME_SIZE 16

static void* my_malloc(size_t size, int align) { return (*my_malloc_current->malloc_align)(size, align); }
static void my_free(void* ptr) { (*my_malloc_current->free)(ptr); }
static int my_getmemblocksize(void* ptr) { return (*my_malloc_current->getmemblocksize)(ptr); }
static int my_gettotalfreesize() { return (*my_malloc_current->gettotalfreesize)(); }

#endif
