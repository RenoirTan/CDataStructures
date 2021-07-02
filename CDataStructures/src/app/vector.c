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
    
    for (int32_t i = 0; i < 100; i += 10) {
        if (CDS_IS_ERROR(cds_vector_push_back(vector, &i))) {
            printf("Could not add numbers.\n");
        }
    }

    for (size_t index = 0; index < 10; index++) {
        int32_t number = *(int32_t*) cds_vector_get(vector, index);
        printf("Number: %d\n", number);
    }

    printf("Success.\n");
    cds_vector_destroy(vector, NULL);
    getchar();
    return 0;

    errored:
    cds_vector_destroy(vector, NULL);
    getchar();
    return 1;
}
