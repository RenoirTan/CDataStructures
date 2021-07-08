#include <stdio.h>
#include <stdlib.h>
#include <CDataStructures.h>


int main(int argc, char **argv) {
    printf("Testing SList.\n");
    cds_slist_t *slist = cds_slist_new();
    if (slist == NULL) {
        printf("Could not allocate memory for SList.\n");
    }
    if (CDS_IS_ERROR(cds_slist_init(slist))) {
        printf("Could not initialise slist.\n");
    }

    size_t index = 0;
    int32_t *location = NULL;

    for (index = 0; index <= 20; ++index) {
        location = malloc(sizeof(int32_t));
        if (location == NULL) {
            goto errored;
        }
        if (index == 20) {
            *location = 1337;
            if (CDS_IS_ERROR(cds_slist_push_back(slist, location))) {
                printf("Could not add item.\n");
                goto errored;
            }
        } else {
            *location = (int32_t)index;
            if (CDS_IS_ERROR(cds_slist_push_front(slist, location))) {
                printf("Could not add item.\n");
                goto errored;
            }
        }
    }

    printf("Length of SList: %zu\n", cds_slist_length(slist));

    cds_slist_node_t *node;
    for (node = slist->head; node != NULL; node = node->next) {
        printf("---------------------------\n");
        printf("Location of node: %p\n", node);
        printf("Location of data: %p\n", node->data);
        printf("Data: %i\n", *((int32_t*) node->data));
    }

    printf("Success.\n");
    cds_slist_free(slist, free);
    return 0;

    errored:
    cds_slist_free(slist, free);
    printf("Errored out.\n");
    return 1;
}
