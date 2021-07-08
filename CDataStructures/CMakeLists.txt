cmake_minimum_required(VERSION 3.12)
project(CDataStructures VERSION 0.1.0)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_STANDARD 90)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=1)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
