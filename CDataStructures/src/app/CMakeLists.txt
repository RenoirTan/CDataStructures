if(${${PROJECT_NAME}-build_test})

    add_executable(${PROJECT_NAME}-slist slist.c)
    target_link_libraries(${PROJECT_NAME}-slist PRIVATE ${PROJECT_NAME}-slist-static)

    add_executable(${PROJECT_NAME}-vector vector.c)
    target_link_libraries(${PROJECT_NAME}-vector PRIVATE ${PROJECT_NAME}-vector-static)

endif()
