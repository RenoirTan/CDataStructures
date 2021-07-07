#ifndef CDATASTRUCTURES_SLIST_H
#   define CDATASTRUCTURES_SLIST_H

#   include "_prelude.h"
#   include "_common.h"


struct _cds_slist_node_t {
    cds_ptr_t data;
    struct _cds_slist_node_t *next;
};

typedef struct _cds_slist_node_t cds_slist_node_t;

cds_slist_node_t *cds_slist_node_get(cds_slist_node_t *node, size_t index);

cds_status_t cds_slist_node_cut_queue(
    cds_slist_node_t *before,
    cds_slist_node_t *next
);

cds_slist_node_t *cds_slist_node_remove_next(cds_slist_node_t *node);

cds_slist_node_t *cds_slist_node_replace(
    cds_slist_node_t *ancestor,
    cds_slist_node_t *sibling
);


struct _cds_slist_t {
    struct _cds_slist_node_t *head;
};

typedef struct _cds_slist_t cds_slist_t;


cds_slist_t *cds_slist_new(void);

cds_status_t cds_slist_init(cds_slist_t *self);

cds_slist_node_t *cds_slist_get_node(cds_slist_t *self, size_t index);

cds_ptr_t cds_slist_get_data(cds_slist_t *self, size_t index);

#endif