/**
 * @file _prelude.h
 * @author RenoirTan
 * @brief Definitions and header files that all header files in this library
 * also include.
 * @version 0.1
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _CDATASTRUCTURES_PRELUDE_H
#   define _CDATASTRUCTURES_PRELUDE_H

#   include "status.h"
#   include "type.h"

/**
 * @brief A macro designating a function definition as inline.
 */
#   define CDS_INLINE static inline

/**
 * @brief A macro designating a function definition as private (i.e. static).
 * 
 */
#   define CDS_PRIVATE static

/**
 * @brief A macro designating a function definition as part of the public
 * API.
 */
#   define CDS_PUBLIC

#endif