/**
 * @file type.h
 * @author RenoirTan
 * @brief Typedefs used by this library.
 * @version 0.1
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CDATASTRUCTURES_TYPE_H
#   define CDATASTRUCTURES_TYPE_H

#   include <stdbool.h>
#   include <stdint.h>
#   include <stdlib.h>

/**
 * @brief A type that represents one byte (8 bits).
 */
typedef char cds_byte_t;

/**
 * @brief A type representing a character that is 8 bits wide.
 */
typedef char char8_t;

/**
 * @brief A pointer to an array of bytes.
 */
typedef cds_byte_t* cds_array_t;

typedef cds_byte_t* cds_buffer_t;

typedef cds_byte_t cds_slice_t[];

/**
 * @brief A pointer with no type associated with it (a void pointer).
 */
typedef void* cds_ptr_t;

/**
 * @brief The universal type which represents a series of options represented
 * by the individual bits in a 32-bit unsigned integer.
 */
typedef uint32_t cds_flag_t;

enum _cds_ordering_t {
    cds_greater = 1,
    cds_equal = 0,
    cds_lesser = -1
};

typedef enum _cds_ordering_t cds_ordering_t;

/**
 * @brief A function type which destroys an object on the heap.
 */
typedef void (*cds_free_f)(cds_ptr_t);

typedef cds_ordering_t (*cds_compare_f)(cds_ptr_t, cds_ptr_t);

#endif