cmake_minimum_required(VERSION 3.24)
project(SFML_BlackWhite LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

# Additional resources like images and fonts
configure_file(res/OpenSans-Regular.ttf OpenSans-Regular.ttf COPYONLY)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# 添加源文件目录
aux_source_directory(src SOURCE_FILES)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}> COMMAND_EXPAND_LISTS)
endif ()

install(TARGETS ${PROJECT_NAME})

