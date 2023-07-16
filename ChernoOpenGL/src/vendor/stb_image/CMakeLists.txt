include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(stb_image STATIC stb_image.cpp)
target_sources(stb_image PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/stb_image.cpp)
target_include_directories(stb_image PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/stb_image.h")