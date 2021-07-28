#ifndef CDATASTRUCTURES_VECTOR_H
#   define CDATASTRUCTURES_VECTOR_H

#   include "_prelude.h"
#   include "_common.h"
#   include "utils.h"

struct _cds_buffer_header_t {
    size_t type_size;
    size_t length;
    size_t _bytes_allocated;
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
    return self->buffer;
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
cds_buffer_data_t *cds_buffer_get_data(cds_slice_t buffer) {
    if (buffer == NULL)
        return NULL;
    else {
        cds_buffer_header_t *header = (cds_buffer_header_t*)buffer;
        return (cds_buffer_data_t*) (header - 1);
    }
}

/**
 * @brief Get how many bytes should be allocated to store the buffer including
 * the preceding metadata.
 * 
 * @param buffer_bytes The number of bytes allocated exclusively for the buffer
 * (the part of the struct which stores user data).
 * 
 * @return size_t The number of bytes required for the entire object.
 */
CDS_INLINE
size_t cds_buffer_alloc_bytes(size_t buffer_bytes) {
    return sizeof(cds_buffer_data_t) + buffer_bytes;
}

/**
 * @brief Get the amount of bytes required to store a buffer (including
 * metadata) in memory based on how much data is stored inside (`length`) and
 * the size of each piece of data (`type_size`).
 * 
 * @param length The number of pieces of data stored in the buffer.
 * @param type_size The number of bytes each piece of data requires. This value
 * can be obtained using the `sizeof(type)` macro.
 * 
 * @return size_t The number of bytes required to be reserved for the full
 * buffer.
 */
CDS_INLINE
size_t cds_buffer_alloc_length(size_t length, size_t type_size) {
    return cds_buffer_alloc_bytes(
        _cds_recommended_capacity(length) * type_size
    );
}

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
cds_status_t cds_buffer_destroy(cds_buffer_t buffer, cds_free_f clean_element);

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
cds_status_t cds_buffer_reserve_more(cds_buffer_t buffer, size_t amount);

#endif