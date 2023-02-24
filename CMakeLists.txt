cmake_minimum_required(VERSION 3.18)
project(leveldb)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g -rdynamic")
#set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
#set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_definitions(-DLEVELDB_PLATFORM_POSIX)
include_directories(include)
aux_source_directory(source/util SOURCE)
aux_source_directory(source/table SOURCE)
aux_source_directory(source/db SOURCE)
add_library(leveldb STATIC ${SOURCE})
target_link_libraries(leveldb pthread)

add_executable(test main.cpp)
target_link_libraries(test leveldb)
