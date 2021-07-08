#ifndef CDATASTRUCTURES_SLIST_H
#   define CDATASTRUCTURES_SLIST_H

#   include "_prelude.h"
#   include "_common.h"


struct _cds_slist_node_t {
    cds_ptr_t data;
    struct _cds_slist_node_t *next;
};

typedef struct _cds_slist_node_t cds_slist_node_t;

cds_slist_node_t *cds_slist_node_new(void);

cds_status_t cds_slist_node_init(cds_slist_node_t *node);

cds_slist_node_t *cds_slist_node_get(cds_slist_node_t *node, size_t index);

size_t cds_slist_node_length(cds_slist_node_t *node);

cds_slist_node_t *cds_slist_node_get_end(cds_slist_node_t *node);

cds_status_t cds_slist_node_cut_queue(
    cds_slist_node_t *before,
    cds_slist_node_t *next
);

cds_slist_node_t *cds_slist_node_remove_next(cds_slist_node_t *node);

cds_slist_node_t *cds_slist_node_replace(
    cds_slist_node_t *ancestor,
    cds_slist_node_t *sibling
);

cds_status_t cds_slist_node_clean_once(
    cds_slist_node_t *node,
    cds_free_f clean_element
);

cds_status_t cds_slist_node_clean_all(
    cds_slist_node_t *node,
    cds_free_f clean_element
);

cds_status_t cds_slist_node_free_all(
    cds_slist_node_t *node,
    cds_free_f clean_element
);


struct _cds_slist_t {
    cds_slist_node_t *head;
};

typedef struct _cds_slist_t cds_slist_t;


cds_slist_t *cds_slist_new(void);

cds_status_t cds_slist_init(cds_slist_t *self);

size_t cds_slist_length(cds_slist_t *self);

cds_status_t cds_slist_destroy(cds_slist_t *self, cds_free_f clean_element);

cds_status_t cds_slist_free(cds_slist_t *self, cds_free_f clean_element);

cds_slist_node_t *cds_slist_get_node(cds_slist_t *self, size_t index);

cds_ptr_t cds_slist_get_data(cds_slist_t *self, size_t index);

cds_slist_node_t *cds_slist_get_last_node(cds_slist_t *self);

cds_status_t cds_slist_insert(
    cds_slist_t *self,
    size_t index,
    cds_ptr_t data
);

cds_status_t cds_slist_push_front(cds_slist_t *self, cds_ptr_t data);

cds_status_t cds_slist_push_back(cds_slist_t *self, cds_ptr_t data);

cds_status_t cds_slist_remove(cds_slist_t *self, size_t index, cds_ptr_t *data);

cds_status_t cds_slist_pop_front(cds_slist_t *self, cds_ptr_t *data);

cds_status_t cds_slist_pop_back(cds_slist_t *self, cds_ptr_t *data);

#endif