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

struct _cds_vector_t {
    struct _cds_vector_header_t header;
    cds_byte_t buffer[];
};

typedef struct _cds_vector_t cds_vector_t;

CDS_INLINE
cds_ptr_t cds_vector_array(cds_vector_t *self) {
    return self->buffer;
}

CDS_INLINE 
cds_vector_header_t *cds_vector_get_header(cds_ptr_t buffer) {
    if (buffer == NULL)
        return NULL;
    else {
        cds_vector_header_t *header = (cds_vector_header_t*)buffer;
        return header - 1;
    }
}

CDS_PUBLIC
cds_vector_t *cds_vector_new(void);

CDS_PUBLIC
cds_status_t cds_vector_init(cds_vector_t *self, size_t type_size);

#endif