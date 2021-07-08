#ifndef CDATASTRUCTURES_SLIST_H
#   define CDATASTRUCTURES_SLIST_H

#   include "_prelude.h"
#   include "_common.h"


struct _cds_slist_node_t {
    cds_ptr_t data;
    struct _cds_slist_node_t *next;
};

/**
 * @brief A structure representing a node in a singly-linked list. 
 */
typedef struct _cds_slist_node_t cds_slist_node_t;

/**
 * @brief Create a new singly-linked list node. This node is uninitialised,
 * so you must pass this pointer to @see {@link cds_slist_node_init}.
 * 
 * @return cds_slist_node_t* The pointer to the node.
 */
cds_slist_node_t *cds_slist_node_new(void);

/**
 * @brief Initialise a node in a singly-linked node.
 * 
 * @param node The node to initialise.
 * @return cds_status_t This operation's status code.
 */
cds_status_t cds_slist_node_init(cds_slist_node_t *node);

/**
 * @brief Get the next <index>-th node after this one. If the successor node
 * at that index cannot be found, NULL is returned.
 * 
 * @param node The current node.
 * @param index The index of the node you want to get.
 * @return cds_slist_node_t* The pointer to the successor node.
 */
cds_slist_node_t *cds_slist_node_get(cds_slist_node_t *node, size_t index);

/**
 * @brief Get the number of nodes after this node including this node itself.
 * If `node` is NULL, 0 is returned.
 * 
 * @param node The node you want to start counting from.
 * @return size_t The length of the node chain.
 */
size_t cds_slist_node_length(cds_slist_node_t *node);

/**
 * @brief Get the final node in a chain of nodes. If the final node cannot be
 * found (because the current node is NULL), NULL is returned.
 * 
 * @param node The current node in the chain.
 * @return cds_slist_node_t* The final node in the chain.
 */
cds_slist_node_t *cds_slist_node_get_end(cds_slist_node_t *node);

/**
 * @brief Add a chain of nodes between a starting node and the node that used
 * to be right after the starting node. For example,
 * 
 *  Let x be a chain with nodes (a->b->c->d->e)
 *  and y be a chain with nodes (h->i->j)
 * 
 *  run `cds_slist_node_cut_queue` after node `c`.
 * 
 *  The result will be a->b->c->h->i->j->d->e
 * 
 * @param before The node where the node cuts the chain.
 * @param next The node which inserts itself into the chain.
 * @return cds_status_t 
 */
cds_status_t cds_slist_node_cut_queue(
    cds_slist_node_t *before,
    cds_slist_node_t *next
);

/**
 * @brief Remove the next node from the chain but reattach the nodes after that
 * node to this node. This has the same effect as removing one element in
 * an array.
 * 
 * @param node The node chain.
 * @return cds_slist_node_t* The node in the chain that has been removed.
 * Note that this node has not has its memory reclaimed yet, so you must free
 * the data in the node as well as the node itself using some form of the
 * function `free`.
 */
cds_slist_node_t *cds_slist_node_remove_next(cds_slist_node_t *node);

/**
 * @brief Replace the node chain after this node with another node chain, then
 * return the old node chain. The new chain is called `sibling` in this
 * function.
 * 
 * @param ancestor The starting node in the chain.
 * @param sibling The new node chain.
 * @return cds_slist_node_t* The old node chain.
 */
cds_slist_node_t *cds_slist_node_replace(
    cds_slist_node_t *ancestor,
    cds_slist_node_t *sibling
);

/**
 * @brief Free the memory pointed to by the `data` pointer.
 * 
 * @param node The current node.
 * @param clean_element The function used to free the data.
 * @return cds_status_t The status code of this operation.
 */
cds_status_t cds_slist_node_clean_once(
    cds_slist_node_t *node,
    cds_free_f clean_element
);

/**
 * @brief Clean all the data pointers in all the nodes in the current chain.
 * 
 * @param node The starting node in the chain.
 * @param clean_element The function used to free the data.
 * @return cds_status_t The status code of this operation.
 */
cds_status_t cds_slist_node_clean_all(
    cds_slist_node_t *node,
    cds_free_f clean_element
);

/**
 * @brief Free all the nodes and data in the current chain.
 * 
 * @param node The current node.
 * @param clean_element The function used to free the data.
 * @return cds_status_t The status code of this operation.
 */
cds_status_t cds_slist_node_free_all(
    cds_slist_node_t *node,
    cds_free_f clean_element
);


struct _cds_slist_t {
    cds_slist_node_t *head;
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
 * @return cds_slist_node_t* The pointer to the node.
 */
cds_slist_node_t *cds_slist_get_node(cds_slist_t *self, size_t index);

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
 * @return cds_slist_node_t* The last node.
 */
cds_slist_node_t *cds_slist_get_last_node(cds_slist_t *self);

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