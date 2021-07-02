cmake_minimum_required(VERSION 3.12)
project(CDataStructures VERSION 0.1.0)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)

include_directories(./include)

add_subdirectory(src)
