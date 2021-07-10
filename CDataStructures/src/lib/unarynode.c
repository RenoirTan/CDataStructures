#include <stdlib.h>
#include <string.h>
#include <CDataStructures/unarynode.h>

CDS_PRIVATE 
cds_status_t _cds_unary_node_cut_queue(
    cds_unary_node_t *before,
    cds_unary_node_t *next
) {
    cds_unary_node_t *after = before->next;
    before->next;
    cds_unary_node_get_end(next)->next = after;
    return cds_ok;
}

CDS_PRIVATE 
cds_unary_node_t *_cds_unary_node_remove_next(
    cds_unary_node_t *node
) {
    cds_unary_node_t *next = node->next;
    cds_unary_node_t *after = next == NULL ? NULL : next->next;
    node->next = after;
    return next;
}

CDS_PRIVATE 
cds_unary_node_t *_cds_unary_node_replace(
    cds_unary_node_t *ancestor,
    cds_unary_node_t *sibling
) {
    cds_unary_node_t *child = ancestor->next;
    ancestor->next = sibling;
    return child;
}

CDS_PRIVATE 
cds_status_t _cds_unary_node_clean_once(
    cds_unary_node_t *node,
    cds_free_f clean_element
) {
    if (node->data != NULL) {
        if (clean_element != NULL)
            clean_element(node->data);
        node->data = NULL;
    }
    return cds_ok;
}

CDS_PUBLIC
cds_unary_node_t *cds_unary_node_new(void) {
    return malloc(sizeof(cds_unary_node_t));
}

CDS_PUBLIC
cds_status_t cds_unary_node_init(cds_unary_node_t *node) {
    CDS_IF_NULL_RETURN_ERROR(node);
    node->data = NULL;
    node->next = NULL;
    return cds_ok;
}

CDS_PUBLIC
cds_unary_node_t *cds_unary_node_get(cds_unary_node_t *node, size_t index) {
    size_t passed = 0;
    while (passed < index && node != NULL) {
        node = node->next;
        ++passed;
    }
    return node;
}

CDS_PUBLIC
size_t cds_unary_node_length(cds_unary_node_t *node) {
    if (node == NULL)
        return 0;
    size_t length = 0;
    while (node != NULL) {
        node = node->next;
        ++length;
    }
    return length;
}

CDS_PUBLIC
cds_unary_node_t *cds_unary_node_get_end(cds_unary_node_t *node) {
    if (node == NULL)
        return NULL;
    while (node->next != NULL) {
        node = node->next;
    }
    return node;
}

CDS_PUBLIC
cds_status_t cds_unary_node_cut_queue(
    cds_unary_node_t *before,
    cds_unary_node_t *next
) {
    CDS_IF_NULL_RETURN_ERROR(before);
    CDS_IF_NULL_RETURN_ERROR(next);
    return _cds_unary_node_cut_queue(before, next);
}

CDS_PUBLIC
cds_unary_node_t *cds_unary_node_remove_next(cds_unary_node_t *node) {
    if (node == NULL)
        return NULL;
    else
        return _cds_unary_node_remove_next(node);
}

CDS_PUBLIC
cds_unary_node_t *cds_unary_node_replace(
    cds_unary_node_t *ancestor,
    cds_unary_node_t *sibling
) {
    if (ancestor == NULL)
        return NULL;
    else
        return _cds_unary_node_replace(ancestor, sibling);
}

CDS_PUBLIC
cds_status_t cds_unary_node_clean_once(
    cds_unary_node_t *node,
    cds_free_f clean_element
) {
    CDS_IF_NULL_RETURN_ERROR(node);
    return _cds_unary_node_clean_once(node, clean_element);
}

CDS_PUBLIC
cds_status_t cds_unary_node_clean_all(
    cds_unary_node_t *node,
    cds_free_f clean_element
) {
    CDS_NEW_STATUS;
    while (node != NULL) {
        status = _cds_unary_node_clean_once(node, clean_element);
        node = node->next;
    }
    return status;
}

CDS_PUBLIC
cds_status_t cds_unary_node_free_all(
    cds_unary_node_t *node,
    cds_free_f clean_element
) {
    CDS_NEW_STATUS = cds_ok;
    while (node != NULL) {
        cds_unary_node_t *next = node->next;
        status = _cds_unary_node_clean_once(node, clean_element);
        free(node);
        node = next;
    }
    return status;
}