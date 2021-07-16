#ifndef CDATASTRUCTURES_VECTOR_H
#   define CDATASTRUCTURES_VECTOR_H

#   include "_prelude.h"
#   include "_common.h"

struct _cds_vector_header_t {
    size_t type_size;
    size_t length;
    size_t _bytes_allocated;
};

typedef struct _cds_vector_header_t cds_vector_header_t;

struct _cds_vector_data_t {
    struct _cds_vector_header_t header;
    cds_buffer_t buffer;
};

typedef struct _cds_vector_data_t cds_vector_data_t;

typedef cds_array_t cds_vector_t;

CDS_INLINE
cds_vector_t cds_vector_get_buffer(cds_vector_data_t *self) {
    return self->buffer;
}

CDS_INLINE 
cds_vector_data_t *cds_vector_get_data(cds_vector_t buffer) {
    if (buffer == NULL)
        return NULL;
    else {
        cds_vector_header_t *header = (cds_vector_header_t*)buffer;
        return (cds_vector_data_t*) (header - 1);
    }
}

CDS_INLINE
size_t cds_vector_alloc_size(size_t buffer_bytes) {
    return sizeof(cds_vector_data_t) + buffer_bytes;
}

CDS_INLINE
size_t cds_vector_alloc_length(size_t length, size_t type_size) {
    return cds_vector_alloc_size(_cds_recommended_capacity(length) * type_size);
}

CDS_PUBLIC
cds_vector_t cds_vector_new(void);

CDS_PUBLIC
cds_status_t cds_vector_init(cds_vector_t *buffer, size_t type_size);

CDS_PUBLIC
cds_status_t cds_vector_destroy(cds_vector_t buffer, cds_free_f clean_element);

CDS_PUBLIC
cds_status_t cds_vector_free(cds_vector_t buffer, cds_free_f clean_element);

#endif