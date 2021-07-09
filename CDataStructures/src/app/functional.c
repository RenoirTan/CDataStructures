#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <CDataStructures.h>


int main(int argc, char **argv) {
    printf("Test functional.\n");
    srand((uint32_t) time(NULL));
    uint32_t a = rand() % 1000, b = rand() % 1000;
    switch (cds_uint32_compare_absolute(a, b)) {
        case cds_greater:
            printf("%i is greater than %i\n", a, b);
            break;
        case cds_equal:
            printf("%i is equal to %i\n", a, b);
            break;
        case cds_lesser:
            printf("%i is lesser than %i\n", a, b);
            break;
        default:
            printf("Unknown cds_ordering_t variant");
            break;
    }
    return 0;
}
