#ifndef CDATASTRUCTURES_STACK_H
#   define CDATASTRUCTURES_STACK_H

#   include "slist.h"

struct _cds_stack_t {
    cds_slist_t *slist;
};

typedef struct _cds_stack_t cds_stack_t;

cds_stack_t *cds_stack_new(void);

cds_status_t cds_stack_init(cds_stack_t *self);

cds_stack_t cds_stack_from_slist(cds_slist_t *slist);

bool cds_stack_is_empty(cds_stack_t *self);

cds_status_t cds_stack_destroy(cds_stack_t *self, cds_free_f clean_element);

cds_status_t cds_stack_free(cds_stack_t *self, cds_free_f clean_element);

cds_ptr_t cds_stack_top(cds_stack_t *self);

cds_status_t cds_stack_push(cds_stack_t *self, cds_ptr_t data);

cds_status_t cds_stack_pop(cds_stack_t *self, cds_ptr_t *data);

#endif