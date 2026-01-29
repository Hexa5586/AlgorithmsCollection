cmake_minimum_required(VERSION 3.10)
project(HoshiInoriCollections)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB ALGO_SOURCES "Algorithms/*.cpp")

add_library(Algorithms OBJECT ${ALGO_SOURCES})

add_executable(TestAlgorithms TestAlgorithms.cpp)

target_link_libraries(TestAlgorithms PRIVATE Algorithms)