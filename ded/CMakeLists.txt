cmake_minimum_required(VERSION 3.24)
project(ded)

find_package(SDL2 CONFIG REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

aux_source_directory(src PROJECT_SOURCES)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} include)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)