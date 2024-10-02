cmake_minimum_required(VERSION 3.18)
project(Hexapod)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")
#set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
add_subdirectory(vendors)
add_subdirectory(src)

include_directories(res)
include_directories(src)

target_compile_definitions(${PROJECT_NAME} PUBLIC GLEW_STATIC)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${OPENGL_INCLUDE_DIRS}
    "${CMAKE_CURRENT_SOURCE_DIR}/vendors/GLFW/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendors/glew/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendors/"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/"
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    ${OPENGL_LIBRARIES}
    "${CMAKE_CURRENT_SOURCE_DIR}/vendors/glew/lib/Release/x64/glew32s.lib"
    #"${CMAKE_CURRENT_SOURCE_DIR}/vendors/glfw/lib-mingw-w64/libglfw3.a"
    "${CMAKE_CURRENT_SOURCE_DIR}/vendors/glfw/lib-vc2022/glfw3.lib"
    
)
