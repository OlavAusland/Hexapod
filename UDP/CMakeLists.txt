cmake_minimum_required(VERSION 3.18)

#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(UDP)

add_library(UDP STATIC)
add_library(UDP::UDP ALIAS UDP)

if(WIN32)
    set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/Windows")
else()
    set(SOURCE_PATH "${PROJECT_SOURCE_DIR}/Linux}")
endif()

message(${SOURCE_PATH})

target_include_directories(UDP PUBLIC ${SOURCE_PATH})

add_subdirectory(${SOURCE_PATH})
