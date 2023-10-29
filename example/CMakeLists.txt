cmake_minimum_required(VERSION 3.7.2)

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../installed/cmake/QuantValue)

project(Test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(QuantValue REQUIRED)

add_executable(Test main.cpp)

target_link_libraries(Test QuantValue)
