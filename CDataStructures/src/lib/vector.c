#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CDataStructures/vector.h>

static cds_byte_t *_cds_vector_get(cds_vector_t *self, size_t index) {
    return self->buffer + (index * self->type_size);
}

static cds_status_t _cds_vector_copy_to(
    cds_vector_t *self,
    size_t index,
    cds_ptr_t dest
) {
    cds_ptr_t element = _cds_vector_get(self, index);
    memcpy(dest, element, self->type_size);
    return cds_ok;
}

static cds_status_t _cds_vector_copy_from(
    cds_vector_t *self,
    size_t index,
    cds_ptr_t src
) {
    cds_ptr_t element = _cds_vector_get(self, index);
    memcpy(element, src, self->type_size);
    return cds_ok;
}

static cds_status_t _cds_vector_realloc_buffer(
    cds_vector_t *self,
    size_t capacity
) {
    cds_array_t new_buffer = realloc(self->buffer, capacity);
    if (new_buffer == NULL)
        return cds_alloc_error;
    self->buffer = new_buffer;
    self->_bytes_allocated = capacity;
    return cds_ok;
}

static cds_status_t _cds_vector_reallocate(cds_vector_t *self, size_t length) {
    size_t recommended = _cds_recommended_capacity(length) * self->type_size;
    return _cds_vector_realloc_buffer(self, recommended);
}

static cds_status_t _cds_vector_lazy_reallocate(
    cds_vector_t *self,
    size_t length
) {
    size_t recommended = _cds_recommended_capacity(length) * self->type_size;
    if (self->_bytes_allocated != recommended)
        return _cds_vector_realloc_buffer(self, recommended);
    else
        return cds_ok;
}

static cds_status_t _cds_vector_change_length(
    cds_vector_t *self,
    size_t new_length
) {
    cds_status_t status = _cds_vector_lazy_reallocate(self, new_length);
    if (CDS_IS_ERROR(status))
        return status;
    self->length = new_length;
    return cds_ok;
}

static cds_status_t _cds_vector_increase_one(cds_vector_t *self) {
    if (self->length >= SIZE_MAX)
        return cds_alloc_error;
    return _cds_vector_change_length(self, self->length + 1);
}

static cds_status_t _cds_vector_decrease_one(cds_vector_t *self) {
    if (self->length <= 0)
        return cds_alloc_error;
    return _cds_vector_change_length(self, self->length - 1);
}

static cds_status_t _cds_vector_make_gap(cds_vector_t *self, size_t index) {
    if (index >= self->length)
        return cds_ok;
    size_t block_size = (self->length - index) * self->type_size;
    cds_byte_t *old_location = _cds_vector_get(self, index);
    cds_byte_t *new_location = old_location + self->type_size;
    memcpy(new_location, old_location, block_size);
    return cds_ok;
}

static cds_status_t _cds_vector_close_gap(cds_vector_t *self, size_t index) {
    if (index >= self->length)
        return cds_ok;
    size_t block_size = (self->length - index) * self->type_size;
    cds_byte_t *new_location = _cds_vector_get(self, index);
    cds_byte_t *old_location = new_location + self->type_size;
    memcpy(new_location, old_location, block_size);
    return cds_ok;
}

static cds_status_t _cds_vector_remove(
    cds_vector_t *self,
    size_t index,
    cds_ptr_t dest
);

cds_vector_t *cds_vector_new(void) {
    return malloc(sizeof(cds_vector_t));
}

cds_status_t cds_vector_init(cds_vector_t *self, size_t type_size) {
    CDS_IF_NULL_RETURN_ERROR(self);
    CDS_IF_ZERO_RETURN_ERROR(type_size);
    self->type_size = type_size;
    self->_bytes_allocated = _cds_recommended_capacity(0) * self->type_size;
    self->buffer = malloc(self->_bytes_allocated);
    self->length = 0;
    CDS_IF_NULL_RETURN_ALLOC_ERROR(self->buffer);
    return cds_ok;
}

cds_status_t cds_vector_destroy(cds_vector_t *self, cds_free_f clean_element) {
    if (self == NULL)
        return cds_warning;
    if (self->buffer != NULL) {
        if (clean_element != NULL) {
            size_t index = 0;
            for (; index < self->length; index++) {
                clean_element(_cds_vector_get(self, index));
            }
        }
        free(self->buffer);
        self->buffer = NULL;
    }
    return cds_ok;
}

cds_status_t cds_vector_free(cds_vector_t *self, cds_free_f clean_element) {
    if (self == NULL)
        return cds_warning;
    cds_status_t status = cds_vector_destroy(self, clean_element);
    free(self);
    return status;
}

cds_ptr_t cds_vector_get(cds_vector_t *self, size_t index) {
    // Safe short-circuit in logic gate
    if (self == NULL || self->buffer == NULL || index >= self->length)
        return NULL;
    return _cds_vector_get(self, index);
}

cds_status_t cds_vector_copy_to(
    cds_vector_t *self,
    size_t index,
    cds_ptr_t dest
) {
    if (self == NULL || self->buffer == NULL || dest == NULL)
        return cds_null_error;
    if (index >= self->length)
        return cds_index_error;
    return _cds_vector_copy_to(self, index, dest);
}

cds_status_t cds_vector_copy_from(
    cds_vector_t *self,
    size_t index,
    cds_ptr_t src
) {
    if (self == NULL || self->buffer == NULL || src == NULL)
        return cds_null_error;
    if (index >= self->length)
        return cds_index_error;
    return _cds_vector_copy_from(self, index, src);
}

cds_status_t cds_vector_insert(
    cds_vector_t *self,
    size_t index,
    cds_ptr_t src
) {
    if (self == NULL || self->buffer == NULL || src == NULL)
        return cds_null_error;
    CDS_NEW_STATUS = cds_ok;
    CDS_IF_ERROR_RETURN_STATUS(_cds_vector_increase_one(self));
    CDS_IF_ERROR_RETURN_STATUS(_cds_vector_make_gap(self, index));
    return _cds_vector_copy_from(self, index, src);
}

cds_status_t cds_vector_push_back(cds_vector_t *self, cds_ptr_t src) {
    return cds_vector_insert(self, self->length, src);
}

cds_status_t cds_vector_push_front(cds_vector_t *self, cds_ptr_t src) {
    return cds_vector_insert(self, 0, src);
}

cds_status_t cds_vector_remove(
    cds_vector_t *self,
    size_t index,
    cds_ptr_t dest
) {
    if (self == NULL || self->buffer == NULL)
        return cds_null_error;
    if (index >= self->length)
        return cds_index_error;
    CDS_NEW_STATUS = cds_ok;
    if (dest != NULL)
        CDS_IF_ERROR_RETURN_STATUS(_cds_vector_copy_to(self, index, dest));
    CDS_IF_ERROR_RETURN_STATUS(_cds_vector_close_gap(self, index));
    return _cds_vector_decrease_one(self);
}

cds_status_t cds_vector_pop_back(cds_vector_t *self, cds_ptr_t dest) {
    if (self->length <= 0)
        return cds_warning;
    return cds_vector_remove(self, self->length - 1, dest);
}

cds_status_t cds_vector_pop_front(cds_vector_t *self, cds_ptr_t dest) {
    if (self-> length <= 0)
        return cds_warning;
    return cds_vector_remove(self, 0, dest);
}
