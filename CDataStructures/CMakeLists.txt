cmake_minimum_required(VERSION 3.12)
project(CDataStructures VERSION 0.1.0)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)

set(${PROJECT_NAME}-build_test ON CACHE BOOL "Whether to build tests or not.")
message(STATUS "Build test executables - ${${PROJECT_NAME}-build_test}")
set(${PROJECT_NAME}-substitute-unstable ON CACHE BOOL "Whether to use the currently unstable API instead of the stable ones.")
message(STATUS "Substitute using unstable API - ${${PROJECT_NAME}-substitute-unstable}")
set(CMAKE_BUILD_TYPE Debug)
message(STATUS "CMake Build Type - ${CMAKE_BUILD_TYPE}")
set(CMAKE_C_STANDARD 90)
message(STATUS "C Standard - c${CMAKE_C_STANDARD}")


set(${PROJECT_NAME}-debug-output OFF CACHE BOOL "Whether to show debug output.")
message(STATUS "Show debug output - ${${PROJECT_NAME}-debug-output}")
set(${PROJECT_NAME}-use-alloc-lib OFF CACHE BOOL "Whether to use the custom alloc library written for this project.")
message(STATUS "Use custom alloc library - ${${PROJECT_NAME}-use-alloc-lib}")


add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=1)

if(${${PROJECT_NAME}-debug-output})
    set(CDS_DEBUG ON)
else()
    set(CDS_DEBUG OFF)
endif()
if(${${PROJECT_NAME}-use-alloc-lib})
    set(CDS_USE_ALLOC_LIB ON)
else()
    set(CDS_USE_ALLOC_LIB OFF)
endif()
configure_file(${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/_config.h.in ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/_config.h)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
