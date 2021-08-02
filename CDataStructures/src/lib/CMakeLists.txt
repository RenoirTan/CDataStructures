add_library(${PROJECT_NAME}-alloc-static STATIC alloc.c)
add_library(${PROJECT_NAME}-alloc-shared SHARED alloc.c)

add_library(${PROJECT_NAME}-dynbuffer-static STATIC dynbuffer.c)
add_library(${PROJECT_NAME}-dynbuffer-shared SHARED dynbuffer.c)
if (${${PROJECT_NAME}-use-alloc-lib})
    target_link_libraries(${PROJECT_NAME}-dynbuffer-static PUBLIC ${PROJECT_NAME}-alloc-static)
    target_link_libraries(${PROJECT_NAME}-dynbuffer-shared PUBLIC ${PROJECT_NAME}-alloc-shared)
endif()

add_library(${PROJECT_NAME}-slist-static STATIC slist.c)
target_link_libraries(${PROJECT_NAME}-slist-static PUBLIC ${PROJECT_NAME}-unarynode-static)
add_library(${PROJECT_NAME}-slist-shared SHARED slist.c)
target_link_libraries(${PROJECT_NAME}-slist-shared PUBLIC ${PROJECT_NAME}-unarynode-shared)

add_library(${PROJECT_NAME}-stack-static STATIC stack.c)
target_link_libraries(${PROJECT_NAME}-stack-static PUBLIC ${PROJECT_NAME}-slist-static)
add_library(${PROJECT_NAME}-stack-shared SHARED stack.c)
target_link_libraries(${PROJECT_NAME}-stack-shared PUBLIC ${PROJECT_NAME}-slist-shared)

add_library(${PROJECT_NAME}-unarynode-static STATIC unarynode.c)
add_library(${PROJECT_NAME}-unarynode-shared SHARED unarynode.c)

add_library(${PROJECT_NAME}-vector-static STATIC vector.c)
add_library(${PROJECT_NAME}-vector-shared SHARED vector.c)