/**
 * @file status.h
 * @author RenoirTan
 * @brief A header file which provides enumerators and macros for error
 * handling using status codes.
 * @version 0.1
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CDATASTRUCTURES_STATUS_H
#   define CDATASTRUCTURES_STATUS_H

enum _cds_status_t {
    /**
     * @brief For indexing errors, such as requesting the 10th element of an
     * array with only 5 elements.
     */
    cds_index_error = 5,
    /**
     * @brief If a value or parameter is 0.
     */
    cds_zero_error = 4,
    /**
     * @brief If memory allocation could not be made.
     */
    cds_alloc_error = 3,
    /**
     * @brief If a null pointer was passed as an argument or received from
     * somewhere else.
     */
    cds_null_error = 2,
    /**
     * @brief A general error status code.
     */
    cds_error = 1,
    /**
     * @brief If the function was successful.
     */
    cds_ok = 0,
    /**
     * @brief For warnings.
     */
    cds_warning = -1,
};

/**
 * @brief An enumerator of status codes a function can return to tell the
 * caller whether the function was successful or if an error occurred.
 * 
 * The status codes in this enumerator are categorised into 3 types:
 * 1. OK
 * 2. Errors
 * 3. Warning
 * 
 * `OK` has one status code, that is `cds_ok` (0). If you want to check if a
 * function was successful, you check if the status code is `cds_ok` or 0.
 * 
 * As of writing, the are 5 error codes, with `cds_error` being the most
 * general status code used as a catch-all for any error that can occur.
 * You can see what each error code means by reading the documentation for each
 * enum variant. If you want to test for an error, check if the status code
 * is greater than 0.
 * 
 * If a warning code is emitted, it means the function was successful, but the
 * input or state had bad data or errors which the function had to find a
 * workaround for, sometimes not performing the action the function was
 * supposed to do. To check for warning codes, check if the status code is
 * negative.
 */
typedef enum _cds_status_t cds_status_t;

/**
 * @brief Create a new variable or parameter called status of type
 * `cds_status_t`.
 */
#   define CDS_NEW_STATUS cds_status_t status

/**
 * @brief The condition part of an if statement checking if an expression
 * returned an error code.
 */
#   define CDS_IF_STATUS_ERROR(expression) if ((status = (expression)) > 0)

/**
 * @brief Return the status if the expression being checked returns an error.
 */
#   define CDS_IF_ERROR_RETURN_STATUS(expression) \
    CDS_IF_STATUS_ERROR(expression) return status;

/**
 * @brief Return a null pointer if the expression being checked has errored
 * out.
 */
#   define CDS_IF_ERROR_RETURN_NULL(expression) \
    CDS_IF_STATUS_ERROR(expression) return NULL;

/**
 * @brief A macro which returns whether an expression returned an error
 * code.
 */
#   define CDS_IS_ERROR(status) ((status) > 0)

/**
 * @brief If the pointer is null, return `cds_null_error`.
 */
#   define CDS_IF_NULL_RETURN_ERROR(pointer) \
    if ((pointer) == NULL) \
        return cds_null_error;

/**
 * @brief If the pointer is null, return `cds_alloc_error`.
 * 
 */
#   define CDS_IF_NULL_RETURN_ALLOC_ERROR(pointer) \
    if ((pointer) == NULL) \
        return cds_alloc_error;

/**
 * @brief If the expression returns 0, return `cds_zero_error`.
 */
#   define CDS_IF_ZERO_RETURN_ERROR(value) \
    if ((value) == 0) \
        return cds_zero_error;

#endif