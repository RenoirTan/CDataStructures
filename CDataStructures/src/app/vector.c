#include <stdio.h>
#include <CDataStructures.h>

int main(int argc, char **argv) {
    printf("Test vector.\n");
    cds_vector_t *vector = cds_vector_new();
    if (vector == NULL) {
        printf("Could not allocate memory for vector.\n");
    }
    if (CDS_IS_ERROR(cds_vector_init(vector, sizeof(int32_t)))) {
        printf("Could not initalise vector.\n");
        goto errored;
    }

    printf("Vector allocated!\n");
    
    int32_t i = 0xdead0000;
    size_t index = 0;
    for (; i < 0xdead0020; i += 1) {
        if (CDS_IS_ERROR(cds_vector_push_back(vector, &i))) {
            printf("Could not add numbers.\n");
            goto errored;
        }
    }

    printf("Length of vector: %zu\n", vector->length);

    printf("Remove all even numbers.\n");

    index = 0;
    while (index < vector->length) {
        int32_t *ptr = cds_vector_get(vector, index);
        if (!(*ptr % 2)) {
            if (CDS_IS_ERROR(cds_vector_remove(vector, index, ptr))) {
                printf("Could not remove numbers.\n");
                goto errored;
            }
        }
        ++index;
    }

    printf("Length of vector: %zu\n", vector->length);
    printf("Memory allocated: %zu\n", vector->_bytes_allocated);

    for (index = 0; index < vector->length; index++) {
        int32_t number = *(int32_t*) cds_vector_get(vector, index);
        printf("Number: %x\n", number);
    }

    printf("Success.\n");
    cds_vector_free(vector, NULL);
    return 0;

    errored:
    printf("Errored out.\n");
    cds_vector_free(vector, NULL);
    return 1;
}
