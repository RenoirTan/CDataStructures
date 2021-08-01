#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CDataStructures/dynbuffer.h>

#define _HEAD(self) (*self)->header
#define _VALIDATE_BUF(buffer) \
    CDS_IF_NULL_RETURN_ERROR(buffer); \
    self = cds_buffer_get_data(buffer); \
    CDS_IF_NULL_RETURN_ERROR(self);


const cds_alloc_config_t CDS_BUFFER_DATA_ALLOC_CONFIG = {
    .constant_offset = sizeof(cds_buffer_header_t),
    .block_mincapacity = CDS_DEFAULT_BLOCK_MINSIZE,
    .block_increment = CDS_DEFAULT_BLOCK_INCREMENT
};

/**
 * @brief Get how many bytes are required to store a buffer of a certain
 * length carrying a certain type of data.
 */
CDS_PRIVATE
size_t _cds_buffer_required_bytes(cds_buffer_data_t *self, size_t capacity) {
#if 0
    return cds_required_space_with_config(
        capacity,
        self->header.type_size,
        CDS_BUFFER_DATA_ALLOC_CONFIG
    );
#else
    return self->header.type_size * capacity + sizeof(cds_buffer_header_t);
#endif
}

CDS_INLINE
size_t _cds_buffer_calculate_reserved_from_bytes_allocated(
    cds_buffer_data_t *self
) {
    return (self->header.bytes_allocated - sizeof(cds_buffer_header_t))
        / self->header.type_size;
}

CDS_INLINE
void _cds_buffer_set_reserved_from_bytes_allocated(cds_buffer_data_t *self) {
    self->header.reserved =
        _cds_buffer_calculate_reserved_from_bytes_allocated(self);
}

/**
 * @brief Reallocate the buffer to a certain number of bytes.
 */
CDS_PRIVATE
cds_status_t _cds_buffer_realloc_data(
    cds_buffer_data_t **self,
    size_t bytes
) {
    cds_buffer_data_t *new = realloc(*self, bytes);
    CDS_IF_NULL_RETURN_ALLOC_ERROR(new);
    *self = new;
    _HEAD(self).bytes_allocated = bytes;
    return cds_ok;
}

/* 
CDS_PRIVATE
cds_status_t _cds_buffer_realloc_eager(
    cds_buffer_data_t **self,
    size_t length
) {
    size_t bytes = _cds_buffer_required_bytes(*self, length);
    CDS_NEW_STATUS = _cds_buffer_realloc_data(self, bytes);
    if (!CDS_IS_ERROR(status)) {
        _HEAD(self).length = length;
        _cds_buffer_set_reserved_from_bytes_allocated(*self);
    }
    return status;
}

CDS_PRIVATE
cds_status_t _cds_buffer_realloc_lazy(
    cds_buffer_data_t **self,
    size_t length
) {
    size_t bytes = _cds_buffer_required_bytes(*self, length);
    if (bytes > _HEAD(self)._bytes_allocated) {
        CDS_NEW_STATUS = _cds_buffer_realloc_data(self, bytes);
        if (!CDS_IS_ERROR(status)) {
            _HEAD(self).length = length;
            _cds_buffer_set_reserved_from_bytes_allocated(*self);
        }
        return status;
    } else {
        _HEAD(self).length = length;
        return cds_ok;
    }
}
 */

CDS_PRIVATE
cds_status_t _cds_buffer_reserve(
    cds_buffer_data_t **self,
    size_t new_capacity
) {
    CDS_NEW_STATUS = cds_ok;
    size_t current = _HEAD(self).reserved;
    if (new_capacity > current) {
        CDS_IF_ERROR_RETURN_STATUS(_cds_buffer_realloc_data(
            self,
            _cds_buffer_required_bytes(*self, new_capacity)
        ));
        _HEAD(self).reserved = new_capacity;
    } else if (new_capacity < current) {
        return cds_alloc_error;
    }
    return status;
}

CDS_PRIVATE
cds_status_t _cds_buffer_increase_reserved(cds_buffer_data_t **self) {
    size_t extra = _HEAD(self).reserved;
    if (extra == 0)
        return _cds_buffer_reserve(self, 1);
    CDS_NEW_STATUS = cds_ok;
    while (extra > 0) {
        size_t new_capacity = _HEAD(self).reserved + extra;
        switch (status = _cds_buffer_reserve(self, new_capacity)) {
            case cds_ok:
                return cds_ok;
            case cds_alloc_error:
                extra >>= 1;
                break;
            default:
                return status;
        }
    }
    return cds_error;
}

