//
// Created by jatte on 2022-10-16.
//

#include <iostream>
#include "Program.h"

Program::Program() {
    program = glCreateProgram();
}

void Program::link(Shader &shader) {
    glAttachShader(program, shader.getVs());
    glAttachShader(program, shader.getFs());
    glLinkProgram(program);
    checkError(program);
}

void Program::use() const {
    glUseProgram(program);
}

bool Program::hasErrors() const {
    return error;
}

void Program::printErrors() {
    if (error) {
        std::cout << errorMsg << std::endl;
    }
}

bool Program::checkError(uint32_t shader) {
    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);

    error = false;
    if (!success) {
        error = true;
        char msg[512];
        glGetProgramInfoLog(shader, 512, nullptr, msg);
        errorMsg = "ERROR::SHADER_COMPILE::\n";
        errorMsg += msg;
    }
    return !success;
}
