cmake_minimum_required(VERSION 3.17)

project(andromeda)

add_executable(andromeda glad.c main.cpp Shader/Shader.cpp Shader/Shader.h Fileutil/fileutil.cpp Fileutil/fileutil.h Shader/Program.cpp Shader/Program.h)

target_link_libraries(andromeda GL dl glfw)