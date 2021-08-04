#define CDS_USE_ALLOC_LIB
#include <CDataStructures.h>
#include <stdio.h>

#define _DEBUG_FMTSTR \
    "Amount of memory required to store %zu objects of a " \
    "certain type whose size is %zu, is: %zu bytes\n"

#define _DEBUG_RESULT(length, type_size, recommended) \
    printf(_DEBUG_FMTSTR, length, type_size, recommended)

int test_alloc_1(int argc, char **argv) {
    cds_alloc_config_t config_1 = {
        .constant_offset = 24,
        .block_mincapacity = 16,
        .block_increment = 8};
    cds_alloc_config_debug(config_1, stdout);
    printf("\n");
    size_t length_1 = 16;
    size_t type_1 = sizeof(FILE);
    size_t recommended_1 = cds_required_space_with_config(
        length_1,
        type_1,
        config_1);
    _DEBUG_RESULT(length_1, type_1, recommended_1);
    return 0;
}

int test_alloc_2(int argc, char **argv) {
    cds_alloc_config_t config_2 = {
        .constant_offset = 24,
        .block_mincapacity = 125,
        .block_increment = 19
    };
    cds_alloc_config_debug(config_2, stdout);
    printf("\n");
    size_t length_2 = 1961;
    size_t type_2 = sizeof(int32_t);
    size_t recommended_2 = cds_required_space_with_config(
        length_2,
        type_2,
        config_2);
    _DEBUG_RESULT(length_2, type_2, recommended_2);
    return 0;
}

int main(int argc, char **argv) {
    printf("Testing alloc.\n");

    test_alloc_1(argc, argv);
    test_alloc_2(argc, argv);

    return 0;
}
