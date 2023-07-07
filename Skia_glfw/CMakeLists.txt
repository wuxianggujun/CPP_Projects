cmake_minimum_required(VERSION 3.25)
project(Skia_glfw)
# -DCMAKE_TOOLCHAIN_FILE=D:/Software/vcpkg/scripts/buildsystems/vcpkg.cmake
set(CMAKE_TOOLCHAIN_FILE "D:/Software/vcpkg/scripts/buildsystems/vcpkg.cmake")


set(CMAKE_CXX_STANDARD 17)


include(D:/Software/vcpkg/scripts/buildsystems/vcpkg.cmake)

add_subdirectory(src)

