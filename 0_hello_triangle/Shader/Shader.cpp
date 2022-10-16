//
// Created by jatte on 2022-10-16.
//

#include "Shader.h"

#include <utility>
#include <iostream>
#include "../Fileutil/fileutil.h"

Shader::Shader(std::string vsFile, std::string fsFile) : vsFilename(std::move(vsFile)),
                                                         fsFilename(std::move(fsFile)),
                                                         vs(0),
                                                         fs(0) {}

void Shader::compile() {
    auto vsSource = fileutil::readFile(vsFilename);
    auto fsSource = fileutil::readFile(fsFilename);

    vs = compileShader(vsSource.c_str(), GL_VERTEX_SHADER);
    if (checkError(vs, "VERTEX")) { return; }
    fs = compileShader(fsSource.c_str(), GL_FRAGMENT_SHADER);
    if (checkError(fs, "FRAGMENT")) { return; }
}

uint32_t Shader::compileShader(const char *shaderSource, uint32_t shaderType) {
    unsigned int shader = glCreateShader(shaderType);

    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    return shader;
}

uint32_t Shader::getVs() const {
    return vs;
}

uint32_t Shader::getFs() const {
    return fs;
}

bool Shader::hasErrors() const {
    return error;
}

void Shader::printErrors() {
    if (error) {
        std::cout << errorMsg << std::endl;
    }
}

bool Shader::checkError(uint32_t shader, const std::string &type) {
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    error = false;
    if (!success) {
        error = true;
        char msg[512];
        glGetShaderInfoLog(shader, 512, nullptr, msg);
        errorMsg = "ERROR::SHADER_COMPILE::" + type + "\n" + msg;
    }
    return !success;
}
