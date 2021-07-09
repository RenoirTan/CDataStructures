#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CDataStructures/slist.h>


CDS_PRIVATE cds_unary_node_t *_cds_slist_get_node(
    cds_slist_t *self,
    size_t index
) {
    return cds_unary_node_get(self->head, index);
}

CDS_PRIVATE cds_status_t _cds_slist_push_front(
    cds_slist_t *self,
    cds_ptr_t data
) {
    cds_unary_node_t *new_node = cds_unary_node_new();
    CDS_IF_NULL_RETURN_ALLOC_ERROR(new_node);
    CDS_NEW_STATUS;
    CDS_IF_STATUS_ERROR((cds_unary_node_init(new_node))) {
        free(new_node);
        return status;
    }
    new_node->data = data;
    new_node->next = self->head;
    self->head = new_node;
    return status;
}

CDS_PRIVATE cds_status_t _cds_slist_push_back(
    cds_slist_t *self,
    cds_ptr_t data
) {
    cds_unary_node_t *end_node = cds_unary_node_get_end(self->head);
    cds_unary_node_t *new_node = cds_unary_node_new();
    CDS_IF_NULL_RETURN_ALLOC_ERROR(new_node);
    CDS_NEW_STATUS;
    CDS_IF_STATUS_ERROR((cds_unary_node_init(new_node))) {
        free(new_node);
        return status;
    }
    new_node->data = data;
    new_node->next = NULL;
    if (end_node == NULL) {
        self->head = new_node;
    } else {
        end_node->next = new_node;
    }
    return status;
}

CDS_PRIVATE cds_status_t _cds_slist_pop_front(
    cds_slist_t *self,
    cds_ptr_t *data
) {
    cds_unary_node_t *head = self->head;
    CDS_IF_NULL_RETURN_ERROR(head);
    cds_unary_node_t *next = head->next;
    if (data != NULL)
        *data = head->data;
    self->head = next;
    free(head);
    return cds_ok;
}

cds_slist_t *cds_slist_new(void) {
    return malloc(sizeof(cds_slist_t));
}

cds_status_t cds_slist_init(cds_slist_t *self) {
    CDS_IF_NULL_RETURN_ERROR(self);
    self->head = NULL;
    return cds_ok;
}

size_t cds_slist_length(cds_slist_t *self) {
    if (self == NULL)
        return 0;
    return cds_unary_node_length(self->head);
}

cds_status_t cds_slist_destroy(cds_slist_t *self, cds_free_f clean_element) {
    if (self == NULL)
        return cds_warning;
    cds_unary_node_t *last_head = self->head;
    self->head = NULL;
    return cds_unary_node_free_all(last_head, clean_element);
}

cds_status_t cds_slist_free(cds_slist_t *self, cds_free_f clean_element) {
    cds_status_t status = cds_slist_destroy(self, clean_element);
    free(self);
    return status;
}

cds_unary_node_t *cds_slist_get_node(cds_slist_t *self, size_t index) {
    if (self == NULL)
        return NULL;
    return _cds_slist_get_node(self, index);
}

cds_ptr_t cds_slist_get_data(cds_slist_t *self, size_t index) {
    cds_unary_node_t *node = cds_slist_get_node(self, index);
    return node == NULL ? NULL : node->data;
}

cds_unary_node_t *cds_slist_get_last_node(cds_slist_t *self) {
    if (self == NULL)
        return NULL;
    return cds_unary_node_get_end(self->head);
}

cds_status_t cds_slist_insert(
    cds_slist_t *self,
    size_t index,
    cds_ptr_t data
) {
    if (index == 0)
        return cds_slist_push_front(self, data);

    CDS_IF_NULL_RETURN_ERROR(self);
    CDS_NEW_STATUS;
    cds_unary_node_t *new_node;
    CDS_IF_NULL_RETURN_ALLOC_ERROR((new_node = cds_unary_node_new()));
    CDS_IF_STATUS_ERROR((cds_unary_node_init(new_node))) {
        free(new_node);
        return status;
    }
    new_node->data = data;
    cds_unary_node_t *before = _cds_slist_get_node(self, index - 1);
    if (before == NULL) {
        free(new_node);
        return cds_index_error;
    } else {
        return cds_unary_node_cut_queue(before, new_node);
    }
}

cds_status_t cds_slist_push_front(cds_slist_t *self, cds_ptr_t data) {
    CDS_IF_NULL_RETURN_ERROR(self);
    return _cds_slist_push_front(self, data);
}

cds_status_t cds_slist_push_back(cds_slist_t *self, cds_ptr_t data) {
    CDS_IF_NULL_RETURN_ERROR(self);
    return _cds_slist_push_back(self, data);
}

cds_status_t cds_slist_remove(
    cds_slist_t *self,
    size_t index,
    cds_ptr_t *data
) {
    if (index == 0)
        return cds_slist_pop_front(self, data);

    CDS_IF_NULL_RETURN_ERROR(self);
    cds_unary_node_t *before = _cds_slist_get_node(self, index - 1);
    if (before == NULL)
        return cds_index_error;
    else {
        cds_unary_node_t *node = cds_unary_node_remove_next(before);
        *data = node->data;
        free(node);
        return cds_ok;
    }
}

cds_status_t cds_slist_pop_front(cds_slist_t *self, cds_ptr_t *data) {
    CDS_IF_NULL_RETURN_ERROR(self);
    return _cds_slist_pop_front(self, data);
}

cds_status_t cds_slist_pop_back(cds_slist_t *self, cds_ptr_t *data) {
    CDS_IF_NULL_RETURN_ERROR(self);
    cds_unary_node_t *tortoise = self->head;
    if (tortoise == NULL) {
        return cds_zero_error;
    }
    cds_unary_node_t *hare = tortoise->next;
    if (hare == NULL) {
        return _cds_slist_pop_front(self, data);
    }
    while (hare->next != NULL) {
        tortoise = hare;
        hare = hare->next;
    }
    if (data != NULL)
        *data = hare->data;
    tortoise->next = NULL;
    free(hare);
    return cds_ok;
}
