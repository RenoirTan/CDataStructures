#include <stdlib.h>
#include <CDataStructures/slist.h>


static cds_slist_node_t *_cds_slist_get_node(cds_slist_t *self, size_t index) {
    return cds_slist_node_get(self->head, index);
}

static cds_status_t _cds_slist_node_cut_queue(
    cds_slist_node_t *before,
    cds_slist_node_t *next
) {
    cds_slist_node_t *after = before->next;
    before->next;
    next->next = after;
    return cds_ok;
}

static cds_slist_node_t *_cds_slist_node_remove_next(cds_slist_node_t *node) {
    cds_slist_node_t *next = node->next;
    cds_slist_node_t *after = next == NULL ? NULL : next->next;
    node->next = after;
    return next;
}

static cds_slist_node_t *_cds_slist_node_replace(
    cds_slist_node_t *ancestor,
    cds_slist_node_t *sibling
) {
    cds_slist_node_t *child = ancestor->next;
    ancestor->next = sibling;
    return child;
}

static cds_status_t *_cds_slist_node_clean_once(
    cds_slist_node_t *node,
    cds_free_f clean_element
) {
    if (node->data != NULL) {
        clean_element(node->data);
        node->data = NULL;
    }
    return cds_ok;
}

cds_slist_node_t *cds_slist_node_get(cds_slist_node_t *node, size_t index) {
    size_t passed = 0;
    while (passed < index && node != NULL) {
        node = node->next;
        ++passed;
    }
    return node;
}

cds_status_t cds_slist_node_cut_queue(
    cds_slist_node_t *before,
    cds_slist_node_t *next
) {
    CDS_IF_NULL_RETURN_ERROR(before);
    CDS_IF_NULL_RETURN_ERROR(next);
    return _cds_slist_node_cut_queue(before, next);
}

cds_slist_node_t *cds_slist_node_remove_next(cds_slist_node_t *node) {
    if (node == NULL)
        return NULL;
    else
        return _cds_slist_node_remove_next(node);
}

cds_slist_node_t *cds_slist_node_replace(
    cds_slist_node_t *ancestor,
    cds_slist_node_t *sibling
) {
    if (ancestor == NULL)
        return NULL;
    else
        return _cds_slist_node_replace(ancestor, sibling);
}

cds_status_t cds_slist_node_clean_once(
    cds_slist_node_t *node,
    cds_free_f clean_element
) {
    CDS_IF_NULL_RETURN_ERROR(node);
    return _cds_slist_node_clean_once(node, clean_element);
}

cds_status_t cds_slist_node_clean_all(
    cds_slist_node_t *node,
    cds_free_f clean_element
) {
    CDS_NEW_STATUS;
    while (node != NULL) {
        status = _cds_slist_node_clean_once(node, clean_element);
        node = node->next;
    }
    return status;
}

cds_slist_t *cds_slist_new(void) {
    return malloc(sizeof(cds_slist_t));
}

cds_status_t cds_slist_init(cds_slist_t *self) {
    CDS_IF_NULL_RETURN_ERROR(self);
    self->head = NULL;
    return cds_ok;
}

cds_status_t cds_slist_destroy(cds_slist_t *self, cds_free_f clean_element) {
    if (self == NULL)
        return cds_warning;
    return cds_slist_node_clean_all(self->head, clean_element);
}

cds_status_t cds_slist_free(cds_slist_t *self, cds_free_f clean_element) {
    cds_status_t status = cds_slist_destroy(self, clean_element);
    free(self);
    return status;
}

cds_slist_node_t *cds_slist_get_node(cds_slist_t *self, size_t index) {
    if (self == NULL)
        return NULL;
    return _cds_slist_get_node(self, index);
}

cds_ptr_t cds_slist_get_data(cds_slist_t *self, size_t index) {
    cds_slist_node_t *node = cds_slist_get_node(self, index);
    return node == NULL ? NULL : node->data;
}
