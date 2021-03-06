#ifndef CDATASTRUCTURES_DYNBUFFER_H
#   define CDATASTRUCTURES_DYNBUFFER_H

#   include "_prelude.h"
#   include "_common.h"
#   ifdef CDS_USE_ALLOC_LIB
#       include "alloc.h"
#   endif
#   include "utils.h"
#   ifdef CDS_DEBUG
#       include <stdio.h>
#   endif

/**
 * @brief A pointer to an array of bytes. Although it pretty much has the same
 * representation under the hood as `cds_array_t`, I've defined this typedef
 * to distinguish the "purposes" of variables marked as a `cds_array_t` and
 * a `cds_buffer_t`.
 */
typedef cds_ptr_t cds_buffer_t;

struct _cds_buffer_header_t {
    size_t type_size;
    size_t length;
    size_t reserved;
    size_t bytes_allocated;
};

/**
 * @brief The part of the buffer that stores metadata about it, including its
 * length and how much capacity has been allocated for it.
 */
typedef struct _cds_buffer_header_t cds_buffer_header_t;

struct _cds_buffer_data_t {
    struct _cds_buffer_header_t header;
    cds_slice_t buffer;
};

/**
 * @brief The entire buffer, including the metadata from `cds_buffer_header_t`
 * as `cds_buffer_data_t::header` and the dynamically-sized array at the end as
 * `cds_buffer_data_t::buffer`.
 */
typedef struct _cds_buffer_data_t cds_buffer_data_t;

#   ifdef CDS_USE_ALLOC_LIB
/**
 * @brief Memory allocation configuration data for `cds_buffer_t`.
 */
CDS_PUBLIC const cds_alloc_config_t CDS_BUFFER_DATA_ALLOC_CONFIG;
#   endif

// typedef cds_array_t cds_buffer_t;

/**
 * @brief Get a pointer to the buffer stored in a `cds_buffer_data_t` object.
 * 
 * @param self The pointer to a `cds_buffer_data_t` object.
 * 
 * @return cds_buffer_t The buffer stored by the object.
 */
CDS_INLINE
cds_buffer_t cds_buffer_get_inner(cds_buffer_data_t *self) {
#ifdef CDS_DEBUG
    printf(" --> [cds_buffer_get_inner]\n");
#endif
#ifdef CDS_DEBUG
    printf(" <-- [cds_buffer_get_inner] Returning inner buffer\n");
#endif
    return (cds_buffer_t) &((cds_buffer_header_t *) self)[1];
}

/**
 * @brief Get the `cds_buffer_data_t` object managing the current buffer.
 * 
 * @param self The pointer to the buffer storing all your data.
 * 
 * @return cds_buffer_data_t* The pointer to the object managing the given
 * buffer.
 */
CDS_INLINE 
cds_buffer_data_t *cds_buffer_get_data(cds_buffer_t buffer) {
#ifdef CDS_DEBUG
    printf(" --> [cds_buffer_get_data]\n");
#endif
    if (buffer == NULL) {
#ifdef CDS_DEBUG
        printf(" <-- [cds_buffer_get_data] NULL pointer\n");
#endif
        return NULL;
    } else {
#ifdef CDS_DEBUG
        printf("[cds_buffer_get_data] Grabbing header\n");
#endif
        cds_buffer_header_t *header = (cds_buffer_header_t*)buffer;
#ifdef CDS_DEBUG
        printf(" <-- [cds_buffer_get_data] Returning\n");
#endif
        return (cds_buffer_data_t*) (header - 1);
    }
}

#define _SIZE_T_FIELDS(applier) \
    applier(type_size) \
    applier(length) \
    applier(reserved) \
    applier(bytes_allocated)

#define _SIZE_T_GETTER(field) \
    CDS_INLINE \
    size_t CDS_SMASH_PUBLIC(buffer, _CDS_SMASH_NAMES(get, field)) \
    (cds_buffer_t buffer) { \
        return cds_buffer_get_data(buffer)->header.field; \
    }

_SIZE_T_FIELDS(_SIZE_T_GETTER)

#undef _SIZE_T_GETTER
#undef _SIZE_T_FIELDS

/**
 * @brief Calculate the number of required bytes based on the desired
 * `length` of the buffer.
 * 
 * @param self The data object managing the buffer.
 * @param length The desired length.
 * 
 * @return size_t The number of bytes to be allocated.
 */
CDS_PUBLIC
size_t cds_buffer_required_bytes(cds_buffer_data_t *self, size_t length);

/**
 * @brief Create a new uninitialised buffer object.
 * 
 * @return cds_buffer_t The pointer to the buffer (not including the preceding
 * buffer metadata).
 */
CDS_PUBLIC
cds_buffer_t cds_buffer_new(void);

/**
 * @brief Initialise the buffer object with the size of the type. In addition,
 * the buffer object will be of 0 length.
 * 
 * Please note that all data previously stored in the buffer will be
 * permanently lost, unless they are simply pointers to an object stored
 * somewhere else.
 * 
 * @param buffer The buffer to be initialised.
 * @param type_size The size of the type of data to be stored. This value can
 * be computed using `sizeof(type)`. For example, if you are storing `int`s
 * in this buffer, you can use `sizeof(int)`.
 * 
 * @return cds_status_t The status code for this operation.
 */
