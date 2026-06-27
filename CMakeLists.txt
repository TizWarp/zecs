cmake_minimum_required(VERSION 4.3)
project(ZenECS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
file(GLOB_RECURSE ecs_src CONFIGURE_DEPENDS ./src/*.cpp)


add_library(ZECS SHARED ${ecs_src})
include_directories(ZECS ./include)

add_executable(test_ecs ./tests.cpp)
include_directories(test_ecs ./src)
target_link_libraries(test_ecs ZECS)
