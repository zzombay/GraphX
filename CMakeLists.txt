cmake_minimum_required(VERSION 3.28)
project(GraphX)

set(CMAKE_CXX_STANDARD 17)

add_executable(GraphX src/main.cpp)


set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw-3.4)
target_link_libraries(GraphX PRIVATE glfw)

find_package(OpenGL REQUIRED)
target_link_libraries(GraphX PRIVATE OpenGL::GL)

add_subdirectory(libs/glad)
target_link_libraries(GraphX PRIVATE glad)