#ifndef CDATASTRUCTURES_ALLOC_H
#   define CDATASTRUCTURES_ALLOC_H

#   include "_prelude.h"
#   include "_common.h"

#   ifndef CDS_DEFAULT_BLOCK_MINSIZE
#       define CDS_DEFAULT_BLOCK_MINSIZE 16
#   endif

#   ifndef CDS_DEFAULT_BLOCK_INCREMENT
#       define CDS_DEFAULT_BLOCK_INCREMENT 8
#   endif

struct _cds_alloc_config_t {
    size_t constant_offset;
    size_t block_mincapacity;
    size_t block_increment;
};

/**
 * @brief A configuration structure that allows you to store options for how
 * much memory should be given to your data structure. Using this (with
 * functions ending in `...with_config`) is less perilous than using the other
 * functions without that suffix, as any changes to your config object gets
 * transferred to all instances where your config object gets used.
 */ 
typedef struct _cds_alloc_config_t cds_alloc_config_t;

/**
 * @brief Calculate the number of bytes required to store a dynamically
 * allocated object. The difference between the result and
 * `block_mincapacity` * `type_size` will always be divisible by
 * `block_increment` and will always be equals to or greater than
 * `length` * `type_size` + `constant_offset`.
 * 
 * This formula takes into account the fact these dynamically allocated data
 * structures will usually have some metadata (whose size is constant, hence
 * the name `constant_offset`) accompanying the dynamically allocated portion
 * of the object and so the space recommended will be aligned to any multiple
 * of `block_increment` (as long as `block_mincapacity` is also a multiple of
 * `block_increment`).
 * 
 * @param length The number of elements the dynamically allocated portion of
 * the object should be able to hold.
 * @param type_size The size of each element in bytes.
 * @param constant_offset The minimum amount of memory the object actually uses.
 * This corresponds to the size of the metadata segment of a dynamically
 * allocated data structure.
 * @param block_mincapacity The minimum amount of space the object should
 * be given. This parameter is multiplied by `type_size` to ensure that any
 * extra space implied by `block_mincapacity` can contain roughly the same
 * number of elements.
 * @param block_increment If the object needs more space, how much more space
 * should be committed to the object.
 * 
 * @return size_t The number of bytes required to store the object.
 */
CDS_PUBLIC
size_t cds_required_space(
    size_t length,
    size_t type_size,
    size_t constant_offset,
    size_t block_mincapacity,
    size_t block_increment
);

/**
 * @see cds_required_space
 * 
 * @brief How much memory (in bytes) should be given to a dynamically allocated
 * object. See `cds_required_space` for more information on how this works.
 * 
 * @param length The number of elements the object should be able to store.
 * @param type_size The size of each element in bytes.
 * @param config The memory allocation configuration object for your data
 * structure. See cds_alloc_config_t for more information on its purpose.
 * 
 * @return size_t The required number of bytes to be allocated.
 */ 
CDS_PUBLIC
size_t cds_required_space_with_config(
    size_t length,
    size_t type_size,
    cds_alloc_config_t config
);

#endif