cmake_minimum_required(VERSION 3.19)
project(Chess)

set(CMAKE_CXX_STANDARD 14)

add_executable(Chess main.cpp)
target_link_libraries(Chess z)