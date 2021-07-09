add_library(${PROJECT_NAME}-unarynode-static STATIC unarynode.c)
add_library(${PROJECT_NAME}-unarynode-shared SHARED unarynode.c)

add_library(${PROJECT_NAME}-slist-static STATIC slist.c)
target_link_libraries(${PROJECT_NAME}-slist-static PUBLIC ${PROJECT_NAME}-unarynode-static)
add_library(${PROJECT_NAME}-slist-shared SHARED slist.c)
target_link_libraries(${PROJECT_NAME}-slist-shared PUBLIC ${PROJECT_NAME}-unarynode-shared)

add_library(${PROJECT_NAME}-vector-static STATIC vector.c)
add_library(${PROJECT_NAME}-vector-shared SHARED vector.c)