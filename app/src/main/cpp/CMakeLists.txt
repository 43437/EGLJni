cmake_minimum_required(VERSION 2.8)

set(base_dir ${CMAKE_CURRENT_LIST_DIR})

set(lib_name "EGLib")

file(GLOB src_files
    ${base_dir}/*.cpp
)

message("src file " ${src_files})

include_directories(${base_dir})

add_library(${lib_name} SHARED ${src_files})

target_link_libraries(${lib_name}
                      GLESv1_CM
                      log
)