cmake_minimum_required(VERSION 2.8.9)
project(mario)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
include_directories(include)

file(GLOB SOURCES "../src/*.cpp")
 
add_executable(testStudent ${SOURCES})