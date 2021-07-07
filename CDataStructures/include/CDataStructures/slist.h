#ifndef CDATASTRUCTURES_SLIST_H
#   define CDATASTRUCTURES_SLIST_H

#   include "_prelude.h"
#   include "_common.h"


struct _cds_slist_node_t {
    cds_ptr_t data;
    struct _cds_slist_node_t *next;
};


struct _cds_slist_t {
    struct _cds_slist_node_t *head;
};

typedef struct _cds_slist_t cds_slist_t;


cds_slist_t *cds_slist_new(void);

#endif