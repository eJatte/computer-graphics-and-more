cmake_minimum_required(VERSION 3.17)

project(hello_triangle)

add_executable(hello_triangle glad.c main.cpp)

target_link_libraries(hello_triangle GL dl glfw)