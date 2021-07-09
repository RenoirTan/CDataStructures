#ifndef CDATASTRUCTURES_UTILS_H
#   define CDATASTRUCTURES_UTILS_H

#   include "_prelude.h"
#   include "_common.h"

/**
 * @brief A short macro for requesting memory on the heap for a certain type.
 */
#   define CDS_NEW(type) malloc(sizeof(type))

/**
 * @brief Get the recommended capacity for a certain length.
 * 
 * @param length The length of the array.
 * @return size_t The recommended capacity the array should have.
 */
inline size_t _cds_recommended_capacity(size_t length) {
    if (length <= CDATASTRUCTURES_MIN_CAPACITY)
        return CDATASTRUCTURES_MIN_CAPACITY;
    else
        return length + amount_to_next_multiple(
            length - CDATASTRUCTURES_MIN_CAPACITY,
            CDATASTRUCTURES_BLOCK_SIZE
        );
}

/**
 * @brief An extremely fast implementation of a logarithm calculator for
 * unsigned integers. This is basically binary searching the most significant
 * digit (i.e. 1 in base 2) by bitshifting the input number whenever required.
 * Using unrolled loops, this function should be blindingly quick. The big-O
 * notation for this function is O(1) as it passes through a predetermined
 * 6 loops.
 * 
 * This was taken from https://stackoverflow.com/a/24748637.
 * 
 * @see cds_int_log10
 * 
 * @param n The input number
 * @return int32_t The index of the most significant digit (i.e. the floor
 * of the log of `n`). -1 if n is invalid (e.g. 0).
 */
inline int32_t cds_int_log2(uint64_t n) {
#   define S(k)                    \
    if (n >= (UINT64_C(1) << k)) { \
        i += k;                    \
        n >>= k;                   \
    }

    // 0 if n > 0
    // -1 if n == 0 (-1 for invalid numbers like 0)
    int32_t i = -(n == 0);
    S(32); // 0xFFFFFFFF
    S(16); // 0x0000FFFF
    S(8);  // 0x000000FF
    S(4);  // 0x0000000F
    S(2);  // 0x00000004
    S(1);  // 0x00000002
    return i;
#   undef S
}

/**
 * @brief Same as cds_int_log2 but the logarithm is now base 10. This was also
 * taken from https://stackoverflow.com/a/24748637.
 * 
 * @see cds_int_log2
 * 
 * @param n 
 * @return int32_t 
 */
inline int32_t cds_int_log10(uint64_t n) {
#   define S(k, m)          \
    if (n >= UINT64_C(m)) { \
        i += k;             \
        n /= UINT64_C(m);   \
    }

    int32_t i = -(n == 0);
    S(16, 10000000000000000); // 16 zeroes
    S(8, 100000000);          // 8 zeroes
    S(4, 10000);              // and so on...
    S(2, 100);
    S(1, 10);
    return i;

#   undef S
}

/**
 * @brief The number of leading zeroes in a 64-bit unsigned integer.
 * 
 * @param n The input integer.
 * @return int32_t The number of leading zeroes.
 */
inline int32_t cds_uint64_leading_zeros(uint64_t n) {
    // Same as 1 << 63
#   define SIXTY_FOURTH_DIGIT 0x8000000000000000
    int32_t bits = 0;
    while (!(n & SIXTY_FOURTH_DIGIT)) {
        n <<= 1;
        ++bits;
    }
    return bits;
#   undef SIXTY_FOURTH_DIGIT
}

/**
 * @brief The number of leading zeroes in a 32-bit unsigned integer.
 * 
 * @param n The input integer.
 * @return int32_t The number of leading zeroes.
 */
inline int32_t cds_uint32_leading_zeros(uint32_t n) {
    return cds_uint64_leading_zeros((uint64_t) n) - 32;
}

/**
 * @brief The number of leading zeroes in a 16-bit unsigned integer.
 * 
 * @param n The input integer.
 * @return int32_t The number of leading zeroes.
 */
inline int32_t cds_uint16_leading_zeros(uint16_t n) {
    return cds_uint64_leading_zeros((uint64_t) n) - 48;
}

/**
 * @brief The number of leading zeroes in a 8-bit unsigned integer.
 * 
 * @param n The input integer.
 * @return int32_t The number of leading zeroes.
 */
inline int32_t cds_uint8_leading_zeros(uint8_t n) {
    return cds_uint64_leading_zeros((uint64_t) n) - 56;
}

/**
 * @brief Count the number of trailing ones in an integer.
 * 
 * @param n The input integer.
 * @return int32_t The number of trailing ones.
 */
inline int32_t cds_uint64_trailing_ones(uint64_t n) {
    // Put a 1 in the index after the trailing 1s.
    // So 1011 -> 0100
    // If n is max, b == 0
    uint64_t b = ~n & (n+1);
    return b == 0 ? 64 : cds_int_log2(b);
}

#endif