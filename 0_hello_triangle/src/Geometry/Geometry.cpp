//
// Created by jatte on 2022-10-20.
//

#include "Geometry.h"

#include <utility>

Geometry::Geometry(std::vector<glm::vec4> mVertices) : m_vertices(std::move(mVertices)) {}

void Geometry::upload() {
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo_vertices);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, (GLsizei) (m_vertices.size() * sizeof(this->m_vertices[0])), m_vertices.data(),
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, nullptr);

    if (!m_indices.empty()) {
        glGenBuffers(1, &m_ebo_indices);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_indices);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei) (m_indices.size() * sizeof(this->m_indices[0])),
                     m_indices.data(), GL_STATIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Geometry::render() {
    glBindVertexArray(m_vao);
    if (m_ebo_indices == 0) {
        glDrawArrays(GL_TRIANGLES, 0, (GLsizei) m_vertices.size());
    } else {
        glDrawElements(GL_TRIANGLES, (GLsizei) m_indices.size(), GL_UNSIGNED_SHORT, nullptr);
    }
    glBindVertexArray(0);
}

void Geometry::setIndices(const std::vector<uint16_t> &indices) {
    Geometry::m_indices = indices;
}
