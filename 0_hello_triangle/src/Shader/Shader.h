//
// Created by jatte on 2022-10-16.
//

#ifndef ANDROMEDA_SHADER_H
#define ANDROMEDA_SHADER_H

#include <string>
#include <glad/glad.h>

class Shader {
public:
    Shader(std::string vsFilename, std::string fsFilename);

    ~Shader();

    void compile();

    uint32_t getVs() const;

    uint32_t getFs() const;

    bool hasErrors() const;

    void printErrors();

private:
    uint32_t vs, fs;

    bool error = true;
    std::string errorMsg = "ERROR::SHADER: no shader has been compiled";

    const std::string vsFilename;
    const std::string fsFilename;

    bool checkError(uint32_t shader, const std::string &type);

    static uint32_t compileShader(const char *shaderSource, uint32_t shaderType);
};


#endif //ANDROMEDA_SHADER_H
