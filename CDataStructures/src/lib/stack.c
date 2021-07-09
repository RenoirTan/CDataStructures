#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <CDataStructures/stack.h>
#include <CDataStructures/utils.h>


cds_stack_t *cds_stack_new(void) {
    return CDS_NEW(cds_stack_t);
}

cds_status_t cds_stack_init(cds_stack_t *self) {
    CDS_IF_NULL_RETURN_ERROR(self);
    cds_slist_t *slist = cds_slist_new();
    if (slist == NULL)
        return cds_alloc_error;
    if (CDS_IS_ERROR(cds_slist_init(slist))) {
        free(slist);
        return cds_alloc_error;
    }
    self->slist = slist;
    return cds_ok;
}

cds_stack_t cds_stack_from_slist(cds_slist_t *slist) {
    cds_stack_t stack = {
        .slist = slist
    };
    return stack;
}

bool cds_stack_is_empty(cds_stack_t *self) {
    return (self == NULL || self->slist == NULL || self->slist->head == NULL);
}

cds_status_t cds_stack_destroy(cds_stack_t *self, cds_free_f clean_element) {
    CDS_IF_NULL_RETURN_ERROR(self);
    return cds_slist_destroy(self->slist, clean_element);
}

cds_status_t cds_stack_free(cds_stack_t *self, cds_free_f clean_element) {
    CDS_NEW_STATUS;
    CDS_IF_ERROR_RETURN_STATUS((cds_stack_destroy(self, clean_element)));
    free(self);
    return cds_ok;
}

cds_ptr_t cds_stack_top(cds_stack_t *self) {
    if (self == NULL || self->slist == NULL)
        return NULL;
    return self->slist->head;
}

cds_status_t cds_stack_push(cds_stack_t *self, cds_ptr_t data) {
    if (self == NULL || self->slist == NULL)
        return cds_null_error;
    return cds_slist_push_front(self->slist, data);
}

cds_status_t cds_stack_pop(cds_stack_t *self, cds_ptr_t *data) {
    if (self == NULL || self->slist == NULL)
        return cds_null_error;
    return cds_slist_pop_front(self->slist, data);
}