CDS_PRIVATE
cds_status_t _cds_buffer_fit(cds_buffer_data_t **self) {
    size_t length = _HEAD(self).length;
    size_t old_reserved = _HEAD(self).reserved;
    if (length < old_reserved) {
        CDS_NEW_STATUS = cds_ok;
        CDS_IF_ERROR_RETURN_STATUS(_cds_buffer_realloc_data(
            self,
            _cds_buffer_required_bytes(*self, length)
        )) else {
            _HEAD(self).reserved = length;
            return status;
        }
    } else if (length > old_reserved) {
        return cds_error;
    } else {
        return cds_ok;
    }
}

CDS_PRIVATE
cds_status_t _cds_buffer_set_length(cds_buffer_data_t **self, size_t length) {
    if (length > _HEAD(self).reserved) {
        CDS_NEW_STATUS = cds_ok;
        CDS_IF_ERROR_RETURN_STATUS(_cds_buffer_increase_reserved(self));
        _HEAD(self).length = length;
        return status;
    } else {
        _HEAD(self).length = length;
        return cds_ok;
    }
}

CDS_PRIVATE
cds_ptr_t _cds_buffer_get(cds_buffer_data_t *self, size_t index) {
    return cds_buffer_get_inner(self) + (index * self->header.type_size);
}

CDS_PRIVATE
cds_status_t _cds_buffer_destroy(
    cds_buffer_data_t **self,
    cds_free_f clean_element
) {
    if (clean_element != NULL) {
        size_t index = 0;
        for (; index < _HEAD(self).length; ++index) {
            clean_element(_cds_buffer_get(*self, index));
        }
    }
    CDS_NEW_STATUS = cds_ok;
    CDS_IF_ERROR_RETURN_STATUS(_cds_buffer_set_length(self, 0));
    CDS_IF_ERROR_RETURN_STATUS(_cds_buffer_fit(self));
    return status;
}

CDS_PRIVATE
cds_status_t _cds_buffer_make_gap(cds_buffer_data_t *self, size_t index) {
    if (index >= self->header.length)
        return cds_ok;
    size_t block_size = (self->header.length - index) * self->header.type_size;
    cds_byte_t *old_location = _cds_buffer_get(self, index);
    cds_byte_t *new_location = old_location + self->header.type_size;
    memcpy(new_location, old_location, block_size);
    return cds_ok;
}

CDS_PRIVATE
cds_status_t _cds_buffer_close_gap(cds_buffer_data_t *self, size_t index) {
    if (index >= self->header.length)
        return cds_error;
    size_t block_size = (self->header.length - index - 1)
        * self->header.type_size;
    cds_byte_t *new_location = _cds_buffer_get(self, index);
    cds_byte_t *old_location = old_location + self->header.type_size;
    memcpy(new_location, old_location, block_size);
    return cds_ok;
}

CDS_PRIVATE
cds_status_t _cds_buffer_insert(
    cds_buffer_data_t **self,
    size_t index,
    cds_ptr_t src
) {
    if (index > _HEAD(self).length) {
        return cds_index_error;
    }

    CDS_NEW_STATUS = cds_ok;

    CDS_IF_ERROR_RETURN_STATUS(_cds_buffer_set_length(
        self,
        _HEAD(self).length + 1
    ));
    CDS_IF_ERROR_RETURN_STATUS(_cds_buffer_make_gap(*self, index));
    memcpy(_cds_buffer_get(*self, index), src, _HEAD(self).type_size);

    return status;
}

CDS_PUBLIC
size_t cds_buffer_required_bytes(cds_buffer_data_t *self, size_t length) {
    if (self == NULL)
        return cds_null_error;
    else
        return _cds_buffer_required_bytes(self, length);
}

CDS_PUBLIC
cds_buffer_t cds_buffer_new(void) {
    cds_buffer_data_t *buffer = CDS_NEW(cds_buffer_data_t);
    if (buffer == NULL)
        return NULL;
    return cds_buffer_get_inner(buffer);
}

