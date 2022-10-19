//
// Created by jatte on 2022-10-16.
//

#ifndef ANDROMEDA_PROGRAM_H
#define ANDROMEDA_PROGRAM_H


#include "Shader.h"

class Program {
public:
    Program();

    ~Program();

    void link(Shader &shader);

    void use() const;

    bool hasErrors() const;

    void printErrors();

    int32_t getAttribLocation(const char *attribute_name);

private:

    bool error = true;
    std::string errorMsg = "ERROR::PROGRAM: no shader has been linked";

    uint32_t program;

    bool checkError(uint32_t program);
};


#endif //ANDROMEDA_PROGRAM_H
