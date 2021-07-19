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

typedef struct _cds_buffer_header_t cds_buffer_header_t;

struct _cds_buffer_data_t {
    struct _cds_buffer_header_t header;
    cds_buffer_t buffer;
};

typedef struct _cds_buffer_data_t cds_buffer_data_t;

typedef cds_array_t cds_buffer_t;

CDS_INLINE
cds_buffer_t cds_buffer_get_inner(cds_buffer_data_t *self) {
    return self->buffer;
}

CDS_INLINE 
cds_buffer_data_t *cds_buffer_get_data(cds_buffer_t buffer) {
    if (buffer == NULL)
        return NULL;
    else {
        cds_buffer_header_t *header = (cds_buffer_header_t*)buffer;
        return (cds_buffer_data_t*) (header - 1);
    }
}

CDS_INLINE
size_t cds_buffer_alloc_bytes(size_t buffer_bytes) {
    return sizeof(cds_buffer_data_t) + buffer_bytes;
}

CDS_INLINE
size_t cds_buffer_alloc_length(size_t length, size_t type_size) {
    return cds_buffer_alloc_bytes(_cds_recommended_capacity(length) * type_size);
}

CDS_PUBLIC
cds_buffer_t cds_buffer_new(void);

CDS_PUBLIC
cds_status_t cds_buffer_init(cds_buffer_t *buffer, size_t type_size);

CDS_PUBLIC
cds_status_t cds_buffer_destroy(cds_buffer_t buffer, cds_free_f clean_element);

CDS_PUBLIC
cds_status_t cds_buffer_free(cds_buffer_t buffer, cds_free_f clean_element);

#endif