cmake_minimum_required(VERSION 3.24)
project(MineSweep VERSION 0.1.0 LANGUAGES CXX)


# 指定源文件夹路径
set(source_folder "${CMAKE_CURRENT_SOURCE_DIR}/resources")

# 指定目标文件夹路径
set(destination_folder "${CMAKE_CURRENT_SOURCE_DIR}/build")

# 将源文件夹复制到目标文件夹
file(COPY ${source_folder} DESTINATION ${destination_folder})


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(INCLUDE_HEADER include/pch.hpp
        include/window.hpp
        include/context.hpp
        include/renderer.hpp
        include/matrix.hpp)

find_package(SDL2 REQUIRED)
# 添加SDL2头文件路径
include_directories(${SDL2_INCLUDE_DIRS})


aux_source_directory(src SRC)
add_executable(${PROJECT_NAME} ${SRC}
        ${INCLUDE_HEADER})
target_include_directories(${PROJECT_NAME} PRIVATE include)
# 添加SDL2链接库
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
# 采用c++ 17的风格来编译
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
