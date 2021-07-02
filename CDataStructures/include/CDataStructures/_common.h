#ifndef _CDATASTRUCTURES_COMMON_H
#   define _CDATASTRUCTURES_COMMON_H

#   include "_prelude.h"

#   define CDATASTRUCTURES_MIN_CAPACITY 16
#   define CDATASTRUCTURES_BLOCK_SIZE 8

#   define bound(n, x, y) (max(min(n, y), x))
#   define amount_to_next_multiple(a, b) (b - (a % b))

static inline size_t _cds_recommended_capacity(size_t length) {
    if (length <= CDATASTRUCTURES_MIN_CAPACITY)
        return length;
    else
        return length + amount_to_next_multiple(
            length,
            CDATASTRUCTURES_BLOCK_SIZE
        );
}

#endif