CDS_PUBLIC
cds_status_t cds_buffer_init(cds_buffer_t *buffer, size_t type_size);

/**
 * @brief Destroy all the data stored in the buffer, clearing the entire
 * buffer to length 0 without freeing the memory storing the buffer metadata.
 * 
 * This function uses another function (called `clean_element`) to clean each
 * element of data in the buffer.
 * 
 * @param buffer The buffer to clear.
 * @param clean_element The function used to clean each element.
 * 
 * @return cds_status_t The status code of this operation.
 */
CDS_PUBLIC
cds_status_t cds_buffer_destroy(cds_buffer_t *buffer, cds_free_f clean_element);

/**
 * @brief Free the entire buffer, including the metadata.
 * 
 * This function uses another function (called `clean_element`) to clean each
 * element of data in the buffer.
 * 
 * @param buffer The buffer to clear.
 * @param clean_element The function used to clean each element.
 * 
 * @return cds_status_t The status code of this operation.
 */
CDS_PUBLIC
cds_status_t cds_buffer_free(cds_buffer_t buffer, cds_free_f clean_element);


/**
 * @brief Increase the size of the buffer so that it can fit an additional
 * specified number of elements (`amount`).
 * 
 * @param buffer The buffer whose size is to be increased.
 * @param amount The number of extra elements the buffer should have.
 * 
 * @return cds_status_t The status code of this operation.
 */
CDS_PUBLIC
cds_status_t cds_buffer_reserve(cds_buffer_t *buffer, size_t amount);


/**
 * @brief Remove unused capacity from the buffer. This means that the amount
 * of space reserved for this buffer should only be able to hold the current
 * number of elements inside the buffer. This has the effect of reducing the
 * amount of space used by the buffer, hence "compacting" it.
 * 
 * @param buffer The buffer to be compacted into a smaller memory block.
 * 
 * @return cds_status_t The status code of this operation.
 */
CDS_PUBLIC
cds_status_t cds_buffer_compact(cds_buffer_t *buffer);


/**
 * @brief Insert an item into the buffer at the specified index. After
 * insertion, the item can be accessed again using `buffer[index]`. This
 * function inserts the item by copying the data held in `src`.
 * 
 * @param buffer The buffer which you want to insert the element into.
 * @param index The position of the new element.
 * @param src A pointer pointing to the data to be inserted into the buffer.
 * 
 * @return cds_status_t The status code of this operation.
 */
CDS_PUBLIC
cds_status_t cds_buffer_insert(
    cds_buffer_t *buffer,
    size_t index,
    cds_ptr_t src
);


/**
 * @brief Insert an item to the start of the buffer.
 * 
 * @param buffer The buffer which you want to insert the element into.
 * @param src A pointer pointing to the data to be inserted into the buffer.
 * 
 * @return cds_status_t The status code of this operation.
 */
CDS_PUBLIC
cds_status_t cds_buffer_push_front(cds_buffer_t *buffer, cds_ptr_t src);


/**
 * @brief Insert an item to the end of the buffer.
 * 
 * @param buffer The buffer which you want to insert the element into.
 * @param src A pointer pointing to the data to be inserted into the buffer.
 * 
 * @return cds_status_t The status code of this operation.
 */
CDS_PUBLIC
cds_status_t cds_buffer_push_back(cds_buffer_t *buffer, cds_ptr_t src);


/**
 * @brief Remove an item in the buffer at a specified index. As you may want
 * to use the item's data somewhere else, you can pass in a pointer to the
 * `dest` parameter to copy the removed data to.
 * 
 * @param buffer The buffer you want to remove the item from.
 * @param index The index of the element.
 * @param dest The destination pointer which contains the address of the
 * memory block where you want to copy the discarded element's data to. If
 * the pointer is NULL, then no data will be copied over.
 * @return cds_status_t The status code of this operation.
 */
CDS_PUBLIC
cds_status_t cds_buffer_remove(
    cds_buffer_t *buffer,
    size_t index,
    cds_ptr_t dest
);


/**
 * @brief Remove the first item in the buffer. The data of the now deleted
 * element will be copied to `dest` if it's not NULL.
 * 
 * @see cds_buffer_remove
 * 
 * @param buffer The buffer you want to remove the item from.
 * @param dest The destination pointer for the removed data.
 * @return cds_status_t The status code of this operation.
 */
CDS_PUBLIC
cds_status_t cds_buffer_pop_front(cds_buffer_t *buffer, cds_ptr_t dest);


/**
 * @brief Remove the last item in the buffer. The data of the now deleted
 * element will be copied to `dest` if it's not NULL.
 * 
 * @see cds_buffer_remove
 * 
 * @param buffer The buffer you want to remove the item from.
 * @param dest The destination pointer for the removed data.
 * @return cds_status_t The status code of this operation.
 */
CDS_PUBLIC
cds_status_t cds_buffer_pop_back(cds_buffer_t *buffer, cds_ptr_t dest);

#endif