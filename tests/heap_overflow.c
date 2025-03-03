/* iso_alloc heap_overflow.c
 * Copyright 2023 - chris.rohlf@gmail.com */

#include "iso_alloc.h"
#include "iso_alloc_internal.h"

int main(int argc, char *argv[]) {
    uint8_t *p = NULL;

    for(int32_t i = 0; i < 1024; i++) {
        p = (uint8_t *) iso_alloc(32);
        iso_free(p);
    }

    p = (uint8_t *) iso_alloc(32);

    const char *A = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
                    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"
                    "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
#if MEMCPY_SANITY
    memcpy(p, A, strlen(A));
#else
    size_t n = strlen(A);
    while(n--) {
        *p++ = *A++;
    }
#endif

    iso_free(p);
    iso_verify_zones();

    return OK;
}
