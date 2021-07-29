#include <CDataStructures/alloc.h>

CDS_PUBLIC
size_t cds_required_space(
    size_t length, // 1961
    size_t type_size, // 4
    size_t constant_offset, // 24
    size_t block_mincapacity, // 125
    size_t block_increment // 19
) {
    size_t block_size = (length*type_size) + constant_offset; // 7844
    size_t block_minbytes = block_mincapacity * type_size; // 500
    size_t block_incrbytes = block_increment * type_size; // 76

    // 7872 = 500 + 76*97
    return block_size // 7844
        + amount_to_next_multiple(block_size - block_minbytes, block_incrbytes); // 28
}

CDS_PUBLIC
size_t cds_required_space_with_config(
    size_t length,
    size_t type_size,
    cds_alloc_config_t config
) {
    return cds_required_space(
        length,
        type_size,
        config.constant_offset,
        config.block_mincapacity,
        config.block_increment
    );
}
