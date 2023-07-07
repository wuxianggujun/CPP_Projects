aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_LIST)

set(PROJECT_SOURCES ${SRC_LIST})

find_package(GLEW CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)


add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic -Werror>
)
target_link_libraries(${PROJECT_NAME} PRIVATE GLEW::GLEW)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
