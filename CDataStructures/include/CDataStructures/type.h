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
 * @brief A pointer to an array of bytes.
 */
typedef cds_byte_t* cds_array_t;

/**
 * @brief A pointer with no type associated with it (a void pointer).
 */
typedef void* cds_ptr_t;

/**
 * @brief The universal type which represents a series of options represented
 * by individual bits.
 */
typedef int32_t cds_flag_t;

/**
 * @brief A function type which destroys an object on the heap.
 */
typedef void (*cds_free_f)(cds_ptr_t);

#endif