CDS_PUBLIC
cds_status_t cds_buffer_init(cds_buffer_t *buffer, size_t type_size) {
    CDS_IF_NULL_RETURN_ERROR(buffer);
    CDS_IF_NULL_RETURN_ERROR(*buffer);
    CDS_IF_ZERO_RETURN_ERROR(type_size);
    cds_buffer_data_t *self = cds_buffer_get_data(*buffer);
    self->header.type_size = type_size;
    self->header.length = 0;
    self->header.reserved = 0;
    CDS_NEW_STATUS;
    CDS_IF_ERROR_RETURN_STATUS(_cds_buffer_realloc_eager(&self, 0)) else {
        *buffer = cds_buffer_get_inner(self);
        return cds_ok;
    }
}

CDS_PUBLIC
cds_status_t cds_buffer_destroy(cds_buffer_t *buffer, cds_free_f clean_element) {
    cds_buffer_data_t *self;
    _VALIDATE_BUF(buffer);
    CDS_IF_NULL_RETURN_ERROR(self);
    CDS_NEW_STATUS;
    if (!CDS_IS_ERROR(_cds_buffer_destroy(&self, clean_element))) {
        *buffer = cds_buffer_get_inner(self);
    }
    return status;
}

CDS_PUBLIC
cds_status_t cds_buffer_free(cds_buffer_t buffer, cds_free_f clean_element) {
    CDS_NEW_STATUS = cds_ok;
    CDS_IF_ERROR_RETURN_STATUS(cds_buffer_destroy(buffer, clean_element));
    free(cds_buffer_get_data(buffer));
    return status;
}

CDS_PUBLIC
cds_status_t cds_buffer_reserve(cds_buffer_t *buffer, size_t amount) {
    CDS_IF_NULL_RETURN_ERROR(buffer);
    cds_buffer_data_t *self;
    _VALIDATE_BUF(*buffer);
    CDS_IF_NULL_RETURN_ERROR(self);

    size_t needed = self->header.length + amount;
    CDS_NEW_STATUS = cds_ok;
    CDS_IF_ERROR_RETURN_STATUS(_cds_buffer_reserve(&self, needed)) else {
        *buffer = cds_buffer_get_inner(self);
    }
    return status;
}

CDS_PUBLIC
cds_status_t cds_buffer_compact(cds_buffer_t *buffer) {
    CDS_IF_NULL_RETURN_ERROR(buffer);
    cds_buffer_data_t *self;
    _VALIDATE_BUF(*buffer);
    CDS_IF_NULL_RETURN_ERROR(self);

    CDS_NEW_STATUS = cds_ok;
    CDS_IF_ERROR_RETURN_STATUS(_cds_buffer_fit(&self)) else {
        *buffer = cds_buffer_get_inner(self);
    }
    return status;
}

CDS_PUBLIC
cds_status_t cds_buffer_insert(
    cds_buffer_t *buffer,
    size_t index,
    cds_ptr_t src
) {
    CDS_IF_NULL_RETURN_ERROR(buffer);
    CDS_IF_NULL_RETURN_ERROR(src);
    cds_buffer_data_t *self;
    _VALIDATE_BUF(*buffer);
    CDS_IF_NULL_RETURN_ERROR(self);
    CDS_NEW_STATUS = _cds_buffer_insert(&self, index, src);
    CDS_IF_ERROR_RETURN_STATUS(status) else {
        *buffer = cds_buffer_get_inner(self);
    }
    return status;
}

CDS_PUBLIC
cds_status_t cds_buffer_push_front(cds_buffer_t *buffer, cds_ptr_t src) {
    return cds_buffer_insert(buffer, 0, src);
}

/**
 * @brief Insert an item to the end of the buffer.
 * 
 * @param buffer The buffer which you want to insert the element into.
 * @param src A pointer pointing to the data to be inserted into the buffer.
 * 
 * @return cds_status_t The status code of this operation.
 */
CDS_PUBLIC
cds_status_t cds_buffer_push_back(cds_buffer_t *buffer, cds_ptr_t src) {
    CDS_IF_NULL_RETURN_ERROR(buffer);
    CDS_IF_NULL_RETURN_ERROR(src);
    cds_buffer_data_t *self;
    _VALIDATE_BUF(*buffer);
    CDS_IF_NULL_RETURN_ERROR(self);
    CDS_NEW_STATUS = _cds_buffer_insert(&self, self->header.length, src);
    CDS_IF_ERROR_RETURN_STATUS(status) else {
        *buffer = cds_buffer_get_inner(self);
    }
    return status;
}
