/**
 * @file slist.h
 * @author RenoirTan
 * @brief A header defining a singly-linked list.
 * @version 0.1
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CDATASTRUCTURES_SLIST_H
#   define CDATASTRUCTURES_SLIST_H

#   include "_prelude.h"
#   include "_common.h"
#   include "unarynode.h"


struct _cds_slist_t {
    cds_unary_node_t *head;
};

/**
 * @brief A structure representing a singly-linked list.
 */
typedef struct _cds_slist_t cds_slist_t;


/**
 * @brief Create a new singly-linked list on the heap.
 * 
 * @return cds_slist_t* The new singly-linked list. If memory cannot be
 * allocated, NULL is returned.
 */
cds_slist_t *cds_slist_new(void);

/**
 * @brief Initialise the singly-linked list with default data.
 * 
 * @param self The uninitialised singly-linked list.
 * @return cds_status_t The status code of this operation.
 */
cds_status_t cds_slist_init(cds_slist_t *self);

/**
 * @brief Get the length of the list. This traverses through all the nodes in
 * the chain and hence will take O(N) time where N is the number of nodes in
 * the list.
 * 
 * @param self The list.
 * @return size_t The number of nodes.
 */
size_t cds_slist_length(cds_slist_t *self);

/**
 * @brief Free all the data and the nodes within. This has the effect of
 * clearing the entirely list.
 * 
 * @param self The list.
 * @param clean_element The function used to free the data.
 * @return cds_status_t The status code of this operation.
 */
cds_status_t cds_slist_destroy(cds_slist_t *self, cds_free_f clean_element);

/**
 * @brief Free all the data in this list, including the list pointer itself.
 * 
 * @param self The list.
 * @param clean_element The function used to free the data.
 * @return cds_status_t The status code of this operation.
 */
cds_status_t cds_slist_free(cds_slist_t *self, cds_free_f clean_element);

/**
 * @brief Get the node at a certain index.
 * 
 * @param self The list.
 * @param index The index of the node.
 * @return cds_unary_node_t* The pointer to the node.
 */
cds_unary_node_t *cds_slist_get_node(cds_slist_t *self, size_t index);

/**
 * @brief Get the pointer to the data stored in the node at a certain index.
 * 
 * @param self The list.
 * @param index The index of the node.
 * @return cds_ptr_t The pointer to the data.
 */
cds_ptr_t cds_slist_get_data(cds_slist_t *self, size_t index);

/**
 * @brief Get the last node in the list.
 * 
 * @param self The list.
 * @return cds_unary_node_t* The last node.
 */
cds_unary_node_t *cds_slist_get_last_node(cds_slist_t *self);

/**
 * @brief Insert some data into the list at a certain index.
 * 
 * @param self The list.
 * @param index The index where the new data should be.
 * @param data The data to be stored in the list.
 * @return cds_status_t The status code of this operation.
 */
cds_status_t cds_slist_insert(
    cds_slist_t *self,
    size_t index,
    cds_ptr_t data
);

/**
 * @brief Add data to the front of the list.
 * 
 * @param self The list.
 * @param data The data to be prepended to the list.
 * @return cds_status_t The status code of this operation.
 */
cds_status_t cds_slist_push_front(cds_slist_t *self, cds_ptr_t data);

/**
 * @brief Add data to the end of the list. As this function has to travel all
 * the way to the end of the list, it will take considerable time on large
 * lists.
 * 
 * @param self The list.
 * @param data The data to be appended to the list.
 * @return cds_status_t The status code of this operation.
 */
cds_status_t cds_slist_push_back(cds_slist_t *self, cds_ptr_t data);

/**
 * @brief Remove the data at a certain index. The pointer to that data is
 * copied over to the parameter called `data` for you to deal with later. Hence,
 * this function can be understood as removing the responsibility over a
 * certain piece of data.
 * 
 * @param self The list.
 * @param index The index of the element to be removed.
 * @param data The pointer to a void pointer. The value here will be
 * overwritten with the pointer to the removed data.
 * @return cds_status_t The status code of this operation.
 */
cds_status_t cds_slist_remove(cds_slist_t *self, size_t index, cds_ptr_t *data);

/**
 * @brief Remove the data at the start of the list. The pointer to that data is
 * copied over to the parameter called `data` for you to deal with later. Hence,
 * this function can be understood as removing the responsibility over a
 * certain piece of data.
 * 
 * @param self The list.
 * @param data The pointer to a void pointer. The value here will be
 * overwritten with the pointer to the removed data.
 * @return cds_status_t The status code of this operation.
 */
cds_status_t cds_slist_pop_front(cds_slist_t *self, cds_ptr_t *data);

/**
 * @brief Remove the data at the end of the list. The pointer to that data is
 * copied over to the parameter called `data` for you to deal with later. Hence,
 * this function can be understood as removing the responsibility over a
 * certain piece of data.
 * 
 * @param self The list.
 * @param data The pointer to a void pointer. The value here will be
 * overwritten with the pointer to the removed data.
 * @return cds_status_t The status code of this operation.
 */
cds_status_t cds_slist_pop_back(cds_slist_t *self, cds_ptr_t *data);

#endif