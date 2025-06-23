#include "Runtime.PPCEABI.H/NMWException.h"
#include "Runtime.PPCEABI.H/MWCPlusLib.h"

#pragma exceptions on

#define ARRAY_HEADER_SIZE 8

class __partial_array_destructor {
  private:
    void* p;
    size_t size;
    size_t n;
    ConstructorDestructor dtor;

  public:
    size_t i;

    __partial_array_destructor(void* array, size_t elementsize, size_t nelements, ConstructorDestructor destructor) {
        p = array;
        size = elementsize;
        n = nelements;
        dtor = destructor;
        i = n;
    }

    ~__partial_array_destructor() {
        char* ptr;

        if (i < n && dtor) {
            for (ptr = (char*)p + size * i; i > 0; i--) {
                ptr -= size;
                DTORCALL_COMPLETE(dtor, ptr);
            }
        }
    }
};

extern void __construct_array(void* ptr, ConstructorDestructor ctor, ConstructorDestructor dtor, size_t size,
                              size_t n) {
    __partial_array_destructor pad(ptr, size, n, dtor);
    char* p;

    for (pad.i = 0, p = (char*)ptr; pad.i < n; pad.i++, p += size) {
        CTORCALL_COMPLETE(ctor, p);
    }
}

extern void __destroy_arr(void* block, ConstructorDestructor* dtor, size_t size, size_t n) {
    char* p;

    for (p = (char*)block + size * n; n > 0; n--) {
        p -= size;
        DTORCALL_COMPLETE(dtor, p);
    }
}
