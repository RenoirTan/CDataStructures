# from https://bertvandenbroucke.netlify.app/2019/12/12/unit-testing-with-ctest/
# adapted because the syntax seemed dodgy

macro(add_unit_test)
    set(options PARALLEL)
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCES LIBS)
    cmake_parse_arguments(TEST "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    message(STATUS "generating ${TEST_NAME}")
    add_executable(${TEST_NAME} EXCLUDE_FROM_ALL ${TEST_SOURCES})
    target_link_libraries(${TEST_NAME} ${TEST_LIBS})

    if(TEST_PARALLEL AND HAVE_MPI)
      set(TESTCOMMAND ${MPIEXEC})
      set(TESTARGS ${MPIEXEC_NUMPROC_FLAG} 3 ${MPIEXEC_PREFLAGS} "./${TEST_NAME}" ${MPIEXEC_POSTFLAGS})
      set(TESTCOMMAND ${TESTCOMMAND} ${TESTARGS})
    else()
      set(TESTCOMMAND ${TEST_NAME})
    endif()

    add_test(NAME ${TEST_NAME} WORKING_DIRECTORY ${CTEST_BINARY_DIRECTORY} COMMAND ${TESTCOMMAND})
    add_custom_target(check_${TEST_NAME} COMMAND ${CMAKE_CTEST_COMMAND} -R ${TEST_NAME} DEPENDS ${TEST_NAME})

    set(TESTNAMES ${TESTNAMES} ${TEST_NAME})
endmacro()