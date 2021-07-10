/**
 * @file stack.h
 * @author RenoirTan
 * @brief A header file defining a stack structure and functions associated
 * with it.
 * @version 0.1
 * @date 2021-07-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef CDATASTRUCTURES_STACK_H
#   define CDATASTRUCTURES_STACK_H

#   include "slist.h"

struct _cds_stack_t {
    cds_slist_t *slist;
};

/**
 * @brief A structure representing a LIFO stack. This means that the if an
 * element is pushed onto the stack last, it will be the first element to be
 * taken out when cds_stack_pop is called.
 */
typedef struct _cds_stack_t cds_stack_t;

/**
 * @brief Create a new stack on the heap and return the pointer to it.
 * 
 * @return cds_stack_t*
 */
CDS_PUBLIC
cds_stack_t *cds_stack_new(void);

/**
 * @brief Initialise the stack immediately after calling cds_stack_new.
 * 
 * @param self The uninitialised stack object.
 * @return cds_status_t
 */
CDS_PUBLIC
cds_status_t cds_stack_init(cds_stack_t *self);

/**
 * @brief Create a new stack from a singly-linked list.
 * 
 * @param slist The list from which the stack will be created. This list can
 * have data already in it.
 * @return cds_stack_t 
 */
CDS_PUBLIC
cds_stack_t cds_stack_from_slist(cds_slist_t *slist);

/**
 * @brief Check if the stack is empty.
 * 
 * @param self The stack object.
 * @return bool
 */
CDS_PUBLIC
bool cds_stack_is_empty(cds_stack_t *self);

/**
 * @brief Clear the contents in the stack using a "free" function.
 * 
 * @param self The stack object.
 * @param clean_element The function that can free the memory occupied by the
 * pointers to each element.
 * @return cds_status_t
 */
CDS_PUBLIC
cds_status_t cds_stack_destroy(cds_stack_t *self, cds_free_f clean_element);

/**
 * @brief Clear the stack as well as freeing the stack object itself.
 * 
 * @param self The stack object.
 * @param clean_element The function that can free the memory occupied by the
 * pointers to each element.
 * @return cds_status_t 
 */
CDS_PUBLIC
cds_status_t cds_stack_free(cds_stack_t *self, cds_free_f clean_element);

/**
 * @brief Peek at the data pointer at the top of the stack. This function
 * returns NULL if there are no elements.
 * 
 * @param self 
 * @return cds_ptr_t 
 */
CDS_PUBLIC
cds_ptr_t cds_stack_top(cds_stack_t *self);

/**
 * @brief Push some data onto the stack. This is stored as a pointer to the
 * data.
 * 
 * @param self The stack object.
 * @param data The pointer to the data you want to store.
 * @return cds_status_t 
 */
CDS_PUBLIC
cds_status_t cds_stack_push(cds_stack_t *self, cds_ptr_t data);

/**
 * @brief Pop some data off the stack. The pointer to the data which is no
 * longer on the stack is passed onto the parameter called "data". If there
 * are no elements on the stack, the pointer location referenced by "data" does
 * not change. If the "data" parameter is NULL, it is not changed to avoid
 * dereferencing errors.
 * 
 * Once this function is called, you have to manage the memory occupied by the
 * object that "data" is pointing at.
 * 
 * @param self 
 * @param data 
 * @return cds_status_t 
 */
CDS_PUBLIC
cds_status_t cds_stack_pop(cds_stack_t *self, cds_ptr_t *data);

#endif