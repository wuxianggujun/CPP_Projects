aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)

set(PROJECT_SOURCES ${SRC_LIST})

find_package(GLEW CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

# 添加第三方库
add_subdirectory(vendor/stb_image)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# 如果不注释掉，没有使用的函数也会导致报错，无法编译，可恶
#[[target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)]]
target_link_libraries(${PROJECT_NAME} PRIVATE stb_image)
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

