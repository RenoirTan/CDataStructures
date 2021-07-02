enable_testing()

set(CTEST_BINARY_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin/tests)

include(./testing.cmake)

# from https://skandhurkat.com/post/intro-to-ctest/
file(GLOB test_files "test-*.c")
foreach(file ${test_files})
    string(REGEX REPLACE "(^.*/|\\.[^.]*$)" "" test_name ${file})
    add_unit_test()
endforeach()

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ${TESTNAMES})
