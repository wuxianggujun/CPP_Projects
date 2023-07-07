cmake_minimum_required(VERSION 3.24)
project(CPP_Projects)

set(CMAKE_TOOLCHAIN_FILE "D:/Software/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_CXX_STANDARD 17)
include(D:/Software/vcpkg/scripts/buildsystems/vcpkg.cmake)

add_subdirectory(ChernoOpenGL)
add_subdirectory(Demo_01)
add_subdirectory(Skia_glfw)
