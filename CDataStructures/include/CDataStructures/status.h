#ifndef CDATASTRUCTURES_STATUS_H
#   define CDATASTRUCTURES_STATUS_H

enum _cds_status_t {
    cds_index_error = 5,
    cds_zero_error = 4,
    cds_alloc_error = 3,
    cds_null_error = 2,
    cds_error = 1,
    cds_ok = 0,
    cds_warning = -1,
};

typedef enum _cds_status_t cds_status_t;

#   define CDS_NEW_STATUS cds_status_t status
#   define CDS_IF_STATUS_ERROR(expression) if ((status = expression) > 0)
#   define CDS_IF_ERROR_RETURN_STATUS(expression) \
    CDS_IF_STATUS_ERROR(expression) return status;
#   define CDS_IF_ERROR_RETURN_NULL(expression) \
    CDS_IF_STATUS_ERROR(expression) return NULL;

#   define CDS_IS_ERROR(status) ((status) > 0)

#   define CDS_IF_NULL_RETURN_ERROR(pointer) \
    if (pointer == NULL) \
        return cds_null_error;

#   define CDS_IF_NULL_RETURN_ALLOC_ERROR(pointer) \
    if (pointer == NULL) \
        return cds_alloc_error;

#   define CDS_IF_ZERO_RETURN_ERROR(value) \
    if (value == 0) \
        return cds_zero_error;

#endif