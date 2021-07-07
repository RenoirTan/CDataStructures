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
    
    for (int32_t i = 0xdead0000; i < 0xdead0100; i += 1) {
        if (CDS_IS_ERROR(cds_vector_push_back(vector, &i))) {
            printf("Could not add numbers.\n");
        }
    }

    printf("Length of vector: %lu\n", vector->length);

    for (size_t index = 0; index < vector->length; index++) {
        int32_t number = *(int32_t*) cds_vector_get(vector, index);
        printf("Number: %x\n", number);
    }

    printf("Success.\n");
    cds_vector_destroy(vector, NULL);
    printf("Press enter to continue > ");
    getchar();
    return 0;

    errored:
    cds_vector_destroy(vector, NULL);
    printf("Errored out. Press enter to continue > ");
    getchar();
    return 1;
}
