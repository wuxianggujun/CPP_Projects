cmake_minimum_required(VERSION 3.25)
project(ChernoOpenGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)
# 指定源文件夹路径
set(source_folder "${CMAKE_CURRENT_SOURCE_DIR}/res")

# 指定目标文件夹路径
set(destination_folder "${CMAKE_CURRENT_SOURCE_DIR}/build")

# 将源文件夹复制到目标文件夹
file(COPY ${source_folder} DESTINATION ${destination_folder})

add_subdirectory(src)