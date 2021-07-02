#ifndef CDATASTRUCTURES_VECTOR_H
#   define CDATASTRUCTURES_VECTOR_H

#   include "_prelude.h"
#   include "_common.h"

struct _cds_vector_t {
    cds_byte_t *buffer;
    size_t type_size;
    size_t length;
    size_t _bytes_allocated;
};

/**
 * @brief A structure representing a vector.
 */
typedef struct _cds_vector_t cds_vector_t;

/**
 * @brief Get the pointer to the internal buffer.
 * 
 * @param self The pointer to a vector object.
 * @return cds_ptr_t 
 */
static inline cds_ptr_t cds_vector_array(cds_vector_t *self) {
    return self->buffer;
}

/**
 * @brief Get the vector metadata from an array allocated using cds_vector_new
 * and/or initialised by cds_vector_init.
 * 
 * @param buffer The pointer to the buffered array.
 * @return cds_vector_t* 
 */
static inline cds_vector_t *cds_vector_get_info(cds_ptr_t buffer) {
    return (cds_vector_t*) buffer; 
}

/**
 * @brief Allocate memory for a new vector on the heap.
 * 
 * @return cds_vector_t* The location of the vector in memory.
 */
cds_vector_t *cds_vector_new(void);

/**
 * @brief Initialise the vector with the memory block for the buffer and the
 * size of each type.
 * 
 * @param self The pointer to a vector object.
 * @param type_size The size of the type being stored in bytes.
 * @return cds_status_t This operation's status code.
 */
cds_status_t cds_vector_init(cds_vector_t *self, size_t type_size);

/**
 * @brief Get the pointer to an element in the vector.
 * 
 * @param self The pointer to a vector object.
 * @param index The placement of the element in the queue.
 * @return cds_ptr_t The pointer to the element. NULL if there is an error.
 */
cds_ptr_t cds_vector_get(cds_vector_t *self, size_t index);

/**
 * @brief Overwrite the data pointed by a pointer with the data in one of the
 * elements of the vector.
 * 
 * @param self The pointer to a vector object.
 * @param index The position of the element in the array to be copied from.
 * @param dest The pointer to the data to be overwritten.
 * @return cds_status_t 
 */
cds_status_t cds_vector_copy_to(
    cds_vector_t *self,
    size_t index,
    cds_ptr_t dest
);

/**
 * @brief Overwrite the data of one of the elements in the vector with the
 * data from a "source" pointer.
 * 
 * @param self The pointer to a vector object.
 * @param index The index of the element to be overwritten.
 * @param src The source of the data.
 * @return cds_status_t 
 */
cds_status_t cds_vector_copy_from(
    cds_vector_t *self,
    size_t index,
    cds_ptr_t src
);

/**
 * @brief Insert an element to the vector.
 * 
 * @param self The pointer to a vector object.
 * @param index The location of the new element.
 * @param src The source of the data.
 * @return cds_status_t 
 */
cds_status_t cds_vector_insert(cds_vector_t *self, size_t index, cds_ptr_t src);

/**
 * @brief Push an element to the end of a vector.
 * 
 * @param self The pointer to a vector object.
 * @param src The source of the data of the new element.
 * @return cds_status_t 
 */
cds_status_t cds_vector_push_back(cds_vector_t *self, cds_ptr_t src);

/**
 * @brief Remove an element from the vector. If dest is a non-null pointer, the
 * data from the removed element is copied over to dest, otherwise dest is
 * simply ignored.
 * 
 * @param self The pointer to a vector object.
 * @param index The index of the element to be removed from the array.
 * @param dest The pointer to a memory block to be overwritten by the data from
 * the removed element.
 * @return cds_status_t 
 */
cds_status_t cds_vector_remove(
    cds_vector_t *self,
    size_t index,
    cds_ptr_t dest
);

/**
 * @brief Remove the last element from the vector. If dest is a non-null
 * pointer, the data from the removed element is copied over to dest, otherwise
 * dest is simply ignored.
 * 
 * @param self The pointer to a vector object.
 * @param dest The pointer to a memory block to be overwritten by the data from
 * the removed element.
 * @return cds_status_t 
 */
cds_status_t cds_vector_pop_back(cds_vector_t *self, cds_ptr_t dest);

#endif