add_executable(slist slist.c)
target_link_libraries(slist PRIVATE ${PROJECT_NAME}-slist-static)

add_executable(vector vector.c)
target_link_libraries(vector PRIVATE ${PROJECT_NAME}-vector-static)
