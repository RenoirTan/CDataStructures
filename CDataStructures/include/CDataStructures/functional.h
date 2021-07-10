/**
 * @file functional.h
 * @author RenoirTan
 * @brief A header defining common functions for functional programming.
 * This includes comparison functions for the most common types.
 * 
 * To avoid having to write too much boilerplate code, the functions for
 * each data type are generated using macros.
 * 
 * "TS" is a macro which applies each function generator macro onto each of the
 * data types. These function generator macros include "F1" and "F2" which
 * expands to functions involving the types found in "TS".
 * @version 0.1
 * @date 2021-07-10
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CDATASTRUCTURES_FUNCTIONAL_H
#   define CDATASTRUCTURES_FUNCTIONAL_H

#   include "_common.h"
#   include "type.h"

#   define TS(applier) \
    applier(int8, int8_t) \
    applier(int16, int16_t) \
    applier(int32, int32_t) \
    applier(int64, int64_t) \
    applier(uint8, uint8_t) \
    applier(uint16, uint16_t) \
    applier(uint32, uint32_t) \
    applier(uint64, uint64_t) \
    applier(char, char) \
    applier(size, size_t) \
    applier(wchar, wchar_t) \
    applier(byte, cds_byte_t) \
    applier(pointer, cds_ptr_t)

#   define F1(stn, ltn)        \
    CDS_PRIVATE cds_ordering_t \
    CDS_SMASH_PUBLIC(stn, compare_pointers) \
    (ltn *a, ltn *b) { \
        if (*a > *b) return cds_greater; \
        else if (*a < *b) return cds_lesser; \
        else return cds_equal; \
    }

TS(F1)

#   undef F1
#   define F2(stn, ltn) \
    CDS_PRIVATE cds_ordering_t \
    CDS_SMASH_PUBLIC(stn, compare_absolute) \
    (ltn a, ltn b) { \
        if (a > b) return cds_greater; \
        else if (a < b) return cds_lesser; \
        else return cds_equal; \
    }

TS(F2)

#   undef F2
#   undef TS

#endif