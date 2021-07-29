if(${${PROJECT_NAME}-build_test})

    add_executable(${PROJECT_NAME}-alloc alloc.c)
    target_link_libraries(${PROJECT_NAME}-alloc PRIVATE ${PROJECT_NAME}-alloc-static)

    add_executable(${PROJECT_NAME}-functional functional.c)

    add_executable(${PROJECT_NAME}-stack stack.c)
    target_link_libraries(${PROJECT_NAME}-stack PRIVATE ${PROJECT_NAME}-stack-static)

    add_executable(${PROJECT_NAME}-slist slist.c)
    target_link_libraries(${PROJECT_NAME}-slist PRIVATE ${PROJECT_NAME}-slist-static)

    add_executable(${PROJECT_NAME}-vector vector.c)
    target_link_libraries(${PROJECT_NAME}-vector PRIVATE ${PROJECT_NAME}-vector-static)

endif()
