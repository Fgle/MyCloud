cmake_minimum_required(VERSION 3.13)
project(MyCloud)

set(CMAKE_CXX_STANDARD 17)

add_executable(LinuxSystemLearn main.cpp src/tool/connPool/ConnPool.cpp src/tool/connPool/ConnPool.h)
target_link_libraries(MyCloud)