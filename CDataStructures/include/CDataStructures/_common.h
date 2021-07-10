/**
 * @file _common.h
 * @author RenoirTan
 * @brief Common macros used by this library.
 * @version 0.1
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _CDATASTRUCTURES_COMMON_H
#   define _CDATASTRUCTURES_COMMON_H

#   include "_prelude.h"

#   define CDATASTRUCTURES_MIN_CAPACITY 16
#   define CDATASTRUCTURES_BLOCK_SIZE 8

#   define bound(n, x, y) (max(min((n), (y)), (x)))
#   define amount_to_next_multiple(a, b) ((b) - ((a) % (b)))

#   define _CDS_SMASH_NAMES(a, b) cds_##a##_##b
#   define CDS_SMASH_PUBLIC(typename, suffix) _CDS_SMASH_NAMES(typename, suffix)
#   define _CDS_SMASH_ENDT(t) t##_t
#   define CDS_SMASH_ENDT(typename) _CDS_SMASH_ENDT(typename)

#endif