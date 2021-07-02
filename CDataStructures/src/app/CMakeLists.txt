add_executable(vector vector.c)
target_link_libraries(vector PRIVATE ${PROJECT_NAME}-vector-static)
