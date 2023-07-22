cmake_minimum_required(VERSION 3.24)
project(Demo_01)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
        src/strquote.cpp)