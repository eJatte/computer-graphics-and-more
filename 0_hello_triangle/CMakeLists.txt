cmake_minimum_required(VERSION 3.17)

project(andromeda)

add_executable(andromeda src/glad.c src/main.cpp src/Shader/Shader.cpp src/Shader/Shader.h src/Fileutil/fileutil.cpp src/Fileutil/fileutil.h src/Shader/Program.cpp src/Shader/Program.h)

target_link_libraries(andromeda GL dl glfw)