#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CDataStructures/_vector_unsized.h>
#include <CDataStructures/utils.h>

#define _HEAD(self) (*self)->header
#define _VALIDATE_BUF(buffer) \
    CDS_IF_NULL_RETURN_ERROR(buffer); \
    self = cds_vector_get_data(buffer); \
    CDS_IF_NULL_RETURN_ERROR(self);

CDS_PRIVATE
cds_status_t _cds_vector_realloc_data(
    cds_vector_data_t **self,
    size_t bytes
) {
    cds_vector_data_t *new = realloc(*self, bytes);
    CDS_IF_NULL_RETURN_ALLOC_ERROR(new);
    *self = new;
    _HEAD(self)._bytes_allocated = bytes;
    return cds_ok;
}

CDS_PRIVATE
cds_status_t _cds_vector_realloc_eager(
    cds_vector_data_t **self,
    size_t length
) {
    CDS_NEW_STATUS = _cds_vector_realloc_data(
        self,
        cds_vector_alloc_length(length, _HEAD(self).type_size)
    );
    if (!CDS_IS_ERROR(status)) {
        _HEAD(self).length = length;
    }
    return status;
}

CDS_PRIVATE
cds_status_t _cds_vector_realloc_lazy(
    cds_vector_data_t **self,
    size_t length
) {
    size_t bytes = cds_vector_alloc_length(length, _HEAD(self).type_size);
    if (bytes != _HEAD(self)._bytes_allocated) {
        CDS_NEW_STATUS = _cds_vector_realloc_data(self, bytes);
        if (!CDS_IS_ERROR(status)) {
            _HEAD(self).length = length;
        }
        return status;
    } else {
        return cds_ok;
    }
}

CDS_PRIVATE
cds_ptr_t _cds_vector_get(cds_vector_data_t *self, size_t index) {
    return cds_vector_get_buffer(self) + (index * self->header.type_size);
}

CDS_PRIVATE
cds_status_t _cds_vector_destroy(
    cds_vector_data_t **_self,
    cds_free_f clean_element
) {
    cds_vector_data_t *self = _self;
    if (clean_element != NULL) {
        size_t index = 0;
        for (; index < self->header.length; ++index) {
            clean_element(_cds_vector_get(self, index));
        }
    }
    return _cds_vector_realloc_eager(self, 0);
}

CDS_PUBLIC
cds_vector_t cds_vector_new(void) {
    cds_vector_data_t *vector = CDS_NEW(cds_vector_data_t);
    if (vector == NULL)
        return NULL;
    return cds_vector_get_buffer(vector);
}

CDS_PUBLIC
cds_status_t cds_vector_init(cds_vector_t *buffer, size_t type_size) {
    CDS_IF_NULL_RETURN_ERROR(buffer);
    CDS_IF_NULL_RETURN_ERROR(*buffer);
    CDS_IF_ZERO_RETURN_ERROR(type_size);
    cds_vector_data_t *self = cds_vector_get_data(*buffer);
    self->header.type_size = type_size;
    self->header.length = 0;
    cds_vector_data_t *inited = realloc(
        self,
        cds_vector_alloc_length(0, type_size)
    );
    if (inited == NULL)
        return cds_alloc_error;
    else {
        *buffer = cds_vector_get_buffer(self);
        return cds_ok;
    }
}

CDS_PUBLIC
cds_status_t cds_vector_destroy(cds_vector_t buffer, cds_free_f clean_element) {
    cds_vector_data_t *self;
    _VALIDATE_BUF(buffer);
    CDS_IF_NULL_RETURN_ERROR(self);
    CDS_NEW_STATUS;
    if (!CDS_IS_ERROR(_cds_vector_destroy(&self, clean_element))) {
        cds_vector_get_buffer(self);
    }
    return status;
}

CDS_PUBLIC
cds_status_t cds_vector_free(cds_vector_t buffer, cds_free_f clean_element) {
    CDS_NEW_STATUS;
    CDS_IF_ERROR_RETURN_STATUS(cds_vector_destroy(buffer, clean_element));
    free(cds_vector_get_data(buffer));
    return cds_ok;
}
