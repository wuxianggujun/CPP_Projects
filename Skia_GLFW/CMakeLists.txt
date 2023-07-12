cmake_minimum_required(VERSION 3.25)
project(Skia_glfw)
# -DCMAKE_TOOLCHAIN_FILE=D:/Software/vcpkg/scripts/buildsystems/vcpkg.cmake
#set(CMAKE_TOOLCHAIN_FILE "D:/Software/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(CMAKE_CXX_STANDARD 17)
#include(D:/Software/vcpkg/scripts/buildsystems/vcpkg.cmake)

find_package(glfw3 CONFIG REQUIRED)
find_package(unofficial-skia CONFIG REQUIRED)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} PROJECT_SOURCES)

set(PROJECT_SOURCES ${PROJECT_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_subdirectory(glad)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

#[[target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)]]

target_link_libraries(${PROJECT_NAME} PRIVATE glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::skia::skia)

