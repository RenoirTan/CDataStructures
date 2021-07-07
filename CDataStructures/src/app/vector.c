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
    
    for (int32_t i = 0xdead0000; i < 0xdead0020; i += 1) {
        if (CDS_IS_ERROR(cds_vector_push_back(vector, &i))) {
            printf("Could not add numbers.\n");
            goto errored;
        }
    }

    printf("Length of vector: %lu\n", vector->length);

    printf("Remove all even numbers.\n");

    {
        size_t index = 0;
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
    }

    printf("Length of vector: %lu\n", vector->length);
    printf("Memory allocated: %lu\n", vector->_bytes_allocated);

    for (size_t index = 0; index < vector->length; index++) {
        int32_t number = *(int32_t*) cds_vector_get(vector, index);
        printf("Number: %x\n", number);
    }

    printf("Success.\n");
    cds_vector_free(vector, NULL);
    printf("Press enter to continue > ");
    getchar();
    return 0;

    errored:
    cds_vector_free(vector, NULL);
    printf("Errored out. Press enter to continue > ");
    getchar();
    return 1;
}
