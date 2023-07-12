aux_source_directory(src DIR_LIB_SRCS)

add_library(glad STATIC ${DIR_LIB_SRCS})

target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
