/**
 * @file unarynode.h
 * @author RenoirTan
 * @brief A header defining a unary node.
 * @version 0.1
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CDATASTRUCTURES_UNARYNODE_H
#   define CDATASTRUCTURES_UNARYNODE_H

#   include "_prelude.h"
#   include "_common.h"

struct _cds_unary_node_t {
    cds_ptr_t data;
    struct _cds_unary_node_t *next;
};

typedef struct _cds_unary_node_t cds_unary_node_t;

/**
 * @brief Create a node with at most 1 child. This node is uninitialised,
 * so you must pass this pointer to @see {@link cds_unary_node_init}.
 * 
 * @return cds_unary_node_t* The pointer to the node.
 */
cds_unary_node_t *cds_unary_node_new(void);

/**
 * @brief Initialise a unary node.
 * 
 * @param node The node to initialise.
 * @return cds_status_t This operation's status code.
 */
cds_status_t cds_unary_node_init(cds_unary_node_t *node);

/**
 * @brief Get the next <index>-th node after this one. If the successor node
 * at that index cannot be found, NULL is returned.
 * 
 * @param node The current node.
 * @param index The index of the node you want to get.
 * @return cds_unary_node_t* The pointer to the successor node.
 */
cds_unary_node_t *cds_unary_node_get(cds_unary_node_t *node, size_t index);

/**
 * @brief Get the number of nodes after this node including this node itself.
 * If `node` is NULL, 0 is returned.
 * 
 * @param node The node you want to start counting from.
 * @return size_t The length of the node chain.
 */
size_t cds_unary_node_length(cds_unary_node_t *node);

/**
 * @brief Get the final node in a chain of nodes. If the final node cannot be
 * found (because the current node is NULL), NULL is returned.
 * 
 * @param node The current node in the chain.
 * @return cds_unary_node_t* The final node in the chain.
 */
cds_unary_node_t *cds_unary_node_get_end(cds_unary_node_t *node);

/**
 * @brief Add a chain of nodes between a starting node and the node that used
 * to be right after the starting node. For example,
 * 
 *  Let x be a chain with nodes (a->b->c->d->e)
 *  and y be a chain with nodes (h->i->j)
 * 
 *  run `cds_unary_node_cut_queue` after node `c`.
 * 
 *  The result will be a->b->c->h->i->j->d->e
 * 
 * @param before The node where the node cuts the chain.
 * @param next The node which inserts itself into the chain.
 * @return cds_status_t 
 */
cds_status_t cds_unary_node_cut_queue(
    cds_unary_node_t *before,
    cds_unary_node_t *next
);

/**
 * @brief Remove the next node from the chain but reattach the nodes after that
 * node to this node. This has the same effect as removing one element in
 * an array.
 * 
 * @param node The node chain.
 * @return cds_unary_node_t* The node in the chain that has been removed.
 * Note that this node has not has its memory reclaimed yet, so you must free
 * the data in the node as well as the node itself using some form of the
 * function `free`.
 */
cds_unary_node_t *cds_unary_node_remove_next(cds_unary_node_t *node);

/**
 * @brief Replace the node chain after this node with another node chain, then
 * return the old node chain. The new chain is called `sibling` in this
 * function.
 * 
 * @param ancestor The starting node in the chain.
 * @param sibling The new node chain.
 * @return cds_unary_node_t* The old node chain.
 */
cds_unary_node_t *cds_unary_node_replace(
    cds_unary_node_t *ancestor,
    cds_unary_node_t *sibling
);

/**
 * @brief Free the memory pointed to by the `data` pointer.
 * 
 * @param node The current node.
 * @param clean_element The function used to free the data.
 * @return cds_status_t The status code of this operation.
 */
cds_status_t cds_unary_node_clean_once(
    cds_unary_node_t *node,
    cds_free_f clean_element
);

/**
 * @brief Clean all the data pointers in all the nodes in the current chain.
 * 
 * @param node The starting node in the chain.
 * @param clean_element The function used to free the data.
 * @return cds_status_t The status code of this operation.
 */
cds_status_t cds_unary_node_clean_all(
    cds_unary_node_t *node,
    cds_free_f clean_element
);

/**
 * @brief Free all the nodes and data in the current chain.
 * 
 * @param node The current node.
 * @param clean_element The function used to free the data.
 * @return cds_status_t The status code of this operation.
 */
cds_status_t cds_unary_node_free_all(
    cds_unary_node_t *node,
    cds_free_f clean_element
);

#endif