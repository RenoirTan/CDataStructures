/**
 * @file CDataStructures.h
 * @author RenoirTan
 * @brief The top-level header file which includes all the headers in the
 * library.
 * @version 0.1
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021
 */

#ifndef CDATASTRUCTURES_H
#   define CDATASTRUCTURES_H

#   include "CDataStructures/_config.h"
#   ifdef CDS_USE_ALLOC_LIB
#       include "CDataStructures/alloc.h"
#   endif
#   include "CDataStructures/dynbuffer.h"
#   include "CDataStructures/functional.h"
#   include "CDataStructures/slist.h"
#   include "CDataStructures/stack.h"
#   include "CDataStructures/status.h"
#   include "CDataStructures/type.h"
#   include "CDataStructures/unarynode.h"
#   include "CDataStructures/utils.h"
#   include "CDataStructures/vector.h"

#endif