//
// Created by jatte on 2022-10-20.
//

#ifndef ANDROMEDA_GEOMETRY_H
#define ANDROMEDA_GEOMETRY_H

#include <glm/glm.hpp>
#include <vector>
#include <glad/glad.h>
#include "../Shader/Program.h"

class Geometry {
public:
    Geometry(std::vector<glm::vec4> vertices);

    void upload();

    void render();

    void setIndices(const std::vector<uint16_t> &indices);

private:
    uint32_t m_vbo_vertices = 0, m_ebo_indices = 0, m_vao = 0;

    std::vector<glm::vec4> m_vertices;
    std::vector<uint16_t> m_indices;
};


#endif //ANDROMEDA_GEOMETRY_H
