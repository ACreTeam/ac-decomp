#include "gamealloc.h"

#include "libc64/malloc.h"

extern void* gamealloc_malloc(GameAlloc* gamealloc, size_t size) {
  GameAllocList* alloc = (GameAllocList*)malloc(size + sizeof(GameAllocList));

  if (alloc != NULL) {
    alloc->alloc_size = size;
    alloc->prev = gamealloc->tail;
    gamealloc->tail->next = alloc;
    gamealloc->tail = alloc;
    gamealloc->tail->next = &gamealloc->head;
    gamealloc->head.prev = gamealloc->tail;

    return (void*)(alloc + 1); // data starts after GameAllocList structure
  }
  else {
    return NULL;
  }
}

extern void gamealloc_free(GameAlloc* gamealloc, void* ptr) {
  if (ptr != NULL) {
    GameAllocList* alloc = ((GameAllocList*)ptr) - 1; // back up to GameAllocList struct

    alloc->prev->next = alloc->next;
    alloc->next->prev = alloc->prev;
    gamealloc->tail = gamealloc->head.prev;

    free(alloc);
  }
}

extern void gamealloc_cleanup(GameAlloc* gamealloc) {
  GameAllocList* now_p = gamealloc->head.next;
  GameAllocList* end_p = &gamealloc->head;

  /* Go through entire list and free each until we wrap around to the head list */
  while (now_p != end_p) {
    GameAllocList* temp_p = now_p;
    now_p = now_p->next;
    free(temp_p);
  }

  gamealloc->tail = end_p;
  gamealloc->head.next = gamealloc->tail;
  gamealloc->head.prev = gamealloc->tail;
}

extern void gamealloc_init(GameAlloc* gamealloc) {
  gamealloc->tail = &gamealloc->head;
  gamealloc->head.next = gamealloc->tail;
  gamealloc->head.prev = gamealloc->tail;
}
