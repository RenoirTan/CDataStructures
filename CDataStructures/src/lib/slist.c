#include <stdlib.h>
#include <CDataStructures/slist.h>


cds_slist_t *cds_slist_new(void) {
    return malloc(sizeof(cds_slist_t));
}
